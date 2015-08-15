#pragma once

namespace Watchog
{
    namespace IPC
    {
        // This must match to MovieState in SharedMemoryStructs.hpp!
        public enum class MovieState
        {
            Unknown = 0,
            NotWatched = 1,
            Watched = 2,
            InProgress = 3
        };
    }
}