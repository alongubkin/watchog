#pragma once

#include "../Watchog.IPC/Movie.hpp"
#include "MovieState.hpp"

namespace Watchog
{
    namespace IPC
    {
        public ref class MovieWrapper sealed
        {
        public:
            MovieWrapper() {};
            virtual ~MovieWrapper() {};

            property System::String^ Path;
            property MovieState State;

        internal:
            MovieWrapper(const ipc::Movie& movie)
            {
                Path = gcnew System::String(movie.get_path().c_str());
                State = (MovieState) movie.get_state();
            }

            ipc::Movie ToNative()
            {
                const wchar_t* native_path = (const wchar_t*)
                    System::Runtime::InteropServices::Marshal::StringToHGlobalUni(Path).ToPointer();

                try
                {
                    return ipc::Movie(native_path, static_cast<ipc::MovieState>(State));
                }
                finally
                {
                    System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)native_path));
                }
            }
        };
    }
}