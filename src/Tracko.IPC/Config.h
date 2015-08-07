#pragma once

#include <string>
#include <cstdint>
#include <chrono>

class Config final
{
public:
	Config() = delete;

	static const std::wstring SHARED_MEMORY_NAME() { return L"TrackoSharedMemory"; }
	static const uint64_t SHARED_MEMORY_SIZE = 512 * 1024;

	static const std::wstring MUTEX_NAME() { return L"TrackoMutex"; }
	static const std::chrono::seconds MUTEX_TIMEOUT() { return std::chrono::seconds(10); }
};