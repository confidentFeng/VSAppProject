#include <Windows.h>
#include "capture.h"

// ����������
#define WIN_CLASS_NAME	TEXT("VideoCapture\0")
// ��������
#define WIN_NAME		TEXT("Video capture Preview\0")
// ���ڿ�͸�
#define WIN_WIDTH	480
#define WIN_HEIGHT	480

LRESULT CALLBACK WndMainProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		//capture.ResizeWindow();
		break;
	case WM_WINDOWPOSCHANGED:
		break;
	case WM_CLOSE:
		ShowWindow(hwnd, SW_HIDE); // ����Ļ����ʾ����
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // ��"�˳�"��Ϣ������Ϣ����
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam); // ִ��Ĭ�ϵ���Ϣ����
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hInstP, PSTR szCmdLine, int nCmdShow)
{
	HWND hwnd = 0;
	CCapture capture;

	HRESULT hr = S_OK;
	WNDCLASS wc;

	// 1����ʼ��COM��
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FALSE(hr))
		return 1;

	// ע�ᴰ����
	ZeroMemory(&wc, sizeof(wc));
	wc.lpfnWndProc = WndMainProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = WIN_CLASS_NAME;
	wc.lpszMenuName = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	if (!RegisterClass(&wc)) // ΪӦ�ó���Ĵ���ע��һ��������
	{
		
		CoUninitialize();
		return 1;
	}

	// ���ڴ����ഴ��һ������
	hwnd = CreateWindow(WIN_CLASS_NAME, WIN_NAME,
		WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT, 0, 0, hInstance, 0);
	if (hwnd)
	{	
		// 2��������filter Graph
		capture.Init(hwnd);
		// 3���ҵ���Ƶ�ɼ��豸
		capture.FindCaptureDevice();
		// 4��������filter��ӵ�filter granph Manager��
		capture.AddToGraph();
		// 5����Ⱦ��Ԥ����Ƶ
		capture.Render();

		ShowWindow(hwnd, SW_SHOW); // ����Ļ����ʾ����

		// ����Ϣ���л�ȡ��Ϣ
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg); // ����һЩ������Ϣ
			DispatchMessage(&msg); // ����Ϣ���͸����ڹ���
		}
	}
	
	// 6��������ǰ������filter Graph
	capture.DestroyGraph();
	// 7���ͷ�COM
	CoUninitialize();

	return 0;
}
