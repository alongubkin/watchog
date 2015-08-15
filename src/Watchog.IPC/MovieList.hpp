#pragma once

#include <cstdint>
#include <memory>

#include "Movie.hpp"

namespace ipc
{    
    class MovieList
    {
    public:
        MovieList();
        virtual ~MovieList() = default;
        MovieList(const MovieList&) = delete;
        MovieList& operator=(const MovieList&) = delete;

        uint32_t get_version() const { return _version; }
        void set_version(uint32_t version) { _version = version; }

        MovieVectorPtr get_movies() const { return _movies; }

    private:
        uint32_t _version;
        MovieVectorPtr _movies;
    };

    using MovieListPtr = std::shared_ptr<MovieList>;
}