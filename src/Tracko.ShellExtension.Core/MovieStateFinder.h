#pragma once

#include <string>

#include "Models.h"
#include "SharedMemory.h"

class MovieStateFinder
{
public:
	MovieStateFinder();
	virtual ~MovieStateFinder() = default;
	MovieStateFinder(const MovieStateFinder&) = delete;
	MovieStateFinder& operator=(const MovieStateFinder&) = delete;

	MovieState get_movie_state(const std::wstring& path) const;

private:
	SharedMemory _shared_memory;
};

