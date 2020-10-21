#include "stdafx.h"
#include "image.h"
image::image() : _imageInfo(NULL), _fileName(NULL), _blendImage(NULL), _stretchImage(NULL), _minimapImage(NULL), _rotateImage(NULL)
{
}
image::~image()
{
}

//�� ��Ʈ�� �ʱ�ȭ
HRESULT image::init(int width, int height)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	_fileName = NULL;
	//����Ű �÷� ����
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//�̹��� ������ ��µ� �������� ��
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//�̹��� ���Ϸ� �ʱ�ȭ
HRESULT image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//�̹��� ������ ��µ� �������� ��
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//�̹��� ������ ��µ� �������� ��
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//�̹��� ������ ��µ� �������� ��
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//�̹��� ������ ��µ� �������� ��
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
//���ĺ��� �ʱ�ȭ
HRESULT image::initForAlphaBlend()
{
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//���ĺ��� �ɼ� �ʱ�ȭ
	//BlendOp => ����� AC_SRC_OVER�� ��밡��
	//BlendFlags => �׳� 0����, ���� �� ��, ���� OS���� ����ߴٰ� ��
	//AlphaFormat => 24bit���� 0, 32bit���� AC_SRC_ALPHA ����ϸ� ������ �����̰� ��� �츰 �׳� 0 
	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	//0 ~ 255 => 255�϶� ��������
	//_blendFunc.SourceConstantAlpha = 255;

	int size;
	(_imageInfo->width > _imageInfo->height ? size = _imageInfo->width : size = _imageInfo->height);

	//���ĺ��� �̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = size;
	_blendImage->height = size;

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForStretch()
{
	HDC hdc = GetDC(_hWnd);

	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = LOAD_EMPTY;
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);
	_stretchImage->width = WINSIZEX;
	_stretchImage->height = WINSIZEY;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForStretch(int x, int y)
{
	HDC hdc = GetDC(_hWnd);

	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = LOAD_EMPTY;
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc,x,y);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);
	_stretchImage->width = x;
	_stretchImage->height = y;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForMinimap(int sizeX, int sizeY)
{
	HDC hdc = GetDC(_hWnd);

	_minimapImage = new IMAGE_INFO;
	_minimapImage->loadType = LOAD_EMPTY;
	_minimapImage->hMemDC = CreateCompatibleDC(hdc);
	_minimapImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, sizeX, sizeY);
	_minimapImage->hOBit = (HBITMAP)SelectObject(_minimapImage->hMemDC, _minimapImage->hBit);
	_minimapImage->width = WINSIZEX;
	_minimapImage->height = WINSIZEY;

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT image::initForRotate()
{
	HDC hdc = GetDC(_hWnd);
	int size;
	(_imageInfo->width > _imageInfo->height ? size = _imageInfo->width : size = _imageInfo->height);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

//����
void image::release()
{
	//�̹��� ������ ���� �ִٸ� ���� ���Ѷ�
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//���� �÷�Ű �ʱ�ȭ
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}

	//���ĺ��� �̹��� ������ ���� �ִٸ� ���� ���Ѷ�
	if (_blendImage)
	{
		//�̹��� ����
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//������ ����
		SAFE_DELETE(_blendImage);
	}
}

//����(���� ���ϴ� ��ǥ�� ����ض�, �Ϲ������� �츮�� RECT�� LT��ǥ�� �̹����� ���δ�)
void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)//���� ���ְ� ���
	{
		//GdiTransparentBlt : ��Ʈ�� �̹����� Ư�������� �����ϰ� ���� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,				//������ ����� DC
			destX,				//������ ��ǥ ����X
			destY,				//������ ��ǥ ����Y
			_imageInfo->width,	//������ �̹��� ����ũ��
			_imageInfo->height,	//������ �̹��� ����ũ��
			_imageInfo->hMemDC,	//����� ��� DC
			0, 0,				//����� ����� ��������
			_imageInfo->width,	//���� ���� ����ũ��
			_imageInfo->height,	//���� ���� ����ũ��
			_transColor);		//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)
	}
	else//���� �̹��� �״�� ���
	{
		//BitBlt : DC���� �������� ��Ӻ��� ���ִ� �Լ�
		//�޸�DC => ȭ��DC�� �����Ѵ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//����(���ϴ� ��ǥ�� �̹����� �߶� ���̱�)
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)//���� ���ְ� ���
	{
		//GdiTransparentBlt : ��Ʈ�� �̹����� Ư�������� �����ϰ� ���� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,				//������ ����� DC
			destX,				//������ ��ǥ ����X
			destY,				//������ ��ǥ ����Y
			sourWidth,			//������ �̹��� ����ũ��
			sourHeight,			//������ �̹��� ����ũ��
			_imageInfo->hMemDC,	//����� ��� DC
			sourX, sourY,		//����� ����� ��������
			sourWidth,			//���� ���� ����ũ��
			sourHeight,			//���� ���� ����ũ��
			_transColor);		//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)
	}
	else//���� �̹��� �״�� ���
	{
		//BitBlt : DC���� �������� ��Ӻ��� ���ִ� �Լ�
		//�޸�DC => ȭ��DC�� �����Ѵ�
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//���ĺ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) this->initForAlphaBlend();
	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//���� ���ְ� ���
	{
		//1. ����ȭ��DC�� ������ => �����̹����� ����
		//2. �̹����޸�DC�� ������ ���� �� => �����̹����� ����
		//3. �����̹����� ȭ��DC�� ����

		//1
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		//2
		//GdiTransparentBlt : ��Ʈ�� �̹����� Ư�������� �����ϰ� ���� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC
			0,						//������ ��ǥ ����X
			0,						//������ ��ǥ ����Y
			_imageInfo->width,		//������ �̹��� ����ũ��
			_imageInfo->height,		//������ �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//����� ����� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)

		//3
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else//���� �̹��� �״�� ���
	{
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{

	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//���� ���ְ� ���
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC
			0,						//������ ��ǥ ����X
			0,						//������ ��ǥ ����Y
			_imageInfo->width,		//������ �̹��� ����ũ��
			_imageInfo->height,		//������ �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//����� ����� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)

		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else//���� �̹��� �״�� ���
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	if (!_blendImage) this->initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt(
			_blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _imageInfo->hMemDC,
			_imageInfo->frameWidth * currentFrameX, _imageInfo->frameHeight * currentFrameY, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _transColor);

		GdiAlphaBlend(
			hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);

	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _imageInfo->hMemDC, _imageInfo->frameWidth * currentFrameX, _imageInfo->frameHeight * currentFrameY, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//���� ���ְ� ���
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC
			0,						//������ ��ǥ ����X
			0,						//������ ��ǥ ����Y
			sourWidth,				//������ �̹��� ����ũ��
			sourHeight,				//������ �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			sourX, sourY,			//����� ����� ��������
			sourWidth,				//���� ���� ����ũ��
			sourHeight,				//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)

		GdiAlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else//���� �̹��� �״�� ���
	{
		GdiAlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}

void image::stretchRender(HDC hdc, int centerX, int centerY, float size)
{
	//��Ʈ��ġ�̹��� ó�� ����ϳ�?
		//�̹��� �����ϸ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_stretchImage) this->initForStretch();

	_stretchImage->width = _imageInfo->width * size;
	_stretchImage->height = _imageInfo->height * size;

	if (_isTrans) //���� ���ٲ���?
	{
		//�����̹����� Scale�� ��ŭ Ȯ��/��ҽ��Ѽ� �׷��ش�
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);

		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			centerX - _stretchImage->width / 2,					//����� ��ǥ ������ X
			centerY - _stretchImage->height /2,					//����� ��ǥ ������ Y
			_stretchImage->width,	//����� �̹��� ����ũ��
			_stretchImage->height,	//����� �̹��� ����ũ��
			_stretchImage->hMemDC,	//����� ��� DC
			0, 0,					//���� ��������
			_stretchImage->width,	//���� ���� ����ũ��
			_stretchImage->height,	//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)

	}
	else //���� �̹��� �׷��� ����Ҳ���?
	{
		//���� �̹����� ũ�⸦ Ȯ��/��� �ؼ� ���� ��Ų��
		StretchBlt(hdc, centerX - _stretchImage->width / 2, centerY - _stretchImage->height / 2, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::stretchRender(HDC hdc, int centerX, int centerY, int scaleX, int scaleY)
{
	//��Ʈ��ġ�̹��� ó�� ����ϳ�?
		//�̹��� �����ϸ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_stretchImage) this->initForStretch();

	_stretchImage->width = scaleX;
	_stretchImage->height = scaleY;

	if (_isTrans) //���� ���ٲ���?
	{
		//�����̹����� Scale�� ��ŭ Ȯ��/��ҽ��Ѽ� �׷��ش�
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);

		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			centerX - _stretchImage->width / 2,					//����� ��ǥ ������ X
			centerY - _stretchImage->height / 2,					//����� ��ǥ ������ Y
			_stretchImage->width,	//����� �̹��� ����ũ��
			_stretchImage->height,	//����� �̹��� ����ũ��
			_stretchImage->hMemDC,	//����� ��� DC
			0, 0,					//���� ��������
			_stretchImage->width,	//���� ���� ����ũ��
			_stretchImage->height,	//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)

	}
	else //���� �̹��� �׷��� ����Ҳ���?
	{
		//���� �̹����� ũ�⸦ Ȯ��/��� �ؼ� ���� ��Ų��
		StretchBlt(hdc, centerX - _stretchImage->width / 2, centerY - _stretchImage->height / 2, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::stretchFrameRender(HDC hdc, int centerX, int centerY, int currentFrameX, int currentFrameY, float size)
{
	//��Ʈ��ġ�̹��� ó�� ����ϳ�?
	//�̹��� �����ϸ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_stretchImage) this->initForStretch(_imageInfo->width * size, _imageInfo->height * size);

	_stretchImage->width = _imageInfo->width * size;
	_stretchImage->height = _imageInfo->height * size;
	_stretchImage->frameWidth = _stretchImage->width / (_imageInfo->maxFrameX + 1);
	_stretchImage->frameHeight = _stretchImage->height / (_imageInfo->maxFrameY + 1);

	if (_isTrans) //���� ���ٲ���?
	{
		//�����̹����� Scale�� ��ŭ Ȯ��/��ҽ��Ѽ� �׷��ش�
		SetStretchBltMode(getMemDC(), COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->frameWidth, _stretchImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);

		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,							//������ ����� DC
			centerX - _stretchImage->frameWidth /2,							//����� ��ǥ ������ X
			centerY - _stretchImage->frameHeight / 2,							//����� ��ǥ ������ Y
			_stretchImage->frameWidth,		//����� �̹��� ����ũ��
			_stretchImage->frameHeight,		//����� �̹��� ����ũ��
			_stretchImage->hMemDC,			//����� ��� DC
			0, 0,							//���� ��������
			_stretchImage->frameWidth,		//���� ���� ����ũ��
			_stretchImage->frameHeight,		//���� ���� ����ũ��
			_transColor);					//�����Ҷ� ������ ���� (����Ÿ)
	}
	else //���� �̹��� �׷��� ����Ҳ���?
	{
		//�����̹����� Scale�� ��ŭ Ȯ��/��ҽ��Ѽ� �׷��ش�
		StretchBlt(hdc, centerX - _stretchImage->frameWidth / 2, centerY - _stretchImage->frameHeight / 2, _stretchImage->frameWidth, _stretchImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);
	}
}

void image::stretchFrameRender(HDC hdc, int centerX, int centerY, int currentFrameX, int currentFrameY, int scaleX, int scaleY)
{
	//��Ʈ��ġ�̹��� ó�� ����ϳ�?
	//�̹��� �����ϸ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_stretchImage) this->initForStretch();

	_stretchImage->frameWidth = scaleX;
	_stretchImage->frameHeight = scaleY;
	_stretchImage->width = scaleX * _imageInfo->maxFrameX;
	_stretchImage->height = scaleY * _imageInfo->maxFrameY;

	if (_isTrans) //���� ���ٲ���?
	{
		//�����̹����� Scale�� ��ŭ Ȯ��/��ҽ��Ѽ� �׷��ش�
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->frameWidth, _stretchImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);

		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,							//������ ����� DC
			centerX - _stretchImage->frameWidth / 2,							//����� ��ǥ ������ X
			centerY - _stretchImage->frameHeight / 2,							//����� ��ǥ ������ Y
			_stretchImage->frameWidth,		//����� �̹��� ����ũ��
			_stretchImage->frameHeight,		//����� �̹��� ����ũ��
			_stretchImage->hMemDC,			//����� ��� DC
			0, 0,							//���� ��������
			_stretchImage->frameWidth,		//���� ���� ����ũ��
			_stretchImage->frameHeight,		//���� ���� ����ũ��
			_transColor);					//�����Ҷ� ������ ���� (����Ÿ)
	}
	else //���� �̹��� �׷��� ����Ҳ���?
	{
		//�����̹����� Scale�� ��ŭ Ȯ��/��ҽ��Ѽ� �׷��ش�
		StretchBlt(hdc, centerX - _stretchImage->frameWidth / 2, centerY - _stretchImage->frameHeight / 2, _stretchImage->frameWidth, _stretchImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)//���� ���ְ� ���
	{
		GdiTransparentBlt(
			hdc,						//������ ����� DC
			destX,						//������ ��ǥ ����X
			destY,						//������ ��ǥ ����Y
			_imageInfo->frameWidth,		//������ �̹��� ����ũ��
			_imageInfo->frameHeight,	//������ �̹��� ����ũ��
			_imageInfo->hMemDC,			//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//����� ����� ��������
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//����� ����� ��������			
			_imageInfo->frameWidth,		//���� ���� ����ũ��
			_imageInfo->frameHeight,	//���� ���� ����ũ��
			_transColor);				//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)
	}
	else//���� �̹��� �״�� ���
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹��� ����ó��
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameX;
	}

	if (_isTrans)//���� ���ְ� ���
	{
		GdiTransparentBlt(
			hdc,						//������ ����� DC
			destX,						//������ ��ǥ ����X
			destY,						//������ ��ǥ ����Y
			_imageInfo->frameWidth,		//������ �̹��� ����ũ��
			_imageInfo->frameHeight,	//������ �̹��� ����ũ��
			_imageInfo->hMemDC,			//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//����� ����� ��������
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//����� ����� ��������			
			_imageInfo->frameWidth,		//���� ���� ����ũ��
			_imageInfo->frameHeight,	//���� ���� ����ũ��
			_transColor);				//�����Ҷ� ������ ���� (�Ϲ������� ����Ÿ ������ �����)
	}
	else//���� �̹��� �״�� ���
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

//��������
void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//������(offset)�� �Ϲ������� ���� ������Ʈ �ȿ��� ������Ʈ ó������ �־��� ��ҳ� Ư�� ���������� ������
		//offset�� � Ư���� ������ �ణ ���̰� ���� �� �Ǵ� �� ���� ��ü�� �ǹ�(���̿� ���� ������)

		//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ���� (ȭ��ũ��)
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ��������
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����(�Ϲݷ���-�̹����߶󼭺��̱�)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ���� (ȭ��ũ��)
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ��������
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����(���ķ���-�̹����߶󼭺��̱�)
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight, alpha);
		}
	}
}

void image::rotateRender(HDC hdc, float centerX, float centerY, float angle)
{
	if (!_rotateImage) this->initForRotate();
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void image::rotateFrameRender(HDC hdc, float centerX, float centerY, float angle, int frameX, int frameY)
{
	if (!_rotateImage) this->initForRotate();
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->frameWidth * frameX, _imageInfo->frameHeight * frameY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);

		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, _imageInfo->frameWidth * frameX, _imageInfo->frameHeight * frameY, _imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

void image::rotateAlphaRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha)
{
	if (!_blendImage) this->initForAlphaBlend();
	if (!_rotateImage) this->initForRotate();

	_blendFunc.SourceConstantAlpha = alpha;

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAnlge[3];
	baseAnlge[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAnlge[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAnlge[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAnlge[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 - sinf(baseAnlge[i] + angle) * dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, SRCCOPY);

		HBRUSH brush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, brush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(brush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(_blendImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
		GdiAlphaBlend(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_blendImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_blendFunc);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}

}

void image::rotateAlphaFrameRender(HDC hdc, float centerX, float centerY, float angle, int frameX, int frameY, BYTE alpha)
{
	if (!_rotateImage) this->initForRotate();
	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, SRCCOPY);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->frameWidth * frameX, _imageInfo->frameHeight * frameY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);

		GdiTransparentBlt(_blendImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
		GdiAlphaBlend(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_blendImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_blendFunc);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, _imageInfo->frameWidth * frameX, _imageInfo->frameHeight * frameY, _imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

void image::rotateStretchFrameRender(HDC hdc, float centerX, float centerY, int frameX, int frameY, float angle, float scale)
{
	if (!_rotateImage) this->initForRotate();

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (!_stretchImage) this->initForStretch(_rotateImage->width * scale, _rotateImage->height * scale);

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		SetStretchBltMode(hdc, COLORONCOLOR);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->frameWidth * frameX, _imageInfo->frameHeight * frameY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);

		StretchBlt(_stretchImage->hMemDC,
			0, 0, _stretchImage->width, _stretchImage->height, _rotateImage->hMemDC,
			0, 0, _rotateImage->width, _rotateImage->height, SRCCOPY);

		GdiTransparentBlt(hdc,
			centerX - _stretchImage->width / 2,
			centerY - _stretchImage->height / 2,
			_stretchImage->width,
			_stretchImage->height,
			_stretchImage->hMemDC,
			0, 0,
			_stretchImage->width,
			_stretchImage->height,
			_transColor);
	
	
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, _imageInfo->frameWidth * frameX, _imageInfo->frameHeight * frameY, _imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
	delete _stretchImage;
	_stretchImage = nullptr;
}
