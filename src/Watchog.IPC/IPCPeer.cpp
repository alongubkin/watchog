#include "Exceptions.hpp"
#include "Config.hpp"
#include "LockedMutex.hpp"
#include "SharedMovieListUtils.hpp"
#include "IPCPeer.hpp"

namespace ipc
{
    IPCPeer::IPCPeer() :
        _mutex(std::make_shared<Mutex>(Config::MUTEX_NAME())),
        _file_mapping(std::make_shared<FileMapping>(Config::SHARED_MEMORY_NAME(), Config::SHARED_MEMORY_SIZE)),
        _shared_memory(std::make_shared<MappedViewOfFile>(_file_mapping, MappedViewOfFile::Access::ReadWrite)),
        _change_event(Config::CHANGE_EVENT_NAME(), false)
    {}

    const MovieState IPCPeer::get_movie_state(const std::wstring& path)
    {    
        LockedMutex lock(_mutex, Config::MUTEX_TIMEOUT());

        SharedMovie* movie = get_movie_by_path(path);
        if (nullptr == movie)
        {
            return MovieState::Unknown;
        }

        return movie->state;
    }

    void IPCPeer::set_movie_state(const std::wstring& path, const MovieState state)
    {
        LockedMutex lock(_mutex, Config::MUTEX_TIMEOUT());
        auto list = _shared_memory->get<SharedMovieList>();
    
        // Try to find this movie path in the shared memory. If we can't find it,
        // we need to add a new record to the shared memory movies array.
        SharedMovie* movie = get_movie_by_path(path);
        if (nullptr == movie)
        {
            // Don't permit adding a not watched/unknown entries to the memory, as
            // all files are considered not watched by default.
            if ((MovieState::NotWatched == state) ||
                (MovieState::Unknown == state))
            {
                return;
            }

            // Increment the movie pointer to one movie after the last 
            // movie in the memory.
            movie = &list->movies[0];
            for (uint32_t i = 0; i < list->count; i++)
            {
                movie = SharedMovieListUtils::get_next_movie(movie);
            }

            // Make sure the movie pointer is within the shared memory range
            if (!SharedMovieListUtils::is_valid_pointer(_shared_memory, movie, path))
            {
                throw InsufficientSharedMemoryException();
            }

            // Copy path to the new record
            if (0 != wcscpy_s(movie->path, MAX_PATH, path.c_str()))
            {
                throw StringException();
            }

            list->count++;
        }

        movie->state = state;
        list->version++;

        _change_event.set();
    }

    MovieListPtr IPCPeer::get_all()
    {
        auto shared_movies = _shared_memory->get<SharedMovieList>();

        // Create the movies vector
        MovieListPtr movies = std::make_shared<MovieList>();
        movies->set_version(shared_movies->version);
    
        // Iterate movies in the shared memory and add to the vector
        SharedMovie* shared_movie = &shared_movies->movies[0];
        for (uint32_t i = 0; i < shared_movies->count; i++)
        {
            movies->get_movies()->emplace_back(Movie(shared_movie->path, shared_movie->state));
        }

        return movies;
    }

    void IPCPeer::reset(const MovieList& movies)
    {
        LockedMutex lock(_mutex, Config::MUTEX_TIMEOUT());
        auto list = _shared_memory->get<SharedMovieList>();
    
        // Zero shared memory
        ZeroMemory(list, static_cast<size_t>(_shared_memory->get_size()));

        // Initialize the shared movie list
        list->version = movies.get_version();

        // Add all movies to the shared memory
        SharedMovie* shared_movie = &list->movies[0];
        for (const auto& movie : *movies.get_movies())
        {
            // Copy data to the shared memory movie instance
            shared_movie->state = movie.get_state();
            if (0 != wcscpy_s(shared_movie->path, movie.get_path().size(), movie.get_path().c_str()))
            {
                throw StringException();
            }

            list->count++;

            // Increment shared memory movie pointer
            shared_movie = SharedMovieListUtils::get_next_movie(shared_movie);

            // Make sure the shared movie pointer is within the shared memory range
            if (!SharedMovieListUtils::is_valid_pointer(_shared_memory, shared_movie, movie.get_path()))
            {
                throw InsufficientSharedMemoryException();
            }
        }
    }

    SharedMovie* IPCPeer::get_movie_by_path(const std::wstring& path)
    {
        auto list = _shared_memory->get<SharedMovieList>();

        SharedMovie* movie = &list->movies[0];
        for (uint32_t i = 0; i < list->count; i++)
        {
            if (0 == _wcsnicmp(path.c_str(), movie->path, MAX_PATH))
            {
                return movie;
            }

            // Continue to the next movie
            movie = SharedMovieListUtils::get_next_movie(movie);
        }

        return nullptr;
    }
}