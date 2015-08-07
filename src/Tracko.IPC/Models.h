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
struct MovieMetadata
{
    wchar_t path[MAX_PATH + 1];
    MovieState state;
};

struct MovieMetadataList
{
    uint32_t count;
    MovieMetadata movies[ANYSIZE_ARRAY];
};
#pragma pack(pop)