#include "stdafx.h"
#include "potionShop.h"

HRESULT potionShop::init()
{
	//���̵�Ŵ��� �ʱ�ȭ 
	_fadeManager = new fadeManager;
	_fadeManager->init();

	//����Ʈ�޴� �ʱ�ȭ 
	_selectMenu = new selectMenu;
	_selectMenu->init();

	//�ִϸ��̼� �ʱ�ȭ 
	_animation = new animation;
	_animation->init(IMAGEMANAGER->findImage("craftPotionAnim"), 0, 5, false, false);
	_animation->aniStop();

	//Ŀ�� �ʱ�ȭ 
	_cursor = new cursor;
	_cursor->init();

	//���ǻ��� �ʱ�ȭ 
	initPotionSlot();
	initPotionShop();

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

	_frameCount = 0;

	//�޴� ���� �ݱ� ���� ���� �ʱ�ȭ 
	_menuOn = false; 
	_openMenu = false; 
	_closeMenu = false; 
	_showBannerTxt = false; 
	_animPlayed = false; 
	_playAnim = false; 
	
	return S_OK;
}

void potionShop::release()
{
	SAFE_DELETE(_fadeManager);
	SAFE_DELETE(_potionMenu);
	SAFE_DELETE(_shopBanner);
	SAFE_DELETE(_eKeyIcon);
	SAFE_DELETE(_selectMenu);
	SAFE_DELETE(_cursor);
}

void potionShop::update()
{
	_fadeManager->update();
	_selectMenu->update();
	_animation->update();
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
	//wsprintf(str, "produceCount : %d", _produceCount);
	//TextOut(getMemDC(), 10, 130, str, strlen(str));
	//
	//wsprintf(str, "frameCount : %d", _frameCount);
	//TextOut(getMemDC(), 10, 150, str, strlen(str));

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
				if (_playAnim) potionCraftRender();
				break;

			case POTION_MESSAGE:
				printMessage();
				break;

			case POTION_SET_COUNT:
				setCountRender();
				break;

			case POTION_SELECTMENU:
				selectMenuRender();
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
			initPotionShop();

			//�������̽� �������� ���� 
			PLAYERDATA->setRenderHp(false);
			PLAYERDATA->setRenderKeyInfo(false);
			PLAYERDATA->setRenderItemCount(false);

			//�����۸޴��� Ű�Է��� ���� �ʴ´�.(�޴��� Ű���� ���� �浹�ϱ� ����)
			ITEMMENU->setCanKeyInput(false);
			_fadeManager->fadeInit(16, FADE_OUT, 205);
			SOUNDMANAGER->play("witch_open", 0.5f);
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
	_potionSlot[1].type = POTION_CRAFT;
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
	_potionSlot[3].type = POTION_CRAFT;
	_potionSlot[3].item = ITEMMENU->getItemManager()->getItemByIdx(POTION2_IDX);
	_potionSlot[3].price = 800;
	_potionSlot[3].description[0] = "ü���� 75 ȸ���Ѵ�. ������";
	_potionSlot[3].description[1] = "������ �ϴ� ��ǰ�̴�.";
	_potionSlot[3].mixRecipe = new recipe;
	_potionSlot[3].mixRecipe->addMaterial(RICHJELLY_IDX, 1);
	_potionSlot[3].mixRecipe->addMaterial(VENOMJELLY_IDX, 1);
}

void potionShop::initCursor()
{
	_cursor->setSlotIdx(0);
	_cursor->setDestX(POTION_CURSORX);
	_cursor->setDestY(POTION_CURSORY);
}

void potionShop::initPotionShop()
{
	setPotionCtrl(POTION_MENU);
	_messageType = LACK_OF_GOLD;
	initCursor();

	_produceCount = 1;
	_maxProduceCount = 1;
}

void potionShop::setPotionCtrl(POTION_CTRL state)
{
	switch (state)
	{
		case POTION_MENU:
			_cursor->setDestX(POTION_CURSORX + (_cursor->getSlotIdx()*POTION_CURSOR_DISTANCE));
			_cursor->setDestY(POTION_CURSORY);
			_cursor->setCursorState(CURSOR_MOVE);
			_potionCtrl = state;
			break;

		case POTION_MESSAGE:
			_potionCtrl = state;
			break;

		case POTION_SET_COUNT:
			_produceCount = 1;
			_potionCtrl = state;
			break;

		case POTION_SELECTMENU:
			_cursor->setDestPos(718, 138);
			_cursor->setCursorState(CURSOR_SELECT_MOVE);
			_potionPosY = 484;
			_selectMenu->init();
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

void potionShop::checkMaxProduceCount()
{
	//1.�κ��丮 ���Կ� ����� �ִ��������� ���ϱ� 
	_maxProduceCount = ITEMMENU->getInventory()->getMaxProduceBasedOnRoom(
		_potionSlot[_cursor->getSlotIdx()].item.getItemIdx(),
		_potionSlot[_cursor->getSlotIdx()].item.getMaxCount());

	//2.��忡 ����� �ִ��������� ���ϱ� 
	int maxGoldCount = PLAYERDATA->getGold() / _potionSlot[_cursor->getSlotIdx()].price;

	//1. 2�� �߿��� ���������� �� ���� ��츦 �ִ����������� ���� 
	if (maxGoldCount < _maxProduceCount) _maxProduceCount = maxGoldCount;

	//3.������ ���� ���� ��� ��ῡ ����� �ִ������������� ���ؼ� ��  
	if (_potionSlot[_cursor->getSlotIdx()].type == POTION_CRAFT)
	{
		int maxMaterialCount = _potionSlot[_cursor->getSlotIdx()].mixRecipe->getMaxProduceBasedOnMaterial();
		if (maxMaterialCount < _maxProduceCount) _maxProduceCount = maxMaterialCount;
	}
}

void potionShop::playCraftingAnim()
{
	if (!_animPlayed)
	{
		int totalPrice = (_produceCount * _potionSlot[_cursor->getSlotIdx()].price);
		DAMAGEFONT->init(90, 112, -totalPrice);
		PLAYERDATA->startChangeGold(totalPrice, GOLD_SUBTRACT);

		_animation->aniRestart();
		applyCraftingResult();
		_animPlayed = true;

		SOUNDMANAGER->play("witch_craft", 0.4f);
		SOUNDMANAGER->play("gold_decrement", 0.3f);
	}
}

void potionShop::applyCraftingResult()
{	
	//1. ������ ��ŭ �κ��丮�� ��� �谨(ũ�������� ��� )
	if (_potionSlot[_cursor->getSlotIdx()].type == POTION_CRAFT)
	{
		_potionSlot[_cursor->getSlotIdx()].mixRecipe->deleteUsedMaterial(_produceCount);
	}

	//2. ������ ��ŭ �κ��丮�� ���� 
	ITEMMENU->getInventory()->addItemByCount(_potionSlot[_cursor->getSlotIdx()].item, _produceCount);
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
			setCountKeyInput();
			break;

		case POTION_SELECTMENU:
			selectMenuKeyInput();
			break;

		//case POTION_CRAFTING:
		//	break;
	}
}

void potionShop::menuKeyInput()
{
	if (_playAnim)
	{
		playCraftingAnim();
		_potionPosY -= 0.3f;
		_frameCount++;

		if (_frameCount >= 85 && _animPlayed)
		{
			_playAnim = false;
			_animPlayed = false;
			_frameCount = 0;
		}
		return;
	}

	//�����¿� Ű�Է� 
	if (INPUT->GetKeyDown('A'))
	{
		leftKeyDown();
		_cursor->setCursorState(CURSOR_MOVE);
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}
	if (INPUT->GetKeyDown('D'))
	{
		rightKeyDown();
		_cursor->setCursorState(CURSOR_MOVE);
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}
	if (INPUT->GetKeyDown('W'))
	{
		upKeyDown();
		_cursor->setCursorState(CURSOR_MOVE);
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}
	if (INPUT->GetKeyDown('S'))
	{
		downKeyDown();
		_cursor->setCursorState(CURSOR_MOVE);
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}

	//JŰ �Է�(���� ����)
	if (INPUT->GetKeyDown('J'))
	{
		_cursor->setCursorState(CURSOR_CLICK);
		SOUNDMANAGER->play("cursor_move", 0.2f);

		//�� ������ �ǳʶٱ� 
		if (_cursor->getSlotIdx() >= POTION_MAXSLOT) return; 

		//�ʿ���������� Ȯ���ϰ� ���� �����ϸ� ���� ����ȭ������ �̵� 
		if (checkRequirements())
		{
			//���� ������ �ִ� ������ �����ϰ� ���� ����â���� �̵� 
			checkMaxProduceCount();
			setPotionCtrl(POTION_SET_COUNT);
		}
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
	//�����¿� Ű �Է¿� ���� ������� �ϴ� ���� ���� 
	if (INPUT->GetKeyDown('W'))
	{
		if(_produceCount < _maxProduceCount)_produceCount++;
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}
	if (INPUT->GetKeyDown('S'))
	{
		if(_produceCount > 1) _produceCount--;
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}
	if (INPUT->GetKeyDown('A'))
	{
		if (_produceCount <= 5) _produceCount = 1;
		else _produceCount -= 5;
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}
	if (INPUT->GetKeyDown('D'))
	{
		if (_produceCount + 5 > _maxProduceCount) _produceCount = _maxProduceCount;
		else _produceCount += 5;
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}

	//JŰ�� �Է��ؼ� ���� ���� 
	if (INPUT->GetKeyDown('J'))
	{
		SOUNDMANAGER->play("cursor_move", 0.2f);
		
		setPotionCtrl(POTION_SELECTMENU);
	}
}

void potionShop::selectMenuKeyInput()
{
	//�¿� Ű �Է� �� selectIdx�� �����ϱ�(��,�ƴϿ�)
	if (INPUT->GetKeyDown('A') && _selectMenu->getSelectIdx() != SELECT_YES)
	{
		_selectMenu->setMenuState(SELECT_YES);
		_cursor->setCursorState(CURSOR_SELECT_MOVE);
		_cursor->setDestX(620);
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}
	if (INPUT->GetKeyDown('D') && _selectMenu->getSelectIdx() != SELECT_NO)
	{
		_selectMenu->setMenuState(SELECT_NO);
		_cursor->setCursorState(CURSOR_SELECT_MOVE);
		_cursor->setDestX(718);
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}

	if (INPUT->GetKeyDown('J'))
	{
		if (_selectMenu->getSelectIdx() == SELECT_YES)
		{
			//��
			SOUNDMANAGER->play("cursor_move", 0.2f);
			setPotionCtrl(POTION_MENU);
			_playAnim = true; 
		}
		else
		{
			//�ƴϿ� 
			SOUNDMANAGER->play("cursor_move", 0.2f);
			setPotionCtrl(POTION_MENU);
		}
	}
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
	//ī��Ʈ ���� �޴� ���� 
	IMAGEMANAGER->render("menu_potionMake", getMemDC(), 396, 236);
	setCountTextRender();

	//ī��Ʈ ���� ȭ��ǥ ���� 
	setCountIconRender();

	//ī��Ʈ ���� ������ ���� 
	_potionSlot[_cursor->getSlotIdx()].item.getItemImg()->render(getMemDC(), 470, 354);

	//ī��Ʈ ���� 
	countRender(_produceCount, 505, 394, COLOR_BLACK);
	totalPriceRender();
}

void potionShop::setCountTextRender()
{
	//'�� ���� �ʿ��ϼ���?' ���  
	RECT txtRC1 = RectMake(414, 254, 174, 24);
	HFONT font = CreateFont(19, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(224, 205, 169));
	DrawText(getMemDC(), "�� ���� �ʿ��ϼ���?", -1, &txtRC1, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);

	//'�ʿ�:' ���  
	RECT txtRC2 = RectMake(604, 304, 46, 24);
	DrawText(getMemDC(), "�ʿ�:", -1, &txtRC2, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);
}

void potionShop::setCountIconRender()
{
	if (_produceCount > 1)
	{
		IMAGEMANAGER->frameRender("potion_arrow", getMemDC(), 439, 372, 0, 0);
		IMAGEMANAGER->frameRender("icon_five", getMemDC(), 424, 356, 0, 0);
	}

	if (_produceCount < _maxProduceCount)
	{
		IMAGEMANAGER->frameRender("potion_arrow", getMemDC(), 487, 324, 1, 0);
		IMAGEMANAGER->frameRender("icon_five", getMemDC(), 545, 356, 1, 0);
	}
}

void potionShop::produceCountRender()
{

}

void potionShop::totalPriceRender()
{
	int totalPrice = _produceCount * _potionSlot[_cursor->getSlotIdx()].price;

	countRender(totalPrice, 769, 330, COLOR_WHITE);
}

void potionShop::countRender(int count, int destX, int destY, COLOR_TYPE color)
{
	for (int i = 1, distance = 0; i <= count; i *= 10)
	{
		int number = (count / i) % 10;

		char keyName[16];

		switch (color)
		{
			case COLOR_BLACK:
				wsprintf(keyName, "%d_black", number);
				IMAGEMANAGER->render(keyName, getMemDC(), destX - (distance * 12), destY);
				break;

			case COLOR_WHITE:
				wsprintf(keyName, "%d", number);
				IMAGEMANAGER->render(keyName, getMemDC(), destX - (distance * 12), destY);
				break;
		}

		distance++;

	}//end of for 
}

void potionShop::selectMenuRender()
{
	//��ǳ�� ��� 
	IMAGEMANAGER->render("shop_bubble", getMemDC(), 328, 120);
	selectMenuTextRender();

	selectMenuAnimRender();
}

void potionShop::selectMenuTextRender()
{
	char tempStr[72];
	strcpy(tempStr, _potionSlot[_cursor->getSlotIdx()].item.getName());
	strcat(tempStr, "��(��) ����� �;�?");

	RECT txtRC = RectMake(352, 168, 448, 54);
	HFONT font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	HFONT oFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(230, 215, 187));
	DrawText(getMemDC(), tempStr,
		-1, &txtRC, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	SelectObject(getMemDC(), oFont);
	DeleteObject(font);
}

void potionShop::selectMenuAnimRender()
{
	if (_selectMenu->getSelectIdx() == SELECT_YES)
	{
		IMAGEMANAGER->frameRender("select_no", getMemDC(), 730, 150, 0, 0);
		_selectMenu->render(getMemDC(), 632, 150);
	}
	else
	{
		IMAGEMANAGER->frameRender("select_yes", getMemDC(), 632, 150, 0, 0);
		_selectMenu->render(getMemDC(), 730, 150);
	}
}

void potionShop::potionCraftRender()
{
	//���� �׸��� ���� 
	IMAGEMANAGER->render("potion_shadow", getMemDC(), 586, 512);

	//������ ���ǰ��� ��� 
	countRender(_produceCount, 616, 518, COLOR_WHITE);

	IMAGEMANAGER->findImage(_potionSlot[_cursor->getSlotIdx()].item.getName())->stretchRender(
		getMemDC(), 602, (int)_potionPosY, 1.5f);

	//�ִϸ��̼� ��� 
	if (_animation->getAniState() == ANIMATION_PLAY) 
		_animation->render(getMemDC(), 418, 314);
}





