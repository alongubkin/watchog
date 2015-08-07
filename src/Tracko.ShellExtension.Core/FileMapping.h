#pragma once

#include <string>
#include <memory>
#include <cstdint>

#include <Windows.h>
#include "AutoCloseHandle.h"

class FileMapping final : public AutoCloseHandle
{
public:
	FileMapping(const std::wstring& name);
	FileMapping(const std::wstring& name, const uint64_t size);
	virtual ~FileMapping() = default;
	FileMapping(const FileMapping&) = delete;
	FileMapping& operator=(const FileMapping&) = delete;

private:
	static HANDLE open_file_mapping(const std::wstring& name);
	static HANDLE create_file_mapping(const std::wstring& name, const uint64_t size);
};