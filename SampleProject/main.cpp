//======================================================================
// 
// Main
// â√éËî[ètåc
// 
//======================================================================
#include<Windows.h>
#include<assert.h>

#include<chrono>
#include<ctime>

#include"main.h"

#include"Renderer.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HWND g_hWnd;
static HINSTANCE g_Hinstance;

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	lpCmdLine = lpCmdLine;
	hPrevInstance = hPrevInstance;

	const LPCWSTR CLASS_NAME = TEXT("Windows");
	const LPCWSTR WINDOW_NAME = TEXT("AstralLayer");

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW),
		NULL,
		CLASS_NAME,
		NULL
	};


	RegisterClassEx(&wcex);

	g_Hinstance = hInstance;
	g_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		(GetSystemMetrics(SM_CXSCREEN) / 2) - ((SCREEN_WIDHT + GetSystemMetrics(SM_CXDLGFRAME)) / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - ((SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) + GetSystemMetrics(SM_CYCAPTION)) / 2),
		SCREEN_WIDHT,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	Renderer renderer;
	renderer.Init(g_hWnd);
	
	time_t dwExecLastTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	time_t dwCurrentTime = 0;

	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

			if ((dwCurrentTime - dwExecLastTime) >= (1 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				renderer.Update();
				renderer.Draw();
			}
		}
	}

	renderer.Uninit();

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			DestroyWindow(hWnd);
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}