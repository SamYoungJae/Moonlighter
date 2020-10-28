#include "stdafx.h"
#include "loading.h"

HRESULT loadItem::init(string strKey, int width, int height)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_0;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_2;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, bool isBGM, bool isLoop)
{
	_kind = LOAD_KIND_SOUND;
	_soundResource.key = strKey;
	_soundResource.fileName = fileName;
	_soundResource.isBGM = isBGM;
	_soundResource.isLoop = isLoop;
	return S_OK;
}

//=============================================================
//	## loading ## (�ε�Ŭ���� - �ε�ȭ�� �����ϱ�, �ε���, ��׶���)
//=============================================================
HRESULT loading::init()
{
	//�ε�ȭ�� ��׶��� �̹��� �ʱ�ȭ
	//_background = IMAGEMANAGER->addImage("bgLoadingScene", "bgLoadingScene.bmp", WINSIZEX, WINSIZEY);
	//�ε��� �̹��� �ʱ�ȭ
	/*IMAGEMANAGER->addImage("loadingBarFront", "loadingBarFront.bmp", 600, 20);
	IMAGEMANAGER->addImage("loadingBarBack", "loadingBarBack.bmp", 600, 20);*/

	IMAGEMANAGER->addFrameImage("�ε�������", "Images/Ÿ��Ʋȭ��/load2��.bmp", 5896, 90, 67, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ε��ؽ�Ʈ", "Images/Ÿ��Ʋȭ��/loading.bmp", 1440, 44, 4, 1, true, RGB(255, 0, 255));
	////�ε��� Ŭ���� �ʱ�ȭ
	//_loadingBar = new progressBar;
	//_loadingBar->init("loadingBarFront", "loadingBarBack");
	////�ε��� ��ġ �ʱ�ȭ
	//_loadingBar->setPos(100, 500);

	//���� ������
	_currentGauge = 0;
	r_index = 0;
	_index = 0;
	_count = 0;

	return S_OK;
}

void loading::release()
{
	for (int i = 0; i < _vLoadItem.size(); i++)
	{
		SAFE_DELETE(_vLoadItem[i]);
	}
	_vLoadItem.clear();

}

void loading::update()
{
	//�ε��� Ŭ���� ������Ʈ
	//_loadingBar->update();
	loadingAnim();
}

void loading::render()
{
	//��׶��� �̹��� ����
	//_background->render(getMemDC());
	//�ε��� Ŭ���� ����
	//_loadingBar->render();

	if (_currentGauge < _vLoadItem.size())
	{
		if (_vLoadItem[_currentGauge]->getLoadKind() >= 1 && _vLoadItem[_currentGauge]->getLoadKind() <= 4)
		{
			TextOut(getMemDC(), 10, 50, _vLoadItem[_currentGauge]->getImageResource().fileName, strlen(_vLoadItem[_currentGauge]->getImageResource().fileName));
		}
		else if (_vLoadItem[_currentGauge]->getLoadKind() == LOAD_KIND_SOUND)
		{
			TextOut(getMemDC(), 10, 50, _vLoadItem[_currentGauge]->getSoundResource().fileName, strlen(_vLoadItem[_currentGauge]->getSoundResource().fileName));
		}
	}
	float per = (float)_currentGauge / (float)_vLoadItem.size();


	IMAGEMANAGER->frameRender("�ε��ؽ�Ʈ", getMemDC(), WINSIZEX / 2 - 200, WINSIZEY - 100);
	IMAGEMANAGER->frameRender("�ε�������", getMemDC(), WINSIZEX - 100, WINSIZEY - 100);

}

void loading::loadImage(string strKey, int width, int height)
{
	loadItem* item = new loadItem;
	item->init(strKey, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, x, y, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadSound(string key, const char * fileName, bool isBGM, bool isLoop)
{
	loadItem* item = new loadItem;
	item->init(key, fileName, isBGM, isLoop);
	_vLoadItem.push_back(item);
}

void loading::loadingAnim()
{
	IMAGEMANAGER->findImage("�ε�������")->setFrameY(0);
	IMAGEMANAGER->findImage("�ε��ؽ�Ʈ")->setFrameY(0);

	_count++;

	if (_count % 7 == 0)
	{
		r_index++;

		if (r_index > IMAGEMANAGER->findImage("�ε�������")->getMaxFrameX())
		{

			r_index = 0;
		}

		IMAGEMANAGER->findImage("�ε�������")->setFrameX(r_index);
	}

	if (_count % 15 == 0)
	{
		_index++;
		if (_index > IMAGEMANAGER->findImage("�ε��ؽ�Ʈ")->getMaxFrameX())
		{
			_index = 0;
		}
		IMAGEMANAGER->findImage("�ε��ؽ�Ʈ")->setFrameX(_index);
	}
}

bool loading::loadingDone()
{
	//�ε��Ϸ��
	if (_currentGauge >= _vLoadItem.size())
	{
		return true;
	}

	loadItem* item = _vLoadItem[_currentGauge];
	switch (item->getLoadKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
		}
		break;
		
		case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.isTrans, img.transColor);
		}
		break;
		
		case LOAD_KIND_IMAGE_2:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.isTrans, img.transColor);
		}
		break;
		
		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
		}
		break;
		
		case LOAD_KIND_FRAMEIMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
		}
		break;

		//�����е��� �ѹ� ����� ����
		case LOAD_KIND_SOUND:
		{
			tagSoundResource sound = item->getSoundResource();
			SOUNDMANAGER->addSound(sound.key, sound.fileName, sound.isBGM, sound.isLoop);
		}
		break;
	}
	
	//���� ������ ����
	_currentGauge++;

	//�ε��� �̹��� ����
	//_loadingBar->setGauge(_vLoadItem.size(), _currentGauge);

	return false;
}
