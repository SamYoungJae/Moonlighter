#include "stdafx.h"
#include "potionShop.h"

HRESULT potionShop::init()
{
	//���̵�Ŵ��� �ʱ�ȭ 
	_fadeManager = new fadeManager;
	_fadeManager->init();

	//���ǽ��� �ʱ�ȭ 
	initPotionSlot();
	_potionCtrl = POTION_MENU;
	_messageType = LACK_OF_GOLD;

	//�̵��޴� Ŭ���� �ʱ�ȭ 
	_potionMenu = new movingObject;
	_potionMenu->init(IMAGEMANAGER->findImage("menu_potion"),
		POTION_MENUPOSX, WINSIZEY, 90.f);

	_shopBanner = new movingObject;
	_shopBanner->init(IMAGEMANAGER->findImage("shop_nameBase"),
		POTION_BANNERPOSX, -IMAGEMANAGER->findImage("shop_nameBase")->getHeight(), 20.f);

	_eKeyIcon = new movingObject;
	_eKeyIcon->init(IMAGEMANAGER->findImage("icon_potionKeyE"),
		WINSIZEX, POTION_EKEYPOSY, 20.f);

	//Ŀ�� �ʱ�ȭ 
	_cursor = new cursor;
	_cursor->init();
	initCursor();

	//�޴� ���� �ݱ� ���� ���� �ʱ�ȭ 
	_menuOn = false; 
	_openMenu = false; 
	_closeMenu = false; 
	_showBannerTxt = false; 

	return S_OK;
}

void potionShop::release()
{
	SAFE_DELETE(_fadeManager);
	SAFE_DELETE(_potionMenu);
	SAFE_DELETE(_shopBanner);
	SAFE_DELETE(_eKeyIcon);
	SAFE_DELETE(_cursor);
}

void potionShop::update()
{
	_fadeManager->update();
	_cursor->update();

	//�޴� ���� �ݱ� 
	toggleMenu();
	openMenu();
	closeMenu();

	if (_menuOn)
	{
		//Ű�Է� �Լ� 
		keyInput();

	}
}

void potionShop::render()
{
	_fadeManager->render(getMemDC());

	//char str[100];
	//wsprintf(str, "cursorIdx : %d", _cursor->getSlotIdx());
	//TextOut(getMemDC(), 10, 130, str, strlen(str));
	
	if (!_menuOn) return; 

	//�����޴� �̹��� ��� 
	potionMenuRender();

	//�����̸� �ؽ�Ʈ ��� 
	if (_showBannerTxt) bannerTextRender();

	//�޴��� �����Ǿ����� ���� ��� 
	if (_cursor->getShowCursor())
	{
		potionMenuTextRender();
		potionInfoRender();
		recipeInfoRender();

		switch (_potionCtrl)
		{
			case POTION_MENU:
				_cursor->render(getMemDC());
				break;

			case POTION_MESSAGE:
				printMessage();
				break;

			case POTION_SET_COUNT:
				break;

			case POTION_SET_OX:
				_cursor->render(getMemDC());
				break;
		}
	}
}

void potionShop::toggleMenu()
{
	if (INPUT->GetKeyDown('O'))
	{
		//���� �޴��� ���� �ְų� �ݰ� �ִ� ���̶�� �Լ� ���� 
		if (_openMenu || _closeMenu) return;

		if (_menuOn)
		{
			_closeMenu = true;
			_showBannerTxt = false; 
			_fadeManager->fadeInit(16, FADE_IN);
			_cursor->setShowCursor(false);
		}
		else
		{
			_menuOn = true;
			_openMenu = true;

			//�������̽� �������� ���� 
			PLAYERDATA->setRenderHp(false);
			PLAYERDATA->setRenderKeyInfo(false);
			PLAYERDATA->setRenderItemCount(false);

			//�����۸޴��� Ű�Է��� ���� �ʴ´�.(�޴��� Ű���� ���� �浹�ϱ� ����)
			ITEMMENU->setCanKeyInput(false);
			_fadeManager->fadeInit(16, FADE_OUT, 205);
			SOUNDMANAGER->play("witch_Open", 0.5f);
		}
	}
}

void potionShop::initMenuPos()
{
	//���Ǹ޴� ��ġ �ʱ�ȭ 
	_potionMenu->initPos(POTION_MENUPOSX, WINSIZEY);
	_shopBanner->initPos(POTION_BANNERPOSX, -(_shopBanner->getImg()->getHeight()));
	_eKeyIcon->initPos(WINSIZEX, POTION_EKEYPOSY);

	//��ȭ�޴� ��ġ �ʱ�ȭ 
}

void potionShop::openPotionMenu()
{
	//���� �޴��� ���� �ְų� �ݰ� �ִ� ���̶�� �Լ� ���� 
	if (_openMenu || _closeMenu) return;

	_menuOn = true;
	_openMenu = true;
	
	//�������̽� �������� ���� 
	PLAYERDATA->setRenderHp(false);
	PLAYERDATA->setRenderKeyInfo(false);
	PLAYERDATA->setRenderItemCount(false);

	//�����۸޴��� Ű�Է��� ���� �ʴ´�.(�޴��� Ű���� ���� �浹�ϱ� ����)
	ITEMMENU->setCanKeyInput(false);

	_fadeManager->fadeInit(16, FADE_OUT, 205);
	SOUNDMANAGER->play("witch_Open", 0.5f);
}

void potionShop::closePotionMenu()
{
	//���� �޴��� ���� �ְų� �ݰ� �ִ� ���̶�� �Լ� ���� 
	if (_openMenu || _closeMenu) return;

	_closeMenu = true;
	_fadeManager->fadeInit(16, FADE_IN);
	_cursor->setShowCursor(false);
}

void potionShop::openMenu()
{
	if (!_openMenu) return;

	_potionMenu->moveUp(POTION_MENUPOSY);
	_shopBanner->moveDown(POTION_BANNERPOSY);
	_eKeyIcon->moveLeft(POTION_EKEYPOSX);

	if (_shopBanner->getIsArrived()) _showBannerTxt = true; 

	//��� �� ��ġ�� �������� �� 
	if (_potionMenu->getIsArrived() && _shopBanner->getIsArrived() && _eKeyIcon->getIsArrived())
	{
		_openMenu = false; 
		_potionMenu->setIsArrived(false);
		_shopBanner->setIsArrived(false);
		_eKeyIcon->setIsArrived(false);
		
		initCursor();
		_cursor->setShowCursor(true);
		_cursor->setCursorState(CURSOR_MOVE);
	}
}

void potionShop::closeMenu()
{
	if (!_closeMenu) return;

	_potionMenu->moveDown(WINSIZEY);
	_shopBanner->moveUp(-(_shopBanner->getImg()->getHeight()));
	_eKeyIcon->moveRight(WINSIZEX);

	//��� �� ��ġ�� �������� �� 
	if (_potionMenu->getIsArrived() && _shopBanner->getIsArrived() && _eKeyIcon->getIsArrived())
	{
		_menuOn = false; 
		_closeMenu = false;

		//���Ǹ޴� ������ ���� 
		_potionMenu->setIsArrived(false);
		_shopBanner->setIsArrived(false);
		_eKeyIcon->setIsArrived(false);

		//�������̽� �������� ���� 
		PLAYERDATA->setRenderHp(true);
		PLAYERDATA->setRenderKeyInfo(true);
		PLAYERDATA->setRenderItemCount(true);

		//�����۸޴� Ű�Է� �ޱ� 
		ITEMMENU->setCanKeyInput(true);
	}
}

void potionShop::initPotionSlot()
{
	memset(_potionSlot, 0, sizeof(_potionSlot));

	//���� 1��(HP����1 ����)
	_potionSlot[0].slotIdx = 0;
	_potionSlot[0].type = POTION_BUY;
	_potionSlot[0].item = ITEMMENU->getItemManager()->getItemByIdx(POTION1_IDX);
	_potionSlot[0].price = 400;
	_potionSlot[0].description[0] = "ü���� 40 ȸ���Ѵ�. �ѵ� ��";
	_potionSlot[0].description[1] = "������ �׻� �޴��ϴ� �� ����.";
	
	//���� 2��(HP����1 ����)
	_potionSlot[1].slotIdx = 1;
	_potionSlot[1].type = POTION_MAKE;
	_potionSlot[1].item = ITEMMENU->getItemManager()->getItemByIdx(POTION1_IDX);
	_potionSlot[1].price = 125;
	_potionSlot[1].description[0] = "ü���� 40 ȸ���Ѵ�. �ѵ� ��";
	_potionSlot[1].description[1] = "������ �׻� �޴��ϴ� �� ����.";
	_potionSlot[1].mixRecipe = new recipe;
	_potionSlot[1].mixRecipe->addMaterial(RICHJELLY_IDX, 1);
	
	//���� 3��(HP����2 ����)
	_potionSlot[2].slotIdx = 2;
	_potionSlot[2].type = POTION_BUY;
	_potionSlot[2].item = ITEMMENU->getItemManager()->getItemByIdx(POTION2_IDX);
	_potionSlot[2].price = 2500;
	_potionSlot[2].description[0] = "ü���� 75 ȸ���Ѵ�. ������";
	_potionSlot[2].description[1] = "������ �ϴ� ��ǰ�̴�.";

	//���� 2��(HP����2 ����)
	_potionSlot[3].slotIdx = 3;
	_potionSlot[3].type = POTION_MAKE;
	_potionSlot[3].item = ITEMMENU->getItemManager()->getItemByIdx(POTION2_IDX);
	_potionSlot[3].price = 800;
	_potionSlot[3].description[0] = "ü���� 75 ȸ���Ѵ�. ������";
	_potionSlot[3].description[1] = "������ �ϴ� ��ǰ�̴�.";
	_potionSlot[3].mixRecipe = new recipe;
	_potionSlot[3].mixRecipe->addMaterial(RICHJELLY_IDX, 10);
	_potionSlot[3].mixRecipe->addMaterial(VENOMJELLY_IDX, 15);
}

void potionShop::initCursor()
{
	_cursor->setSlotIdx(0);
	_cursor->setDestX(POTION_CURSORX);
	_cursor->setDestY(POTION_CURSORY);
}

void potionShop::setPotionCtrl(POTION_CTRL state)
{
	switch (state)
	{
		case POTION_MENU:
			_potionCtrl = state;
			break;

		case POTION_MESSAGE:
			_potionCtrl = state;
			break;

		case POTION_SET_COUNT:
			_potionCtrl = state;
			break;

		case POTION_SET_OX:
			_potionCtrl = state;
			break;
	}
}

bool potionShop::checkRequirements()
{
	//���濡 ������ ���ٸ� ����,���� ������� false
	int itemIdx = _potionSlot[_cursor->getSlotIdx()].item.getItemIdx();
	if (!ITEMMENU->getInventory()->checkRoomForItem(itemIdx))
	{
		_messageType = LACK_OF_ROOM;
		setPotionCtrl(POTION_MESSAGE);
		SOUNDMANAGER->play("cursor_error", 0.6f);
		return false; 
	}

	//���� ���� �� ��� �������θ� Ȯ�� 
	if (_potionSlot[_cursor->getSlotIdx()].type == POTION_BUY)
	{
		//���� �������� ��尡 �̿��ݺ��� ���� ��� ��� �޽��� ���� return
		if (PLAYERDATA->getGold() < _potionSlot[_cursor->getSlotIdx()].price)
		{
			_messageType = LACK_OF_GOLD;
			setPotionCtrl(POTION_MESSAGE);
			SOUNDMANAGER->play("cursor_error", 0.6f);
			return false; 
		}
		else return true;
	}
	else //���� ���� �� ����������� + ����������� Ȯ�� 
	{
		//��ᰡ ������ ��� 
		if (!_potionSlot[_cursor->getSlotIdx()].mixRecipe->checkRequirements())
		{
			//��尡 �����ϴٸ� ���,������ �޽��� ���� 
			if (PLAYERDATA->getGold() < _potionSlot[_cursor->getSlotIdx()].price)
			{
				_messageType = LACK_OF_BOTH;
				setPotionCtrl(POTION_MESSAGE);
				SOUNDMANAGER->play("cursor_error", 0.6f);
				return false;
			}
			else
			{
				_messageType = LACK_OF_MATERIAL;
				setPotionCtrl(POTION_MESSAGE);
				SOUNDMANAGER->play("cursor_error", 0.6f);
				return false; 
			}
		}
		else //��ᰡ �������� ���� ��� 
		{
			//��尡 �����ϴٸ� ������ �޽��� ���� 
			if (PLAYERDATA->getGold() < _potionSlot[_cursor->getSlotIdx()].price)
			{
				_messageType = LACK_OF_GOLD;
				setPotionCtrl(POTION_MESSAGE);
				SOUNDMANAGER->play("cursor_error", 0.6f);
				return false;
			}
			else return true; 
		}
	}
}

void potionShop::printMessage()
{
	switch (_messageType)
	{
		case LACK_OF_GOLD:
			printLackOfGold();
			break;

		case LACK_OF_MATERIAL:
			printLackOfMaterial();
			break;

		case LACK_OF_BOTH:
			printLackOfBoth();
			break;

		case LACK_OF_ROOM:
			printLackOfRoom();
			break;
	}
}

void potionShop::printLackOfGold()
{
	IMAGEMANAGER->render("shop_bubble", getMemDC(), 328, 120);

	RECT txtRC = RectMake(356, 168, 400, 54);
	HFONT font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(230, 215, 187));
	DrawText(getMemDC(), "��尡 ������� �ʾ�.",
		-1, &txtRC, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);
}

void potionShop::printLackOfMaterial()
{
	IMAGEMANAGER->render("shop_bubble", getMemDC(), 328, 120);

	char tempStr[64];
	strcpy(tempStr, _potionSlot[_cursor->getSlotIdx()].mixRecipe->getShortMaterialName());
	strcat(tempStr, " �������� ����.");

	RECT txtRC = RectMake(356, 168, 448, 54);
	HFONT font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(230, 215, 187));
	DrawText(getMemDC(), tempStr,
		-1, &txtRC, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);
}

void potionShop::printLackOfBoth()
{
	IMAGEMANAGER->render("shop_bubble", getMemDC(), 328, 120);

	RECT txtRC = RectMake(356, 168, 400, 54);
	HFONT font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(230, 215, 187));
	DrawText(getMemDC(), "�ʿ��� ��ᳪ ��尡 ������.",
		-1, &txtRC, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);
}

void potionShop::printLackOfRoom()
{
	IMAGEMANAGER->render("shop_bubble", getMemDC(), 328, 120);

	RECT txtRC = RectMake(356, 168, 400, 54);
	HFONT font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(230, 215, 187));
	DrawText(getMemDC(), "���濡 �������� ���� ������ ������.",
		-1, &txtRC, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);
}

void potionShop::buyPotion()
{
}

void potionShop::makePotion()
{
}

void potionShop::keyInput()
{
	switch (_potionCtrl)
	{
		case POTION_MENU:
			menuKeyInput();
			break;

		case POTION_MESSAGE:
			messageKeyInput();

		case POTION_SET_COUNT:
			break;

		case POTION_SET_OX:
			break;
	}
}

void potionShop::menuKeyInput()
{
	//�����¿� Ű�Է� 
	if (INPUT->GetKeyDown('A'))
	{
		leftKeyDown();
		_cursor->setCursorState(CURSOR_MOVE);
	}
	if (INPUT->GetKeyDown('D'))
	{
		rightKeyDown();
		_cursor->setCursorState(CURSOR_MOVE);
	}
	if (INPUT->GetKeyDown('W'))
	{
		upKeyDown();
		_cursor->setCursorState(CURSOR_MOVE);
	}
	if (INPUT->GetKeyDown('S'))
	{
		downKeyDown();
		_cursor->setCursorState(CURSOR_MOVE);
	}

	//JŰ �Է�(���� ����)
	if (INPUT->GetKeyDown('J'))
	{
		_cursor->setCursorState(CURSOR_CLICK);

		if (_cursor->getSlotIdx() >= POTION_MAXSLOT) return; 

		//���� ������ ���� �ʿ��� �������� Ȯ���ϰ� ����,������ ���� �Լ� ���� 
		//if (_potionSlot[_cursor->getSlotIdx()].type == POTION_BUY)
		//{
		//	if(checkRequirements()) buyPotion();
		//	SOUNDMANAGER->play("cursor_move", 0.2f);
		//}
		//else
		//{
		//	if(checkRequirements()) makePotion();
		//	SOUNDMANAGER->play("cursor_move", 0.2f);
		//}

		if (checkRequirements()) setPotionCtrl(POTION_SET_COUNT);
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}
}

void potionShop::messageKeyInput()
{
	if (INPUT->GetKeyDown('J') || INPUT->GetKeyDown('L'))
	{
		setPotionCtrl(POTION_MENU);
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}
}

void potionShop::setCountKeyInput()
{
}

void potionShop::leftKeyDown()
{
	switch (_cursor->getSlotIdx())
	{
		case 0: case 4:
			_cursor->setSlotIdx(_cursor->getSlotIdx() + 3);
			_cursor->setDestX(_cursor->getDestX() + POTION_CURSOR_DISTANCE * 3);
			break;

		default:
			_cursor->setSlotIdx(_cursor->getSlotIdx() - 1);
			_cursor->setDestX(_cursor->getDestX() - POTION_CURSOR_DISTANCE);
			break;
	}
}

void potionShop::rightKeyDown()
{
	switch (_cursor->getSlotIdx())
	{
		case 3: case 7:
			_cursor->setSlotIdx(_cursor->getSlotIdx() - 3);
			_cursor->setDestX(_cursor->getDestX() - POTION_CURSOR_DISTANCE * 3);
			break;

		default:
			_cursor->setSlotIdx(_cursor->getSlotIdx() + 1);
			_cursor->setDestX(_cursor->getDestX() + POTION_CURSOR_DISTANCE);
			break;
	}
}

void potionShop::upKeyDown()
{
	switch (_cursor->getSlotIdx())
	{
		//case 0: case 1: case 2: case 3:
		//	_cursor->setSlotIdx(_cursor->getSlotIdx() + 4);
		//	_cursor->setDestY(_cursor->getDestY() + POTION_CURSOR_DISTANCE);
		//	break;

		case 4: case 5: case 6: case 7:
			_cursor->setSlotIdx(_cursor->getSlotIdx() - 4);
			_cursor->setDestY(_cursor->getDestY() - POTION_CURSOR_DISTANCE);
			break;
	}
}

void potionShop::downKeyDown()
{
	switch (_cursor->getSlotIdx())
	{
		case 0: case 1: case 2: case 3:
			_cursor->setSlotIdx(_cursor->getSlotIdx() + 4);
			_cursor->setDestY(_cursor->getDestY() + POTION_CURSOR_DISTANCE);
			break;

		//default:
		//	_cursor->setSlotIdx(_cursor->getSlotIdx() - 4);
		//	_cursor->setDestY(_cursor->getDestY() - POTION_CURSOR_DISTANCE);
		//	break;
	}
}

void potionShop::bannerTextRender()
{
	//��ȣ�� '���� ����' ��� 
	RECT txtRC = RectMake(538, 30, 126, 40);
	HFONT font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(236, 221, 182));
	DrawText(getMemDC(), "���� ����", -1, &txtRC, DT_CENTER | DT_WORDBREAK | DT_VCENTER);
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);
}

void potionShop::potionMenuRender()
{
	_shopBanner->render(getMemDC());
	_potionMenu->render(getMemDC());
	_eKeyIcon->render(getMemDC());
}

void potionShop::potionMenuTextRender()
{
	//���Ǹ޴� '���� ���:' ���  
	RECT txtRC1 = RectMake(425, 132, 92, 30);
	HFONT font = CreateFont(19, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(81, 75, 64));
	DrawText(getMemDC(), "���� ���:", -1, &txtRC1, DT_CENTER | DT_WORDBREAK | DT_VCENTER);
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);

	//���Ǹ޴� '������' ���  
	RECT txtRC2 = RectMake(890, 372, 60, 30);
	oFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(50, 50, 50));
	DrawText(getMemDC(), "������", -1, &txtRC2, DT_CENTER | DT_WORDBREAK | DT_VCENTER);
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);
}

void potionShop::potionInfoRender()
{
	if (_cursor->getSlotIdx() >= POTION_MAXSLOT) return;

	potionIconRender();
	potionNameRender();
	potionDesRender();
	potionPriceRender();
	possessCountRender();
}

void potionShop::potionIconRender()
{
	_potionSlot[_cursor->getSlotIdx()].item.getItemImg()->render(getMemDC(), 1104, 80);
}

void potionShop::potionNameRender()
{
	RECT txtRC = RectMake(960, 24, 144, 24);
	HFONT font = CreateFont(19, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(81, 75, 64));
	DrawText(getMemDC(), _potionSlot[_cursor->getSlotIdx()].item.getName(),
		-1, &txtRC, DT_CENTER | DT_WORDBREAK | DT_VCENTER);
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);
}

void potionShop::potionDesRender()
{
	for (int i = 0; i < 2; i++)
	{
		RECT txtRC = RectMake(914, 180 + (i * 28), 260, 36);
		HFONT font = CreateFont(19, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
		HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
		SetTextColor(getMemDC(), RGB(223, 209, 181));
		DrawText(getMemDC(), _potionSlot[_cursor->getSlotIdx()].description[i],
			-1, &txtRC, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
		SelectObject(getMemDC(), oFont);
		DeleteObject(font);
	}
}

void potionShop::potionPriceRender()
{
	for (int i = 1, distance = 0; i <= _potionSlot[_cursor->getSlotIdx()].price; i *= 10)
	{
		int number = (_potionSlot[_cursor->getSlotIdx()].price / i) % 10;

		char keyName[16];
		wsprintf(keyName, "%d_black", number);
		IMAGEMANAGER->render(keyName, getMemDC(), 1120 - (distance * 12), 378);

		distance++;
	}
}

void potionShop::possessCountRender()
{
	RECT txtRC = RectMake(914, 146, 44, 24);
	HFONT font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(220, 206, 180));
	DrawText(getMemDC(), "����:", -1, &txtRC, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);

	int multiplyCount = 0;
	int potionCount = ITEMMENU->getInventory()->getCountByIdx(
		_potionSlot[_cursor->getSlotIdx()].item.getItemIdx());
	int count = potionCount;

	while (true)
	{
		if (count / 10 != 0)
		{
			count /= 10;
			multiplyCount++;
		}
		else break;
	}

	for (int i = 1; i <= potionCount; i *= 10)
	{
		int number = (potionCount / i) % 10;

		char keyName[16];
		wsprintf(keyName, "%d", number);
		IMAGEMANAGER->render(keyName, getMemDC(), 962 + (multiplyCount * 12), 146);

		multiplyCount--;
	}
}

void potionShop::recipeInfoRender()
{
	if (_cursor->getSlotIdx() >= POTION_MAXSLOT ||
		_potionSlot[_cursor->getSlotIdx()].type == POTION_BUY) return;

	_potionSlot[_cursor->getSlotIdx()].mixRecipe->render(getMemDC(), 892, 430);
}

void potionShop::setCountRender()
{
}




