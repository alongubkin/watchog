// dllmain.h : Declaration of module class.

class CTrackoShellExtensionModule : public ATL::CAtlDllModuleT< CTrackoShellExtensionModule >
{
public :
    DECLARE_LIBID(LIBID_TrackoShellExtensionLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TRACKOSHELLEXTENSION, "{98228592-8D1E-42C6-8FD7-9CFCC8F2D0CB}")
};

extern class CTrackoShellExtensionModule _AtlModule;
