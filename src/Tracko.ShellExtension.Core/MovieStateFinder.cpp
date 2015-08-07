#include <cstdint>
#include <algorithm>

#include "MovieStateFinder.h"

MovieStateFinder::MovieStateFinder() : 
	_shared_memory(L"TrackoSharedMemory", SharedMemoryAccess::Read)
{}

MovieState MovieStateFinder::get_movie_state(const std::wstring& path) const
{
	auto data = _shared_memory.get<MovieMetadataList>();
	for (uint32_t i = 0; i < data->count; i++)
	{
		if (0 == wcsncmp(path.c_str(), data->movies[i].path, MAX_PATH))
		{
			return data->movies[i].state;
		}
	}

	return MovieState::NotWatched;
}
