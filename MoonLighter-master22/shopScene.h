#pragma once
#include "gameNode.h"
#include "ShopNpcManager.h"
#include "displayStand.h"

#define ITEMDESKCOUNT 4
class shopScene : public gameNode
{
private:
	ShopNpcManager* _npc; // npc�Ŵ���
	displayStand* _displayStand; //������ ���� ����

	RECT GoTownPortal; // �����ΰ��� ��Ż

	int _npcTime;
	bool _visit; //�÷��̾� �湮����

	vector <pair<int, int>> v_itemPos; //��������ġ
	vector <pair<int, int>> v_itemShadowPos;//�����۱׸�����ġ

	RECT _desk;
	void ItemPosSet(); // ������ ��ġ ����

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void PortaltoTown(); // ������ ��Ż
	void PlayerCol(); // �÷��̾� �ȼ��浹 �Լ� 
	void PlayerSell(); // ������ �Ĵ� �Լ�

	void npcAI(); // npc update ����� ����
};

