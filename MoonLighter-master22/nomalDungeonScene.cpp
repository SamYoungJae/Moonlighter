#include "stdafx.h"
#include "nomalDungeonScene.h"
#include "mapSaveLoad.h"

HRESULT nomalDungeonScene::init()
{
	//���� ������Ʈ ����
	_dState = DS_UPDATE;
	//��������
	_dgFloor = 1;

	_startDungeon = new DungeonMap(0, 0);
	_startDungeon->setCurrentFloor(_dgFloor);
	_startDungeon->init();
	_currentDungeon = _startDungeon;

	_golemScroll = new animation;
	_golemScroll->init(IMAGEMANAGER->findImage("golemScroll"), 0, 7);

	//�÷��̾� �׽�Ʈ
	_player = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 40, 40);
	PLAYERDATA->setIsInDungeon(true);
	//���ʹ� �׽�Ʈ


	PLAYER->setX(WINSIZEX / 2);
	PLAYER->setY(WINSIZEY / 2);

	SOUNDMANAGER->play("bossRoomBGM");


	//ī�޶� �ʱ�ȭ
	CAMERAMANAGER->init(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY, 0, 0, WINSIZEX / 2, WINSIZEY / 2);
	CAMERAMANAGER->FadeInit(80, FADE_IN);
	CAMERAMANAGER->FadeStart();

	this->initItemSlot();
	this->getInvenItem();

	return S_OK;
}

void nomalDungeonScene::release()
{
}

void nomalDungeonScene::update()
{
	
	//this->soundUpdate();


	if (_currentDungeon->moveDungeon(PLAYER->getShadowRect()) != nullptr && _currentDungeon->getDungeonDoorState() == DUNGEONDOOR::DOOR_OPEN 
		&& _currentDungeon->getDungeonKind() != DG_SEMIBOSS)
	{
		//�÷��̾� �̵�
		switch (_currentDungeon->moveDungeonDirection(PLAYER->getShadowRect()))
		{
		case 1:
			_currentDungeon = _currentDungeon->moveDungeon(PLAYER->getShadowRect());
			PLAYER->setX(1085 + 17);
			PLAYER->setY(350 + 17);
			break;
		case 2:
			_currentDungeon = _currentDungeon->moveDungeon(PLAYER->getShadowRect());
			PLAYER->setX(140 + 17);
			PLAYER->setY(350 + 17);
			break;
		case 3:
			_currentDungeon = _currentDungeon->moveDungeon(PLAYER->getShadowRect());
			PLAYER->setX(595 + 17);
			PLAYER->setY(595 + 17);
			break;
		case 4:
			_currentDungeon = _currentDungeon->moveDungeon(PLAYER->getShadowRect());
			PLAYER->setX(595 + 17);
			PLAYER->setY(105 + 17);
			break;
		}
		//���� �̵�
		
		
	}
	else if (_currentDungeon->moveDungeonDirection(PLAYER->getShadowRect()) == 5 && _currentDungeon->getDungeonDoorState() == DUNGEONDOOR::DOOR_OPEN)
	{
		this->setNewFloor();
	}


	//�񷽽�ũ�� ����
	_golemScroll->update();
	//�̴ϸ� �Ȱ��κ� �߰����� (�ǵ��ʿ����)
	if (this->minimapPush(_currentDungeon->getDungeonXY()))
	{
		_vMinimap.push_back(make_pair(_currentDungeon->getDungeonXY(), _currentDungeon));
	}


	//���� ����
	_currentDungeon->update();
	//ī�޶� ����
	CAMERAMANAGER->update(PLAYER->getX(),PLAYER->getY());
	CAMERAMANAGER->movePivot(PLAYER->getX(), PLAYER->getY());


	PLAYER->update();
	ITEMMENU->update();
}

void nomalDungeonScene::render()
{

	PLAYER->render(getMemDC());
	_currentDungeon->render();

	//�� ��ũ�� ����
	if (_golemScroll->getAniState() == ANIMATION_PLAY)
	{
		_golemScroll->ZorderStretchRender(2000, WINSIZEX / 2, WINSIZEY - 150, 2.f);
		RECT txtRC = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 70, 300, 40);
		HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
		CAMERAMANAGER->ZorderDrawText("��   ����", WINSIZEY / 2, txtRC, hFont, RGB(255, 255, 255), DT_CENTER | DT_WORDBREAK | DT_VCENTER);
		txtRC = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 50, 300, 40);
		CAMERAMANAGER->ZorderDrawText(to_string(_dgFloor), WINSIZEY / 2, txtRC, hFont, RGB(255, 255, 255), DT_CENTER | DT_WORDBREAK | DT_VCENTER);
	}

	if (INPUT->GetKey(VK_TAB))
	{
		this->minimapRender();
	}

	CAMERAMANAGER->ZorderTotalRender(getMemDC());
	ITEMMENU->render(getMemDC());

	//this->itemResultRender();
	
}
bool nomalDungeonScene::minimapPush(POINT pt)
{
	for (int i = 0; i < _vMinimap.size(); i++)
	{
		if (_vMinimap[i].first.x == pt.x && _vMinimap[i].first.y == pt.y) return false;
	}
	return true;
}
void nomalDungeonScene::minimapRender()
{
	IMAGEMANAGER->addImage("minimapBack", WINSIZEX, WINSIZEY)->alphaRender(getMemDC(), 0, 0, 150);

	for (int i = 0; i < _vMinimap.size(); i++)
	{
		RECT rc = RectMakeCenter(WINSIZEX / 2 + (_vMinimap[i].first.x * 100), WINSIZEY / 2 + (_vMinimap[i].first.y * 65), 86, 48);
		//Rectangle(getMemDC(), rc);
		IMAGEMANAGER->findImage("minimap")->frameRender(getMemDC(), rc.left, rc.top, 0, 0);

		if (_vMinimap[i].second->getLeftDG() != nullptr)        IMAGEMANAGER->findImage("minimapEntranceW")->frameRender(getMemDC(), rc.left - 6, rc.bottom - 28, 0, 0);
		else                                            IMAGEMANAGER->findImage("minimapEntranceW")->frameRender(getMemDC(), rc.left, rc.bottom - 28, 0, 1);
		if (_vMinimap[i].second->getRightDG() != nullptr)    IMAGEMANAGER->findImage("minimapEntranceW")->frameRender(getMemDC(), rc.right - 2, rc.bottom - 28, 0, 0);
		else                                            IMAGEMANAGER->findImage("minimapEntranceW")->frameRender(getMemDC(), rc.right - 2, rc.bottom - 28, 0, 1);
		if (_vMinimap[i].second->getTopDG() != nullptr)        IMAGEMANAGER->findImage("minimapEntranceH")->frameRender(getMemDC(), rc.left + 38, rc.top - 6, 0, 0);
		else                                            IMAGEMANAGER->findImage("minimapEntranceH")->frameRender(getMemDC(), rc.left + 38, rc.top - 4, 0, 1);
		if (_vMinimap[i].second->getBottomDG() != nullptr)    IMAGEMANAGER->findImage("minimapEntranceH")->frameRender(getMemDC(), rc.left + 38, rc.bottom, 0, 0);
		else                                            IMAGEMANAGER->findImage("minimapEntranceH")->frameRender(getMemDC(), rc.left + 38, rc.bottom - 6, 0, 1);
	}

	RECT rc = RectMakeCenter(WINSIZEX / 2 + (_currentDungeon->getDungeonXY().x * 100), WINSIZEY / 2 + (_currentDungeon->getDungeonXY().y * 65), 86, 48);
	IMAGEMANAGER->findImage("minimap")->frameRender(getMemDC(), rc.left, rc.top, 1, 0);

	if (_currentDungeon->getLeftDG() != nullptr)        IMAGEMANAGER->findImage("minimapEntranceW")->frameRender(getMemDC(), rc.left - 6, rc.bottom - 28, 1, 0);
	else                                        IMAGEMANAGER->findImage("minimapEntranceW")->frameRender(getMemDC(), rc.left, rc.bottom - 28, 1, 1);
	if (_currentDungeon->getRightDG() != nullptr)    IMAGEMANAGER->findImage("minimapEntranceW")->frameRender(getMemDC(), rc.right - 2, rc.bottom - 28, 1, 0);
	else                                        IMAGEMANAGER->findImage("minimapEntranceW")->frameRender(getMemDC(), rc.right - 2, rc.bottom - 28, 1, 1);
	if (_currentDungeon->getTopDG() != nullptr)        IMAGEMANAGER->findImage("minimapEntranceH")->frameRender(getMemDC(), rc.left + 38, rc.top - 6, 1, 0);
	else                                        IMAGEMANAGER->findImage("minimapEntranceH")->frameRender(getMemDC(), rc.left + 38, rc.top - 4, 1, 1);
	if (_currentDungeon->getBottomDG() != nullptr)    IMAGEMANAGER->findImage("minimapEntranceH")->frameRender(getMemDC(), rc.left + 38, rc.bottom, 1, 0);
	else                                        IMAGEMANAGER->findImage("minimapEntranceH")->frameRender(getMemDC(), rc.left + 38, rc.bottom - 6, 1, 1);
	
}

void nomalDungeonScene::setNewFloor()
{
	SAFE_DELETE(_startDungeon);
	//��������
	_dgFloor++;

	_startDungeon = new DungeonMap(0, 0);
	_startDungeon->setCurrentFloor(_dgFloor);
	_startDungeon->init();
	_currentDungeon = _startDungeon;

	_golemScroll->aniRestart();

	//�÷��̾� �׽�Ʈ
	_player = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 40, 40);
	//���ʹ� �׽�Ʈ

	PLAYER->setX(WINSIZEX / 2);
	PLAYER->setY(WINSIZEY / 2);


	CAMERAMANAGER->FadeInit(80, FADE_IN);
	CAMERAMANAGER->FadeStart();
}

void nomalDungeonScene::soundUpdate()
{

}

void nomalDungeonScene::initItemSlot()
{
	for (int i = 0; i < 28; i++)
	{
		_dungeonSlot[i].slotIdx = i;
		_dungeonSlot[i].isEmpty = true;
	}
}

void nomalDungeonScene::getInvenItem()
{	
	//���� �� �κ��丮 ���Ϳ� �ִ� �������� ���� ����� 
	
	deleteInvenItems();

	for (int i = 0; i < ITEMMENU->getInventory()->getItem().size(); i++)
	{
		//���� ���Կ� �ִ� �������� �����ϰ� �κ��丮 ���Կ� �ִ� ������ �������� 
		switch (ITEMMENU->getInventory()->getItem()[i]->getInvenPosIdx())
		{
			case 5: case 6: case 12: case 13:
			case 19: case 20: case 26: case 27:
				break;

			default:
				gameItem *item = new gameItem;
				item->init(ITEMMENU->getInventory()->getItem()[i]);
				_vItem.push_back(item);
				_dungeonSlot[item->getInvenPosIdx()].isEmpty = false;
				break;
		}
	}
}

void nomalDungeonScene::deleteInvenItems()
{
	for (int i = 0; i < _vItem.size(); )
	{
		switch (_vItem[i]->getInvenPosIdx())
		{
			case 5: case 6: case 12: case 13:
			case 19: case 20: case 26: case 27:
				i++;
				break;

			default:
				SAFE_DELETE(_vItem[i]);
				_vItem.erase(_vItem.begin() + i);
				break;
		}
	}
}

void nomalDungeonScene::itemResultRender()
{
	IMAGEMANAGER->render("menu_shopInventory", getMemDC(), 100, 86);
	for (int i = 0; i < 28; i++)
	{
		//����ִ� ������ �ǳʶٱ� 
		if (_dungeonSlot[i].isEmpty) continue;

		//������� ���� ������ �κ��丮 ���Ϳ��� �ش� ������ �ε����� ��ġ�ϴ� �������� ��� 
		for (int j = 0; j < _vItem.size(); j++)
		{
			//�κ��丮 ���Ϳ��� ������ �ε����� ��ġ���� �ʴ� �������� �ǳʶٱ� 
			if (_vItem[j]->getInvenPosIdx() != i) continue;

			int columnIdx = _vItem[j]->getInvenPosIdx() % 7;
			int rowIdx = _vItem[j]->getInvenPosIdx() / 7;

			switch (_vItem[j]->getInvenPosIdx())
			{
			case 0: case 1: case 2: case 3: case 4:
				_vItem[j]->getItemImg()->render(getMemDC(),
					200 + (columnIdx * 72), 172);
				countRender(_vItem[j]->getCount(),
					240 + (columnIdx * 72), 208);
				break;

			case 7: case 8: case 9: case 10: case 11:
			case 14: case 15: case 16: case 17: case 18:
			case 21: case 22: case 23: case 24: case 25:
				_vItem[j]->getItemImg()->render(getMemDC(),
					200 + (columnIdx * 72), 258 + ((rowIdx - 1) * 72));
				countRender(_vItem[j]->getCount(),
					240 + (columnIdx * 72), 294 + ((rowIdx - 1) * 72));
				break;

			}//end of switch
		}//end of for(j)
	}//end of for(i)
}

void nomalDungeonScene::countRender(int count, int destX, int destY)
{
	if (count == 0)
	{
		IMAGEMANAGER->render("0_black", getMemDC(), destX, destY);
		return;
	}

	for (int i = 1, distance = 0; i <= count; i *= 10)
	{
		int number = (count / i) % 10;

		char keyName[16];

		wsprintf(keyName, "%d_black", number);
		IMAGEMANAGER->render(keyName, getMemDC(), destX - (distance * 12), destY);
		distance++;

	}//end of for
}
