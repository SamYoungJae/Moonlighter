#include "stdafx.h"
#include "bossLoading.h"

HRESULT bossLoading::init()
{
	_loading = new loading;
	_loading->init();

	this->loadImage();
	this->loadSound();

	PLAYERDATA->setIsActivate(false);
	return S_OK;
}

void bossLoading::release()
{
	if (_loading)
	{
		_loading->release();
		SAFE_DELETE(_loading);
	}
}

void bossLoading::update()
{
	_loading->update();
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("��������");
		PLAYERDATA->setIsActivate(true);
	}
}

void bossLoading::render()
{
	_loading->render();
}

void bossLoading::loadImage()
{
	//������ ���
	_loading->loadImage("bossRoomBack", "Images/����/bossRoom .bmp", 1024, 839);

	//�����̹���
	_loading->loadFrameImage("bossUp", "Images/����/BossUp32 .bmp", 5600, 175, 32, 1);
	_loading->loadFrameImage("bossDead1", "Images/����/dead1 .bmp", 7175, 175, 41, 1);
	_loading->loadFrameImage("bossDead2", "Images/����/dead2 .bmp", 7175, 175, 41, 1);
	_loading->loadFrameImage("bossFistShoot", "Images/����/FistShoot .bmp", 3850, 525, 22, 3);
	_loading->loadFrameImage("bossHandShootStart", "Images/����/Hand_Shoot_First .bmp", 3500, 175, 20, 1);
	_loading->loadFrameImage("bossHandShootEnd", "Images/����/Hand_Shoot_Last .bmp", 1925, 175, 11, 1);
	_loading->loadFrameImage("bossIdle", "Images/����/idleBoss .bmp", 350, 175, 2, 1);

	//����������Ʈ
	_loading->loadImage("bossRock0", "Images/����/Boss_Rock0 .bmp", 100, 108, true, RGB(255, 0, 255));
	_loading->loadImage("bossRock1", "Images/����/Boss_Rock1 .bmp", 100, 108, true, RGB(255, 0, 255));
	_loading->loadImage("bossRock2", "Images/����/Boss_Rock2 .bmp", 100, 108, true, RGB(255, 0, 255));
	_loading->loadImage("bossRock3", "Images/����/Boss_Rock3 .bmp", 100, 108, true, RGB(255, 0, 255));
	//_loading->loadImage("bossFist", "Images/����/fist .bmp", 104, 373, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bossFist", "Images/����/fist2 .bmp", 623, 746, 6, 1);
	_loading->loadFrameImage("bossHand", "Images/����/hand.bmp", 1140, 60, 19, 1);


	//�����ε��������� �׽�Ʈ�� �ϴ°�
	_loading->loadFrameImage("golemScroll", "Images/����/�񷽴�����ũ��11.bmp", 2277, 60, 11, 1);
	_loading->loadImage("semiBossHpBarFront(red)", "Images/����/semiBossHpFront(red).bmp", 927, 17, true, RGB(255, 0, 255));
	_loading->loadImage("semiBossHpBarFront(white)", "Images/����/semiBossHpFront(white).bmp", 927, 17, true, RGB(255, 0, 255));
	_loading->loadImage("semiBossHpBarBack", "Images/����/semiBossHpBack.bmp", 947, 23, true, RGB(255, 0, 255));
}

void bossLoading::loadSound()
{

}
