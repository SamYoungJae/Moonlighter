#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "dungeonMap.h"
#include "object.h"
#include "enemy.h"

enum DUNGEONSCENESTATE
{
	DS_UPDATE, DS_RESULT, DS_RETURN
};

enum RESULTKIND
{
	RESULT_PLAYERDIE,RESULT_RETURN
};

typedef struct
{
	int slotIdx;
	bool isEmpty;

}dungeonSlot;

class nomalDungeonScene : public gameNode
{
private:
	typedef vector<gameItem*> vGameItem;
private:
	vGameItem _vItem;
	dungeonSlot _dungeonSlot[28];
	RESULTKIND _resultKind;
	vector<RESULTENEMY> _vEnemy;			//���â ���ʹ�s
	RESULTENEMY* _killEnemy;				//�÷��̾����ο��ʹ�
	animation* _potal;						//���ư����� ��Ż
private:
	DUNGEONSCENESTATE _dState;

	DungeonMap* _startDungeon;				//��ü ������ ������

	DungeonMap* _currentDungeon;				//���� �÷��̾ �ִ� ����

	vector<pair<POINT, DungeonMap*>> _vMinimap;		//�̴ϸ�


	//��ŸƮ���� �η縶��
	animation* _golemScroll;

	//�÷��̾� �׽�Ʈ
	RECT _player;
	bool left;
	bool right;
	bool up;
	bool down;

	//���ʹ� �׽�Ʈ
	enemy*	_em;

	//���� ����
	int _dgFloor;
public:
	nomalDungeonScene() { };
	~nomalDungeonScene() { };

	HRESULT init();
	void release();
	void update();
	void render();
	bool minimapPush(POINT pt);		//ó������ ���̶�� �̴ϸɿ� Ǫ������
	void minimapRender();			//�̴ϸ��� ��������
	void setNewFloor();				//������ �ʱ�ȭ�ϴ°�
	void soundUpdate();				//����� ����
	void dungeonUpdate();			//�Ϲ����� ������Ʈ
	void resultUpdate();			//���â ������Ʈ

public:
	void initItemSlot();
	void getInvenItem();
	void deleteInvenItems();
	void itemResultRender();
	void countRender(int count, int destX, int destY);	//������ ī��Ʈ ��� 
	void golemScrollRender();
	void updateRender();
	void resultRender();
};

