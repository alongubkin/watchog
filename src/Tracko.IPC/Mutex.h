#pragma once

#include <string>
#include <memory>

#include <Windows.h>
#include "AutoCloseHandle.h"

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