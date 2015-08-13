#include "AutoCloseHandle.h"

AutoCloseHandle::AutoCloseHandle(HANDLE handle) :
    _handle(handle)
{}

AutoCloseHandle::~AutoCloseHandle()
{
    try
    {
        if (!CloseHandle(_handle))
        {
            // TODO: Log
        }
    }
    catch (...)
    {
        // TODO: Log
    }
}
