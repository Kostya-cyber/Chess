#include "hole.h"

#include <math.h>
#include <stdlib.h>
#include <random>
#include <wingdi.h>

#define PESHKA 2001
#define SLON 2002
#define KOROL 2003
#define FERZ 2004
#define KON 2005
#define LADI 2006
#define WHITE 2007
#define BLACK 2008
#define FIGUR 2009
#define COLOR 2010

HOLE::HOLE(int x, int y, int figure, int color) {
	this->x = x;
	this->y = y;
	this->x /= 80;
	this->x *= 80;
	this->y /= 80;
	this->y *= 80;
	this->figure = figure;
	this->color = color;
}

int HOLE::GetX() {
	return x;
}

// прочитать координату Y
int HOLE::GetY() {
	return y;
}

int HOLE::getFigure() {
	return figure;
}

int HOLE::getColor() {
	return color;
}

// проверка, лежит ли точка внутри отверстия
int HOLE::IsPointInside(int x, int y) {
	if (this->x <= x && this->x+80 > x && this->y <= y && this->y+80 > y) {
		return 1;
	}
	else {
		return 0;
	}
}

// сдвинуть отверстие
void HOLE::MoveBy(int dx, int dy) {
	x += dx;
	y += dy;
}

void HOLE::SavePoint() {
	x /= 80;
	x *= 80;
	y /= 80;
	y *= 80;
}

// нарисовать отверстие
void HOLE::Draw(HDC hDC) {
	BITMAP bitmap;
	static HBITMAP hBitmap;
	HGDIOBJ oldBitmap;
	LPCWSTR name =  L"";
	if (this->color == WHITE) {
		if (this->figure == PESHKA) {
			name = L"Chess\\block_w_00.bmp";
		}
		if (this->figure == SLON) {
			name = L"Chess\\block_w_02.bmp";
		}
		if (this->figure == KOROL) {
			name = L"Chess\\block_w_05.bmp";
		}
		if (this->figure == FERZ) {
			name = L"Chess\\block_w_04.bmp";
		}
		if (this->figure == KON) {
			name = L"Chess\\block_w_01.bmp";
		}
		if (this->figure == LADI) {
			name = L"Chess\\block_w_03.bmp";
		}
	}
	if(this->color == BLACK) {
		if (this->figure == PESHKA) {
			name = L"Chess\\block_b_00.bmp";
		}
		if (this->figure == SLON) {
			name = L"Chess\\block_b_02.bmp";
		}
		if (this->figure == KOROL) {
			name = L"Chess\\block_b_05.bmp";
		}
		if (this->figure == FERZ) {
			name = L"Chess\\block_b_04.bmp";
		}
		if (this->figure == KON) {
			name = L"Chess\\block_b_01.bmp";
		}
		if (this->figure == LADI) {
			name = L"Chess\\block_b_03.bmp";
		}
	}
	hBitmap = (HBITMAP)LoadImageW(NULL, name, IMAGE_BITMAP, 80, 80, LR_LOADFROMFILE);
	HDC bmpDC = CreateCompatibleDC(hDC);
	oldBitmap = SelectObject(bmpDC, hBitmap);
	GetObject(hBitmap, sizeof(bitmap), &bitmap);


	BitBlt(hDC, this->x,this->y, bitmap.bmWidth, bitmap.bmHeight, bmpDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(bmpDC, oldBitmap));
	DeleteDC(bmpDC);

}

void HOLE::DrawPlate00(HDC hDC, bool flag) {
	BITMAP bitmap;
	static HBITMAP hBitmap;
	HGDIOBJ oldBitmap;

	LPCWSTR name;
	if(flag) {
		name = L"Chess\\block00.bmp";
	}
	else {
		name = L"Chess\\block01.bmp";
	}
	hBitmap = (HBITMAP)LoadImageW(NULL, name, IMAGE_BITMAP, 80, 80, LR_LOADFROMFILE);
	HDC bmpDC = CreateCompatibleDC(hDC);
	oldBitmap = SelectObject(bmpDC, hBitmap);
	GetObject(hBitmap, sizeof(bitmap), &bitmap);
	BitBlt(hDC, x, y, bitmap.bmWidth, bitmap.bmHeight, bmpDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(bmpDC, oldBitmap));
	DeleteDC(bmpDC);
}

// стереть отверстие
void HOLE::Erase(HDC hDC) {
	// рисуем белым цветом
	SelectObject(hDC, GetStockObject(WHITE_PEN));
	SelectObject(hDC, GetStockObject(WHITE_BRUSH));
	Rectangle(hDC,x, y, x+80, y+80);
}