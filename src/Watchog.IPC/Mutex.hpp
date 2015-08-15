#pragma once

#include <string>
#include <memory>

#include <Windows.h>
#include "AutoCloseHandle.hpp"

namespace ipc
{    
    /// <summary>
    /// Mutex synchronization object that can be shared between processes.
    /// To lock the mutex, use <see cref="LockedMutex"/>.
    /// </summary>
    class Mutex final : public AutoCloseHandle
    {
    public:
        Mutex(const std::wstring& name);
        virtual ~Mutex() = default;
        Mutex(const Mutex&) = delete;
        Mutex& operator=(const Mutex&) = delete;

    private:
        static HANDLE create_mutex(const std::wstring& name);
    };

    using MutexPtr = std::shared_ptr<Mutex>;
}