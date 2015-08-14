#pragma once

#include <memory>

#include "../Watchog.IPC/MovieList.h"
#include "Movie.h"

namespace Watchog
{
    namespace IPC
    {
        public ref class MovieList sealed
        {
        public:
            MovieList() {};
            virtual ~MovieList() {};

            property System::UInt32 Version;
            property System::Collections::Generic::List<Movie^>^ Movies;

        internal:
            MovieList(const ipc::MovieList& list)
            {
                Version = list.get_version();
                Movies = gcnew System::Collections::Generic::List<Movie^>();

                for (const auto& movie : *list.get_movies())
                {
                    Movies->Add(gcnew Movie(movie));
                }
            }

            ipc::MovieListPtr ToNative()
            {
                ipc::MovieListPtr movies = std::make_shared<ipc::MovieList>();
                movies->set_version(Version);

                for each(auto movie in Movies)
                {
                    movies->get_movies()->emplace_back(movie->ToNative());
                }

                return movies;
            }
        };
    }
}

