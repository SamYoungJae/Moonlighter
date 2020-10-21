#include "stdafx.h"
#include "bossDungeonScene.h"
#include "mapSaveLoad.h"

HRESULT bossDungeonScene::init()
{
	
	PLAYER->setX(1024);
	PLAYER->setY(839 * 2 - 150);

	//_golemKing = new bossGolemKing;
	//_golemKing->init(1067, 477);
	_golemKing = nullptr;
	_bsState = BS_INIT;

	//Ÿ�� �ε��ϱ�
	this->loadTile();

	CAMERAMANAGER->init(PLAYER->getX(), PLAYER->getY(), 2048, 839 * 2, 0, 0, WINSIZEX / 2, WINSIZEY / 2);
	CAMERAMANAGER->FadeInit(80, FADE_IN);
	CAMERAMANAGER->FadeStart();


	SOUNDMANAGER->play("bossBGM", 0.5f);

	_potal = nullptr;
	_isPlayerRender = true;
	_aniCenter = new animation;

	this->initItemSlot();

	return S_OK;
}

void bossDungeonScene::release()
{
	if (_potal)
	{
		_potal->release();
		SAFE_DELETE(_potal);
	}	
}

void bossDungeonScene::update()
{
	PLAYER->update();
	//Ÿ���̶� �浹ó��
	this->collisionTile();
	PLAYER->updateWeaponState();

	switch (_bsState)
	{
	case BS_INIT:
		if (!_golemKing && PLAYER->getY() < 1100)
		{
			_golemKing = new bossGolemKing;
			_golemKing->init(1067, 477);
			_bsState = BS_UPDATE;
		}
		break;
	case BS_UPDATE:
		_golemKing->update();
		//��Ż ������Ʈ
		if (_potal)
		{
			_potal->update();
			if (_potal->getPotalState() == POTAL_INIT)
				CAMERAMANAGER->ChangePivot(_potal->getX(), _potal->getY(), 20);

			if (_potal->getPotalState() == POTAL_PLAYERIN && _potal->getAnimation()->getAniState() == ANIMATION_END)
			{
				this->getInvenItem();
				_aniCenter->init(IMAGEMANAGER->findImage("potalUpdate"), 0, 5, true);
				_bsState = BS_RESULT;
				_rtKind = BOSSRESULTKIND::RT_POTAL;
				_vEnemy = PLAYERDATA->getVEnemy();
			}

			if (INPUT->GetKeyDown('J') && _potal->getIsInRange())
			{

				_potal->setPotalState(POTAL_PLAYERIN);
				_isPlayerRender = false;
			}
		}
		//���̸� ��Ż����
		if (_golemKing->getIsDead() == true && !_potal)
		{
			_potal = new potal;
			_potal->init(1024, 839, POTAL_INIT);
		}
		
		//�÷��̾� ������ ���â
		if (PLAYERDATA->getInDungeonHp() <= 0 && PLAYER->getPlayerState() != PLAYER_DIE)
		{
			PLAYER->setPlayerState(PLAYER_DIE);
		}
		else if (PLAYER->getPlayerState() == PLAYER_DIE && PLAYER->getAnimation()->getAniState() == ANIMATION_END)
		{
			this->getInvenItem();
			_aniCenter->init(IMAGEMANAGER->findImage("����"), 0, 5);
			_bsState = BS_RESULT;
			_rtKind = BOSSRESULTKIND::RT_DIE;
			_vEnemy = PLAYERDATA->getVEnemy();
			_killEnemy = PLAYERDATA->getKillEnemy();
		}
	
		break;
	case BS_RESULT:
		_aniCenter->update();
		_killEnemy->attack->update();
		PLAYERDATA->setIsActivate(false);
		if (INPUT->GetKeyDown('J'))
		{
			if (_rtKind == BOSSRESULTKIND::RT_DIE)
			{
				PLAYERDATA->setIsPendantReturn(true);
			}
			else if (_rtKind == BOSSRESULTKIND::RT_POTAL)
			{
				PLAYERDATA->setIsBossReturn(true);
			}
			PLAYERDATA->setIsInDungeon(false);
			SCENEMANAGER->loadScene("Ÿ��ȭ��");
			SOUNDMANAGER->stop("bossBGM");
		}
		break;
	default:
		break;
	}
	
	cout << CAMERAMANAGER->getRect().left << endl;

	CAMERAMANAGER->update(PLAYER->getX(), PLAYER->getY());
	CAMERAMANAGER->movePivot(PLAYER->getX(), PLAYER->getY());
	
}

void bossDungeonScene::render()
{
	CAMERAMANAGER->StretchRender(getMemDC(), IMAGEMANAGER->findImage("bossRoomBack"), 1024, 839, 2.f);
	CAMERAMANAGER->ZorderTotalRender(getMemDC());
	if(_isPlayerRender)
	PLAYER->render(getMemDC());
	switch (_bsState)
	{
	case BS_INIT:case BS_UPDATE:
		
	
		break;
	case BS_RESULT:
		IMAGEMANAGER->addImage("dark", WINSIZEX, WINSIZEY)->alphaRender(getMemDC(), 0, 0, 170);
		IMAGEMANAGER->findImage("resultBack")->render(getMemDC(), 40, 22);
		this->resultRender();
		this->itemResultRender();
		break;
	default:
		break;
	}
	if(_golemKing)
	_golemKing->render();

	if(_potal)
	_potal->render();

	POINT pt = CAMERAMANAGER->getRelativeMouse(_ptMouse);
	textOut(getMemDC(), 10, 120, to_string(pt.x).c_str(), to_string(pt.x).size());
	textOut(getMemDC(), 10, 150, to_string(pt.y).c_str(), to_string(pt.y).size());

	//Ÿ�� Ȯ�ο�
	if (INPUT->GetToggleKey(VK_F1))
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			RECT temp;
			if (!IntersectRect(&temp, &_vTile[i].rc, &CAMERAMANAGER->getRect()))continue;
			CAMERAMANAGER->FrameRect(getMemDC(), _vTile[i].rc, RGB(255, 255, 255));
			if (_vTile[i].tState == TS_MOVEBAN)
				CAMERAMANAGER->FrameRect(getMemDC(), _vTile[i].rc, RGB(255, 0, 0));
		}
	}
}

void bossDungeonScene::loadTile()
{
	_vTile = mapSaveLoad::getSingleton()->loadTile("maptool/bossDungeon", 60, 48);
}

void bossDungeonScene::collisionTile()
{
	for (int i = 0; i < _vTile.size(); i++)
	{
		RECT temp;
		if (!IntersectRect(&temp, &CAMERAMANAGER->getRect(), &_vTile[i].rc)) continue;
		if (IntersectRect(&temp, &PLAYER->getShadowRect(), &_vTile[i].rc))
		{
			if (_vTile[i].tState == TS_MOVEBAN)
			{
				int wid = temp.right - temp.left;
				int hei = temp.bottom - temp.top;
				int pwid = (PLAYER->getShadowRect().right - PLAYER->getShadowRect().left) / 2;
				int phei = (PLAYER->getShadowRect().bottom - PLAYER->getShadowRect().top) / 2;

				if (wid > hei) // ���Ʒ�
				{
					if (temp.top == PLAYER->getShadowRect().top) // �Ʒ�
					{
						PLAYER->setY(_vTile[i].rc.bottom + phei);
					}
					else  // ��
					{
						PLAYER->setY(_vTile[i].rc.top - phei);
					}
				}
				else  // �翷
				{
					if (temp.left == PLAYER->getShadowRect().left) // ������
					{
						PLAYER->setX(_vTile[i].rc.right + pwid);
					}
					else // ����
					{
						PLAYER->setX(_vTile[i].rc.left - pwid);
					}
				}

			}
		}
	}
}

void bossDungeonScene::initItemSlot()
{
	for (int i = 0; i < 28; i++)
	{
		_dungeonSlot[i].slotIdx = i;
		_dungeonSlot[i].isEmpty = true;
	}
}

void bossDungeonScene::getInvenItem()
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

void bossDungeonScene::deleteInvenItems()
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

void bossDungeonScene::itemResultRender()
{
	//IMAGEMANAGER->render("menu_shopInventory", getMemDC(), 100, 86);
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
					140 + (columnIdx * 72), 172 + 152 + 6);
				countRender(_vItem[j]->getCount(),
					180 + (columnIdx * 72), 208 + 152 + 6);
				break;

			case 7: case 8: case 9: case 10: case 11:
			case 14: case 15: case 16: case 17: case 18:
			case 21: case 22: case 23: case 24: case 25:
				_vItem[j]->getItemImg()->render(getMemDC(),
					140 + (columnIdx * 72), 258 + 152 + 6 + ((rowIdx - 1) * 72));
				countRender(_vItem[j]->getCount(),
					180 + (columnIdx * 72), 294 + 152 + 6 + ((rowIdx - 1) * 72));
				break;

			}//end of switch
		}//end of for(j)
	}//end of for(i)
}

void bossDungeonScene::countRender(int count, int destX, int destY)
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

void bossDungeonScene::resultRender()
{
	RECT txtRC = RectMake(1198, 584, 82, 20);
	HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	HFONT oFont = (HFONT)SelectObject(getMemDC(), hFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	string str = " X " + to_string(_vEnemy.size());
	DrawText(getMemDC(), str.c_str(), -1, &txtRC, DT_LEFT | DT_VCENTER);
	txtRC = RectMake(486, 21, 311, 34);
	str = "Golem King";
	DrawText(getMemDC(), str.c_str(), -1, &txtRC, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	switch (_rtKind)
	{
	case BOSSRESULTKIND::RT_DIE:
	{
		_aniCenter->centerRender(getMemDC(), 630, 170);
		_killEnemy->attack->setFrameY(_killEnemy->frameY);
		_killEnemy->attack->stretchRender(getMemDC(), 762, 240, _killEnemy->scale);
	}
	break;
	case BOSSRESULTKIND::RT_POTAL:
	{
		_aniCenter->stretchRender(getMemDC(), 640, 170, 2.f);
		int cx = 762 - IMAGEMANAGER->findImage("bag_emblem")->getWidth() / 2;
		int cy = 240 - IMAGEMANAGER->findImage("bag_emblem")->getHeight() / 2;
		IMAGEMANAGER->findImage("bag_emblem")->render(getMemDC(), cx, cy);
	}
	break;
	}

	int destY;
	if (_vEnemy.size() / 2 / 9 > 0)  destY = 70 / (_vEnemy.size() / 2 / 9);
	else destY = 70;
	for (int i = 0; i < _vEnemy.size() / 2; i++)
	{
		_vEnemy[i].attack->setFrameY(_vEnemy[i].frameY);
		_vEnemy[i].attack->stretchRender(getMemDC(), 724 + ((i % 9) * 50), 320 + (i / 9 * destY), _vEnemy[i].scale);
	}
	for (int i = _vEnemy.size() / 2, j = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i].attack->setFrameY(_vEnemy[i].frameY);
		_vEnemy[i].attack->stretchRender(getMemDC(), 724 + ((j % 9) * 50), 480 + (j / 9 * destY), _vEnemy[i].scale);
		j++;
	}

}
