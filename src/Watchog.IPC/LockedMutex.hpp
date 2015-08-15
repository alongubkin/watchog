#pragma once

#include <chrono>
#include "Mutex.hpp"

namespace ipc
{    
    /// <summary>
    /// Locks a <see cref="Mutex"/>. The mutex is unlocked when this object is
    /// destructed.
    /// </summary>
    class LockedMutex final
    {
    public:
        LockedMutex(MutexPtr mutex, const std::chrono::milliseconds timeout);
        virtual ~LockedMutex();
        LockedMutex(const LockedMutex&) = delete;
        LockedMutex& operator=(const LockedMutex&) = delete;

    private:
        MutexPtr _mutex;
    };
}