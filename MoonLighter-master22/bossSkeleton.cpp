#include "stdafx.h"
#include "enemy.h"

HRESULT bossSkeleton::init(int x, int y)
{
	_move = new animation;
	_attackSword = new animation;
	_attackHammer = new animation;
	_hammerWave1 = new animation;
	_scroll = new animation;

	_move->init(IMAGEMANAGER->findImage("skeletonMove"), 0, 8, true);
	_attackSword->init(IMAGEMANAGER->findImage("skeletonAttackSword"), 0, 5);
	_attackHammer->init(IMAGEMANAGER->findImage("skeletonAttackHammer"), 0, 7);
	_hammerWave1->init(IMAGEMANAGER->findImage("hammerWave1"), 0, 7);
	_scroll->init(IMAGEMANAGER->findImage("golemScroll"), 0, 7);

	IMAGEMANAGER->addImage("pixelCollision_skeleton", WINSIZEX, WINSIZEY);

	vector<POINT> vp;

	_attackSword->aniStop();
	_attackHammer->aniStop();
	_hammerWave1->aniStop();
	_scroll->aniStop();

	_stState = ST_INIT;
	_bossPhase = ST_PHASE_1;
	_x = x;
	_y = y;

	//��Ÿ �ʱ�ȭ
	_emHp = 0;
	_emAtkHammer = 30;
	_emAtkSword = 20;
	_emAtkWave = 15;
	_waveCount = 0;
	_waveTime = 0;
	_hitCount = 0;
	_autoAttackCount = 0;
	_autoAttackCool = RANDOM->range(200, 500);
	_dieCount = 0;
	_isWaveHit = false;

	//ü�¹� �ʱ�ȭ
	_hpBarRed = new progressBar;
	_hpBarRed->init("semiBossHpBarFront(red)", "semiBossHpBarBack", 666);

	_hpBarWhite = new progressBar;
	_hpBarWhite->init("semiBossHpBarFront(white)", "semiBossHpBarBack", 666);

	_hpBar = _hpBarRed;

	//�Һ��� �ʱ�ȭ
	_isHit = false;
	_isAttackRange = false;
	_isActivate = true;
	_isItemDrop = false;
	_emPlayerColi = false;

	//���ʹ� ���ݹڽ� �ʱ�ȭ
	_swordAtkBox.isHit = false;
	_hammerAtkBox.isHit = false;

	//���̵� �ʱ�ȭ
	_blade = new tagBlade;
	_blade->ani = new animation;
	_blade->ani->init(IMAGEMANAGER->findImage("skeletonBlade"), 0, 5);
	_blade->ani->aniStop();
	_blade->x = 0;
	_blade->y = 0;
	_blade->angle = 0;
	_blade->isFire = false;
	_blade->isBreak = false;
	_blade->atk = 10;


	// ���� ���� �Լ� �ʱ�ȭ
	_isAttackPlay = false;

	//������ �ʱ�ȭ
	_isItemDrop = true;
	_itemIndexSize = 11;
	_itemDropSize = RANDOM->range(3 , 10);
	_itemIndex = new int[_itemIndexSize];
	_itemNum = new int[_itemDropSize];

	//���ü� �ִ� �������ε��� �ʱ�ȭ
	for (int i = 0; i < 10; i++)
	{
		_itemIndex[i] = i + 1;
	}

	// ����� �������� �ε����� �������� ����
	for (int i = 0; i < _itemDropSize; i++)
	{
		_itemNum[i] = _itemIndex[RANDOM->range(_itemIndexSize)];
	}


	CAMERAMANAGER->FadeInit(50, FADE_IN);
	CAMERAMANAGER->FadeStart();
	return S_OK;
}

void bossSkeleton::release()
{
	
}

void bossSkeleton::update()
{
	_scroll->update();			//��ũ�� ������Ʈ
	if (_emHp < 333)
	{
		_bossPhase = ST_PHASE_2;
	}
	if (_emHp <= 0 && _stState != ST_INIT)
	{
		_stState = ST_DIE;
	}

	this->soundUpdate();				//���� ����


	this->atkBoxUpdate();				//���ݷ�Ʈ ������Ʈ
	this->collision();					//�÷��̾�� �浹
	this->hitToPlayer();				//�÷��̾� �����ϱ�
	this->attackUpdate();				//���ݿ� ���� ������Ʈ

	//��Ʈ ����
	this->hitUpdate();

	switch (_stState)
	{
	case bossSkeleton::ST_MOVE:
		_move->update();				// �ִϸ��̼� ����

		this->setStartNode();			// ���̽�Ÿ ���ۼ���
		this->aStar();					// ���̽�Ÿ
		this->enemyMove();				// ������
		this->atkRangeUpdate();			// ���ݹ��� ����
		this->moveUpdate();				// �÷��̾�� �浹�˻��ؼ� ����	
		break;
	case bossSkeleton::ST_INIT:
		_emHp += 10;
		if (_emHp >= 666)
		{
			_emHp = 666;
			_stState = ST_MOVE;
			_bossPhase = ST_PHASE_1;
			_scroll->aniPlay();
		}
		break;
	case bossSkeleton::ST_DIE:
		_dieCount++;
		_attackHammer->changeImg(IMAGEMANAGER->findImage("skeletonAttackHammerHitWhite"));
		_attackSword->changeImg(IMAGEMANAGER->findImage("skeletonAttackSwordHitWhite"));
		_move->changeImg(IMAGEMANAGER->findImage("skeletonMoveHitWhite"));
		if (_dieCount > 80)
		{
			_isActivate = false;
			_isItemDrop = false;
		}

		break;
	default:
		break;
	}

	// ����� �ִϸ��̼� ����
	_hammerWave1->update();
	//ü�¹� ����
	_hpBarRed->update(_emHp);
	_hpBarWhite->update(_emHp);
}

void bossSkeleton::render()
{
	this->animationRender();
	if (_scroll->getAniState() == ANIMATION_PLAY) _scroll->ZorderStretchRender(WINSIZEY, WINSIZEX / 2, WINSIZEY - 150, 2.f);
	RECT txtRC = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 70, 300, 40);
	HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	
	CAMERAMANAGER->ZorderDrawText("Dual Weapon Skeleton", WINSIZEY / 2, txtRC, hFont, RGB(255, 255, 255), DT_CENTER | DT_WORDBREAK | DT_VCENTER);

	//IMAGEMANAGER->addImage("pixelCollision_skeleton", WINSIZEX, WINSIZEY);
	//_blade->ani->ZorderRotateAlphaRender(getMemDC(), 2000, _blade->x, _blade->y, _blade->angle, 150);
	
	_hpBar->cameraRender(WINSIZEX / 2, WINSIZEY - 50);
}

void bossSkeleton::setStartNode()
{
	POINT pt = { _x,_y };
	for (int x = 0; x < _idx; x++)
	{
		for (int y = 0; y < _idy; y++)
		{
			if (PtInRect(&_totalNode[y][x].rc, pt))
			{
				_startNode = &_totalNode[y][x];
			}
		}
	}
}

void bossSkeleton::enemyMove()
{
	if (_finalList.size() > 0)
	{
		float angle = getAngle(_x, _y, _finalList.front()->centerX, _finalList.front()->centerY);
		_x += cosf(angle) * 0.5f;
		_y -= sinf(angle) * 0.5f;

		angle = getAngle(_x, _y, (_endNode->rc.left + _endNode->rc.right) / 2, (_endNode->rc.top + _endNode->rc.bottom) / 2);
		if (angle > DEGREE(45) && angle <= DEGREE(135))
		{
			_emDirection = EM_TOP;
		}
		if (angle > DEGREE(135) && angle <= DEGREE(225))
		{
			_emDirection = EM_LEFT;
		}
		if (angle > DEGREE(225) && angle <= DEGREE(315))
		{
			_emDirection = EM_BOTTOM;
		}
		if (angle > DEGREE(315) || angle <= DEGREE(45))
		{
			_emDirection = EM_RIGHT;
		}
	}

	_emRC = RectMakeCenter(_x, _y - 50, 130, 160);
	_aStarRC = RectMakeCenter(_x, _y, 35, 35);
}

void bossSkeleton::animationRender()
{
	//���ʹ� �ִϸ��̼� y�� ����� ����� ����
	switch (_emDirection)
	{
	case EM_LEFT:
		_move->setFrameY(1);
		_attackHammer->setFrameY(2);
		_attackSword->setFrameY(3);

		if (_hammerWave1->getAniState() != ANIMATION_END) _hammerWave1->ZoderRender(0, _x - IMAGEMANAGER->findImage("hammerWave1")->getFrameWidth() / 2 - 166, _y - IMAGEMANAGER->findImage("hammerWave1")->getFrameHeight() / 2 + 30);
		break;
	case EM_RIGHT:
		_move->setFrameY(2);
		_attackHammer->setFrameY(1);
		_attackSword->setFrameY(0);

		if (_hammerWave1->getAniState() != ANIMATION_END) _hammerWave1->ZoderRender(0, _x - IMAGEMANAGER->findImage("hammerWave1")->getFrameWidth() / 2 + 166, _y - IMAGEMANAGER->findImage("hammerWave1")->getFrameHeight() / 2 + 30);
		break;
	case EM_TOP:
		_move->setFrameY(3);
		_attackHammer->setFrameY(0);
		_attackSword->setFrameY(1);

		if (_hammerWave1->getAniState() != ANIMATION_END) _hammerWave1->ZoderRender(0, _x - IMAGEMANAGER->findImage("hammerWave1")->getFrameWidth() / 2 - 8, _y - IMAGEMANAGER->findImage("hammerWave1")->getFrameHeight() / 2 - 149);
		break;
	case EM_BOTTOM:
		_move->setFrameY(0);
		_attackHammer->setFrameY(3);
		_attackSword->setFrameY(2);

		if (_hammerWave1->getAniState() != ANIMATION_END) _hammerWave1->ZoderRender(0, _x - IMAGEMANAGER->findImage("hammerWave1")->getFrameWidth() / 2 + 13, _y - IMAGEMANAGER->findImage("hammerWave1")->getFrameHeight() / 2 + 140);
		break;

	}
	//���̵� ����
	if (_blade->ani->getAniState() != ANIMATION_END)
	{
		_blade->ani->ZorderRotateRender(getMemDC(), 2000, _blade->x, _blade->y, _blade->angle);
	}

	int wid = IMAGEMANAGER->findImage("skeletonMove")->getFrameWidth() / 2 * 3;
	int hei = IMAGEMANAGER->findImage("skeletonMove")->getFrameHeight() / 2 * 3;

	//����, �����ӿ� ���� �ִϸ��̼� ����
	switch (_stState)
	{
	case bossSkeleton::ST_ATTACK_HAMMER:
	case bossSkeleton::ST_SKILL_HAMMER:
	case bossSkeleton::ST_WAVE:
		if (_attackHammer->getAniState() != ANIMATION_END)
		{
			if (_attackHammer->getCurIndex() >= 6 && _attackHammer->getCurIndex() < 17)
				_attackHammer->ZorderStretchRender(PLAYER->getY() + 1, _x , _y ,3.f);
			else
				_attackHammer->ZorderStretchRender(_y, _x , _y , 3.f);
		}
		break;
	case bossSkeleton::ST_ATTACK_SWORD:
	case bossSkeleton::ST_SKILL_SWORD:

		if (_attackSword->getAniState() != ANIMATION_END)
		{
			if (_attackSword->getCurIndex() >= 7 && _attackSword->getCurIndex() <= 15)
				_attackSword->ZorderStretchRender(PLAYER->getY() + 1, _x , _y , 3.f);
			else
				_attackSword->ZorderStretchRender(_y, _x , _y , 3.f);
		}
		break;
	case bossSkeleton::ST_MOVE:
		_move->ZorderStretchRender(_y, _x , _y , 3.f);
		break;
	case bossSkeleton::ST_INIT:
		_move->ZorderStretchRender(_y, _x , _y , 3.f);
		break;
	case bossSkeleton::ST_DIE:
		if (_attackSword->getAniState() != ANIMATION_END) _attackSword->ZorderStretchRender(_y, _x, _y, 3.f);
		else if (_attackHammer->getAniState() != ANIMATION_END) _attackHammer->ZorderStretchRender(_y, _x, _y, 3.f);
		else _move->ZorderStretchRender(_y, _x, _y, 3.f);
		break;
	default:
		break;
	}
}

void bossSkeleton::atkRangeUpdate()
{
	switch (_emDirection)
	{
	case EM_LEFT:
		_hammerRange = RectMake(_emRC.left - 140, _y, _x - (_emRC.left - 140), 60);
		_swordRange = RectMake(_emRC.left - 140, _emRC.top + 50, 140, 220);
		break;
	case EM_RIGHT:
		_hammerRange = RectMake(_x, _y, (_emRC.right + 140) - _x, 60);
		_swordRange = RectMake(_emRC.right, _emRC.top + 50, 140, 220);
		break;
	case EM_TOP:
		_hammerRange = RectMake(_emRC.left + 10, _emRC.top + 20, 90, _y - _emRC.top + 20);
		_swordRange = RectMake(_emRC.left - 20, _emRC.top, 150, _y - _emRC.top);
		break;
	case EM_BOTTOM:
		_hammerRange = RectMake(_x - 35, _y, 100, 200);
		_swordRange = RectMake(_emRC.left, _y, 150, 150);
		break;
	}
}

void bossSkeleton::atkBoxUpdate()
{
	switch (_emDirection)
	{
	case EM_LEFT:
		// �ظ� ���ݿ� ��Ʈ 
		if (_attackHammer->getCurIndex() >= 6 && _attackHammer->getCurIndex() <= 13)
		{
			_hammerAtkBox.box = RectMake(_hammerRange.left + 10, _hammerRange.top + 10, _x - _hammerRange.left + 10, 50);
		}
		else _hammerAtkBox = { 0,0,0,0 };
		// Į ���ݿ� ��Ʈ
		if (_attackSword->getCurIndex() >= 7 && _attackSword->getCurIndex() <= 13)
		{
			_swordAtkBox.box = { _swordRange.left, _swordRange.top + 30, _swordRange.right, _swordRange.bottom };
		}
		else _swordAtkBox.box = { 0,0,0,0 };
		break;
	case EM_RIGHT:
		if (_attackHammer->getCurIndex() >= 6 && _attackHammer->getCurIndex() <= 13)
		{
			_hammerAtkBox.box = RectMake(_x, _hammerRange.top + 10, _hammerRange.right - _x - 10, 50);
		}
		else _hammerAtkBox = { 0,0,0,0 };
		// Į ���ݿ� ��Ʈ
		if (_attackSword->getCurIndex() >= 7 && _attackSword->getCurIndex() <= 13)
		{
			_swordAtkBox.box = { _swordRange.left, _swordRange.top + 30, _swordRange.right, _swordRange.bottom };
		}
		else _swordAtkBox.box = { 0,0,0,0 };
		break;
	case EM_TOP:
		if (_attackHammer->getCurIndex() >= 6 && _attackHammer->getCurIndex() <= 13)
		{
			_hammerAtkBox.box = RectMake(_hammerRange.left + 10, _hammerRange.top + 5, 80, _y - _hammerRange.top + 5);
		}
		else _hammerAtkBox = { 0,0,0,0 };
		// Į ���ݿ� ��Ʈ
		if (_attackSword->getCurIndex() >= 7 && _attackSword->getCurIndex() <= 13)
		{
			_swordAtkBox.box = { _swordRange.left + 10, _swordRange.top + 20, _swordRange.right, _swordRange.bottom };
		}
		else _swordAtkBox.box = { 0,0,0,0 };
		break;
	case EM_BOTTOM:
		if (_attackHammer->getCurIndex() >= 6 && _attackHammer->getCurIndex() <= 13)
		{
			_hammerAtkBox.box = RectMake(_x - 35, _y, 95, 180);
		}
		else _hammerAtkBox = { 0,0,0,0 };
		// Į ���ݿ� ��Ʈ
		if (_attackSword->getCurIndex() >= 7 && _attackSword->getCurIndex() <= 13)
		{
			_swordAtkBox.box = { _swordRange.left, _swordRange.top, _swordRange.right, _swordRange.bottom - 30 };
		}
		else _swordAtkBox.box = { 0,0,0,0 };
		break;
	}
}

void bossSkeleton::moveUpdate()
{
	_autoAttackCount++;
	if (_autoAttackCount > _autoAttackCool)
	{
		_autoAttackCool = RANDOM->range(200, 500);
		_autoAttackCount = 0;

		if (_attackSword->getAniState() == ANIMATION_END)
		{
			_attackSword->aniRestart();
			_stState = ST_SKILL_SWORD;
		}
	}
	RECT temp;
	if (_bossPhase == ST_PHASE_1)
	{
		if (IntersectRect(&temp, &PLAYER->getRect(), &_hammerRange) && IntersectRect(&temp, &PLAYER->getRect(), &_swordRange))
		{

			if (RANDOM->range(2) == 0)
			{

				if (_attackSword->getAniState() == ANIMATION_END)
				{
					_attackSword->aniRestart();
					_stState = ST_ATTACK_SWORD;
				}
			}
			else
			{
				if (_attackHammer->getAniState() == ANIMATION_END)
				{
					_attackHammer->aniRestart();
					_stState = ST_ATTACK_HAMMER;
				}
			}
		}
		else if (IntersectRect(&temp, &PLAYER->getRect(), &_hammerRange))
		{
			if (_attackHammer->getAniState() == ANIMATION_END)
			{
				_attackHammer->aniRestart();
				_stState = ST_ATTACK_HAMMER;
			}
		}
		else if (IntersectRect(&temp, &PLAYER->getRect(), &_swordRange))
		{
			if (_attackSword->getAniState() == ANIMATION_END)
			{
				_attackSword->aniRestart();
				_stState = ST_ATTACK_SWORD;
			}
		}
	}
	else
	{
		if (IntersectRect(&temp, &PLAYER->getRect(), &_hammerRange) && IntersectRect(&temp, &PLAYER->getRect(), &_swordRange))
		{
			if (_attackHammer->getAniState() == ANIMATION_END)
			{
				_attackHammer->aniRestart();
				_stState = ST_SKILL_HAMMER;
			}
		}
		else if (IntersectRect(&temp, &PLAYER->getRect(), &_hammerRange))
		{
			if (_attackHammer->getAniState() == ANIMATION_END)
			{
				_attackHammer->aniRestart();
				_stState = ST_SKILL_HAMMER;
			}
		}
		else if (IntersectRect(&temp, &PLAYER->getRect(), &_swordRange))
		{
			if (_attackSword->getAniState() == ANIMATION_END)
			{
				_attackSword->aniRestart();
				_stState = ST_SKILL_SWORD;
			}
		}
	}



}

void bossSkeleton::attackUpdate()
{
	//���̵� ����
	this->bladeUpdate();

	switch (_stState)
	{
	case bossSkeleton::ST_ATTACK_SWORD:
		_attackSword->update();
		if (_attackSword->getAniState() == ANIMATION_END)
		{
			_isAttackPlay = false;
			_attackSword->aniStop();
			_stState = ST_MOVE;
		}
		break;
	case bossSkeleton::ST_ATTACK_HAMMER:
		_attackHammer->update();
		// ��ġ�� ���� ������� ����� �ִϸ��̼� ����
		if (_attackHammer->getCurIndex() == 6 && _hammerWave1->getAniState() == ANIMATION_END)
		{
			_hammerWave1->aniRestart();
			CAMERAMANAGER->setShake(10, 10, 1);
		}
		if (_attackHammer->getAniState() == ANIMATION_END)
		{
			_isAttackPlay = false;				//���� ��� �ʱ�ȭ
			_attackHammer->aniStop();
			_stState = ST_MOVE;
		}
		break;
	case bossSkeleton::ST_SKILL_SWORD:
		_attackSword->update();

		if (_attackSword->getCurIndex() == 7 && _blade->isFire == false)
		{
			_blade->angle = getAngle(_x, _y, PLAYER->getX(), PLAYER->getY());
			_blade->x = _x + cosf(_blade->angle) * 150;
			_blade->y = _y - sinf(_blade->angle) * 150;
			_blade->isFire = true;
			_blade->ani->aniRestart();
		}
		if (_attackSword->getAniState() == ANIMATION_END)
		{
			_stState = ST_MOVE;
			_isAttackPlay = false;
		}

		break;
	case bossSkeleton::ST_SKILL_HAMMER:
		_attackHammer->update();
		if (_attackHammer->getCurIndex() == 12)
		{
			_attackHammer->aniPause();
			_hammerWave1->aniRestart();
			_stState = ST_WAVE;
			_isAttackPlay = false;
			CAMERAMANAGER->setShake(10, 10, 1);
		}
		break;
	case bossSkeleton::ST_WAVE:
		_attackHammer->update();
		if (_hammerWave1->getAniState() == ANIMATION_END)
		{
			if (_waveCount < 4)
			{
				if (_attackHammer->getAniState() != ANIMATION_PLAY)
				{
					if (_attackHammer->getAniState() != ANIMATION_REVERSE)
					{
						_attackHammer->aniReverse();
					}

					if (_attackHammer->getCurIndex() == 9 && _attackHammer->getAniState() == ANIMATION_REVERSE)
					{
						_attackHammer->aniPlay();
					}
				}
				if (_attackHammer->getAniState() == ANIMATION_PLAY && _attackHammer->getCurIndex() == 12)
				{
					SOUNDMANAGER->play("skeletonWave");
					_attackHammer->aniPause();
					_hammerWave1->aniRestart();
					_waveCount++;
					CAMERAMANAGER->setShake(10, 10, 1);
				}

			}
			else
			{
				_attackHammer->aniPlay();
			}
		}
		if (_attackHammer->getCurIndex() == _attackHammer->getImage()->getMaxFrameX())
		{
			_isAttackPlay = false;
			_stState = ST_MOVE;
			_waveCount = 0;
			_attackHammer->aniStop();
		}
		break;
	case bossSkeleton::ST_MOVE:

		break;
	default:
		break;
	}

	//���̵� �ȼ��浹
	if (_blade->isFire && !_blade->isBreak)
	{
		IMAGEMANAGER->findImage("skeletonBlade")->rotateFrameRender(IMAGEMANAGER->findImage("pixelCollision_skeleton")->getMemDC(), _blade->x, _blade->y, _blade->angle, _blade->ani->getCurIndex(), 0);
		IMAGEMANAGER->findImage("pixelCollision_skeleton")->render(getMemDC(), 0, 0);
		COLORREF co = GetPixel(IMAGEMANAGER->findImage("pixelCollision_skeleton")->getMemDC(), PLAYER->getX(), PLAYER->getY());
		int r = GetRValue(co);
		int g = GetGValue(co);
		int b = GetBValue(co);
		if (r != 0 && g != 0 && b != 0)
		{
			_blade->ani->aniPlay();
			_blade->isBreak = true;
			if (PLAYER->getPlayerState() == PLAYER_SHILED)
			{
				PLAYER->playerPush();
			}
			else
			{
				PLAYERDATA->minusInDungeonHp(_blade->atk);
			}
		}
		BitBlt(IMAGEMANAGER->findImage("pixelCollision_skeleton")->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, getMemDC(), 0, 0, BLACKNESS);
	}

	if (PLAYERDATA->getInDungeonHp() <= 0)
	{
		RESULTENEMY* em = new RESULTENEMY;
		em->attack = new animation;
		em->attack->init(_attackHammer->getImage(), 0, 7, true);
		em->frameY = 3;
		em->scale = 3.f;
		PLAYERDATA->setKillEnemy(em);
		PLAYERDATA->setInDungeonHp(0);
		PLAYER->setPlayerState(PLAYER_DIE);
	}
}

void bossSkeleton::soundUpdate()
{
	switch (_stState)
	{
	case bossSkeleton::ST_ATTACK_SWORD:
		if (_attackSword->getCurIndex() == 3 && _isAttackPlay == false)
		{
			_isAttackPlay = true;
			SOUNDMANAGER->play("skullAttackSword", 0.2f);
		}
		break;
	case bossSkeleton::ST_ATTACK_HAMMER:
		if (_attackHammer->getCurIndex() == 3 && _isAttackPlay == false)
		{
			_isAttackPlay = true;
			SOUNDMANAGER->play("skullAttackHammer", 0.2f);
		}
		break;
	case bossSkeleton::ST_SKILL_SWORD:
		if (_attackSword->getCurIndex() == 3 && _isAttackPlay == false)
		{
			_isAttackPlay = true;
			SOUNDMANAGER->play("skullAttackSword", 0.2f);
		}
		break;
	case bossSkeleton::ST_SKILL_HAMMER:
		if (_attackHammer->getCurIndex() == 11 && _isAttackPlay == false)
		{
			_isAttackPlay = true;
			SOUNDMANAGER->play("skeletonWave");
		}
		break;
	case bossSkeleton::ST_MOVE:

		break;
	default:
		break;
	}
}

void bossSkeleton::bladeUpdate()
{
	if (_blade->isFire == false) return;
	_blade->ani->update();
	//�μ����� �ʾ����� ������
	if (_blade->isBreak == false)
	{
		_blade->x += cosf(_blade->angle) * 6.f;
		_blade->y -= sinf(_blade->angle) * 6.f;
	}


	//���ư��� ���߿� Į����� ����
	if (_blade->isBreak == false && _blade->ani->getCurIndex() == 2)
	{
		_blade->ani->aniPause();
	}

	//���� ���� �������� ��Ʈ
	RECT dunRC = RectMake(140, 105, 35 * _idx, 35 * _idy);
	POINT pt = { _blade->x,_blade->y };
	if (!PtInRect(&dunRC, pt))
	{
		_blade->ani->aniPlay();
		_blade->isBreak = true;
	}

	if (_blade->ani->getCurIndex() == _blade->ani->getImage()->getMaxFrameX())
	{
		_blade->isFire = false;
		_blade->isBreak = false;
		_blade->ani->aniStop();
	}

}

void bossSkeleton::hitUpdate()
{
	if (!_isHit) return;
	_hitCount++;

	if (_hitCount < 5)
	{
		_hpBar = _hpBarWhite;
		_attackHammer->changeImg(IMAGEMANAGER->findImage("skeletonAttackHammerHitRed"));
		_attackSword->changeImg(IMAGEMANAGER->findImage("skeletonAttackSwordHitRed"));
		_move->changeImg(IMAGEMANAGER->findImage("skeletonMoveHitRed"));
	}
	else if (_hitCount < 10)
	{
		_hpBar = _hpBarRed;
		_attackHammer->changeImg(IMAGEMANAGER->findImage("skeletonAttackHammerHitWhite"));
		_attackSword->changeImg(IMAGEMANAGER->findImage("skeletonAttackSwordHitWhite"));
		_move->changeImg(IMAGEMANAGER->findImage("skeletonMoveHitWhite"));
	}


	if (_hitCount > 10)
	{
		_hitCount = 0;
		_hpBar = _hpBarRed;
		_isHit = false;
		_attackHammer->changeImg(IMAGEMANAGER->findImage("skeletonAttackHammer"));
		_attackSword->changeImg(IMAGEMANAGER->findImage("skeletonAttackSword"));
		_move->changeImg(IMAGEMANAGER->findImage("skeletonMove"));
	}

}

void bossSkeleton::hitToPlayer()
{
	RECT temp;

	if (PLAYER->getPlayerState() != PLAYER_ROLL)
	{
		switch (_stState)
		{
		case bossSkeleton::ST_ATTACK_SWORD: case bossSkeleton::ST_SKILL_SWORD:
			if (IntersectRect(&temp, &PLAYER->getRect(), &_swordAtkBox.box) && _swordAtkBox.isHit == false)
			{
				bossColi(_emAtkSword, _swordAtkBox);
			}
			if (_attackSword->getCurIndex() == _attackSword->getImage()->getMaxFrameX()) _swordAtkBox.isHit = false;
			break;

		case bossSkeleton::ST_ATTACK_HAMMER: case bossSkeleton::ST_SKILL_HAMMER:
			if (IntersectRect(&temp, &PLAYER->getRect(), &_hammerAtkBox.box) && _hammerAtkBox.isHit == false)
			{
				bossColi(_emAtkHammer, _hammerAtkBox);
			}
			if (_attackHammer->getCurIndex() == _attackHammer->getImage()->getMaxFrameX()) _hammerAtkBox.isHit = false;
			break;

		case bossSkeleton::ST_WAVE:
			RECT _waveRC;
			float pDist;
			float cx = (PLAYER->getRect().left + PLAYER->getRect().right) / 2;
			float cy = (PLAYER->getRect().top + PLAYER->getRect().bottom) / 2;
			switch (_emDirection)
			{
			case EM_LEFT:
				_waveRC = RectMakeCenter(_x - 166, _y + 30, 180, 180);
				if (IntersectRect(&temp, &PLAYER->getRect(), &_waveRC) && _isWaveHit == false && _hammerWave1->getAniState() == ANIMATION_PLAY)
				{
					pDist = getDistance(cx, cy, PLAYER->getRect().left, PLAYER->getRect().right);
					if (getDistance(_x - 166, _y + 30, cx, cy) < 180 + pDist)
					{
						this->coliWaveAtk(_emAtkWave);
					}
				}
				break;
			case EM_RIGHT:
				_waveRC = RectMakeCenter(_x + 166, _y + 30, 180, 180);
				if (IntersectRect(&temp, &PLAYER->getRect(), &_waveRC) && _isWaveHit == false && _hammerWave1->getAniState() == ANIMATION_PLAY)
				{
					pDist = getDistance(cx, cy, PLAYER->getRect().left, PLAYER->getRect().right);
					if (getDistance(_x + 166, _y + 30, cx, cy) < 180 + pDist)
					{
						this->coliWaveAtk(_emAtkWave);
					}
				}
				break;
			case EM_TOP:
				_waveRC = RectMakeCenter(_x - 8, _y - 149, 180, 180);
				if (IntersectRect(&temp, &PLAYER->getRect(), &_waveRC) && _isWaveHit == false && _hammerWave1->getAniState() == ANIMATION_PLAY)
				{
					pDist = getDistance(cx, cy, PLAYER->getRect().left, PLAYER->getRect().right);
					if (getDistance(_x - 8, _y - 149, cx, cy) < 180 + pDist)
					{
						this->coliWaveAtk(_emAtkWave);
					}
				}
				break;
			case EM_BOTTOM:
				_waveRC = RectMakeCenter(_x + 13, _y + 140, 180, 180);
				if (IntersectRect(&temp, &PLAYER->getRect(), &_waveRC) && _isWaveHit == false && _hammerWave1->getAniState() == ANIMATION_PLAY)
				{
					pDist = getDistance(cx, cy, PLAYER->getRect().left, PLAYER->getRect().right);
					if (getDistance(_x + 13, _y + 140, cx, cy) < 180 + pDist)
					{
						this->coliWaveAtk(_emAtkWave);
					}
				}
				break;
			}
			if (_hammerWave1->getAniState() == ANIMATION_END)
			{
				_isWaveHit = false;
			}
			break;
		}
	}

	if (PLAYERDATA->getInDungeonHp() <= 0)
	{
		RESULTENEMY* em = new RESULTENEMY;
		em->attack = new animation;
		em->attack->init(_attackHammer->getImage(), 0, 7, true);
		em->frameY = 3;
		em->scale = 3.f;
		PLAYERDATA->setKillEnemy(em);
	}
	
}

void bossSkeleton::hitSoundPlay()
{
	switch (RANDOM->range(3))
	{
	case 0:
		SOUNDMANAGER->play("skullHit", 0.3f);
		break;
	case 1:
		SOUNDMANAGER->play("skullHit2", 0.3f);
		break;
	case 2:
		SOUNDMANAGER->play("skullHit2", 0.3f);
		break;
	}
}

void bossSkeleton::bossColi(int bossTypeDemage, tagAtkBox &bossTypeRect)
{
	if (PLAYER->getPlayerState() == PLAYER_SHILED && checkDirection())
	{
		PLAYER->playerPush();
	}
	else
	{
		bossTypeRect.isHit = true;
		PLAYERDATA->minusInDungeonHp(bossTypeDemage);
		PLAYER->setPlayerState(HIT_IDLE);
		PLAYER->setHit(true);
		DAMAGEFONT->init(PLAYER->getX(), PLAYER->getY(), bossTypeDemage);
	}
}

void bossSkeleton::coliWaveAtk(int waveDamage)
{
	if (PLAYER->getPlayerState() == PLAYER_SHILED)
	{
		PLAYER->playerPush();
	}
	else
	{
		PLAYERDATA->minusInDungeonHp(waveDamage);
		PLAYER->setPlayerState(HIT_IDLE);
		PLAYER->setHit(true);
		_isWaveHit = true;
	}
}

animation * bossSkeleton::getAttackAnimation()
{
	_attackHammer->changeImg(IMAGEMANAGER->findImage("skeletonAttackHammer"));
	return _attackHammer;
}

int bossSkeleton::getDownDirectionY()
{
	return 3;
}

