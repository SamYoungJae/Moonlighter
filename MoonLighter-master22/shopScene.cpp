#include "stdafx.h"
#include "shopScene.h"

void shopScene::ItemPosSet()
{
	/*int displayX[4] = { 472 , 520 , 472 , 520 };
	int displayY[4] = { 646 , 646 , 694 , 694 };*/

	v_itemPos.push_back(make_pair(472, 646));
	v_itemPos.push_back(make_pair(520, 646));
	v_itemPos.push_back(make_pair(472, 694));
	v_itemPos.push_back(make_pair(520, 694));

	v_itemShadowPos.push_back(make_pair(486, 690));
	v_itemShadowPos.push_back(make_pair(534, 690));
	v_itemShadowPos.push_back(make_pair(486, 738));
	v_itemShadowPos.push_back(make_pair(534, 738));

}

HRESULT shopScene::init()
{
	//Ŭ���� �ʱ�ȭ
	

	_npc = new ShopNpcManager;
	_npc->init();

	_displayStand = new displayStand;
	_displayStand->init();

	PLAYER->init();
	PLAYER->setX(700);
	PLAYER->setY(850);

	CAMERAMANAGER->init(PLAYER->getX(), PLAYER->getY(), 2000, 1000, 0, 0, WINSIZEX / 2, WINSIZEY / 2);

	_npcTime = 0;
	//675 870
	GoTownPortal = RectMake(670, 1000, 80, 50);

	IMAGEMANAGER->addImage("temp", 2000, 1000);

	CAMERAMANAGER->FadeInit(80, FADE_IN);
	CAMERAMANAGER->FadeStart();

	ItemPosSet();

	_visit = false;
	return S_OK;
}

void shopScene::release()
{
	//_npc->release();

	//_displayStand->release();
	//SAFE_DELETE(_displayStand);
}

void shopScene::update()
{
	if (!CAMERAMANAGER->getFadeIsStart() && !_visit) {
		_visit = true;
		SOUNDMANAGER->play("���ݾ�");
	}

	if (!SOUNDMANAGER->isPlaySound("�������")) {
		SOUNDMANAGER->play("�������", 0.3f);
	}

	_npc->update();
	_displayStand->update();

	ITEMMENU->update();
	PLAYER->update();
	CAMERAMANAGER->movePivot(PLAYER->getX(), PLAYER->getY());
	CAMERAMANAGER->update(PLAYER->getX(), PLAYER->getY());

	PlayerCol();
	PortaltoTown();
}

void shopScene::render()
{
	
	IMAGEMANAGER->findImage("�����ȼ�")->render(IMAGEMANAGER->findImage("temp")->getMemDC(), 304, 132);
	CAMERAMANAGER->Render(getMemDC(), IMAGEMANAGER->findImage("������"), 304, 132);
	//CAMERAMANAGER->Render(getMemDC() , IMAGEMANAGER->findImage("�����ȼ�"), 304, 132);
	
	_npc->render();
	
	CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("�������"), 458 + IMAGEMANAGER->findImage("�������")->getFrameHeight(), 654, 458);

	CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("������"), 870 + IMAGEMANAGER->findImage("������")->getFrameHeight(), 638, 870);

	CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("����ħ��"), 302 + IMAGEMANAGER->findImage("����ħ��")->getFrameHeight()/4, 752, 302);

	CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("��������"), 674 + IMAGEMANAGER->findImage("��������")->getFrameHeight()/4, 472, 674);

	CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("����å��"), 670 + IMAGEMANAGER->findImage("����å��")->getFrameHeight()/4, 646, 670);
	
	for (int i = 0; i < ITEMDESKCOUNT; i++)
	{
		if (_displayStand->getDisplayItem()[i].getType() == ITEM_EMPTY) continue; 
		
		CAMERAMANAGER->ZorderRender(_displayStand->getDisplayItem()[i].getItemImg(),
			680 + _displayStand->getDisplayItem()[i].getItemImg()->getHeight() / 2
			, v_itemPos[i].first, v_itemPos[i].second);
		
		CAMERAMANAGER->ZorderAlphaRender(IMAGEMANAGER->findImage("�����۱׸���")
			, 700 + IMAGEMANAGER->findImage("�����۱׸���")->getHeight()
			, v_itemShadowPos[i].first, v_itemShadowPos[i].second, 60);
	}

	CAMERAMANAGER->ZorderTotalRender(getMemDC());

	char str[256];
	POINT tmp = CAMERAMANAGER->getRelativeMouse(_ptMouse);

	wsprintf(str, "X: %d", tmp.x);
	TextOut(getMemDC(), 5, 150, str, strlen(str));
	wsprintf(str, "Y: %d", tmp.y);
	TextOut(getMemDC(), 5, 170, str, strlen(str));

	PLAYER->render(getMemDC());
	ITEMMENU->render(getMemDC());
	_displayStand->render();
	//IMAGEMANAGER->findImage("������")->render(getMemDC(), 304, 132);

	//CAMERAMANAGER->Rectangle(getMemDC(), GoTownPortal);
	//Rectangle(getMemDC(), GoTownPortal);

	//CAMERAMANAGER->Rectangle(getMemDC(), PLAYER->getShadowRect());
}

void shopScene::PortaltoTown()
{
	RECT tmp;
	if (IntersectRect(&tmp , &PLAYER->getShadowRect() , &GoTownPortal))
	{
		SOUNDMANAGER->stop("�������");
		SCENEMANAGER->loadScene("Ÿ��ȭ��");

		PLAYER->setX(1680);
		PLAYER->setY(450);
	}
}

void shopScene::PlayerCol()
{
	if (INPUT->GetKey(VK_SPACE))
	{
		PLAYER->setPlayerState(PLAYER_STATE::PLAYER_IDLE);
	}

	if (GetPixel(IMAGEMANAGER->findImage("temp")->getMemDC(),
		(PLAYER->getShadowRect().left + PLAYER->getShadowRect().right) /2 , PLAYER->getShadowRect().top) == RGB(255, 0, 0) ||
		GetPixel(IMAGEMANAGER->findImage("temp")->getMemDC(),
		(PLAYER->getShadowRect().left + PLAYER->getShadowRect().right) / 2, PLAYER->getShadowRect().bottom) == RGB(255, 0, 0) ||
		GetPixel(IMAGEMANAGER->findImage("temp")->getMemDC(),
		PLAYER->getShadowRect().left, (PLAYER->getShadowRect().bottom + PLAYER->getShadowRect().top) /2) == RGB(255, 0, 0) ||
		GetPixel(IMAGEMANAGER->findImage("temp")->getMemDC(),
		PLAYER->getShadowRect().right, (PLAYER->getShadowRect().bottom + PLAYER->getShadowRect().top) / 2) == RGB(255, 0, 0)) {

		if (PLAYER->getLeft()) {
			PLAYER->setX(PLAYER->getX() + 4);
		}
		if (PLAYER->getRight()) {
			PLAYER->setX(PLAYER->getX() - 4);
		}
		if (PLAYER->getUp()) {
			PLAYER->setY(PLAYER->getY() + 4);
		}
		if (PLAYER->getDown()) {
			PLAYER->setY(PLAYER->getY() - 4);
		}
	}
}
