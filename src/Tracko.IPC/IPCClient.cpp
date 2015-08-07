#include <cstdint>
#include <algorithm>

#include "Config.h"
#include "IPCClient.h"

IPCClient::IPCClient() :
	_shared_memory(std::make_shared<SharedMemory>(Config::SHARED_MEMORY_NAME(), SharedMemoryAccess::Read, Config::SHARED_MEMORY_SIZE))
{}

SharedMemoryPtr IPCClient::get_shared_memory()
{
	return _shared_memory;
}