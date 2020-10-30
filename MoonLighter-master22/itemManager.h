#pragma once
#include "csvload.h"

#define MAXITEM	16

//�������� ���� 
enum ITEM
{
	ITEM_EMPTY,		//�� ������ 
	ITEM_NORMAL,	//��� ������ 
	ITEM_WEAPON,	//���� ������ 
	ITEM_HELMET,	//���� ������ 
	ITEM_ARMOR,		//���� ������ 
	ITEM_BOOTS,		//���� ������ 
	ITEM_RING,		//���� ������	
	ITEM_POTION		//���� ������ 
};

//�������� �ɷ�ġ  
enum ABILITY
{
	ABILITY_HP,		//ü�� 
	ABILITY_ATK,	//���ݷ�
	ABILITY_DEF,	//���� 
	ABILITY_SPD		//���ǵ�
};

//�������� ���ݹ��� 
enum PRICE_RANGE
{
	PRICE_CHEAP,		//������
	PRICE_REASONABLE,	//�ո�����
	PRICE_EXPENSIVE,	//���
	PRICE_OUTRAGEOUS	//�͹��Ͼ���
};

//�������� �α���� 
enum POPULARITY
{
	POPULARITY_LOW = -1,		//�α� ����
	POPULARITY_AVERAGE = 0,		//�����
	POPULARITY_HIGH = 1,		//�α� ����  
};

enum ITEMMOVESTATE
{
	ITEM_INIT,ITEM_FALL,ITEM_FOLLOW,ITEM_IDLE,ITEM_CHECKSTATE
};

typedef struct
{
	image *imgItem;			//������ �̹��� 
	image *imgName;			//������ �̸� �̹��� 
	image *imgDes;			//������ ���� �̹��� 
	RECT rc;				//������ RECT
	ITEM type;				//������ ����
	const char* name;		//������ �̸�(��� �ÿ� ���)
	POINT itemPos;			//������ ��ǥ��(���� ��� ������ �� ���)
	int invenPosIdx;		//������ �κ��丮 �ε�����(�κ��丮 ���� ���� ���� ��ġ��)
	int itemIdx;			//�������� �ε�����(�����ϰ� �������� �̾Ƴ��ų� ��Ʈ�Ͽ� ���)
	int potionValue;		//�������� ������ �� ü�� ȸ����
	int ability[4];			//�������� ����� �� �������� �ɷ�ġ�� (0.hp/1.atk/2.def/3.spd) 
	int priceRange[4];		//�������� ���� ���� (0.������/1.�ո�����/2.���/3.�͹��Ͼ���)
	int price;				//�������� ����(�������� �Ǹ��ϴ� ����)
	int popularity;			//������ �Ǹ� ���� �α����(-1.�α����/0.�����/1.�α��ִ�)
	int count;				//������ ���� 
	int maxCount;			//�� ĭ�� ���Կ� ���� ������ �ִ� ������ ���� 
	bool isObtained;		//�������� ���� ȹ�濩�� (false.ȹ����������/true.ȹ����) 
	//===========================================================================
	ITEMMOVESTATE moveState;	// ������ �����ӻ���
	int holeAlpha;				// ������ ���ķ���
	float initSpeed;			// ����ƥ�� ���ǵ�
	float initAngle;			// ������ ����
	bool isPop;					// Ȧ�� �������� ���Ұų�?

}itemUnit;

class gameItem
{
private:
	itemUnit _item;

public:
	//�Ϲ� ������ �ʱ�ȭ 
	HRESULT init(string itemKey, string nameKey, string desKey, const char* name, int itemIdx,
		int cheapPrice, int reasonablePrice, int expensivePrice, int outrageousPrice, int maxCount);
	//���� ������ �ʱ�ȭ 
	HRESULT init(string itemKey, string nameKey, string desKey, const char* name, int itemIdx, int potionValue,
		int cheapPrice, int reasonablePrice, int expensivePrice, int outrageousPrice, int maxCount);
	//��� ������ �ʱ�ȭ 
	HRESULT init(string itemKey, string nameKey, string desKey, const char* name,
		ITEM type, int itemIdx, int hpValue, int atkValue, int defValue, int spdValue,
		int cheapPrice, int reasonablePrice, int expensivePrice, int outrageousPrice, int maxCount);
	//Ŭ���� �����ϱ� 
	HRESULT init(gameItem *copyItem);

	void render(HDC hdc);
	void moveUpdate(float x, float y);				//������ �̵� �Լ� 
	bool checkCollision(RECT rc);					//������ �浹 Ȯ�� �Լ� 

	//get�Լ� 
	itemUnit getItem() { return _item; }
	image *getItemImg() { return _item.imgItem; }
	image *getNameImg() { return _item.imgName; }
	image *getDesImg() { return _item.imgDes; }
	RECT getRect() { return _item.rc; }
	ITEM getType() { return _item.type; }
	const char* getName() { return _item.name; }
	POINT getPos() { return _item.itemPos; }

	int& getInvenPosIdx() { return _item.invenPosIdx; }
	int& getItemIdx() { return _item.itemIdx; }
	int& getPotionValue() { return _item.potionValue; }
	int *getAbility() { return _item.ability; }
	int *getPriceRange() { return _item.priceRange; }
	int& getPrice() { return _item.price; }
	int& getPopularity() { return _item.popularity; }
	int& getCount() { return _item.count; }
	int& getMaxCount() { return _item.maxCount; }
	bool getIsObtained() { return _item.isObtained; }

	//set�Լ� 
	void setType(ITEM type) { _item.type = type; }
	void setInvenPosIdx(int index) { _item.invenPosIdx = index; }
	void setPrice(int price) { _item.price = price; }
	void addPrice(int addValue) { _item.price += addValue; }
	void subPrice(int subValue) { _item.price -= subValue; }	
	void setCount(int count) { _item.count = count; }
	void plusOneCount() { _item.count++; }				//������ ���� +1
	void minusOneCount() { _item.count--; }				//������ ���� -1
	void setItemPos(POINT pt) { _item.itemPos = pt; }
	void setItemMoveState(ITEMMOVESTATE state) { _item.moveState = state; }
};

class itemManager
{
private:
	typedef vector<gameItem*> vItem;
	typedef vector<gameItem*>::iterator viItem;
	int _cnt;

private:
	vItem _vItem;
	unordered_map<int, ::Item> m_itemData;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	//�Ϲ� ������ �߰� 
	void addNormalItem(string itemKey, string nameKey, string desKey, const char* name, int itemIdx,
		int cheapPrice, int reasonablePrice, int expensivePrice, int outrageousPrice, int maxCount);
	//���� ������ �߰� 
	void addPotionItem(string itemKey, string nameKey, string desKey, const char* name, int itemIdx,
		int potionValue, int cheapPrice, int reasonablePrice, int expensivePrice, int outrageousPrice, int maxCount);
	//��� ������ �߰� 
	void addEquipmentItem(string itemKey, string nameKey, string desKey, const char* name,
		ITEM type, int itemIdx, int hpValue, int atkValue, int defValue, int spdValue,
		int cheapPrice, int reasonablePrice, int expensivePrice, int outrageousPrice, int maxCount);

	void csvItemDataLoad(string path, CSVITEMTYPE _type);

	//���ӿ� ����ϴ� �����۵� �߰��ϴ� �Լ� 
	void addGameItems();
	gameItem getItemByIdx(int idx);

	//������ Ŭ���� ����ִ� ���� ��������
	vector<gameItem*> getItem() { return _vItem; }
};

