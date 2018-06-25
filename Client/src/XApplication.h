#pragma once

#include <wtypes.h>

#include "ApplicationParam.h"

class XApplication
{
public:
	XApplication();
	virtual ~XApplication();

public:
	virtual HINSTANCE GetInstance() const throw() { return m_hInstance; }
	virtual void SetInstance(HINSTANCE hInstance) { m_hInstance = hInstance; }
	virtual HWND GetWindow() const throw() { return m_hWnd; }
	virtual void SetWindow(HWND hWnd) { m_hWnd = hWnd; };

	virtual HRESULT InitApp(HINSTANCE hInst, SApplicationParam *param);
	virtual int Run();
	virtual int Exit();
	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual void OnFrame();

	//请求退出游戏
	virtual void ExitGame();

public:
	HRESULT AdjustWindowInfo(UINT &width, UINT &height, EWindowStatus status);
	DWORD GetWindowStyleByStatus(EWindowStatus status);
	virtual bool ResizeWindow(UINT width, UINT height, EWindowStatus status);

	EWindowStatus GetWindowStatus() const { return m_windowStatus; }

protected:
	HWND CreateMainWindow(LPCTSTR className,
		LPCTSTR titleName,
		UINT width,
		UINT height,
		bool bFullScreen);

	ATOM RegisterWindowClass(LPCTSTR className);

	//处理WM_CLOSE消息
	virtual void OnClose();

protected:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	DWORD m_windowStyle;
	EWindowStatus m_windowStatus;
};
