#include "MovieList.hpp"

namespace ipc
{
    MovieList::MovieList() :
        _movies(std::make_shared<MovieVector>())
    {}
}