// dllmain.cpp : Implementation of DllMain.

#include "stdafx.hpp"
#include "resource.h"
#include "WatchogShellExtension_i.h"
#include "dllmain.hpp"

CWatchogShellExtensionModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}
