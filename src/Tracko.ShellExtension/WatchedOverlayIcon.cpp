#include "stdafx.h"
#include "WatchedOverlayIcon.h"

using AutoGlobalUnlock = std::unique_ptr<std::remove_pointer<HDROP>::type, decltype(&GlobalUnlock)>;
using AutoReleaseStg = std::unique_ptr<STGMEDIUM, decltype(&ReleaseStgMedium)>;

// IShellExtInit::Initialize
// Initializes context menu for a file.
STDMETHODIMP
CWatchedOverlayIcon::Initialize(
    LPCITEMIDLIST pidlFolder,
    LPDATAOBJECT ptDataObject,
    HKEY hProgID
)
{
    try
    {
        // Validate arguments
        if (nullptr == ptDataObject)
        {
            return E_INVALIDARG;
        }

        FORMATETC tFormat = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
        STGMEDIUM tStg = { TYMED_HGLOBAL };

        // Look for CF_HDROP data in the data object. If there
        // is no such data, return an error back to Explorer.
        if (FAILED(ptDataObject->GetData(&tFormat, &tStg)))
        {
            return E_INVALIDARG;
        }

        AutoReleaseStg ptStg(&tStg, ReleaseStgMedium);
        
        // Get a pointer to the actual data.
        AutoGlobalUnlock phDrop((HDROP) GlobalLock(tStg.hGlobal), GlobalUnlock);
        if (nullptr == phDrop)
        {
            return E_INVALIDARG;
        }

        // Find count of selected files
        UINT nFiles = DragQueryFileW(phDrop.get(), 0xFFFFFFFF, NULL, 0);
        if (0 == nFiles)
        {
            return E_INVALIDARG;
        }

        _tSelectedFiles.clear();

        // Add selected files to the list
        WCHAR wszFileName[MAX_PATH] = {0};
        for (UINT nFile = 0; nFile < nFiles; nFile++)
        {
            if (0 == DragQueryFileW(phDrop.get(), nFile, wszFileName, MAX_PATH))
            {
                return E_INVALIDARG;
            }

            _tSelectedFiles.push_back(std::wstring(wszFileName));
        }

        return S_OK;
    }
    catch (...)
    {
        return E_FAIL;
    }
}

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

// IContextMenu::QueryContextMenu
// Adds commands to a shortcut menu.
STDMETHODIMP
CWatchedOverlayIcon::QueryContextMenu(
    HMENU hMenu, 
    UINT uMenuIndex, 
    UINT uidFirstCmd, 
    UINT uidLastCmd, 
    UINT uFlags
)
{
    try
    { 
        // Validate arguments
        if (nullptr == hMenu)
        {
            return E_INVALIDARG;
        }

        // If the flags include CMF_DEFAULTONLY then we shouldn't do anything.
        if (uFlags & CMF_DEFAULTONLY)
        {
            return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
        }

        // Make sure that all selected items are in the same state
        MovieState eState = MovieState::Unknown;
        for (const auto& tPath : _tSelectedFiles)
        {
            if (MovieState::Watched == _tIPC.get_movie_state(tPath))
            {
                // The current file is watched. If the previous file wasn't watched,
                // and this isn't the first file, then don't add a context menu item.
                if ((MovieState::Watched != eState) &&
                    (MovieState::Unknown != eState))
                {
                    return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
                }

                eState = MovieState::Watched;
            }
            else
            {
                // The current file isn't watched. If the previous file was watched,
                // then don't add a context menu item.
                if (MovieState::Watched == eState)
                {
                    return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
                }

                eState = MovieState::NotWatched;
            }
        }

        if (MovieState::Watched == eState)
        {
            InsertMenuW(hMenu, uMenuIndex, MF_BYPOSITION, uidFirstCmd, L"Mark as Unwatched");
        }
        else
        {
            InsertMenuW(hMenu, uMenuIndex, MF_BYPOSITION, uidFirstCmd, L"Mark as Watched");
        }
        
        return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 1);
    }
    catch (...)
    {
        return E_FAIL;
    }
}

// IContextMenu::GetCommandString
// Gets information about a shortcut menu command, including the help string
// and the name for the command.
STDMETHODIMP
CWatchedOverlayIcon::GetCommandString(
    UINT_PTR idCmd,
    UINT uFlags, 
    UINT* pwReserved,
    PSTR pszName, 
    UINT cchMax
)
{
    try
    {
        // Check command ID, which must be 0 since we have only one menu item.
        if (0 != idCmd)
        {
            return E_INVALIDARG;
        }

        // If Explorer is asking for a help string, copy our string into the
        // supplied buffer.
        if (uFlags & GCS_HELPTEXT)
        {
            PCWSTR wszText = L"This is the simple shell extension's help";
            
            if (uFlags & GCS_UNICODE)
            {
                lstrcpynW((LPWSTR) pszName, wszText, cchMax);
            }
            else
            {
                USES_CONVERSION;
                lstrcpynA(pszName, W2CA(wszText), cchMax);
            }

            return S_OK;
        }

        return E_INVALIDARG;
    }
    catch (...)
    {
        return E_FAIL;
    }
}

// IContextMenu::InvokeCommand
// Called when the user clicks on the context menu item.
STDMETHODIMP
CWatchedOverlayIcon::InvokeCommand(
    LPCMINVOKECOMMANDINFO ptCmdInfo
)
{
    try 
    {
        // Validate arguments
        if (nullptr == ptCmdInfo)
        {
            return E_INVALIDARG;
        }

        // The command info's lpVerb property performs double duty:
        //   * it can be either the name of the verb that was invoked, or 
        //   * it can be an index telling us which of our menu items was clicked on. 
        // If lpVerb really points to a string, ignore this function call and bail out.
        if (0 != HIWORD(ptCmdInfo->lpVerb))
        {
            return E_INVALIDARG;
        }

        // Handle the command
        switch (LOWORD(ptCmdInfo->lpVerb))
        {
        case 0:
            // Loop all selected files. If the file was watched, then mark it was unwatched.
            // Otherwise, mark it as watched.
            for (const auto& tPath : _tSelectedFiles)
            {
                if (MovieState::Watched == _tIPC.get_movie_state(tPath))
                {
                    _tIPC.set_movie_state(tPath, MovieState::NotWatched);
                }
                else
                {
                    _tIPC.set_movie_state(tPath, MovieState::Watched);
                }
                
                // Refresh file
                SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATH, tPath.c_str(), NULL);
            }
            
            return S_OK;
        }
        
        return E_INVALIDARG;
    }
    catch (...)
    {
        return E_FAIL;
    }
}