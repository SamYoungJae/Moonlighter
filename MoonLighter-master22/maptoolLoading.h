#pragma once
#include "gameNode.h"
#include "loading.h"
#include "maptoolScene.h"

class maptoolLoading : public gameNode
{
private:
	loading* _loading;

public:
	maptoolLoading() : _loading(nullptr) {}
	~maptoolLoading() {}

	HRESULT init();
	void release();
	void update();
	void render();

	//�ε��̹��� �Լ� (�̰��� �̹����� ���� �־��)
	void loadingImage();
	//�ε����� �Լ� (�̰��� ���带 ���� �־��)
	void loadingSound();
};

