#pragma once
#include "gameNode.h"
#include "itemManager.h"
#include "cursor.h"
#define SHOPINVENPOSX	100
#define SHOPINVENPOSY	86
#define DISPLAYPOSX		658
#define DISPLAYPOSY		142
#define MAXSHOPSLOT		28
#define MAXDIGIT		7
#define MAXPRICE		9999999

//���� ��Ʈ�ѷ�(�κ��丮 or ����å��) 
enum SHOP_CTRL
{
	CTRL_INVENTORY,
	CTRL_PRICE
};

//���� �̹��� ���� 
enum COLOR_TYPE
{
	COLOR_BLACK,
	COLOR_WHITE
};

//���� �κ��丮 ������ Ÿ�� 
enum SHOPSLOT
{
	SLOT_INVEN,
	SLOT_DISPLAY,
	SLOT_PRICE
};

//���� ���� ����ü 
typedef struct
{
	SHOPSLOT slotType;
	ITEM type;
	int slotIdx;
	bool isEmpty;

}shopSlot;

//���� Ŀ�� ����ü 
typedef struct
{
	image *img;				//Ŀ�� �̹��� 
	int posIdx;				//Ŀ���� ��ġ �ε��� 
	int digit[MAXDIGIT];	//�ڸ��������� ���� 

}priceCursor;

class displayStand : public gameNode
{
private:
	typedef vector<gameItem*> vShopInven;
	typedef vector<gameItem*>::iterator viShopInven;

	vShopInven _vShopInven;
	viShopInven _viShopInven;

private:
	cursor *_cursor;					//�޴� �̵� Ŀ�� 
	shopSlot _shopSlot[MAXSHOPSLOT];	//���� ����ü 
	priceCursor _priceCursor;			//����å�� �� �̵� Ŀ�� 
	SHOP_CTRL _shopCtrl;				//���� ��Ʈ�ѷ�(�κ��丮/����å��)

	gameItem _itemEmpty;				//�� ������ ����ü 
	gameItem _itemGrabbed;				//��� �ִ� ������ ����ü 

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
	void initInvenItem();			//�κ��丮 ������ �ʱ�ȭ(���Ǵ븦 �� ������ ����)
	void deleteInvenItems();		//�κ��丮�� �ִ� ������ ���� ���� 
	gameItem getDisplayOne();		//���Ǵ��� ����1 ��ȯ
	gameItem getDisplayTwo();		//���Ǵ��� ����2 ��ȯ 
	gameItem getDisplayThree();		//���Ǵ��� ����3 ��ȯ 
	gameItem getDisplayFour();		//���Ǵ��� ����4 ��ȯ 

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

	//����å�� ���� �Լ� 
	void setPriceUp();				//���� �ø���
	void setPriceDown();			//���� ������ 
	void saveLastPrice();			//�ش� �����ۿ� ���������� å���� ���ݰ� �����ϱ� 
	void loadLastPrice(int index);	//�ε��� ��ġ�� �����ۿ� ���������� å���� ���ݰ� �޾ƿ��� 

	//���� �Լ� 
	void menuRender();				//�޴� �̹��� ��� 
	void cursorRender();			//Ŀ�� �̹��� ��� 
	void priceCursorRender();		//���� Ŀ�� �̹��� ���(ȭ��ǥ)
	void itemRender();				//������ �̹��� ��� 
	void itemGrabbedRender();		//���� ��� �ִ� ������ �̹��� ��� 
	void itemNameRender();			//���� Ŀ���� ����Ű�� ������ �̸� ��� 
	void displayCountRender();		//���Ǵ뿡 �ִ� �������� ���� ��� 
	void unitPriceRender();			//������ �� ���� ���� ��� 
	void totalPriceRender();		//������ ���� x ������ ����� �� ���� ��� 
	void countRender(int count, int destX, int destY, COLOR_TYPE colorIdx);	//������ ī��Ʈ ��� 
	void greenCountRender(int count, int destX, int destY);					//������ ī��Ʈ ���(���λ�)
	void priceCountRender(int count, int destX, int destY);

};

