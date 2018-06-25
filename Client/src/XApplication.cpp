#include <tchar.h>

#include "XApplication.h"

#define IDR_MAINFRAME                   200

static XApplication *g_pD3dApp = NULL;

LRESULT CALLBACK _MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_pD3dApp->MsgProc(hWnd, msg, wParam, lParam);
}

XApplication::XApplication() :
	m_windowStatus(EWindowStatus::normalWindow)
{
	g_pD3dApp = this;
}

XApplication::~XApplication()
{
}

HRESULT XApplication::InitApp(HINSTANCE hInst, SApplicationParam *param)
{
	//ASSERT(hInst != NULL && param != NULL);
	m_hInstance = hInst;
	m_windowStatus = param->windowStatus;
	m_hWnd = CreateMainWindow(param->wndClassName, param->title, param->width, param->height, param->windowStatus == EWindowStatus::fullScreen);

	::UpdateWindow(m_hWnd);
	::ShowWindow(m_hWnd, m_windowStatus == EWindowStatus::maxWindow ? SW_SHOWMAXIMIZED : SW_SHOW);

	return m_hWnd != NULL ? S_OK : S_FALSE;
}

int XApplication::Run()
{
	MSG msg;
	while (true)
	{
		if (0 == PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			OnFrame();
			Sleep(1);
		}
		else
		{
			if (WM_QUIT == msg.message)
			{
				break;
			}

			if (!TranslateAccelerator(m_hWnd, NULL, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	return Exit();
}

int XApplication::Exit()
{
	return 0;
}

LRESULT XApplication::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		OnClose();
		return TRUE;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return TRUE;
	}

	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

void XApplication::OnFrame()
{
}

HWND XApplication::CreateMainWindow(LPCTSTR className,
	LPCTSTR titleName,
	UINT width,
	UINT height,
	bool bFullScreen)
{
	//ASSERT(className != NULL && titleName != NULL);

	if (0 == RegisterWindowClass(className))
	{
		return NULL;
	}

	AdjustWindowInfo(width, height, m_windowStatus);
	m_windowStyle = GetWindowStyleByStatus(m_windowStatus);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = width;
	rect.bottom = height;
	AdjustWindowRect(&rect, m_windowStyle, false);	//调整窗口大小到真实分辨率大小
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	//居中
	{
		//获得屏幕尺寸
		// 		int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
		// 		int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);
		// 		rect.left = (screenWidth - width) >> 1;
		// 		rect.top = (screenHeight - height) >> 1;

		rect.top = 0;
		rect.left = 0;
	}

	return CreateWindowEx(0,
		className,
		titleName,
		m_windowStyle,
		rect.left,
		rect.top,
		width,
		height,
		NULL,
		NULL,
		m_hInstance,
		NULL);
}

ATOM XApplication::RegisterWindowClass(LPCTSTR className)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX),
	CS_DBLCLKS ,
	_MsgProc,
	0L,
	0L,
	m_hInstance,
	LoadIcon(m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME)),
	LoadCursor(NULL, IDC_ARROW),
	(HBRUSH)GetStockObject(BLACK_BRUSH), //NULL, //
	NULL,
	className,
	NULL };

	return RegisterClassEx(&wc);
}

bool XApplication::ResizeWindow(UINT width, UINT height, EWindowStatus status)
{
	return false;
}

DWORD XApplication::GetWindowStyleByStatus(EWindowStatus status)
{
	DWORD style = WS_OVERLAPPEDWINDOW;

	switch (status)
	{
	case EWindowStatus::fullWindow:
		style = WS_POPUP;
		break;
	case EWindowStatus::fullScreen:
		style = WS_POPUP |/*WS_SYSMENU|*/WS_VISIBLE;
		break;
	}

	return style;
}

HRESULT XApplication::AdjustWindowInfo(UINT &width, UINT &height, EWindowStatus status)
{
	//获取屏幕分辨率
	HWND hDesktop = ::GetDesktopWindow();
	RECT rcDesktop;
	::GetWindowRect(hDesktop, &rcDesktop);
	LONG desktopWidth = rcDesktop.right - rcDesktop.left;
	LONG desktopHeight = rcDesktop.bottom - rcDesktop.top;

	m_windowStatus = status;

	if (m_windowStatus == EWindowStatus::fullWindow || m_windowStatus == EWindowStatus::fullScreen)
	{//全屏
		width = desktopWidth;
		height = desktopHeight;
	}
	else
	{
		if (width >= desktopWidth && height >= desktopHeight)
		{
			m_windowStatus = EWindowStatus::maxWindow;
		}

		if (width > desktopWidth || 0 == width)
		{
			width = desktopWidth;
		}
		if (height > desktopHeight || 0 == height)
		{
			height = desktopHeight;
		}
	}

	return S_OK;
}

//处理退出游戏的消息
void XApplication::OnClose()
{
	ExitGame();
}
//请求退出游戏
void XApplication::ExitGame()
{
	::DestroyWindow(m_hWnd);
}