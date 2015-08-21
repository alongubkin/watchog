#pragma once

#include <memory>

#include "../Watchog.IPC/MovieList.hpp"
#include "MovieWrapper.hpp"

namespace Watchog
{
    namespace IPC
    {
        public ref class MovieListWrapper sealed
        {
        public:
            MovieListWrapper() {};
            virtual ~MovieListWrapper() {};

            property System::UInt32 Version;
            property System::Collections::Generic::List<MovieWrapper^>^ Movies;

        internal:
            MovieListWrapper(const ipc::MovieList& list)
            {
                Version = list.get_version();
                Movies = gcnew System::Collections::Generic::List<MovieWrapper^>();

                for (const auto& movie : *list.get_movies())
                {
                    Movies->Add(gcnew MovieWrapper(movie));
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

