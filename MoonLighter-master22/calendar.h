#pragma once
#define CALENDARPOSX	130
#define CALENDARPOSY	92

class calendar
{
private:
	POINT _calendarPos;		//Ķ�����޴� ��ġ 
	float _menuMoveSpeed;	//�޴��� �̵��ϴ� �ӵ� 

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	POINT getCalendarPos() { return _calendarPos; }					//Ķ���� ��ġ�� get�Լ�
	void setCalendarPosX(int posX) { _calendarPos.x = posX; }		//Ķ���� x��ǥ set�Լ�
	void setCalendarPosY(int posY) { _calendarPos.y = posY; }		//Ķ���� y��ǥ set�Լ� 
	void initPos();													//Ķ���� ��ġ�� �ʱ�ȭ 
	void moveCalendarLeft(int destPos);								//Ķ������ destPos���� �������� �̵���Ŵ						
	void moveCalendarRight(int destPos);							//Ķ������ destPos���� �������� �̵���Ŵ

};

