#pragma once

#include <string>

#include "Models.h"
#include "SharedMemory.h"
#include "IPCPeer.h"

class IPCClient final : public IPCPeer
{
public:
	IPCClient();
	virtual ~IPCClient() = default;
	IPCClient(const IPCClient&) = delete;
	IPCClient& operator=(const IPCClient&) = delete;

protected:
	virtual SharedMemoryPtr get_shared_memory() override;

private:
	SharedMemoryPtr _shared_memory;
};

