#pragma once

#include <chrono>
#include "Mutex.h"

namespace ipc
{
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