#include <Shlobj.h>
#include "PluginState.hpp"

namespace ipc
{

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

	void PluginState::set_movie_length(const uint64_t length)
	{
		_movie_length = length;
	}

	void PluginState::mark_as_watched()
	{
		if (MovieState::Watched == _current_movie_state)
		{
			return;
		}

		_peer.set_movie_state(_current_file_path, MovieState::Watched);
		_current_movie_state = MovieState::Watched;

		// Refresh file
		SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATHW | SHCNF_FLUSHNOWAIT, _current_file_path.c_str(), nullptr);
	}

}