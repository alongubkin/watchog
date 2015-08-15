// dllmain.h : Declaration of module class.

class CWatchogShellExtensionModule : public ATL::CAtlDllModuleT< CWatchogShellExtensionModule >
{
public :
    DECLARE_LIBID(LIBID_WatchogShellExtensionLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_WATCHOGSHELLEXTENSION, "{98228592-8D1E-42C6-8FD7-9CFCC8F2D0CB}")
};

extern class CWatchogShellExtensionModule _AtlModule;
