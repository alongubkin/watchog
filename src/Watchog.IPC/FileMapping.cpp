#include "Exceptions.hpp"
#include "FileMapping.hpp"

namespace ipc
{
    FileMapping::FileMapping(const std::wstring& name, uint64_t size) :
        AutoCloseHandle(create_file_mapping(name, size)),
        _size(size)
    {}

    HANDLE FileMapping::create_file_mapping(const std::wstring& name, uint64_t size)
    {
        static const HANDLE NOT_BACKED_BY_FILE = INVALID_HANDLE_VALUE;
        static const PSECURITY_ATTRIBUTES DEFAULT_SECURITY = nullptr;

        HANDLE handle = CreateFileMappingW(NOT_BACKED_BY_FILE,
                                           DEFAULT_SECURITY,
                                           PAGE_READWRITE,
                                           static_cast<uint32_t>(size / ULONG_MAX),
                                           static_cast<uint32_t>(size),
                                           name.c_str());
        if (nullptr == handle)
        {
            throw WindowsException(GetLastError());
        }

        return handle;
    }
}