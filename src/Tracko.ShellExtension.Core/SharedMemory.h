#pragma once

#include <string>
#include <memory>

#include <Windows.h>
#include "FileMapping.h"

class SharedMemory final
{
public:
	SharedMemory(const std::wstring& name);
	virtual ~SharedMemory();
	SharedMemory(const SharedMemory&) = delete;
	SharedMemory& operator=(const SharedMemory&) = delete;

	template <class T>
	const T* get() const;

private:
	static const void* map_view_of_file(const FileMapping& file_mapping);

private:
	FileMapping _file_mapping;
	const void* _file_view;
};

template<class T>
const T* SharedMemory::get() const
{
	return reinterpret_cast<const T*>(_file_view);
}
