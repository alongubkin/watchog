#include "Exceptions.h"
#include "Config.h"
#include "LockedMutex.h"
#include "IPCPeer.h"

IPCPeer::IPCPeer() :
	_mutex(std::make_shared<Mutex>(Config::MUTEX_NAME())),
	_shared_memory(std::make_shared<SharedMemory>(Config::SHARED_MEMORY_NAME(), 
												  SharedMemoryAccess::ReadWrite, 
		                                          Config::SHARED_MEMORY_SIZE))
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

void IPCPeer::set_movie_state(const std::wstring& path, const MovieState state)
{
	LockedMutex lock(_mutex, Config::MUTEX_TIMEOUT());
	auto data = _shared_memory->get<MovieMetadataList>();

	// Try to find this movie path in the shared memory. If we can't find it,
	// we need to add a new record to the shared memory movies array.
	auto movie = get_movie_by_path(path);
	if (nullptr == movie)
	{
		// Make sure we are within the shared memory bounds
		if (MAXIMUM_MOVIE_COUNT < data->count + 1)
		{
			throw InsufficientSharedMemoryException();
		}

		movie = &data->movies[data->count];
		data->count++;

		// Copy path to the new record
		if (0 != wcscpy_s(movie->path, MAX_PATH, path.c_str()))
		{
			throw StringException();
		}
	}

	// Set the movie state
	movie->state = state;
}

MovieMetadata* IPCPeer::get_movie_by_path(const std::wstring& path)
{
	auto data = _shared_memory->get<MovieMetadataList>();
	for (uint32_t i = 0; i < data->count; i++)
	{
		if (0 == _wcsnicmp(path.c_str(), data->movies[i].path, MAX_PATH))
		{
			return &data->movies[i];
		}
	}

	return nullptr;
}
