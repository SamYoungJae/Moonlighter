#include "stdafx.h"
#include "itemManager.h"

//�Ϲ� ������ �ʱ�ȭ 
HRESULT gameItem::init(string itemKey, string nameKey, string desKey, const char* name, int itemIdx, int cheapPrice, int reasonablePrice, int expensivePrice, int outrageousPrice, int maxCount)
{
	//��ü ������ 0���� �ʱ�ȭ 
	memset(&_item, 0, sizeof(_item));

	_item.name = name;
	_item.imgItem = IMAGEMANAGER->findImage(itemKey);
	_item.imgName = IMAGEMANAGER->findImage(nameKey);
	_item.imgDes = IMAGEMANAGER->findImage(desKey);

	_item.type = ITEM_NORMAL;
	_item.priceRange[PRICE_CHEAP] = cheapPrice;
	_item.priceRange[PRICE_REASONABLE] = reasonablePrice;
	_item.priceRange[PRICE_EXPENSIVE] = expensivePrice;
	_item.priceRange[PRICE_OUTRAGEOUS] = outrageousPrice;

	_item.itemIdx = itemIdx;
	_item.count = 1;
	_item.maxCount = maxCount;
	_item.holeAlpha = 255;
	_item.initSpeed = 3.f;
	_item.initAngle = RANDOM->range(PI2);

	return S_OK;
}

//���� ������ �ʱ�ȭ 
HRESULT gameItem::init(string itemKey, string nameKey, string desKey, const char* name, int itemIdx, int potionValue, int cheapPrice, int reasonablePrice, int expensivePrice, int outrageousPrice, int maxCount)
{
	//��ü ������ 0���� �ʱ�ȭ 
	memset(&_item, 0, sizeof(_item));

	_item.name = name;
	_item.imgItem = IMAGEMANAGER->findImage(itemKey);
	_item.imgName = IMAGEMANAGER->findImage(nameKey);
	_item.imgDes = IMAGEMANAGER->findImage(desKey);

	_item.type = ITEM_POTION;
	_item.potionValue = potionValue;
	_item.priceRange[PRICE_CHEAP] = cheapPrice;
	_item.priceRange[PRICE_REASONABLE] = reasonablePrice;
	_item.priceRange[PRICE_EXPENSIVE] = expensivePrice;
	_item.priceRange[PRICE_OUTRAGEOUS] = outrageousPrice;

	_item.itemIdx = itemIdx;
	_item.count = 1;
	_item.maxCount = maxCount;
	_item.holeAlpha = 255;
	_item.initSpeed = 3.f;

	return S_OK;
}

//��� ������ �ʱ�ȭ 
HRESULT gameItem::init(string itemKey, string nameKey, string desKey, const char* name, ITEM type, int itemIdx, int hpValue, int atkValue, int defValue, int spdValue, int cheapPrice, int reasonablePrice, int expensivePrice, int outrageousPrice, int maxCount)
{
	//��ü ������ 0���� �ʱ�ȭ 
	memset(&_item, 0, sizeof(_item));

	_item.name = name;
	_item.imgItem = IMAGEMANAGER->findImage(itemKey);
	_item.imgName = IMAGEMANAGER->findImage(nameKey);
	_item.imgDes = IMAGEMANAGER->findImage(desKey);

	_item.type = type;
	_item.ability[ABILITY_HP] = hpValue;
	_item.ability[ABILITY_ATK] = atkValue;
	_item.ability[ABILITY_DEF] = defValue;
	_item.ability[ABILITY_SPD] = spdValue;

	_item.priceRange[PRICE_CHEAP] = cheapPrice;
	_item.priceRange[PRICE_REASONABLE] = reasonablePrice;
	_item.priceRange[PRICE_EXPENSIVE] = expensivePrice;
	_item.priceRange[PRICE_OUTRAGEOUS] = outrageousPrice;

	_item.itemIdx = itemIdx;
	_item.count = 1;
	_item.maxCount = maxCount;
	_item.holeAlpha = 255;
	_item.initSpeed = 3.f;

	return S_OK;
}

//Ŭ���� �����ؼ� �ʱ�ȭ 
HRESULT gameItem::init(gameItem * copyItem)
{
	_item = copyItem->getItem();
	_item.initAngle = RANDOM->range(PI2);
	return S_OK;
}

void gameItem::render(HDC hdc)
{
	switch (_item.moveState)
	{
	case ITEM_FALL:
		//CAMERAMANAGER->AlphaRender(hdc, _item.imgItem, _item.rc.left, _item.rc.top,_item.holeAlpha);
		CAMERAMANAGER->ZorderAlphaRender(_item.imgItem, _item.itemPos.y, _item.rc.left, _item.rc.top, _item.holeAlpha);
		break;
	default:
		//CAMERAMANAGER->Render(hdc, _item.imgItem, _item.rc.left, _item.rc.top);
		CAMERAMANAGER->ZorderRender(_item.imgItem, _item.itemPos.y, _item.rc.left, _item.rc.top);
		break;
	}
}

void gameItem::moveUpdate(float x, float y)
{
	switch (_item.moveState)
	{
	case ITEM_INIT:
	{
		_item.itemPos.x += cosf(_item.initAngle) * _item.initSpeed;
		_item.itemPos.y -= sinf(_item.initAngle) * _item.initSpeed;

		_item.initSpeed -= 0.1f;
		if (_item.initSpeed <= 0)
		{
			_item.moveState = ITEM_CHECKSTATE;
		}
	}
	break;
	case ITEM_FALL:
		_item.holeAlpha -= 3;
		if (_item.holeAlpha <= 0)
		{
			_item.isPop = true;
		}
		if (getDistance(_item.itemPos.x, _item.itemPos.y, x, y) < 100 && getDistance(_item.itemPos.x, _item.itemPos.y, x, y) > 7)
		{
			_item.holeAlpha = 255;
			_item.moveState = ITEM_FOLLOW;
		}
		break;
	case ITEM_FOLLOW:
	{
		if (getDistance(_item.itemPos.x, _item.itemPos.y, x, y) < 100 && getDistance(_item.itemPos.x, _item.itemPos.y, x, y) > 7)
		{
			float angle = getAngle(_item.itemPos.x, _item.itemPos.y, x, y);
			_item.itemPos.x += cosf(angle) * 2.f;
			_item.itemPos.y -= sinf(angle) * 2.f;
		}

		if (getDistance(_item.itemPos.x, _item.itemPos.y, x, y) >= 100)
		{
			_item.holeAlpha = 255;
			_item.moveState = ITEM_CHECKSTATE;
		}
	}
	break;
	case ITEM_IDLE:
	{
		if (getDistance(_item.itemPos.x, _item.itemPos.y, x, y) < 100 && getDistance(_item.itemPos.x, _item.itemPos.y, x, y) > 7)
		{
			_item.moveState = ITEM_FOLLOW;
		}
	}
	break;
	case ITEM_CHECKSTATE:
	{
	}
	break;
	default:
		break;
	}
	_item.rc = RectMakeCenter(_item.itemPos.x, _item.itemPos.y, 35, 35);
}

bool gameItem::checkCollision(RECT rc)
{
	RECT tempRect;

	if (IntersectRect(&tempRect, &_item.rc, &rc)) return true; 
	else false; 
}

//=============================================================
//	## itemManager ## (�����۸Ŵ���)
//=============================================================

HRESULT itemManager::init()
{
	this->addGameItems();

	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{
}

void itemManager::render(HDC hdc)
{
}

//�Ϲ� ������ �߰� 
void itemManager::addNormalItem(string itemKey, string nameKey, string desKey, const char* name, int itemIdx, int cheapPrice, int reasonablePrice, int expensivePrice, int outrageousPrice, int maxCount)
{
	gameItem *item = new gameItem;
	item->init(itemKey, nameKey, desKey, name, itemIdx,
		cheapPrice, reasonablePrice, expensivePrice, outrageousPrice, maxCount);

	_vItem.push_back(item);
}

//���� ������ �߰� 
void itemManager::addPotionItem(string itemKey, string nameKey, string desKey, const char* name, int itemIdx, int potionValue, int cheapPrice, int reasonablePrice, int expensivePrice, int outrageousPrice, int maxCount)
{
	gameItem *item = new gameItem;
	item->init(itemKey, nameKey, desKey, name, itemIdx, potionValue,
		cheapPrice, reasonablePrice, expensivePrice, outrageousPrice, maxCount);

	_vItem.push_back(item);
}

//��� ������ �߰� 
void itemManager::addEquipmentItem(string itemKey, string nameKey, string desKey, const char* name, ITEM type, int itemIdx, int hpValue, int atkValue, int defValue, int spdValue, int cheapPrice, int reasonablePrice, int expensivePrice, int outrageousPrice, int maxCount)
{
	gameItem *item = new gameItem;
	item->init(itemKey, nameKey, desKey, name, type,
		itemIdx, hpValue, atkValue, defValue, spdValue,
		cheapPrice, reasonablePrice, expensivePrice, outrageousPrice, maxCount);

	_vItem.push_back(item);
}

//���ӿ� ����ϴ� �����۵� �߰��ϴ� �Լ� 
void itemManager::addGameItems()
{
	////�Ϲ� ������ �߰�
	//addNormalItem("richJelly", "name_richJelly", "des_richJelly", "richJelly", RICHJELLY_IDX, 3, 6, 8, 9, 10);
	//addNormalItem("venomJelly", "name_venomJelly", "des_venomJelly", "venomJelly", VENOMJELLY_IDX, 17, 22, 24, 25, 10);
	//addNormalItem("crystal", "name_crystal", "des_crystal", "crystal", CRYSTAL_IDX, 89, 110, 115, 116, 5);
	//addNormalItem("crystal", "name_crystal", "des_crystal", "crystal", CRYSTAL_IDX, 89, 110, 115, 116, 5);

	//addNormalItem("vine", "name_vine", "des_vine", "vine", VINE_IDX, 2, 3, 5, 6, 10);
	//addNormalItem("teethStone", "name_teethStone", "des_teethStone", "teethStone", TEETHSTONE_IDX, 3, 6, 8, 9, 10);
	//addNormalItem("root", "name_root", "des_root", "root", ROOT_IDX, 3, 6, 8, 9, 10);
	//addNormalItem("ironBar", "name_ironBar", "des_ironBar", "ironBar", IRONBAR_IDX, 21, 28, 30, 31, 10);
	//addNormalItem("foundryRests", "name_foundryRests", "des_foundryRests", "foundryRests", FOUNDRYRESTS_IDX, 134, 165, 173, 174, 5);
	//addNormalItem("brokenSword", "name_brokenSword", "des_brokenSword", "brokenSword", BROKENSWORD_IDX, 134, 165, 173, 174, 5);
	//addNormalItem("fabric", "name_fabric", "des_fabric", "fabric", FABRIC_IDX, 224, 275, 288, 289, 5);
	//addNormalItem("hardenedSteel", "name_hardenedSteel", "des_hardenedSteel", "hardenedSteel", HARDENEDSTEEL_IDX, 269, 330, 345, 346, 5);

	////���� ������ �߰� 
	//addPotionItem("hpPotion1", "name_hpPotion1", "des_hpPotion1", "hpPotion1",
	//	POTION1_IDX, 40, 111, 138, 144, 145, 5);
	//addPotionItem("hpPotion2", "name_hpPotion2", "des_hpPotion2", "hpPotion2",
	//	POTION2_IDX, 75, 719, 880, 920, 921, 5);

	////���� ������ �߰� 
	//addEquipmentItem("trainingBow", "name_trainingBow", "des_trainingBow",
	//	"trainingBow", ITEM_WEAPON, TRAININGBOW_IDX, 0, 15, 0, 0, 899, 1100, 1150, 1151, 1);
	//addEquipmentItem("trainingShortSword", "name_trainingShortSword", "des_trainingShortSword",
	//	"trainingShortSword", ITEM_WEAPON, TRAININGSWORD_IDX, 0, 20, 0, 0, 899, 1100, 1150, 1151, 1);

	//�Ϲ� ������ �߰�
	addNormalItem("ǳ���� ����", "name_richJelly", "des_richJelly", "ǳ���� ����", RICHJELLY_IDX, 3, 6, 8, 9, 10);
	addNormalItem("�͵��� ����", "name_venomJelly", "des_venomJelly", "�͵��� ����", VENOMJELLY_IDX, 17, 22, 24, 25, 10);
	addNormalItem("��ȭ ����", "name_crystal", "des_crystal", "��ȭ ����", CRYSTAL_IDX, 89, 110, 115, 116, 5);
	addNormalItem("����", "name_vine", "des_vine", "����", VINE_IDX, 2, 3, 5, 6, 10);
	addNormalItem("�̻���", "name_teethStone", "des_teethStone", "�̻���", TEETHSTONE_IDX, 3, 6, 8, 9, 10);
	addNormalItem("�Ѹ�", "name_root", "des_root", "�Ѹ�", ROOT_IDX, 3, 6, 8, 9, 10);
	addNormalItem("�踷��", "name_ironBar", "des_ironBar", "�踷��", IRONBAR_IDX, 21, 28, 30, 31, 10);
	addNormalItem("�ֹ� ����", "name_foundryRests", "des_foundryRests", "�ֹ� ����", FOUNDRYRESTS_IDX, 134, 165, 173, 174, 5);
	addNormalItem("������ ��", "name_brokenSword", "des_brokenSword", "������ ��", BROKENSWORD_IDX, 134, 165, 173, 174, 5);
	addNormalItem("õ", "name_fabric", "des_fabric", "õ", FABRIC_IDX, 224, 275, 288, 289, 5);
	addNormalItem("��ȭ ��ö", "name_hardenedSteel", "des_hardenedSteel", "��ȭ ��ö", HARDENEDSTEEL_IDX, 269, 330, 345, 346, 5);

	//���� ������ �߰� 
	addPotionItem("HP ���॰", "name_hpPotion1", "des_hpPotion1", "HP ���॰",
		POTION1_IDX, 40, 111, 138, 144, 145, 5);
	addPotionItem("HP ���ॱ", "name_hpPotion2", "des_hpPotion2", "HP ���ॱ",
		POTION2_IDX, 75, 719, 880, 920, 921, 5);

	//���� ������ �߰� 
	addEquipmentItem("�Ʒÿ� Ȱ", "name_trainingBow", "des_trainingBow",
		"�Ʒÿ� Ȱ", ITEM_WEAPON, TRAININGBOW_IDX, 0, 15, 0, 0, 899, 1100, 1150, 1151, 1);
	addEquipmentItem("�Ʒÿ� �ܰ�", "name_trainingShortSword", "des_trainingShortSword",
		"�Ʒÿ� �ܰ�", ITEM_WEAPON, TRAININGSWORD_IDX, 0, 20, 0, 0, 899, 1100, 1150, 1151, 1);

}

gameItem itemManager::getItemByIdx(int idx)
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		if (_vItem[i]->getItemIdx() != idx) continue;

		return *(_vItem[i]);
	}
}
