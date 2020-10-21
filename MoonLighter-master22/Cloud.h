#pragma once
class Cloud
{
private:
	tagPosF _pos;
	float _angle;
	float _speed;

public:
	HRESULT init(tagPosF pos);
	void release();
	void update();
	void render(HDC hdc);
	void move();

};
