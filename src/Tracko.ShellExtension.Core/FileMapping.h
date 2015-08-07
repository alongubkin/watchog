#pragma once

#include <string>
#include <memory>

#include <Windows.h>
#include "AutoCloseHandle.h"

class FileMapping final : public AutoCloseHandle
{
public:
	FileMapping(const std::wstring& name);
	virtual ~FileMapping() = default;
	FileMapping(const FileMapping&) = delete;
	FileMapping& operator=(const FileMapping&) = delete;

private:
	static HANDLE open_file_mapping(const std::wstring& name);
};