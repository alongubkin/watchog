#include "Exceptions.h"
#include "Mutex.h"

Mutex::Mutex(const std::wstring& name) :
    AutoCloseHandle(create_mutex(name))
{}

HANDLE Mutex::create_mutex(const std::wstring& name)
{
    static const PSECURITY_ATTRIBUTES DEFAULT_SECURITY = nullptr;
    static const bool NOT_INITIAL_OWNER = false;

    HANDLE handle = CreateMutexW(DEFAULT_SECURITY, NOT_INITIAL_OWNER, name.c_str());
    if (nullptr == handle)
    {
        throw WindowsException(GetLastError());
    }

    return handle;
}