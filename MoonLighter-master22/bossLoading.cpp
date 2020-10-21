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
	_loading->loadFrameImage("bossRock0", "Images/����/Boss_Rock0 .bmp", 100, 108,1,1);
	_loading->loadFrameImage("bossRock1", "Images/����/Boss_Rock1 .bmp", 100, 108, 1, 1);
	_loading->loadFrameImage("bossRock2", "Images/����/Boss_Rock2 .bmp", 100, 108, 1, 1);
	_loading->loadFrameImage("bossRock3", "Images/����/Boss_Rock3 .bmp", 100, 108, 1, 1);
	//_loading->loadImage("bossFist", "Images/����/fist .bmp", 104, 373, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bossFist", "Images/����/fist2 .bmp", 623, 746, 6, 1);
	_loading->loadFrameImage("bossHand", "Images/����/hand.bmp", 1140, 60, 19, 1);


	//�����ε��������� �׽�Ʈ�� �ϴ°�
	_loading->loadFrameImage("golemScroll", "Images/����/�񷽴�����ũ��11.bmp", 2277, 60, 11, 1);
	_loading->loadImage("semiBossHpBarFront(red)", "Images/����/semiBossHpFront(red).bmp", 927, 17, true, RGB(255, 0, 255));
	_loading->loadImage("semiBossHpBarFront(white)", "Images/����/semiBossHpFront(white).bmp", 927, 17, true, RGB(255, 0, 255));
	_loading->loadImage("semiBossHpBarBack", "Images/����/semiBossHpBack.bmp", 947, 23, true, RGB(255, 0, 255));
	_loading->loadFrameImage("potalUpdate", "Images/����/potalUpdate7.bmp", 917, 108, 7, 1);
	_loading->loadFrameImage("potalInit", "Images/����/potalInit26.bmp", 3406, 108, 26, 1);
	_loading->loadFrameImage("potalPlayer", "Images/����/potalPlayer25.bmp", 3275, 108, 25, 1);
	_loading->loadFrameImage("�÷��̾��Ҵ�Ʈ���", "Images/�÷��̾�/playerUsePendant31.bmp", 4464, 120, 31, 1);
	_loading->loadImage("messegeBox_potal", "Images/����/messegeBox_potal.bmp", 183, 50, true, RGB(255, 0, 255));
	_loading->loadFrameImage("dungeonStageBar", "Images/�������â/dungeonProgress1X3.bmp", 85, 45, 1, 3);
	_loading->loadImage("resultBack", "Images/�������â/ui_dungeonResult4022.bmp", 1158, 656, true, RGB(255, 0, 255));
	
}

void bossLoading::loadSound()
{
	_loading->loadSound("bossBGM", "Sound/����/bossGolemBGM.wav", true, true);


	_loading->loadSound("bossInit", "Sound/���ʹ�/����/����ó������.wav" );
	_loading->loadSound("bossRock", "Sound/���ʹ�/����/���� ����������.wav" );
	_loading->loadSound("bossHit", "Sound/���ʹ�/����/��������.wav" );
	_loading->loadSound("bossDead", "Sound/���ʹ�/����/��������.wav" );

}
