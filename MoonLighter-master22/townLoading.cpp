#include "stdafx.h"
#include "townLoading.h"

HRESULT townLoading::init()
{
	_loading = new loading;
	_loading->init();

	this->loadingImage();
	this->loadingSound();

	PLAYERDATA->setIsActivate(false);

	return S_OK;
}

void townLoading::release()
{
	if (_loading)
	{
		_loading->release();
		SAFE_DELETE(_loading);
	}
}

void townLoading::update()
{
	_loading->update();
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("Ÿ��ȭ��");
		PLAYERDATA->setIsActivate(true);
	}
}

void townLoading::render()
{
	_loading->render();
}

void townLoading::loadingImage()
{
	/*for (int i = 0; i < 2000; i++)
	{
		_loading->loadImage("test", 0, 0);
	}*/
	_loading->loadImage("tileMenu", "Images/����/tileMenu.bmp", 550, 720, true, RGB(255, 0, 255));
	_loading->loadImage("townBack", "Images/����/townBackground74X60.bmp", 2590, 2100);
	_loading->loadImage("gotoDungeon", "Images/����/goToDungeon.bmp", 2380, 1995);

	//�����޴� �̹��� �ʱ�ȭ 
	_loading->loadImage("menu_size", "Images/����/menu_size.bmp", 408, 490, true, RGB(255, 0, 255));
	_loading->loadImage("menu_tile", "Images/����/menu_tile.bmp", 408, 490, true, RGB(255, 0, 255));
	_loading->loadImage("menu_tile_state", "Images/����/menu_tile_state.bmp", 408, 490, true, RGB(255, 0, 255));
	_loading->loadImage("menu_data", "Images/����/menu_data.bmp", 408, 490, true, RGB(255, 0, 255));
	_loading->loadFrameImage("menu_eraser", "Images/����/menu_eraser.bmp", 88, 54, 2, 1);

	//�̹��� �߰�
	_loading->loadFrameImage("������npc", "Images/npc/doberman10x4.bmp", 380, 232, 10, 4);
	_loading->loadFrameImage("����", "Images/npc/Snot_Kid_walking(4x6).bmp", 360, 272, 6, 4);
	_loading->loadFrameImage("���", "Images/npc/Irish_Woman_walking(4x8).bmp", 512, 320, 8, 4);
	_loading->loadFrameImage("������", "Images/npc/NPC_Witch_64x1.bmp", 3712, 77, 64, 1);
	_loading->loadFrameImage("��", "Images/npc/��Ӹ������� 8 X 4.bmp", 400, 328, 8, 4);
	_loading->loadFrameImage("����յ�", "Images/npc/NPC_Irish_Dad(4x8).bmp", 512, 304, 8, 4);
	_loading->loadFrameImage("����Ż�������", "Images/npc/����������8X4.bmp", 352, 304, 8, 4);

	_loading->loadFrameImage("�����Ϸ�", "Images/npc/�����Ϸ�.bmp", 233, 200, 1,1);
	_loading->loadFrameImage("����Ϸ�", "Images/npc/����Ϸ�.bmp", 175, 200, 1,1);
	_loading->loadFrameImage("�������Ϸ�", "Images/npc/�������Ϸ�.bmp", 184, 200, 1,1);
	_loading->loadFrameImage("����յ��Ϸ�", "Images/npc/����յ��Ϸ�.bmp", 228, 200, 1, 1);
	_loading->loadFrameImage("���Ϸ�", "Images/npc/���Ϸ�.bmp", 188, 200, 1, 1);

	_loading->loadFrameImage("��������", "Images/����/��������.bmp", 15680, 362, 32, 1);
	_loading->loadFrameImage("���ִ���", "Images/����/���ִ���.bmp", 304, 340, 1, 1);
	_loading->loadFrameImage("���ΰ���", "Images/����/���ΰ���40.bmp", 19600, 400, 40, 1);
	_loading->loadFrameImage("�ظ���", "Images/����/�ظ���.bmp", 410, 340, 1, 1);
	_loading->loadFrameImage("�̰ǹ�����", "Images/����/ratailer.bmp", 546, 458, 1, 1);
	_loading->loadFrameImage("���ǻ���", "Images/����/potionShop.bmp", 498, 688, 1, 1);
	_loading->loadFrameImage("���������", "Images/����/���������.bmp", 462, 420, 1, 1);
	_loading->loadFrameImage("������", "Images/����/������.bmp", 318, 418, 1, 1);
	_loading->loadFrameImage("�������ڱ�", "Images/����/�������ڱ�.bmp", 2774, 150, 40, 1);
	_loading->loadFrameImage("������", "Images/����/������.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("������2", "Images/����/������2.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("������3", "Images/����/������3.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("������4", "Images/����/������4.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("������5", "Images/����/������5.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("�����Ѹ�", "Images/����/�����Ѹ�.bmp", 105, 84, 1, 1);
	_loading->loadFrameImage("�����Ѹ�2", "Images/����/�����Ѹ�2.bmp", 84, 126, 1, 1);
	_loading->loadFrameImage("������Ʈ", "Images/����/������Ʈ.bmp", 280, 210, 1, 1);
	_loading->loadFrameImage("����å", "Images/����/����å.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("��������", "Images/����/��������.bmp", 70, 70, 1, 1);
	_loading->loadFrameImage("������", "Images/����/������.bmp", 35, 35, 1, 1);
	_loading->loadFrameImage("������������", "Images/����/������������14.bmp", 420, 38, 14, 1);

	// ���� �߰��� �͵�
	_loading->loadFrameImage("����Ÿ��", "Images/����/����Ÿ��.bmp", 175, 175, SAMPLETILEX, SAMPLETILEY);
	_loading->loadFrameImage("�ܵ�Ÿ��", "Images/����/�ܵ�Ÿ��.bmp", 175, 175, SAMPLETILEX, SAMPLETILEY);
	_loading->loadFrameImage("¼��Ÿ��", "Images/����/¼��Ÿ��2.bmp", 175, 175, SAMPLETILEX, SAMPLETILEY);

	_loading->loadFrameImage("����", "Images/����/bench.bmp", 102, 52, 1, 1);
	_loading->loadFrameImage("�밢������", "Images/����/bench_diagonal.bmp", 100, 100, 1, 1);
	_loading->loadFrameImage("���尣", "Images/����/blacksmith.bmp", 588, 506, 1, 1);
	_loading->loadFrameImage("�Խ���", "Images/����/board.bmp", 178, 116, 1, 1);
	_loading->loadFrameImage("���峭�м�", "Images/����/fountain.bmp", 82, 102, 1, 1);
	_loading->loadFrameImage("��Ÿ����", "Images/����/��Ÿ����.bmp", 486, 454, 1, 1);
	_loading->loadFrameImage("�����Ѹ�", "Images/����/gas_suit_12.bmp", 696, 77, 12, 1);

	_loading->loadFrameImage("�м���", "Images/����/�м���9.bmp", 378, 48, 9, 1);

	_loading->loadFrameImage("��Ȳ����", "Images/����/��Ȳ����14.bmp", 2352, 190, 14, 1);
	_loading->loadFrameImage("������Ȳ����", "Images/����/������Ȳ����13.bmp", 1976, 162, 13, 1);
	_loading->loadFrameImage("�ʷϳ���", "Images/����/�ʷ�35.bmp", 7315, 180, 35, 1);

	_loading->loadFrameImage("��������", "Images/����/tree_small.bmp", 50, 58, 1, 1);
	_loading->loadFrameImage("�޳�����", "Images/����/stump_left.bmp", 48, 42, 1, 1);
	_loading->loadFrameImage("��������", "Images/����/stump_right.bmp", 48, 42, 1, 1);

	//�������±濡 �� �̹��� �߰�
	_loading->loadFrameImage("�÷��̾��������", "Images/�÷��̾�/TeleportIn20X1.bmp", 1040, 70, 20, 1);
	_loading->loadFrameImage("�������±湮", "Images/�������±�/�������±湮.bmp", 1280*2, 128*2, 10, 1);

}

void townLoading::loadingSound()
{
	_loading->loadSound("�������", "Sound/shopBGM.mp3", true, true);
	_loading->loadSound("�������", "Sound/townBGM.mp3", true, true);

	//�����۸޴� ���� 
	_loading->loadSound("openInven", "Sound/UI&inventorySound/openInven.wav");
	_loading->loadSound("moveMenu", "Sound/UI&inventorySound/moveMenu.wav");
	_loading->loadSound("cursor_move", "Sound/UI&inventorySound/cursor_move.wav");
	_loading->loadSound("cursor_pick", "Sound/UI&inventorySound/cursor_pick.wav");
	_loading->loadSound("cursor_drop", "Sound/UI&inventorySound/cursor_drop.wav");
	_loading->loadSound("cursor_error", "Sound/UI&inventorySound/cursor_error.wav");

	//����(����,���尣) ����
	_loading->loadSound("witch_Open", "Sound/witch&blacksmith/witch_open.wav");

	//�÷��̾� ���� 
	_loading->loadSound("heal", "Sound/playerSound/heal.wav");
	_loading->loadSound("weaponChange", "Sound/playerSound/weaponChange.wav");
	_loading->loadSound("doorBGM", "Sound/door.wav");

	_loading->loadSound("��������0", "Sound/shopSound/shopDoorOpen0.wav");
	_loading->loadSound("��������1", "Sound/shopSound/shopDoorOpen1.wav");
	_loading->loadSound("���ݾ�", "Sound/shopSound/������.wav");

	_loading->loadSound("ȭ��߻�", "Sound/playerSound/bow.wav");			//����
	_loading->loadSound("ȭ�����", "Sound/playerSound/bow_Attack.wav");		//����
	_loading->loadSound("ȭ�콺ų", "Sound/playerSound/bow_Charge.wav");	
	_loading->loadSound("������", "Sound/playerSound/roll.wav");				//����
	_loading->loadSound("���ֵθ���", "Sound/playerSound/Sword.wav");		//�ָ�
	_loading->loadSound("�÷��̾�ȱ�", "Sound/playerSound/walk.wav");		//����
	_loading->loadSound("ħ��", "Sound/playerSound/ħ��.wav");
	_loading->loadSound("��õ", "Sound/playerSound/ȸ��_��.wav");			//����

	//���� ����
	_loading->loadSound("���Ҹ�" , "Sound/townSound/���Ҹ�.wav");

}
