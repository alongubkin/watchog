#define __PLUGIN__
#define MODULE_STRING "tracko"

#define ssize_t SSIZE_T
#define LIBVLC_USE_PTHREAD_CANCEL 1

#include <cstdlib>

#include <vlc_common.h>
#include <vlc_plugin.h>
#include <vlc_variables.h>
#include "vlc_interface.h"

static int Open(vlc_object_t * l);
static void Close(vlc_object_t * l);

vlc_module_begin()
    set_shortname("tracko")
    set_description("tracko")
    set_category(CAT_INTERFACE)
    set_subcategory(SUBCAT_INTERFACE_CONTROL)
    set_capability("interface", 0)
    set_callbacks(Open, Close)

    
vlc_module_end()

struct intf_sys_t
{
};

static int ItemChange(vlc_object_t *p_this, const char *psz_var,
    vlc_value_t oldval, vlc_value_t newval, void *param)
{
    return VLC_SUCCESS;
}

static int Open(vlc_object_t* p_this)
{
    intf_thread_t * p_intf = (intf_thread_t *) p_this;
    intf_sys_t * p_sys = (intf_sys_t *) malloc(sizeof(*p_sys));
    if (!p_sys)
    {
        return VLC_ENOMEM;
    }

    p_intf->p_sys = p_sys;

    var_AddCallback(pl_Get(p_intf), "input-current", ItemChange, p_intf);
    return VLC_SUCCESS;
}

static void Close(vlc_object_t * l)
{
    MessageBoxW(NULL, L"Close", NULL, MB_OK);
}
