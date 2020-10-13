#include "stdafx.h"
#include "maptoolLoading.h"

HRESULT maptoolLoading::init()
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�ε� �̹��� �� ���� �ʱ�ȭ
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void maptoolLoading::release()
{
	//�ε�Ŭ���� ����
	if (_loading)
	{
		_loading->release();
		SAFE_DELETE(_loading);
	}
}

void maptoolLoading::update()
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ȭ�� ����
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("����ȭ��");
	}

}

void maptoolLoading::render()
{
	//�ε�Ŭ���� ����
	_loading->render();

}

void maptoolLoading::loadingImage()
{
	_loading->loadImage("tileMenu", "Images/����/tileMenu.bmp", 550, 720, true, RGB(255, 0, 255));
	_loading->loadImage("townBack", "Images/����/townBackground74X60.bmp", 2590, 2100);
	_loading->loadImage("dungeonBack", "Images/����/dungeon_default37X21.bmp", 1280, 720);
	_loading->loadImage("gotoDungeon", "Images/����/goToDungeon.bmp", 2380, 1995);

	//�����޴� �̹��� �ʱ�ȭ 
	_loading->loadImage("menu_size", "Images/����/menu_size.bmp", 408, 490, true, RGB(255, 0, 255));
	_loading->loadImage("menu_tile", "Images/����/menu_tile.bmp", 408, 490, true, RGB(255, 0, 255));
	_loading->loadImage("menu_tile_state", "Images/����/menu_tile_state.bmp", 408, 490, true, RGB(255, 0, 255));
	_loading->loadImage("menu_data", "Images/����/menu_data.bmp", 408, 490, true, RGB(255, 0, 255));
	_loading->loadFrameImage("menu_eraser", "Images/����/menu_eraser.bmp", 88, 54, 2, 1);

	//�̹��� �߰�
	_loading->loadFrameImage("������npc", "Images/npc/doberman10x4.bmp", 380, 232, 10, 4);
	_loading->loadFrameImage("����", "Images/npc/Snot_Kid_walking(4x6).bmp", 360, 272, 6, 4); //����
	_loading->loadFrameImage("���", "Images/npc/Irish_Woman_walking(4x8).bmp", 512, 320, 8, 4); // ���
	_loading->loadFrameImage("������", "Images/npc/NPC_Witch_64x1.bmp", 3712, 77, 64, 1); // ������
	_loading->loadFrameImage("��", "Images/npc/��Ӹ������� 8 X 4.bmp", 400, 328, 8, 4); // ��
	_loading->loadFrameImage("����յ�", "Images/npc/NPC_Irish_Dad(4x8).bmp", 512, 304, 8, 4); //����յ�
	_loading->loadFrameImage("����Ż�������", "Images/npc/����������8X4.bmp", 352, 304, 8, 4);

	/*_loading->loadFrameImage("��������", "Images/����/��������.bmp", 7840, 181, 32, 1);
	_loading->loadFrameImage("���ִ���", "Images/����/���ִ���.bmp", 201, 200, 1, 1);
	_loading->loadFrameImage("���ΰ���", "Images/����/���ΰ���40.bmp", 9800, 200, 40, 1);
	_loading->loadFrameImage("���ǻ���", "Images/����/���ǻ���.bmp", 208, 264, 1, 1);
	_loading->loadFrameImage("���������", "Images/����/���������.bmp", 231, 210, 1, 1);
	_loading->loadFrameImage("������", "Images/����/������.bmp", 159, 209, 1, 1);
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
	_loading->loadFrameImage("������������", "Images/����/������������14.bmp", 420, 38, 14, 1);*/

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



	_loading->loadFrameImage("�ذ�����", "Images/����/skullHammerMove14X4.bmp", 2982, 688, 14, 4);

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
	_loading->loadFrameImage("������", "Images/����/objectHouse.bmp", 250, 250, 2, 2);
	_loading->loadFrameImage("��������", "Images/����/objectTree.bmp", 250, 250, 2, 2);
	_loading->loadFrameImage("�ǹ�����", "Images/����/object2.bmp", 250, 250, 2, 2);
	_loading->loadFrameImage("�ǹ�����2", "Images/����/object3.bmp", 250, 250, 2, 2);
	_loading->loadFrameImage("�ǹ�����3", "Images/����/object4.bmp", 250, 250, 2, 2);

	_loading->loadFrameImage("��������1", "Images/����/dungeonObj.bmp", 250, 250, 2, 2);
	_loading->loadFrameImage("��������2", "Images/����/dungeonObj2.bmp", 250, 250, 2, 2);
	_loading->loadFrameImage("��������3", "Images/����/dungeonObj3.bmp", 250, 250, 2, 2);
	_loading->loadFrameImage("���ͻ���", "Images/����/sampleMonster.bmp", 250, 250, 2, 2);
	_loading->loadFrameImage("���ͻ���2", "Images/����/sampleMonster2.bmp", 250, 250, 2, 2);

	_loading->loadFrameImage("NPC����", "Images/����/objectNPC.bmp", 250, 250, 2, 2);
	_loading->loadFrameImage("NPC����2", "Images/����/objectNPC2.bmp", 250, 250, 2, 2);
	_loading->loadFrameImage("�м���", "Images/����/�м���9.bmp", 378, 48, 9, 1);

	_loading->loadFrameImage("��Ȳ����", "Images/����/��Ȳ����14.bmp", 2352, 190, 14, 1);
	_loading->loadFrameImage("������Ȳ����", "Images/����/������Ȳ����13.bmp", 1976, 162, 13, 1);
	_loading->loadFrameImage("�ʷϳ���", "Images/����/�ʷ�35.bmp", 7315, 180, 35, 1);

	_loading->loadFrameImage("��������", "Images/����/tree_small.bmp", 50, 58, 1, 1);
	_loading->loadFrameImage("�޳�����", "Images/����/stump_left.bmp", 48, 42, 1, 1);
	_loading->loadFrameImage("��������", "Images/����/stump_right.bmp", 48, 42, 1, 1);

	_loading->loadImage("�Ʒ���ũ�ѹ�ư", "Images/����/scrolldown.bmp", 18, 10, true, RGB(255, 0, 255));
	_loading->loadImage("����ũ�ѹ�ư", "Images/����/scrollup.bmp", 18, 10, true, RGB(255, 0, 255));
	_loading->loadImage("arrow_up", "Images/����/arrow_up.bmp", 18, 10, true, RGB(255, 0, 255));
	_loading->loadImage("arrow_down", "Images/����/arrow_down.bmp", 18, 10, true, RGB(255, 0, 255));
	_loading->loadImage("scrollBar", "Images/����/scrollBar.bmp", 10, 47, true, RGB(255, 0, 255));

	_loading->loadFrameImage("babySlime", "Images/����/babySlime9x4(2).bmp", 1152, 512, 9, 4);
	_loading->loadFrameImage("bigSlime", "Images/����/BigSlime12x2.bmp", 984, 526, 12, 2);
	_loading->loadFrameImage("�񷽰���", "Images/����/GolemAttack13x4.bmp", 2470, 760, 13, 4);
	_loading->loadFrameImage("������", "Images/����/GolemMove8x4.bmp", 1520, 760, 8, 4);
	_loading->loadFrameImage("�׾Ƹ�", "Images/����/pot11x4.bmp", 519, 235, 11, 4);
	
	_loading->loadSound("�������", "Sound/shopBGM.mp3", true, true);
	






}

void maptoolLoading::loadingSound()
{
}
