#ifndef holeH
#define holeH

#include <windows.h>

#include <vector>
using namespace std;

class HOLE {
private:
	int x, y;         // координаты центра отверстия
	int figure;
	int color;
	
public:
	HOLE(int x, int y, int figure, int color);        // конструктор
	int GetX();                       // прочитать координату Х
	int GetY();                       // прочитать координату Y
	int getFigure();
	int getColor();
	int IsPointInside(int x, int y);   // проверка, лежит ли точка внутри
	void MoveBy(int dx, int dy);       // сдвинуть отверстие
	void Draw(HDC hDC);               // нарисовать отверстие
	void Erase(HDC hDC);              // стереть отверстие
	void DrawPlate00(HDC hDC, bool flag);
	void SavePoint();
};

#endif
