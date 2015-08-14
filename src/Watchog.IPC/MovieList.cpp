#include "MovieList.h"

MovieList::MovieList() :
    _movies(std::make_shared<MovieVector>())
{}