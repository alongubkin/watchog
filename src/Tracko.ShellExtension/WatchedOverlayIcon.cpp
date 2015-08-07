#include "stdafx.h"
#include "WatchedOverlayIcon.h"

// IShellIconOverlayIdentifier::GetOverlayInfo
// Returns the overlay icon location to the system.
STDMETHODIMP 
CWatchedOverlayIcon::GetOverlayInfo(
	PWSTR pwszIconFile, 
	int cchMax, 
	int* piIndex, 
	DWORD* pdwFlags
)
{
	try
	{
		// Validate arguments
		if ((nullptr == pwszIconFile) ||
			(nullptr == piIndex) ||
			(nullptr == pdwFlags))
		{
			return E_INVALIDARG;
		}

		// Get current module's full path
		if (0 == GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(),
			pwszIconFile,
			cchMax))
		{
			return E_FAIL;
		}

		// Use first icon in the resource
		*piIndex = 0;

		*pdwFlags = ISIOI_ICONFILE | ISIOI_ICONINDEX;
		return S_OK;
	}
	catch (...)
	{
		// TODO: Log
		return E_FAIL;
	}
}

// IShellIconOverlayIdentifier::GetPriority
// Returns the priority of this overlay 0 being the highest. 
STDMETHODIMP 
CWatchedOverlayIcon::GetPriority(
	int* piPriority
)
{
	try
	{
		// Validate arguments
		if (nullptr == piPriority)
		{
			return E_INVALIDARG;
		}

		// We want highest priority 
		*piPriority = 0;
		return S_OK;
	}
	catch (...)
	{
		return E_FAIL;
	}
}

// IShellIconOverlayIdentifier::IsMemberOf
// Returns whether the object should have this overlay or not.
STDMETHODIMP 
CWatchedOverlayIcon::IsMemberOf(
	PCWSTR pwszPath, 
	DWORD dwAttrib
)
{
	try
	{
		// Validate arguments
		if (nullptr == pwszPath)
		{
			return E_INVALIDARG;
		}

		std::wstring path(pwszPath);

		// The shell sometimes asks overlays for invalid paths, e.g. for network
		// printers (in that case the path can be something like "0").
		if (MINIMUM_PATH_LENGTH >= path.length())
		{
			return S_FALSE;
		}

		if (MovieState::Watched == _tIPC.get_movie_state(path))
		{
			return S_OK;
		}

		return S_FALSE;
	}
	catch (...)
	{
		return E_FAIL;
	}
}