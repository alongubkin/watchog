#include "Exceptions.h"
#include "LockedMutex.h"

LockedMutex::LockedMutex(MutexPtr mutex, const std::chrono::milliseconds timeout) :
	_mutex(mutex)
{
	switch (WaitForSingleObject(mutex->native_handle(), (unsigned long) timeout.count()))
	{
	case WAIT_OBJECT_0:
		// Great success!
		return;

	case WAIT_FAILED:
		throw WindowsException(GetLastError());

	case WAIT_TIMEOUT:
		throw TimeoutException();

	case WAIT_ABANDONED:
		throw AbandonedMutexException();

	default:
		throw std::runtime_error("LockedMutex::LockedMutex: Unexpected return value of WaitForSingleObject.");
	}
}

LockedMutex::~LockedMutex()
{
	try 
	{
		if (!ReleaseMutex(_mutex->native_handle()))
		{
			// TODO: Log
		}
	}
	catch (...)
	{
		// TODO: Log
	}
}