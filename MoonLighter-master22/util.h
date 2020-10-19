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

//������ �ε��� ���� 
#define RICHJELLY_IDX		0
#define VENOMJELLY_IDX		1
#define CRYSTAL_IDX			2
#define VINE_IDX			3
#define TEETHSTONE_IDX		4
#define ROOT_IDX			5
#define IRONBAR_IDX			6
#define FOUNDRYRESTS_IDX	7
#define BROKENSWORD_IDX		8
#define FABRIC_IDX			9
#define HARDENEDSTEEL_IDX	10

#define POTION1_IDX			11
#define POTION2_IDX			12
#define TRAININGBOW_IDX		13
#define TRAININGSWORD_IDX	14

enum MESSAGE_TYPE
{
	LACK_OF_GOLD,
	LACK_OF_MATERIAL,
	LACK_OF_BOTH
};

//===================================================

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
