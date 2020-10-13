#pragma once
#include "item.h"
#define WISHLISTPOSX	232
#define WISHLISTPOSY	130

class wishList
{
private:
	POINT _wishListPos;		//���ø���Ʈ ��ġ 
	float _menuMoveSpeed;	//�޴��� �̵��ϴ� �ӵ� 

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	POINT getWishListPos() { return _wishListPos; }					//���ø���Ʈ ��ġ�� get�Լ�
	void setWishListPosX(int posX) { _wishListPos.x = posX; }		//���ø���Ʈ x��ǥ set�Լ�
	void setWishListPosY(int posY) { _wishListPos.y = posY; }		//���ø���Ʈ y��ǥ set�Լ� 
	void initPos();
	void moveWishListLeft(int destPos);								//���ø���Ʈ�� destPos���� �������� �̵���Ŵ						
	void moveWishListRight(int destPos);							//���ø���Ʈ�� destPos���� �������� �̵���Ŵ
};

