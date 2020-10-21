#pragma once
#include "itemManager.h"

typedef struct
{
	gameItem item;
	int itemIdx;
	int count;
	int possession;

}materialUnit;

class material
{
private:
	materialUnit _material;

public:
	//��� �ʱ�ȭ 
	HRESULT init(int itemIdx, int count);
	void release();
	void update();
	void render(HDC hdc);

	//get�Լ� 
	gameItem getItem() { return _material.item; }
	int getCount() { return _material.count; }
	int updatePossession();

	//set�Լ� 
	void setCount(int count) { _material.count = count; }
	void setPossession(int count) { _material.possession = count; }

};

class recipe
{
private:
	typedef vector<material*> vMaterial;
	vMaterial _vMaterial;

private:
	char _materialName[64];

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc, int destX, int destY);

	//get�Լ� 
	vector<material*> getMeterial() { return _vMaterial; }

	void addMaterial(int itemIdx, int count);		//�����ǿ� ��� �߰��ϱ� 
	bool checkMaterialOX(int index);				//�ش� ����� ������������ Ȯ��
	bool checkRequirements();						//��ü ����� ������������ Ȯ�� 
	int getMaxProduceBasedOnMaterial();				//���� ���� ��Ḧ ������� �ִ��������� ���ϱ� 
	const char *getShortMaterialName();				//������ ����� �̸� �ޱ� 

	//�����Լ� 
	void recipeIconRender(HDC hdc, int destX, int destY);
	void recipeTextRender(HDC hdc, int destX, int destY);
	void recipeOXIconRender(HDC hdc, int destX, int destY);
	void recipeCountRender(HDC hdc, int destX, int destY);
	void countRender(HDC hdc, int destX, int destY, int count);
};

