#pragma once

#include <string>
#include <cstdint>
#include <chrono>

namespace ipc
{
    /// <summary>
    /// Hard-coded configuration for the IPC.
    /// </summary>
    class Config final
    {
    public:
        Config() = delete;

        static const std::wstring SHARED_MEMORY_NAME() { return L"WatchogSharedMemory"; }
        static const uint64_t SHARED_MEMORY_SIZE = 512 * 1024;

        static const std::wstring MUTEX_NAME() { return L"WatchogMutex"; }
        static const std::chrono::seconds MUTEX_TIMEOUT() { return std::chrono::seconds(10); }
    };
}