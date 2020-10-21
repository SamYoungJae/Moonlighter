#pragma once
#include "fadeManager.h"
#include "movingObject.h"
#include "selectMenu.h"
#include "animation.h"
#include "cursor.h"
#include "recipe.h"
#include "gameNode.h"
#define POTION_MENUPOSX			76
#define POTION_MENUPOSY			18
#define POTION_BANNERPOSX		400
#define POTION_BANNERPOSY		0
#define POTION_EKEYPOSX			1212
#define POTION_EKEYPOSY			320
#define POTION_CURSORX			476
#define POTION_CURSORY			182
#define POTION_CURSOR_DISTANCE	74
#define POTION_MAXSLOT			4
#define POTION_MAXPRODUCE		99

//���� ����Ÿ��(����,��������)
enum POTION_TYPE
{
	POTION_BUY,
	POTION_CRAFT
};

//���Ǹ޴� ��Ʈ�ѷ� 
enum POTION_CTRL
{
	POTION_MENU,
	POTION_MESSAGE,
	POTION_SET_COUNT,
	POTION_SELECTMENU
};

//���Ǹ޴� ���� ����ü 
typedef struct
{
	gameItem item;						//���� �� ������
	POTION_TYPE type;					//���� ����(����ǰ ����/���� ����)
	int price;							//���� ���
	const char* description[2];			//������ ����
	recipe *mixRecipe;					//���� ������
	int slotIdx;						//������ �ε���

}potionSlot;

class potionShop : public gameNode
{
private:
	fadeManager *_fadeManager;
	animation *_animation;
	movingObject *_potionMenu;
	movingObject *_shopBanner;
	movingObject *_eKeyIcon;
	selectMenu *_selectMenu;
	cursor *_cursor;

	potionSlot _potionSlot[POTION_MAXSLOT];
	POTION_CTRL _potionCtrl;
	MESSAGE_TYPE _messageType;

private:
	bool _menuOn;			//�޴� on/off ���� Ȯ�ο� ���� 
	bool _openMenu;			//�޴� ���� ���� ���࿩�� 
	bool _closeMenu;		//�޴� �ݱ� ���� ���࿩�� 
	bool _showBannerTxt;	//������� �ؽ�Ʈ ��¿��� 
	bool _animPlayed;		//�ִϸ��̼� �÷��� 1ȸ ��Ű�� 
	bool _playAnim;			//�ִϸ��̼��� ���� �÷��� ������ Ȯ�� 

	int _produceCount;			//���� �� ������ ���� 
	int _maxProduceCount;		//�κ��丮�� �� ������ ���� �ؼ� ���� ������ �ִ� ������ ���� 
	float _potionPosY;			//���� �� ��������� ���� ��ġ 
	int _frameCount;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//get�Լ� 
	bool getMenuOn() { return _menuOn; }

	//set�Լ� 

	//���ǻ��� ����ݱ� �Լ� 
	void toggleMenu();					//�׽�Ʈ�� �޴� on/off Ű �Է��� �޴� �Լ� 
	void initMenuPos();					//�� �޴��� ��ġ�� �ʱ�ȭ�ϴ� �Լ�
	void openPotionMenu();				//���ǻ��� �޴� ���� �Լ� 
	void closePotionMenu();				//���ǻ��� �޴� �ݱ� �Լ� 
	void openMenu();					//�޴� ���� ���� �Լ� 
	void closeMenu();					//�޴� �ݱ� ���� �Լ� 

	//���Ǹ޴� ���� �Լ� 
	void initPotionSlot();					//���Ǹ޴� ���� �ʱ�ȭ �Լ�(���� 1ȸ ����)
	void initCursor();						//Ŀ�� �ε��� �� ��ġ �ʱ�ȭ(���� ���¸��� ����)
	void initPotionShop();					//���ǻ��� ������ �ʱ�ȭ 
	void setPotionCtrl(POTION_CTRL state);	//���ǻ��� ��Ʈ�ѷ� ���� 
	bool checkRequirements();				//���� ������ �ʿ��� ����� �����Ǵ��� ���� Ȯ��
	void checkMaxProduceCount();			//���� ������ �ִ� ������ ���� Ȯ�� 
	void playCraftingAnim();				//���� ���� �ִϸ��̼� ���� 
	void applyCraftingResult();

	//Ű�Է� �Լ� 
	void keyInput();					//��ü Ű�Է� �Լ� 
	void menuKeyInput();				//�޴� ��Ʈ�ѷ� Ű�Է� �Լ� 
	void messageKeyInput();				//�޽��� ��Ʈ�ѷ� Ű�Է� �Լ� 
	void setCountKeyInput();			//ī��Ʈ ���� ��Ʈ�ѷ� Ű�Է� �Լ� 
	void selectMenuKeyInput();			//��,�ƴϿ� ���ø޴� ��Ʈ�ѷ� Ű�Է� �Լ� 
	void leftKeyDown();					//���� Ű(A) �Է� �Լ� 
	void rightKeyDown();				//������ Ű(D) �Է� �Լ� 
	void upKeyDown();					//���� Ű(W) �Է� �Լ� 
	void downKeyDown();					//�Ʒ��� Ű(S) �Է� �Լ� 

	//���� �Լ�(�޴� �� ��������) 
	void bannerTextRender();			//�����̸� '���� ����' ��� 
	void potionMenuRender();			//�������� �޴� ���� ���
	void potionMenuTextRender();		//���Ǹ޴� �ؽ�Ʈ ���(���� ���, ������) 
	void potionInfoRender();			//���� Ŀ���� ����Ű�� ���� ���� ��ü ��� 
	void potionIconRender();			//Ŀ���� ����Ű�� ���� ������ ��� 
	void potionNameRender();			//Ŀ���� ����Ű�� ���� �̸� ��� 
	void potionDesRender();				//Ŀ���� ����Ű�� ���� ���� ��� 
	void potionPriceRender();			//Ŀ���� ����Ű�� ������ ������� ��� 
	void possessCountRender();			//Ŀ���� ����Ű�� ������ �������� ��� 
	void recipeInfoRender();			//Ŀ���� ����Ű�� ������ ���� ��� 

	//���� �Լ�(�޽���)
	void printMessage();				//�ʿ��� ���� �޽��� ���� 
	void printLackOfGold();				//��� ���� �޽��� ���� 
	void printLackOfMaterial();			//��� ���� �޽��� ���� 
	void printLackOfBoth();				//���� ��� ���� �޽��� ���� 
	void printLackOfRoom();				//���� ���� �޽��� ���� 

	//���� �Լ�(���� ���� ����)
	void setCountRender();				//���۰��� ���� ���� ��ü �Լ�  
	void setCountTextRender();			//���۰��� ���� �ؽ�Ʈ ���� 
	void setCountIconRender();			//���۰��� ȭ��ǥ(Ŀ��) ��� 
	void produceCountRender();			//���۰���(���� �̹���) ���� 
	void totalPriceRender();			//���۰���*���۱ݾ� = �� ���۱ݾ� ���� 
	void countRender(int count, int destX, int destY, COLOR_TYPE color);//���� ���� �̹��� ��� �Լ� 

	//���� �Լ�(��/�ƴϿ� ���ø޴�)
	void selectMenuRender();			//��,�ƴϿ� ���ø޴� ���� ��ü �Լ� 
	void selectMenuTextRender();		//���ø޴� �ؽ�Ʈ ���� 
	void selectMenuAnimRender();		//���ø޴� ������ �ִϸ��̼� ���� 

	//���� �Լ�(���� ����)
	void potionCraftRender();			//���� ���� ���� ��ü �Լ� 

};

