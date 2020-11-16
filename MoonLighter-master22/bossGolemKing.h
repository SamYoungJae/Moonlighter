#pragma once
#include "boss.h"
#include "progressBar.h"

#define ROCKDAMAGE 7
#define FISTDAMAGE 15
#define HANDDAMAGE 10
#define BOSS_MAXHP 2000

enum class GOLEMKINGSTATE
{
	BS_INIT,BS_IDLE,BS_FIST,BS_ROCK_SHOOT,BS_ROCK_ROUND,BS_HAND,BS_DEAD
};

enum class GOLEMANISTATE
{
	ANI_BOSSUP,ANI_DEAD1,ANI_DEAD2,ANI_FISTSHOOT1, ANI_FISTSHOOT2, ANI_FISTSHOOT3, ANI_HANDSHOOTSTART,ANI_HANDSHOOTEND,ANI_IDLE
};

enum class BOSSPATTERN
{
	PATTERN1, PATTERN2, PATTERN3, PATTERN4, EMPTY
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
	int atkCount;
	bool isHit;
	HANDSTATE state;
};

struct tagRock
{
	image* img;
	RECT rc;
	RECT colRC;
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
	BOSSPATTERN _pattern;						//���� ����
	

	vector<BOSSPATTERN> _vGolemAttack;			//�� �������ϵ�

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
	int _patternCool;							//���� �Ѿ ��
	int _hitCount;

	int* _itemIndex;			//������ �ε���
	int* _itemNum;				//������ ����
	int	 _itemIndexSize;		//�������ε��� ������
	int  _itemDropSize;			//�����۵�ӵɰ���
	bool _isItemDrop;

	bool _isFirst;

	tagGolemHand _golemHand;					//������ ��°���

	vector<tagRock> _vRock;						//����

	float _rockShootAngle[2];						//���� ������

	tagFist _bossFist;							//���� �ָ���

	bool _isAttackSoundPlay;					//������ ����
	bool _isDeadSoundPlay;						//�״� ����
	bool _isDead;								//�׾���?
	bool _isHit;
	bool _coliSkillAroow;

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
	void hitUpdate();

	void initVGolemAttack();								//���Ϳ� �������� �ֱ�
	void suffleVGolemAttack();								//�����ϰ� �����ϱ�
	void initGolemHand();									//�հ��� �̴�

	void bsFistUpdate();
	void bsRockShootUpdate();
	void bsRockRoundUpdate();
	void bsHandUpdate();
	void vRockUpdate();
	void collisionRock();
	void collisionArrow();


	float getX() { return _x; }
	float getY() { return _y; }
	bool getIsDead() { return _isDead; }
	bool getIsItemDrop() { return _isItemDrop; }

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setIsItemDrop(bool drop) { _isItemDrop = drop; }
	int* getDropItemIndex() { return _itemNum; }
	int getDropItemSize() { return _itemDropSize; }
};

