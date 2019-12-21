#include "capture.h"

CCapture::CCapture()
{

}

CCapture::~CCapture()
{

}

// ��ʼ��
HRESULT CCapture::Init(HWND hwnd)
{
	HRESULT hr;

	// ����filter graph
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void **)&m_pGraph);
	if (FAILED(hr))
		return hr;

	// ����capture granph
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC,IID_ICaptureGraphBuilder2, (void **)&m_pCapture);
	if (FAILED(hr))
		return hr;

	// ��ѯgraph�и�IID������ʶ�Ľӿ�ָ��
	hr = m_pGraph->QueryInterface(IID_IMediaControl, (LPVOID *)&m_pMediaC);
	if (FAILED(hr))
		return hr;
	hr = m_pGraph->QueryInterface(IID_IMediaEventEx, (LPVOID *)&m_pMediaE);
	if (FAILED(hr))
		return hr;
	hr = m_pGraph->QueryInterface(IID_IVideoWindow, (LPVOID *)&m_pVideoW);
	if (FAILED(hr))
		return hr;

	// Ϊcapture graphָ��Ҫʹ�õ�filter graph
	hr = m_pCapture->SetFiltergraph(m_pGraph);
	if (FAILED(hr))
		return hr;

	// ��ô��ھ��
	m_hwnd = hwnd;

	return hr;
}

// Ѱ����Ƶ�ɼ��豸
HRESULT CCapture::FindCaptureDevice()
{
	HRESULT hr = S_OK;
	ICreateDevEnum *pDevEnum = NULL;
	IEnumMoniker *pClassEnum = NULL; // ������Ƶ�ɼ��豸��ö��
	IMoniker* pMoniker = NULL; // �豸Moniker��

	// ����ϵͳ�豸ö��
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,IID_ICreateDevEnum, (void **)&pDevEnum);
	if (FAILED(hr))
		return hr;

	// ����һ��ָ����Ƶ�ɼ��豸��ö��
	hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pClassEnum, 0);
	if (FAILED(hr) || pClassEnum == NULL)
	{
		SAFE_RELEASE(pDevEnum);
		return hr;
	}

	// ʹ�õ�һ���ҵ�����Ƶ�ɼ��豸��ֻ�����ڵ�����ͷ�������
	hr = pClassEnum->Next(1, &pMoniker, NULL);
	if (hr == S_FALSE)
	{
		SAFE_RELEASE(pDevEnum);
		SAFE_RELEASE(pClassEnum);
		return hr;
	}
	// ���ҵ�����ͷ��moniker��filter graph
	hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&m_pFilter);
	if (FAILED(hr))
	{
		SAFE_RELEASE(pDevEnum);
		SAFE_RELEASE(pClassEnum);
		SAFE_RELEASE(pMoniker);
		return hr;
	}

	// ����filter graph�����ü���
	m_pFilter->AddRef(); 

	return hr;
}

// ��base filter��ӵ�filter graph��
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

// ��Ⱦ��Ԥ����Ƶ
HRESULT CCapture::Render()
{
	HRESULT hr;

	// ��ICaptureGraphBuilder2�ӿڹ���Ԥ����filter��·
	hr = m_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, m_pFilter, NULL, NULL);
	if (FAILED(hr))
	{
		m_pFilter->Release();
		return hr;
	}
	// ͬʱ����һ��д�ļ���filter��·
	IBaseFilter *pMux;
	hr = m_pCapture->SetOutputFileName(&MEDIASUBTYPE_Avi, L"D:\\example.avi", &pMux, NULL); // ���������Ƶ�ļ�λ��
	hr = m_pCapture->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, m_pFilter, NULL, pMux); // ��m_pFilter�����pin���ӵ�pMux
	
	// ʹ����Ϳ����ͷ�base filter��
	pMux->Release();
	m_pFilter->Release();

	// ��ʾ���� , Ԥ���ɼ�ͼ��
	hr = m_pVideoW->put_Owner((OAHWND)m_hwnd);
	if (FAILED(hr))
		return hr;
	hr = m_pVideoW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);
	if (FAILED(hr))
		return hr;
	ResizeWindow(); // ���贰��
	hr = m_pVideoW->put_Visible(OATRUE);
	if (FAILED(hr))
		return hr;
	hr = m_pMediaC->Run();
	
	return hr;
}

// ������ǰ������filter
void CCapture::DestroyGraph()
{
	if (m_pMediaC)
		m_pMediaC->StopWhenReady();

	if (m_pVideoW)
	{
		m_pVideoW->put_Visible(OAFALSE);
		m_pVideoW->put_Owner(NULL);
	}

	// ȷ���ӿڶ���ȫ�ͷ���
	SAFE_RELEASE(m_pMediaC);
	SAFE_RELEASE(m_pMediaE);
	SAFE_RELEASE(m_pVideoW);
	SAFE_RELEASE(m_pGraph);
	SAFE_RELEASE(m_pCapture);
}

// ���贰��
void CCapture::ResizeWindow()
{
	RECT rc;

	if (m_pVideoW)
	{
		GetClientRect(m_hwnd, &rc);
		m_pVideoW->SetWindowPosition(0, 0, rc.right, rc.bottom);
	}
}