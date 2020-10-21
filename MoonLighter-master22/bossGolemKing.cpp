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
	/*_aniBossFistShoot = new animation;
	_aniBossFistShoot->init(IMAGEMANAGER->findImage("bossFistShoot"), 0, 7, false);*/
	_aniBossHandShootStart = new animation;
	_aniBossHandShootStart->init(IMAGEMANAGER->findImage("bossHandShootStart"), 0, 7, false);
	_aniBossHandShootEnd = new animation;
	_aniBossHandShootEnd->init(IMAGEMANAGER->findImage("bossHandShootEnd"), 0, 7, false);
	_aniIdle = new animation;
	_aniIdle->init(IMAGEMANAGER->findImage("bossIdle"), 0, 50, true);
	_scroll = new animation;
	_scroll->init(IMAGEMANAGER->findImage("golemScroll"), 0, 9);

	_aniBossFistShoot1 = new animation;
	_aniBossFistShoot2 = new animation;
	_aniBossFistShoot3 = new animation;
	vector<POINT> pt;

	for (int i = 0; i < 17; i++)
	{
		pt.push_back(PointMake(i, 0));
	}
	_aniBossFistShoot1->initArray(pt, IMAGEMANAGER->findImage("bossFistShoot"), 7);
	pt.clear();
	for (int i = 0; i < 22; i++)
	{
		pt.push_back(PointMake(i, 1));
	}
	_aniBossFistShoot2->initArray(pt, IMAGEMANAGER->findImage("bossFistShoot"), 7);
	pt.clear();
	for (int i = 0; i < 16; i++)
	{
		pt.push_back(PointMake(i, 2));
	}
	_aniBossFistShoot3->initArray(pt, IMAGEMANAGER->findImage("bossFistShoot"), 7);

	//���Ϳ� ���
	_vAni.push_back(_aniBossUp);					
	_vAni.push_back(_aniBossDead1);					
	_vAni.push_back(_aniBossDead2);					
	_vAni.push_back(_aniBossFistShoot1);				
	_vAni.push_back(_aniBossFistShoot2);				
	_vAni.push_back(_aniBossFistShoot3);				
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
	_attackCool = RANDOM->range(150,300);


	_golemState = GOLEMKINGSTATE::BS_INIT;
	_golemAni = GOLEMANISTATE::ANI_BOSSUP;

	//���� xy ��ǥ
	_x = x;
	_y = y;
	_bossRC = RectMakeCenter(_x - 10, _y + 85, 250, 150);
	_hitCount = 0;

	//������ ī��Ʈ �ʱ�ȭ
	_rockFireTime = 0;
	_rockFireCount = 0;

	_golemHand.ani = nullptr;

	_isAttackSoundPlay = false;
	_isDeadSoundPlay = false;
	_isDead = false;
	_isHit = false;
	_coliSkillAroow = false;

	return S_OK;
}

void bossGolemKing::release()
{
}

void bossGolemKing::update()
{
	if (INPUT->GetKeyDown(VK_DOWN))
	{
		PLAYERDATA->setInDungeonHp(PLAYERDATA->getInDungeonHp() - 10);
	}
	//��ũ�� ����
	_scroll->update();
	//���¿����� �ִϸ��̼� ������Ʈ
	_vAni[(int)_golemAni]->update();
	//ü�¹� ������Ʈ
	_hpRed->update(_hp);
	_hpWhite->update(_hp);
	//ü�� 0�Ǹ� �׿�!
	if (_hp <= 0 && _golemState != GOLEMKINGSTATE::BS_INIT && _golemState != GOLEMKINGSTATE::BS_DEAD)
	{
		this->changeAniState(GOLEMANISTATE::ANI_DEAD1);
		_golemState = GOLEMKINGSTATE::BS_DEAD;
	}
	//�浹ó��
	this->collisionPlayer();
	this->hitUpdate();

	//���¿����� ������Ʈ
	switch (_golemState)
	{
	case GOLEMKINGSTATE::BS_INIT:
		_hp += 5;
		if (_hp > 1000)
		{
			_hp = 1000;
			_golemState = GOLEMKINGSTATE::BS_IDLE;
			CAMERAMANAGER->ChangePivot(PLAYER->getX(), PLAYER->getY(), 20);
		}
		else
		CAMERAMANAGER->ChangePivot(_x, _y, 10);
		if ((CAMERAMANAGER->getPivotX() == _x || CAMERAMANAGER->getPivotY() == _y) && !CAMERAMANAGER->getIsShake())
		{
			//���� ���
			if (!SOUNDMANAGER->isPlaySound("bossInit"))
				SOUNDMANAGER->play("bossInit", 1.f);
			CAMERAMANAGER->setShake(5, 30, 2);
		}
		break;
	case GOLEMKINGSTATE::BS_IDLE:
		_attackCool--;

		//������Ÿ���� ������ ����~
		if (_attackCool <= 0)
		{
			this->initAttack();
		}

		break;
	case  GOLEMKINGSTATE::BS_FIST:
		this->bsFistUpdate();
		break;
	case GOLEMKINGSTATE::BS_ROCK_SHOOT:
		this->bsRockShootUpdate();
		break;
	case GOLEMKINGSTATE::BS_ROCK_ROUND:
		this->bsRockRoundUpdate();
	
		break;
	case GOLEMKINGSTATE::BS_HAND:
		this->bsHandUpdate();
		break;
	case GOLEMKINGSTATE::BS_DEAD:
		if (!_isDeadSoundPlay)
		{
			SOUNDMANAGER->play("bossDead");
			_isDeadSoundPlay = true;
		}
		if (_vAni[(int)_golemAni]->getAniState() == ANIMATION_END)
		{
			if (_golemAni == GOLEMANISTATE::ANI_DEAD1)
			{
				this->changeAniState(GOLEMANISTATE::ANI_DEAD2);
			}
			if (_golemAni == GOLEMANISTATE::ANI_DEAD2)
			{
				_isDead = true;
			}
		}
		break;
	}

	//�����̵� ������Ʈ
	this->vRockUpdate();
	this->collisionRock();

}

void bossGolemKing::render()
{
	if(_golemAni == GOLEMANISTATE::ANI_DEAD2)
		_vAni[(int)_golemAni]->ZorderStretchRender(_y, _x, _y + 78, 3.f);
	else
	_vAni[(int)_golemAni]->ZorderStretchRender(_y, _x, _y, 3.f);
	//��ũ�� ����
	if(_scroll->getAniState() == ANIMATION_PLAY)
	_scroll->stretchRender(getMemDC(), WINSIZEX / 2, WINSIZEY - 150, 2.f);
	//ü�¹� ����
	if (!_isDead)
	{
		_hpBar->render(WINSIZEX / 2, WINSIZEY - 50);
		//�̸� ����
		RECT txtRC = RectMakeCenter((CAMERAMANAGER->getRect().right + CAMERAMANAGER->getRect().left) / 2
			, CAMERAMANAGER->getRect().bottom - 70, 300, 40);
		HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
		CAMERAMANAGER->ZorderDrawText("�� �� ��", 2000, txtRC, hFont, RGB(255, 255, 255), DT_CENTER | DT_WORDBREAK | DT_VCENTER);
	}
	CAMERAMANAGER->FrameRect(getMemDC(), _bossRC, RGB(255, 0, 0));

	switch (_golemState)
	{
	case GOLEMKINGSTATE::BS_INIT:
		break;
	case GOLEMKINGSTATE::BS_IDLE:
		break;
	case GOLEMKINGSTATE::BS_FIST:
		if(_golemAni != GOLEMANISTATE::ANI_FISTSHOOT1)
		_bossFist.ani->ZorderRotateStretchRender(1999, _bossFist.x, _bossFist.y, _bossFist.angle, 1.5f);
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
		CAMERAMANAGER->FrameRect(getMemDC(), _vRock[i].colRC, RGB(255, 0, 0));
	}

	textOut(getMemDC(), 10, 200, to_string((int)_golemState).c_str(), to_string((int)_golemState).size());
}

void bossGolemKing::changeAniState(GOLEMANISTATE state)
{
	_golemAni = state;
	_vAni[(int)_golemAni]->aniRestart();
}

void bossGolemKing::initAttack()
{
	if (_vGolemAttack.size() == 0)
		this->initVGolemAttack();


	switch (_vGolemAttack.back())
	{
	case GOLEMKINGSTATE::BS_FIST:
		//�ָ��� �ʱ�ȭ
		_bossFist.ani = new animation;
		_bossFist.ani->initReverse(IMAGEMANAGER->findImage("bossFist"), 0, 7, false, true);
		_bossFist.angle = RANDOM->range(DEGREE(240), DEGREE(300)) + DEGREE(90);
		_bossFist.x = _x - 70;
		_bossFist.y = _y + 30;
		_bossFist.count = RANDOM->range(4, 7);
		_bossFist.isMoveLeft = (bool)RANDOM->range(2);
		_bossFist.isHit = false;
		this->changeAniState(GOLEMANISTATE::ANI_FISTSHOOT1);
		break;
	case GOLEMKINGSTATE::BS_HAND:
		//�� �ʱ�Ȳ
		this->initGolemHand();
		this->changeAniState(GOLEMANISTATE::ANI_HANDSHOOTSTART);
		break;
	case GOLEMKINGSTATE::BS_ROCK_ROUND:
		if (_vRock.size() > 0) _vRock.clear();
		if (!_isAttackSoundPlay)
		{
			SOUNDMANAGER->play("bossRock");
			_isAttackSoundPlay = true;
		}
		else if (SOUNDMANAGER->isPlaySound("bossRock")) return;
		break;
	case GOLEMKINGSTATE::BS_ROCK_SHOOT:
		if (_vRock.size() > 0) _vRock.clear();
		if (!_isAttackSoundPlay)
		{
			SOUNDMANAGER->play("bossRock");
			_isAttackSoundPlay = true;
		}
		else if (SOUNDMANAGER->isPlaySound("bossRock")) return;
		
		//���� �ʱ�Ȳ
		_rockShootAngle[0] = RANDOM->range(DEGREE(240), DEGREE(300));
		_rockShootAngle[1] = _rockShootAngle[0] + DEGREE(5);
		_rockShootAngle[2] = _rockShootAngle[0] + DEGREE(10);

		break;
	}

	_attackCool = RANDOM->range(150, 300);
	_golemState = _vGolemAttack.back();
	_isAttackSoundPlay = false;

	//������� ����
	_vGolemAttack.pop_back();
}

void bossGolemKing::collisionPlayer()
{
	int damage = RANDOM->range(PLAYERDATA->getAtk() - 2, PLAYERDATA->getAtk() + 2);
	RECT temp;
	if (IntersectRect(&temp, &PLAYER->getPlayerAttackBox().rc, &_bossRC))
	{
		if (PLAYER->getPlayerAttackBox().isHit == false && _golemState != GOLEMKINGSTATE::BS_DEAD)
		{
			EFFECTMANAGER->addEffect("��������Ʈ", 2000,
				(_bossRC.right + _bossRC.left) / 2,
				(_bossRC.bottom + _bossRC.top) / 2, PLAYER->getPlayerDirection(), 10);
			DAMAGEFONT->init(_x, _y - 30, damage);
			_hp -= damage;
			_isHit = true;
			PLAYER->setPlayerAttackBoxHit(true);
		}
	}

	if (IntersectRect(&temp, &PLAYER->getPlayerAttackTwoBox().rc, &_bossRC))
	{
		if (PLAYER->getPlayerAttackTwoBox().isHit == false && _golemState != GOLEMKINGSTATE::BS_DEAD)
		{
			EFFECTMANAGER->addEffect("��������Ʈ", 2000,
				(_bossRC.right + _bossRC.left) / 2,
				(_bossRC.bottom + _bossRC.top) / 2, PLAYER->getPlayerDirection(), 10);
			DAMAGEFONT->init(_x, _y - 30, damage);
			_hp -= damage;
			_isHit = true;
			PLAYER->setPlayerAttackTwoBoxHit(true);
		}
	}

	if (IntersectRect(&temp, &PLAYER->getArrow()->getRect(), &_bossRC) && PLAYER->getArrow()->getIsShoot())
	{
		if (!_coliSkillAroow)
		{
			_coliSkillAroow = true;
			EFFECTMANAGER->addEffect("ȭ������Ʈ", (_bossRC.bottom + _bossRC.top) / 2 + 3,
				(_bossRC.right + _bossRC.left) / 2,
				(_bossRC.bottom + _bossRC.top) / 2, PLAYER->getPlayerDirection(), 10);
			DAMAGEFONT->init(_x, _y - 30, damage);

			if (PLAYER->getSkill())
			{
				_hp -= 10 + damage;
				_isHit = true;
			}
			else
			{
				_hp -= damage;
				_isHit = true;
				PLAYER->getArrow()->setIsShoot(false);
			}
		}
	}
	else
	{
		_coliSkillAroow = false;
	}
}

void bossGolemKing::hitUpdate()
{
	if (!_isHit) return;

	_hitCount++;

	if (_hitCount < 10)
	{
		_hpBar = _hpWhite;
	}
	if (_hitCount < 20)
	{
		_hpBar = _hpRed;
	}
	if (_hitCount > 20)
	{
		_hitCount = 0;
		_isHit = false;
		_hpBar = _hpRed;
	}


}

void bossGolemKing::initVGolemAttack()
{
	_vGolemAttack.push_back(GOLEMKINGSTATE::BS_FIST);
	_vGolemAttack.push_back(GOLEMKINGSTATE::BS_HAND);
	switch (RANDOM->range(2))
	{
	case 0:
		_vGolemAttack.push_back(GOLEMKINGSTATE::BS_ROCK_ROUND);
		break;
	case 1:
		_vGolemAttack.push_back(GOLEMKINGSTATE::BS_ROCK_SHOOT);
		break;
	}
	this->suffleVGolemAttack();
}

void bossGolemKing::suffleVGolemAttack()
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
	if(!_golemHand.ani)
	_golemHand.ani = new animation;
	_golemHand.ani->init(IMAGEMANAGER->findImage("bossHand"), 0, 7, false);
	_golemHand.shadowScale = 0.2f;
	_golemHand.x = PLAYER->getX();
	_golemHand.y = PLAYER->getY() + 25;
	_golemHand.rc = RectMakeCenter(_golemHand.x, _golemHand.hight + 20, 100, 50);
	_golemHand.hight = CAMERAMANAGER->getRect().top - 200;
	_golemHand.count = 200;
	_golemHand.atkCount = 0;
	_golemHand.state = HANDSTATE::HAND_INIT;
	_golemHand.isHit = false;
	_golemHand.speed = 15;
}

void bossGolemKing::bsFistUpdate()
{
	
	if (_vAni[(int)_golemAni]->getAniState() == ANIMATION_END && _golemAni == GOLEMANISTATE::ANI_FISTSHOOT1)
	{
		this->changeAniState(GOLEMANISTATE::ANI_FISTSHOOT2);
	}
	if (_golemAni == GOLEMANISTATE::ANI_FISTSHOOT2)
	{
		_bossFist.ani->update();
		//���� ���� �ִϸ��̼� ����
		if (_bossFist.ani->getCurIndex() == _bossFist.ani->getAniList().size() / 2)
		{
			_bossFist.ani->aniPause();
		}
		//�� ����
		if (_bossFist.ani->getAniState() == ANIMATION_PAUSE)
		{
			if (_bossFist.isMoveLeft)
			{
				_bossFist.angle -= DEGREE(1);
				if (_bossFist.angle <= DEGREE(270))
				{
					_bossFist.isMoveLeft = false;
					_bossFist.isHit = false;
					_bossFist.count--;
				}
			}
			else if (!_bossFist.isMoveLeft)
			{
				_bossFist.angle += DEGREE(1);
				if (_bossFist.angle > DEGREE(360 + 90))
				{
					_bossFist.isMoveLeft = true;
					_bossFist.isHit = false;
					_bossFist.count--;
				}
			}
		}
		//���ݳ������� ���� �ִϸ��̼�����
		if (_bossFist.count <= 0)
		{
			this->changeAniState(GOLEMANISTATE::ANI_FISTSHOOT3);
		}
	}
	//�÷��̾�� �浹ó��
	if (_golemAni == GOLEMANISTATE::ANI_FISTSHOOT2)
	{
		//�÷��׾� �����浹
		float bx = _bossFist.x - 20;
		float by = _bossFist.y;
		float x = bx + cosf(_bossFist.angle - DEGREE(90)) * 555;
		float y = by - sinf(_bossFist.angle - DEGREE(90)) * 555;
		float sDist = getDistance(bx, by, PLAYER->getX(), PLAYER->getY());
		float eDist = getDistance(x, y, PLAYER->getX(), PLAYER->getY());
		float tDist = getDistance(bx, by, x, y);
		if (sDist + eDist <= tDist + 5.f && sDist + eDist >= tDist - 10.f && _bossFist.isHit == false && PLAYER->getPlayerState() != PLAYER_ROLL)
		{
			//����� ����� �浹ó������ �ȴ�
			DAMAGEFONT->init(PLAYER->getX(), PLAYER->getY(), FISTDAMAGE);
			_bossFist.isHit = true;
			PLAYERDATA->setInDungeonHp(PLAYERDATA->getInDungeonHp() - FISTDAMAGE);
			PLAYER->setPlayerState(HIT_IDLE);
			PLAYER->setHit(true);

			if (PLAYERDATA->getInDungeonHp() <= 0)
			{
				RESULTENEMY* em = new RESULTENEMY;
				em->attack = new animation;
				em->attack->init(_bossFist.ani->getImage(), 0, 7, true);
				em->frameY = 0;
				em->scale = 0.5f;
				PLAYERDATA->setKillEnemy(em);
			}
		}
	}
	//���̵� ���·� �ٲٱ�
	if (_golemAni == GOLEMANISTATE::ANI_FISTSHOOT3)
	{
		//�����ִ��� ���
		_bossFist.ani->update();
		if (_bossFist.ani->getAniState() == ANIMATION_PAUSE)
		{
			_bossFist.ani->aniPlay();
		}

		if (_bossFist.ani->getAniState() == ANIMATION_END)
		{
			_golemAni = GOLEMANISTATE::ANI_IDLE;
			_golemState = GOLEMKINGSTATE::BS_IDLE;
		}
	}
	
}

void bossGolemKing::bsRockShootUpdate()
{
	_rockFireTime++;

	//�߻�ð��� �Ǹ� �߻��ض�
	if (_rockFireTime % 20 == 0)
	{
		tagRock rock[3];
		for (int i = 0; i < 3; i++)
		{
			string str = "bossRock" + to_string(RANDOM->range(4));
			rock[i].img = IMAGEMANAGER->findImage(str);
			rock[i].x = _x + cosf(_rockShootAngle[i]) * (100 + _rockFireTime * 5);
			rock[i].y = _y - sinf(_rockShootAngle[i]) * (100 + _rockFireTime * 5);
			rock[i].hight = -100;
			rock[i].time = 0;
			rock[i].shadowScale = 0.5f;
			rock[i].isHit = false;
			_vRock.push_back(rock[i]);
		}
		_rockFireCount++;
	}
	if (_rockFireCount > 8)
	{
		_rockFireCount = 0;
		_rockFireTime = 0;
		_golemState = GOLEMKINGSTATE::BS_IDLE;
	}
}

void bossGolemKing::bsRockRoundUpdate()
{
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
			_rock.x = _x - 50 + cosf(angle * i + PI) * (100 + _rockFireTime * 3);
			_rock.y = _y - sinf(angle * i + PI) * (100 + _rockFireTime * 3);
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
}

void bossGolemKing::bsHandUpdate()
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
			DAMAGEFONT->init(PLAYER->getX(), PLAYER->getY(), HANDDAMAGE);
			PLAYERDATA->setInDungeonHp(PLAYERDATA->getInDungeonHp() - HANDDAMAGE);
			PLAYER->setPlayerState(HIT_IDLE);
			PLAYER->setHit(true);
			_golemHand.isHit = true;

			if (PLAYERDATA->getInDungeonHp() <= 0)
			{
				RESULTENEMY* em = new RESULTENEMY;
				em->attack = new animation;
				em->attack->init(_golemHand.ani->getImage(), 0, 7, true);
				em->frameY = 0;
				em->scale = 3.f;
				PLAYERDATA->setKillEnemy(em);
			}
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
			if (_golemHand.ani->getCurIndex() < 15)
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
			if (_golemHand.atkCount < 3)
			{
				_golemHand.state = HANDSTATE::HAND_INIT;
				_golemHand.count = 200;
				_golemHand.atkCount++;
				_golemHand.ani->aniRestart();
				_golemHand.ani->aniStop();
			}
			else if(_golemHand.atkCount == 3)
			{
				if(_golemAni != GOLEMANISTATE::ANI_HANDSHOOTEND)
				this->changeAniState(GOLEMANISTATE::ANI_HANDSHOOTEND);
				if (_vAni[(int)_golemAni]->getAniState() == ANIMATION_END)
				{
					_golemAni = GOLEMANISTATE::ANI_IDLE;
					_golemState = GOLEMKINGSTATE::BS_IDLE;
				}
			}
			
		}
		//�׸��� ũ�� ���̱�
		_golemHand.shadowScale -= 0.04f;
		if (_golemHand.shadowScale < 0.2f) _golemHand.shadowScale = 0.2f;
		_golemHand.rc = { 0,0,0,0 };
		break;
	}
}

void bossGolemKing::vRockUpdate()
{
	//������ ������ �������� ������Ʈ
	for (int i = 0; i < _vRock.size();)
	{
		_vRock[i].hight += 10;
		if (_vRock[i].hight >= _vRock[i].y)
		{
			//�浹�뷺Ʈ����
			_vRock[i].colRC = RectMakeCenter(_vRock[i].x, _vRock[i].y + 10, 60, 60);
			_vRock[i].hight = _vRock[i].y;
			//�ٴ� �����ϸ� Ÿ�̸� ����
			_vRock[i].time++;
			if (_vRock[i].time < 30)
			{
				_vRock[i].rc = RectMakeCenter(_vRock[i].x, _vRock[i].y + 10, 60, 60);
			}
			else _vRock[i].rc = { 0,0,0,0 };
		}

		RECT temp;
		if (IntersectRect(&temp, &PLAYER->getRect(), &_vRock[i].rc) && !_vRock[i].isHit && PLAYER->getPlayerState() != PLAYER_ROLL)
		{
			DAMAGEFONT->init(PLAYER->getX(), PLAYER->getY(), ROCKDAMAGE);
			PLAYERDATA->setInDungeonHp(PLAYERDATA->getInDungeonHp() - ROCKDAMAGE);
			PLAYER->setPlayerState(HIT_IDLE);
			PLAYER->setHit(true);
			_vRock[i].isHit = true;
			if (PLAYERDATA->getInDungeonHp() <= 0)
			{
				RESULTENEMY* em = new RESULTENEMY;
				em->attack = new animation;
				em->attack->init(_vRock[i].img, 0, 7, true);
				em->frameY = 0;
				em->scale = 1.f;
				PLAYERDATA->setKillEnemy(em);
			}
		}

		if (_vRock[i].time > 600)
		{
			_vRock.erase(_vRock.begin() + i);
		}
		else i++;
	}
}

void bossGolemKing::collisionRock()
{
	for (int i = 0; i < _vRock.size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_vRock[i].colRC, &PLAYER->getShadowRect()))
		{
			int wid = temp.right - temp.left;
			int hei = temp.bottom - temp.top;
			int pWid = (PLAYER->getShadowRect().right - PLAYER->getShadowRect().left) / 2;
			int phei = (PLAYER->getShadowRect().bottom - PLAYER->getShadowRect().top) / 2;

			if (wid > hei) // ���Ʒ�
			{
				if (temp.top == PLAYER->getShadowRect().top) // �Ʒ�
				{
					PLAYER->setY(_vRock[i].colRC.bottom + phei);
				}
				else  // ��
				{
					PLAYER->setY(_vRock[i].colRC.top - phei);
				}
			}
			else  // �翷
			{
				if (temp.left == PLAYER->getShadowRect().left) // ������
				{
					PLAYER->setX(_vRock[i].colRC.right + pWid);
				}
				else // ����
				{
					PLAYER->setX(_vRock[i].colRC.left - phei);
				}
			}
			
		}
	}
}
