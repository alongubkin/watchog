#pragma once

#include <string>
#include <vector>
#include <memory>

#include "SharedMemoryStructs.hpp"

namespace ipc
{    
    class Movie
    {
    public:
        Movie(const std::wstring& path, MovieState state);
        virtual ~Movie() = default;
        Movie(const Movie&) = delete;
        Movie& operator=(const Movie&) = delete;
        Movie(Movie&&) = default;
        Movie& operator=(Movie&&) = default;

        std::wstring get_path() const { return _path; }
        void set_path(const std::wstring& path) { _path = path; }

        MovieState get_state() const { return _state; }
        void set_state(MovieState state) { _state = state; }

    private:
        std::wstring _path;
        MovieState _state;
    };

    using MovieVector = std::vector<Movie>;
    using MovieVectorPtr = std::shared_ptr<MovieVector>;
}