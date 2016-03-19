#define  WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <strsafe.h>
#include <string>
#include <codecvt>
#include "BSPLugin.hpp"

PpluginInfo g_ptInfo;
ipc::PluginState g_state;

INT
__stdcall
CallbackProc(
	CONST DWORD dwCmdID, 
	PVOID pvParam1, 
	PVOID pvParam2
)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> string_converter;
	std::wstring file_path;
	LRESULT bs_result = 0;
	uint64_t time_left_in_seconds = 0;

	UNREFERENCED_PARAMETER(pvParam2);

	switch (dwCmdID)
	{
	case EV_ABOUT:
		(VOID)MessageBoxA((HWND)pvParam1, BSPLUGIN_ABOUT, BSPLUGIN_TITLE, MB_OK);
		break;

	// In case of new movie opened, initialize his data.
	case EV_FILE_OPEN:
		// Convert the buffer to Unicode
		file_path = string_converter.from_bytes((PSTR)pvParam1);
		// Get Movie length
		bs_result = SendMessage(g_ptInfo->hwndParent, WM_BSP_CMD, BSP_GetMovLen, 0);

		// Set file path and length
		g_state.set_current_file(file_path);
		g_state.set_movie_length(bs_result);

		// If movie already exist, seek to its last position.
		// TODO

		break;

	// In case we closed the movie, save last position and mark as watch if needed.
	case EV_STOP:
	case EV_FILE_CLOSE:
		// Get Movie current position.
		bs_result = SendMessage(g_ptInfo->hwndParent, WM_BSP_CMD, BSP_GetMovPos, 0);
		if (0 == bs_result) break;

		g_state.set_current_length(bs_result);
		// Calc time left
		time_left_in_seconds = (g_state.get_movie_length() - bs_result) / 1000;

		// TODO: Read user config of LEFT_TIME.

		// If there are less than LEFT_TIME_SEC seconds to the movie, mark it
		// as watched.
		if (LEFT_TIME_SEC > time_left_in_seconds)
		{
			g_state.mark_as_watched();
		}

		break;

	case EV_PLAYBACK_COMPLETE:
		g_state.mark_as_watched();
		break;
	}

	return 0;
}

#ifdef __cplusplus
extern "C" {
#endif

BOOL
APIENTRY
DllMain(
	HANDLE hModule,
	DWORD  dwReason,
	LPVOID lpReserved
	)
{
	UNREFERENCED_PARAMETER(hModule);
	UNREFERENCED_PARAMETER(dwReason);
	UNREFERENCED_PARAMETER(lpReserved);

	return TRUE;
}

//v2.11+
INT
__stdcall
pluginVersion()
{
	return BSP_PLUGIN_VER;
}

BOOL 
__stdcall 
pluginInit(
	PpluginInfo ptPlgInfo
)
{
	StringCchCopyA(ptPlgInfo->description, ARRAY_ENTIRES(ptPlgInfo->description), BSPLUGIN_TITLE);
	ptPlgInfo->plgCallback = CallbackProc;
	g_ptInfo = ptPlgInfo;

	return TRUE;
}

#ifdef __cplusplus
}
#endif