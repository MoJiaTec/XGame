#pragma once

#include <wtypes.h>

enum class EWindowStatus: char
{
	normalWindow,	//普通窗口
	maxWindow,		//最大化窗口
	fullWindow,	//窗口模式全屏
	fullScreen	//非窗口模式全屏
};

//初始化Application所需的参数结构
struct SApplicationParam
{
	LPCTSTR wndClassName;
	LPCTSTR title;

	UINT width;
	UINT height;

	EWindowStatus windowStatus;
};