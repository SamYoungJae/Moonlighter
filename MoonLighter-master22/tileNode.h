#pragma once
#include "object.h"
//����ȭ�� Ÿ��
#define TILESIZE 35

//�̹��� Ÿ�� (ȭ�� ������ܿ� �ٿ����� ����Ÿ��)
#define SAMPLETILEX 5
#define SAMPLETILEY 5

#define SAMPLEOBJECT 32
#define SAMPLEOBJECTX 2
#define SAMPLEOBJECTY 2

#define SAMPLENPC 12
#define SAMPLENPCX 2
#define SAMPLENPCY 2

//�������� ����� ��Ʈ��
enum CTRL
{
	CTRL_DATA, CTRL_SAVE, CTRL_LOAD,
	CTRL_TERRAIN, CTRL_OBJECT, CTRL_NPC, CTRL_ERASER,
	CTRL_SIZE, CTRL_NONE, CTRL_TILESTATE
};

//����
enum TERRAIN
{
	TR_DUNGEONWALL, TR_GRASS, TR_OTHERS,TR_HOLE,TR_BLOCK, TR_NONE
};

enum TILESTATE
{
	TS_MOVEBAN, TS_PORTAL, TS_EMPTY, TS_HOLE
};

//������Ʈ
enum OBJECT
{
	OBJ_OBJECT,
	OBJ_NPC,
	OBJ_NONE
};
//Ÿ�ϱ���ü
struct tagTile
{
	TILESTATE tState;
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;

	string key;		//Ÿ�� / ������Ʈ �̹����� Ű��
};

//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	string key;
};

struct tagSampleObject
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

//����Ÿ�� ����ü
struct tagCurrentTile
{
	TILESTATE tState;
	int x, y;
	string key;
	RECT rc;
};

struct tagTileUI
{
	RECT rc;
	int tileSizeX;
	int tileSizeY;
	wstring s;
};
