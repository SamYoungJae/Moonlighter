#include "stdafx.h"
#include "arrow.h"

HRESULT arrow::init()
{
	IMAGEMANAGER->addFrameImage("ȭ��", "Images/�÷��̾�/arrow1X4.bmp", 52, 208, 1, 4);

	_x = PLAYER->getX();
	_y = PLAYER->getY();
	_rc = RectMake(_x, _y, 50, 20);

	_speed = 8;
	_alpha = 255;
	_isSkill = false;

	//_shadowArrow.img = IMAGEMANAGER->addFrameImage()
	//_shadowArrow.x = 0;
	//_shadowArrow.y = 0;
	//_shadowArrow.alpha = 255;

	return S_OK;
}

void arrow::release()
{

}

void arrow::update()
{
	this->animation();
	this->moveArrow();
}

void arrow::render(HDC hdc)
{

	switch (_arrowDirection)
	{
	case ARROW_DOWN:
		//IMAGEMANAGER->frameRender("ȭ��", hdc, _x - 20, _y);
		CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("ȭ��"), (_rc.bottom + _rc.top) / 2, _x - 20, _y, IMAGEMANAGER->findImage("ȭ��")->getFrameX(), IMAGEMANAGER->findImage("ȭ��")->getFrameY());
		break;
	case ARROW_UP:
		//IMAGEMANAGER->frameRender("ȭ��", hdc, _x - 20, _y);
		CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("ȭ��"), (_rc.bottom + _rc.top) / 2, _x - 10, _y, IMAGEMANAGER->findImage("ȭ��")->getFrameX(), IMAGEMANAGER->findImage("ȭ��")->getFrameY());
		break;
	case ARROW_RIGHT:
		//IMAGEMANAGER->frameRender("ȭ��", hdc, _x, _y - 20);
		CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("ȭ��"), (_rc.bottom + _rc.top) / 2, _x , _y - 20, IMAGEMANAGER->findImage("ȭ��")->getFrameX(), IMAGEMANAGER->findImage("ȭ��")->getFrameY());
		break;
	case ARROW_LEFT:
		//IMAGEMANAGER->frameRender("ȭ��", hdc, _x, _y - 20);
		CAMERAMANAGER->ZorderFrameRender(IMAGEMANAGER->findImage("ȭ��"), (_rc.bottom + _rc.top) / 2, _x , _y - 20, IMAGEMANAGER->findImage("ȭ��")->getFrameX(), IMAGEMANAGER->findImage("ȭ��")->getFrameY());
		break;
	}
}

void arrow::animation()
{
	IMAGEMANAGER->findImage("ȭ��")->setFrameY(_arrowDirection);
	IMAGEMANAGER->findImage("ȭ��")->setFrameX(0);
}

void arrow::shootArrow()
{
	switch (PLAYER->getPlayerDirection())
	{
	case 0:
		_arrowDirection = ARROW_DOWN;
		_x = PLAYER->getX() - 20;
		_y = PLAYER->getY() - 20;
		_rc = RectMake(_x, _y, 20, 50);
		break;
	case 1:
		_arrowDirection = ARROW_UP;
		_x = PLAYER->getX() - 20;
		_y = PLAYER->getY() - 20;
		_rc = RectMake(_x, _y, 20, 50);
		break;
	case 2:
		_arrowDirection = ARROW_RIGHT;
		_x = PLAYER->getX() - 20;
		_y = PLAYER->getY() - 20;
		_rc = RectMake(_x, _y, 50, 20);
		break;
	case 3:
		_arrowDirection = ARROW_LEFT;
		_x = PLAYER->getX() - 20;
		_y = PLAYER->getY() - 20;
		_rc = RectMake(_x, _y, 50, 20);
		break;
	}
}

void arrow::moveArrow()
{
	if (!PLAYER->getShoot())
	{
		this->shootArrow();
	}
	switch (_arrowDirection)
	{
	case ARROW_DOWN:
		_y += _speed;
		_rc = RectMake(_x, _y, 20, 50);
		break;
	case ARROW_UP:
		_y -= _speed;		
		_rc = RectMake(_x, _y, 20, 50);
		break;
	case ARROW_RIGHT:
		_x += _speed;
		_rc = RectMake(_x, _y, 50, 20);
		break;
	case ARROW_LEFT:
		_x -= _speed;
		_rc = RectMake(_x, _y, 50, 20);
		break;
	}
}
