#pragma once

#include <Windows.h>

namespace ipc
{
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