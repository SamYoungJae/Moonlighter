#pragma once
#include "gameNode.h"
/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
/*������ ������ϸ� �̰��� �߰��Ѵ�*/
#include "maptoolLoading.h"
#include "maptoolScene.h"
#include "startScene.h"
#include "townLoading.h"
#include "townScene.h"
#include "nomalDungeonScene.h"
#include "bossDungeonScene.h"
#include "dungeonLoading.h"
#include "itemMenu.h"
#include "shopLoading.h"
#include "shopScene.h"
#include "gotoDungeon.h"
#include "bossLoading.h"

class mainGame : public gameNode
{
private:
	itemMenu* _itemMenu;
	HFONT hFont;
	HFONT oldFont;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};