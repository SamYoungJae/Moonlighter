#pragma once
#include "singletonBase.h"
#include "itemManager.h"

class playerData : public singletonBase <playerData>
{
private:
	int _defaultHp;				//�÷��̾� ����Ʈ ü�� 
	int _defaultAtk;			//�÷��̾� ����Ʈ ���ݷ� 
	int _defaultDef;			//�÷��̾� ����Ʈ ���� 
	int _defaultSpd;			//�÷��̾� ����Ʈ ���ǵ� 

	int _hp;					//��� �ɷ°� �ݿ��� ü�� 
	int _atk;					//��� �ɷ°� �ݿ��� ���ݷ�  
	int _def;					//��� �ɷ°� �ݿ��� ���� 
	int _spd;					//��� �ɷ°� �ݿ��� ���ǵ� 

	int _inDungeonHp;			//�������� ����ϴ� ü�� 
	int _hpBarLength;			//ü�¹��� �� ���� 

	int _gold;					//������ 
	int _itemCount;				//���� �����ϰ� �ִ� ������ ���� 
	int _weaponIdx;				//���� ������ �Ǿ��ִ� ������ �ε���(1 or 2)
	float _x, _y;

	bool _isInDungeon;			//�÷��̾ ������ �ִ��� ���� Ȯ��

private:
	gameItem _potionEquipped;	//���� ���� ���� ���� ������ 
	gameItem _weaponEquipped;	//���� ���� ���� ���� ������ 

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void initPlayerStatus();		//�÷��̾� ���Ȱ� �ʱ�ȭ 
	void initDungeonHp();			//���� HP�� �ʱ�ȭ 

	//get�Լ� 
	const int getDefaultHp() { return _defaultHp; }
	const int getDefaultAtk() { return _defaultAtk; }
	const int getDefaultDef() { return _defaultDef; }
	const int getDefaultSpd() { return _defaultSpd; }
	int getHp() { return _hp; }
	int getAtk() { return _atk; }
	int getDef() { return _def; }
	int getSpd() { return _spd; }
	int getInDungeonHp() { return _inDungeonHp; }
	int getGold() { return _gold; }
	int getItemCount() { return _itemCount; }
	float getX() { return _x; }
	float getY() { return _y; }
	bool getIsInDungeon() { return _isInDungeon; }

	//set�Լ� 
	void setHp(int hp) { _hp = hp; }
	void setAtk(int atk) { _atk = atk; }
	void setDef(int def) { _def = def; }
	void setSpd(int spd) { _spd = spd; }
	void setInDungeonHp(int hp) { _inDungeonHp = hp; }
	void setGold(int gold) { _gold = gold; }
	void setItemCount(int itemCount) { _itemCount = itemCount; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setIsInDungeon(bool value) { _isInDungeon = value; }
	void setPotionEquipped(gameItem item) { _potionEquipped = item; }
	void setWeaponIdx(int index) { _weaponIdx = index; }
	void setWeaponEquipped(gameItem item) { _weaponEquipped = item; }

	//ü�� ���� �Լ� 
	void plusInDungeonHp(int plusHp);
	void minusInDungeonHp(int minusHp);

	//�������̽� �����Լ� 
	void goldRender(HDC hdc);					//���� �����ϰ� �ִ� ��� ��� 
	void goldCountRender(HDC hdc);				//���� �����ϰ� �ִ� ��� ī��Ʈ ��� 
	void hpRender(HDC hdc);						//�÷��̾� ü�� ��� 
	void hpGaugeRender(HDC hdc);				//�÷��̾� ���� ü��(������) ��� 
	void hpCountRender(HDC hdc, int currentHp);	//�÷��̾� ü�� ī��Ʈ ��� 
	void equipInfoRender(HDC hdc);				//ȭ�� ������ �������� ��� 
	void itemCountRender(HDC hdc);				//������ ���� ���� �� �ִ� ���� ���� ��� 
	void weaponEquippedRender(HDC hdc);			//���� �������� ���� ��� 
	void potionEquippedRender(HDC hdc);			//���� �������� ���� ��� 
};

