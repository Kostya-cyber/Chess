#ifndef PlateH
#define PlateH

#include <windows.h>

#include <vector>
using namespace std;

#include "Hole.h"

class PLATE {
private:
	int width, height;                     // размеры пластины
	vector<HOLE *> Hole;                   // список отверстий
public:
	PLATE(int width, int height);          // конструктор
	void AddHole(HOLE * Hole);   
	void DeleteHole(int x, int y, HDC hDC);
	HOLE* GetHoleFromPoint(int x, int y);   // определить отверстие по координате
	void Draw(HDC hDC, HWND hwnd);                    // нарисовать пластину с отверстиями
	void DrawBord(HDC hDC);
	void DeleteHoleObject(HOLE* Hole, HDC hDC);
	bool CheckPlateFree(HOLE* Hole);
};

#endif
