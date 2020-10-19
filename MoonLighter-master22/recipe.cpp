#include "stdafx.h"
#include "recipe.h"

//=============================================================
//	## material ## (���� ���)
//=============================================================

HRESULT material::init(int itemIdx, int count)
{
	_material.itemIdx = itemIdx;
	_material.item = *(ITEMMENU->getItemManager()->getItem()[itemIdx]);
	_material.count = count;
	_material.possession = ITEMMENU->getInventory()->getCountByIdx(itemIdx);

	return S_OK;
}

void material::release()
{
}

void material::update()
{
}

void material::render(HDC hdc)
{
}

int material::updatePossession()
{
	_material.possession = ITEMMENU->getInventory()->getCountByIdx(_material.itemIdx);

	return _material.possession;
}

//=============================================================
//	## recipe ## (������ ����)
//=============================================================

HRESULT recipe::init()
{
	return S_OK;
}

void recipe::release()
{
}

void recipe::update()
{
}

void recipe::render(HDC hdc, int destX, int destY)
{
	if (_vMaterial.size() <= 0) return;

	recipeIconRender(hdc, destX, destY);
	recipeTextRender(hdc, destX, destY);
	recipeOXIconRender(hdc, destX, destY);
	recipeCountRender(hdc, destX, destY);
}

void recipe::addMaterial(int itemIdx, int count)
{
	material *item = new material;
	item->init(itemIdx, count);
	_vMaterial.push_back(item);
}

bool recipe::checkMaterialOX(int index)
{
	int itemIdx = _vMaterial[index]->getItem().getItemIdx();

	//���� �κ��丮�� �ִ� ����� ������ �ʿ��� ��ᰳ������ ���ٸ� false ��ȯ 
	if (ITEMMENU->getInventory()->getCountByIdx(itemIdx) < _vMaterial[index]->getCount())
	{
		return false; 
	}
	else
	{
		//���� �κ��丮�� �ִ� ����� ������ �ʿ��� ��ᰳ���� ���ų� ũ�ٸ� true ��ȯ  
		return true; 
	}
}

bool recipe::checkRequirements()
{
	//��ü ��Ḧ Ȯ���ϸ鼭 ������ ��ᰡ ���� ��� false ���� 
	for (int i = 0; i < _vMaterial.size(); i++)
	{
		int itemIdx = _vMaterial[i]->getItem().getItemIdx();

		if (ITEMMENU->getInventory()->getCountByIdx(itemIdx) < _vMaterial[i]->getCount())
		{
			return false; 
		}
	}

	//������ ��ᰡ ���� ��� true ���� 
	return true; 
}

const char * recipe::getShortMaterialName()
{
	memset(_materialName, 0, sizeof(_materialName));
	int count = 0;

	for (int i = 0; i < _vMaterial.size(); i++)
	{
		//������ ��ᰡ ���� �� 
		if (!checkMaterialOX(_vMaterial[i]->getItem().getItemIdx()))
		{
			if (count == 0)
			{
				strcpy(_materialName, _vMaterial[i]->getItem().getName());
			}
			else
			{
				strcat(_materialName, ", ");
				strcat(_materialName, _vMaterial[i]->getItem().getName());
			}

			count++;
		}
	}

	return _materialName;
}

void recipe::recipeIconRender(HDC hdc, int destX, int destY)
{
	for (int i = 0; i < _vMaterial.size(); i++)
	{
		IMAGEMANAGER->render("slot_base", hdc, destX, destY + (i * 74));
		_vMaterial[i]->getItem().getItemImg()->render(hdc, (destX + 6), (destY + 6) + (i * 74));
	}
}

void recipe::recipeTextRender(HDC hdc, int destX, int destY)
{
	int tempX = destX + 74;
	int tempY = destY + 6;

	for (int i = 0; i < _vMaterial.size(); i++)
	{
		RECT txtRC1 = RectMake(tempX, tempY + (i * 74), 44, 24);
		HFONT font = CreateFont(19, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("JejuGothic"));
		HFONT oFont = (HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(50, 50, 50));
		DrawText(hdc, "�ʿ�:", -1, &txtRC1, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
		SelectObject(hdc, oFont);
		DeleteObject(font);

		RECT txtRC2 = RectMake(tempX, (tempY + 30) + (i * 74), 44, 24);
		SetTextColor(hdc, RGB(50, 50, 50));
		DrawText(hdc, "����:", -1, &txtRC2, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
		SelectObject(hdc, oFont);
		DeleteObject(font);
	}
}

void recipe::recipeOXIconRender(HDC hdc, int destX, int destY)
{
	int tempX = destX + 232;
	int tempY = destY;

	for (int i = 0; i < _vMaterial.size(); i++)
	{
		IMAGEMANAGER->frameRender("shop_ox", hdc,
			tempX, tempY + (i * 74), checkMaterialOX(i), 0);
	}
}

void recipe::recipeCountRender(HDC hdc, int destX, int destY)
{
	int tempX = destX + 186;
	int tempY = destY + 8;

	for (int i = 0; i < _vMaterial.size(); i++)
	{
		int countNeeded = _vMaterial[i]->getCount();
		int countHaving = ITEMMENU->getInventory()->getCountByIdx(_vMaterial[i]->getItem().getItemIdx());

		countRender(hdc, tempX, tempY + (i * 74), countNeeded);
		countRender(hdc, tempX, (tempY + 30) + (i * 74), countHaving);
	}
}

void recipe::countRender(HDC hdc, int destX, int destY, int count)
{
	int multiplyCount = 0;
	int tempCount = count;

	while (true)
	{
		if (tempCount / 10 != 0)
		{
			tempCount /= 10;
			multiplyCount++;
		}
		else break;
	}

	for (int i = 1, distance = 0; i <= count; i *= 10)
	{
		int number = (count / i) % 10;

		char keyName[16];
		wsprintf(keyName, "%d_black", number);
		IMAGEMANAGER->render(keyName, hdc, destX + (multiplyCount * 12), destY);

		multiplyCount--;
	}
}
