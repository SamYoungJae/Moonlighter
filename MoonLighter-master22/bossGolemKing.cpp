#include "stdafx.h"
#include "bossGolemKing.h"

HRESULT bossGolemKing::init(int x, int y)
{
	//�ִϸ��̼� �ʱ�ȭ
	_aniBossUp = new animation;
	_aniBossUp->init(IMAGEMANAGER->findImage("bossUp"), 0, 7, false);
	_aniBossDead1 = new animation;
	_aniBossDead1->init(IMAGEMANAGER->findImage("bossDead1"), 0, 7, false);
	_aniBossDead2 = new animation;
	_aniBossDead2->init(IMAGEMANAGER->findImage("bossDead2"), 0, 7, false);
	_aniBossFistShoot = new animation;
	_aniBossFistShoot->init(IMAGEMANAGER->findImage("bossFistShoot"), 0, 7, false);
	_aniBossHandShootStart = new animation;
	_aniBossHandShootStart->init(IMAGEMANAGER->findImage("bossHandShootStart"), 0, 7, false);
	_aniBossHandShootEnd = new animation;
	_aniBossHandShootEnd->init(IMAGEMANAGER->findImage("bossHandShootEnd"), 0, 7, false);
	_aniIdle = new animation;
	_aniIdle->init(IMAGEMANAGER->findImage("bossIdle"), 0, 50, true);
	_scroll = new animation;
	_scroll->init(IMAGEMANAGER->findImage("golemScroll"), 0, 9);

	//���Ϳ� ���
	_vAni.push_back(_aniBossUp);					
	_vAni.push_back(_aniBossDead1);					
	_vAni.push_back(_aniBossDead2);					
	_vAni.push_back(_aniBossFistShoot);				
	_vAni.push_back(_aniBossHandShootStart);		
	_vAni.push_back(_aniBossHandShootEnd);
	_vAni.push_back(_aniIdle);

	//ü�¹�
	_hpRed = new progressBar;
	_hpRed->init("semiBossHpBarFront(red)", "semiBossHpBarBack", 1000);
	_hpWhite = new progressBar;
	_hpWhite->init("semiBossHpBarFront(white)", "semiBossHpBarBack", 1000);
	_hpBar = _hpRed;


	_hp = 0;
	//_attackCool = RANDOM->range(300,500);
	_attackCool = 200;

	_golemState = GOLEMKINGSTATE::BS_INIT;
	_golemAni = GOLEMANISTATE::ANI_BOSSUP;

	//���� xy ��ǥ
	_x = x;
	_y = y;

	//������ ī��Ʈ �ʱ�ȭ
	_rockFireTime = 0;
	_rockFireCount = 0;


	return S_OK;
}

void bossGolemKing::release()
{
}

void bossGolemKing::update()
{
	//��ũ�� ����
	_scroll->update();
	//���¿����� �ִϸ��̼� ������Ʈ
	_vAni[(int)_golemAni]->update();
	//ü�¹� ������Ʈ
	_hpRed->update(_hp);
	_hpWhite->update(_hp);

	//���¿����� ������Ʈ
	switch (_golemState)
	{
	case GOLEMKINGSTATE::BS_INIT:
		_hp += 5;
		if (_hp > 1000)
		{
			_hp = 1000;
			_golemState = GOLEMKINGSTATE::BS_IDLE;
		}
		CAMERAMANAGER->ChangePivot(_x, _y, 10);
		CAMERAMANAGER->setShake(10, 10, 1);
		break;
	case GOLEMKINGSTATE::BS_IDLE:
		_attackCool--;

		//�������ϵ��� ������ ä�����
		if (_vGolemAttack.size() == 0)
			this->initGolemAttack();

		//������Ÿ���� ������ ����~
		if (_attackCool <= 0)
		{
			_attackCool = RANDOM->range(300, 500);
			_golemState = GOLEMKINGSTATE::BS_ROCK_ROUND;
			this->initGolemHand();
		}

		break;
	case  GOLEMKINGSTATE::BS_FIST:
		break;
	case GOLEMKINGSTATE::BS_ROCK_SHOOT:

		break;
	case GOLEMKINGSTATE::BS_ROCK_ROUND:
		//������ �߻��Ѱ��� �����Ѵٸ� ġ�ƶ�
		_rockFireTime++;
		
		if (_rockFireTime % 100 == 0)
		{
			int j = RANDOM->range(11);
			for (int i = 0; i <= 10; i++)
			{
				if (i == j) continue;
				float angle = PI / 10;
				string str = "bossRock" + to_string(RANDOM->range(4));
				tagRock _rock;
				_rock.img = IMAGEMANAGER->findImage(str);
				_rock.x = _x - 50 + cosf(angle * i + PI) * (100+_rockFireTime * 3);
				_rock.y = _y - sinf(angle * i + PI) * (100+_rockFireTime * 3);
				_rock.hight = -100;
				_rock.time = 0;
				_rock.shadowScale = 0.5f;
				_rock.isHit = false;
				_vRock.push_back(_rock);
			}
			//����Ƚ�� ++
			_rockFireCount++;
		}
		if (_rockFireCount >= 2)
		{
			_rockFireCount = 0;
			_rockFireTime = 0;
			_golemState = GOLEMKINGSTATE::BS_IDLE;
		}
		break;
	case GOLEMKINGSTATE::BS_HAND:
	{
		//���� �����Ҷ� �ѹ��� �ʱ�ȭ���ְ�
		if (_golemAni != GOLEMANISTATE::ANI_HANDSHOOTSTART && _golemAni != GOLEMANISTATE::ANI_HANDSHOOTEND)
		{
			_golemAni = GOLEMANISTATE::ANI_HANDSHOOTSTART;
			_vAni[(int)_golemAni]->aniRestart();
		}
		//�ִϸ��̼� ����
		_golemHand.ani->update();
		//�÷��̾�� �浹ó��		����������
		RECT temp;
		if (IntersectRect(&temp, &PLAYER->getRect(), &_golemHand.rc) && !_golemHand.isHit && PLAYER->getPlayerState() != PLAYER_ROLL)
		{

			if (PLAYER->getPlayerState() == PLAYER_SHILED)
			{
				PLAYER->playerPush();
			}
			else
			{
				PLAYERDATA->setInDungeonHp(PLAYERDATA->getInDungeonHp() - 10);
				PLAYER->setPlayerState(HIT_IDLE);
				PLAYER->setHit(true);
				_golemHand.isHit = true;
			}
		}

		switch (_golemHand.state)
		{
		case HANDSTATE::HAND_INIT:
		{
			//�׻� ī�޶�ۿ��־��
			_golemHand.hight = CAMERAMANAGER->getRect().top - 200;

			//�÷��̾� ��ġ�� ���󰡰����ش�
			float dist = getDistance(_golemHand.x, _golemHand.y, PLAYER->getX(), PLAYER->getY() + 25);
			float angle = getAngle(_golemHand.x, _golemHand.y, PLAYER->getX(), PLAYER->getY() + 25);
			if (dist > 0.5f)
			{
				_golemHand.x += cosf(angle) * 1.5f;
				_golemHand.y -= sinf(angle) * 1.5f;
			}
			//�����ð� ������ ������
			_golemHand.count--;
			if (_golemHand.count <= 0)
			{
				_golemHand.count = 0;
				_golemHand.state = HANDSTATE::HAND_FALL;
			}

			if (_golemHand.ani->getCurIndex() == 1)
				_golemHand.ani->aniPause();
		}
			break;
		case HANDSTATE::HAND_FALL:
			//�׸��� ũ��Ű���
			_golemHand.shadowScale += 0.04f;
			if (_golemHand.shadowScale > 1.f) _golemHand.shadowScale = 1.f;

			//�� ���ο÷�
			_golemHand.hight += _golemHand.speed;
			if (_golemHand.hight >= _golemHand.y - 35)
			{
				//��ġ����
				_golemHand.hight = _golemHand.y - 35;
				//�ִϸ��̼� ���
				if(_golemHand.ani->getCurIndex() < 15)
				_golemHand.ani->aniPlay();
				else _golemHand.ani->aniPause();				
				//��ġ�� ���������� �����ð��ִ� �÷�����
				_golemHand.count++;
				if (_golemHand.count > 140)
				{
					_golemHand.count = 0;
					_golemHand.state = HANDSTATE::HAND_UP;
				}
				//�浹�� ��Ʈ ��� ������
				if (_golemHand.count < 30)
					_golemHand.rc = RectMakeCenter(_golemHand.x, _golemHand.hight + 20, 100, 50);
				else _golemHand.rc = { 0,0,0,0 };
			}
			break;
		case HANDSTATE::HAND_UP:
			//�� ���οø���
			_golemHand.hight -= _golemHand.speed;
			//�ִϸ��̼� ���
			_golemHand.ani->aniPlay();
			//ī�޶� ������ �������� ���º���
			if (_golemHand.hight < CAMERAMANAGER->getRect().top - 200)
			{
				_golemAni = GOLEMANISTATE::ANI_HANDSHOOTEND;
				if (_vAni[(int)_golemAni]->getAniState() == ANIMATION_END)
				{
					_golemAni = GOLEMANISTATE::ANI_IDLE;
					_golemState = GOLEMKINGSTATE::BS_IDLE;
				}
			}
			//�׸��� ũ�� ���̱�
			_golemHand.shadowScale -= 0.04f;
			if (_golemHand.shadowScale < 0.2f) _golemHand.shadowScale = 0.2f;
			_golemHand.rc = { 0,0,0,0 };
			break;
		default:
			break;
		}


	}
		break;

	}

	//������ ������ �������� ������Ʈ
	for (int i = 0; i < _vRock.size();)
	{
		_vRock[i].hight += 10;
		if (_vRock[i].hight >= _vRock[i].y)
		{
			_vRock[i].hight = _vRock[i].y;
			//�ٴ� �����ϸ� Ÿ�̸� ����
			_vRock[i].time++;
			if (_vRock[i].time < 30)
			{

				_vRock[i].rc = RectMakeCenter(_vRock[i].x, _vRock[i].y + 10, 60 , 60);
			}
			else _vRock[i].rc = { 0,0,0,0 };
		}

		RECT temp;
		if (IntersectRect(&temp, &PLAYER->getRect(), &_vRock[i].rc) && !_vRock[i].isHit)
		{
			PLAYERDATA->setInDungeonHp(PLAYERDATA->getInDungeonHp() - 10);
			PLAYER->setPlayerState(HIT_IDLE);
			PLAYER->setHit(true);
			_vRock[i].isHit = true;
		}

		if (_vRock[i].time > 600)
		{
			_vRock.erase(_vRock.begin() + i);
		}
		else i++;
	}


}

void bossGolemKing::render()
{
	_vAni[(int)_golemAni]->ZorderStretchRender(_y, _x, _y, 3.f);
	CAMERAMANAGER->Rectangle(getMemDC(), RectMakeCenter(_x, _y, 10, 10));
	//��ũ�� ����
	if(_scroll->getAniState() == ANIMATION_PLAY)
	_scroll->stretchRender(getMemDC(), WINSIZEX / 2, WINSIZEY - 150, 2.f);
	//ü�¹� ����
	_hpBar->render(WINSIZEX / 2, WINSIZEY - 50);
	//�̸� ����
	RECT txtRC = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 70, 300, 40);
	HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	CAMERAMANAGER->ZorderDrawText("�� �� ��", 2000, txtRC, hFont, RGB(255, 255, 255), DT_CENTER | DT_WORDBREAK | DT_VCENTER);


	switch (_golemState)
	{
	case GOLEMKINGSTATE::BS_INIT:
		break;
	case GOLEMKINGSTATE::BS_IDLE:
		break;
	case GOLEMKINGSTATE::BS_FIST:
		break;
	case GOLEMKINGSTATE::BS_ROCK_SHOOT:
		break;
	case GOLEMKINGSTATE::BS_ROCK_ROUND:
		break;
	case GOLEMKINGSTATE::BS_HAND:
		CAMERAMANAGER->ZorderStretchRender(IMAGEMANAGER->findImage("�׸���"), 0, _golemHand.x, _golemHand.y, _golemHand.shadowScale);
		_golemHand.ani->ZorderStretchRender(_golemHand.y, _golemHand.x, _golemHand.hight,3.f);
		CAMERAMANAGER->FrameRect(getMemDC(), _golemHand.rc, RGB(255, 0, 0));
		break;
	}

	//������ ����
	for (int i = 0; i < _vRock.size(); i++)
	{
		CAMERAMANAGER->ZorderStretchRender(IMAGEMANAGER->findImage("�׸���"), 0, _vRock[i].x, _vRock[i].y, _vRock[i].shadowScale);
		int cx = _vRock[i].x - _vRock[i].img->getWidth() / 2;
		int cy = _vRock[i].hight - _vRock[i].img->getHeight() / 2;
		CAMERAMANAGER->ZorderRender(_vRock[i].img, _vRock[i].y, cx, cy);
		CAMERAMANAGER->FrameRect(getMemDC(), _vRock[i].rc, RGB(255, 0, 0));
	}

	textOut(getMemDC(), 10, 200, to_string((int)_golemState).c_str(), to_string((int)_golemState).size());
}

void bossGolemKing::bossAtkUpdate()
{
}

void bossGolemKing::initGolemAttack()
{
	for (int i = 2; i < 6; i++)
	{
		_vGolemAttack.push_back((GOLEMKINGSTATE)i);
	}
}

void bossGolemKing::suffleGolemAttack()
{
	for (int i = 0; i < 100; i++)
	{
		int a = RANDOM->range((int)_vGolemAttack.size());
		int b = RANDOM->range((int)_vGolemAttack.size());
		swap(_vGolemAttack[a], _vGolemAttack[b]);
	}
}

void bossGolemKing::initGolemHand()
{
	_golemHand.ani = new animation;
	_golemHand.ani->init(IMAGEMANAGER->findImage("bossHand"), 0, 7, false);
	_golemHand.shadowScale = 0.2f;
	_golemHand.x = PLAYER->getX();
	_golemHand.y = PLAYER->getY() + 25;
	_golemHand.rc = RectMakeCenter(_golemHand.x, _golemHand.hight + 20, 100, 50);
	_golemHand.hight = CAMERAMANAGER->getRect().top - 200;
	_golemHand.count = 200;
	_golemHand.state = HANDSTATE::HAND_INIT;
	_golemHand.isHit = false;
	_golemHand.speed = 10;
}