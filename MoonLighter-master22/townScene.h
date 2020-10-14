#pragma once
#include "gameNode.h"
#include "npcManager.h"
class townScene : public gameNode
{
private:
	//Ÿ�� ���μ��α���
	int _tileX;
	int _tileY;

	//��ü Ÿ�� ���� �����Ͽ� first �� Ÿ������ second�� ������Ʈ ������ �������
	//�������� Ÿ���� ������� �����Ƿ� second���� �̿��ҿ����Դϴ�
	vector<pair<tagTile, tagTile>> _vTiles;

	vector<tagTile> _vTest; // ��� �̰� ���°� �´°��� - ����� ����

	npcManager* _npcManager;

	vector<animation*> _objManager; // �ǹ� �ִϸ��̼� ���� - ����� ����
	//ī�޶� �׽�Ʈ�� �ǹ�
	float _pivotX, _pivotY;

	RECT shopPortal;       // ���� ��Ż �߰� - ����� ����
	RECT gotoDungeonPortal;// �������±� ��Ż �߰� - ����� ����

	int _index;
	int _count;
public:

	HRESULT init();
	void release();
	void update();
	void render();

	void portalColl(); // ��Ż �̵� �߰� - ����� ����
	void ObjectColl(); // �÷��̾� -> ������Ʈ �浹ó�� - ����� ����
	void ObjectAnim(); // ������Ʈ �ִϸ��̼� �Լ� - ����� ����

	void ObjectSetAnim(); // _objManager ���� - ����� ����

};
