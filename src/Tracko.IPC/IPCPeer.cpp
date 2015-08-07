#include "Exceptions.h"
#include "Config.h"
#include "LockedMutex.h"
#include "IPCPeer.h"

IPCPeer::IPCPeer() :
    _mutex(std::make_shared<Mutex>(Config::MUTEX_NAME())),
    _file_mapping(std::make_shared<FileMapping>(Config::SHARED_MEMORY_NAME(), Config::SHARED_MEMORY_SIZE)),
    _shared_memory(std::make_shared<MappedViewOfFile>(_file_mapping, MappedViewOfFile::Access::ReadWrite))
{}

const MovieState IPCPeer::get_movie_state(const std::wstring& path)
{    
    LockedMutex lock(_mutex, Config::MUTEX_TIMEOUT());

    MovieModel* movie = get_movie_by_path(path);
    if (nullptr == movie)
    {
        return MovieState::Unknown;
    }

    return movie->state;
}

void IPCPeer::set_movie_state(const std::wstring& path, const MovieState state)
{
    LockedMutex lock(_mutex, Config::MUTEX_TIMEOUT());
    auto data = _shared_memory->get<MovieListModel>();

    // Try to find this movie path in the shared memory. If we can't find it,
    // we need to add a new record to the shared memory movies array.
    MovieModel* movie = get_movie_by_path(path);
    if (nullptr == movie)
    {
        // Don't permit adding a not watched/unknown entries to the memory, as
        // all files are considered not watched by default.
        if ((MovieState::NotWatched == state) ||
            (MovieState::Unknown == state))
        {
            return;
        }

        // Increment the movie pointer to be the first unwatched movie,
        // or to point to after the last movie in the memory.
        movie = &data->movies[0];
        for (uint32_t i = 0; i < data->count; i++)
        {
            movie = reinterpret_cast<MovieModel*>((size_t) movie + sizeof(*movie) + (wcslen(movie->path) + 1) * sizeof(wchar_t));
        }

        // Make sure the movie pointer is within the shared memory range
        size_t movie_as_size = reinterpret_cast<size_t>(movie);
        size_t shared_memory_as_size = reinterpret_cast<size_t>(data);
        if ((movie_as_size < shared_memory_as_size) ||
            (movie_as_size + sizeof(MovieModel) + path.size() * sizeof(wchar_t) >= 
                shared_memory_as_size + _file_mapping->get_size()))
        {
            throw InsufficientSharedMemoryException();
        }

        // Copy path to the new record
        if (0 != wcscpy_s(movie->path, MAX_PATH, path.c_str()))
        {
            throw StringException();
        }

        data->count++;
    }

    movie->state = state;
}

MovieModel* IPCPeer::get_movie_by_path(const std::wstring& path)
{
    auto data = _shared_memory->get<MovieListModel>();

    MovieModel* movie = &data->movies[0];
    for (uint32_t i = 0; i < data->count; i++)
    {
        if (0 == _wcsnicmp(path.c_str(), movie->path, MAX_PATH))
        {
            return movie;
        }

        // Continue to the next movie
        movie = reinterpret_cast<MovieModel*>((size_t)movie + sizeof(*movie) + (wcslen(movie->path) + 1) * sizeof(wchar_t));
    }

    return nullptr;
}
