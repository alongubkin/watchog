#include "Exceptions.hpp"
#include "AutoResetEvent.hpp"

namespace ipc
{
    AutoResetEvent::AutoResetEvent(const std::wstring& name, bool initial_state) :
        AutoCloseHandle(create_event(name, initial_state))
    {}

    HANDLE AutoResetEvent::create_event(const std::wstring& name, bool initial_state)
    {
        static const PSECURITY_ATTRIBUTES DEFAULT_SECURITY = nullptr;
        static const bool AUTO_RESET_EVENT = false;

        HANDLE event = CreateEventW(DEFAULT_SECURITY, 
                                    AUTO_RESET_EVENT, 
                                    initial_state, 
                                    name.c_str());
        if (nullptr == event)
        {
            throw WindowsException(GetLastError());
        }

        return event;
    }

    void AutoResetEvent::set()
    {
        if (!SetEvent(native_handle()))
        {
            throw WindowsException(GetLastError());
        }
    }
}