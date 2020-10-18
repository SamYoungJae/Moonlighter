#pragma once
#include "gameNode.h"
#include "ShopNpcManager.h"
#include "displayStand.h"

#define ITEMDESKCOUNT 4 //���� ����

class shopScene : public gameNode
{
private:
	ShopNpcManager* _npc; // npc�Ŵ���
	displayStand* _displayStand; //������ ���� ����

	RECT GoTownPortal; // �����ΰ��� ��Ż

	bool _visit; //�÷��̾� �湮����
	bool _disMenuOn; // ���Ǹ޴��� �����ֳ� �������ֳ�

	vector <pair<int, int>> v_itemPos; //��������ġ
	vector <pair<int, int>> v_itemShadowPos;//�����۱׸�����ġ

	RECT _desk; // ����
	RECT _stand; // ����
	void ItemPosSet(); // ������ ��ġ ����


	RECT _itemText[4]; // ������ ��ο� �ؽ�Ʈ ��Ʈ
	HFONT hFont; // ������ ���� ��Ʈ
	HFONT oldFont; // ������ ���� ��Ʈ

	animation* _cashRegister; // å�� �� �ݰ�
	animation* _button; // ���� ��ġ ��ư


	vector < pair<float, float>> v_itemMoveSpeed; // ������ ������ �ӵ�, ���ӵ� ����
	
	bool b[4] = { false, }; // ������ ������ true false 

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void PortaltoTown(); // ������ ��Ż
	void PlayerCol(); // �÷��̾� �ȼ��浹 �Լ� 
	void PlayerSell(); // ������ �Ĵ� �Լ�
	void itemInfoUpdate(); // ������ ������������ �˻��� npc�� �ʱ�ȭ��Ű�� �Լ�

	void npcAI(); // npc update ����� ����
	void npcInit(int idx); //npc �ʱ�ȭ�Լ�

	void itemMove(); // ���ǿ� ��ġ�� ������ ������ �Լ�

	void SoundUpdate(); // ���� ������Ʈ

	void backGroundRender(); // ��� �� ���� �����Լ�
	void InterfaceRender(); //��ư �� �������̽� , ������ ���� �Լ�
};

