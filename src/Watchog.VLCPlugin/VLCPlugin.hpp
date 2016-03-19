#pragma once

#include "vlc_includes.h"
#include "../Watchog.IPC/PluginState.hpp"

struct intf_sys_t
{
    PluginState state;
    void* input;
};

static
int
OnPlayingItemUpdated(
    vlc_object_t* plugin,
    const char* variable,
    vlc_value_t old_value,
    vlc_value_t new_value,
    void* data
);

static
int
OnPlayingItemChanged(
    vlc_object_t* plugin,
    const char* variable,
    vlc_value_t old_value,
    vlc_value_t new_value,
    void* data
);

static
int
OnPluginStart(
    vlc_object_t* plugin
);

static
void
OnPluginEnd(
    vlc_object_t* plugin
);

static inline uint64_t from_mtime(mtime_t time)
{
    return (time + 500ULL) / 1000ULL;
}

vlc_module_begin()
    set_shortname("Watchog")
    set_description("Watchog")
    set_category(CAT_INTERFACE)
    set_subcategory(SUBCAT_INTERFACE_CONTROL)
    set_capability("interface", 0)
    set_callbacks(OnPluginStart, OnPluginEnd)
vlc_module_end()