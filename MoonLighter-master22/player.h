#pragma once
#include "singletonBase.h"
#include "arrow.h"
#include "animation.h"

enum PLACE
{
	SHOP,
	TOWN_DUNGEON
};
enum PLAYER_STATE
{
	PLAYER_IDLE,
	PLAYER_RUN,
	PLAYER_ROLL,
	PLAYER_ATTACK_SWORD, PLAYER_ATTACK_SWORD_SECOND, PLAYER_ATTACK_BOW,
	PLAYER_SHILED, BOW_CHARGE,
	PLAYER_TALK,
	PLAYER_DIE,
	PLAYER_DIE_PORTAL,
	PLAYER_FALL,
	PLAYER_SWIM,
	HIT_IDLE,
	HIT_RUN,
	HIT_SWORD,
	HIT_SWORD_TWO,
};

enum WEAPONSTATE
{
	EMPTY,
	SHORT_SOWRD,
	BOW
};

struct tagPlayer
{
	RECT rc;
	RECT shadowRc;
	float x;
	float y;
	int direction;
	int speed;
	WEAPONSTATE weapon;
	int count;
	int index;
	int dashCount;
};

struct tagPlayerAttackBox
{
	RECT rc;
	bool isHit;
};

struct tagDamegeFont
{
	int damage;
	bool iaActivate;
};

class player : public singletonBase <player>
{
private:
	vector<tagDamegeFont*> _damageFont;
private:
	arrow* _arrow;

	PLAYER_STATE _state;
	PLACE _place;

	tagPlayerAttackBox _playerAttackBox;
	tagPlayerAttackBox _playerAttackTwoBox;

	bool _right;
	bool _left;
	bool _up;
	bool _down;
	bool _isTalk;
	bool _isHit;
	bool _isDie;
	bool _isReturn;
	bool _isSkill;		//���� ��ų�̳�?

	bool _displayOn;

	int _frameX;
	int _frameY;

	tagPlayer _player;

	int _rollCount;
	int _rollIndex;

	int _lastRollX;			// �������� x
	int _lastRollY;			// �������� y
	int	_holeAlpha;			// ������ ���İ�

	int _attackCount;
	int _attackIndex;

	int _playerHp;
	int _hitAlpha;

	int _skillCount;		//����ī��Ʈ
	int _skillIndex;

	float _rollJumpPower;
	float _rollGravity;
private:

	animation* _aniTownIdle;
	animation* _aniTownRun;
	animation* _aniTownRoll;
	animation* _aniDgIdle;
	animation* _aniDgRun;
	animation* _aniDgRoll;
	animation* _aniFall;
	animation* _aniSword;
	animation* _aniSwordTwo;
	animation* _aniBow;
	animation* _aniDie;
	animation* _aniSwim;
	
	animation* _aniShiled;
	animation* _bowCharge;

	animation* _aniHit;
	animation* _aniRunHit;
	animation* _aniSwordHit;
	animation* _aniSwordTwoHit;

	animation* _aniDiePortal;

public:
	HRESULT init();
	void release(); // �޸� ������ ��Ȱȭ ����.
	void update();
	void render(HDC hdc);

	//�κ��丮 ���� �Լ� 
	int getMaxItemSlot();

	void animation(int frameY);	//�÷��̾� �ִϸ��̼�
	void playerState();			//�÷��̾� ���¿����� �ൿ
	void attackRCUpdate();		//�÷��̾� ���� ��Ʈ ������Ʈ
	void updateWeaponState();	//�÷��̾��� ���� ���� ���� ������Ʈ 
	void keyInput();			//�÷��̾��� ���¿� ������� Ű �Է��� �޴� �Լ� 
	void npcTalk(bool& isTalk);	//npc�� �̾߱� ���̳�
	void hitPlayer();			//�÷��̾ �¾ҳ�
	void playerMove();			//�÷��̾� ������
	void playerAttack();		//j Ű�� �̿��� ����
	void playerSkill();			//kŰ ��ų
	void playerPush();			//���и� ��ä�� �°ų� ȭ���� �� �з�����
	bool getKeyMove();			//wasd�� ������?
	void arrowSkillSet();		//�÷��̾� ��ų ����


	void imageInit();

	void setDisplayOn(bool on) { _displayOn = on; }
	bool& getDisplayOn() { return _displayOn; }

	float getX() { return _player.x; }
	float getY() { return _player.y; }

	RECT& getRect() { return _player.rc; }
	RECT getShadowRect() { return _player.shadowRc; }

	arrow *getArrow() { return _arrow; }

	int getPlayerDirection() { return _player.direction; }
	int getSpeed() { return _player.speed; }
	float getJumpPower() { return _rollJumpPower; }

	bool& getRight() { return _right; }
	bool& getLeft() { return _left; }
	bool& getUp() { return _up; }
	bool& getDown() { return _down; }
	bool getSkill() { return _isSkill; }


	WEAPONSTATE getWeaponState() { return _player.weapon; }

	PLAYER_STATE getPlayerState() { return _state; }

	void setPlayerState(PLAYER_STATE state) { _state = state; }

	void setX(float x) { _player.x = x; }
	void setY(float y) { _player.y = y; }
	void setRollPower(float p) { _rollJumpPower = p; }
	void setRollGravity(float g) { _rollGravity = g; }
	void setSkill(bool isSkill) { _isSkill = isSkill; }

	tagPlayerAttackBox& getPlayerAttackBox() { return _playerAttackBox; }
	void setPlayerAttackBoxHit(bool hit) { _playerAttackBox.isHit = hit; }

	tagPlayerAttackBox& getPlayerAttackTwoBox() { return _playerAttackTwoBox; }
	void setPlayerAttackTwoBoxHit(bool hit) { _playerAttackTwoBox.isHit = hit; }

	void setPlace(PLACE place) { _place = place; }
	void setHit(bool isHit) { _isHit = isHit; }
	void setPlayerDirection(int i) { _player.direction = i; }
	::animation* getPlayerDGRoll() { return _aniDgRoll; }
	void playDgRoll() { _aniDgRoll->aniRestart(); }
	::animation* getAnimation();

};

