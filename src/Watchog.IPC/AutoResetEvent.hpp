#pragma once

#include <string>
#include <memory>

#include <Windows.h>

#include "AutoCloseHandle.hpp"

namespace ipc
{
    class AutoResetEvent : public AutoCloseHandle
    {
    public:
        AutoResetEvent(const std::wstring& name, bool initial_state);
        virtual ~AutoResetEvent() = default;
        AutoResetEvent(const AutoResetEvent&) = delete;
        AutoResetEvent& operator=(const AutoResetEvent&) = delete;

        void set();

    private:
        static HANDLE create_event(const std::wstring& name, bool initial_state);
    };

    using AutoResetEventPtr = std::shared_ptr<AutoResetEvent>;
}