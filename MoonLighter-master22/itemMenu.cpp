#include "stdafx.h"
#include "itemMenu.h"

HRESULT itemMenu::init()
{
	// 'I' ��ư�� ������ �޴� on/off 
	// 'Q(��)' 'E(��)' ��ư�� ������ �޴� �̵� 

	//Ŭ���� �ʱ�ȭ 
	_calendar = new calendar;
	_calendar->init();

	_wishList = new wishList;
	_wishList->init();

	_inventory = new inventory;
	_inventory->init();

	_noteBook = new noteBook;
	_noteBook->init();

	//�޴� ��ġ �ʱ�ȭ 
	initMenuPos();
	_tagPos.x = 490;
	_tagPos.y = -TAGINITPOSY;

	//���� �ʱ�ȭ 
	_ctrlState = CTRL_INVEN;
	_tagIdx = CTRL_INVEN;

	_menuMoveSpeed = 90.f;
	_tagMoveSpeed = 10.f;

	_menuOn = false;
	_canKeyInput = true; 
	_calendarOn = false;
	_wishListOn = false;
	_invenOn = false;
	_noteBookOn = false;

	_openMenu = false;
	_closeMenu = false;
	_openTagMenu = false;
	_closeTagMenu = false;
	_movingLeft = false;
	_movingRight = false;
	_goToTown = false; 

	return S_OK;
}

void itemMenu::release()
{
	_calendar->release();
	SAFE_DELETE(_calendar);

	_wishList->release();
	SAFE_DELETE(_wishList);

	_inventory->release();
	SAFE_DELETE(_inventory);

	_noteBook->release();
	SAFE_DELETE(_noteBook);
}

void itemMenu::update()
{
	//�޴� on/off ���� �Լ� 
	if(_canKeyInput) toggleMenu();
	openMenu();
	closeMenu();
	openTagMenu();
	closeTagMenu();

	//Ű�Է� �Լ� 
	keyInput();

	//�÷��̾� ������ ������Ʈ �Լ�  
	setCurItemCount();
	setPotionEquipped();
	setWeaponIdx();
	setWeaponEquipped();

	if (_menuOn)
	{
		switch (_ctrlState)
		{
			case CTRL_CALENDAR:
				break;

			case CTRL_WISHLIST:
				break;

			case CTRL_INVEN:
				_inventory->update();
				break;

			case CTRL_NOTEBOOK:
				break;
		}
	}
}

void itemMenu::render(HDC hdc)
{
	if (_menuOn)
	{
		menuRender(hdc);
		tagMenuRender(hdc);
	}

	//char str[128];
	//wsprintf(str, "ctrlState : %d", _ctrlState);
	//TextOut(hdc, 10, 70, str, strlen(str));

	//wsprintf(str, "calendarOn : %d", _calendarOn);
	//TextOut(getMemDC(), 10, 90, str, strlen(str));

	//wsprintf(str, "noteOn : %d", _noteBookOn);
	//TextOut(getMemDC(), 10, 110, str, strlen(str));

	//wsprintf(str, "wishlistOn : %d", _wishListOn);
	//TextOut(getMemDC(), 10, 130, str, strlen(str));

	//wsprintf(str, "invenOn : %d", _invenOn);
	//TextOut(hdc, 10, 150, str, strlen(str));

	//wsprintf(str, "tagIdx : %d", _tagIdx);
	//TextOut(getMemDC(), 10, 170, str, strlen(str));
}

void itemMenu::setCurItemCount()
{
	int itemCount = _inventory->getCurItemCount();

	PLAYERDATA->setItemCount(itemCount);
}

void itemMenu::setPotionEquipped()
{
	PLAYERDATA->setPotionEquipped(_inventory->getPotionEquipped());
}

void itemMenu::setWeaponIdx()
{
	PLAYERDATA->setWeaponIdx(_inventory->getWeaponIdx());
}

void itemMenu::setWeaponEquipped()
{
	PLAYERDATA->setWeaponEquipped(_inventory->getWeaponEquipped());
}

void itemMenu::toggleMenu()
{
	if (!_canKeyInput) return; 

	if (INPUT->GetKeyDown('I'))
	{
		if (_menuOn)
		{
			DoCloseMenu();
		}
		else
		{
			//��Ʈ�ѷ� ���� �ʱ�ȭ(�κ��丮) �� �κ��丮 ���� �ʱ�ȭ  
			setCtrlState(CTRL_INVEN);
			_inventory->initInven();

			_tagIdx = CTRL_INVEN;
			_menuOn = true;
			_invenOn = true;
			_openMenu = true;
			_openTagMenu = true;

			SOUNDMANAGER->play("openInven", 0.4f);
		}
	}
}

void itemMenu::DoCloseMenu()
{
	_closeMenu = true;
	_closeTagMenu = true;

	//�κ��丮 â�� �����Ƿ� Ŀ���� ���ش�.
	_inventory->getCursor()->setShowCursor(false);
}

void itemMenu::openMenu()
{
	if (!_openMenu) return;

	_inventory->setInvenPosY(_inventory->getInvenPos().y - _menuMoveSpeed);

	if (_inventory->getInvenPos().y <= INVENPOSY)
	{
		_inventory->setInvenPosY(INVENPOSY);
		_openMenu = false;
		_inventory->getCursor()->setShowCursor(true);	//�κ��丮 â�� �������Ƿ� Ŀ���� ���ش�.
	}
}

void itemMenu::closeMenu()
{
	if (!_closeMenu) return;

	//���� �����ִ� �޴� ���¿� ���� �޴��� ���� �� �̵��ϴ� �޴��� �ٸ��Ƿ� 
	//������ ��Ʈ�ѷ� ����(�����ִ� �޴� ����)�� ���߾� �׿� �˸��� ���� ���� 
	switch (_ctrlState)
	{
		case CTRL_CALENDAR:
			_calendar->moveCalendarLeft(-IMAGEMANAGER->findImage("menu_calendar")->getWidth());

			if (_calendar->getCalendarPos().x == -IMAGEMANAGER->findImage("menu_calendar")->getWidth())
			{
				_closeMenu = false;
				_calendarOn = false;
				_menuOn = false;
			}
			break;

		case CTRL_WISHLIST:
			_wishList->moveWishListLeft(-IMAGEMANAGER->findImage("menu_wishlist")->getWidth());

			if (_wishList->getWishListPos().x == -IMAGEMANAGER->findImage("menu_wishlist")->getWidth())
			{
				_closeMenu = false;
				_wishListOn = false;
				_menuOn = false;
			}
			break;

		case CTRL_INVEN:
			_inventory->setInvenPosY(_inventory->getInvenPos().y + _menuMoveSpeed);

			if (_inventory->getInvenPos().y >= WINSIZEY)
			{
				_inventory->setInvenPosY(WINSIZEY);
				_closeMenu = false;
				_invenOn = false;
				_menuOn = false;
			}
			break;

		case CTRL_NOTEBOOK:
			_noteBook->moveNoteBookRight(WINSIZEX);

			if (_noteBook->getNoteBookPos().x == WINSIZEX)
			{
				_closeMenu = false;
				_noteBookOn = false;
				_menuOn = false;
			}
			break;
	}

	//�޴��� �ݴ� �Ϸ��� ���۵��� �� ������ ��, ��� �޴��� ��ġ�� �ʱ�ȭ
	//�޴��� �����鼭 �̺��丮 â�� Ŀ���� �Բ� ���ش�. 
	if (!_closeMenu) initMenuPos();
}

void itemMenu::openTagMenu()
{
	if (!_openTagMenu) return;

	_tagPos.y += _tagMoveSpeed;

	if (_tagPos.y >= TAGPOSY)
	{
		_tagPos.y = TAGPOSY;
		_openTagMenu = false;
	}
}

void itemMenu::closeTagMenu()
{
	if (!_closeTagMenu) return;

	_tagPos.y -= _tagMoveSpeed;

	if (_tagPos.y <= -TAGINITPOSY)
	{
		_tagPos.y = -TAGINITPOSY;
		_closeTagMenu = false;
	}
}

void itemMenu::initMenuPos()
{
	_calendar->initPos();
	_wishList->initPos();
	_inventory->initPos();
	_noteBook->initPos();
}

void itemMenu::setCtrlState(CTRL_MENU state)
{
	_movingLeft = false;
	_movingRight = false;

	switch (state)
	{
		case CTRL_CALENDAR:
			_ctrlState = state;
			break;

		case CTRL_WISHLIST:
			_ctrlState = state;
			break;

		case CTRL_INVEN:
			_ctrlState = state;
			break;

		case CTRL_NOTEBOOK:
			_ctrlState = state;
			break;
	}
}

void itemMenu::keyInput()
{
	//���� �޴��� �������� �ʰų�, �޴����� �� �޴��ݱ� ������ �������̶�� Ű�Է��� ���� ����.
	if (!_menuOn || _openMenu || _closeMenu) return;

	//�¿�(Q,E) Ű �Է��� �޴´�.
	leftKeyDown();
	rightKeyDown();

	//���� ��Ʈ�ѷ� ���¿� ���� Ű �Է¿� ���� ����(�޴� �̵�)�� �ٸ��� ó���Ѵ�. 
	switch (_ctrlState)
	{
		case CTRL_CALENDAR:
			ctrlCalendarInput();
			break;

		case CTRL_WISHLIST:
			ctrlWishListInput();
			break;

		case CTRL_INVEN:
			ctrlInvenInput();
			break;

		case CTRL_NOTEBOOK:
			ctrlNoteBookInput();
			break;
	}
}

void itemMenu::leftKeyDown()
{
	//Ķ�����޴��� ���� �� �޴��̹Ƿ� Ķ�����޴����� ���� Ű �Է��� ���� �ʵ��� ��. 
	if (_ctrlState == CTRL_CALENDAR) return;

	if (INPUT->GetKeyDown('Q'))
	{
		if (!_movingLeft && !_movingRight)
		{
			_movingLeft = true;
			_movingRight = false;
			_tagIdx--;

			SOUNDMANAGER->play("moveMenu", 0.3f);
		}
	}
}

void itemMenu::rightKeyDown()
{
	//��Ʈ�ϸ޴��� ������ �� �޴��̹Ƿ� ��Ʈ�ϸ޴����� ������ Ű �Է��� ���� �ʵ��� ��. 
	if (_ctrlState == CTRL_NOTEBOOK) return;

	if (INPUT->GetKeyDown('E'))
	{
		if (!_movingRight && !_movingLeft)
		{
			_movingRight = true;
			_movingLeft = false;
			_tagIdx++;

			SOUNDMANAGER->play("moveMenu", 0.3f);
		}
	}
}

void itemMenu::ctrlCalendarInput()
{
	if (_movingRight)
	{
		if (!_wishListOn) _wishListOn = true;

		//�� �޴��� position ���� destination ������ �̵���Ų��.  
		_calendar->moveCalendarLeft(-IMAGEMANAGER->findImage("menu_calendar")->getWidth());
		_wishList->moveWishListLeft(WISHLISTPOSX);

		//�� �޴��� destination ��ġ���� �������� ��� ������ ���� ���� �� ��Ʈ�ѷ����� ���� 
		if (_calendar->getCalendarPos().x == -IMAGEMANAGER->findImage("menu_calendar")->getWidth() &&
			_wishList->getWishListPos().x == WISHLISTPOSX)
		{
			_calendarOn = false;
			setCtrlState(CTRL_WISHLIST);
		}
	}
}

void itemMenu::ctrlWishListInput()
{
	if (_movingLeft)
	{
		if (!_calendarOn) _calendarOn = true;

		_wishList->moveWishListRight(WINSIZEX);
		_calendar->moveCalendarRight(CALENDARPOSX);

		if (_wishList->getWishListPos().x == WINSIZEX && _calendar->getCalendarPos().x == CALENDARPOSX)
		{
			_wishListOn = false;
			setCtrlState(CTRL_CALENDAR);
		}
	}
	if (_movingRight)
	{
		if (!_invenOn) _invenOn = true;

		//�� �޴��� position ���� destination ������ �̵���Ų��.  
		_wishList->moveWishListLeft(-IMAGEMANAGER->findImage("menu_wishlist")->getWidth());
		_inventory->moveInvenLeft(INVENPOSX);

		//�� �޴��� destination ��ġ���� �������� ��� ������ ���� ���� �� ��Ʈ�ѷ����� ���� 
		if (_wishList->getWishListPos().x == -IMAGEMANAGER->findImage("menu_wishlist")->getWidth() &&
			_inventory->getInvenPos().x == INVENPOSX)
		{
			_wishListOn = false;
			setCtrlState(CTRL_INVEN);

			//�κ��丮 â���� �Ѿ�����Ƿ� Ŀ���� ���ش�.
			_inventory->getCursor()->setShowCursor(true);	
		}
	}
}

void itemMenu::ctrlInvenInput()
{
	if (_movingLeft)
	{
		//�κ��丮�� �̵���ų ���̹Ƿ� Ŀ���� ���ش�. 
		if (_inventory->getCursor()->getShowCursor())
		{
			_inventory->getCursor()->setShowCursor(false);
		}
		if (!_wishListOn) _wishListOn = true;

		_inventory->moveInvenRight(WINSIZEX);
		_wishList->moveWishListRight(WISHLISTPOSX);

		if (_inventory->getInvenPos().x == WINSIZEX && _wishList->getWishListPos().x == WISHLISTPOSX)
		{
			_invenOn = false;
			setCtrlState(CTRL_WISHLIST);
		}
	}
	if (_movingRight)
	{
		//�κ��丮�� �̵���ų ���̹Ƿ� Ŀ���� ���ش�. 
		if (_inventory->getCursor()->getShowCursor())
		{
			_inventory->getCursor()->setShowCursor(false);
		}
		if (!_noteBookOn) _noteBookOn = true;

		//�� �޴��� position ���� destination ������ �̵���Ų��.  
		_inventory->moveInvenLeft(-IMAGEMANAGER->findImage("menu_inventory")->getWidth());
		_noteBook->moveNoteBookLeft(NOTEBOOKPOSX);

		//�� �޴��� destination ��ġ���� �������� ��� ������ ���� ���� �� ��Ʈ�ѷ����� ���� 
		if (_inventory->getInvenPos().x == -IMAGEMANAGER->findImage("menu_inventory")->getWidth() &&
			_noteBook->getNoteBookPos().x == NOTEBOOKPOSX)
		{
			_invenOn = false;
			setCtrlState(CTRL_NOTEBOOK);
		}
	}
}

void itemMenu::ctrlNoteBookInput()
{
	if (_movingLeft)
	{
		if (!_invenOn) _invenOn = true;

		_noteBook->moveNoteBookRight(WINSIZEX);
		_inventory->moveInvenRight(INVENPOSX);

		if (_inventory->getInvenPos().x == INVENPOSX && _noteBook->getNoteBookPos().x == WINSIZEX)
		{
			_noteBookOn = false;
			setCtrlState(CTRL_INVEN);
			
			//�κ��丮 â���� �Ѿ�����Ƿ� Ŀ���� ���ش�. 
			_inventory->getCursor()->setShowCursor(true);	
		}
	}
}

void itemMenu::menuMoveLeft(POINT *pos, const int destPos)
{
	pos->x -= _menuMoveSpeed;

	if (pos->x <= destPos)
	{
		pos->x = destPos;
	}
}

void itemMenu::menuMoveRight(POINT *pos, const int destPos)
{
	pos->x += _menuMoveSpeed;

	if (pos->x >= destPos)
	{
		pos->x = destPos;
	}
}

void itemMenu::menuRender(HDC hdc)
{
	if (_calendarOn)
	{
		_calendar->render(hdc);
	}
	if (_wishListOn)
	{
		_wishList->render(hdc);
	}
	if (_invenOn)
	{
		_inventory->render(hdc);
	}
	if (_noteBookOn)
	{
		_noteBook->render(hdc);
	}
}

void itemMenu::tagMenuRender(HDC hdc)
{
	IMAGEMANAGER->findImage("btn_qe")->render(hdc, 490, _tagPos.y);

	//Ķ�����±� ��� 
	if (_tagIdx == CTRL_CALENDAR)
	{
		IMAGEMANAGER->findImage("toggle_calendar")->frameRender(
			hdc, 542, _tagPos.y - 6, 1, 0);
	}
	else
	{
		IMAGEMANAGER->findImage("toggle_calendar")->frameRender(
			hdc, 542, _tagPos.y - 6, 0, 0);
	}

	//���ø���Ʈ�±� ��� 
	if (_tagIdx == CTRL_WISHLIST)
	{
		IMAGEMANAGER->findImage("toggle_wishlist")->frameRender(
			hdc, 592, _tagPos.y - 6, 1, 0);
	}
	else
	{
		IMAGEMANAGER->findImage("toggle_wishlist")->frameRender(
			hdc, 592, _tagPos.y - 6, 0, 0);
	}

	//�κ��丮�±� ��� 
	if (_tagIdx == CTRL_INVEN)
	{
		IMAGEMANAGER->findImage("toggle_inventory")->frameRender(
			hdc, 642, _tagPos.y - 6, 1, 0);
	}
	else
	{
		IMAGEMANAGER->findImage("toggle_inventory")->frameRender(
			hdc, 642, _tagPos.y - 6, 0, 0);
	}

	//��Ʈ���±� ��� 
	if (_tagIdx == CTRL_NOTEBOOK)
	{
		IMAGEMANAGER->findImage("toggle_notebook")->frameRender(
			hdc, 692, _tagPos.y - 6, 1, 0);
	}
	else
	{
		IMAGEMANAGER->findImage("toggle_notebook")->frameRender(
			hdc, 692, _tagPos.y - 6, 0, 0);
	}
}

