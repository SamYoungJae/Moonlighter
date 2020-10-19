#pragma once
#include "gameNode.h"

enum POTALSTATE
{
	POTAL_INIT,POTAL_UPDATE,POTAL_BREAK,
	POTAL_PLAYERIN,POTAL_PLAYEROUT
};

class potal : public gameNode
{
private:
	POTALSTATE _potalState;		//��Ż�� ����
	float _x, _y;				//��Ż ������ǥ
	RECT _rc;					//��Ż �ٴڷ�Ʈ
	animation* _init;			//�̴ֿ��ϸ��̼�
	animation* _update;			//������Ʈ
	animation* _break;			//�μ����°�
	animation* _playerIn;		//�÷��̾� ���Ƶ��̱�
	animation* _playerOut;		//�÷��̾� ���

	bool _isActivate;			//Ȱ��ȭ�Ƴ�?
	bool _isInRange;			//�����ȿ� �ֳ�?


public:
	potal() {}
	~potal() {}

	HRESULT init(float x, float y, POTALSTATE state);
	void update();
	void render();


	POTALSTATE getPotalState() { return _potalState;}
	bool getIsActivate() { return _isActivate; }
	bool getIsInRange() { return _isInRange; }
	float getX() { return _x; }
	float getY() { return _y; }
	animation* getAnimation();

	void setPotalState(POTALSTATE state);
	void setIsActivate(bool activate) { _isActivate = activate; }
	void setIsInRange(bool range) { _isInRange = range; }
	float setX(float x) { _x = x; }
	float setY(float y) { _y = y; }

};

