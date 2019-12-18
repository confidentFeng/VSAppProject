/* ������
* �й���ý��ѧ/���ֵ��Ӽ���
* leixiaohua1020@126.com
*
*/

#include "stdafx.h"
#include <dshow.h>

// �õ���DirectShow SDK���ӿ�
#pragma comment(lib,"strmiids.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	IGraphBuilder *pGraph = NULL; // ��������һ��Filter Graph(�̳���IFilterGraph�ӿ�)
	IMediaControl *pControl = NULL; // ý�����
	IMediaEvent   *pEvent = NULL; // ý���¼�

								  // ��ʼ��COM��.
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		printf("���� - �޷���ʼ�� COM ���\n");
		return -1;
	}

	// ����Filter Graph Manager(�˲���ͼ�������)
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph);
	if (FAILED(hr))
	{
		printf("���� - �޷����� Filter Graph Manager.\n");
		return -1;
	}

	// ��ѯý����ƺ�ý���¼��ӿ�
	hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

	// ����Graph������������Ը��Ĵ����ŵ��ļ�����
	hr = pGraph->RenderFile(L"test.mp4", NULL);
	if (SUCCEEDED(hr))
	{
		// ����Graph.
		hr = pControl->Run();
		if (SUCCEEDED(hr))
		{
			//�ȴ��طŽ����¼�.
			long evCode;
			pEvent->WaitForCompletion(INFINITE, &evCode);
			// �м�: ��ʵ��Ӧ�õ���,����ʹ��INFINITE��ʶ, ��Ϊ���᲻ȷ������������
		}
	}
	else 
	{
		printf("���� - ����Ƶ�ļ�ʧ��\n");
	}

	// �ͷ�������Դ�͹ر�COM��
	pControl->Release();
	pEvent->Release();
	pGraph->Release();
	CoUninitialize();

	return 0;
}