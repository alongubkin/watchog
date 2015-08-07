#include "Exceptions.h"
#include "FileMapping.h"

FileMapping::FileMapping(const std::wstring& name) :
	AutoCloseHandle(open_file_mapping(name))
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