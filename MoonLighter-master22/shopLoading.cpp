#include "stdafx.h"
#include "shopLoading.h"

HRESULT shopLoading::init()
{
	_loading = new loading;
	_loading->init();

	this->loadingImage();
	this->loadingSound();

	PLAYERDATA->setIsActivate(false);
	return S_OK;
}

void shopLoading::release()
{
	if (_loading)
	{
		_loading->release();
		SAFE_DELETE(_loading);
	}
}

void shopLoading::update()
{
	_loading->update();
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("상점화면");
		PLAYERDATA->setIsActivate(true);
	}
}

void shopLoading::render()
{
	_loading->render();
}

void shopLoading::loadingImage()
{
	_loading->loadImage("상점맵", "Images/상점/myShop_noon.bmp", 670, 860, true, RGB(255, 0, 255));
	_loading->loadImage("상점픽셀", "Images/상점/myShop_pixel2.bmp", 670, 860, true, RGB(255, 0, 255));
	//_loading->loadImage("상점문기둥", "Images/상점/shop_door.bmp", 183, 118, true, RGB(255, 0, 255));
	//_loading->loadImage("상점문기둥", "Images/상점/shop_door.bmp", 91, 64, true, RGB(255, 0, 255));

	_loading->loadFrameImage("상점문열어", "Images/상점/shopDoor.bmp", 492, 90, 6, 1); // 900 139

	_loading->loadFrameImage("상점길목", "Images/상점/상점길목.bmp", 80, 154, 1, 1);
	_loading->loadFrameImage("상점문", "Images/상점/상점문.bmp", 110, 110, 1, 1);
	_loading->loadFrameImage("상점좌판", "Images/상점/상점좌판.bmp", 98, 112, 1, 1);
	_loading->loadFrameImage("상점책상", "Images/상점/상점책상.bmp", 192, 66, 1, 1);
	_loading->loadFrameImage("상점침대", "Images/상점/상점침대.bmp", 102, 76, 1, 1);
	_loading->loadFrameImage("아이템그림자", "Images/상점/item_shadow.bmp", 24, 12, 1, 1);


	_loading->loadFrameImage("엄청싸다", "Images/npc/엄청싸다.bmp", 832, 52, 16, 1);
	_loading->loadFrameImage("싸다", "Images/npc/싸다.bmp", 416, 52, 8, 1);
	_loading->loadFrameImage("비싸다", "Images/npc/비싸다.bmp", 468, 52, 9, 1);
	_loading->loadFrameImage("엄청비싸다", "Images/npc/엄청비싸다.bmp", 624, 52, 12, 1);
	_loading->loadFrameImage("기다리는중", "Images/npc/npc_waiting.bmp", 104, 52, 2, 1);

	_loading->loadFrameImage("npc말풍선몸", "Images/상점/bubble_body.bmp", 24, 24, 1, 1);
	_loading->loadFrameImage("npc말풍선꼬리", "Images/상점/bubble_bottom.bmp", 10, 6, 1, 1);
	_loading->loadFrameImage("npc말풍선왼쪽", "Images/상점/bubble_left.bmp", 6, 24, 1, 1);
	_loading->loadFrameImage("npc말풍선오른쪽", "Images/상점/bubble_right.bmp", 6, 24, 1, 1);

	_loading->loadFrameImage("상점배치", "Images/상점/ui_onDP.bmp", 310, 50, 3, 1);
	_loading->loadFrameImage("책상금고", "Images/상점/cash_register.bmp", 704, 64, 11, 1);
	_loading->loadFrameImage("판매버튼", "Images/상점/jButton.bmp", 40, 40, 1, 1);
	//_loading->loadFrameImage("상점배치", "Images/상점/ui_onDP.bmp", 310, 50, 3, 1);


}

void shopLoading::loadingSound()
{

	_loading->loadSound("엄청싸다", "Sound/shopSound/엄청싸다.wav");
	_loading->loadSound("싸다", "Sound/shopSound/싸다.wav");
	_loading->loadSound("비싸다", "Sound/shopSound/비싸다.wav");
	_loading->loadSound("엄청비싸다", "Sound/shopSound/엄청비싸다.wav");

	_loading->loadSound("아이템팔림", "Sound/shopSound/아이템팔림.wav");
}
