#include "Exceptions.h"
#include "Config.h"
#include "LockedMutex.h"
#include "IPCPeer.h"

IPCPeer::IPCPeer() :
    _mutex(std::make_shared<Mutex>(Config::MUTEX_NAME())),
    _shared_memory(std::make_shared<SharedMemory>(Config::SHARED_MEMORY_NAME(), 
                                                  SharedMemoryAccess::ReadWrite, 
                                                  Config::SHARED_MEMORY_SIZE))
{}

const MovieState IPCPeer::get_movie_state(const std::wstring& path)
{    
    LockedMutex lock(_mutex, Config::MUTEX_TIMEOUT());

    auto movie = get_movie_by_path(path);
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
        // Increment the movie pointer to be after the last movie
        movie = &data->movies[0];
        for (uint32_t i = 0; i < data->count; i++)
        {
            movie = reinterpret_cast<MovieModel*>((size_t) movie + sizeof(*movie) + (wcslen(movie->path) + 1) * sizeof(wchar_t));
        }

        // Make sure the movie pointer is within the shared memory range
        size_t movie_as_size = reinterpret_cast<size_t>(movie);
        size_t shared_memory_as_size = reinterpret_cast<size_t>(data);
        if ((movie_as_size < shared_memory_as_size) ||
            (movie_as_size + sizeof(MovieModel) + path.size() * sizeof(wchar_t) >= shared_memory_as_size + _shared_memory->get_size()))
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
