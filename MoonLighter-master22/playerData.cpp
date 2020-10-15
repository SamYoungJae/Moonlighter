#include "stdafx.h"
#include "playerData.h"

HRESULT playerData::init()
{
	initPlayerStatus();
	initDungeonHp();
	_isActivate = true;
	
	_killEnemy = nullptr;

	return S_OK;
}

void playerData::release()
{
}

void playerData::update()
{
}

void playerData::render(HDC hdc)
{
	if (!_isActivate) return;
	//���� UI ���
	goldRender(hdc);
	hpRender(hdc);


	//���� UI ��� 
	equipInfoRender(hdc);
}

void playerData::initPlayerStatus()
{
	_defaultHp = 100;
	_defaultAtk = 5;
	_defaultDef = 10;
	_defaultSpd = 185;

	_hp = _defaultHp;
	_atk = _defaultAtk;
	_def = _defaultDef;
	_spd = _defaultSpd;

	_hpBarLength = 130;

	_gold = 5000;

	_itemCount = 0;

	_isInDungeon = true;
}

void playerData::initDungeonHp()
{
	_inDungeonHp = _hp;
}

void playerData::plusInDungeonHp(int plusHp)
{
	_inDungeonHp += plusHp;

	if (_inDungeonHp > _hp) _inDungeonHp = _hp;
}

void playerData::minusInDungeonHp(int minusHp)
{
	_inDungeonHp -= minusHp;

	if (_inDungeonHp < 0) _inDungeonHp = 0;
}

void playerData::goldRender(HDC hdc)
{
	//��� �ָӴ� �� ���� ������ ��� 
	IMAGEMANAGER->render("icon_goldPouch", hdc, 20, 24);
	IMAGEMANAGER->render("icon_coin", hdc, 20, 106);

	//��� ī��Ʈ ��� 
	goldCountRender(hdc);
}

void playerData::goldCountRender(HDC hdc)
{
	//�ڸ����� �°� ù ��° ���ں��� ��� 

	int multiplyCount = 0;
	int gold = _gold;

	while (true)
	{
		if (gold / 10 != 0)
		{
			gold /= 10;
			multiplyCount++;
		}
		else break; 
	}
	  
	for (int i = 1; i <= _gold; i *= 10)
	{
		int num = (_gold / i) % 10;

		char keyName[24];
		wsprintf(keyName, "%d_white_small", num);
		IMAGEMANAGER->render(keyName, hdc, 46 + (multiplyCount * 8), 108);

		multiplyCount--;
	}
}

void playerData::hpRender(HDC hdc)
{
	//hp��(���) �̹��� ��� 
	IMAGEMANAGER->render("hp_barBack", hdc, 156, 34);

	//hp��(������) �̹��� ��� 
	hpGaugeRender(hdc);

	//hp������ �̹��� ��� 
	IMAGEMANAGER->render("icon_hp", hdc, 112, 26);
}

void playerData::hpGaugeRender(HDC hdc)
{
	//���� ���� �ȿ� �ִٸ� �δ��� ü�� ��� 
	if (_isInDungeon)
	{
		float currentGauge = (_hpBarLength * _inDungeonHp) / _hp;

		//cout << currentGauge << endl; 

		IMAGEMANAGER->render("hp_barFront", hdc, 156, 34, 0, 0, (int)currentGauge, 24);
		hpCountRender(hdc, _inDungeonHp);
	}
	//���� �ٱ��� �ִٸ� ��� �ɷ�ġ�� �ݿ��� ü�� ���(Ǯü��) 
	else
	{
		IMAGEMANAGER->render("hp_barFront", hdc, 156, 34);
		hpCountRender(hdc, _hp);
	}
}

void playerData::hpCountRender(HDC hdc, int currentHp)
{
	//���� ü�� ��� 
	for (int i = 1, distance = 0; i <= currentHp; i *= 10)
	{
		int num = (currentHp / i) % 10;

		char keyName[24];
		wsprintf(keyName, "%d_white_small", num);
		IMAGEMANAGER->render(keyName, hdc, 248 - (distance * 8), 64);

		distance++;
	}

	//������ ��� 
	IMAGEMANAGER->render("slash_white_small", hdc, 256, 64);

	//��ü ü�� ��� 
	for (int i = 1, distance = 0; i <= _hp; i *= 10)
	{
		int num = (_hp / i) % 10;

		char keyName[24];
		wsprintf(keyName, "%d_white_small", num);
		IMAGEMANAGER->render(keyName, hdc, 280 - (distance * 8), 64);

		distance++;
	}
}

void playerData::equipInfoRender(HDC hdc)
{
	//�������� ���� ��� 
	weaponEquippedRender(hdc);

	IMAGEMANAGER->render("interface_key", hdc, 1084, 8);
	IMAGEMANAGER->render("icon_bag", hdc, 1168, 166);

	//�������� ���� ��� 
	potionEquippedRender(hdc);

	//������ ���� ��� 
	itemCountRender(hdc);
}

void playerData::itemCountRender(HDC hdc)
{
	//���� �����ϰ� �ִ� ������ ���� ��� 
	for (int i = 1, distance = 0; i <= _itemCount; i *= 10)
	{
		int num = (_itemCount / i) % 10;

		char keyName[24];
		wsprintf(keyName, "%d_white_small", num);
		IMAGEMANAGER->render(keyName, hdc, 1206 - (distance * 8), 242);

		distance++;
	}

	//������ ��� 
	IMAGEMANAGER->render("slash_white_small", hdc, 1214, 242);

	//�ִ� ���������� ������ ���� ��� 
	for (int i = 1, distance = 0; i <= PLAYER->getMaxItemSlot(); i *= 10)
	{
		int num = (PLAYER->getMaxItemSlot() / i) % 10;

		char keyName[24];
		wsprintf(keyName, "%d_white_small", num);
		IMAGEMANAGER->render(keyName, hdc, 1230 - (distance * 8), 242);

		distance++;
	}
}

void playerData::weaponEquippedRender(HDC hdc)
{
	//���� ����(�ĸ�) ��� 
	IMAGEMANAGER->frameRender("weapon_slot", hdc, 1132, 60, 1, 0);
	
	switch (_weaponIdx)
	{
		case 1:
			IMAGEMANAGER->frameRender("weapon_backIdx", hdc, 1132, 68, 1, 0);
			break;

		case 2: 
			IMAGEMANAGER->frameRender("weapon_backIdx", hdc, 1132, 68, 0, 0);
			break; 
	}

	//���� ����(����) ��� 
	IMAGEMANAGER->frameRender("weapon_slot", hdc, 1146, 60, 0, 0);

	switch (_weaponIdx)
	{
		case 1:
			IMAGEMANAGER->frameRender("weapon_frontIdx", hdc, 1146, 68, 0, 0);
			break;

		case 2:
			IMAGEMANAGER->frameRender("weapon_frontIdx", hdc, 1146, 68, 1, 0);
			break;
	}

	//���⸦ ���� ���̶�� ���� �̹��� ��� 
	if (_weaponEquipped.getType() != ITEM_WEAPON) return; 

	_weaponEquipped.getItemImg()->render(hdc, 1192, 70);
}

void playerData::potionEquippedRender(HDC hdc)
{
	//���� ���� ���Կ� ���� ���� �������� ���ٸ� �Լ� ����
	if (_potionEquipped.getType() == ITEM_POTION)
	{
		//���� �̹��� ��� 
		_potionEquipped.getItemImg()->render(hdc, 1234, 20);

		//���� ���� ��� 
		for (int i = 1; i <= _potionEquipped.getCount(); i *= 10)
		{
			int num = (_potionEquipped.getCount() / i) % 10;

			char keyName[24];
			wsprintf(keyName, "%d_white_small", num);
			IMAGEMANAGER->render(keyName, hdc, 1238, 50);
		}
	}
}

