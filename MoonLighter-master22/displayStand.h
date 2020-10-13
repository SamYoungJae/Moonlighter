#pragma once
#include "gameNode.h"
#include "itemManager.h"
#include "cursor.h"
#define SHOPINVENPOSX	100
#define SHOPINVENPOSY	86
#define DISPLAYPOSX		658
#define DISPLAYPOSY		142
#define MAXSHOPSLOT		28

enum SHOP_CTRL
{
	CTRL_INVENTORY,
	CTRL_PRICE
};

enum COLOR_TYPE
{
	COLOR_BLACK,
	COLOR_WHITE
};

enum SHOPSLOT
{
	SLOT_INVEN,
	SLOT_DISPLAY,
	SLOT_PRICE
};

typedef struct
{
	SHOPSLOT slotType;
	ITEM type;
	int slotIdx;
	bool isEmpty;

}shopSlot;

class displayStand : public gameNode
{
private:
	typedef vector<gameItem*> vShopInven;
	typedef vector<gameItem*>::iterator viShopInven;

	vShopInven _vShopInven;
	viShopInven _viShopInven;

private:
	cursor *_cursor;
	shopSlot _shopSlot[MAXSHOPSLOT];
	SHOP_CTRL _shopCtrl;

	gameItem _tempItem;
	gameItem _itemEmpty;
	gameItem _itemGrabbed;

	gameItem _displayItem1;
	gameItem _displayItem2;
	gameItem _displayItem3;
	gameItem _displayItem4;

	POINT _shopInvenPos;
	POINT _displayPos;

	float _menuMoveSpeed;
	int _grabTime;
	int _itemPrice[MAXITEM];

	bool _menuOn;
	bool _openMenu;
	bool _closeMenu;

	bool _isGrabbingItem;
	bool _isPuttingItem;
	bool _grabSoundPlayed;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//�޴� ���� �ݴ� �Լ� 
	void openDisplayStand();								//�������Ǵ� ���� 
	void closeDisplayStand();								//�������Ǵ� �ݱ� 
	void toggleMenu();										//�׽�Ʈ�� �޴� on/off Ű �Է��� �޴� �Լ� 
	void initMenuPos();										//�� �޴��� ��ġ�� �ʱ�ȭ�ϴ� �Լ�
	void openMenu();										//�޴� ���� �Լ� 
	void closeMenu();										//�޴� �ݱ� �Լ� 
	void menuMoveLeft(POINT *pos, const int destPos);		//��ġ���� �޾� �������� ���� �̵�
	void menuMoveRight(POINT *pos, const int destPos);		//��ġ���� �޾� �������� ������ �̵�
	void menuMoveUp(POINT *pos, const int destPos);			//��ġ���� �޾� �������� ���� �̵�
	void menuMoveDown(POINT *pos, const int destPos);		//��ġ���� �޾� �������� �Ʒ��� �̵� 

	//���� �κ��丮 ���� �Լ� 
	void initShopSlot();			//������ ���� ���� �ʱ�ȭ 
	void initInvenSlot();			//�κ��丮 ���� �ʱ�ȭ(���Ǵ븦 �� ������ ����)
	void initInvenItem();			//�κ��丮 ������ ����ȭ(���Ǵ븦 �� ������ ����)
	void deleteInvenItems();		//�κ��丮�� �ִ� ������ ���� ���� 

	//Ű �Է� �Լ� 
	void setShopCtrl(SHOP_CTRL state);	//���� ��Ʈ�ѷ� ���� �Լ� 
	void keyInput();					//��ü Ű �Է� ���� 
	void invenKeyInput();				//�κ��丮 Ű �Է� ���� 
	void priceKeyInput();				//����å�� Ű �Է� ���� 
	void leftKeyDown();					//���� Ű(A) �Է� �Լ�
	void rightKeyDown();				//������ Ű(D) �Է� �Լ� 
	void upKeyDown();					//���� Ű(W) �Է� �Լ� 
	void downKeyDown();					//�Ʒ��� Ű(S) �Է� �Լ� 

	//������ ��� �� ���� �Լ� 
	void grabItem();
	void grabOneItem();
	void grabAllItem();
	void grabOneMoreItem();
	void putItem();
	void putItemOnEmptySlot();
	void putItemOnOccupiedSlot();

	//���� �Լ� 
	void menuRender();
	void cursorRender();
	void itemRender();
	void itemGrabbedRender();
	void itemNameRender();
	void itemCountRender(int count, int destX, int destY, COLOR_TYPE colorIdx);
	void greenCountRender(int count, int destX, int destY);
	void displayCount();
};

