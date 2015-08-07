#pragma once

#include <string>
#include <memory>
#include <cstdint>

#include <Windows.h>
#include "FileMapping.h"

enum class SharedMemoryAccess : unsigned long
{
	Read = FILE_MAP_READ,
	Write = FILE_MAP_WRITE
};

class SharedMemory final
{
public:
	SharedMemory(const std::wstring& name, const SharedMemoryAccess access);
	SharedMemory(const std::wstring& name, const SharedMemoryAccess access, const uint64_t size);
	virtual ~SharedMemory();
	SharedMemory(const SharedMemory&) = delete;
	SharedMemory& operator=(const SharedMemory&) = delete;

	template <class T>
	const T* get() const;

private:
	static const void* map_view_of_file(const FileMapping& file_mapping, const SharedMemoryAccess access);

private:
	FileMapping _file_mapping;
	const void* _file_view;
};

template<class T>
const T* SharedMemory::get() const
{
	return reinterpret_cast<const T*>(_file_view);
}
