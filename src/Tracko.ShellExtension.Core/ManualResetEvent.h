#pragma once

#include <chrono>

#include <Windows.h>
#include "AutoCloseHandle.h"

class ManualResetEvent final : public AutoCloseHandle
{
public:
	ManualResetEvent();
	virtual ~ManualResetEvent() = default;
	ManualResetEvent(const ManualResetEvent&) = delete;
	ManualResetEvent& operator=(const ManualResetEvent&) = delete;

	void wait(const std::chrono::milliseconds& timeout) const;

private:
	static HANDLE create_event();
};