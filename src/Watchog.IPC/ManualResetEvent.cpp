#include "Exceptions.hpp"
#include "ManualResetEvent.hpp"

namespace ipc
{
    ManualResetEvent::ManualResetEvent(const std::wstring& name, bool initial_state) :
        AutoCloseHandle(create_event(name, initial_state))
    {}

    HANDLE ManualResetEvent::create_event(const std::wstring& name, bool initial_state)
    {
        static const PSECURITY_ATTRIBUTES DEFAULT_SECURITY = nullptr;
        static const bool MANUAL_RESET_EVENT = true;

        HANDLE event = CreateEventW(DEFAULT_SECURITY, 
                                    MANUAL_RESET_EVENT,
                                    initial_state, 
                                    name.c_str());
        if (nullptr == event)
        {
            throw WindowsException(GetLastError());
        }

        return event;
    }

    void ManualResetEvent::set()
    {
        if (!SetEvent(native_handle()))
        {
            throw WindowsException(GetLastError());
        }
    }
}