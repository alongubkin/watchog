#pragma once

#include <Windows.h>

namespace ipc
{        
    /// <summary>
    /// Abstract class for managing most Windows objects. The handle is closed
    /// when the object is destructed.
    /// </summary>
    class AutoCloseHandle
    {
    public:
        AutoCloseHandle(HANDLE handle);
        virtual ~AutoCloseHandle();
        AutoCloseHandle(const AutoCloseHandle&) = delete;
        AutoCloseHandle& operator=(const AutoCloseHandle&) = delete;

        const HANDLE native_handle() const { return _handle; }

    private:
        HANDLE _handle;
    };
}