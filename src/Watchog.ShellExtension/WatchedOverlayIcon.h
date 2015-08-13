#pragma once

#include <cstdint>
#include <vector>

#include "resource.h"
#include "WatchogShellExtension_i.h"

#include <shlobj.h>
#include <comdef.h>

#include "../Watchog.IPC/IPCPeer.h"

using namespace ATL;

class ATL_NO_VTABLE CWatchedOverlayIcon :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CWatchedOverlayIcon, &CLSID_WatchedOverlayIcon>,
    public IShellExtInit,
    public IShellIconOverlayIdentifier,
    public IContextMenu
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
        COM_INTERFACE_ENTRY(IShellExtInit)
        COM_INTERFACE_ENTRY(IShellIconOverlayIdentifier)
        COM_INTERFACE_ENTRY(IContextMenu)
    END_COM_MAP()

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    // IShellExtInit::Initialize
    // Initializes context menu for a file.
    STDMETHOD(Initialize)(
        LPCITEMIDLIST pidlFolder,
        LPDATAOBJECT ptDataObject,
        HKEY hProgID
    ) override;

    // IShellIconOverlayIdentifier::GetOverlayInfo
    // Returns the overlay icon location to the system.
    STDMETHOD(GetOverlayInfo)(
        PWSTR pwszIconFile, 
        int cchMax, 
        int* piIndex, 
        DWORD* pdwFlags
    ) override;

    // IShellIconOverlayIdentifier::GetPriority
    // Returns the priority of this overlay 0 being the highest. 
    STDMETHOD(GetPriority)(
        int* piPriority
    ) override;

    // IShellIconOverlayIdentifier::IsMemberOf
    // Returns whether the object should have this overlay or not.
    STDMETHOD(IsMemberOf)(
        PCWSTR pwszPath, 
        DWORD dwAttrib
    ) override;

    // IContextMenu::QueryContextMenu
    // Adds commands to a shortcut menu.
    STDMETHOD(QueryContextMenu)(
        HMENU hMenu, 
        UINT uMenuIndex, 
        UINT uidFirstCmd, 
        UINT uidLastCmd, 
        UINT uFlags
    ) override;

    // IContextMenu::GetCommandString
    // Gets information about a shortcut menu command, including the help string
    // and the name for the command.
    STDMETHOD(GetCommandString)(
        UINT_PTR idCmd, 
        UINT uFlags, 
        UINT* pwReserved,
        PSTR pszName, 
        UINT cchMax
    ) override;

    // IContextMenu::InvokeCommand
    // Called when the user clicks on the context menu item.
    STDMETHOD(InvokeCommand)(
        LPCMINVOKECOMMANDINFO ptCmdInfo
    ) override;

    HRESULT FinalConstruct() { return S_OK; }
    void FinalRelease() {}

private:
    IPCPeer _tIPC;
    std::vector<std::wstring> _tSelectedFiles;
};

OBJECT_ENTRY_AUTO(__uuidof(WatchedOverlayIcon), CWatchedOverlayIcon)
