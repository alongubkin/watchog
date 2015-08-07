#include "Config.h"
#include "LockedMutex.h"
#include "IPCPeer.h"

IPCPeer::IPCPeer() :
	_mutex(std::make_shared<Mutex>(Config::MUTEX_NAME()))
{}

const MovieState IPCPeer::get_movie_state(const std::wstring& path)
{	
	LockedMutex lock(_mutex, Config::MUTEX_TIMEOUT());

	auto movie = get_movie_by_path(path);
	if (nullptr == movie)
	{
		return MovieState::Unknown;
	}

	return movie->state;
}

MovieMetadata* IPCPeer::get_movie_by_path(const std::wstring& path)
{
	auto data = get_shared_memory()->get<MovieMetadataList>();
	for (uint32_t i = 0; i < data->count; i++)
	{
		if (0 == _wcsnicmp(path.c_str(), data->movies[i].path, MAX_PATH))
		{
			return &data->movies[i];
		}
	}

	return nullptr;
}
