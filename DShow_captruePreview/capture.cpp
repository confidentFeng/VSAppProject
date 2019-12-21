#include "capture.h"

CCapture::CCapture()
{

}

CCapture::~CCapture()
{

}

// 初始化
HRESULT CCapture::Init(HWND hwnd)
{
	HRESULT hr;

	// 创建filter graph
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void **)&m_pGraph);
	if (FAILED(hr))
		return hr;

	// 创建capture granph
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC,IID_ICaptureGraphBuilder2, (void **)&m_pCapture);
	if (FAILED(hr))
		return hr;

	// 查询graph中各IID参数标识的接口指针
	hr = m_pGraph->QueryInterface(IID_IMediaControl, (LPVOID *)&m_pMediaC);
	if (FAILED(hr))
		return hr;
	hr = m_pGraph->QueryInterface(IID_IMediaEventEx, (LPVOID *)&m_pMediaE);
	if (FAILED(hr))
		return hr;
	hr = m_pGraph->QueryInterface(IID_IVideoWindow, (LPVOID *)&m_pVideoW);
	if (FAILED(hr))
		return hr;

	// 为capture graph指定要使用的filter graph
	hr = m_pCapture->SetFiltergraph(m_pGraph);
	if (FAILED(hr))
		return hr;

	// 获得窗口句柄
	m_hwnd = hwnd;

	return hr;
}

// 寻找视频采集设备
HRESULT CCapture::FindCaptureDevice()
{
	HRESULT hr = S_OK;
	ICreateDevEnum *pDevEnum = NULL;
	IEnumMoniker *pClassEnum = NULL; // 用于视频采集设备的枚举
	IMoniker* pMoniker = NULL; // 设备Moniker号

	// 创建系统设备枚举
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,IID_ICreateDevEnum, (void **)&pDevEnum);
	if (FAILED(hr))
		return hr;

	// 创建一个指定视频采集设备的枚举
	hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pClassEnum, 0);
	if (FAILED(hr) || pClassEnum == NULL)
	{
		SAFE_RELEASE(pDevEnum);
		return hr;
	}

	// 使用第一个找到的视频采集设备（只适用于单摄像头的情况）
	hr = pClassEnum->Next(1, &pMoniker, NULL);
	if (hr == S_FALSE)
	{
		SAFE_RELEASE(pDevEnum);
		SAFE_RELEASE(pClassEnum);
		return hr;
	}
	// 绑定找到摄像头的moniker到filter graph
	hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&m_pFilter);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pDevEnum);
		SAFE_RELEASE(pClassEnum);
		SAFE_RELEASE(pMoniker);
		return hr;
	}

	// 增加filter graph的引用计数
	m_pFilter->AddRef(); 

	return hr;
}

// 将base filter添加到filter graph中
HRESULT CCapture::AddToGraph()
{
	HRESULT hr = m_pGraph->AddFilter(m_pFilter, L"Video capture");	
	if (FAILED(hr))
	{
		m_pFilter->Release();
		return hr;
	}

	return hr;
}

// 渲染并预览视频
HRESULT CCapture::Render()
{
	HRESULT hr;

	// 用ICaptureGraphBuilder2接口构建预览的filter链路
	hr = m_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, m_pFilter, NULL, NULL);
	if (FAILED(hr))
	{
		m_pFilter->Release();
		return hr;
	}
	// 同时构建一个写文件的filter链路
	IBaseFilter *pMux;
	hr = m_pCapture->SetOutputFileName(&MEDIASUBTYPE_Avi, L"D:\\example.avi", &pMux, NULL); // 设置输出视频文件位置
	hr = m_pCapture->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, m_pFilter, NULL, pMux); // 将m_pFilter的输出pin连接到pMux
	
	// 使用完就可以释放base filter了
	pMux->Release();
	m_pFilter->Release();

	// 显示窗口 , 预览采集图形
	hr = m_pVideoW->put_Owner((OAHWND)m_hwnd);
	if (FAILED(hr))
		return hr;
	hr = m_pVideoW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);
	if (FAILED(hr))
		return hr;
	ResizeWindow(); // 重设窗口
	hr = m_pVideoW->put_Visible(OATRUE);
	if (FAILED(hr))
		return hr;
	hr = m_pMediaC->Run();
	
	return hr;
}

// 销毁先前创建的filter
void CCapture::DestroyGraph()
{
	if (m_pMediaC)
		m_pMediaC->StopWhenReady();

	if (m_pVideoW)
	{
		m_pVideoW->put_Visible(OAFALSE);
		m_pVideoW->put_Owner(NULL);
	}

	// 确保接口都安全释放了
	SAFE_RELEASE(m_pMediaC);
	SAFE_RELEASE(m_pMediaE);
	SAFE_RELEASE(m_pVideoW);
	SAFE_RELEASE(m_pGraph);
	SAFE_RELEASE(m_pCapture);
}

// 重设窗口
void CCapture::ResizeWindow()
{
	RECT rc;

	if (m_pVideoW)
	{
		GetClientRect(m_hwnd, &rc);
		m_pVideoW->SetWindowPosition(0, 0, rc.right, rc.bottom);
	}
}