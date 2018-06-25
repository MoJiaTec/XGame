
#include "XClientApplication.h"

XClientApplication &GetApp()
{
	static XClientApplication app;
	return app;
}