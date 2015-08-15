#pragma once

#include <string>
#include <memory>
#include <cstdint>

#include <Windows.h>
#include "AutoCloseHandle.hpp"

namespace ipc
{    
    /// <summary>
    /// File mapping objects are used for creating memory sections that are shared
    /// between multiple processes (for example: VLC plugin, tray application, etc).
    /// To map a file mapping object to the current process memory, use <see cref="MappedViewOfFile"/>.
    /// </summary>
    class FileMapping final : public AutoCloseHandle
    {
    public:
        FileMapping(const std::wstring& name, uint64_t size);
        virtual ~FileMapping() = default;
        FileMapping(const FileMapping&) = delete;
        FileMapping& operator=(const FileMapping&) = delete;

        uint64_t get_size() { return _size; }

    private:
        static HANDLE create_file_mapping(const std::wstring& name, uint64_t size);

    private:
        uint64_t _size;
    };

    using FileMappingPtr = std::shared_ptr<FileMapping>;
}