#include "stdafx.h"
#include "townScene.h"
#include "mapSaveLoad.h"		//������� ������ ���� �ʿ��Ѱ����� ��Ŭ����ؼ� ���

HRESULT townScene::init()
{
	_vTest = mapSaveLoad::getSingleton()->loadObject("maptool/town3", 74, 60);

	IMAGEMANAGER->addImage("test", 2590, 2100);

	_npcManager = new npcManager;
	_npcManager->init(_vTest);

	PLAYER->init();
	CAMERAMANAGER->init(PLAYER->getX(), PLAYER->getY(), 2590, 2100, 0, 0, WINSIZEX / 2, WINSIZEY / 2);
	ITEMMENU->init();

	shopPortal = RectMake(1650, 315 , 80 , 80);
	gotoDungeonPortal = RectMake(460, 0, 460, 20);

	_index = 0;
	_count = 0;

	ObjectSetAnim();

	CAMERAMANAGER->FadeInit(80, FADE_IN);
	CAMERAMANAGER->FadeStart();

	// ��Ż 
	if (PLAYERDATA->getIsEmblemReturn())
	{
		_potal = new potal;
		_potal->init(300, 200, POTAL_INIT);
		PLAYER->setX(300);
		PLAYER->setY(205);
		PLAYER->setPlayerDirection(0);
	}
	else _potal = nullptr;

	if (PLAYERDATA->getIsPendantReturn())
	{
		PLAYER->setX(300);
		PLAYER->setY(205);
		PLAYER->setPlayerState(PLAYER_DIE_PORTAL);
		PLAYER->setPlayerDirection(0);
	}

	this->initPotal();
	return S_OK;
}

void townScene::release()
{
	//_npcManager->release();
}

void townScene::update()
{
	//PLAYER->setPlace(SHOP);
	if (!SOUNDMANAGER->isPlaySound("�������")) 
	{
		SOUNDMANAGER->play("�������", 0.3f);
	}
	else 
	{
		if (ITEMMENU->getOpenMenu()) SOUNDMANAGER->setVolumn("�������", 0.08f);
		else SOUNDMANAGER->setVolumn("�������", 0.3f);
	}

	//====================================================
	if (INPUT->GetKeyDown('G')) {
		SOUNDMANAGER->stop("�������");
		SCENEMANAGER->loadScene("�����ε�");
	}
	if (INPUT->GetKeyDown('H')) {
		SOUNDMANAGER->stop("�������");
		SCENEMANAGER->loadScene("�����ε�");
	}
	if (INPUT->GetKeyDown('P')) {
		SOUNDMANAGER->stop("�������");
		SCENEMANAGER->loadScene("�����ε�");
	}
	if (INPUT->GetKeyDown('U')) {
		//SOUNDMANAGER->stop("�������");
		SCENEMANAGER->loadScene("�������±�");
	}

	if (!_potal || (_potal->getPotalState() != POTAL_INIT && _potal->getPotalState() != POTAL_PLAYERIN && _potal->getPotalState() != POTAL_PLAYEROUT))
	PLAYER->update();

	this->updatePotal();

	CAMERAMANAGER->movePivot(PLAYER->getX(), PLAYER->getY());
	CAMERAMANAGER->update(PLAYER->getX(), PLAYER->getY());
	//====================================================

	_npcManager->update();
    ITEMMENU->update();

	portalColl(); // ��Ż �̵� �߰� - ����� ����
	ObjectAnim();
	ObjectColl();

}

void townScene::render()
{
	CAMERAMANAGER->Render(getMemDC(), IMAGEMANAGER->findImage("townBack"), 0, 0);
	
	for (int i = 0; i < _objManager.size(); i++)
	{
		RECT tmp;
		if (!IntersectRect(&tmp, &_objManager[i]->getRect(), &CAMERAMANAGER->getRect())) continue;

		RECT temp;
		temp = RectMake(_objManager[i]->getRect().left + _objManager[i]->getImage()->getFrameWidth() / 8,
			_objManager[i]->getRect().top + (_objManager[i]->getRect().bottom - _objManager[i]->getRect().top)/8,
			(_objManager[i]->getRect().right - _objManager[i]->getRect().left) / 1.3,
			(_objManager[i]->getRect().bottom - _objManager[i]->getRect().top) / 2);

		//CAMERAMANAGER->Rectangle(getMemDC(), temp); //����׿� -> z������Ʈ 

		RECT temp2;
		if (_objManager[i]->getKey() == "��Ȳ����" || _objManager[i]->getKey() == "������Ȳ����" || _objManager[i]->getKey() == "�ʷϳ���") {
			
			temp2 = RectMake(_objManager[i]->getRect().left + _objManager[i]->getImage()->getFrameWidth() / 4,
				_objManager[i]->getRect().top + (_objManager[i]->getRect().bottom - _objManager[i]->getRect().top)/2,
				(_objManager[i]->getRect().right - _objManager[i]->getRect().left) - _objManager[i]->getImage()->getFrameWidth() / 3,
				(_objManager[i]->getRect().bottom - _objManager[i]->getRect().top) - _objManager[i]->getImage()->getFrameHeight()*0.6);
		}
		else {
			temp2 = RectMake(_objManager[i]->getRect().left + _objManager[i]->getImage()->getFrameWidth() / 40,
				_objManager[i]->getRect().top + (_objManager[i]->getRect().bottom - _objManager[i]->getRect().top)/4,
				//(_objManager[i]->getRect().right - _objManager[i]->getRect().left/10),
				_objManager[i]->getImage()->getFrameWidth()- _objManager[i]->getImage()->getFrameWidth() / 40,
				(_objManager[i]->getRect().bottom - _objManager[i]->getRect().top) - _objManager[i]->getImage()->getFrameHeight()*0.3);

		}

		//CAMERAMANAGER->Rectangle(getMemDC(), temp2); //����׿� -> �浹��Ʈ

		if (IntersectRect(&tmp, &PLAYER->getShadowRect(), &temp)) {
			if (_objManager[i]->getKey() == "���ΰ���" || _objManager[i]->getKey() == "���ִ���") {
				_objManager[i]->ZoderAlphaRender(_objManager[i]->getRect().top + _objManager[i]->getImage()->getFrameHeight() / 2,
					_objManager[i]->getRect().left - 15, _objManager[i]->getRect().top, 150);
			}
			else {
				_objManager[i]->ZoderAlphaRender(_objManager[i]->getRect().top + _objManager[i]->getImage()->getFrameHeight() / 2,
					_objManager[i]->getRect().left, _objManager[i]->getRect().top, 150);
			}
		}
		else {
			if (_objManager[i]->getKey() == "���ΰ���" || _objManager[i]->getKey() == "���ִ���") {
				_objManager[i]->ZoderRender(_objManager[i]->getRect().top + _objManager[i]->getImage()->getFrameHeight() / 2,
					_objManager[i]->getRect().left - 15, _objManager[i]->getRect().top);
			}
			else {
				_objManager[i]->ZoderRender(_objManager[i]->getRect().top + _objManager[i]->getImage()->getFrameHeight() / 2,
					_objManager[i]->getRect().left, _objManager[i]->getRect().top);
			}
		}
	}

	CAMERAMANAGER->ZorderTotalRender(getMemDC());
	_npcManager->render();

	if (!_potal || (_potal->getPotalState() != POTAL_INIT && _potal->getPotalState() != POTAL_PLAYERIN && _potal->getPotalState() != POTAL_PLAYEROUT))
		PLAYER->render(getMemDC());

	ITEMMENU->render(getMemDC());

	this->renderPotal();

	//CAMERAMANAGER->Rectangle(getMemDC(), shopPortal);
	//CAMERAMANAGER->Rectangle(getMemDC(), gotoDungeonPortal);

	//Rectangle(getMemDC(), PLAYER->getShadowRect());
	/*char str[256];
	POINT tmp = CAMERAMANAGER->getRelativeMouse(_ptMouse);

	wsprintf(str, "X: %d", tmp.x);
	TextOut(getMemDC(), 5, 150, str, strlen(str));
	wsprintf(str, "Y: %d", tmp.y);
	TextOut(getMemDC(), 5, 170, str, strlen(str));*/

}

void townScene::portalColl()
{
	RECT tmp;
	if (IntersectRect(&tmp , &PLAYER->getShadowRect() , &gotoDungeonPortal))
	{
		SCENEMANAGER->loadScene("�������±�");
	}
	if (IntersectRect(&tmp, &PLAYER->getShadowRect(), &shopPortal))
	{
		SOUNDMANAGER->stop("�������");
		SCENEMANAGER->loadScene("�����ε�");
		SOUNDMANAGER->play("��������0");
	}
}

void townScene::ObjectColl()
{
	for (int i = 0; i < _objManager.size(); i++)
	{
	    RECT tmp;
		if (!IntersectRect(&tmp, &_objManager[i]->getRect(), &CAMERAMANAGER->getRect())) continue;
		
			RECT temp;
			
			temp = RectMake(_objManager[i]->getRect().left + _objManager[i]->getImage()->getFrameWidth() / 8,
				_objManager[i]->getRect().top + (_objManager[i]->getRect().bottom - _objManager[i]->getRect().top) / 8,
				(_objManager[i]->getRect().right - _objManager[i]->getRect().left) / 1.3,
				(_objManager[i]->getRect().bottom - _objManager[i]->getRect().top) / 2);


			if (_objManager[i]->getKey() == "��Ȳ����" || _objManager[i]->getKey() == "������Ȳ����" || _objManager[i]->getKey() == "�ʷϳ���") {
				temp = RectMake(_objManager[i]->getRect().left + _objManager[i]->getImage()->getFrameWidth() / 4,
					_objManager[i]->getRect().top + (_objManager[i]->getRect().bottom - _objManager[i]->getRect().top) / 2,
					(_objManager[i]->getRect().right - _objManager[i]->getRect().left) - _objManager[i]->getImage()->getFrameWidth() / 3,
					(_objManager[i]->getRect().bottom - _objManager[i]->getRect().top) - _objManager[i]->getImage()->getFrameHeight()*0.6);
			}
			else {
				temp = RectMake(_objManager[i]->getRect().left + _objManager[i]->getImage()->getFrameWidth() / 40,
					_objManager[i]->getRect().top + (_objManager[i]->getRect().bottom - _objManager[i]->getRect().top) / 4,
					//(_objManager[i]->getRect().right - _objManager[i]->getRect().left/10),
					_objManager[i]->getImage()->getFrameWidth() - _objManager[i]->getImage()->getFrameWidth() / 40,
					(_objManager[i]->getRect().bottom - _objManager[i]->getRect().top) - _objManager[i]->getImage()->getFrameHeight()*0.3);
			}

			if(IntersectRect(&tmp, &PLAYER->getShadowRect(), &temp)) {
				int wid = tmp.right - tmp.left;
				int hei = tmp.bottom - tmp.top;

				if (wid > hei) // ���Ʒ�
				{
					if (tmp.top == PLAYER->getShadowRect().top) // �Ʒ�
					{
						PLAYER->setY(PLAYER->getY() + hei);
					}
					else  // ��
					{
						PLAYER->setY(PLAYER->getY() - hei);
					}
				}
				else  // �翷
				{
					if (tmp.left == PLAYER->getShadowRect().left) // ������
					{
						PLAYER->setX(PLAYER->getX() + wid);
					}
					else // ����
					{
						PLAYER->setX(PLAYER->getX() - wid);
					}
				}
		}
	}
}

void townScene::ObjectAnim()
{
	RECT tmp;
	for (int i = 0; i < _objManager.size(); i++)
	{
		if (!IntersectRect(&tmp, &_objManager[i]->getRect(), &CAMERAMANAGER->getRect())) continue;
		_objManager[i]->update();
	}
}

void townScene::ObjectSetAnim()
{
	for (int i = 0; i < _vTest.size(); i++) {

		if (_vTest[i].obj != OBJ_NPC && _vTest[i].key != "") {
			animation* anim;
			anim = new animation;
			anim->init(IMAGEMANAGER->findImage(_vTest[i].key), 0, 7, _vTest[i].rc, _vTest[i].key, true, false);
			_objManager.push_back(anim);
		}
	}
}

HRESULT townScene::initPotal()
{
	

	return S_OK;
}

void townScene::updatePotal()
{
	if (!_potal) return;
	_potal->update();

	if (INPUT->GetKeyDown('J') && _potal->getIsInRange())
	{
		_potal->setPotalState(POTAL_PLAYERIN);
	}
	if (_potal->getPotalState() == POTAL_PLAYERIN && _potal->getAnimation()->getAniState() == ANIMATION_END)
	{
		SOUNDMANAGER->stop("�������");
		SCENEMANAGER->loadScene("�����ε�");
	}

}

void townScene::renderPotal()
{
	if (!_potal) return;
	_potal->render();
}
