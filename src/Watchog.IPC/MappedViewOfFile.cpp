#include "Exceptions.hpp"
#include "MappedViewOfFile.hpp"

namespace ipc
{
    MappedViewOfFile::MappedViewOfFile(FileMappingPtr file_mapping, Access access) :
        _file_mapping(file_mapping),
        _file_view(map_view_of_file(_file_mapping, access))
    {}

    void* MappedViewOfFile::map_view_of_file(FileMappingPtr file_mapping, Access access)
    {
        static const unsigned long FILE_BEGIN_OFFSET_HIGH = 0;
        static const unsigned long FILE_BEGIN_OFFSET_LOW = 0;
        static const size_t MAP_ALL_FILE = 0;

        void* file_view = MapViewOfFile(file_mapping->native_handle(),
                                        static_cast<unsigned long>(access),
                                        FILE_BEGIN_OFFSET_HIGH,
                                        FILE_BEGIN_OFFSET_LOW,
                                        MAP_ALL_FILE);
        if (nullptr == file_view)
        {
            throw WindowsException(GetLastError());
        }

        return file_view;
    }

    MappedViewOfFile::~MappedViewOfFile()
    {
        try
        {
            if (!UnmapViewOfFile(_file_view))
            {
                // TODO: Log
            }
        }
        catch (...)
        {
            // TODO: Log
        }
    }

    uint64_t MappedViewOfFile::get_size() const
    {
        return _file_mapping->get_size();
    }
}