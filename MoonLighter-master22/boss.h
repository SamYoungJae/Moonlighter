#pragma once
#include "gameNode.h"

enum BOSSSTATE
{
	BOSS_INIT,BOSS_UPDATE,BOSS_DIE
};

class boss : public gameNode
{
protected:
	BOSSSTATE _bState;		//���� ������Ʈ
	float _x, _y;			//���� ������ǥ
	RECT _bossRC;			//���� ��Ʈ

	vector<animation*> _vAni;	//���� �ִϸ��̼� ����
	int _aniIdx;				//���� ���� �̵��� �ε���

public:
	boss() {}
	virtual ~boss() {}

	virtual HRESULT init(int x, int y);			//xy ��ǥ�� �ʱ�ȭ
	virtual void release();
	virtual void update();
	virtual void render();

};

