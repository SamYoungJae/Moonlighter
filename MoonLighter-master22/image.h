#pragma once
//=============================================================
//	## image ## (������ ��� ������Ʈ �ȴ�)
//=============================================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_EMPTY,		//���Ʈ�� �ε�
		LOAD_FILE		//���Ϸ� �ε�
	};

	typedef struct tagImage
	{
		HDC hMemDC;			//�޸� DC
		HBITMAP hBit;		//��Ʈ��
		HBITMAP hOBit;		//�õ��Ʈ��
		float x;				//�̹��� x��ǥ
		float y;				//�̹��� y��ǥ
		int width;			//�̹��� ���α���
		int height;			//�̹��� ���α���
		int currentFrameX;	//���� ������X
		int currentFrameY;	//���� ������Y
		int maxFrameX;		//�ִ� ������X ����
		int maxFrameY;		//�ִ� ������Y ����
		int frameWidth;		//1������ ���α���
		int frameHeight;	//1������ ���α���
		BYTE loadType;		//�̹��� �ε�Ÿ��
		tagImage()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_EMPTY;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	char*			_fileName;		//�̹��� �����̸�
	bool			_isTrans;		//���� ���ٰų�?
	COLORREF		_transColor;	//���� ���� RGB (����Ÿ = RGB(255, 0, 255))

	LPIMAGE_INFO	_blendImage;	//���ĺ��� �̹���
	BLENDFUNCTION	_blendFunc;		//���ĺ��� ���

	LPIMAGE_INFO	_stretchImage;  //��Ʈ��ġ �̹���
	LPIMAGE_INFO	_minimapImage;	//�̴ϸ� �̹���
	LPIMAGE_INFO	_rotateImage;	//ȸ ���̹���

public:
	image();
	~image();

	//�� ��Ʈ�� �ʱ�ȭ
	HRESULT init(int width, int height);
	//�̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));

	//���ĺ��� �ʱ�ȭ
	HRESULT initForAlphaBlend();
	HRESULT initForStretch();
	HRESULT initForMinimap(int sizeX, int sizeY);
	HRESULT initForRotate();


	//����
	void release();

	//����(���� ���ϴ� ��ǥ�� ����ض�, �Ϲ������� �츮�� RECT�� LT��ǥ�� �̹����� ���δ�)
	void render(HDC hdc, int destX = 0, int destY = 0);
	//����(���ϴ� ��ǥ�� �̹����� �߶� ���̱�)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	//���ķ���(�̹����� ���İ���ŭ ����ȭ �����ش�)
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	//��Ʈ��ġ ����
	void stretchRender(HDC hdc, int centerX, int centerY, float size);
	void stretchRender(HDC hdc, int centerX, int centerY, int scaleX , int scaleY );
	void stretchFrameRender(HDC hdc, int centerX, int centerY, int currentFrameX, int currentFrameY, float size);
	void stretchFrameRender(HDC hdc, int centerX, int centerY, int currentFrameX, int currentFrameY, int scaleX , int scaleY );
	//�����ӷ���
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//void minimapRender(HDC hdc, int destX, int destY, int sizeX, int sizeY,bool isAlpha, BYTE alpha = 255);

	//��������
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//ȸ������ �⺻������ ������������
	void rotateRender(HDC hdc, float centerX, float centerY, float angle);
	void rotateFrameRender(HDC hdc, float centerX, float centerY, float angle, int frameX = 0, int frameY = 0);
	void rotateAlphaRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha);
	void rotateAlphaFrameRender(HDC hdc, float centerX, float centerY, float angle, int frameX = 0, int frameY = 0, BYTE alpha = 255);

	//DC ���
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//�̹��� x, y��ǥ
	inline float getX() { return _imageInfo->x; }
	inline float getY() { return _imageInfo->y; }
	inline void setX(float x) { _imageInfo->x = x; }
	inline void setY(float y) { _imageInfo->y = y; }
	//�̹��� ������ǥ
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x + (_imageInfo->width / 2);
		_imageInfo->y = y + (_imageInfo->height / 2);
	}
	//�̹��� ����, ���α��� ��������
	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }
	//�ٿ�� �ڽ�(�浹�� ��Ʈ)
	inline RECT boundingBox()
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
		(int)_imageInfo->x + _imageInfo->width,
		(int)_imageInfo->y + _imageInfo->height };
		return rc;
	}
	inline RECT boudingBoxWithFrame()
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
		(int)_imageInfo->x + _imageInfo->frameWidth,
		(int)_imageInfo->y + _imageInfo->frameHeight };
		return rc;
	}
	//������ X, Y
	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}
	//1������ ����, ���α��� ��������
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }
	//�ƽ� ������ ��������
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	//�̹��� Ʈ���� ����
	inline void setIsTrans(bool trans) { _isTrans = trans; }
	inline void setTransColor(COLORREF color) { _transColor = color; }

};

