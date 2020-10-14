#include "stdafx.h"
#include "npcManager.h"

HRESULT npcManager::init(vector<tagTile>& vec)
{
	
	IMAGEMANAGER->addFrameImage("npc��ǳ��", "Images/npc/talkBox.bmp", 450, 180, 1, 1);
	IMAGEMANAGER->addFrameImage("npc��ȭ", "Images/npc/���ϱ�.bmp", 363, 50, 3, 1);

	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i].key == "������") {
			_witch = new npc;
			_witch->init(tagPosF(vec[i].rc.left, vec[i].rc.top), vec[i].key);
			_npcs.push_back(_witch);
		}
		if (vec[i].key == "���")
		{
			_girl = new npc;
			_girl->init(tagPosF(vec[i].rc.left, vec[i].rc.top), vec[i].key);
			_npcs.push_back(_girl);
		}
		if (vec[i].key == "��")
		{
			_blackOctopus = new npc;
			_blackOctopus->init(tagPosF(vec[i].rc.left, vec[i].rc.top), vec[i].key);
			_npcs.push_back(_blackOctopus);
		}
		if (vec[i].key == "����")
		{
			_masa = new npc;
			_masa->init(tagPosF(vec[i].rc.left, vec[i].rc.top), vec[i].key);
			_npcs.push_back(_masa);
		}
		if (vec[i].key == "����յ�")
		{
			_redmond = new npc;
			_redmond->init(tagPosF(vec[i].rc.left, vec[i].rc.top), vec[i].key);
			_npcs.push_back(_redmond);
		}
		if (vec[i].key == "������npc")
		{
			_doberman = new npc;
			_doberman->init(tagPosF(vec[i].rc.left, vec[i].rc.top), vec[i].key);
			_npcs.push_back(_doberman);
		}
	
	}
	
	npcColl = false;

	return S_OK;
}

void npcManager::release()
{
	SAFE_DELETE(_witch);
	SAFE_DELETE(_girl);
	SAFE_DELETE(_blackOctopus);
	SAFE_DELETE(_redmond);
	SAFE_DELETE(_masa);
	SAFE_DELETE(_doberman);
}

void npcManager::update()
{

	for (int i = 0; i < _npcs.size(); i++)
	{
		if(_npcs[i]->getKey() != "������npc")
		_npcs[i]->update();

		_npcs[i]->collision();
	}
	
	_doberman->lookPlayer();

	_blackOctopus->move();
	_girl->move();
	_redmond->move();
	_masa->move();

	_witch->action("�� ��ġ ������? �� �ݾ� ������");
	_girl->action("����");
	_blackOctopus->action("Ż��� !!!!");
	_masa->action("�๰ ���ܸ� �䵵��");
	_redmond->action("���� ��");
	_doberman->action();

	Coll();

}

void npcManager::render()
{
	RECT tmp;
	for (int i = 0; i < _npcs.size(); i++)
	{
		if (!IntersectRect(&tmp, &CAMERAMANAGER->getRect(), &_npcs[i]->getRect())) continue;
		_npcs[i]->render();
	}

}

void npcManager::Coll()
{
	RECT tmp;

	int cnt = 0;

	for (int i = 0; i < _npcs.size(); i++)
	{
		if (!IntersectRect(&tmp, &_npcs[i]->getRect(), &PLAYER->getRect()))
		{
			cnt++;
		}	
	}

	if (cnt == _npcs.size() - 1) {
		npcColl = true;
	}
	else {
		npcColl = false;
	}


	PLAYER->npcTalk(npcColl);
}
