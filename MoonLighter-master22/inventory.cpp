#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	//Ŭ���� �ʱ�ȭ 
	_itemManager = new itemManager;
	_itemManager->init();

	_cursor = new cursor;
	_cursor->init();

	_selectMenu = new selectMenu;
	_selectMenu->init();

	//�κ��丮�޴� ��ġ �ʱ�ȭ 
	initPos();

	//�κ��丮 ���� ���� �ʱ�ȭ 
	initInvenSlot();
	_invenCtrl = INVEN_INVENTORY;

	//������ �ʱ�ȭ 
	initItem();

	//������ ��� ���� ���� 
	_isGrabbingItem = false;
	_isPuttingItem = false;
	_canGrab = true; 
	_grabTime = 12;

	//���� ���� ���� ���� 
	_curWeaponIdx = 1;
	_itemCount = 0;

	//�޴� �̵��ӵ� 
	_menuMoveSpeed = 90.f;

	//���� ���� ���� 
	_grabSoundPlayed = false;

	return S_OK;
}

void inventory::release()
{
	_itemManager->release();
	SAFE_DELETE(_itemManager);

	_cursor->release();
	SAFE_DELETE(_cursor);

	_selectMenu->release();
	SAFE_DELETE(_selectMenu);
}

void inventory::update()
{
	_cursor->update();
	keyInput();

	if (_invenCtrl == INVEN_MERCHANT_PENDANT ||
		_invenCtrl == INVEN_MERCHANT_EMBLEM)
	{
		_selectMenu->update();
	}
}

void inventory::render(HDC hdc)
{
	//������ �ִ��� ���ο� ���� �޴��̹��� �ٸ��� ��� 
	if (PLAYERDATA->getIsInDungeon())
	{
		IMAGEMANAGER->findImage("menu_inventory_inDungeon")->render(hdc, _invenPos.x, _invenPos.y);
	}
	else
	{
		IMAGEMANAGER->findImage("menu_inventory")->render(hdc, _invenPos.x, _invenPos.y);
	}

	//�޴��� ���� ������ ������ �� ��� 
	if (_cursor->getShowCursor())
	{
		merchantIconRender(hdc);
		itemRender(hdc);
		itemNameRender(hdc);
		statusRender(hdc);

		if (_itemGrabbed.getType() != ITEM_EMPTY) itemGrabbedRender(hdc);

		cursorRender(hdc);
		weaponIconRender(hdc);

		switch (_invenCtrl)
		{
			case INVEN_MERCHANT_MIRROR:
				break;

			case INVEN_MERCHANT_PENDANT:
				pendantCtrlRender(hdc);
				break;

			case INVEN_MERCHANT_EMBLEM:
				emblemCtrlRender(hdc);
				break;
		}//end of switch 
	}

	//char str[128];

	//wsprintf(str, "invenCtrl : %d", _invenCtrl);
	//TextOut(hdc, 10, 130, str, strlen(str));

	//wsprintf(str, "canGrab : %d", _canGrab);
	//TextOut(hdc, 10, 150, str, strlen(str));

	//wsprintf(str, "isGrabbingItem : %d", _isGrabbingItem);
	//TextOut(hdc, 10, 170, str, strlen(str));

	//for (int i = 0; i < _vInvenItem.size(); i++)
	//{
	//	wsprintf(str, "inven[%d].invenIdx : %d", i, _vInvenItem[i]->getInvenPosIdx());
	//	TextOut(hdc, 10, 170 + (i * 20), str, strlen(str));
	//}

}

int inventory::getCurItemCount()
{
	int itemCount = 0;

	for (int i = 0; i < _vInven.size(); i++)
	{
		switch (_vInven[i]->getInvenPosIdx())
		{
			case 5: case 6: case 12: case 13:
			case 19: case 20: case 26: case 27:
			case 28: case 29: case 30:
				break;

			default:
				if (_vInven[i]->getType() != ITEM_EMPTY) itemCount++;
				break;

		}//end of switch
	}//end of for 

	return itemCount;
}

gameItem inventory::getPotionEquipped()
{
	if (_invenSlot[20].isEmpty) return _itemEmpty;
	else
	{
		for (int i = 0; i < _vInven.size(); i++)
		{
			if (_vInven[i]->getInvenPosIdx() != 20) continue;

			return *(_vInven[i]);
		}
	}
}

gameItem inventory::getWeaponEquipped()
{
	switch (_curWeaponIdx)
	{
		case 1:
			if (_invenSlot[5].isEmpty) return _itemEmpty;
			else
			{
				for (int i = 0; i < _vInven.size(); i++)
				{
					if (_vInven[i]->getInvenPosIdx() != 5) continue;

					return *(_vInven[i]);
				}
			}

		case 2:
			if (_invenSlot[6].isEmpty) return _itemEmpty;
			else
			{
				for (int i = 0; i < _vInven.size(); i++)
				{
					if (_vInven[i]->getInvenPosIdx() != 6) continue;

					return *(_vInven[i]);
				}
			}
	}//end of switch
}

void inventory::initPos()
{
	_invenPos.x = INVENPOSX;
	_invenPos.y = WINSIZEY;
}

void inventory::moveInvenLeft(int destPos)
{
	_invenPos.x -= _menuMoveSpeed;

	if (_invenPos.x <= destPos)
	{
		_invenPos.x = destPos;
	}
}

void inventory::moveInvenRight(int destPos)
{
	_invenPos.x += _menuMoveSpeed;

	if (_invenPos.x >= destPos)
	{
		_invenPos.x = destPos;
	}
}

void inventory::initInven()
{
	_isGrabbingItem = false; 
	_isPuttingItem = false; 
	_grabSoundPlayed = false;
	_canGrab = true;

	_cursor->setSlotIdx(0);
	setInvenCtrl(INVEN_INVENTORY);
	putGrabbingItem();
}

void inventory::initInvenSlot()
{
	memset(_invenSlot, 0, sizeof(_invenSlot));

	for (int i = 0; i < MAXSLOT; i++)
	{
		_invenSlot[i].slotIdx = i;
		_invenSlot[i].isEmpty = true;

		//������ �ε����� �°� ���Կ� �� �� �ִ� �������� Ÿ���� �����ش�. 
		switch (_invenSlot[i].slotIdx)
		{
			case 0: case 1: case 2: case 3: case 4:
			case 7: case 8: case 9: case 10: case 11:
			case 14: case 15: case 16: case 17: case 18:
			case 21: case 22: case 23: case 24: case 25:
				_invenSlot[i].slotType = SLOT_ITEM;
				_invenSlot[i].type = ITEM_NORMAL;
				break;

			case 5:
				_invenSlot[i].slotType = SLOT_WEAPON_LEFT;
				_invenSlot[i].type = ITEM_WEAPON;
				break;

			case 6:
				_invenSlot[i].slotType = SLOT_WEAPON_RIGHT;
				_invenSlot[i].type = ITEM_WEAPON;
				break;

			case 12:
				_invenSlot[i].slotType = SLOT_HELMET;
				_invenSlot[i].type = ITEM_HELMET;
				break;

			case 13:
				_invenSlot[i].slotType = SLOT_RING_UP;
				_invenSlot[i].type = ITEM_RING;
				break;

			case 19:
				_invenSlot[i].slotType = SLOT_ARMOR;
				_invenSlot[i].type = ITEM_ARMOR;
				break;

			case 20:
				_invenSlot[i].slotType = SLOT_POTION;
				_invenSlot[i].type = ITEM_POTION;
				break;

			case 26:
				_invenSlot[i].slotType = SLOT_BOOTS;
				_invenSlot[i].type = ITEM_BOOTS;
				break;

			case 27:
				_invenSlot[i].slotType = SLOT_RING_DOWN;
				_invenSlot[i].type = ITEM_RING;
				break;

			case 28:
				_invenSlot[i].slotType = SLOT_MIRROR;
				break;

			case 29:
				_invenSlot[i].slotType = SLOT_PENDANT;
				break;

			case 30:
				_invenSlot[i].slotType = SLOT_EMBLEM;
				break;
		}
	}
}

void inventory::initItemSlot()
{
	for (int i = 0; i < MAXSLOT; i++)
	{
		//������ ������ ���� ����ֱ�  
		switch (_invenSlot[i].slotIdx)
		{
			case 0: case 1: case 2: case 3: case 4:
			case 7: case 8: case 9: case 10: case 11:
			case 14: case 15: case 16: case 17: case 18:
			case 21: case 22: case 23: case 24: case 25:
				_invenSlot[i].isEmpty = true;
				break;

			default:
				break;
		}
	}//end of for 
}

void inventory::initItem()
{
	//������ �ʱ�ȭ 
	memset(&_itemEmpty, 0, sizeof(_itemEmpty));
	memset(&_tempItem, 0, sizeof(_tempItem));
	memset(&_itemGrabbed, 0, sizeof(_itemGrabbed));

	for (int i = 0; i < _itemManager->getItem().size(); i++)
	{
		//���ο� ���� �������� �����ؼ� �����۸Ŵ����� �ִ� �����۸���� �����ؼ� �־��ֱ� 

		gameItem *item = new gameItem;
		item->init(_itemManager->getItem()[i]);

		for (int j = 0; j < MAXSLOT; j++)
		{
			if (!_invenSlot[j].isEmpty || _invenSlot[j].slotType != SLOT_ITEM) continue;
	
			if (i == 15)
			{
				_invenSlot[5].isEmpty = false;
				item->setInvenPosIdx(5);
				_vInven.push_back(item);
				break;
			}
			else
			{
				_invenSlot[j].isEmpty = false;
				item->setInvenPosIdx(j);
				_vInven.push_back(item);
				break;
			}
		}
	}

	_vInven[0]->setCount(5);
	_vInven[1]->setCount(10);
	_vInven[2]->setCount(5);
	_vInven[3]->setCount(5);
	_vInven[13]->setCount(5);
}

bool inventory::addItemToInven(gameItem item)
{
	for (int i = 0; i < _vInven.size(); i++)
	{
		//�߰��ϰ��� �ϴ� �����۰� ���� ������ �������� �κ��丮 ���Կ� ���� ��� 
		if (_vInven[i]->getItemIdx() == item.getItemIdx())
		{
			//������ �������� �̹� �ִ밳�� �̻��� ���� �ǳʶٱ� 
			if (_vInven[i]->getCount() >= _vInven[i]->getMaxCount()) continue;

			//���Կ� �ִ� �����ۿ� ���� + 1
			_vInven[i]->plusOneCount();
			SOUNDMANAGER->play("cursor_pick", 0.6f);
			return true;
		}

		//���� ������ �������� �κ��丮 ���Կ� ���� ��� �κ��丮�� ���Ӱ� �߰��ϱ� 
		if (i == _vInven.size() - 1)
		{
			//�κ��丮�� �� �ڸ��� ��ġ���� �����Ͽ� �κ��丮 ���Ϳ� Ǫ�ù� 
			for (int j = 0; j < MAXSLOT; j++)
			{
				if (!_invenSlot[j].isEmpty || _invenSlot[j].slotType != SLOT_ITEM) continue;

				gameItem *tempItem = new gameItem;
				tempItem->init(&item);
				tempItem->setCount(1);
				tempItem->setInvenPosIdx(j);

				_vInven.push_back(tempItem);
				_invenSlot[j].isEmpty = false;
				SOUNDMANAGER->play("cursor_pick", 0.6f);
				return true;

			}//end of for(j)

			//�κ��丮�� �� ���ִ� ��� �������� ���� ���� 
			return false;
		}
	}//end of for(i)
}

void inventory::deleteInvenItem()
{
	for (int i = 0; i < _vInven.size(); )
	{
		switch (_vInven[i]->getInvenPosIdx())
		{
		case 5: case 6: case 12: case 13:
		case 19: case 20: case 26: case 27:
		case 28: case 29: case 30:
			i++;
			break;

		default:
			SAFE_DELETE(_vInven[i]);
			_vInven.erase(_vInven.begin() + i);
			break;
		}
	}
}

void inventory::syncWithShopInven(vector<gameItem*> vShopInven)
{
	//������ ���Կ� �ִ� ������ �����, ���� 
	deleteInvenItem();
	initItemSlot();

	for (int i = 0; i < vShopInven.size(); i++)
	{
		//���� ���Կ� �ִ� �������� �����ϰ� �κ��丮 ���Կ� �ִ� ������ �������� 
		switch (vShopInven[i]->getInvenPosIdx())
		{
		case 5: case 6: case 12: case 13:
		case 19: case 20: case 26: case 27:
			break;

		default:
			gameItem *item = new gameItem;
			item->init(vShopInven[i]);
			_vInven.push_back(item);

			_invenSlot[item->getInvenPosIdx()].isEmpty = false;
			break;

		}//end of switch 
	}//end of for 
}

void inventory::keyInput()
{
	switch (_invenCtrl)
	{
		case INVEN_INVENTORY:
			invenKeyInput();
			break;

		case INVEN_MERCHANT_MIRROR:
			mirrorKeyInput();
			break;

		case INVEN_MERCHANT_PENDANT:
			pendantKeyInput();
			break;

		case INVEN_MERCHANT_EMBLEM:
			emblemKeyInput();
			break;
	}

	//Ű �Է��� �޾Ƽ� ���� �ٲٱ� 
	if (INPUT->GetKeyDown('Z'))
	{
		switchWeapon();
	}
}

void inventory::setInvenCtrl(INVEN_CTRL state)
{
	switch (state)
	{
		case INVEN_INVENTORY:
			_invenCtrl = state;
			_cursor->setCursorState(CURSOR_MOVE);
			break;

		case INVEN_MERCHANT_MIRROR:
			_invenCtrl = state;
			_selectMenu->setSelectIdx(SELECT_NO);
			_cursor->setCursorState(CURSOR_SELECT_MOVE);
			break;

		case INVEN_MERCHANT_PENDANT:
			_invenCtrl = state;
			_selectMenu->setSelectIdx(SELECT_NO);
			_cursor->setCursorState(CURSOR_SELECT_MOVE);
			break;

		case INVEN_MERCHANT_EMBLEM:
			_invenCtrl = state;
			_selectMenu->setSelectIdx(SELECT_NO);
			_cursor->setCursorState(CURSOR_SELECT_MOVE);
			break;
	}
}

void inventory::setMerchantCtrl()
{
	switch (_cursor->getSlotIdx())
	{
		case 28:
			setInvenCtrl(INVEN_MERCHANT_MIRROR);
			SOUNDMANAGER->play("cursor_move", 0.2f);
			break;

		case 29:
			if (PLAYERDATA->getIsInDungeon() && PLAYERDATA->getGold() >= 200)
				setInvenCtrl(INVEN_MERCHANT_PENDANT);
			SOUNDMANAGER->play("cursor_move", 0.2f);
			break;

		case 30:
			if (PLAYERDATA->getIsInDungeon() && PLAYERDATA->getGold() >= 1000)
				setInvenCtrl(INVEN_MERCHANT_EMBLEM);
			SOUNDMANAGER->play("cursor_move", 0.2f);
			break;
	}
}

void inventory::invenKeyInput()
{
	//�����¿� Ű �Է� �޾Ƽ� Ŀ�� �����̱� 
	//Ŀ���� ������ ������ Ŀ�� �ִϸ��̼� ���� 
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

	//��ư�� ������ �ִ� �ð��� ���� 
	//�������� �� ���� ��ų� ��� ��� ���� ���� 
	if (INPUT->GetKey('J'))
	{
		_cursor->setClickTime(_cursor->getClickTime() + 1);

		//�� ������ ������ �Ѳ����� ��� ���� 
		if (_cursor->getClickTime() >= _grabTime && !_isPuttingItem)
		{
			grabItem();
		}
	}
	if (INPUT->GetKeyDown('J'))
	{
		_cursor->setCursorState(CURSOR_CLICK);
		putItem();
		setMerchantCtrl();
	}
	if (INPUT->GetKeyUp('J'))
	{
		//�Ѳ����� ��⸦ ������ ������ ��� ������ �ʰ� ���� �� ���
		//1���� �������� ���� �� �ֵ��� �Լ� ���� 
		if (!_isPuttingItem) grabItem();

		_isPuttingItem = false;
		_canGrab = true; 
		_grabSoundPlayed = false;
		_cursor->setClickTime(0);
	}
}

void inventory::mirrorKeyInput()
{
}

void inventory::pendantKeyInput()
{
	//�¿� Ű �Է� �� selectIdx�� �����ϱ�(��,�ƴϿ�)
	if (INPUT->GetKeyDown('A') || INPUT->GetKeyDown('D'))
	{
		if (_selectMenu->getSelectIdx() == SELECT_NO)
		{
			_selectMenu->setSelectIdx(SELECT_YES);
			_selectMenu->setMenuState(SELECT_YES);
			_cursor->setCursorState(CURSOR_SELECT_MOVE);
			SOUNDMANAGER->play("cursor_move", 0.2f);
		}
		else
		{
			_selectMenu->setSelectIdx(SELECT_NO);
			_selectMenu->setMenuState(SELECT_NO);
			_cursor->setCursorState(CURSOR_SELECT_MOVE);
			SOUNDMANAGER->play("cursor_move", 0.2f);
		}
	}

	//��,�ƴϿ� �� �����ϱ� 
	if (INPUT->GetKeyDown('J'))
	{
		//�ƴϿ� ���� �� �κ��丮 ��Ʈ�ѷ��� ���� 
		if (_selectMenu->getSelectIdx() == SELECT_NO)
		{
			setInvenCtrl(INVEN_INVENTORY);
			SOUNDMANAGER->play("cursor_move", 0.2f);
		}
		else
		{
			//�� ���� �� ������ ���ư��� 
			//1. gototown���� true�� ���� 
			//2. �����۸޴� �����ϱ�(�޴� �ݱ�)
			//3. ���� ��忡�� �����ϱ�(200��)
			//4. �κ��丮 ��Ʈ�ѷ� �ʱ�ȭ 
			//5. ���ø޴��� ���� �ʱ�ȭ(NO)
			//6. �÷��̾� ���¸� �Ҵ�Ʈ������� ��������

			ITEMMENU->SetGoToTownEmblem(true);
			ITEMMENU->DoCloseMenu();
			PLAYERDATA->subGold(200);
			_selectMenu->setMenuState(SELECT_NO);
			//if (_selectMenu->getSelectIdx() == SELECT_YES) _cursor->setSlotIdx(0);
			SOUNDMANAGER->play("cursor_move", 0.2f);
		}
	}
	if (INPUT->GetKeyUp('J'))
	{
		_canGrab = false;
	}

	//�ڷΰ��� 
	if (INPUT->GetKeyDown('L'))
	{
		setInvenCtrl(INVEN_INVENTORY);
		_selectMenu->setMenuState(SELECT_NO);
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}
}

void inventory::emblemKeyInput()
{
	//�¿� Ű �Է� �� selectIdx�� �����ϱ�(��,�ƴϿ�)
	if (INPUT->GetKeyDown('A') || INPUT->GetKeyDown('D'))
	{
		if (_selectMenu->getSelectIdx() == SELECT_NO)
		{
			_selectMenu->setSelectIdx(SELECT_YES);
			_selectMenu->setMenuState(SELECT_YES);
			_cursor->setCursorState(CURSOR_SELECT_MOVE);
			SOUNDMANAGER->play("cursor_move", 0.2f);
		}
		else
		{
			_selectMenu->setSelectIdx(SELECT_NO);
			_selectMenu->setMenuState(SELECT_NO);
			_cursor->setCursorState(CURSOR_SELECT_MOVE);
			SOUNDMANAGER->play("cursor_move", 0.2f);
		}
	}

	//��,�ƴϿ� �� �����ϱ� 
	if (INPUT->GetKeyDown('J'))
	{
		//�ƴϿ� ���� �� �κ��丮 ��Ʈ�ѷ��� ���� 
		if (_selectMenu->getSelectIdx() == SELECT_NO) setInvenCtrl(INVEN_INVENTORY);
		else
		{
			//�� ���� �� ������ ���ư��� 
			//1. gototown���� true�� ���� 
			//2. �����۸޴� �����ϱ�(�޴� �ݱ�)
			//3. ���� ��忡�� �����ϱ�(200��)
			//4. �κ��丮 ��Ʈ�ѷ� �ʱ�ȭ 
			//5. ���ø޴��� ���� �ʱ�ȭ(NO)
			//6. �÷��̾� ���¸� �Ҵ�Ʈ������� ��������

			ITEMMENU->SetGoToTownEmblem(true);
			ITEMMENU->DoCloseMenu();
			PLAYERDATA->subGold(1000);
			_selectMenu->setMenuState(SELECT_NO);
			//if (_selectMenu->getSelectIdx() == SELECT_YES) _cursor->setSlotIdx(0);
			SOUNDMANAGER->play("cursor_move", 0.2f);
		}
	}
	if (INPUT->GetKeyUp('J'))
	{
		_canGrab = false;
	}

	//�ڷΰ��� 
	if (INPUT->GetKeyDown('L'))
	{
		setInvenCtrl(INVEN_INVENTORY);
		_selectMenu->setMenuState(SELECT_NO);
		SOUNDMANAGER->play("cursor_move", 0.2f);
	}
}

void inventory::leftKeyDown()
{
	//���� Ű �Է��� ���� �� Ŀ���� �ε��� ����
	//������ �� ���ʿ� ���� ��� ���� Ű�� �Է��ϸ� ������ �� ���������� �̵��ϹǷ� 
	//switch���� ���� �ش� ���̽��� ������ ����� ����. 

	switch (_cursor->getSlotIdx())
	{
	case 0:
		_cursor->setSlotIdx(6);
		break;

	case 7:
		_cursor->setSlotIdx(13);
		break;

	case 14:
		_cursor->setSlotIdx(20);
		break;

	case 21:
		_cursor->setSlotIdx(27);
		break;

	case 28:
		_cursor->setSlotIdx(26);
		break;

	default:
		_cursor->setSlotIdx(_cursor->getSlotIdx() - 1);
		break;
	}
}

void inventory::rightKeyDown()
{
	switch (_cursor->getSlotIdx())
	{
	case 6:
		_cursor->setSlotIdx(0);
		break;

	case 13:
		_cursor->setSlotIdx(7);
		break;

	case 20:
		_cursor->setSlotIdx(14);
		break;

	case 27:
		_cursor->setSlotIdx(21);
		break;

	case 30:
		_cursor->setSlotIdx(26);
		break;

	default:
		_cursor->setSlotIdx(_cursor->getSlotIdx() + 1);
		break;
	}
}

void inventory::upKeyDown()
{
	switch (_cursor->getSlotIdx())
	{
	case 0: case 1:
		_cursor->setSlotIdx(28);
		break;

	case 2:
		_cursor->setSlotIdx(29);
		break;

	case 3: case 4:
		_cursor->setSlotIdx(30);
		break;

	case 5: case 6:
		_cursor->setSlotIdx(27);
		break;

	case 13:
		_cursor->setSlotIdx(5);
		break;

	case 29:
		_cursor->setSlotIdx(23);
		break;

	case 30:
		_cursor->setSlotIdx(25);
		break;

	default:
		_cursor->setSlotIdx(_cursor->getSlotIdx() - 7);
		break;
	}
}

void inventory::downKeyDown()
{
	switch (_cursor->getSlotIdx())
	{
		case 5: case 6:
			_cursor->setSlotIdx(13);
			break;

		case 21: case 22:
			_cursor->setSlotIdx(28);
			break;

		case 23:
			_cursor->setSlotIdx(29);
			break;

		case 24: case 25:
			_cursor->setSlotIdx(30);
			break;

		case 26: case 27:
			_cursor->setSlotIdx(5);
			break;

		case 28:
			_cursor->setSlotIdx(0);
			break;

		case 29:
			_cursor->setSlotIdx(2);
			break;

		case 30:
			_cursor->setSlotIdx(4);
			break;

		default:
			_cursor->setSlotIdx(_cursor->getSlotIdx() + 7);
			break;
	}
}

void inventory::switchWeapon()
{
	switch (_curWeaponIdx)
	{
		case 1:
			if (!_invenSlot[5].isEmpty) //5�� ���Կ� ���⸦ �̹� �����ϰ� �ְ�, 
			{
				//6�� ���Կ� ���Ⱑ �����Ǿ����� �ʴٸ� return (�ٲ� ���Ⱑ ����)
				if (_invenSlot[6].isEmpty) return;
				else //5���� 6�� ���� ��� ���⸦ �����ϰ� �ִٸ�, 
				{
					switchWeaponIdx();
					SOUNDMANAGER->play("weaponChange", 0.4f);
				}
			}
			else //5�� ���Կ� ������ ���Ⱑ ����, 
			{
				//6�� ���Կ��� ������ ���Ⱑ ���ٸ� return
				if (_invenSlot[6].isEmpty) return;
				else //5���� ������ ����� ������ 6���� ������ ���Ⱑ �ִٸ� ���� 
				{
					switchWeaponIdx();
				}
			}
			break;

		case 2:
			if (!_invenSlot[6].isEmpty) //6�� ���Կ� ���⸦ �̹� �����ϰ� �ְ�, 
			{
				//5�� ���Կ� ���Ⱑ �����Ǿ����� �ʴٸ� return (�ٲ� ���Ⱑ ����)
				if (_invenSlot[5].isEmpty) return;
				else //5���� 6�� ���� ��� ���⸦ �����ϰ� �ִٸ�, 
				{
					switchWeaponIdx();
					SOUNDMANAGER->play("weaponChange", 0.4f);
				}
			}
			else //6�� ���Կ� ������ ���Ⱑ ����, 
			{
				//5�� ���Կ��� ������ ���Ⱑ ���ٸ� return
				if (_invenSlot[5].isEmpty) return;
				else //6���� ������ ����� ������ 5���� ������ ���Ⱑ �ִٸ� ���� 
				{
					switchWeaponIdx();
				}
			}
			break;
	}
}

void inventory::switchWeaponIdx()
{
	if (_curWeaponIdx == 1) _curWeaponIdx = 2;
	else if (_curWeaponIdx == 2)_curWeaponIdx = 1;
}

void inventory::usePotionEquipped()
{
	//���� ���� ���� ������ ���ٸ� �Լ� ����
	if (_invenSlot[20].isEmpty) return;

	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vInven[i]->getInvenPosIdx() != 20) continue;

		//�ش� ������ ȸ���¸�ŭ ü�� ȸ�� 
		PLAYERDATA->plusInDungeonHp(_vInven[i]->getPotionValue());

		//����� ������ ������ 1�� ����  
		_vInven[i]->minusOneCount();

		//������ ������ 0���� �Ǹ� �κ��丮���� ���� 
		if (_vInven[i]->getCount() <= 0)
		{
			_invenSlot[20].isEmpty = true;
			SAFE_DELETE(_vInven[i]);
			_vInven.erase(_vInven.begin() + i);
		}
	}
}

void inventory::grabItem()
{
	if (!_canGrab) return; 

	//���� ��� �ִ� �������� �ְų� �󽽷��� ��� �Լ� ���� 
	if (_invenSlot[_cursor->getSlotIdx()].isEmpty && !_isGrabbingItem)
	{
		if (!_grabSoundPlayed)
		{
			_grabSoundPlayed = true;
			SOUNDMANAGER->play("cursor_move", 0.2f);
		}
		return;
	}
	if (_isGrabbingItem) return;

	//Ŭ���ϰ� �ִ� �ð��� ��� �Ѳ����� ��� 
	if (_cursor->getClickTime() >= _grabTime)
	{
		_isGrabbingItem = true;
		grabAllItem();
		SOUNDMANAGER->play("cursor_pick", 0.4f);
	}
	else //ª�ٸ� 1���� ��� 
	{
		_isGrabbingItem = true;
		grabOneItem();
		SOUNDMANAGER->play("cursor_pick", 0.4f);
	}
}

void inventory::grabOneItem()
{
	//Ŀ���� ����Ű�� �κ��丮 �ε����� ��ġ�ϴ� �������� itemGrabbed�� ��´�.
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vInven[i]->getInvenPosIdx() != _cursor->getSlotIdx()) continue;

		//�������� �� ���� �����״ϱ� ������ Ŭ������ �������ֵ�, ������ 1���� �����Ѵ�.
		_itemGrabbed = *(_vInven[i]);
		_itemGrabbed.setCount(1);

		//���� �������� ������ŭ �κ��丮 �ε����� ������ ī��Ʈ�� ���ش�. 
		_vInven[i]->setCount(_vInven[i]->getCount() - 1);

		//���Կ� �ִ� �������� 0���� �۾��� ��� �ش� �����ʹ� �������ش�. 
		if (_vInven[i]->getCount() <= 0)
		{
			_invenSlot[_cursor->getSlotIdx()].isEmpty = true;
			SAFE_DELETE(_vInven[i]);
			_vInven.erase(_vInven.begin() + i);
			return;
		}
	}
}

void inventory::grabAllItem()
{
	//Ŀ���� ����Ű�� �κ��丮 �ε����� ��ġ�ϴ� �������� itemGrabbed�� ��´�.
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vInven[i]->getInvenPosIdx() != _cursor->getSlotIdx()) continue;

		//�������� �Ѳ����� ���� ���̹Ƿ� ���� �״�� ������ Ŭ������ �������ش�. 
		_itemGrabbed = *(_vInven[i]);

		//�������� �Ѳ����� ���� ���̹Ƿ� ���Կ� �ִ� �������� ���� 
		_invenSlot[_cursor->getSlotIdx()].isEmpty = true;
		SAFE_DELETE(_vInven[i]);
		_vInven.erase(_vInven.begin() + i);
		return;
	}
}

void inventory::grabOneMoreItem()
{
	//���� �������� ������ŭ �κ��丮 �ε����� ������ ī��Ʈ�� ���ش�. 
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vInven[i]->getInvenPosIdx() != _cursor->getSlotIdx()) continue;

		//���� ���� �����۰� ������ �������� �ٸ��ٸ� �ٲ�ġ���ϱ� 
		if (_itemGrabbed.getItemIdx() != _vInven[i]->getItemIdx())
		{
			SOUNDMANAGER->play("cursor_drop", 0.4f);

			gameItem *item = new gameItem;
			item->init(&_itemGrabbed);
			item->setInvenPosIdx(_cursor->getSlotIdx());

			_itemGrabbed = *(_vInven[i]);
			SAFE_DELETE(_vInven[i]);
			_vInven.erase(_vInven.begin() + i);
			_vInven.push_back(item);
			return;
		}
		else
		{
			//�̹� ������ ���������� �ִ밳���̰ų�, ���� ���� ���� �ִ� ������ �ʰ��� �� ����Ī
			if (_vInven[i]->getCount() == _vInven[i]->getMaxCount() ||
				_vInven[i]->getCount() + _itemGrabbed.getCount() > _vInven[i]->getMaxCount())
			{
				SOUNDMANAGER->play("cursor_drop", 0.4f);

				gameItem *item = new gameItem;
				item->init(&_itemGrabbed);
				item->setInvenPosIdx(_cursor->getSlotIdx());

				_itemGrabbed = *(_vInven[i]);
				SAFE_DELETE(_vInven[i]);
				_vInven.erase(_vInven.begin() + i);
				_vInven.push_back(item);
				return;
			}

			SOUNDMANAGER->play("cursor_pick", 0.4f);

			//������ ��� �ִ� �����۰� ���� ������ �������� �ϳ� �� ��´�. 
			_itemGrabbed.plusOneCount();
			_vInven[i]->minusOneCount();

			//���Կ� �ִ� �������� 0���� �۾��� ��� �ش� �����ʹ� �������ش�. 
			if (_vInven[i]->getCount() <= 0)
			{
				//������ �����ߴ� ������ ��������Ƿ� ���� ����ִ� �������� ��ġ����
				//���� ����Ű�� �ִ� ������ ��ġ������ �����Ѵ�.

				_itemGrabbed.setInvenPosIdx(_cursor->getSlotIdx());
				_invenSlot[_cursor->getSlotIdx()].isEmpty = true;
				SAFE_DELETE(_vInven[i]);
				_vInven.erase(_vInven.begin() + i);
			}
			return;
		}
	}//end of for 
}

void inventory::putItem()
{
	//��� �ִ� �������� ���� ��� �Լ� ���� 
	if (!_isGrabbingItem) return;

	//��� �� ���� ������ �ش� Ÿ���� ���� �����۸� ���� ���� 
	switch (_cursor->getSlotIdx())
	{
	case 5: case 6: case 12: case 13:
	case 19: case 20: case 26: case 27:
		if (_itemGrabbed.getType() != _invenSlot[_cursor->getSlotIdx()].type)
		{
			SOUNDMANAGER->play("cursor_error", 0.6f);
			return;
		}
		break;

	case 28: case 29: case 30:
		SOUNDMANAGER->play("cursor_error", 0.6f);
		return;

	default:
		break;
	}

	//�� ������ Ŭ������ �� �ش� ���Կ� ����ִ� �������� ���´�.
	if (_invenSlot[_cursor->getSlotIdx()].isEmpty)
	{
		_isPuttingItem = true;
		putItemOnEmptySlot();
		_isGrabbingItem = false;
		SOUNDMANAGER->play("cursor_drop", 0.4f);
	}
	else //������ ������� ���� �� 
	{
		//1.ó�� �������� ��Ҵ� ��ġ�� �ٽ� Ŭ������ �� �������� �� ���� ��´�.  
		if (_itemGrabbed.getInvenPosIdx() == _cursor->getSlotIdx())
		{
			_isPuttingItem = true;
			grabOneMoreItem();
		}
		else //2.ó�� �������� ���� ��ġ�� �ƴ� �� 
		{
			_isPuttingItem = true;
			putItemOnOccupiedSlot();
		}
	}
}

void inventory::putItemOnEmptySlot()
{
	//�� ���Ӿ������� �����ؼ� ���� ��� �ִ� �������� �����ϰ� 
	//�ش� ���Ӿ������� ���� Ŀ���� ����Ű�� �ִ� ��ġ�� �����Ͽ� Ǫ�ù��Ѵ�. 
	gameItem *item = new gameItem;
	item->init(&_itemGrabbed);

	item->setInvenPosIdx(_cursor->getSlotIdx());
	_vInven.push_back(item);
	_invenSlot[_cursor->getSlotIdx()].isEmpty = false;

	_itemGrabbed = _itemEmpty;
}

void inventory::putItemOnOccupiedSlot()
{
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vInven[i]->getInvenPosIdx() != _cursor->getSlotIdx()) continue;

		//1.���� ���� ��� �ִ� �����۰� ���Կ� �ִ� �������� ������ ���� �� 
		if (_itemGrabbed.getItemIdx() == _vInven[i]->getItemIdx())
		{
			SOUNDMANAGER->play("cursor_drop", 0.4f);

			//�̹� ������ ���������� �ִ밳���� ���� ����Ī
			if (_vInven[i]->getCount() == _vInven[i]->getMaxCount())
			{
				gameItem *item = new gameItem;
				item->init(&_itemGrabbed);
				item->setInvenPosIdx(_cursor->getSlotIdx());

				_itemGrabbed = *(_vInven[i]);
				SAFE_DELETE(_vInven[i]);
				_vInven.erase(_vInven.begin() + i);
				_vInven.push_back(item);
				return;
			}

			//���� ��� �ִ� �������� ���Կ� ��ġ�µ�, �� �������� ���Կ� ���� ������
			//�ִ� ������ ������ �ѱ� ��� �ִ� �������� ���Կ� �����ϰ�, �������� �ٽ� ��´�. 
			int maxCount = _itemGrabbed.getMaxCount();
			int sum = _itemGrabbed.getCount() + _vInven[i]->getCount();

			if (sum > maxCount) //�ִ� ���� ������ �Ѱ��� �� 
			{
				_itemGrabbed.setCount(_itemGrabbed.getCount() - (maxCount - _vInven[i]->getCount()));
				_vInven[i]->setCount(maxCount);
				_itemGrabbed.setInvenPosIdx(i);
				return;
			}
			else //�ִ� ���� ������ �ѱ��� �ʾ��� �� 
			{
				_vInven[i]->setCount(sum);
				_itemGrabbed = _itemEmpty;
				_isGrabbingItem = false;
				return;
			}
		}
		else //2.���� ���� ��� �ִ� �����۰� ���Կ� �ִ� ������ ������ �ٸ� �� 
		{
			//��� �� ���� ������ �������� �Ϲ� �����۰� �ٲٷ��� �� ��� �Լ� ���� 
			switch (_itemGrabbed.getInvenPosIdx())
			{
			case 5: case 6: case 12: case 13:
			case 19: case 20: case 26: case 27:
				if (_itemGrabbed.getType() != _invenSlot[_cursor->getSlotIdx()].type)
				{
					SOUNDMANAGER->play("cursor_error", 0.6f);
					return;
				}
				break;

			case 28: case 29: case 30:
				SOUNDMANAGER->play("cursor_error", 0.6f);
				return;

			default:
				break;
			}

			SOUNDMANAGER->play("cursor_drop", 0.4f);

			//���� �������� ��Ҵ� �����ڸ��� ����ִ� ���
			if (_invenSlot[_itemGrabbed.getInvenPosIdx()].isEmpty)
			{
				//���� ����ִ� �������� �����ڸ��� ������, 
				//�����ڸ��� �ִ� �������� ���� ����ִ� �������� ����Ű�� �ε����� ������. 
				gameItem *item = new gameItem;
				item->init(&_itemGrabbed);
				item->setInvenPosIdx(_cursor->getSlotIdx());
				_vInven.push_back(item);

				_vInven[i]->setInvenPosIdx(_itemGrabbed.getInvenPosIdx());
				_invenSlot[_itemGrabbed.getInvenPosIdx()].isEmpty = false;

				_itemGrabbed = _itemEmpty;
				_isGrabbingItem = false;
				return;
			}
			else //������� ���� ��� ���� ����ִ� �����۰� ���Կ� �ִ� ������ �ٲ�ġ�� 
			{
				gameItem *item = new gameItem;
				item->init(&_itemGrabbed);
				item->setInvenPosIdx(_cursor->getSlotIdx());

				_itemGrabbed = *(_vInven[i]);
				SAFE_DELETE(_vInven[i]);
				_vInven.erase(_vInven.begin() + i);
				_vInven.push_back(item);
				//push_back�� ���ְ��� �� for���� ���� �ߺ������� �� �� �����Ƿ�
				//�ݵ�� return�Ͽ� �Լ��� ��������ش�. 
				return;
			}
		}
	}//end of for 
}

void inventory::putGrabbingItem()
{
	//��� �ִ� �������� �ִٸ� ���� �ڸ��� �������� 
	if (!_isGrabbingItem) return; 
	
	//���� �������� ���� ������ �ڸ��� ����ִٸ�
	if (_invenSlot[_itemGrabbed.getInvenPosIdx()].isEmpty)
	{
		//����ִ� ������ �����ؼ� ���Ϳ� Ǫ���ϰ� ���� �������� ���ֱ� 
		gameItem *item = new gameItem;
		item->init(&_itemGrabbed);
		_vInven.push_back(item);

		_invenSlot[item->getInvenPosIdx()].isEmpty = false; 
		_itemGrabbed = _itemEmpty;
		_isGrabbingItem = false; 
	}
	else // ������� �ʴٸ� ��� �ִ� �������� ī��Ʈ�� ���Կ� ���ϱ� 
	{
		for (int i = 0; i < _vInven.size(); i++)
		{
			//���� ��� �ִ� �������� ���� �ִ� �ڸ��� �ε��� ã�� 
			if (_vInven[i]->getInvenPosIdx() != _itemGrabbed.getInvenPosIdx()) continue;

			_vInven[i]->setCount(_vInven[i]->getCount() + _itemGrabbed.getCount());

			_itemGrabbed = _itemEmpty;
			_isGrabbingItem = false;
			return;

		}//end of for 
	}
}

void inventory::cursorRender(HDC hdc)
{
	//Ŀ���� ���¿� ���� ����� �޸��Ѵ�. 
	switch (_cursor->getState())
	{
		case CURSOR_SELECT_IDLE : case CURSOR_SELECT_MOVE:
			selectCursorRender(hdc);
			break;

		default:
			invenCursorRender(hdc);
			break;
	}
}

void inventory::invenCursorRender(HDC hdc)
{
	//Ŀ�� ���(������ �ұ�Ģ�ϰ� �����־ ����ó��) 
	for (int i = 0; i < MAXSLOT; i++)
	{
		int columnIdx = _cursor->getSlotIdx() % 7;
		int rowIdx = _cursor->getSlotIdx() / 7;

		switch (_cursor->getSlotIdx())
		{
			case 0: case 1: case 2: case 3: case 4:
				_cursor->getImg()->frameRender(hdc,
					204 + (columnIdx * 72), 158, _cursor->getIdx(), 0);
				break;

			case 7: case 8: case 9: case 10: case 11:
			case 14: case 15: case 16: case 17: case 18:
			case 21: case 22: case 23: case 24: case 25:
				_cursor->getImg()->frameRender(hdc,
					204 + (columnIdx * 72), 244 + ((rowIdx - 1) * 72), _cursor->getIdx(), 0);
				break;

			case 5:
				_cursor->getImg()->frameRender(hdc, 734, 154, _cursor->getIdx(), 0);
				break;

			case 6:
				_cursor->getImg()->frameRender(hdc, 908, 154, _cursor->getIdx(), 0);
				break;

			case 12:
				_cursor->getImg()->frameRender(hdc, 650, 244, _cursor->getIdx(), 0);
				break;

			case 13:
				_cursor->getImg()->frameRender(hdc, 722, 244, _cursor->getIdx(), 0);
				break;

			case 19:
				_cursor->getImg()->frameRender(hdc, 650, 316, _cursor->getIdx(), 0);
				break;

			case 20:
				_cursor->getImg()->frameRender(hdc, 722, 316, _cursor->getIdx(), 0);
				break;

			case 26:
				_cursor->getImg()->frameRender(hdc, 650, 388, _cursor->getIdx(), 0);
				break;

			case 27:
				_cursor->getImg()->frameRender(hdc, 722, 388, _cursor->getIdx(), 0);
				break;

			case 28:
				_cursor->getImg()->frameRender(hdc, 204, 506, _cursor->getIdx(), 0);
				break;

			case 29:
				_cursor->getImg()->frameRender(hdc, 356, 484, _cursor->getIdx(), 0);
				break;

			case 30:
				_cursor->getImg()->frameRender(hdc, 470, 484, _cursor->getIdx(), 0);
				break;
		}
	}
}

void inventory::merchantIconRender(HDC hdc)
{
	//������ ���� �� ������ ���� �̻��� ��尡 ���� ���� ������ ������ ��� 
	if (PLAYERDATA->getIsInDungeon())
	{
		if (PLAYERDATA->getGold() >= 200) IMAGEMANAGER->render("bag_pendant", hdc, 360, 496);
		if (PLAYERDATA->getGold() >= 1000) IMAGEMANAGER->render("bag_emblem", hdc, 474, 488);
	}
}

void inventory::selectCursorRender(HDC hdc)
{
	switch (_cursor->getSlotIdx())
	{
		case 28:
			break;

		case 29:
			break;

		case 30:
			break;

		default:
			break;
	}
}

void inventory::pendantCtrlRender(HDC hdc)
{
	IMAGEMANAGER->frameRender("cursor_move", hdc, 356, 484, 3, 0);
	IMAGEMANAGER->render("inventory_selectBubble", hdc, 404, 332);

	//selectIdx�� ���� �˸��� �̹��� ����ϱ� 
	if (_selectMenu->getSelectIdx() == SELECT_YES)
	{
		_selectMenu->getImg()->frameRender(hdc, 426, 356, _selectMenu->getIdx(), 0);
		_cursor->getImg()->frameRender(hdc, 414, 344, _cursor->getIdx(), 0);

		RECT txtRC = RectMake(444, 438, 42, 26);
		HFONT font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
		HFONT oFont = (HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(227, 212, 184));
		DrawText(hdc, "��", -1, &txtRC, DT_CENTER | DT_WORDBREAK | DT_VCENTER);
		SelectObject(hdc, oFont);
		DeleteObject(font);
	}
	else
	{
		_selectMenu->getImg()->frameRender(hdc, 524, 356, _selectMenu->getIdx(), 0);
		_cursor->getImg()->frameRender(hdc, 512, 344, _cursor->getIdx(), 0);

		RECT txtRC = RectMake(534, 438, 58, 26);
		HFONT font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
		HFONT oFont = (HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(227, 212, 184));
		DrawText(hdc, "�ƴϿ�", -1, &txtRC, DT_CENTER | DT_WORDBREAK | DT_VCENTER);
		SelectObject(hdc, oFont);
		DeleteObject(font);
	}
}

void inventory::emblemCtrlRender(HDC hdc)
{
	IMAGEMANAGER->frameRender("cursor_move", hdc, 356 + 114, 484, 3, 0);
	IMAGEMANAGER->render("inventory_selectBubble", hdc, 404 + 114, 332);

	//selectIdx�� ���� �˸��� �̹��� ����ϱ� 
	if (_selectMenu->getSelectIdx() == SELECT_YES)
	{
		_selectMenu->getImg()->frameRender(hdc, 426 + 114, 356, _selectMenu->getIdx(), 0);
		_cursor->getImg()->frameRender(hdc, 414 + 114, 344, _cursor->getIdx(), 0);

		RECT txtRC = RectMake(444 + 114, 438, 42, 26);
		HFONT font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
		HFONT oFont = (HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(227, 212, 184));
		DrawText(hdc, "��", -1, &txtRC, DT_CENTER | DT_WORDBREAK | DT_VCENTER);
		SelectObject(hdc, oFont);
		DeleteObject(font);
	}
	else
	{
		_selectMenu->getImg()->frameRender(hdc, 524 + 114, 356, _selectMenu->getIdx(), 0);
		_cursor->getImg()->frameRender(hdc, 512 + 114, 344, _cursor->getIdx(), 0);

		RECT txtRC = RectMake(534 + 114, 438, 58, 26);
		HFONT font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
		HFONT oFont = (HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(227, 212, 184));
		DrawText(hdc, "�ƴϿ�", -1, &txtRC, DT_CENTER | DT_WORDBREAK | DT_VCENTER);
		SelectObject(hdc, oFont);
		DeleteObject(font);
	}
}

void inventory::statusRender(HDC hdc)
{
	//�÷��̾� �����Ϳ��� ����Ʈ ���Ȱ� �������� 
	int hp = PLAYERDATA->getDefaultHp();
	int atk = PLAYERDATA->getDefaultAtk();
	int def = PLAYERDATA->getDefaultDef();
	int spd = PLAYERDATA->getDefaultSpd();

	//������ ������ �������ͽ����� �����ͼ� ���ϱ� 
	switch (_curWeaponIdx)
	{
		case 1:
			if (!_invenSlot[5].isEmpty)
			{
				for (int i = 0; i < _vInven.size(); i++)
				{
					if (_vInven[i]->getInvenPosIdx() != 5) continue;

					hp += *(_vInven[i]->getAbility() + ABILITY_HP);
					atk += *(_vInven[i]->getAbility() + ABILITY_ATK);
					def += *(_vInven[i]->getAbility() + ABILITY_DEF);
					spd += *(_vInven[i]->getAbility() + ABILITY_SPD);
				}
			}
			break;

		case 2:
			if (!_invenSlot[6].isEmpty)
			{
				for (int i = 0; i < _vInven.size(); i++)
				{
					if (_vInven[i]->getInvenPosIdx() != 6) continue;

					hp += *(_vInven[i]->getAbility() + ABILITY_HP);
					atk += *(_vInven[i]->getAbility() + ABILITY_ATK);
					def += *(_vInven[i]->getAbility() + ABILITY_DEF);
					spd += *(_vInven[i]->getAbility() + ABILITY_SPD);
				}
			}
			break;
	}

	//��� ���Ȱ��� �ݿ��� �������ͽ����� �÷��̾� �����Ϳ� �ݿ��ϱ� 
	PLAYERDATA->setHp(hp);
	PLAYERDATA->setAtk(atk);
	PLAYERDATA->setDef(def);
	PLAYERDATA->setSpd(spd);

	//��� ���Ȱ��� �ݿ��� �������ͽ��� ����ϱ� 
	statusNumRender(hdc, hp, 292);
	statusNumRender(hdc, atk, 352);
	statusNumRender(hdc, def, 412);
	statusNumRender(hdc, spd, 472);
}

void inventory::weaponIconRender(HDC hdc)
{
	switch (_curWeaponIdx)
	{
		case 1:
			IMAGEMANAGER->findImage("icon_equip_idx_empty")->frameRender(hdc,
				962, 206, 1, 0);
			IMAGEMANAGER->findImage("icon_equip_idx")->frameRender(hdc,
				788, 206, 0, 0);
			IMAGEMANAGER->findImage("icon_euip")->frameRender(hdc,
				806, 176, 0, 0);
			break;

		case 2:
			IMAGEMANAGER->findImage("icon_equip_idx_empty")->frameRender(hdc,
				788, 206, 0, 0);
			IMAGEMANAGER->findImage("icon_equip_idx")->frameRender(hdc,
				962, 206, 1, 0);
			IMAGEMANAGER->findImage("icon_euip")->frameRender(hdc,
				880, 176, 1, 0);
			break;
	}
}

void inventory::itemRender(HDC hdc)
{
	for (int i = 0; i < MAXSLOT; i++)
	{
		//����ִ� ������ �ǳʶٱ� 
		if (_invenSlot[i].isEmpty) continue;

		//������� ���� ������ �κ��丮 ���Ϳ��� �ش� ������ �ε����� ��ġ�ϴ� �������� ��� 
		for (int j = 0; j < _vInven.size(); j++)
		{
			//�κ��丮 ���Ϳ��� ������ �ε����� ��ġ���� �ʴ� �������� �ǳʶٱ� 
			if (_vInven[j]->getInvenPosIdx() != i) continue;

			int columnIdx = _vInven[j]->getInvenPosIdx() % 7;
			int rowIdx = _vInven[j]->getInvenPosIdx() / 7;

			//�κ��丮 �ε����� �´� ��ġ�� ������ �̹����� ���� �̹��� ��� 
			switch (_vInven[j]->getInvenPosIdx())
			{
				case 0: case 1: case 2: case 3: case 4:
					_vInven[j]->getItemImg()->render(hdc,
						218 + (columnIdx * 72), 172);
					itemCountRender(hdc, _vInven[j]->getCount(),
						258 + (columnIdx * 72), 208);
					break;

				case 7: case 8: case 9: case 10: case 11:
				case 14: case 15: case 16: case 17: case 18:
				case 21: case 22: case 23: case 24: case 25:
					_vInven[j]->getItemImg()->render(hdc,
						218 + (columnIdx * 72), 258 + ((rowIdx - 1) * 72));
					itemCountRender(hdc, _vInven[j]->getCount(),
						258 + (columnIdx * 72), 294 + ((rowIdx - 1) * 72));
					break;

				case 5:
					IMAGEMANAGER->findImage("item_slot")->render(hdc, 742, 162);
					_vInven[j]->getItemImg()->render(hdc, 748, 168);
					break;

				case 6:
					IMAGEMANAGER->findImage("item_slot")->render(hdc, 916, 162);
					_vInven[j]->getItemImg()->render(hdc, 922, 168);
					break;

				case 12:
					_vInven[j]->getItemImg()->render(hdc, 664, 258);
					break;

				case 13:
					_vInven[j]->getItemImg()->render(hdc, 736, 258);
					break;

				case 19:
					_vInven[j]->getItemImg()->render(hdc, 664, 330);
					break;

				case 20:
					IMAGEMANAGER->findImage("item_slot")->render(hdc, 730, 324);
					_vInven[j]->getItemImg()->render(hdc, 736, 330);
					itemCountRender(hdc, _vInven[j]->getCount(), 776, 366);
					break;

				case 26:
					_vInven[j]->getItemImg()->render(hdc, 664, 402);
					break;

				case 27:
					_vInven[j]->getItemImg()->render(hdc, 736, 402);
					break;
			}//end of switch 

			//������ �ε����� ��ġ�ϴ� �������� ����ߴٸ� for�� Ż�� 
			break;

		}//end of for(j)
	}//end of for(i)

}

void inventory::itemGrabbedRender(HDC hdc)
{
	//���� ������ ���(Ŀ���� ���)
	for (int i = 0; i < MAXSLOT; i++)
	{
		int columnIdx = _cursor->getSlotIdx() % 7;
		int rowIdx = _cursor->getSlotIdx() / 7;

		switch (_cursor->getSlotIdx())
		{
			case 0: case 1: case 2: case 3: case 4:
				IMAGEMANAGER->render("grabBase", hdc,
					206 + (columnIdx * 72), 90);
				_itemGrabbed.getItemImg()->render(hdc,
					218 + (columnIdx * 72), 100);
				itemCountRender(hdc, _itemGrabbed.getCount(), 258 + (columnIdx * 72), 136);
				break;

			case 7: case 8: case 9: case 10: case 11:
			case 14: case 15: case 16: case 17: case 18:
			case 21: case 22: case 23: case 24: case 25:
				IMAGEMANAGER->render("grabBase", hdc,
					206 + (columnIdx * 72), 176 + ((rowIdx - 1) * 72));
				_itemGrabbed.getItemImg()->render(hdc,
					218 + (columnIdx * 72), 186 + ((rowIdx - 1) * 72));
				itemCountRender(hdc, _itemGrabbed.getCount(),
					258 + (columnIdx * 72), 222 + ((rowIdx - 1) * 72));
				break;

			case 5:
				IMAGEMANAGER->render("grabBase", hdc, 736, 86);
				_itemGrabbed.getItemImg()->render(hdc, 748, 96);
				itemCountRender(hdc, _itemGrabbed.getCount(), 788, 132);
				break;

			case 6:
				IMAGEMANAGER->render("grabBase", hdc, 910, 86);
				_itemGrabbed.getItemImg()->render(hdc, 922, 96);
				itemCountRender(hdc, _itemGrabbed.getCount(), 962, 132);
				break;

			case 12:
				IMAGEMANAGER->render("grabBase", hdc, 652, 176);
				_itemGrabbed.getItemImg()->render(hdc, 664, 186);
				itemCountRender(hdc, _itemGrabbed.getCount(), 704, 222);
				break;

			case 13:
				IMAGEMANAGER->render("grabBase", hdc, 724, 176);
				_itemGrabbed.getItemImg()->render(hdc, 736, 186);
				itemCountRender(hdc, _itemGrabbed.getCount(), 776, 222);
				break;

			case 19:
				IMAGEMANAGER->render("grabBase", hdc, 652, 248);
				_itemGrabbed.getItemImg()->render(hdc, 664, 258);
				itemCountRender(hdc, _itemGrabbed.getCount(), 704, 294);
				break;

			case 20:
				IMAGEMANAGER->render("grabBase", hdc, 724, 248);
				_itemGrabbed.getItemImg()->render(hdc, 736, 258);
				itemCountRender(hdc, _itemGrabbed.getCount(), 776, 294);
				break;

			case 26:
				IMAGEMANAGER->render("grabBase", hdc, 652, 320);
				_itemGrabbed.getItemImg()->render(hdc, 664, 330);
				itemCountRender(hdc, _itemGrabbed.getCount(), 704, 366);
				break;

			case 27:
				IMAGEMANAGER->render("grabBase", hdc, 724, 320);
				_itemGrabbed.getItemImg()->render(hdc, 736, 330);
				itemCountRender(hdc, _itemGrabbed.getCount(), 776, 366);
				break;

			case 28:
				IMAGEMANAGER->render("grabBase", hdc, 206, 438);
				_itemGrabbed.getItemImg()->render(hdc, 218, 448);
				itemCountRender(hdc, _itemGrabbed.getCount(), 258, 484);
				break;

			case 29:
				IMAGEMANAGER->render("grabBase", hdc, 358, 414);
				_itemGrabbed.getItemImg()->render(hdc, 370, 424);
				itemCountRender(hdc, _itemGrabbed.getCount(), 410, 460);
				break;

			case 30:
				IMAGEMANAGER->render("grabBase", hdc, 470, 414);
				_itemGrabbed.getItemImg()->render(hdc, 482, 424);
				itemCountRender(hdc, _itemGrabbed.getCount(), 522, 460);
				break;
		}
	}
}

void inventory::itemNameRender(HDC hdc)
{
	//Ŀ���� ����Ű�� �κ��丮�� ������ ����ִ� ��� �Լ��� ���� 
	if (_invenSlot[_cursor->getSlotIdx()].isEmpty) return;

	//Ŀ���� ����Ű�� �κ��丮 �ε����� ��ġ�ϴ� �������� ã�´�. 
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vInven[i]->getInvenPosIdx() != _cursor->getSlotIdx()) continue;

		IMAGEMANAGER->render("nameBase", hdc, 468, 630);
		_vInven[i]->getNameImg()->render(hdc, 544, 635);
	}
}

void inventory::itemCountRender(HDC hdc, int count, int destX, int destY)
{
	for (int i = 1, distance = 0; i <= count; i *= 10)
	{
		int number = (count / i) % 10;

		char keyName[16];
		wsprintf(keyName, "%d_black", number);
		IMAGEMANAGER->render(keyName, hdc, destX - (distance * 12), destY);

		distance++;
	}
}

void inventory::statusNumRender(HDC hdc, int number, int destY)
{
	// number < 10  
	if (number < 10)
	{
		for (int i = 1; i <= number; i *= 10)
		{
			int num = (number / i) % 10;

			char keyName[16];
			wsprintf(keyName, "%d", num);
			IMAGEMANAGER->render(keyName, hdc, 1114, destY);
		}
	}
	else if (number < 100) // 10 <= number < 100
	{
		for (int i = 1, distance = 0; i <= number; i *= 10)
		{
			int num = (number / i) % 10;

			char keyName[16];
			wsprintf(keyName, "%d", num);
			IMAGEMANAGER->render(keyName, hdc, 1120 - (distance * 12), destY);

			distance++;
		}
	}
	else // number >= 100 
	{
		for (int i = 1, distance = 0; i <= number; i *= 10)
		{
			int num = (number / i) % 10;

			char keyName[16];
			wsprintf(keyName, "%d", num);
			IMAGEMANAGER->render(keyName, hdc, 1126 - (distance * 12), destY);

			distance++;
		}
	}
}

