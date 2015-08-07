#pragma once

#include <string>

#include "Config.h"
#include "SharedMemory.h"
#include "Models.h"
#include "Mutex.h"

class IPCPeer final
{
private:
    static const uint32_t MAXIMUM_MOVIE_COUNT = (Config::SHARED_MEMORY_SIZE - sizeof(MovieListModel)) / sizeof(MovieModel) - 1;

public:
    IPCPeer();
    virtual ~IPCPeer() = default;
    IPCPeer(const IPCPeer&) = delete;
    IPCPeer& operator=(const IPCPeer&) = delete;

    const MovieState get_movie_state(const std::wstring& path);
    void set_movie_state(const std::wstring& path, const MovieState state);

private:
    MovieModel* get_movie_by_path(const std::wstring& path);
    
private:
    MutexPtr _mutex;
    SharedMemoryPtr _shared_memory;
};

