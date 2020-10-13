#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "npc.h"

class npcManager : public gameNode
{
private:
	npc* _witch;
	npc* _girl;
	npc* _blackOctopus;
	npc* _masa;
	npc* _redmond;
	npc* _doberman;

	vector<npc*> _npcs;

	bool npcColl;
public:

	HRESULT init(vector<tagTile>& vec);
	void release();
	void update();
	void render();

	void Coll();
};

