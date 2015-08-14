#pragma once

#include <cstdint>
#include <Windows.h>

enum class MovieState : uint32_t
{
    Unknown = 0,
    NotWatched = 1,
    Watched = 2,
    InProgress = 3
};

#pragma pack(push)
#pragma pack(1)
struct SharedMovie
{
    MovieState state;
    wchar_t path[ANYSIZE_ARRAY];
};

struct SharedMovieList
{
    uint32_t count;
    uint32_t version;
    SharedMovie movies[ANYSIZE_ARRAY];
};
#pragma pack(pop)