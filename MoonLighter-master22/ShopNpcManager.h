#pragma once
#include "gameNode.h"
#include "npc.h"

class displayStand;
class ShopNpcManager : public gameNode
{
private:

	int _npcCnt;

	tagPosF _pos;

	vector<npc*> v_npcs;


	displayStand* _displayStand;

	int _npcTime;
	vector<string> _npcName = {
		"����" , "���" , "����յ�" ,"��"
	};
public:
	HRESULT init(displayStand* dis);
	void release();
	void update();
	void render();

	vector<npc*>& getVector() { return v_npcs; }

};

