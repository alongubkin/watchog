#pragma once

#include "MappedViewOfFile.hpp"
#include "SharedMemoryStructs.hpp"

namespace ipc
{    
    /// <summary>
    /// Provides utilities for dealing with the global movies shared buffer.
    /// </summary>
    // TODO: Replace this with SharedMovieIterator.
    class SharedMovieListUtils final
    {
    public:
        SharedMovieListUtils() = delete;

        static SharedMovie* get_next_movie(const SharedMovie* movie);
        static bool is_valid_pointer(MappedViewOfFilePtr shared_memory, const SharedMovie* current_movie, const std::wstring& path);
    };
}