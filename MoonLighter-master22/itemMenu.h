#pragma once
// 'I' ��ư�� ������ �޴� on/off 
// 'Q(��)' 'E(��)' ��ư�� ������ �޴� �̵� 
#include "calendar.h"
#include "wishList.h"
#include "inventory.h"
#include "noteBook.h"
#include "singletonBase.h"

#define TAGPOSX			490
#define TAGPOSY			12
#define TAGINITPOSY		50
//#define CALENDARPOSX	130
//#define CALENDARPOSY	92
//#define WISHLISTPOSX	232
//#define WISHLISTPOSY	130
//#define INVENPOSX		120
//#define INVENPOSY		86
//#define NOTEBOOKPOSX	230
//#define NOTEBOOKPOSY	98

enum CTRL_MENU
{
	CTRL_CALENDAR,
	CTRL_WISHLIST,
	CTRL_INVEN,
	CTRL_NOTEBOOK
};

class itemMenu : public singletonBase <itemMenu>
{
private:
	calendar *_calendar;
	wishList *_wishList;
	inventory *_inventory;
	noteBook *_noteBook;

	CTRL_MENU _ctrlState;	//���� ��Ʈ�ѷ� ���� 

	POINT _tagPos;			//����� �±׸޴�(Ķ�������� ��Ʈ�ϱ��� ������ �޴�)�� ��ġ 
	int _tagIdx;			//����� �±׸޴� �ε���(��Ʈ�ѷ��� ���߸� �ӵ��� �� ����) 
	float _menuMoveSpeed;	//�޴�â �̵��ϴ� �ӵ� 
	float _tagMoveSpeed;	//�±׸޴� �̵��ϴ� �ӵ� 

	bool _menuOn;			//�޴�â toggle�� ���� 
	bool _calendarOn;		//Ķ�����޴� ������ toggle ����
	bool _wishListOn;		//���ø���Ʈ�޴� ������ toggle ����
	bool _invenOn;			//�κ��丮�޴� ������ toggle ���� 
	bool _noteBookOn;		//��Ʈ�ϸ޴� ������ toggle ���� 

	bool _openMenu;			//�޴�â ����� ���� 
	bool _closeMenu;		//�޴�â �ݱ�� ���� 
	bool _openTagMenu;		//�±׸޴� ����� ����
	bool _closeTagMenu;		//�±׸޴� �ݱ�� ���� 
	bool _canKeyInput;		//Ű �Է� �ޱ⿩�� ���� 
	bool _movingLeft;		//�޴��� �������� �����̴��� Ȯ���ϴ� ���� 
	bool _movingRight;		//�޴��� ���������� �����̴��� Ȯ���ϴ� ���� 
	bool _leftIconOn;		//���� �޴������� toggle�� ���� 
	bool _rightIconOn;		//���� �޴������� toggle�� ���� 

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	//get�Լ� 
	inventory *getInventory() { return _inventory; }				//�κ��丮 Ŭ���� �������� 
	int getMaxItemSlot() { return _inventory->getMaxItemSlot(); }	//���� ������ �ִ� ������ ���� ��ȯ
	bool getCanKeyInput() { return _canKeyInput; }					//������ �޴� Ű �Է� �ޱ⺯�� �������� 
	
	//set�Լ� 
	void setCurItemCount();			//�����ϰ� �ִ� ������ ������ �����Ϳ� ������Ʈ 
	void setPotionEquipped();		//���� ���� ���� ���� �������� �����Ϳ� ������Ʈ
	void setWeaponIdx();			//���� ���� ������ ���� �ε����� �����Ϳ� ������Ʈ
	void setWeaponEquipped();		//���� ���� ���� ���� �������� �����Ϳ� ������Ʈ 
	void setCanKeyInput(bool value) { _canKeyInput = value; }

	void toggleMenu();						//�޴�â ���� �״��ϱ� 
	void openMenu();						//�޴�â ���� ����
	void closeMenu();						//�޴�â �ݱ� ���� 
	void openTagMenu();						//�±׸޴� ���� ����
	void closeTagMenu();					//�±׸޴� �ݱ� ���� 
	void initMenuPos();						//���޴� ��ġ �ʱ�ȭ 
	void setCtrlState(CTRL_MENU state);		//��Ʈ�ѷ����� ���� 
	void keyInput();						//Ű �Է��� �޾Ƽ� �޴�â ��Ʈ��
	void leftKeyDown();						//����(Q) Ű �Է�  
	void rightKeyDown();					//������(E) Ű �Է�
	void ctrlCalendarInput();				//��Ʈ�ѷ��� Ķ���� ������ �� Ű �Է°��� ���� �̵� 
	void ctrlWishListInput();				//��Ʈ�ѷ��� ���ø���Ʈ ������ �� Ű �Է°��� ���� �̵� 
	void ctrlInvenInput();					//��Ʈ�ѷ��� �κ��丮 ������ �� Ű �Է°��� ���� �̵� 
	void ctrlNoteBookInput();				//��Ʈ�ѷ��� ��Ʈ�� ������ �� Ű �Է°��� ���� �̵�
	void menuMoveLeft(POINT *pos, const int destPos);
	void menuMoveRight(POINT *pos, const int destPos);

	//�����Լ�
	void menuRender(HDC hdc);				//�����۸޴� ���� 
	void tagMenuRender(HDC hdc);			//����� �±׸޴� ���� 
	bool& getOpenMenu() { return _menuOn; }

};
