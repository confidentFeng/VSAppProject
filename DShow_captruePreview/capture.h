#pragma once

#include <Windows.h>
#include <dshow.h>

// ����ȷ����ȫ�ͷŵĺ�
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }

class CCapture
{
public:
	CCapture();
	~CCapture();

	HRESULT Init(HWND hwnd); // ��ʼ��
	HRESULT FindCaptureDevice(); // Ѱ����Ƶ�ɼ��豸
	HRESULT AddToGraph(); // ��base filter��ӵ�filter graph��
	HRESULT Render(); // ��Ⱦ��Ԥ����Ƶ
	void DestroyGraph(); // ������ǰ������filter

	void ResizeWindow(); // ���贰��

private:
	// ���ھ��
	HWND					m_hwnd;
	// ��Ƶ�ɼ�Ԥ�����
	IGraphBuilder			*m_pGraph; // filter granph(manager)
	ICaptureGraphBuilder2	*m_pCapture; // capture granph
	IMediaControl			*m_pMediaC; // ý����ƽӿ�
	IMediaEventEx			*m_pMediaE; // ý���¼��ӿ�
	IVideoWindow			*m_pVideoW; // ��Ƶ���ڽӿ�
	IBaseFilter				*m_pFilter; // ����filter
};
