
#include "stdafx.h"

#include "XClientApplication.h"

int GameMain(HINSTANCE hInstance, HINSTANCE, LPTSTR lpCmdLine, int)
{
	UINT ret = S_OK;

	SApplicationParam appParam = { _T("XGameClient"), _T("XGame"), 1024, 768, EWindowStatus::normalWindow};
	XClientApplication &app = GetApp();
	ret = app.InitApp(hInstance, &appParam);
	if (ret != S_OK)
	{
		return ret;
	}

	ret = app.Run();

	return ret;
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UINT ret = S_OK;

	GameMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	return S_OK;
}