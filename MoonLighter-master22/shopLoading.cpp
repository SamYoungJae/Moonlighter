#include "stdafx.h"
#include "shopLoading.h"

HRESULT shopLoading::init()
{
	_loading = new loading;
	_loading->init();

	this->loadingImage();
	this->loadingSound();

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
		SCENEMANAGER->loadScene("����ȭ��");
	}
}

void shopLoading::render()
{
	_loading->render();
}

void shopLoading::loadingImage()
{
	_loading->loadImage("������", "Images/����/myShop_noon.bmp", 670, 860, true, RGB(255, 0, 255));
	_loading->loadImage("�����ȼ�", "Images/����/myShop_pixel2.bmp", 670, 860, true, RGB(255, 0, 255));
	//_loading->loadImage("���������", "Images/����/shop_door.bmp", 183, 118, true, RGB(255, 0, 255));
	//_loading->loadImage("���������", "Images/����/shop_door.bmp", 91, 64, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����������", "Images/����/shopDoor.bmp", 900, 139, 6, 1);

	_loading->loadFrameImage("�������", "Images/����/�������.bmp", 80, 154, 1, 1);
	_loading->loadFrameImage("������", "Images/����/������.bmp", 110, 110, 1, 1);
	_loading->loadFrameImage("��������", "Images/����/��������.bmp", 98, 112, 1, 1);
	_loading->loadFrameImage("����å��", "Images/����/����å��.bmp", 192, 66, 1, 1);
	_loading->loadFrameImage("����ħ��", "Images/����/����ħ��.bmp", 102, 76, 1, 1);
	_loading->loadFrameImage("�����۱׸���", "Images/����/item_shadow.bmp", 24, 12, 1, 1);
	_loading->loadFrameImage("��������", "Images/npc/visitor_face.bmp", 512, 64, 8, 1);
}

void shopLoading::loadingSound()
{
	
	_loading->loadSound("��û�δ�", "Sound/shopSound/��û�δ�.wav");
	_loading->loadSound("�δ�", "Sound/shopSound/�δ�.wav");
	_loading->loadSound("��δ�", "Sound/shopSound/��δ�.wav");
	_loading->loadSound("��û��δ�", "Sound/shopSound/��û��δ�.wav");
}
