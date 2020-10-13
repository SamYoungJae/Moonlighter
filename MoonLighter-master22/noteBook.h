#pragma once
#include "item.h"
#define NOTEBOOKPOSX	230
#define NOTEBOOKPOSY	98

class noteBook
{
private:
	POINT _noteBookPos;		//��Ʈ�ϸ޴� ��ġ 
	float _menuMoveSpeed;	//�޴��� �̵��ϴ� �ӵ� 

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	POINT getNoteBookPos() { return _noteBookPos; }					//��Ʈ�� ��ġ�� get�Լ�
	void setNoteBookPosX(int posX) { _noteBookPos.x = posX; }		//��Ʈ�� x��ǥ set�Լ�
	void setNoteBookPosY(int posY) { _noteBookPos.y = posY; }		//��Ʈ�� y��ǥ set�Լ� 
	void initPos();
	void moveNoteBookLeft(int destPos);								//��Ʈ���� destPos���� �������� �̵���Ŵ
	void moveNoteBookRight(int destPos);							//��Ʈ���� destPos���� �������� �̵���Ŵ
};


