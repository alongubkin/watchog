#pragma once

#include <string>
#include <memory>
#include <cstdint>

#include <Windows.h>
#include "FileMapping.h"

namespace ipc
{    
    /// <summary>
    /// Maps the content of a <see cref="FileMapping"/> object the current process
    /// virtual address space. 
    /// </summary>
    class MappedViewOfFile final
    {
    public:
        enum class Access : unsigned long
        {
            Read = FILE_MAP_READ,
            Write = FILE_MAP_WRITE,
            ReadWrite = FILE_MAP_READ | FILE_MAP_WRITE
        };

        MappedViewOfFile(FileMappingPtr file_mapping, Access access);
        virtual ~MappedViewOfFile();
        MappedViewOfFile(const MappedViewOfFile&) = delete;
        MappedViewOfFile& operator=(const MappedViewOfFile&) = delete;

        template <class T>
        T* get();

        uint64_t get_size() const;

    private:
        static void* map_view_of_file(FileMappingPtr file_mapping, Access access);

    private:
        FileMappingPtr _file_mapping;
        void* _file_view;
    };

    using MappedViewOfFilePtr = std::shared_ptr<MappedViewOfFile>;

    template<class T>
    T* MappedViewOfFile::get()
    {
        return reinterpret_cast<T*>(_file_view);
    }
}