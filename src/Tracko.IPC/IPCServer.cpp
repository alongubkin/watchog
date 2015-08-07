#include "Config.h"
#include "Exceptions.h"
#include "LockedMutex.h"
#include "IPCServer.h"

IPCServer::IPCServer() :
	_shared_memory(std::make_shared<SharedMemory>(
		Config::SHARED_MEMORY_NAME(), SharedMemoryAccess::ReadWrite, Config::SHARED_MEMORY_SIZE))
{}

SharedMemoryPtr IPCServer::get_shared_memory()
{
	return _shared_memory;
}

void IPCServer::set_movie_state(const std::wstring& path, const MovieState state)
{
	LockedMutex lock(_mutex, Config::MUTEX_TIMEOUT());
	auto data = get_shared_memory()->get<MovieMetadataList>();
	
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
		if (0 != wcscpy_s(movie->path, sizeof(movie->path), path.c_str()))
		{
			throw StringException();
		}
	}

	// Set the movie state
	movie->state = state;
}
