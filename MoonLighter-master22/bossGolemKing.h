#pragma once
#include "boss.h"
#include "progressBar.h"

enum class GOLEMKINGSTATE
{
	BS_INIT,BS_IDLE,BS_FIST,BS_ROCK_SHOOT,BS_ROCK_ROUND,BS_HAND,BS_DEAD
};

enum class GOLEMANISTATE
{
	ANI_BOSSUP,ANI_DEAD1,ANI_DEAD2,ANI_FISTSHOOT1, ANI_FISTSHOOT2, ANI_FISTSHOOT3, ANI_HANDSHOOTSTART,ANI_HANDSHOOTEND,ANI_IDLE
};

enum class HANDSTATE
{
	HAND_INIT,HAND_FALL,HAND_UP
};

struct tagGolemHand
{
	animation* ani;
	RECT rc;
	float x, y;
	float hight;
	float speed;
	float shadowScale;
	int count;
	bool isHit;
	HANDSTATE state;
};

struct tagRock
{
	image* img;
	RECT rc;
	float x, y;
	float hight;
	float shadowScale;
	int time;				//�����ð�
	bool isHit;
};

struct tagFist
{
	animation* ani;
	POINT pt[4];
	int wid;
	int hei;
	int count;
	float x;
	float y;
	float angle;
	bool isMoveLeft;
	bool isHit;
};

class bossGolemKing : public boss
{ 
private:
	GOLEMKINGSTATE _golemState;					//�� ������Ʈ
	GOLEMANISTATE _golemAni;					//�� �ִϸ��̼�

	vector<GOLEMKINGSTATE> _vGolemAttack;			//�� �������ϵ�

	animation* _aniBossUp;						//init���
	animation* _aniBossDead1;					//�״°� ù��°
	animation* _aniBossDead2;					//�״°� �ι�°
	animation* _aniBossFistShoot1;				//�������� �ָԹ߻��ϴ°�
	animation* _aniBossFistShoot2;
	animation* _aniBossFistShoot3;
	animation* _aniBossHandShootStart;			//�� �� ���� ������
	animation* _aniBossHandShootEnd;			//�� �� �ޱ�
	animation* _aniIdle;						//��� �񷽾���
	animation* _scroll;							//��ũ��

	
	progressBar* _hpBar;						//������ hp
	progressBar* _hpRed;						//�߱�
	progressBar* _hpWhite;						//���

	int _hp;									//ü��	
	int _attackCool;							//���� ��Ÿ��
	int _hitCount;

	tagGolemHand _golemHand;					//������ ��°���

	int _rockFireTime;							//�����ֱ�� ���� ����߷���
	int _rockFireCount;							//��� ���ɳ�?
	vector<tagRock> _vRock;						//����

	float _rockShootAngle[3];						//���� ������

	tagFist _bossFist;							//���� �ָ���

	bool _isAttackSoundPlay;					//������ ����
	bool _isDeadSoundPlay;						//�״� ����
	bool _isDead;								//�׾���?
	bool _isHit;

public:
	bossGolemKing() {}
	~bossGolemKing() {}

	HRESULT init(int x, int y);
	void release();
	void update();
	void render();
	void changeAniState(GOLEMANISTATE state);				//�ִϸ��̼� ����
	void initAttack();										//�����ϱ��� ���º� �ʱ�ȭ

	void collisionPlayer();

	void initVGolemAttack();								//���Ϳ� �������� �ֱ�
	void suffleVGolemAttack();								//�����ϰ� �����ϱ�
	void initGolemHand();									//�հ��� �̴�

	void bsFistUpdate();
	void bsRockShootUpdate();
	void bsRockRoundUpdate();
	void bsHandUpdate();
	void vRockUpdate();


	float getX() { return _x; }
	float getY() { return _y; }
	bool getIsDead() { return _isDead; }

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
};

