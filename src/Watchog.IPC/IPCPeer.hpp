#pragma once

#include <string>

#include "Config.hpp"
#include "MappedViewOfFile.hpp"
#include "Mutex.hpp"
#include "AutoResetEvent.hpp"
#include "MovieList.hpp"
#include "SharedMemoryStructs.hpp"

namespace ipc
{    
    /// <summary>
    /// Maps the global movies shared buffer to the current process and provides
    /// methods for observing and manipulating it.
    /// </summary>
    class IPCPeer final
    {
    public:
        IPCPeer();
        virtual ~IPCPeer() = default;
        IPCPeer(const IPCPeer&) = delete;
        IPCPeer& operator=(const IPCPeer&) = delete;

        const MovieState get_movie_state(const std::wstring& path);
        void set_movie_state(const std::wstring& path, const MovieState state);

        MovieListPtr get_all();
        void reset(const MovieList& movies);

    private:
        SharedMovie* get_movie_by_path(const std::wstring& path);

    private:
        MutexPtr _mutex;
        FileMappingPtr _file_mapping;
        MappedViewOfFilePtr _shared_memory;
        AutoResetEvent _change_event;
    };
}