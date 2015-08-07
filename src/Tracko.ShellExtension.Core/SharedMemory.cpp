#include "Exceptions.h"
#include "SharedMemory.h"

SharedMemory::SharedMemory(const std::wstring& name, const SharedMemoryAccess access) :
	_file_mapping(name),
	_file_view(map_view_of_file(_file_mapping, access))
{}

SharedMemory::SharedMemory(const std::wstring& name, const SharedMemoryAccess access, const uint64_t size) :
	_file_mapping(name, size),
	_file_view(map_view_of_file(_file_mapping, access))
{}

const void* SharedMemory::map_view_of_file(const FileMapping& file_mapping, const SharedMemoryAccess access)
{
	static const unsigned long FILE_BEGIN_OFFSET_HIGH = 0;
	static const unsigned long FILE_BEGIN_OFFSET_LOW = 0;
	static const size_t MAP_ALL_FILE = 0;

	const void* address = MapViewOfFile(file_mapping.native_handle(),
										static_cast<unsigned long>(access),
										FILE_BEGIN_OFFSET_HIGH,
										FILE_BEGIN_OFFSET_LOW,
										MAP_ALL_FILE);
	if (nullptr == address)
	{
		throw WindowsException(GetLastError());
	}
	
	return address;											  
}

SharedMemory::~SharedMemory()
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
