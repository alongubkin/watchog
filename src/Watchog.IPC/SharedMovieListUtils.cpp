#include "Exceptions.h"
#include "SharedMovieListUtils.h"

namespace ipc
{
    SharedMovie* SharedMovieListUtils::get_next_movie(const SharedMovie* movie)
    {
        return reinterpret_cast<SharedMovie*>((size_t)movie + sizeof(*movie)
            + (wcslen(movie->path) + 1) * sizeof(wchar_t));
    }

    bool SharedMovieListUtils::is_valid_pointer(MappedViewOfFilePtr shared_memory, const SharedMovie* movie, const std::wstring& path)
    {
        auto list = shared_memory->get<SharedMovieList>();

        size_t movie_as_size = reinterpret_cast<size_t>(movie);
        size_t shared_memory_as_size = reinterpret_cast<size_t>(list);

        return (movie_as_size >= shared_memory_as_size) &&
            (movie_as_size + sizeof(SharedMovie) + path.size() * sizeof(wchar_t) <
                shared_memory_as_size + shared_memory->get_size());
    }
}