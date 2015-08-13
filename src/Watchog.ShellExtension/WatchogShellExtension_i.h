

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Aug 07 22:23:06 2015
 */
/* Compiler settings for WatchogShellExtension.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __WatchogShellExtension_i_h__
#define __WatchogShellExtension_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWatchedOverlayIcon_FWD_DEFINED__
#define __IWatchedOverlayIcon_FWD_DEFINED__
typedef interface IWatchedOverlayIcon IWatchedOverlayIcon;

#endif     /* __IWatchedOverlayIcon_FWD_DEFINED__ */


#ifndef __WatchedOverlayIcon_FWD_DEFINED__
#define __WatchedOverlayIcon_FWD_DEFINED__

#ifdef __cplusplus
typedef class WatchedOverlayIcon WatchedOverlayIcon;
#else
typedef struct WatchedOverlayIcon WatchedOverlayIcon;
#endif /* __cplusplus */

#endif     /* __WatchedOverlayIcon_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IWatchedOverlayIcon_INTERFACE_DEFINED__
#define __IWatchedOverlayIcon_INTERFACE_DEFINED__

/* interface IWatchedOverlayIcon */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWatchedOverlayIcon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6248DA0B-EF81-443B-98E3-73A1F673C57A")
    IWatchedOverlayIcon : public IDispatch
    {
    public:
    };
    
    
#else     /* C style interface */

    typedef struct IWatchedOverlayIconVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWatchedOverlayIcon * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWatchedOverlayIcon * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWatchedOverlayIcon * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWatchedOverlayIcon * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWatchedOverlayIcon * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWatchedOverlayIcon * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWatchedOverlayIcon * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IWatchedOverlayIconVtbl;

    interface IWatchedOverlayIcon
    {
        CONST_VTBL struct IWatchedOverlayIconVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWatchedOverlayIcon_QueryInterface(This,riid,ppvObject)    \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWatchedOverlayIcon_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWatchedOverlayIcon_Release(This)    \
    ( (This)->lpVtbl -> Release(This) ) 


#define IWatchedOverlayIcon_GetTypeInfoCount(This,pctinfo)    \
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWatchedOverlayIcon_GetTypeInfo(This,iTInfo,lcid,ppTInfo)    \
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWatchedOverlayIcon_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)    \
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWatchedOverlayIcon_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)    \
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif     /* C style interface */




#endif     /* __IWatchedOverlayIcon_INTERFACE_DEFINED__ */



#ifndef __WatchogShellExtensionLib_LIBRARY_DEFINED__
#define __WatchogShellExtensionLib_LIBRARY_DEFINED__

/* library WatchogShellExtensionLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_WatchogShellExtensionLib;

EXTERN_C const CLSID CLSID_WatchedOverlayIcon;

#ifdef __cplusplus

class DECLSPEC_UUID("D729C131-4A94-4A95-B3EE-361E37BA30BE")
WatchedOverlayIcon;
#endif
#endif /* __WatchogShellExtensionLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


