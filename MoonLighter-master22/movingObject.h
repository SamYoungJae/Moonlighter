#pragma once

typedef struct
{
	image *img;				//������Ʈ �̹��� 
	POINT pos;				//������Ʈ ��ġ 
	float movingSpeed;		//������Ʈ �̵��ӵ� 
	bool isArrived;			//��ǥ�������� ���޻���(true/false)

}objectUnit;

class movingObject
{
private:
	objectUnit _movingObj;

public:
	HRESULT init();
	HRESULT init(image *img, int posX, int posY, float speed);
	void release();
	void update();
	void render(HDC hdc);

	//get�Լ� 
	objectUnit getObject() { return _movingObj; }
	image *getImg() { return _movingObj.img; }
	POINT getPos() { return _movingObj.pos; }
	float getSpeed() { return _movingObj.movingSpeed; }
	bool getIsArrived() { return _movingObj.isArrived; }

	//set�Լ� 
	void setImg(image* img) { _movingObj.img = img; }
	void setPos(POINT pos) { _movingObj.pos = pos; }
	void setPosX(int posX) { _movingObj.pos.x = posX; }
	void setPosY(int posY) { _movingObj.pos.y = posY; }
	void setSpeed(float speed) { _movingObj.movingSpeed = speed; }
	void setIsArrived(bool value) { _movingObj.isArrived = value; }

	void initPos(int posX, int posY);		//�Ű����� ���� �޾� ��ġ�� �ʱ�ȭ�ϴ� �Լ� 
	void moveLeft(const int destPos);		//�������� ���� �̵�
	void moveRight(const int destPos);		//�������� ������ �̵�
	void moveUp(const int destPos);			//�������� ���� �̵�
	void moveDown(const int destPos);		//�������� �Ʒ��� �̵� 
};

