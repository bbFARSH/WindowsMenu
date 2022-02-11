#include<Windows.h>
#include<stdio.h>

CONST CHAR g_szCLASS_NAME[] = "MyWindowClass";
CONST CHAR g_szTitle[] = "My first MainWindow";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wc; //  windowd class
	//1.1) Проиницилизировать поля структуры
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc; // УКАЗАТЕЛЬ НА ПРОЦЕДУРУ ОКНА
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = g_szCLASS_NAME;
	wc.lpszMenuName = NULL;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class Registration failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//2) РЕГИСТРАЦИЯ СОЗДАНИЯ ОКНА
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CXSCREEN);
	int window_weight = screen_width - screen_width / 4;
	int window_height = screen_height - screen_height / 4;
	int window_start_x = screen_width / 8;
	int window_start_y = screen_height / 8;
	HWND hwnd = CreateWindowEx
	(
		WS_EX_CLIENTEDGE, // exStyle
		g_szCLASS_NAME, // имя класса окна
		g_szTitle, // Заголовок окна
		WS_OVERLAPPEDWINDOW, // Стиль окна OVERLAPPED всегда задаётся для главного окна программы
		CW_USEDEFAULT, // ПОЗИЦИЯ окна на экране
		CW_USEDEFAULT, // ПОЗИЦИЯ окна на экране
		CW_USEDEFAULT, // Размер окна
		CW_USEDEFAULT, // Размер окна
		NULL, // Родительское окно
		NULL, // Меню (отсутсвует)
		hInstance, // *.exe файл окна
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failer", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow); // Задаем режим отоброжения окна
	UpdateWindow(hwnd); // Прорисовка окна(отправляем сообщение в WM_PAINT)
	//3) ЗАПУСКАЕМ ЦИКЛ СООБЩЕНИЙ
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE://Создаются элементы окна
		break;
	case WM_COMMAND:
		break;
	case WM_MOVE:
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		CONST INT SIZE = 256;
		CHAR buffer[SIZE]{};
		SendMessage(hwnd, WM_GETTEXT, SIZE, (LPARAM)buffer);
		sprintf
		(
			buffer, "%s Position: %dx%d, Size: %dx%d",
			g_szTitle,
			rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer);
	}
	break;
	case WM_CLOSE:
		switch (MessageBox(
			hwnd,
			"Вы действительно хотите закрыть окно?",
			"Шо в натуре", MB_YESNO | MB_ICONQUESTION))
		{
		case IDYES:
			MessageBox(hwnd, "Лучше б двери закрыли ;-)", "Info", MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd); break;
		case IDNO: MessageBox(hwnd, "Это хорошо", "Info", MB_OK | MB_ICONINFORMATION); break;
		}break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}return 0;
}