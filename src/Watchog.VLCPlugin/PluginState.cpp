#include <Shlobj.h>
#include "PluginState.hpp"

PluginState::PluginState()
{}

void PluginState::set_current_file(const std::wstring& path)
{
    _current_file_path = path;
    _current_movie_state = _peer.get_movie_state(path);
}

void PluginState::set_current_length(const uint64_t length)
{
    _current_length = length;
}

void PluginState::mark_as_watched()
{   
    if (ipc::MovieState::Watched == _current_movie_state)
    {
        return;
    }

    _peer.set_movie_state(_current_file_path, ipc::MovieState::Watched);
    _current_movie_state = ipc::MovieState::Watched;

    // Refresh file
    SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATH, _current_file_path.c_str(), nullptr);
}