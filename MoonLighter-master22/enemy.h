#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "progressBar.h"
#include "itemManager.h"

enum ENEMYKIND			// ����
{
	EM_GOLEM, EM_REDGOLEM, EM_POTGOLEM, EM_SKULLHAMMER, EM_BABYSLIME
};

enum ENEMYSTATE			// ����
{
	EM_MOVE, EM_ATTACK, EM_DIE, EM_HIT
};

enum ENEMYDIRECTION		//�����ִ� ����
{
	EM_LEFT, EM_RIGHT, EM_TOP, EM_BOTTOM
};

enum NODESTATE
{
	NODE_START,
	NODE_END,
	NODE_WALL,
	NODE_EMPTY
};

struct node
{
	RECT rc;
	int idx, idy;
	int centerX, centerY;
	int F, G, H;
	node* parentNode;
	NODESTATE nodeState;

	void init(int _idx, int _idy)
	{
		idx = _idx;
		idy = _idy;
		rc = RectMake(140 + (_idx * 35), 105 + (_idy * 35), 35, 35);
		centerX = (rc.left + rc.right) / 2;
		centerY = (rc.top + rc.bottom) / 2;
		F = G = H = 0;
		nodeState = NODE_EMPTY;
		parentNode = NULL;
	}
};

class enemy : public gameNode
{
protected:
	ENEMYKIND _emKind;
	ENEMYSTATE _emState;
	ENEMYDIRECTION _emDirection;
	image* _enemyImg;

	progressBar* _hpBar;
	bool _isHpBarRender;
	int _hpBarRenterTime;
	int _hpBarAlpha;

	RECT _emRC;
	RECT _aStarRC;
	RECT _attackRange;
	bool _isActivate;
	bool _isAttackRange;
	bool _isHit;
	bool _isItemDrop;


	float _x;
	float _y;

	int _emHp;
	int _emAtk;
	// ������
	int* _itemIndex;			//������ �ε���
	int* _itemNum;				//������ ����
	int	 _itemIndexSize;		//�������ε��� ������
	int  _itemDropSize;			//�����۵�ӵɰ���


	bool _emPlayerColi;	//�浹�� �Լ�
	int count;			//�浹�� �Լ�

	//���ʹ� ���̽�Ÿ ��
	int _idx;						//Ÿ�� ������
	int _idy;						//Ÿ�� ������
	node** _totalNode;				//�����Ҵ����� �������迭�� �ʱ�ȭ�ϱ����� �����������̴�
	node* _startNode;
	node* _endNode;
	node* _curNode;
	vector<node*> _openList;
	vector<node*> _closeList;
	vector<node*> _finalList;

	int _count;
	bool _isFind;
public:
	enemy() {}
	virtual ~enemy() {}

	virtual HRESULT init(int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void initTileSize(int x, int y);
	virtual void setEndTile(int x, int y);
	virtual void setWallTile(vector<tagTile> vTile);
	virtual void aStar();
	virtual void addOpenList(int idx, int idy);
	virtual void delOpenList(int arr);
	virtual void isAttackRange(RECT rc);
	virtual bool isAstarFail();
	virtual void collision();
	virtual void soundUpdate();
	virtual void setProgressBar();
	virtual void hitSoundPlay();
public:
	virtual bool getIsActivate() { return _isActivate; }
	virtual void setIsActivate(bool at) { _isActivate = at; }
	virtual int getEmHp() { return _emHp; }
	virtual void setEmHp(int hp) { _emHp = hp; }
	virtual int getEmAtk() { return _emAtk; }
	virtual RECT getEmRC() { return _emRC; }
	virtual int* getDropItemIndex() { return _itemNum; }
	virtual int getDropItemSize() { return _itemDropSize; }
	virtual float getX() { return _x; }
	virtual float getY() { return _y; }
	virtual bool getIsItemDrop() { return _isItemDrop; }
	virtual void setIsItemDrop(bool drop) { _isItemDrop = drop; }
	virtual animation* getAttackAnimation() { return nullptr; };
	virtual int getDownDirectionY() { return 0; };
	virtual float getEnemyScale() { return 1.f; }
};

class redGolem : public enemy
{
private:

	animation* _move;
	animation* _attack;
	animation* _moveHit;
	animation* _attackHit;
	animation* _die;

	RECT _attackBox;

	bool _emPlayerColi;	//�浹�� �Լ�
	int count;			//�浹�� �Լ�

	bool _isAttackSoundPlay;
	bool _isDieSoundPlay;
	float _knockBackSpeed;
public:
	redGolem() {}
	virtual ~redGolem() {}

	virtual HRESULT init(int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();

	void directionUpdate();
	void moveRender();
	void attackRender();
	void attackAniPlay();
	bool attackAniStop();
	void attackBox();
	void golemMove();
	void setStartNode();
	void soundUpdate();
	void hitSoundPlay() override;
	void dropItem();
	void redGolemCollision();
	virtual animation* getAttackAnimation();
	virtual int getDownDirectionY();

	RECT getAttackBox() { return _attackBox; }
};

class golem : public enemy
{
	// isAttackRange ���� �÷��̾� ��Ʈ �־��ٰ�
	// �÷��̾ �������� _isHit Ʈ�� ������ְ� hp����ٰ�
private:
	animation* _move;
	animation* _attack;
	animation* _moveHit;
	animation* _attackHit;
	animation* _die;

	RECT _attackBox;

	bool _emPlayerColi;	//�浹�� �Լ�
	int count;			//�浹�� �Լ�

	bool _isAttackSoundPlay;
	bool _isDieSoundPlay;
	float _knockBackSpeed;
public:
	golem() {}
	virtual ~golem() {}

	virtual HRESULT init(int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();

	void directionUpdate();
	void moveRender();
	void attackRender();
	void attackAniPlay();
	bool attackAniStop();
	void attackBox();
	void golemMove();
	void setStartNode();
	void hitSoundPlay() override;
	void golemCollision();
	virtual animation* getAttackAnimation();
	virtual int getDownDirectionY();
};

class potGolem : public enemy
{
private:
	enum BULLETDIRECTION
	{
		BM_UP, BM_DOWN, BM_LEFT, BM_RIGHT
	};
	struct tagPotBullet
	{
		BULLETDIRECTION direction;
		image* img;
		RECT rc;
		float x, y;
		float angle;
		bool isFire;
		int frameY;
	};
private:
	animation* _attack;
	animation* _attackHit;
	animation* _die;

	RECT _attackRangeL;
	RECT _attackRangeR;
	RECT _attackRangeT;
	RECT _attackRangeB;

	int _hitCount;
	int _fireCount;
	bool _isFire;
	bool _isDieSoundPlay;
	bool _isFireSoundPlay;

	bool _emPlayerColi;	//�浹�� �Լ�
	int count;			//�浹�� �Լ�

	tagPotBullet* _bullet;
public:
	potGolem() {}
	~potGolem() {}

	HRESULT init(int x, int y);
	void release();
	void update();
	void render();
	void aniUpdate();
	void aniRender();
	void emDirectionUpdate();
	void emBulletFire();
	void emBulletMove();
	bool bulletEmpty();
	virtual void isAttackRange(RECT rc);
	virtual void setWallTile(vector<tagTile> vTile);
	void hitSoundPlay() override;
	void potGolemCollision();
	virtual animation* getAttackAnimation();
	virtual int getDownDirectionY();
};

class skullHammer : public enemy
{
private:
	animation* _move;
	animation* _attack;
	animation* _moveHit;
	animation* _attackHit;
	animation* _die;

	RECT _aStarRC;				// ���̽�Ÿ�� �ٴڷ�Ʈ
	RECT _attackBox;				// ���ݹ��� ��Ʈ
	float _knockBackSpeed;			//�˹齺�ǵ�
	int _hitCount;					// ��Ʈ ī��Ʈ (��Ʈ ������)
	bool _isDieSoundPlay;
	bool _isAttackSoundPlay;

	bool _emPlayerColi;	//�浹�� �Լ�
	int count;			//�浹�� �Լ�

public:
	skullHammer() {}
	~skullHammer() {}

	virtual HRESULT init(int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();

	void directionUpdate();
	void moveRender();
	void attackRender();
	void attackAniPlay();
	bool attackAniStop();
	void attackBox();
	void skullMove();
	void setStartNode();
	void hitSoundPlay() override;
	void skullHammerCollision();
	virtual animation* getAttackAnimation();
	virtual int getDownDirectionY();
};

class gasMan : public enemy
{
private:
	enum GASARROWDIRECTION
	{
		AR_LEFT, AR_RIGHT, AR_UP, AR_DOWN
	};
	struct tagGasArrow
	{
		float x, y;
		float angle;
		float speed;
		bool isFire;
		RECT rc;
		GASARROWDIRECTION direction;
	};
private:
	animation* _move;
	animation* _moveHit;
	animation* _attack;
	animation* _attackHit;
	animation* _die;

	tagGasArrow _arrow;
	vector<tagGasArrow> _vArrow;

	float _knockBackSpeed;
	int _hitCount;
	bool _isFire;
	bool _isDieSoundPlay;
	bool _isFireSoundPlay;

	bool _emPlayerColi;	//�浹�� �Լ�
	int count;			//�浹�� �Լ�

public:
	gasMan() {}
	~gasMan() {}

	HRESULT init(int x, int y);
	void release();
	void update();
	void render();

	void aniRender();
	void attackRangeUpdate();
	void setEmDirection();
	void enemyMove();
	void setStartNode();
	void arrowFire();
	void arrowMove();
	void arrowRender();
	void hitSoundPlay() override;
	void gasManCollision();
	virtual animation* getAttackAnimation();
	virtual int getDownDirectionY();
};

class bossSkeleton : public enemy
{
public:
	enum SKELETONSTATE
	{
		ST_ATTACK_SWORD, ST_ATTACK_HAMMER, ST_SKILL_SWORD, ST_SKILL_HAMMER, ST_WAVE, ST_MOVE, ST_INIT, ST_DIE
	};
	enum SKELETONPHASE
	{
		ST_PHASE_1, ST_PHASE_2
	};
	struct tagAtkBox
	{
		bool isHit;
		RECT box;
	};
	struct tagBlade
	{
		animation* ani;
		float x, y;				// ������
		float angle;			//���ư��� ����
		int atk;
		bool isFire;			// �߻��߳�?
		bool isBreak;			//�μ����� �ִϸ��̼� ����� && �浹��ɵ�
	};
	SKELETONSTATE _stState;
	SKELETONPHASE _bossPhase;
private:
	animation* _move;				//������
	animation* _attackSword;		//Į ��������
	animation* _attackHammer;		//�ظ� ��������
	animation* _hammerWave1;		//�ظ������
	animation* _scroll;
	tagBlade* _blade;				//���̵�

	vector<animation*> _vSkillEffect; // ��ų ����� ����Ʈ ���ϸ��̼�

	RECT _swordRange;
	RECT _hammerRange;
	tagAtkBox _swordAtkBox;
	tagAtkBox _hammerAtkBox;
	tagAtkBox _hammerWaveAtkEllipse;

	int _waveCount;			//����� Ƚ��
	int _waveTime;			//���������
	int _emAtkHammer;		//�ظ� ���ݷ�
	int _emAtkSword;		//Į ���ݷ�
	int _emAtkWave;			//����� ���ݷ�
	int _hitCount;			//��Ʈī��Ʈ
	int _autoAttackCount;	//������� ī��Ʈ
	int _autoAttackCool;	//������� ��
	int _dieCount;			//�׾����� ������� ���ð�

	bool _isWaveHit;		//����� �浹�߳�?

	progressBar* _hpBarRed;
	progressBar* _hpBarWhite;


	// ���� ���� ���Լ�
	bool _isAttackPlay;


public:
	bossSkeleton() {}
	~bossSkeleton() {}

	HRESULT init(int x, int y);
	void release();
	void update();
	void render();
	void setStartNode();
	void enemyMove();
	void animationRender();
	void atkRangeUpdate();
	void atkBoxUpdate();
	void moveUpdate();
	void attackUpdate();
	void soundUpdate();
	void bladeUpdate();
	void hitUpdate();
	void hitToPlayer();
	void hitSoundPlay();
	virtual animation* getAttackAnimation();
	virtual int getDownDirectionY();
	virtual float getEnemyScale() { return 3.f; }
};
