#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	
	AddFontResource("Fonts\JejuGothic.ttf");
	hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
	oldFont = (HFONT)SelectObject(getMemDC(), hFont);
	DeleteObject(oldFont);
	/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
	/*�̰����� ������ ������ �߰��ϰ� ������� �����Ѵ�*/

	SCENEMANAGER->addScene("�����ε�", new maptoolLoading);
	SCENEMANAGER->addScene("����ȭ��", new maptoolScene);
	SCENEMANAGER->addScene("Ÿ��Ʋȭ��", new startScene);
	SCENEMANAGER->addScene("Ÿ��ε�", new townLoading);
	SCENEMANAGER->addScene("Ÿ��ȭ��", new townScene);
	SCENEMANAGER->addScene("�븻����", new nomalDungeonScene);
	SCENEMANAGER->addScene("��������", new bossDungeonScene);
	SCENEMANAGER->addScene("�����ε�", new dungeonLoading);
	SCENEMANAGER->addScene("�����ε�", new shopLoading);
	SCENEMANAGER->addScene("����ȭ��", new shopScene);
	SCENEMANAGER->addScene("�������±�", new gotoDungeon);
	SCENEMANAGER->addScene("�������Ǵ�", new displayStand);
	SCENEMANAGER->addScene("�����ε�", new bossLoading);

	PLAYER->init();

	SCENEMANAGER->loadScene("Ÿ��ε�");

	CAMERAMANAGER->FadeInit(1, FADE_IN);

	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	//PLAYER->release();
	gameNode::release();
}

//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	//����Ŵ��� ������Ʈ (�̰� ������ ����Ŵ��� ����� �������� �ʴ´�!!!)
	SOUNDMANAGER->update();

	//������ ��Ʈ
	DAMAGEFONT->update();
	//����Ʈ �Ŵ��� ������Ʈ
	EFFECTMANAGER->update();

	CAMERAMANAGER->FadeUpdate();

	PLAYERDATA->update();
}

//=============================================================
//	## ���� ## render()
//=============================================================
void mainGame::render()
{
	//��� �� ��Ʈ�� (�̰��� ������ �׳� �α�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================
	//���ڻ� ��� ���ֱ�
	SetBkMode(getMemDC(), TRANSPARENT);
	SCENEMANAGER->render();

	INPUT->Update();
	//����Ʈ �Ŵ�������
	EFFECTMANAGER->render();
	//������ ��Ʈ ����
	DAMAGEFONT->render(getMemDC());
	//�������� ��������� �ּ�����
	TIMEMANAGER->render(getMemDC());
	
	PLAYERDATA->render(getMemDC());
	CAMERAMANAGER->FadeRender(getMemDC());

//=============================================================
	//������� ������ ȭ��DC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC());
}

