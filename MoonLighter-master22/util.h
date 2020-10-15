#pragma once
//=============================================================
//	## namespace ## MY_UTIL
//=============================================================

#define PI 3.1415926f
#define PI2 (PI * 2)

#define DEGREE(p) (PI/180)*(p)

//���߿� �̹��� ȸ���� ����� ��
#define PI_2 (PI / 2) //90��
#define PI_4 (PI / 4) //45��
#define PI_8 (PI / 8) //22.5��

//���� ����ϴ� �� ���� 
#define SELECT_YES	1
#define SELECT_NO	0

namespace MY_UTIL
{
	//���� ������ �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);

	//���� ������ ����
	float getAngle(float startX, float startY, float endX, float endY);

	float RadianToDegree(float rad);
};

struct tagPosF
{
	float x;
	float y;

	tagPosF() { x = 0; y = 0; }
	tagPosF(float _x, float _y) { x = _x; y = _y; }
};
