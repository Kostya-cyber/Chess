#include "PlateWindow.h"
#include "Plate.h"
#include "Hole.h"
#include <winuser.h>
#include <math.h>

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

// Описание и регистрация класса окна "Пластина"
int RegisterPlateWindow() {
	WNDCLASS wcl;
	wcl.hInstance = GetModuleHandle(NULL);
	wcl.lpszClassName = L"PlateWindowClass";
	wcl.lpfnWndProc = PlateWindowProc;
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpszMenuName = NULL;
	wcl.hIcon = NULL;
	wcl.hCursor = LoadCursor(NULL, IDC_CROSS);
	wcl.hbrBackground = (HBRUSH)(1 + COLOR_WINDOW);
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	return RegisterClass(&wcl);
}


// Оконная функция внутреннего окна
LRESULT CALLBACK PlateWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Статические локальные переменные, необходимые для работы оконной функции
	static PLATE Plate(640, 640);   // объект-пластина
	static HOLE * LastHole;        // ссылка на некоторый объект-отверстие
	static int LastX, LastY;        // последние координаты мыши
	static enum { NO_OPERATION, CHANGE_POS} Mode; // режим работы с объектами

	MouseState ms;
	ExtractMouseParams(wParam, lParam, &ms);

	switch (uMsg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);  // получить контекст устройства
		Plate.DrawBord(hDC);
		Plate.Draw(hDC, hWnd);                  // вызвать метод построения изображения пластины
		EndPaint(hWnd, &ps);              // освободить контекст устройства
		break;
	}

	case WM_LBUTTONDOWN: // нажатие левой кнопки манипулятора "мышь"
						 // создаем объект и начинаем менять его размер
	{
		if (Mode != CHANGE_POS) {
			HWND figur = FindWindowExA(GetParent(hWnd), 0, 0, "Фигура");
			HWND color = FindWindowExA(GetParent(hWnd), 0, 0, "Цвет");
			int fig, cor;
			if (IsDlgButtonChecked(color, WHITE)) {
				cor = WHITE;
			}
			if (IsDlgButtonChecked(color, BLACK)) {
				cor = BLACK;
			}
			if (IsDlgButtonChecked(figur, PESHKA)) {
				fig = PESHKA;
			}
			if (IsDlgButtonChecked(figur, SLON)) {
				fig = SLON;
			}
			if (IsDlgButtonChecked(figur, KOROL)) {
				fig = KOROL;
			}
			if (IsDlgButtonChecked(figur, FERZ)) {
				fig = FERZ;
			}
			if (IsDlgButtonChecked(figur, KON)) {
				fig = KON;
			}
			if (IsDlgButtonChecked(figur, LADI)) {
				fig = LADI;
			}
			LastHole = new HOLE(ms.xPos, ms.yPos,fig, cor);  // создаем новый объект-отверстие,
			Plate.AddHole(LastHole);               // добавляем его на пластину
			LastHole->Draw(GetWindowDC(hWnd));
		}// и сразу же рисуем
		break;
	}

	case WM_MBUTTONDOWN: // нажатие средней кнопки манипулятора "мышь"
						 // начинаем менять размер объекта
	{
		Plate.DeleteHole(ms.xPos, ms.yPos, GetWindowDC(hWnd));
		break;
	}

	case WM_RBUTTONDOWN: // нажатие правой кнопки манипулятора "мышь"
						 // начинаем менять положение объекта
	{
		LastHole = Plate.GetHoleFromPoint(ms.xPos, ms.yPos); // получим объект под указателем мыши
		if (LastHole != NULL) { // если он есть
			Mode = CHANGE_POS;    // переходим в режим изменения положения объекта
			LastX = ms.xPos; LastY = ms.yPos;  // запомним координаты курсора
		}
		break;
	}

	case WM_MOUSEMOVE: // перемещение манипулятора "мышь"
	{
		if (LastHole != NULL) // какой-нибудь объект выбран?
			switch (Mode) {     // в каком режиме сейчас находимся?
			case CHANGE_POS: // --- режим изменения положения объекта ---
			{
				// переместить текущий объект
				LastHole->Erase(GetWindowDC(hWnd));             // стереть
				LastHole->MoveBy(ms.xPos - LastX, ms.yPos - LastY);  // изменить координаты
				LastHole->Draw(GetWindowDC(hWnd));             // нарисовать заново
							// запомнили координаты, куда уже переместили объект
				LastX = ms.xPos; LastY = ms.yPos;
				
				break;
			}
			}
		break;
	}

	case WM_LBUTTONUP: // отпустили левую кнопку
	case WM_MBUTTONUP: // отпустили среднюю кнопку
	case WM_RBUTTONUP:// отпустили правую кнопку
	{
		if (Mode == CHANGE_POS) {
			LastHole->SavePoint();
			if (Plate.CheckPlateFree(LastHole)) {
				LastHole->Draw(GetWindowDC(hWnd));
			}
			else {
				LastHole->Draw(GetWindowDC(hWnd));
				Plate.DeleteHoleObject(LastHole, GetWindowDC(hWnd));
			}
			
		}
		Mode = NO_OPERATION; // забыли режим работы

		LastHole = NULL;     // забыли, с каким отверстием работали
		InvalidateRect(hWnd, NULL, false); // обновить окно
		break;
	}

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}


// функция для анализа параметров сообщений манипулятора "мышь"
void ExtractMouseParams(WPARAM wParam, LPARAM lParam, MouseState * ms) {
	// извлечение координат указателя
	ms->xPos = LOWORD(lParam);
	ms->yPos = HIWORD(lParam);
	// анализ состояния кнопок и клавиш
	ms->lButtonPressed = (wParam & MK_LBUTTON) != 0;
	ms->rButtonPressed = (wParam & MK_RBUTTON) != 0;
	ms->mButtonPressed = (wParam & MK_MBUTTON) != 0;
	ms->shiftPressed = (wParam & MK_SHIFT) != 0;
	ms->controlPressed = (wParam & MK_CONTROL) != 0;
}