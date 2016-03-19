#pragma once

#include <string>
#include <cstdint>

#include "IPCPeer.hpp"

namespace ipc
{
	class PluginState
	{
	public:
		PluginState();
		virtual ~PluginState() = default;
		PluginState(const PluginState&) = delete;
		PluginState& operator=(const PluginState&) = delete;

		void set_current_file(const std::wstring& path);
		void set_current_length(const uint64_t length);
		void set_movie_length(const uint64_t length);
		uint64_t get_current_length() const { return _current_length; }
		uint64_t get_movie_length() const { return _movie_length; }
		void mark_as_watched();

	private:
		IPCPeer _peer;
		std::wstring _current_file_path;
		uint64_t _current_length;
		uint64_t _movie_length;
		MovieState _current_movie_state;
	};

}