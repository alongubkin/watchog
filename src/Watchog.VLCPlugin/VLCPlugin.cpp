#include <cstdint>
#include <string>
#include <codecvt>
#include <memory>
#include <vector>
#include <algorithm>

#include <Windows.h>
#include "VLCPlugin.h"

static 
int 
OnPlayingItemUpdated(
    vlc_object_t* plugin, 
    const char* variable,
    vlc_value_t old_value, 
    vlc_value_t new_value, 
    void* data
)
{
    intf_thread_t* plugin_interface = (intf_thread_t*)data;

    if (strcmp(variable, "intf-event") != 0)
    {
        return VLC_SUCCESS;
    }

    input_thread_t* input = (input_thread_t*) plugin;
    uint64_t time_left_in_seconds = 0;

    switch (new_value.i_int)
    {
    case INPUT_EVENT_POSITION:
        time_left_in_seconds = (plugin_interface->p_sys->state.get_current_length()
            - from_mtime(var_GetTime(input, "time"))) / 1000;

        // If there are less than 30 seconds to the movie, mark it
        // as watched.
        if (30 > time_left_in_seconds)
        {
            plugin_interface->p_sys->state.mark_as_watched();
        }

        break;

    case INPUT_EVENT_LENGTH:
        plugin_interface->p_sys->state.set_current_length(
            from_mtime(var_GetTime(input, "length")));
        break;
    }
    
    return VLC_SUCCESS;
}

static 
int 
OnPlayingItemChanged(
    vlc_object_t* plugin, 
    const char* variable,
    vlc_value_t old_value, 
    vlc_value_t new_value, 
    void* data
)
{
    intf_thread_t* plugin_interface = (intf_thread_t*) data;
    
    input_thread_t* input = (input_thread_t*) new_value.p_address;
    if (nullptr == input)
    {
        return VLC_SUCCESS;
    }
    
    if (nullptr != plugin_interface->p_sys->input)
    {
        var_DelCallback(plugin_interface->p_sys->input, "intf-event", OnPlayingItemUpdated, plugin_interface);
        vlc_object_release(plugin_interface->p_sys->input);
        plugin_interface->p_sys->input = nullptr;
    }
    
    input_item_t* item = input_GetItem(input);
    if (nullptr == item)
    {
        return VLC_SUCCESS;
    }
    
    // Calculate URI length
    uint32_t uri_length = static_cast<uint32_t>(strlen(item->psz_uri)) + 1;

    // Create buffer of the file URL
    std::vector<char> buffer(item->psz_uri, item->psz_uri + strlen(item->psz_uri) + 1);
    
    // Decode the URL buffer
    if (nullptr == decode_URI(buffer.data()))
    {
        return VLC_SUCCESS;
    }
    
    // Convert the buffer to Unicode
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> string_converter;
    std::wstring unicode_uri = string_converter.from_bytes(buffer.data());
    
    // Make sure this is a file URI
    std::wstring protocol = L"file://";
    if (0 != unicode_uri.compare(0, protocol.size(), protocol))
    {
        return VLC_SUCCESS;
    }

    // Convert the URI to a file path
    std::wstring file_path = unicode_uri.substr(protocol.size() + 1);
    std::replace(file_path.begin(), file_path.end(), L'/', L'\\');

    plugin_interface->p_sys->state.set_current_file(file_path);

    plugin_interface->p_sys->input = vlc_object_hold(input);
    var_AddCallback(input, "intf-event", OnPlayingItemUpdated, plugin_interface);

    return VLC_SUCCESS;
}

static 
int 
OnPluginStart(
    vlc_object_t* plugin
)
{
    // Validate arguments
    if (nullptr == plugin)
    {
        return VLC_EGENERIC;
    }
   
    // Find correct interface and create a new state
    intf_thread_t *plugin_interface = reinterpret_cast<intf_thread_t*>(plugin);
    plugin_interface->p_sys = new intf_sys_t();

    // Add callback for current playing file changed
    var_AddCallback(pl_Get(plugin_interface), "input-current", OnPlayingItemChanged, plugin_interface);

    return VLC_SUCCESS;
}

static 
void 
OnPluginEnd(
    vlc_object_t* plugin
)
{
    // Validate arguments
    if (nullptr == plugin)
    {
        return;
    }

    intf_thread_t* plugin_interface = reinterpret_cast<intf_thread_t*>(plugin);
    
    var_DelCallback(pl_Get(plugin_interface), "input-current", OnPlayingItemChanged, plugin_interface);
    
    if (nullptr != plugin_interface->p_sys->input)
    {
        var_DelCallback(plugin_interface->p_sys->input, "intf-event", OnPlayingItemUpdated, plugin_interface);
        vlc_object_release(plugin_interface->p_sys->input);
        plugin_interface->p_sys->input = nullptr;
    }

    delete plugin_interface->p_sys;
}