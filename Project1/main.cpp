#include <windows.h>

#include "PlateWindow.h"

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

// прототип оконной функции
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	// Описание класса главного окна приложения
	WNDCLASS wcl;
	wcl.hInstance = hThisInst;
	wcl.lpszClassName = L"MainWindowClass";
	wcl.lpfnWndProc = MainWindowProc;
	wcl.style = 0;
	wcl.lpszMenuName = NULL;
	wcl.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	// Регистрация класса главного окна приложения
	if (!RegisterClass(&wcl)) return 0;

	// Создание главного окна приложения
	HWND hWnd;
	hWnd = CreateWindow(L"MainWindowClass", L"Пример обработки сообщений",
		WS_OVERLAPPEDWINDOW, 0, 0,1000, 700, HWND_DESKTOP, NULL, hThisInst, NULL);
	ShowWindow(hWnd, nWinMode);
	UpdateWindow(hWnd);

	// Регистрация класса внутреннего окна
	RegisterPlateWindow();
	// Создание внутреннего окна
	CreateWindow(L"PlateWindowClass", L"Пластина", WS_CHILD | WS_VISIBLE,
		10, 10, 640, 640, hWnd, NULL, hThisInst, NULL);

	// Цикл обработки сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// Оконная функция главного окна приложения
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE: {
		HWND hGrpButtons1 = CreateWindowEx(WS_EX_WINDOWEDGE,
			L"BUTTON",
			L"Фигура",
			WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
			680, 20,
			100, 150,
			hWnd,
			(HMENU)FIGUR,
			NULL, NULL);
		HWND buttonPeshka = CreateWindow(
			L"BUTTON",
			L"Пешка",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10,
			20,
			70,
			15,
			hGrpButtons1,
			(HMENU)PESHKA,
			NULL,
			NULL
		);
		SendMessage(buttonPeshka, BM_SETCHECK, BST_CHECKED, 0);
		CreateWindow(
			L"BUTTON",
			L"Слон",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10,
			40,
			70,
			15,
			hGrpButtons1,
			(HMENU)SLON,
			NULL,
			NULL
		);
		CreateWindow(
			L"BUTTON",
			L"КОРОЛЬ",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10,
			60,
			80,
			15,
			hGrpButtons1,
			(HMENU)KOROL,
			NULL,
			NULL
		);
		CreateWindow(
			L"BUTTON",
			L"Ферзь",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10,
			80,
			70,
			15,
			hGrpButtons1,
			(HMENU)FERZ,
			NULL,
			NULL
		);
		CreateWindow(
			L"BUTTON",
			L"Конь",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10,
			100,
			70,
			15,
			hGrpButtons1,
			(HMENU)KON,
			NULL,
			NULL
		);
		CreateWindow(
			L"BUTTON",
			L"Ладья",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10,
			120,
			70,
			15,
			hGrpButtons1,
			(HMENU)LADI,
			NULL,
			NULL
		);
		HWND hGrpButtons = CreateWindowEx(WS_EX_WINDOWEDGE,
			L"BUTTON",
			L"Цвет",
			WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
			800, 20,
			100,60,
			hWnd,
			(HMENU)COLOR,
			NULL, NULL);
		HWND buttonBlack = CreateWindow(L"BUTTON",
			L"Черные",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10, 20, 70, 15,
			hGrpButtons,
			(HMENU)BLACK,
			NULL,
			NULL);
		SendMessage(buttonBlack, BM_SETCHECK, BST_CHECKED, 0);
		CreateWindow(L"BUTTON",
			L"Белые",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10, 40, 70, 15,
			hGrpButtons,
			(HMENU)WHITE,
			NULL,
			NULL);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}