#include "stdafx.h"
#include "Cloud.h"


HRESULT Cloud::init(tagPosF pos)
{
	_pos = pos;
	_speed = 0.8f;

	return S_OK;
}

void Cloud::release()
{
}

void Cloud::update()
{
	move();
}

void Cloud::render(HDC hdc)
{
	CAMERAMANAGER->AlphaRender(hdc, IMAGEMANAGER->findImage("ū����"), _pos.x, _pos.y, 100);
	CAMERAMANAGER->AlphaRender(hdc, IMAGEMANAGER->findImage("��������"), _pos.x + IMAGEMANAGER->findImage("ū����")->getWidth() / 2,
		_pos.y - IMAGEMANAGER->findImage("ū����")->getHeight() / 2, 100);
	
}

void Cloud::move()
{
	if (_pos.x <= -40 || _pos.y <= -40) {
		tagPosF tmp;
		tmp.x = RANDOM->range(WINSIZEX, IMAGEMANAGER->findImage("townBack")->getWidth());
		tmp.y = RANDOM->range(WINSIZEY, IMAGEMANAGER->findImage("townBack")->getHeight());

		_pos = tmp;
	}

	_angle = getAngle(_pos.x, _pos.y, -50, -50);

	_pos.x += cosf(_angle) * _speed;
	_pos.y += -sinf(_angle) * _speed / 2;
}
