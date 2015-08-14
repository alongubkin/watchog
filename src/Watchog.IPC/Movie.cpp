#include "Movie.h"

Movie::Movie(const std::wstring& path, MovieState state) :
    _path(path),
    _state(state)
{}
