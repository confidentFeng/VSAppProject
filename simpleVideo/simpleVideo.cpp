/* 雷霄骅
* 中国传媒大学/数字电视技术
* leixiaohua1020@126.com
*
*/

#include "stdafx.h"
#include <dshow.h>

// 用到的DirectShow SDK链接库
#pragma comment(lib,"strmiids.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	IGraphBuilder *pGraph = NULL; // 用来创建一个Filter Graph(继承自IFilterGraph接口)
	IMediaControl *pControl = NULL; // 媒体控制
	IMediaEvent   *pEvent = NULL; // 媒体事件

								  // 初始化COM库.
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		printf("错误 - 无法初始化 COM 组件\n");
		return -1;
	}

	// 创建Filter Graph Manager(滤波器图表管理器)
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph);
	if (FAILED(hr))
	{
		printf("错误 - 无法创建 Filter Graph Manager.\n");
		return -1;
	}

	// 查询媒体控制和媒体事件接口
	hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

	// 建立Graph，在这里你可以更改待播放的文件名称
	hr = pGraph->RenderFile(L"test.mp4", NULL);
	if (SUCCEEDED(hr))
	{
		// 运行Graph.
		hr = pControl->Run();
		if (SUCCEEDED(hr))
		{
			//等待回放结束事件.
			long evCode;
			pEvent->WaitForCompletion(INFINITE, &evCode);
			// 切记: 在实际应用当中,不能使用INFINITE标识, 因为它会不确定的阻塞程序
		}
	}
	else 
	{
		printf("错误 - 打开视频文件失败\n");
	}

	// 释放所有资源和关闭COM库
	pControl->Release();
	pEvent->Release();
	pGraph->Release();
	CoUninitialize();

	return 0;
}