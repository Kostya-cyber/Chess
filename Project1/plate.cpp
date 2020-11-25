#include "hole.h"
#include "Plate.h"


// конструктор
PLATE::PLATE(int width, int height) {
	this->width = width;
	this->height = height;
}

// добавить отверстие на пластину
void PLATE::AddHole(HOLE * Hole) {
	bool flag = true;
	for (unsigned i = 0; i < this->Hole.size(); i++) {
		if (Hole->GetX() == this->Hole[i]->GetX() && Hole->GetY() == this->Hole[i]->GetY()) {
			flag = false;
		}
	}
	if (flag) {
		(this->Hole).push_back(Hole);
	}
	
}

void PLATE::DeleteHole(int x, int y, HDC hDC) {
	bool flag = false;
	int index = 0;
	for (unsigned i = 0; i < Hole.size(); i++) {
		if (Hole[i]->IsPointInside(x, y)) {  // если точка внутри отверстия
			index = i;                   // запомнить ссылку на этот объект
			flag = true;
		}
	}
	if (index>=0 && flag) {
		HOLE* hole = Hole[index];
		Hole.erase(Hole.begin() + index);
		hole->Erase(hDC);
	}
}

// определить отверстие по координате
HOLE* PLATE::GetHoleFromPoint(int x, int y) {
	HOLE * result = NULL;                    // пока отверстие не найдено
	for (unsigned i = 0; i < Hole.size(); i++) {
		if (Hole[i]->IsPointInside(x, y)) {  // если точка внутри отверстия
			result = Hole[i];                // запомнить ссылку на этот объект
		}
	}
	return result;
}

void PLATE::DeleteHoleObject(HOLE* Hole, HDC hDC) {
	bool flag = false;
	int index = 0;
	for (unsigned i = 0; i < this->Hole.size(); i++) {
		if ((this->Hole[i]->getColor() != Hole->getColor() || this->Hole[i]->getFigure() != Hole->getFigure()) && this->Hole[i]->IsPointInside(Hole->GetX(), Hole->GetY())) {  // если точка внутри отверстия
			index = i;                   // запомнить ссылку на этот объект
			flag = true;
			break;
		}
	}
	if (!flag) {
		for (unsigned i = 0; i < this->Hole.size(); i++) {
			if (this->Hole[i]->getColor() == Hole->getColor() && this->Hole[i]->getFigure() == Hole->getFigure() && this->Hole[i]->IsPointInside(Hole->GetX(), Hole->GetY())) {
				index = i;                   // запомнить ссылку на этот объект
				flag = true;
				break;
			}
		}
	}
	
	if (index >= 0 && flag) {
		HOLE* hole = this->Hole[index];
		this->Hole.erase(this->Hole.begin() + index);
		hole->Erase(hDC);
	}
}

bool PLATE::CheckPlateFree(HOLE* Hole) {
	int count = 0;
	for (unsigned i = 0; i < this->Hole.size(); i++) {
		if (Hole->GetX() == this->Hole[i]->GetX() && Hole->GetY() == this->Hole[i]->GetY()) {
			count++;
		}
	}
	if (count == 1) {
		return true;
	}
	else {
		return false;
	}
}

// нарисовать пластину и набор отверстий
void PLATE::Draw(HDC hDC, HWND hwnd) {
	// сначала рисуем пластину
	SelectObject(hDC, GetStockObject(BLACK_PEN));
	SelectObject(hDC, GetStockObject(WHITE_BRUSH));
	// затем рисуем все отверстия
	for (unsigned i = 0; i < Hole.size(); i++) {
		Hole[i]->Draw(hDC);
	}
}

void PLATE::DrawBord(HDC hDC) {
	bool flag = true;
	for (unsigned i = 0; i < 8; i++) {
		if (flag) {
			flag = false;
		}
		else {
			flag = true;
		}
		for (unsigned j = 0; j < 8; j++) {
			HOLE* hole = new HOLE(i * 80, j * 80, 0,0);
			if (flag) {
				flag = false;
			}
			else {
				flag = true;
			}
			hole->DrawPlate00(hDC, flag);

		}
	}
}