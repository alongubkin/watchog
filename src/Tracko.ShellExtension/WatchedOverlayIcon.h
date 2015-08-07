#pragma once

#include <cstdint>

#include "resource.h"
#include "TrackoShellExtension_i.h"

#include <shlobj.h>
#include <comdef.h>

#include "../Tracko.ShellExtension.Core/MovieStateFinder.h"

using namespace ATL;

class ATL_NO_VTABLE CWatchedOverlayIcon :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWatchedOverlayIcon, &CLSID_WatchedOverlayIcon>,
	public IShellIconOverlayIdentifier,
	public IDispatchImpl<IWatchedOverlayIcon, &IID_IWatchedOverlayIcon, &LIBID_TrackoShellExtensionLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
private:
	static const uint32_t MINIMUM_PATH_LENGTH = 2;

public:
	CWatchedOverlayIcon() = default;
	virtual ~CWatchedOverlayIcon() = default;
	CWatchedOverlayIcon(const CWatchedOverlayIcon&) = delete;
	CWatchedOverlayIcon& operator=(const CWatchedOverlayIcon&) = delete;

	DECLARE_REGISTRY_RESOURCEID(IDR_WATCHEDOVERLAYICON)

	BEGIN_COM_MAP(CWatchedOverlayIcon)
		COM_INTERFACE_ENTRY(IWatchedOverlayIcon)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IShellIconOverlayIdentifier)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	// IShellIconOverlayIdentifier::GetOverlayInfo
	// Returns the overlay icon location to the system.
	STDMETHOD(GetOverlayInfo)(
		PWSTR pwszIconFile, 
		int cchMax, 
		int* piIndex, 
		DWORD* pdwFlags
	);

	// IShellIconOverlayIdentifier::GetPriority
	// Returns the priority of this overlay 0 being the highest. 
	STDMETHOD(GetPriority)(
		int* piPriority
	);

	// IShellIconOverlayIdentifier::IsMemberOf
	// Returns whether the object should have this overlay or not.
	STDMETHOD(IsMemberOf)(
		PCWSTR pwszPath, 
		DWORD dwAttrib
	);

	HRESULT FinalConstruct() { return S_OK; }
	void FinalRelease() {}

private:
	MovieStateFinder _tFinder;
};

OBJECT_ENTRY_AUTO(__uuidof(WatchedOverlayIcon), CWatchedOverlayIcon)
