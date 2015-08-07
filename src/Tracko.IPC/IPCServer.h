#pragma once

#include <cstdint>
#include <string>

#include "Models.h"
#include "Config.h"
#include "SharedMemory.h"
#include "IPCPeer.h"

class IPCServer final : public IPCPeer
{
private:
	static const uint32_t MAXIMUM_MOVIE_COUNT = (Config::SHARED_MEMORY_SIZE - sizeof(MovieMetadataList)) / sizeof(MovieMetadata) - 1;

public:
	IPCServer();
	virtual ~IPCServer() = default;
	IPCServer(const IPCServer&) = delete;
	IPCServer& operator=(const IPCServer&) = delete;

	void set_movie_state(const std::wstring& path, const MovieState state);

protected:
	virtual SharedMemoryPtr get_shared_memory() override;

private:
	SharedMemoryPtr _shared_memory;
};

