#include "stdafx.h"
#include "noteBook.h"

HRESULT noteBook::init()
{
	//��Ʈ�ϸ޴� ��ġ �ʱ�ȭ 
	initPos();

	_menuMoveSpeed = 90.f;

	return S_OK;
}

void noteBook::release()
{
}

void noteBook::update()
{
}

void noteBook::render(HDC hdc)
{
	IMAGEMANAGER->findImage("menu_notebook")->render(hdc, _noteBookPos.x, _noteBookPos.y);
}

void noteBook::initPos()
{
	_noteBookPos.x = WINSIZEX;
	_noteBookPos.y = NOTEBOOKPOSY;
}

void noteBook::moveNoteBookLeft(int destPos)
{
	_noteBookPos.x -= _menuMoveSpeed;

	if (_noteBookPos.x <= destPos)
	{
		_noteBookPos.x = destPos;
	}
}

void noteBook::moveNoteBookRight(int destPos)
{
	_noteBookPos.x += _menuMoveSpeed;

	if (_noteBookPos.x >= destPos)
	{
		_noteBookPos.x = destPos;
	}
}
