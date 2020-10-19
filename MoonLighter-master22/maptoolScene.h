#pragma once
#include "gameNode.h"
#include "tileNode.h"
class maptoolScene : public gameNode
{
private:
	image* _backImg;
	int _count; // �ִϸ��̼� �ð�����
	int _alpha; // ���ķ��� ����
	object* _obj; //������Ʈ , NPC

	vector<tagTile> _vTiles; // Ÿ�� ����

	vector<tagTile> _vObject;  // ������Ʈ ����

	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY]; // ����Ÿ�� 5 * 5 ��

	tagSampleTile _sampleObject[SAMPLEOBJECT]; // ���� ������Ʈ 12 ��

	tagSampleTile _sampleNpc[SAMPLENPC]; //���� ���Ǿ� 8��

	tagCurrentTile _currentTile; //����Ÿ��

	RECT _tagSize;		//������ �±׸޴�
	RECT _tagTile;		//Ÿ�� �±׸޴�
	RECT _tagData;		//������ �±׸޴� 

	RECT _rcSave;		//���̺�
	RECT _rcLoad;		//�ε�
	RECT _rcTerrain;	//����
	RECT _rcObject;		//������Ʈ
	RECT _rcNpc;		//npc
	RECT _rcEraser;		//���찳 (������Ʈ�� �����, ������ ������)
	RECT _rcReset;		//���� 
	RECT _rcMoveBan;
	RECT _rcMovePosible;
	RECT _rcPortal;
	RECT _rcState;		//Ÿ�� ������Ʈ ��ư 

	RECT _button30;		//30 * 30 ��Ʈ
	RECT _button50;		//50 * 50 ��Ʈ

	RECT _rcArrowUp;	//��ũ�� �� ȭ��ǥ
	RECT _rcArrowDown;

	CTRL _ctrlSelect;	//���� � ��Ʈ�� ��������
                  
	int tile_X;			
	int tile_Y;

	int _index;

	float _pivotX, _pivotY;

	RECT _menuBar;    //�޴���
	bool _menuBarOn;  //�޴��� ON OFF
	bool _eraserOn;  //���찳 ON OFF bool ����

	float _curScrollY;	//��ũ�ѹ��� ���� y��ǥ ��	
	float _maxScrollY;	//��ũ�ѹ��� �ִ� y��(��ũ�ѹ��� ����)		
	float _barLength;	//��ũ�ѹ��� �ٱ��� 
	float _menuLength;	//��µǴ� ���� �޴��� ���� 
	float _startY;		//���� �̹����� ��µǴ� ������ǥ�� y 
	int _page;			//���� �������� �ִ� ������
	
	bool isleftdown;
	bool isleft;
	bool isleftUp;

	bool objectHit;

	POINT _dragStartPos;		//�巡�� ��������
	POINT _dragEndPos;			//�巡�� ������ ����
	POINT _cmMouse;				//ī�޶� �����ǥ�� �̿��� ���콺
	int _dragSizeX;				//�巡�� ���ΰ���	
	int _dragSizeY;				//�巡�� ���ΰ���
	bool _isAutoDrag;
	image* _alphaRect;
	image* _miniMap;

	static char fileName[128];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//��������
	void maptoolSetup();
	void maptoolSetup(int x, int y);
	void setMap();
	void save();
	void save(string fileName);
	void load();
	void load(string fileName);
	bool checkTileMap(int arr);
	void moveRect();
	void checkButton();
	void animation();
	void objecrRectRender();
	void eraseMap();
	void eraseTerrain();
	void eraseObject();
	void eraseNPC();
	void eraseState();
	//�����޴�
	void toggleMenu();
	void toggleEraser();
	void setCtrlBtns();
	void clickSaveBtn();
	void clickLoadBtn();
	void clickCtrlType();
	void clickTileSizeThirty();
	void clickTileSizeFifty();
	void clickTileTown();
	void clickTileDungeon();
	void clickTileGotoDungeon();
	void clickTileBossDungeon();
	void clickResetBtn();
	void clickMoveBanBtn();
	void clickPortalBtn();
	void eraserRender();
	void ClickTagMenu();
	void menuBarRender();
	void scrollBarRender(); //��ũ�ѹ� ��� 
	void tileArrowUp(); //��ũ�ѹ��� ������ ȭ��ǥ Ŭ��	
	void tileArrowDown(); //��ũ�ѹ��� �Ʒ����� ȭ��ǥ Ŭ��	
	bool checkObject(); //������Ʈ �浹 �˻�

    // npc object ������
	int npc_index[SAMPLENPC];
	int object_index[SAMPLEOBJECT];

	const char* npcStr[SAMPLENPC] = {
		"������npc","���","������","����","����յ�","�����Ѹ�","��","����Ż�������","�ذ�����" , "�׾Ƹ�",
		"������" , "babySlime"
	};

	//��� ������Ʈ �߰���. - ����� ����
	const char* objectStr[SAMPLEOBJECT] = {
		"��������","���ִ���","���ΰ���","���ǻ���","�Խ���","���������","����","������","�ʷϳ���","������Ȳ����","��Ȳ����","�м���",
		"������","������2","������3","������4","������5","�����Ѹ�","�����Ѹ�2","������Ʈ","����å","��������","������","������������",
		"�밢������","���尣","�̰ǹ�����","�ظ���" , "��Ÿ����","���峭�м�","��������","��������"
	};

	//����, ������Ʈ �����ϱ�
	TERRAIN terrainSelect(int frameX, int frameY, string key);
	OBJECT objectSelect(int frameX, int frameY);
	OBJECT NPCSelect(int frameX, int frameY);

	//�巡�� ������ ����
	void setDragStartPos(POINT ptMouse);
	//�巡�� �������� ������Ʈ
	void setDragEndPos(POINT ptMouse);
	//�巡�� ���� �������� Ÿ�ϱ��
	void setDragTerrain(bool isAuto);
	//�巡�� �����ȿ� Ÿ���� �ֳ�?
	bool isTileInDragRange(int i);
	//�巡�� �����ӷ�Ʈ ����������
	void dragFrameRectRender(COLORREF color);
	void autoDragFrameRectRender();
	//�巡�� Ÿ�� �Է� �˰���
	void autoDungeonSet(vector<tagTile> &vTile, int index, POINT size, POINT frame, RECT range);
	void autoGrassSet(vector<tagTile> &vTile, int index, POINT size, POINT frame, RECT range);
	void autoHoleSet(vector<tagTile> &vTile, int index, POINT size, POINT frame, RECT range);
	//�巡������ Ÿ���� ���� ���� ���� �����ֱ�
	void dragCount();
	//�巡���� ���콺�� ī�޶� �̵�
	void dragMouseFix();
	//ī�޶� ���콺 ������Ʈ
	void cmMouseUpdate();
	//���� ��Ʈ ����
	void alphaRectangle(RECT rc, BYTE alpha, COLORREF color,bool isCameraRender);

	//�̵����� ���¼���
	void setTileState();
	void autoSetTileState();
	void tileStateRender();

	void changeSampletile();
	void miniMapRender();

	void saveImage();

	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

