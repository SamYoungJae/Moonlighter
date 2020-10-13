#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
	IMAGEMANAGER->addImage("�ΰ�", "Images/Ÿ��Ʋȭ��/intro_logoImg.bmp", 560, 266, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ��1", "Images/Ÿ��Ʋȭ��/intro0.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ƹ�Ű", "Images/Ÿ��Ʋȭ��/pressAnyKey.bmp", 318, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ڹ���", "Images/Ÿ��Ʋȭ��/mainBack16x1.bmp", 20480, 720, 16, 1);
	IMAGEMANAGER->addFrameImage("�չ���", "Images/Ÿ��Ʋȭ��/mainFront16x1.bmp", 20480, 720, 16, 1);
	//3840
	IMAGEMANAGER->addFrameImage("Ÿ��Ʋȭ��", "Images/Ÿ��Ʋȭ��/maintitle2.bmp", 3840, 720, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���ο����", "Images/Ÿ��Ʋȭ��/newgame.bmp", 200, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ɼ�", "Images/Ÿ��Ʋȭ��/option.bmp", 130, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "Images/Ÿ��Ʋȭ��/out.bmp", 130, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ø޴�", "Images/Ÿ��Ʋȭ��/selectMain.bmp", 145, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Images/Ÿ��Ʋȭ��/maptool.bmp", 36, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ϱ�", "Images/Ÿ��Ʋȭ��/continue.bmp", 71, 18, true, RGB(255, 0, 255));

	//IMAGEMANAGER->addFrameImage("�ε�������", "Images/Ÿ��Ʋȭ��/load67.bmp", 2948, 45, 67, 1, true, RGB(255, 0, 255));

	_count = 0;
	_index = 0;
	SOUNDMANAGER->addSound("introBGM", "Sound/introBGM.mp3", true, true);
	SOUNDMANAGER->addSound("doorBGM", "Sound/door.wav");
	_alpha = 0;
	a_alpha = 0;
	t_count = 0;
	t_index = 0;

	r_index = 0;
	state = 0;

	titleLoad = false;

	return S_OK;

}

void startScene::release()
{
}

void startScene::update()
{

	if (_alpha < 254)
	{
		_alpha++;
	}
	if (INPUT->GetKeyDown(VK_RETURN) && !titleLoad) {
		titleLoad = true;
		IMAGEMANAGER->findImage("���ø޴�")->setX(WINSIZEX / 2 - 75);
		IMAGEMANAGER->findImage("���ø޴�")->setY(WINSIZEY - 310);

	}


	if (!SOUNDMANAGER->isPlaySound("introBGM"))
	{

		SOUNDMANAGER->play("introBGM", 0.3f);
	}


	bubbleAnim();


	if (titleLoad)
	{
		currentPos();
		titleAnim();
	}



	if (a_alpha > 254)
	{
		a_alpha = 0;
	}
	else {
		a_alpha++;
	}

}

void startScene::render()
{
	IMAGEMANAGER->frameRender("�ڹ���", getMemDC(), 0, 0);
	IMAGEMANAGER->frameRender("�չ���", getMemDC(), 0, 0);

	if (!titleLoad)
	{
		IMAGEMANAGER->render("��Ʈ��1", getMemDC(), 0, 0);
		IMAGEMANAGER->alphaRender("�ƹ�Ű", getMemDC(), WINSIZEX / 2 - 150, WINSIZEY - 100, a_alpha);
	}
	else {
		IMAGEMANAGER->frameRender("Ÿ��Ʋȭ��", getMemDC(), 0, 0);

		IMAGEMANAGER->alphaRender("����ϱ�", getMemDC(), WINSIZEX / 2 - 40, WINSIZEY - 300, 255);
		IMAGEMANAGER->alphaRender("����", getMemDC(), WINSIZEX / 2 - 25, WINSIZEY - 270, 255);
		IMAGEMANAGER->alphaRender("�ɼ�", getMemDC(), WINSIZEX / 2 - 73, WINSIZEY - 245, 255);
		IMAGEMANAGER->alphaRender("������", getMemDC(), WINSIZEX / 2 - 75, WINSIZEY - 215, 255);

		IMAGEMANAGER->alphaRender("���ø޴�", getMemDC(), IMAGEMANAGER->findImage("���ø޴�")->getX(), IMAGEMANAGER->findImage("���ø޴�")->getY(), 255);
	}
	//IMAGEMANAGER->render("�ΰ�", getMemDC(), 298, 80);
	IMAGEMANAGER->alphaRender("�ΰ�", getMemDC(), 360, 80, _alpha);

	

}

void startScene::bubbleAnim()
{
	_count++;
	IMAGEMANAGER->findImage("�ڹ���")->setFrameY(0);
	IMAGEMANAGER->findImage("�չ���")->setFrameY(0);

	if (_count % 5 == 0)
	{
		_index++;
		if (_index >= 16)
		{
			_index = 0;
		}
		IMAGEMANAGER->findImage("�ڹ���")->setFrameX(_index);
		IMAGEMANAGER->findImage("�չ���")->setFrameX(_index);
	}
}

void startScene::titleAnim()
{
	t_count++;

	IMAGEMANAGER->findImage("Ÿ��Ʋȭ��")->setFrameY(0);

	if (t_count % 20 == 0)
	{
		SOUNDMANAGER->stop("doorBGM");
		if (t_index < 3)
		{
			SOUNDMANAGER->play("doorBGM");
			t_index++;
		}
		IMAGEMANAGER->findImage("Ÿ��Ʋȭ��")->setFrameX(t_index);


	}
}

void startScene::currentPos()
{
	if (INPUT->GetKeyDown(VK_DOWN))
	{
		if (state < 3)
		{
			state++;
			IMAGEMANAGER->findImage("���ø޴�")->setY(IMAGEMANAGER->findImage("���ø޴�")->getY() + 30);
			return;
		}
	}
	if (INPUT->GetKeyDown(VK_UP))
	{
		if (state > 0)
		{
			state--;
			IMAGEMANAGER->findImage("���ø޴�")->setY(IMAGEMANAGER->findImage("���ø޴�")->getY() - 30);
			return;
		}
	}

	if (INPUT->GetKeyDown(VK_SPACE)) {
		SOUNDMANAGER->stop("introBGM");

		switch (state)
		{
		case 0: // ����ϱ�
			SCENEMANAGER->loadScene("Ÿ��ε�");
			break;
		case 1: // ����
			SCENEMANAGER->loadScene("�����ε�");
			break;
		case 2: // �ɼ�
			break;
		case 3: // ������
			PostQuitMessage(0);
			break;
		default:
			break;
		}
	}

}


