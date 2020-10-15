#pragma once
#include "gameNode.h"
#include "npc.h"

class displayStand;

// ������ npc �Ŵ���

class ShopNpcManager : public gameNode
{
private:

	int _npcCnt;

	tagPosF _pos;

	vector<npc*> v_npcs;


	displayStand* _displayStand;

	int _npcTime;
	vector<pair<string, bool>> _npcName = {
		make_pair("����" , false),
		make_pair("���" , false),
		make_pair("����յ�" , false),
		make_pair("��" , false)
	};
	/*vector<string> _npcName = {
		"����",
		"���",
		"����յ�",
		"��"
	};*/
public:
	HRESULT init(displayStand* dis);
	void release();
	void update();
	void render();
	void getInit(int idx);

	vector<npc*>& getVector() { return v_npcs; }

};

