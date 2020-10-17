#pragma once
#include "singletonBase.h"
#include "itemManager.h"

class animation;
class DungeonMap;

//���â���� ������ ���ʹ� ���ݾִϸ��̼�
typedef struct tagResultEnemyAnimation
{
	animation* attack;
	int frameY;
	float scale;
}RESULTENEMY;

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
	bool _isActivate;			//UI �����Ұ���

	DungeonMap* _mapData;		//�������� �������� �����ʵ����͸� �����Ѵ�
	int _dgFloor;				//�����̾�����
	bool _isEmblemReturn;		//������������ Ȯ��
	bool _isPendantReturn;		//�Ҵ�Ʈ���� / �������� Ȯ��
private:
	vector<RESULTENEMY> _vEnemy;		//���â ���ʹ�
	RESULTENEMY* _killEnemy;				//�÷��̾� ���ο��ʹ�
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
	bool getIsActivate() { return _isActivate; }
	vector<RESULTENEMY> getVEnemy() { return _vEnemy; }
	void pushVEnemy(RESULTENEMY enemy) { _vEnemy.push_back(enemy); }
	void vEnemyClear() { _vEnemy.clear(); }
	RESULTENEMY* getKillEnemy() { return _killEnemy; }
	void setKillEnemy(RESULTENEMY* em) { _killEnemy = em; }
	bool isKillenemy() {
		if (_killEnemy) return true;
		return false;
	} // ų���ʹ̰� �����ϳ�?

	DungeonMap* getMapData() { return _mapData; }
	bool getIsEmblemReturn() { return _isEmblemReturn; }
	bool getIsPendantReturn() { return _isPendantReturn; }
	int getDungeonFloor() { return _dgFloor; }

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
	void setIsActivate(bool isActivate) { _isActivate = isActivate; }

	void plusInDungeonHp(int plusHp);	//�Ű����� ����ŭ ����ü�� ���ϱ� 
	void minusInDungeonHp(int minusHp);	//�Ű����� ����ŭ ����ü�� ���� 
	void addGold(int addValue) { _gold += addValue; }	//�Ű����� ����ŭ ��� ���ϱ� 
	void subGold(int subValue) { _gold -= subValue; if (_gold < 0) _gold = 0; }	//�Ű����� ����ŭ ��� ���� 
	void saveDungeonMap(DungeonMap* data) { _mapData = data; }
	void setIsEmblemReturn(bool value) { _isEmblemReturn = value; }
	void setIsPendantReturn(bool value) { _isPendantReturn = value; }
	void setDungeonFloor(int floor) { _dgFloor = floor; }

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

