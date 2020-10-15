#pragma once
#include "gameNode.h"
#include "npc.h"

class displayStand;

// 상점용 npc 매니저

class ShopNpcManager : public gameNode
{
private:

	int _npcCnt;

	tagPosF _pos;

	vector<npc*> v_npcs;


	displayStand* _displayStand;

	int _npcTime;
	vector<pair<string, bool>> _npcName = {
		make_pair("마사" , false),
		make_pair("토모" , false),
		make_pair("레드먼드" , false),
		make_pair("모리" , false)
	};
	/*vector<string> _npcName = {
		"마사",
		"토모",
		"레드먼드",
		"모리"
	};*/
public:
	HRESULT init(displayStand* dis);
	void release();
	void update();
	void render();
	void getInit(int idx);

	vector<npc*>& getVector() { return v_npcs; }

};

