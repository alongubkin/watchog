#pragma once

#include <string>

#include "SharedMemory.h"
#include "Models.h"
#include "Mutex.h"

class IPCPeer
{
public:
	IPCPeer();
	virtual ~IPCPeer() = default;
	IPCPeer(const IPCPeer&) = delete;
	IPCPeer& operator=(const IPCPeer&) = delete;

	const MovieState get_movie_state(const std::wstring& path);

protected:
	MovieMetadata* get_movie_by_path(const std::wstring& path);
	virtual SharedMemoryPtr get_shared_memory() = 0;

protected:
	MutexPtr _mutex;
};

