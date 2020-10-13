#pragma once
#include "gameNode.h"
//=============================================================
//	## progressBar ## (���α׷����� = ü�¹� = �ε��� ���)
//=============================================================

class progressBar : public gameNode
{
private:
	image* _progressBarFront;		//ü�¹� �� �̹���(��Ʈ�����)
	image* _progressBarBack;		//ü�¹� �� �̹���(�������)
	RECT _rcProgress;				//ü�¹� ��Ʈ
	float _width;					//ü�¹� ���α���
	float _height;					//ü�¹� ���α���
	float _maxGauge;

public:
	HRESULT init(const char* frontImg, const char* backImg, float maxGauge);
	void release();
	void update(float currentHp);
	// ������
	void render(int x, int y);
	void alphaRender(int x, int y, BYTE alpha);
	void cameraRender(int x, int y);
	void cameraAlphaRender(int x, int y, BYTE alpha);
	void ZorderRender(float z, int x, int y);
	void ZorderAlphaRender(float z, int x, int y);

};

