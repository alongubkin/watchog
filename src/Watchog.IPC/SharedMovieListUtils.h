#pragma once

#include "MappedViewOfFile.h"
#include "SharedMemoryStructs.h"

class SharedMovieListUtils final
{
public:
    SharedMovieListUtils() = delete;
    
    static SharedMovie* get_next_movie(const SharedMovie* movie);
    static bool is_valid_pointer(MappedViewOfFilePtr shared_memory, const SharedMovie* current_movie, const std::wstring& path);
};

