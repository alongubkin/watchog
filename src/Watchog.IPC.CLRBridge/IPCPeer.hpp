#pragma once

#include "../Watchog.IPC/IPCPeer.hpp"

#include "MovieState.hpp"
#include "MovieListWrapper.hpp"

namespace Watchog
{
    namespace IPC
    {
        public ref class IPCPeer sealed
        {
        public:
            IPCPeer() { _peer = new ipc::IPCPeer(); }
            ~IPCPeer() { this->!IPCPeer(); }
            !IPCPeer() { delete _peer; }

            void SetMovieState(System::String^ path, MovieState state)
            {
                const wchar_t* native_path = (const wchar_t*)
                    System::Runtime::InteropServices::Marshal::StringToHGlobalUni(path).ToPointer();
                    
                try
                {
                    _peer->set_movie_state(native_path, static_cast<ipc::MovieState>(state));
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

            void Reset(MovieListWrapper^ movieList)
            {
                _peer->reset(*movieList->ToNative());
            }

            MovieListWrapper^ GetAll()
            {
                return gcnew MovieListWrapper(*_peer->get_all());
            }

        private:
            ipc::IPCPeer* _peer;
        };
    }
}

