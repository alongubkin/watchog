#include "Exceptions.h"
#include "ManualResetEvent.h"

ManualResetEvent::ManualResetEvent() : 
	AutoCloseHandle(create_event())
{}

HANDLE ManualResetEvent::create_event()
{
	static const PSECURITY_ATTRIBUTES DEFAULT_SECURITY = nullptr;
	static const bool MANUAL_RESET_EVENT = TRUE;
	static const bool EVENT_UNSIGNALED = FALSE;
	static const wchar_t* NO_EVENT_NAME = nullptr;

	HANDLE handle = CreateEventW(DEFAULT_SECURITY, 
								 MANUAL_RESET_EVENT, 
								 EVENT_UNSIGNALED, 
								 NO_EVENT_NAME);
	if (nullptr == handle)
	{
		throw WindowsException(GetLastError());
	}

	return handle;
}

void ManualResetEvent::wait(const std::chrono::milliseconds& timeout) const
{
	switch (WaitForSingleObject(native_handle(), (unsigned long) timeout.count()))
	{
	case WAIT_OBJECT_0:
		return;

	case WAIT_TIMEOUT:
		throw TimeoutException();

	case WAIT_FAILED:
		throw WindowsException(GetLastError());
	}

	throw std::runtime_error("ManualResetEvent::wait - Unexpected return value of WaitForSingleObject.");
}

