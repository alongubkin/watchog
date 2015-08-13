// Watchog.IPC.CLRBridge.h

#pragma once

#include "../Watchog.IPC/IPCPeer.h"

namespace Watchog
{
    namespace IPC
    {
        // This must match to MovieState in Models.h!
        public enum class MovieState
        {
            Unknown = 0,
            NotWatched = 1,
            Watched = 2,
            InProgress = 3
        };

        public ref class IPCPeer
        {
        public:
            IPCPeer() { _peer = new ::IPCPeer(); }
            ~IPCPeer() { this->!IPCPeer(); }
            !IPCPeer() { delete _peer; }

            void SetMovieState(System::String^ path, MovieState state)
            {
                const wchar_t* native_path = (const wchar_t*)
                    System::Runtime::InteropServices::Marshal::StringToHGlobalUni(path).ToPointer();
                    
                try
                {
                    _peer->set_movie_state(native_path, static_cast<::MovieState>(state));
                }
                finally
                {
                    System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)native_path));
                }
            }

            MovieState GetMovieState(System::String^ path)
            {
                const wchar_t* native_path = (const wchar_t*)
                    System::Runtime::InteropServices::Marshal::StringToHGlobalUni(path).ToPointer();

                try
                {
                    return static_cast<MovieState>(_peer->get_movie_state(native_path));
                }
                finally
                {
                    System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)native_path));
                }
            }

        private:
            ::IPCPeer* _peer;
        };
    }
}

