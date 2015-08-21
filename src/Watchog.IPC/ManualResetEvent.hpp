#pragma once

#include <string>
#include <memory>

#include <Windows.h>

#include "AutoCloseHandle.hpp"

namespace ipc
{
    class ManualResetEvent : public AutoCloseHandle
    {
    public:
        ManualResetEvent(const std::wstring& name, bool initial_state);
        virtual ~ManualResetEvent() = default;
        ManualResetEvent(const ManualResetEvent&) = delete;
        ManualResetEvent& operator=(const ManualResetEvent&) = delete;

        void set();

    private:
        static HANDLE create_event(const std::wstring& name, bool initial_state);
    };

    using AutoResetEventPtr = std::shared_ptr<ManualResetEvent>;
}