#pragma once
#include "singletonBase.h"

class animation;

struct tagEffect
{
	animation* ani;
	float z;
	int x, y;
	bool _isAlpha;
	BYTE alpha;
};

struct tagParticle
{
	string imgKey;
	float angle;
	float z;
	float x, y;
	int frameX, frameY;
	bool isAlpha;
	BYTE alpha;
	int count;
	float speed;
};

class effectManager : public singletonBase<effectManager>
{
private:
	vector<tagEffect> _vEffect;			// ����Ʈ �ִϸ��̼� ���� ����
	vector<tagParticle> _vParticle;
public:
	effectManager() {};
	~effectManager() {};

			// ( z����, x��ǥ, y��ǥ, ����� frameY, ����ӵ�)
	HRESULT addEffect(string key, float z, int x, int y, int frameY, int playSpeed, bool isAlpha = 0, BYTE alpha = 0);
	void update();
	void render();
	void release();
	void deleteAnimation(int idx);

	HRESULT addParticle(string key, float z, int x, int y, bool isAlpha = false, BYTE alpha = 0);
	void delParticle(int idx);
};

