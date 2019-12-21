#include <Windows.h>
#include "capture.h"

// 窗口类名称
#define WIN_CLASS_NAME	TEXT("VideoCapture\0")
// 窗口名称
#define WIN_NAME		TEXT("Video capture Preview\0")
// 窗口宽和高
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
		ShowWindow(hwnd, SW_HIDE); // 在屏幕中显示窗口
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // 将"退出"消息插入消息队列
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam); // 执行默认的消息处理
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hInstP, PSTR szCmdLine, int nCmdShow)
{
	HWND hwnd = 0;
	CCapture capture;

	HRESULT hr = S_OK;
	WNDCLASS wc;

	// 1、初始化COM库
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FALSE(hr))
		return 1;

	// 注册窗口类
	ZeroMemory(&wc, sizeof(wc));
	wc.lpfnWndProc = WndMainProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = WIN_CLASS_NAME;
	wc.lpszMenuName = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	if (!RegisterClass(&wc)) // 为应用程序的窗口注册一个窗口类
	{
		
		CoUninitialize();
		return 1;
	}

	// 基于窗口类创建一个窗口
	hwnd = CreateWindow(WIN_CLASS_NAME, WIN_NAME,
		WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT, 0, 0, hInstance, 0);
	if (hwnd)
	{	
		// 2、创建各filter Graph
		capture.Init(hwnd);
		// 3、找到视频采集设备
		capture.FindCaptureDevice();
		// 4、将基类filter添加到filter granph Manager中
		capture.AddToGraph();
		// 5、渲染并预览视频
		capture.Render();

		ShowWindow(hwnd, SW_SHOW); // 在屏幕中显示窗口

		// 从消息队列获取消息
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg); // 翻译一些键盘消息
			DispatchMessage(&msg); // 将消息发送给窗口过程
		}
	}
	
	// 6、销毁先前创建的filter Graph
	capture.DestroyGraph();
	// 7、释放COM
	CoUninitialize();

	return 0;
}
