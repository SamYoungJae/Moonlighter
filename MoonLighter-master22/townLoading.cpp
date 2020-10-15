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

	//�����۸޴� �̹��� �ʱ�ȭ 
	_loading->loadImage("menu_calendar", "Images/ItemMenu/menu_calendar.bmp", 1002, 592, true, RGB(255, 0, 255));
	_loading->loadImage("menu_wishlist", "Images/ItemMenu/menu_wishlist.bmp", 818, 518, true, RGB(255, 0, 255));
	_loading->loadImage("menu_inventory", "Images/ItemMenu/menu_inventory.bmp", 1044, 598, true, RGB(255, 0, 255));
	_loading->loadImage("menu_inventory_inDungeon", "Images/ItemMenu/menu_inventory_inDungeon.bmp", 1044, 598, true, RGB(255, 0, 255));
	_loading->loadImage("menu_notebook", "Images/ItemMenu/menu_notebook.bmp", 827, 574, true, RGB(255, 0, 255));
	_loading->loadImage("btn_qe", "Images/ItemMenu/btn_qe.bmp", 300, 38, true, RGB(255, 0, 255));
	_loading->loadFrameImage("toggle_calendar", "Images/ItemMenu/toggle_calendar.bmp", 92, 50, 2, 1);
	_loading->loadFrameImage("toggle_wishlist", "Images/ItemMenu/toggle_wishlist.bmp", 92, 50, 2, 1);
	_loading->loadFrameImage("toggle_inventory", "Images/ItemMenu/toggle_inventory.bmp", 92, 50, 2, 1);
	_loading->loadFrameImage("toggle_notebook", "Images/ItemMenu/toggle_notebook.bmp", 92, 50, 2, 1);
	_loading->loadFrameImage("icon_euip", "Images/ItemMenu/icon_euip.bmp", 64, 30, 2, 1);
	_loading->loadFrameImage("icon_equip_idx", "Images/ItemMenu/icon_equip_idx.bmp", 60, 30, 2, 1);
	_loading->loadFrameImage("icon_equip_idx_empty", "Images/ItemMenu/icon_equip_idx_empty.bmp", 60, 30, 2, 1);
	_loading->loadImage("nameBase", "Images/ItemMenu/nameBase.bmp", 310, 34, true, RGB(255, 0, 255));
	_loading->loadImage("grabBase", "Images/ItemMenu/grabBase.bmp", 72, 72, true, RGB(255, 0, 255));
	_loading->loadImage("item_slot", "Images/ItemMenu/item_slot.bmp", 60, 60, true, RGB(255, 0, 255));
	_loading->loadImage("inventory_selectBubble", "Images/ItemMenu/inventory_selectBubble.bmp", 220, 144, true, RGB(255, 0, 255));
	_loading->loadFrameImage("select_yes", "Images/ItemMenu/select_yes.bmp", 312, 78, 4, 1);
	_loading->loadFrameImage("select_no", "Images/ItemMenu/select_no.bmp", 312, 78, 4, 1);
	_loading->loadImage("bag_pendant", "Images/ItemMenu/bag_pendant.bmp", 70, 48, true, RGB(255, 0, 255));
	_loading->loadImage("bag_emblem", "Images/ItemMenu/bag_emblem.bmp", 68, 66, true, RGB(255, 0, 255));


	//Ŀ�� �̹��� �ʱ�ȭ 
	_loading->loadFrameImage("cursor_move", "Images/ItemMenu/cursor_move.bmp", 304, 76, 4, 1);
	_loading->loadFrameImage("cursor_click", "Images/ItemMenu/cursor_click.bmp", 380, 76, 5, 1);
	_loading->loadFrameImage("cursor_price", "Images/Shop/cursor_price.bmp", 408, 94, 2, 1);
	_loading->loadFrameImage("cursor_select", "Images/ItemMenu/cursor_select.bmp", 510, 102, 5, 1);

	//������ �̹��� �ʱ�ȭ 
	_loading->loadImage("richJelly", "Images/Item/item_richJelly.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("venomJelly", "Images/Item/item_venomJelly.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("crystal", "Images/Item/item_crystal.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("vine", "Images/Item/item_vine.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("teethStone", "Images/Item/item_teethStone.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("root", "Images/Item/item_root.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("ironBar", "Images/Item/item_ironBar.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("foundryRests", "Images/Item/item_foundryRests.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("brokenSword", "Images/Item/item_brokenSword.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("fabric", "Images/Item/item_fabric.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("hardenedSteel", "Images/Item/item_hardenedSteel.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->loadImage("trainingShortSword", "Images/Item/item_trainingShortSword.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("trainingBow", "Images/Item/item_trainingBow.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->loadImage("hpPotion1", "Images/Item/item_hpPotion1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("hpPotion2", "Images/Item/item_hpPotion2.bmp", 48, 48, true, RGB(255, 0, 255));

	//������ �̸� �̹��� �ʱ�ȭ
	_loading->loadImage("name_richJelly", "Images/Item/name_richJelly.bmp", 160, 24);
	_loading->loadImage("name_venomJelly", "Images/Item/name_venomJelly.bmp", 160, 24);
	_loading->loadImage("name_crystal", "Images/Item/name_crystal.bmp", 160, 24);
	_loading->loadImage("name_vine", "Images/Item/name_vine.bmp", 160, 24);
	_loading->loadImage("name_teethStone", "Images/Item/name_teethStone.bmp", 160, 24);
	_loading->loadImage("name_root", "Images/Item/name_root.bmp", 160, 24);
	_loading->loadImage("name_ironBar", "Images/Item/name_ironBar.bmp", 160, 24);
	_loading->loadImage("name_foundryRests", "Images/Item/name_foundryRests.bmp", 160, 24);
	_loading->loadImage("name_brokenSword", "Images/Item/name_brokenSword.bmp", 160, 24);
	_loading->loadImage("name_fabric", "Images/Item/name_fabric.bmp", 160, 24);
	_loading->loadImage("name_hardenedSteel", "Images/Item/name_hardenedSteel.bmp", 160, 24);

	_loading->loadImage("name_trainingShortSword", "Images/Item/name_trainingShortSword.bmp", 160, 24);
	_loading->loadImage("name_trainingBow", "Images/Item/name_trainingBow.bmp", 160, 24);

	_loading->loadImage("name_hpPotion1", "Images/Item/name_hpPotion1.bmp", 160, 24);
	_loading->loadImage("name_hpPotion2", "Images/Item/name_hpPotion2.bmp", 160, 24);

	//������ ���� �̹��� �ʱ�ȭ 
	_loading->loadImage("des_richJelly", "Images/Item/des_richJelly.bmp", 304, 66);
	_loading->loadImage("des_venomJelly", "Images/Item/des_venomJelly.bmp", 314, 42);
	_loading->loadImage("des_crystal", "Images/Item/des_crystal.bmp", 280, 20);
	_loading->loadImage("des_vine", "Images/Item/des_vine.bmp", 292, 42);
	_loading->loadImage("des_teethStone", "Images/Item/des_teethStone.bmp", 310, 42);
	_loading->loadImage("des_root", "Images/Item/des_root.bmp", 316, 42);
	_loading->loadImage("des_ironBar", "Images/Item/des_ironBar.bmp", 312, 64);
	_loading->loadImage("des_foundryRests", "Images/Item/des_foundryRests.bmp", 278, 64);
	_loading->loadImage("des_brokenSword", "Images/Item/des_brokenSword.bmp", 276, 64);
	_loading->loadImage("des_fabric", "Images/Item/des_fabric.bmp", 306, 64);
	_loading->loadImage("des_hardenedSteel", "Images/Item/des_hardenedSteel.bmp", 270, 42);

	_loading->loadImage("des_trainingShortSword", "Images/Item/des_trainingShortSword.bmp", 286, 64);
	_loading->loadImage("des_trainingBow", "Images/Item/des_trainingBow.bmp", 306, 66);

	_loading->loadImage("des_hpPotion1", "Images/Item/des_hpPotion1.bmp", 310, 42);
	_loading->loadImage("des_hpPotion2", "Images/Item/des_hpPotion2.bmp", 304, 42);

	//�������̽� �̹��� �ʱ�ȭ 
	_loading->loadImage("interface_key", "Images/Interface/interface_key.bmp", 174, 152, true, RGB(255, 0, 255));
	_loading->loadImage("icon_coin", "Images/Interface/icon_coin.bmp", 18, 18, true, RGB(255, 0, 255));
	_loading->loadImage("icon_goldPouch", "Images/Interface/icon_goldPouch.bmp", 70, 70, true, RGB(255, 0, 255));
	_loading->loadImage("icon_bag", "Images/Interface/icon_bag.bmp", 84, 84, true, RGB(255, 0, 255));
	_loading->loadImage("icon_hp", "Images/Interface/icon_hp.bmp", 56, 40, true, RGB(255, 0, 255));
	_loading->loadImage("hp_barBack", "Images/Interface/hp_barBack.bmp", 130, 24, true, RGB(255, 0, 255));
	_loading->loadImage("hp_barFront", "Images/Interface/hp_barFront.bmp", 130, 24, true, RGB(255, 0, 255));
	_loading->loadFrameImage("weapon_slot", "Images/Interface/weapon_slot.bmp", 212, 70, 2, 1);
	_loading->loadFrameImage("weapon_frontIdx", "Images/Interface/weapon_frontIdx.bmp", 60, 30, 2, 1);
	_loading->loadFrameImage("weapon_backIdx", "Images/Interface/weapon_backIdx.bmp", 60, 30, 2, 1);

	//���� �̹��� 
	_loading->loadImage("menu_shopInventory", "Images/Shop/menu_shopInventory.bmp", 482, 544, true, RGB(255, 0, 255));
	_loading->loadImage("menu_display", "Images/Shop/menu_display.bmp", 500, 464, true, RGB(255, 0, 255));
	_loading->loadImage("arrow_price", "Images/Shop/arrow_price.bmp", 14, 46, true, RGB(255, 0, 255));

	//����(���) �̹��� �ʱ�ȭ 
	_loading->loadImage("0", "Images/Number/0.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("1", "Images/Number/1.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("2", "Images/Number/2.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("3", "Images/Number/3.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("4", "Images/Number/4.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("5", "Images/Number/5.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("6", "Images/Number/6.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("7", "Images/Number/7.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("8", "Images/Number/8.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("9", "Images/Number/9.bmp", 10, 14, true, RGB(255, 0, 255));

	//����(����) �̹��� �ʱ�ȭ 
	_loading->loadImage("0_black", "Images/Number/0_black.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("1_black", "Images/Number/1_black.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("2_black", "Images/Number/2_black.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("3_black", "Images/Number/3_black.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("4_black", "Images/Number/4_black.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("5_black", "Images/Number/5_black.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("6_black", "Images/Number/6_black.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("7_black", "Images/Number/7_black.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("8_black", "Images/Number/8_black.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("9_black", "Images/Number/9_black.bmp", 10, 14, true, RGB(255, 0, 255));

	//����(�ʷϻ�) �̹��� �ʱ�ȭ 
	_loading->loadImage("0_green", "Images/Number/0_green.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("1_green", "Images/Number/1_green.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("2_green", "Images/Number/2_green.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("3_green", "Images/Number/3_green.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("4_green", "Images/Number/4_green.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("5_green", "Images/Number/5_green.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("6_green", "Images/Number/6_green.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("7_green", "Images/Number/7_green.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("8_green", "Images/Number/8_green.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("9_green", "Images/Number/9_green.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("x_green", "Images/Number/x_green.bmp", 10, 14, true, RGB(255, 0, 255));
	_loading->loadImage("0_gray", "Images/Number/0_gray.bmp", 10, 14, true, RGB(255, 0, 255));

	//���� ����(���) �̹��� �ʱ�ȭ 
	_loading->loadImage("0_white_small", "Images/Number/0_white_small.bmp", 6, 12, true, RGB(255, 0, 255));
	_loading->loadImage("1_white_small", "Images/Number/1_white_small.bmp", 6, 12, true, RGB(255, 0, 255));
	_loading->loadImage("2_white_small", "Images/Number/2_white_small.bmp", 6, 12, true, RGB(255, 0, 255));
	_loading->loadImage("3_white_small", "Images/Number/3_white_small.bmp", 6, 12, true, RGB(255, 0, 255));
	_loading->loadImage("4_white_small", "Images/Number/4_white_small.bmp", 6, 12, true, RGB(255, 0, 255));
	_loading->loadImage("5_white_small", "Images/Number/5_white_small.bmp", 6, 12, true, RGB(255, 0, 255));
	_loading->loadImage("6_white_small", "Images/Number/6_white_small.bmp", 6, 12, true, RGB(255, 0, 255));
	_loading->loadImage("7_white_small", "Images/Number/7_white_small.bmp", 6, 12, true, RGB(255, 0, 255));
	_loading->loadImage("8_white_small", "Images/Number/8_white_small.bmp", 6, 12, true, RGB(255, 0, 255));
	_loading->loadImage("9_white_small", "Images/Number/9_white_small.bmp", 6, 12, true, RGB(255, 0, 255));
	_loading->loadImage("slash_white_small", "Images/Number/slash_white_small.bmp", 6, 12, true, RGB(255, 0, 255));

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

	//�÷��̾� ���� 
	_loading->loadSound("heal", "Sound/playerSound/heal.wav");
	_loading->loadSound("weaponChange", "Sound/playerSound/weaponChange.wav");
	_loading->loadSound("doorBGM", "Sound/door.wav");

	_loading->loadSound("��������0", "Sound/shopSound/shopDoorOpen0.wav");
	_loading->loadSound("��������1", "Sound/shopSound/shopDoorOpen1.wav");
	_loading->loadSound("���ݾ�", "Sound/shopSound/������.wav");

	_loading->loadSound("ȭ��߻�", "Sound/playerSound/bow.wav");			//����
	_loading->loadSound("ȭ�����", "Sound/playerSound/bow_Attack.wav");	//����
	_loading->loadSound("ȭ�콺ų", "Sound/playerSound/bow_Charge.wav");	
	_loading->loadSound("������", "Sound/playerSound/roll.wav");			//����
	_loading->loadSound("���ֵθ���", "Sound/playerSound/Sword.wav");		//�ָ�
	_loading->loadSound("�÷��̾�ȱ�", "Sound/playerSound/walk.wav");		//����
	_loading->loadSound("ħ��", "Sound/playerSound/ħ��.wav");
	_loading->loadSound("��õ", "Sound/playerSound/ȸ��_��.wav");			//����

	
	//���� ����
	_loading->loadSound("���Ҹ�" , "Sound/townSound/���Ҹ�.wav");

}
