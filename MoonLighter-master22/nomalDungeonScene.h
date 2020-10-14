#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "dungeonMap.h"
#include "object.h"
#include "enemy.h"

enum DUNGEONSCENESTATE
{
	DS_UPDATE, DS_RESULT
};

class nomalDungeonScene : public gameNode
{
private:
	DUNGEONSCENESTATE _dState;

	DungeonMap* _startDungeon;				//��ü ������ ������

	DungeonMap* _currentDungeon;				//���� �÷��̾ �ִ� ����

	vector<pair<POINT, DungeonMap*>> _vMinimap;

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
};

