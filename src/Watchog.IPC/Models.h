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
struct MovieModel
{
    MovieState state;
    wchar_t path[ANYSIZE_ARRAY];
};

struct MovieListModel
{
    uint32_t count;
    MovieModel movies[ANYSIZE_ARRAY];
};
#pragma pack(pop)