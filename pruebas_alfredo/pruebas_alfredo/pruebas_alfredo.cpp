// pruebas_alfredo.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "pruebas_alfredo.h"
#include "Recursividad.h"
#include <Windowsx.h>

#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRUEBASALFREDO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRUEBASALFREDO));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRUEBASALFREDO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(GetStockObject(GRAY_BRUSH));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PRUEBASALFREDO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//
const int CELL_SIZE = 60;
int playerTurn = 1;
int anterior = 0;
bool cambio = true;
int gameBoardplayer[64] = {};
int gameBoardrandom[64] = {};
int cambiarCell[3];
//HICON jolla1, jolla2;
/**
*@brief crea el cuadro principal del juego (el fondo)
*@param pRect rectangulo
*@param hWnd es un window handeler}
*@return regresa un verdadero o falso dependiendo de la instruccion
*/
BOOL GetGameBoardRect(HWND hWnd, RECT* pRect) {
	RECT rc;
	if (GetClientRect(hWnd, &rc)) {
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;
		pRect->left = (width - CELL_SIZE * 8) / 2;
		pRect->top = (height - CELL_SIZE * 8) / 2;
		pRect->right = pRect->left + CELL_SIZE * 8;
		pRect->bottom = pRect->top + CELL_SIZE * 8;
		return true;
	}
	SetRectEmpty(pRect);
	return false;
}
/**
*@brief dibuja las lineas dentro del cuadro que conforman al grid
*@param son el vector de inicio y final que se le asigna a la linea
*/
void DrawLine(HDC hdc, int x1, int y1, int x2, int y2) {
	MoveToEx(hdc, x1, y1, nullptr);
	LineTo(hdc, x2, y2);
}
/**
*@brief te da el index de la casilla donde hiciste clic
*@param hWnd es un window handeler
*@param x, y son los valores en x, y del punto dado
*@return regresa un valor deacuerdo donde hiciste clic en la pantalla
*/
int GetCellNumberFromPoint(HWND hWnd, int x, int y) {
	RECT rc;
	POINT pt;
	pt.x = x;
	pt.y = y;
	int colum;
	int row;
	if (GetGameBoardRect(hWnd, &rc)) {
		//hace clic dentro de la reticula del juego
		if (PtInRect(&rc, pt)) {
			x = pt.x - rc.left;
			y = pt.y - rc.top;
			colum = x / CELL_SIZE;
			row = y / CELL_SIZE;
			return colum + row * 8;
		}
		//hace clic fuera de la reticula del juego
		else {
			return -1;
		}
	}
	return -1;
}
/**
*@brief te da la dimencion de la celda dependiendo de su index
*@param hWnd es un window handler
*@param index es el index de la celda
*@param pRect es un rectangulo
*@return regresa un true o false dependiendo de la instruccion
*/
bool GetCellRect(HWND hWnd, int index, RECT* pRect) {
	RECT rcBoard;
	SetRectEmpty(pRect);
	int x, y;
	if (index < 0 || index > 63) {
		return false;
	}
	if (GetGameBoardRect(hWnd, &rcBoard)) {
		y = index / 8;
		x = index % 8;
		//es el rectangulo deacuerdo al index
		pRect->left = rcBoard.left + x * CELL_SIZE + 1;
		pRect->top = rcBoard.top + y * CELL_SIZE + 1;
		pRect->right = pRect->left + CELL_SIZE - 1;
		pRect->bottom = pRect->top + CELL_SIZE - 1;
		return true;
	}
	return false;
}
/**
*@brief esto es para saver que color hay en especifico en cada casilla y poder usar x, y (k, j) 
*@brief para comparar en recursividad
*@param cellContenido es un array que contiene los colores de todas las casillas
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
switch (message) {
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		// Analizar las selecciones de menú:
		switch (wmId) {
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_CREATE: {
		//brush = CreateSolidBrush(RGB(20,30,5));
		//cargar los iconos
		//jolla1 = LoadIcon(hInst, MAKEINTRESOURCE(jolla_redonda));
		//jolla2 = LoadIcon(hInst, MAKEINTRESOURCE(jolla_triangular));
	}
	break;
	case WM_LBUTTONDOWN: {
		HDC hdc = GetDC(hWnd);
		bool precionado = false;
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		int index = GetCellNumberFromPoint(hWnd, xPos, yPos);
		if (NULL != hdc) {
			//regresa el valor (index) de la casilla
			/*WCHAR temp[100];
			wsprintf(temp, L"Index = %d", index);
			TextOut(hdc, xPos, yPos, temp, lstrlen(temp));*/
			//da la dimencion de la casilla dado su index, evita que los colores se sobrepongan y
			//si el jugador da dos clicls en diferentes casillas lo siguiente intercambia el color de las casillas donde se iso clic
			if (index != -1) {
				RECT rcCell;
				if (GetCellRect(hWnd, index, &rcCell)) {
					if (playerTurn == 2) {
						cambiarCell[1] = gameBoardrandom[index];
						playerTurn = 1;
						precionado = true;
					}
					else if ((playerTurn == 1)) {
						cambiarCell[0] = gameBoardrandom[index];
						anterior = index;
						playerTurn = 2;
					}
					if (precionado == true) {
						gameBoardrandom[index] = cambiarCell[0];
						gameBoardrandom[anterior] = cambiarCell[1];
						precionado = false;
					}
				}
			}
			ReleaseDC(hWnd, hdc);
		}
	}
	break;
	//tamaño minimo de la ventana
	case WM_GETMINMAXINFO: {
		MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;
		if (pMinMax != nullptr) {
			pMinMax->ptMinTrackSize.x = CELL_SIZE * 10;
			pMinMax->ptMinTrackSize.y = CELL_SIZE * 10;
		}
	}
	break;
	case WM_PAINT: {
		Recursividad* recursividad;
		recursividad = new Recursividad;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rc;
		RECT rcCell;
		int random = 0;
		if (GetGameBoardRect(hWnd, &rc)) {
			FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
			// TODO: Agregar cualquier código de dibujo que use hDC aquí...
			//dibuja las lineas del grid
			for (int i = 0; i < 9; i++) {
				DrawLine(hdc, rc.left + CELL_SIZE * i, rc.top, rc.left + CELL_SIZE * i, rc.bottom);
				DrawLine(hdc, rc.left, rc.top + CELL_SIZE * i, rc.right, rc.top + CELL_SIZE * i);
			}
			//rellena al azar las casillas y le dice con el "cambiar" si puede cambiar cuales casillas estan rellenadas
			if (cambio == true) {
				for (int i = 0; i < ARRAYSIZE(gameBoardrandom); i++) {
					random = rand() % 3;
					if (GetCellRect(hWnd, i, &rcCell)) {
						if (random == 0) {
							FillRect(hdc, &rcCell, (HBRUSH)GetStockObject(WHITE_BRUSH));
						}
						if (random == 1) {
							FillRect(hdc, &rcCell, (HBRUSH)GetStockObject(BLACK_BRUSH));
						}
						if (random == 2) {
							FillRect(hdc, &rcCell, (HBRUSH)GetStockObject(GRAY_BRUSH));
						}
						
						/*if (random % 5 == 0) {
							DrawIcon(hdc, rcCell.left, rcCell.top, jolla1);
						}*/
					}
					//le da un color especifico a la casilla 
					//inportante
					if (random == 0) {
						//este valor puede servir para recursividad
						gameBoardrandom[i] = 2;
					}
					if (random == 1) {
						gameBoardrandom[i] = 1;
					}
					if (random == 2) {
						gameBoardrandom[i] = 3;
					}
					/*if (random % 5 == 0) {
						gameBoardrandom[i] = 4;
					}*/
				}
				recursividad ->Asignar(gameBoardrandom);
				cambio = false;
			}
			//evita que cambie el color de las casillas cuando se escala la ventana
			for (int i = 0; i < ARRAYSIZE(gameBoardrandom); i++) {
				if (GetCellRect(hWnd, i, &rcCell)) {
					if (gameBoardrandom[i] == 1) {
						FillRect(hdc, &rcCell, (HBRUSH)GetStockObject(WHITE_BRUSH));
					}
					if (gameBoardrandom[i] == 2) {
						FillRect(hdc, &rcCell, (HBRUSH)GetStockObject(BLACK_BRUSH));
					}
					if (gameBoardrandom[i] == 3) {
						FillRect(hdc, &rcCell, (HBRUSH)GetStockObject(GRAY_BRUSH));
					}
					/*if (gameBoardrandom[i] == 4) {
						DrawIcon(hdc, rcCell.left, rcCell.top, jolla1);
					}*/
				}
			}
			//dibuja todas las celdas ocupadas
			//si al reescalar la ventana el las regillas se invierten aqui puede haver un bug 
			//o en la seleccion de color por jugador en el case WM_LBUTTONDOWN de LRESULT
			//for (int i = 0; i < ARRAYSIZE(gameBoardplayer); i++) {
			//	if (GetCellRect(hWnd, i, &rcCell)) {
			//		if (gameBoardplayer[i] == 1) {
			//			FillRect(hdc, &rcCell, (HBRUSH)GetStockObject(WHITE_BRUSH));
			//		}
			//		if (gameBoardplayer[i] == 2) {
			//			FillRect(hdc, &rcCell, (HBRUSH)GetStockObject(BLACK_BRUSH));
			//		}
			//		if (gameBoardplayer[i] == 3) {
			//			FillRect(hdc, &rcCell, (HBRUSH)GetStockObject(GRAY_BRUSH));
			//		}
			//		/*if (gameBoardrandom[i] == 4) {
			//			DrawIcon(hdc, rcCell.left, rcCell.top, jolla1);
			//		}*/
			//	}
			//}
			//for (int i = 0; i < ARRAYSIZE(gameBoardplayer); i++) {
			//	if (gameBoardplayer[i] != 0 && GetCellRect(hWnd, i, &rcCell)) {
			//		FillRect(hdc, &rcCell, gameBoardplayer[i] == 2 ? (HBRUSH)GetStockObject(BLACK_BRUSH) :
			//			(HBRUSH)GetStockObject(WHITE_BRUSH));
			//	}
			//}
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Controlador de mensajes del cuadro Acerca de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

