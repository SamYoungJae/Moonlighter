#pragma once

//Ŀ�� ���� 
enum CURSOR_STATE
{
	CURSOR_IDLE,
	CURSOR_MOVE,
	CURSOR_CLICK,
	CURSOR_PRICE_OFF,
	CURSOR_PRICE_ON
};

//Ŀ�� ����ü 
typedef struct
{
	CURSOR_STATE state;		//���� Ŀ���� ����(�ִϸ��̼ǿ�)
	image *img;				//Ŀ�� �̹��� 
	int idx;				//�ִϸ��̼� �ε���X 
	int slotIdx;			//Ŀ���� ��ġ�� ���� �ε��� 
	int clickTime;			//Ŀ���� Ŭ���� �ð�

}cursorUnit;

class cursor 
{
private:
	cursorUnit _cursor;

	int _animTimer;
	int _moveFrameUnit;
	int _clickFrameUnit;

	bool _showCursor;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	//get �Լ� 
	cursorUnit getCursor() { return _cursor; }
	image *getImg() { return _cursor.img; }
	int getIdx() { return _cursor.idx; }
	int getSlotIdx() { return _cursor.slotIdx; }
	int getClickTime() { return _cursor.clickTime; }
	bool getShowCursor() { return _showCursor; }

	//set �Լ� 
	void setSlotIdx(int idx) { _cursor.slotIdx = idx; }
	void setClickTime(int clickTime) { _cursor.clickTime = clickTime; }
	void setShowCursor(bool value) { _showCursor = value; }

	//animation �Լ� 
	void setCursorState(CURSOR_STATE state);	//Ŀ���� ���� setting �Լ�(Ŀ�� �ִϸ��̼� ���濡 ���)
	void animation();							//Ŀ�� �ִϸ��̼� �Լ� 
	void idleAnim();							//Ŀ�� idle �ִϸ��̼� 
	void moveAnim();							//Ŀ�� move �ִϸ��̼� 
	void clickAnim();							//Ŀ�� click �ִϸ��̼� 
};

