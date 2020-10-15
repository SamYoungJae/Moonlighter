#include "stdafx.h"
#include "ShopNpcManager.h"
HRESULT ShopNpcManager::init(displayStand* dis)
{
	_npcCnt = 0;

	_pos.x = 660;
	_pos.y = 830;

	v_npcs.resize(MAX_NPC);

	_npcTime = 0;
	_displayStand = dis;

	random_shuffle(_npcName.begin(), _npcName.end());

	for (int i = 0; i < MAX_NPC; i++)
	{
		v_npcs[i] = new npc;
		v_npcs[i]->init(_pos, _npcName[i].first, NPC_SHOP, i, _displayStand);
		_npcName[i].second = false;
	}
	return S_OK;
}

void ShopNpcManager::release()
{
	for (int i = 0; i < MAX_NPC; i++)
	{
		v_npcs[i]->release();
		SAFE_DELETE(v_npcs[i]);
	}
}

void ShopNpcManager::update()
{

	for (int i = 0; i < MAX_NPC; i++)
	{
		v_npcs[i]->collision(); // npc �浹��Ʈ ������Ʈ

	}

}

void ShopNpcManager::render()
{

}

void ShopNpcManager::getInit(int idx)
{
	v_npcs[idx]->init(_pos, _npcName[idx].first, NPC_SHOP, idx, _displayStand);
}

