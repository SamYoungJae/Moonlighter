#pragma once
#include "gameNode.h"
#define MAX_NPC 4

class displayStand;

enum NPC_ACTION
{
	NPC_MOVE,
	NPC_STOP,
	NPC_CHECK_PRICE,
	NPC_WAIT,
	NPC_GO_HOME,
	NPC_ITEM_PICK
};

enum NPC_MAP
{
	NPC_SHOP
};
class npc : public gameNode
{
private:
	animation* _aniNpc; // npc 애니메이션 변수
	animation* _aniPriceCheck; // 이모티콘 애니메이션 변수
	image* _peekItemImg; // 현재 잡고 있는 아이템 이미지
private:
	int _count;
	int _idx;
	int _time;
	float _speed;
	float _angle;

	string _key;

	tagPosF _pos;
	tagPosF _probe;

	tagPosF _target[4];

	vector<vector<tagPosF>> shop_target; // 타겟 좌표 배열

	int _targetIdx;

	int shop_targetIdx; // 좌판 번호 타겟 인덱스
	int shop_currentTargetIdx; // 현재 좌표 위치정보 인덱스

	RECT _rc;
	RECT _talkRect;
	bool _stop;
	bool _Istalk;
	bool _delay;

	bool _isActive;
	bool _isSpawn;

	int _boxidx;
	int _boxCnt;

	string _talk;
	string _name;

	HFONT hFont;
	HFONT oldFont;

	RECT _nameRect;
	RECT _textRect;

	displayStand* _displayStand; // 상점 좌판 정보

	string _illustrator = "일러";

	NPC_ACTION _state; // npc 상태

	bool _isBarking; // 강아지가 짖고 있는가

	void setshopTargetPos(); // 상점에서 타겟 좌표 설정

public:
	HRESULT init(tagPosF pos, string key); // 마을 npc 초기화
	HRESULT init(tagPosF pos, string key, NPC_MAP NPC_SHOP, int idx, displayStand* dis);  //상점 npc 초기화

	void release();
	void update(); // 마을 NPC 업데이트
	void update(NPC_MAP NPC_SHOP); // 상점NPC 업데이트

	void render(); // 기본 npc 렌더링
	void render(NPC_MAP NPC_SHOP); // 상점 npc 렌더링

	void anim(); // npc 애니메이션
	void boxAnim(); // 대화박스 애니메이션
	void move(); // 마을 npc 움직임
	void move(NPC_MAP NPC_SHOP); // 상점에서의 npc 움직임
	void action(string talk); //NPC 멘트 및 말풍선 업데이트
	void action(); //강아지 전용
	void collision(); // NPC 충돌렉트 설정
	void lookPlayer(); // 플레이어를 바라보도록 조정 강아지전용
	void npcSpawn(); // npc 스폰

	tagPosF& getPos() { return _pos; } // npc x , y 좌표 가져오기
	RECT& getRect() { return _rc; } // npc 렉트 가져오기
	string getKey() { return _key; } // npc 이미지 KEY값 가져오기

	void setPosX(float x) { _pos.x = x; } // x 좌표 세팅
	void setPosY(float y) { _pos.x = y; } // y 좌표 세팅

	bool& getActive() { return _isActive; } // npc가 살아있는가
	void setActive(bool ac) { _isActive = ac; } // npc 생존여부 세팅

	int& getCurrentTargetIdx() { return shop_currentTargetIdx; } // 현재 가야할 좌표 인덱스
	void setCurrentTargetIdxPlus() { shop_currentTargetIdx++; }
	void priceCheck(); // 상점 아이템 가격에 따른 세팅
	void PriceCheckAnim(); // 이모티콘 애니메이션
	void ItemGet(); // 아이템 정보 가져오기

	NPC_ACTION& getState() { return _state; } // npc 현재 스테이트 반환
	void setState(NPC_ACTION st) { _state = st; } // npc 상태 업데이트
	npc() {}
	~npc() {}
};

