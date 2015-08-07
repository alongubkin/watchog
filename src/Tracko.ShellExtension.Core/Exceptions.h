#pragma once

#include <cstdint>
#include <stdexcept>

class WindowsException final : public std::exception
{
public:
	WindowsException(const uint32_t last_error) :
		std::exception(),
		_last_error(last_error)
	{}

	virtual ~WindowsException() = default;
	WindowsException(const WindowsException&) = default;
	WindowsException& operator=(const WindowsException&) = delete;

	const uint32_t get_last_error() { return _last_error; }

private:
	const uint32_t _last_error;
};

class TimeoutException final : public std::exception
{
public:
	TimeoutException() : std::exception()
	{}
	virtual ~TimeoutException() = default;
	TimeoutException(const TimeoutException&) = default;
	TimeoutException& operator=(const TimeoutException&) = delete;
};

