#include "Exceptions.h"
#include "FileMapping.h"

FileMapping::FileMapping(const std::wstring& name) :
	AutoCloseHandle(open_file_mapping(name))
{}

FileMapping::FileMapping(const std::wstring& name, const uint64_t size) :
	AutoCloseHandle(create_file_mapping(name, size))
{}

HANDLE FileMapping::open_file_mapping(const std::wstring& name)
{
	static const BOOL NO_HANDLE_INHERITANCE = FALSE;

	HANDLE handle = OpenFileMappingW(FILE_MAP_READ, NO_HANDLE_INHERITANCE, name.c_str());
	if (NULL == handle)
	{
		throw WindowsException(GetLastError());
	}

	return handle;
}

HANDLE FileMapping::create_file_mapping(const std::wstring& name, const uint64_t size)
{
	static const HANDLE NOT_BACKED_BY_FILE = INVALID_HANDLE_VALUE;
	static const PSECURITY_ATTRIBUTES DEFAULT_SECURITY = nullptr;
	 
	HANDLE handle = CreateFileMappingW(NOT_BACKED_BY_FILE,
									   DEFAULT_SECURITY,
									   PAGE_READWRITE,
									   static_cast<uint32_t>(size / ULONG_MAX),
									   static_cast<uint32_t>(size),
									   name.c_str());
	if (NULL == handle)
	{
		throw WindowsException(GetLastError());
	}

	return handle;
}