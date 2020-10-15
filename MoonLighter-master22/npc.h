#pragma once
#include "gameNode.h"
#include "itemManager.h"
#define MAX_NPC 4

class displayStand;

enum NPC_ACTION
{
	NPC_MOVE,
	NPC_STOP,
	NPC_CHECK_PRICE,
	NPC_WAIT,
	NPC_GO_HOME,
	NPC_ITEM_PICK
};

enum NPC_MAP
{
	NPC_SHOP
};
class npc : public gameNode
{
private:
	animation* _aniNpc; // npc �ִϸ��̼� ����
	animation* _aniPriceCheck; // �̸�Ƽ�� �ִϸ��̼� ����
	image* _peekItemImg; // ���� ��� �ִ� ������ �̹���
	string thinkInfo; // ��û�δ� �δ� ��δ� ��û��δ�
private:
	int _count;
	int _idx;
	int _time;

	int _spawnTime;
	float _speed;
	float _angle;

	string _key;

	tagPosF _pos;
	tagPosF _probe;

	tagPosF _target[4];

	vector<vector<tagPosF>> shop_target; // Ÿ�� ��ǥ �迭

	int _targetIdx;

	int shop_targetIdx; // ���� ��ȣ Ÿ�� �ε���
	int shop_currentTargetIdx; // ���� ��ǥ ��ġ���� �ε���

	RECT _rc;
	RECT _talkRect;
	bool _stop;
	bool _Istalk;
	bool _delay;

	bool _isActive;
	bool _isSpawn;

	int _boxidx;
	int _boxCnt;

	string _talk;
	string _name;

	HFONT hFont;
	HFONT oldFont;

	RECT _nameRect;
	RECT _textRect;

	displayStand* _displayStand; // ���� ���� ����
	gameItem _itemEmpty;		//����ִ� ������ 

	string _illustrator = "�Ϸ�";

	NPC_ACTION _state; // npc ����

	bool _isBarking; // �������� ¢�� �ִ°�

	void setshopTargetPos(); // �������� Ÿ�� ��ǥ ����

public:
	HRESULT init(tagPosF pos, string key); // ���� npc �ʱ�ȭ
	HRESULT init(tagPosF pos, string key, NPC_MAP NPC_SHOP, int idx, displayStand* dis);  //���� npc �ʱ�ȭ

	void release();
	void update(); // ���� NPC ������Ʈ
	void update(NPC_MAP NPC_SHOP); // ����NPC ������Ʈ

	void render(); // �⺻ npc ������
	void render(NPC_MAP NPC_SHOP); // ���� npc ������

	void anim(); // npc �ִϸ��̼�
	void boxAnim(); // ��ȭ�ڽ� �ִϸ��̼�
	void move(); // ���� npc ������
	void move(NPC_MAP NPC_SHOP); // ���������� npc ������

	void DistanceCheck();
	void action(string talk); //NPC ��Ʈ �� ��ǳ�� ������Ʈ
	void action(); //������ ����
	void collision(); // NPC �浹��Ʈ ����
	void lookPlayer(); // �÷��̾ �ٶ󺸵��� ���� ����������
	void npcSpawn(); // npc ����

	tagPosF& getPos() { return _pos; } // npc x , y ��ǥ ��������
	RECT& getRect() { return _rc; } // npc ��Ʈ ��������
	string getKey() { return _key; } // npc �̹��� KEY�� ��������

	void setPosX(float x) { _pos.x = x; } // x ��ǥ ����
	void setPosY(float y) { _pos.x = y; } // y ��ǥ ����

	bool& getActive() { return _isActive; } // npc�� ����ִ°�
	void setActive(bool ac) { _isActive = ac; } // npc �������� ����

	int& getCurrentTargetIdx() { return shop_currentTargetIdx; } // ���� ������ ��ǥ �ε���
	void setCurrentTargetIdxPlus() { shop_currentTargetIdx++; }
	void priceCheck(); // ���� ������ ���ݿ� ���� ����
	void PriceCheckAnim(); // �̸�Ƽ�� �ִϸ��̼�
	void ItemGet(); // ������ ���� ��������
	void ItemActive();

	NPC_ACTION& getState() { return _state; } // npc ���� ������Ʈ ��ȯ
	void setState(NPC_ACTION st) { _state = st; } // npc ���� ������Ʈ
	npc() {}
	~npc() {}
};

