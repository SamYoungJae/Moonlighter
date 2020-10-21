#pragma once

typedef struct
{
	image *img;
	int animTimer;
	int frameUnit;
	int idx;
	int selectIdx;

}selectMenuUnit;

class selectMenu 
{
private:
	selectMenuUnit _selectMenu;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc, int destX, int destY);

	//get�Լ� 
	image *getImg() { return _selectMenu.img; }
	int getIdx() { return _selectMenu.idx; }
	int getSelectIdx() { return _selectMenu.selectIdx; }

	//set�Լ� 
	void setSelectIdx(int idx) { _selectMenu.selectIdx = idx; }

	//�ִϸ��̼� �Լ�
	void setMenuState(int selectIdx);
	void animation();
	void yesAnim();
	void noAnim();


};

