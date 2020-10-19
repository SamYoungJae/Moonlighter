#pragma once
#include "itemManager.h"
#include "cursor.h"
#include "selectMenu.h"
#define INVENPOSX	120
#define INVENPOSY	86
#define MAXSLOT		31
#define MAXITEMSLOT	20

//�κ��丮 ���Ժ� Ÿ������ 
enum SLOT
{
	SLOT_ITEM,
	SLOT_WEAPON_LEFT,
	SLOT_WEAPON_RIGHT,
	SLOT_HELMET,
	SLOT_ARMOR,
	SLOT_BOOTS,
	SLOT_RING_UP,
	SLOT_RING_DOWN,
	SLOT_POTION,
	SLOT_MIRROR,
	SLOT_PENDANT,
	SLOT_EMBLEM
};

//�κ��丮 ��Ʈ�ѷ� Ÿ������
enum INVEN_CTRL
{
	INVEN_INVENTORY,
	INVEN_MERCHANT_MIRROR,
	INVEN_MERCHANT_PENDANT,
	INVEN_MERCHANT_EMBLEM
};

//���� ����ü 
typedef struct
{
	SLOT slotType;
	ITEM type;
	int slotIdx;
	bool isEmpty;

}slotUnit;

class inventory
{
private:
	typedef vector<gameItem*> vInven;
	typedef vector<gameItem*>::iterator viInven;

	vInven _vInven;
	viInven _viInven;

private:
	itemManager *_itemManager;				//������ �Ŵ��� Ŭ���� 
	selectMenu *_selectMenu;				//���ø޴� Ŭ���� 
	cursor *_cursor;						//Ŀ�� Ŭ���� 

	gameItem _tempItem;						//�ӽ� ���Ӿ����� ����ü 
	gameItem _itemEmpty;					//����ִ� ������ ����ü 
	gameItem _itemGrabbed;					//���� ����ִ� ������ ����ü 

	slotUnit _invenSlot[MAXSLOT];			//�κ��丮 ���Կ� ����ü 
	INVEN_CTRL _invenCtrl;					//�κ��丮 ��Ʈ�ѷ� 
	POINT _invenPos;						//�κ��丮�޴� ��ġ 

private:
	float _menuMoveSpeed;					//�޴��� �̵��ϴ� �ӵ� 
	int _curWeaponIdx;						//���� ���� ���� ���� �ε��� 
	int _grabTime;							//Ŀ���� ��� �������� ��� Ŭ���ð� 
	int _itemCount;							//���� �����ϰ� �ִ� ������ ���� 

	bool _isGrabbingItem;					//���� �������� ����ִ��� Ȯ���ϴ� ���� 
	bool _isPuttingItem;					//���� �������� �����ִ��� Ȯ���ϴ� ���� 
	bool _grabSoundPlayed;					//��� ���尡 �÷��̵Ǿ����� Ȯ���ϴ� ����(�ߺ� ��� ����)
	bool _canGrab;							//�޴�â�� ���� �� ������ ���� ���� 

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	//get�Լ� 
	vector<gameItem*> getItem() { return _vInven; }			//�κ��丮 ������ ��ȯ 
	itemManager* getItemManager();							//�����۸Ŵ��� Ŭ���� ��ȯ 
	cursor *getCursor() { return _cursor; }					//�κ��丮 Ŀ�� ��ȯ 
	int getWeaponIdx() { return _curWeaponIdx; }			//������ �����ε��� ���� ��ȯ 
	int getMaxItemSlot() { return MAXITEMSLOT; }			//�κ��丮�� ���� ������ �ִ� ������ ���� ��ȯ 
	int getCurItemCount();									//���� �κ��丮�� �����ϰ� �ִ� ������ �� ��ȯ
	gameItem getPotionEquipped();							//���� �����ϰ� �ִ� ���� ������ Ŭ������ ��ȯ 
	gameItem getWeaponEquipped();							//���� �����ϰ� �ִ� ���� ������ Ŭ������ ��ȯ 
	int getCountByIdx(int itemIdx);									//Ư�� �������� ���������� �ε����� ���� ���� ã�Ƽ� ��ȯ 

	//set�Լ� 
	void setWeaponIdx(int index) { _curWeaponIdx = index; }	//�����ϴ� ������ �ε��� ���� �����ϴ� �Լ� 
	void setCanGrab(bool value) { _canGrab = value; }

	//�κ��丮�޴� �̵� ���� �Լ� 
	POINT getInvenPos() { return _invenPos; }				//�κ��丮 ��ġ�� get�Լ�
	void setInvenPosX(int posX) { _invenPos.x = posX; }		//�κ��丮 x��ǥ set�Լ�
	void setInvenPosY(int posY) { _invenPos.y = posY; }		//�κ��丮 y��ǥ set�Լ� 
	void initPos();											//�κ��丮 ��ġ�� �ʱ�ȭ 
	void moveInvenLeft(int destPos);						//�κ��丮�� destPos���� �������� �̵���Ŵ
	void moveInvenRight(int destPos);						//�κ��丮�� destPos���� �������� �̵���Ŵ

	//�κ��丮 �ʱ�ȭ �� ������ ȹ�� ���� �Լ� 
	void initInven();						//�κ��丮 â�� �������� �ʱ�ȭ�ϴ� �Լ� 
	void initInvenSlot();					//�κ��丮 ���� ������ �ʱ�ȭ 	
	void initItemSlot();					//������ ���� �ʱ�ȭ(���� ����)
	void initItem();						//������ �ʱ�ȭ(���Ƿ� �������� �־����)  
	bool addItemToInven(gameItem item);		//�������� ȹ���� �������� �κ��丮�� �߰� 
	void deleteInvenItem();					//�κ��丮 ���Կ� �ִ� �����۵� ���� ���� 
	void syncWithShopInven(vector<gameItem*> vShopInven);	//������ �κ��丮�� ����ȭ�ϴ� �Լ� 

	//Ű�Է� ���� �Լ� 
	void keyInput();						//w,a,s,d(�����¿�) Ű ���� �޾Ƽ� Ŀ�� �����̱� 
	void setInvenCtrl(INVEN_CTRL state);	//�κ��丮 ��Ʈ�ѷ� ���� �Լ� 
	void setMerchantCtrl();					//���� Ŀ���� ����Ű�� ���ξ����ۿ� �°� ��Ʈ�ѷ� ����
	void invenKeyInput();					//�κ��丮 ��Ʈ�ѷ� ������ Ű �Է� 
	void mirrorKeyInput();					//������ �ſ� ��Ʈ�ѷ� ������ Ű �Է� 
	void pendantKeyInput();					//������ ���Ʈ ��Ʈ�ѷ� ������ Ű �Է� 
	void emblemKeyInput();					//������ ���� ��Ʈ�ѷ� ������ Ű �ӷ�
	void leftKeyDown();						//���� Ű �Է� �� Ŀ���� ��ġ�� ���� 
	void rightKeyDown();					//������ Ű �Է� �� Ŀ���� ��ġ�� ���� 
	void upKeyDown();						//���� Ű �Է� �� Ŀ���� ��ġ�� ���� 
	void downKeyDown();						//�Ʒ��� Ű �Է� �� Ŀ���� ��ġ�� ����
	void switchWeapon();					//���� �ٲٱ�(���⸦ �ٲ� �� �ִ� ��Ȳ���� Ȯ���ؼ� ����) 
	void switchWeaponIdx();					//���� ���� �ε����� �ٲٱ� 
	void usePotionEquipped();				//���� ���� ���� ���� ����ϱ� 

	//������ ��� �Լ� 
	void grabItem();							//��ü ������ ��� �Լ� 
	void grabOneItem();							//����� �� �� ���� ������ ��� 
	void grabAllItem();							//����� �� �Ѳ����� ������ ��� 
	void grabOneMoreItem();						//�������� ��� ���� �� �� ���� ������ �� ���
	void putItem();								//��ü ������ ���� �Լ� 
	void putItemOnEmptySlot();					//�� ���Կ� ����ִ� ������ ���� 
	void putItemOnOccupiedSlot();				//�̹� ä���� ���Կ� ����ִ� ������ ���� 
	void putGrabbingItem();						//����ִ� �������� �ִٸ� ���� �ڸ��� �������� 

	//���� �Լ� 
	void cursorRender(HDC hdc);					//Ŀ�� ��� �Լ�
	void invenCursorRender(HDC hdc);			//�κ��丮 �޴��� Ŀ�� ��� 
	void merchantIconRender(HDC hdc);			//���ξ������� ������ �̹��� ��� 
	void selectCursorRender(HDC hdc);			//���� �޴�(��,�ƴϿ�)�� Ŀ�� ��� 
	void pendantCtrlRender(HDC hdc);			//���Ʈ ��Ʈ�ѷ� ���¿� �ʿ��� �̹��� ��� 
	void emblemCtrlRender(HDC hdc);				//���� ��Ʈ�ѷ� ���¿� �ʿ��� �̹��� ���
	void statusRender(HDC hdc);					//�÷��̾� �������ͽ� ��� �Լ� 
	void weaponIconRender(HDC hdc);				//���� ���� ���� ������ ��� �Լ� 
	void itemRender(HDC hdc);					//������ �̹��� ��� �Լ� 
	void itemGrabbedRender(HDC hdc);			//����ִ� ������ �̹��� ��� �Լ� 
	void itemNameRender(HDC hdc);				//�κ��丮 �ϴܿ� ������ �̸��� ����ϴ� �Լ�  
	void itemCountRender(HDC hdc, int count, int destX, int destY);	//�������� ������ ����ϴ� �Լ� 
	void statusNumRender(HDC hdc, int number, int destY);			//�������ͽ� ���� ��� �Լ� 

};

