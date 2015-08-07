#pragma once

#include <string>
#include <memory>
#include <cstdint>

#include <Windows.h>
#include "FileMapping.h"

enum class SharedMemoryAccess : unsigned long
{
    Read = FILE_MAP_READ,
    Write = FILE_MAP_WRITE,
    ReadWrite = FILE_MAP_READ| FILE_MAP_WRITE
};

class SharedMemory final
{
public:
    SharedMemory(const std::wstring& name, const SharedMemoryAccess access, const uint64_t size);
    virtual ~SharedMemory();
    SharedMemory(const SharedMemory&) = delete;
    SharedMemory& operator=(const SharedMemory&) = delete;

    template <class T>
    T* get();
    
    uint64_t get_size() { return _size; }

private:
    static void* map_view_of_file(const FileMapping& file_mapping, const SharedMemoryAccess access);

private:
    FileMapping _file_mapping;
    void* _file_view;
    uint64_t _size;
};

using SharedMemoryPtr = std::shared_ptr<SharedMemory>;

template<class T>
T* SharedMemory::get()
{
    return reinterpret_cast<T*>(_file_view);
}