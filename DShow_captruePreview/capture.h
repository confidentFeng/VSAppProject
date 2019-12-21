#pragma once

#include <Windows.h>
#include <dshow.h>

// 用于确保安全释放的宏
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }

class CCapture
{
public:
	CCapture();
	~CCapture();

	HRESULT Init(HWND hwnd); // 初始化
	HRESULT FindCaptureDevice(); // 寻找视频采集设备
	HRESULT AddToGraph(); // 将base filter添加到filter graph中
	HRESULT Render(); // 渲染并预览视频
	void DestroyGraph(); // 销毁先前创建的filter

	void ResizeWindow(); // 重设窗口

private:
	// 窗口句柄
	HWND					m_hwnd;
	// 视频采集预览相关
	IGraphBuilder			*m_pGraph; // filter granph(manager)
	ICaptureGraphBuilder2	*m_pCapture; // capture granph
	IMediaControl			*m_pMediaC; // 媒体控制接口
	IMediaEventEx			*m_pMediaE; // 媒体事件接口
	IVideoWindow			*m_pVideoW; // 视频窗口接口
	IBaseFilter				*m_pFilter; // 基类filter
};
