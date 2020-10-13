#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	IMAGEMANAGER->addFrameImage("����������", "Images/�÷��̾�/player_roll_dungeon8X4.bmp", 960, 480, 8, 4);
	IMAGEMANAGER->addFrameImage("�����޸���", "Images/�÷��̾�/player_run_dungeon8X4.bmp", 960, 480, 8, 4);
	IMAGEMANAGER->addFrameImage("����idle", "Images/�÷��̾�/player_idle_dungeon10X4.bmp", 1200, 480, 10, 4);

	IMAGEMANAGER->addFrameImage("������", "Images/�÷��̾�/shop_roll.bmp", 960, 480, 8, 4);
	IMAGEMANAGER->addFrameImage("�޸���", "Images/�÷��̾�/shop_run8x4.bmp", 960, 480, 8, 4);
	IMAGEMANAGER->addFrameImage("idle", "Images/�÷��̾�/shop_idle10x4.bmp", 1200, 480, 10, 4);

	IMAGEMANAGER->addFrameImage("����", "Images/�÷��̾�/player_die10X1.bmp", 1200, 120, 10, 1);
	IMAGEMANAGER->addFrameImage("���ۺ���", "Images/�÷��̾�/hole_fall3X1.bmp", 360, 120, 3, 1);

	IMAGEMANAGER->addFrameImage("Ȱ������", "Images/�÷��̾�/bow_attack9X4.bmp", 1080, 480, 9, 4);
	IMAGEMANAGER->addFrameImage("Ȱ��ų", "Images/�÷��̾�/bow_skill2X4.bmp", 240, 480, 2, 4);


	IMAGEMANAGER->addFrameImage("���ҵ�", "Images/�÷��̾�/short_attack6X4.bmp", 720, 480, 6, 4);
	IMAGEMANAGER->addFrameImage("���ҵ�2����", "Images/�÷��̾�/short_attack_two5X4.bmp", 600, 480, 5, 4);
	IMAGEMANAGER->addFrameImage("����", "Images/�÷��̾�/player_shild.bmp", 120, 480, 1, 4);

	IMAGEMANAGER->addImage("�׸���", "Images/�÷��̾�/player_Shadow.bmp", 70, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��õ", "Images/�÷��̾�/swimState10X4.bmp", 500, 208, 10, 4);

	IMAGEMANAGER->addFrameImage("�����޸���HIT", "Images/�÷��̾�/player_run_dungeon_Hit8X4.bmp", 960, 480, 8, 4);
	IMAGEMANAGER->addFrameImage("����idleHIT", "Images/�÷��̾�/player_idle_dungeon_Hit10X4.bmp", 1200, 480, 10, 4);

	_aniTownIdle = new ::animation;
	_aniTownRun = new ::animation;
	_aniTownRoll = new ::animation;
	_aniDgIdle = new ::animation;
	_aniDgRun = new ::animation;
	_aniDgRoll = new ::animation;
	_aniFall = new ::animation;
	_aniSword = new ::animation;
	_aniSwordTwo = new ::animation;
	_aniBow = new ::animation;
	_aniDie = new ::animation;
	_aniSwim = new ::animation;

	_aniTownIdle->init(IMAGEMANAGER->findImage("idle"), 0, 7, true);
	_aniTownRun->init(IMAGEMANAGER->findImage("�޸���"), 0, 5, true);
	_aniTownRoll->init(IMAGEMANAGER->findImage("������"), 0, 7);
	_aniTownRoll->aniStop();
	_aniDgIdle->init(IMAGEMANAGER->findImage("����idle"), 0, 7, true);
	_aniDgRun->init(IMAGEMANAGER->findImage("�����޸���"), 0, 5, true);
	_aniDgRoll->init(IMAGEMANAGER->findImage("����������"), 0, 5);
	_aniDgRoll->aniStop();
	_aniFall->init(IMAGEMANAGER->findImage("���ۺ���"), 0, 7);
	_aniFall->aniStop();
	_aniSword->init(IMAGEMANAGER->findImage("���ҵ�"), 0, 5);
	_aniSword->aniStop();
	_aniSwordTwo->init(IMAGEMANAGER->findImage("���ҵ�2����"), 0, 5);
	_aniSwordTwo->aniStop();
	_aniBow->init(IMAGEMANAGER->findImage("Ȱ������"), 0, 5);
	_aniBow->aniStop();
	_aniDie->init(IMAGEMANAGER->findImage("����"), 0, 7);
	_aniDie->aniStop();
	_aniSwim->init(IMAGEMANAGER->findImage("��õ"), 0, 7);

	_player.x = 200;
	_player.y = 200;

	_player.shadowRc = RectMakeCenter(_player.x, _player.y, 35, 35);
	_player.rc = RectMakeCenter(_player.x, _player.y, 45, 60);

	_player.direction = 0;
	_player.weapon = SHORT_SOWRD;
	_player.index = 0;
	_player.count = 0;

	_playerAttackBox.rc = RectMakeCenter(10, 10, 10, 10);
	_playerAttackBox.isHit = false;
	_playerAttackTwoBox.rc = RectMakeCenter(10, 10, 10, 10);
	_playerAttackTwoBox.isHit = false;

	_holeAlpha = 255;

	_place = TOWN_DUNGEON;
	_state = PLAYER_STATE::PLAYER_IDLE;

	_right = false;
	_left = false;
	_up = false;
	_down = false;
	_isShoot = false;
	_isTalk = false;

	_rollCount = 0;
	_rollIndex = 0;
	_rollJumpPower = 0;
	_rollGravity = 0;

	_attackCount = 0;
	_attackIndex = 0;;

	_arrow = new arrow;
	_arrow->init();

	return S_OK;
}

void player::release()
{
	_arrow->release();
}

void player::update( )
{
	
	this->playerState();
	this->animation(_player.direction);
	this->attackRCUpdate();
	_player.shadowRc = RectMakeCenter(_player.x , _player.y, 35, 35);
	_player.rc = RectMakeCenter(_player.x, _player.y - 12, 45, 60);
	_arrow->update();
	this->keyInput();
	this->updateWeaponState();
}

void player::render(HDC hdc)
{
	//char str[100];
	//wsprintf(str, "weapon : %d", _player.weapon);
	//TextOut(hdc, 10, 90, str, strlen(str));
	POINT pt = CAMERAMANAGER->getRelativeMouse(PointMake(CAMERAMANAGER->getDistanceX(), CAMERAMANAGER->getDistanceY()));

	//IMAGEMANAGER->alphaRender("�׸���", hdc, CAMERAMANAGER->getDistanceX() - 35, CAMERAMANAGER->getDistanceY() - 10 , 100);
	if(_state != PLAYER_SWIM) CAMERAMANAGER->ZorderAlphaRender(IMAGEMANAGER->findImage("�׸���"), _player.y - 1, pt.x - 35, pt.y - 10, 100);
	if (_isShoot)
	{
		_arrow->render(hdc);
	}
	switch (_place)
	{
	case SHOP:
		switch (_state)
		{
		case PLAYER_IDLE:
			//IMAGEMANAGER->frameRender("idle", hdc, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68);
			//CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("idle"),_player.y ,CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, _player.index,IMAGEMANAGER->findImage("idle")->getFrameY());
			_aniTownIdle->ZoderRender(_player.y, pt.x - 60, pt.y - 68);
		break;
		case PLAYER_RUN:
			//IMAGEMANAGER->frameRender("�޸���", hdc, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68);
			//CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("�޸���"),_player.y, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, IMAGEMANAGER->findImage("�޸���")->getFrameX(), IMAGEMANAGER->findImage("�޸���")->getFrameY());
			_aniTownRun->ZoderRender(_player.y, pt.x - 60, pt.y - 68);
			break;
		case PLAYER_ROLL:
			//IMAGEMANAGER->frameRender("������", hdc, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68);
			//CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("������"),_player.y, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, IMAGEMANAGER->findImage("������")->getFrameX(), IMAGEMANAGER->findImage("������")->getFrameY());
			_aniTownRoll->ZoderRender(_player.y, pt.x - 60, pt.y - 68);
		break;
		case PLAYER_ATTACK_SWORD:

		break;
		case PLAYER_ATTACK_BOW:

			break;
		case PLAYER_DIE:


		break;
		}
		break;

	case TOWN_DUNGEON:
		switch (_state)
		{
		case PLAYER_IDLE:
			//IMAGEMANAGER->frameRender("����idle", hdc, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68);
			//CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("����idle"), _player.y, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, IMAGEMANAGER->findImage("����idle")->getFrameX(), IMAGEMANAGER->findImage("����idle")->getFrameY());
			_aniDgIdle->ZoderRender(_player.y, pt.x - 60, pt.y - 68);
		break;
		case PLAYER_RUN:
			//IMAGEMANAGER->frameRender("�����޸���", hdc, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68);
			//CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("�����޸���"), _player.y, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, IMAGEMANAGER->findImage("�����޸���")->getFrameX(), IMAGEMANAGER->findImage("�����޸���")->getFrameY());
			_aniDgRun->ZoderRender(_player.y, pt.x - 60, pt.y - 68);
		break;
		case PLAYER_ROLL:
			//IMAGEMANAGER->frameRender("����������", hdc, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68);
			//CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("����������"), _player.y, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, IMAGEMANAGER->findImage("����������")->getFrameX(), IMAGEMANAGER->findImage("����������")->getFrameY());
			_aniDgRoll->ZoderRender(_player.y, pt.x - 60, pt.y - 68);
		break;
		case PLAYER_FALL:
			//IMAGEMANAGER->findImage("���ۺ���")->alphaFrameRender(hdc, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, 0, 0, _holeAlpha);
			//CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("���ۺ���"), _player.y, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, IMAGEMANAGER->findImage("���ۺ���")->getFrameX(), IMAGEMANAGER->findImage("���ۺ���")->getFrameY());
			_aniFall->ZoderRender(_player.y, pt.x - 60, pt.y - 68);
		break;
		case PLAYER_ATTACK_SWORD:
			//IMAGEMANAGER->frameRender("���ҵ�", hdc, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68);
			//CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("���ҵ�"), _player.y, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, IMAGEMANAGER->findImage("���ҵ�")->getFrameX(), IMAGEMANAGER->findImage("���ҵ�")->getFrameY());
			_aniSword->ZoderRender(_player.y, pt.x - 60, pt.y - 68);
		break;
		case PLAYER_ATTACK_SWORD_SECOND:
			//IMAGEMANAGER->frameRender("���ҵ�2����", hdc, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68);
			//CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("���ҵ�2����"), _player.y, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, IMAGEMANAGER->findImage("���ҵ�2����")->getFrameX(), IMAGEMANAGER->findImage("���ҵ�2����")->getFrameY());
			_aniSwordTwo->ZoderRender(_player.y, pt.x - 60, pt.y - 68);
		break;
		case PLAYER_TALK:
			//IMAGEMANAGER->frameRender("����idle", hdc, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68);
			//CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("����idle"), _player.y, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, IMAGEMANAGER->findImage("����idle")->getFrameX(), IMAGEMANAGER->findImage("����idle")->getFrameY());
			_aniDgIdle->ZoderRender(_player.y, pt.x - 60, pt.y - 68);
			break;
		case PLAYER_ATTACK_BOW:
			//IMAGEMANAGER->frameRender("Ȱ������", hdc, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68);
			//CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("Ȱ������"), _player.y, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, IMAGEMANAGER->findImage("Ȱ������")->getFrameX(), IMAGEMANAGER->findImage("Ȱ������")->getFrameY());
			_aniBow->ZoderRender(_player.y, pt.x - 60, pt.y - 68);
		break;
		case PLAYER_DIE:
			//IMAGEMANAGER->frameRender("����", hdc, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68);
			//CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("����"), _player.y, CAMERAMANAGER->getDistanceX() - 60, CAMERAMANAGER->getDistanceY() - 68, IMAGEMANAGER->findImage("����")->getFrameX(), IMAGEMANAGER->findImage("����")->getFrameY());
			_aniDie->ZoderRender(_player.y, pt.x - 60, pt.y - 68);
		break;
		case PLAYER_SWIM:
			_aniSwim->ZoderRender(_player.y, pt.x - 20, pt.y - 15);
			break;
		}
		break;
	}
}

int player::getMaxItemSlot()
{
	return ITEMMENU->getMaxItemSlot();
}

void player::animation(int frameY)
{

	_aniTownIdle->update();
	_aniTownRun->update();
	_aniTownRoll->update();
	_aniDgIdle->update();
	_aniDgRun->update();
	_aniDgRoll->update();
	_aniFall->update();
	_aniSword->update();
	_aniSwordTwo->update();
	_aniBow->update();
	_aniDie->update();
	_aniSwim->update();

	_aniTownIdle->setFrameY(_player.direction);
	_aniTownRun->setFrameY(_player.direction);
	_aniTownRoll->setFrameY(_player.direction);
	_aniDgIdle->setFrameY(_player.direction);
	_aniDgRun->setFrameY(_player.direction);
	_aniDgRoll->setFrameY(_player.direction);
	_aniFall->setFrameY(_player.direction);
	_aniSword->setFrameY(_player.direction);
	_aniSwordTwo->setFrameY(_player.direction);
	_aniBow->setFrameY(_player.direction);
	_aniDie->setFrameY(_player.direction);
	_aniSwim->setFrameY(_player.direction);

}

void player::playerState()
{
	if (!ITEMMENU->getOpenMenu())
	{
		switch (_state)
		{
		case PLAYER_IDLE:
			if (INPUT->GetKey('W') || INPUT->GetKey('S')
				|| INPUT->GetKey('A')
				|| INPUT->GetKey('D')) _state = PLAYER_RUN;

			if (INPUT->GetKeyDown(VK_SPACE))
			{
				_lastRollX = _player.x;
				_lastRollY = _player.y;
				_holeAlpha = 255;
				_state = PLAYER_ROLL;
				_aniTownRoll->aniRestart();
				_aniDgRoll->aniRestart();
			}

			if (INPUT->GetKey('J') && _place == TOWN_DUNGEON)
			{
				switch (_player.weapon)
				{
					case EMPTY:
					_state = PLAYER_TALK;
					break;
					case SHORT_SOWRD:
						_state = PLAYER_ATTACK_SWORD;
						_aniSword->aniRestart();
						break;

					case BOW:
						_state = PLAYER_ATTACK_BOW;
						_aniBow->aniRestart();
						_isShoot = true;

						break;
				}

			}	

			if (_attackIndex != 0)
			{
				_attackIndex = 0;
			}
			break;
		case PLAYER_RUN:
			if (INPUT->GetKeyUp('W') || INPUT->GetKeyUp('S')
				|| INPUT->GetKeyUp('A')
				|| INPUT->GetKeyUp('D')) _state = PLAYER_IDLE;

			if (INPUT->GetKeyDown(VK_SPACE))
			{
				_lastRollX = _player.x;
				_lastRollY = _player.y;
				_holeAlpha = 255;
				_state = PLAYER_ROLL;
				_aniTownRoll->aniRestart();
				_aniDgRoll->aniRestart();
			}

			if (INPUT->GetKey('J') && _place == TOWN_DUNGEON )
			{

				switch (_player.weapon)
				{
				case EMPTY:
					_state = PLAYER_TALK;
					break;

				case SHORT_SOWRD:
					_state = PLAYER_ATTACK_SWORD;
					_aniSword->aniRestart();
					break;

				case BOW:
					_state = PLAYER_ATTACK_BOW;
					_aniBow->aniRestart();
					_isShoot = true;
					break;
				}
			}

			if (_attackIndex != 0)
			{
				_attackIndex = 0;
			}

			if (INPUT->GetKey('W'))
			{
				_player.y -= 4;
				_player.direction = 1;
				_up = true;
			}
			else {
				_up = false;
			}
			
			if (INPUT->GetKey('S'))
			{
				_player.y += 4;
				_player.direction = 0;
				_down = true;
			}
			else {
				_down = false;
			}

			if (INPUT->GetKey('A'))
			{
				_player.x -= 4;
				_player.direction = 3;
				_left = true;
			}
			else {
				_left = false;
			}
			if (INPUT->GetKey('D'))
			{
				_player.x += 4;
				_player.direction = 2;
				_right = true;
			}
			else {
				_right = false;
			}
			break;

		case PLAYER_ROLL:
			_rollJumpPower = 6.0f;
			_rollGravity = 0.1f;

			_rollCount++;
			switch (_player.direction)
			{
				case 0:
					_player.y += _rollJumpPower;
					break;
				case 1:
					_player.y -= _rollJumpPower;
					break;
				case 2:
					_player.x += _rollJumpPower;
					break;
				case 3:
					_player.x -= _rollJumpPower;
					break;
			}

			_rollJumpPower -= _rollGravity;
			if (_aniDgRoll->getAniState() == ANIMATION_END ||
				_aniTownRoll->getAniState() == ANIMATION_END)
			{
				_state = PLAYER_IDLE;
				_rollCount = 0;
				_rollIndex = 0;
				_rollGravity = 0;
				_rollJumpPower = 0;
			}
			break;

		case PLAYER_FALL:
			_holeAlpha -= 3;
			if (_holeAlpha <= 0)
			{
				_player.x = _lastRollX;
				_player.y = _lastRollY;
				_state = PLAYER_IDLE;
			}
			break;

		case PLAYER_ATTACK_SWORD:

			_attackCount++;

			if (_aniSword->getAniState() == ANIMATION_END)
			{
				_attackCount = 0;
				_attackIndex = 0;
				_attackIndex = 0;
				_state = PLAYER_IDLE;
				if (INPUT->GetKey('J'))
				{
					_state = PLAYER_ATTACK_SWORD_SECOND;
					_aniSwordTwo->aniRestart();
				}
			}
			break;

		case PLAYER_ATTACK_SWORD_SECOND:

			_attackCount++;

			if (_aniSwordTwo->getAniState() == ANIMATION_END)
			{
				_attackCount = 0;
				_attackIndex = 0;
				_state = PLAYER_IDLE;
			}
			break;

		case PLAYER_ATTACK_BOW:
			_attackCount++;
			if (_aniBow->getAniState() == ANIMATION_END)
			{
				_attackCount = 0;
				_attackIndex = 0;
				_state = PLAYER_IDLE;
			}
			if (_aniBow->getCurIndex() == 1)
			{
				switch (_player.direction)
				{
				case 0:
					_player.y -= 3;
					break;
				case 1:
					_player.y += 3;
					break;
				case 2:
					_player.x -= 3;
					break;
				case 3:
					_player.x += 3;
					break;
				}
			}
			if (_attackIndex == IMAGEMANAGER->findImage("Ȱ������")->getMaxFrameX())
			{
				_attackCount = 0;
				_attackIndex = 0;
				_state = PLAYER_IDLE;
			}
			
			break; 

		case PLAYER_TALK:
			if (INPUT->GetKey('W') || INPUT->GetKey('S')
				|| INPUT->GetKey('A')
				|| INPUT->GetKey('D')) _state = PLAYER_RUN;

			if (INPUT->GetKeyDown(VK_SPACE))
			{
				_lastRollX = _player.x;
				_lastRollY = _player.y;
				_holeAlpha = 255;
				_state = PLAYER_ROLL;
			}
			break;
		case PLAYER_DIE:
			break;
		case PLAYER_SWIM:
			if (INPUT->GetKey('W'))
			{
				_player.y -= 4;
				_player.direction = 1;
				_up = true;
			}
			if (INPUT->GetKey('S'))
			{
				_player.y += 4;
				_player.direction = 0;
				_down = true;
			}
			if (INPUT->GetKey('A'))
			{
				_player.x -= 4;
				_player.direction = 3;
				_left = true;
			}
			if (INPUT->GetKey('D'))
			{
				_player.x += 4;
				_player.direction = 2;
				_right = true;
			}
			break;
		}
	}
}

void player::attackRCUpdate()
{
	switch (_state)
	{
	case PLAYER_ATTACK_SWORD:
		switch (_player.direction)
		{
			case 0:
				_playerAttackBox.rc = RectMakeCenter(_player.x, _player.y + 30, 80, 40);
				break;
			case 1:
				_playerAttackBox.rc = RectMakeCenter(_player.x, _player.y - 35, 80, 40);
				break;
			case 2:
				_playerAttackBox.rc = RectMakeCenter(_player.x + 30, _player.y, 40, 60);
				break;
			case 3:
				_playerAttackBox.rc = RectMakeCenter(_player.x - 30, _player.y, 40, 60);
				break;
		}
		break;
	case PLAYER_ATTACK_SWORD_SECOND:
		switch (_player.direction)
		{
			case 0:
				_playerAttackTwoBox.rc = RectMakeCenter(_player.x, _player.y + 30, 80, 40);
				break;
			case 1:
				_playerAttackTwoBox.rc = RectMakeCenter(_player.x, _player.y - 35, 80, 40);
				break;
			case 2:
				_playerAttackTwoBox.rc = RectMakeCenter(_player.x + 30, _player.y, 40, 60);
				break;
			case 3:
				_playerAttackTwoBox.rc = RectMakeCenter(_player.x - 30, _player.y, 40, 60);
				break;
		}
		break;

	default:
		_playerAttackBox = { 0,0,0,0 };
		_playerAttackBox.isHit = false;
		_playerAttackTwoBox = { 0,0,0,0 };
		_playerAttackTwoBox.isHit = false;
		break;
	}
}

void player::keyInput()
{
	//���⸦ �ٲٴ� �Լ�
	if (INPUT->GetKeyDown('Z'))
	{
		ITEMMENU->getInventory()->switchWeapon();
	}

	//������ ����ϴ� �Լ�
	//������ �޴��� ���µ��� �ʾ��� ���� ���� 
	if (!ITEMMENU->getOpenMenu())
	{
		if (INPUT->GetKeyDown('E'))
		{
			//�÷��̾ ������ �ְ� && ���� ü���� Ǯü���� �ƴ� ���� ��� 
			if (PLAYERDATA->getIsInDungeon() &&
				PLAYERDATA->getInDungeonHp() < PLAYERDATA->getHp())
			{
				SOUNDMANAGER->play("heal", 0.4f);

				ITEMMENU->getInventory()->usePotionEquipped();
			}
		}
	}
}

void player::updateWeaponState()
{
	switch (ITEMMENU->getInventory()->getWeaponEquipped().getItemIdx())
	{
		case 16:
			_player.weapon = SHORT_SOWRD;
			break;

		case 15:
			_player.weapon = BOW;
			break;

		default:
			_player.weapon = SHORT_SOWRD;
			break;
	}
}

void player::npcTalk(bool& isTalk)
{
	if (isTalk) {
		_player.weapon = EMPTY;
	}
	else {
		_player.weapon = SHORT_SOWRD;
	}
}

