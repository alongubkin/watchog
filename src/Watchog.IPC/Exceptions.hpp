#pragma once

#include <cstdint>
#include <stdexcept>

namespace ipc
{    
    /// <summary>
    /// Thrown when a Win32 API call fails.
    /// </summary>
    class WindowsException final : public std::exception
    {
    public:
        WindowsException(const uint32_t last_error) :
            std::exception(),
            _last_error(last_error)
        {}

        virtual ~WindowsException() = default;
        WindowsException(const WindowsException&) = default;
        WindowsException& operator=(const WindowsException&) = delete;

        const uint32_t get_last_error() { return _last_error; }

    private:
        const uint32_t _last_error;
    };
    
    /// <summary>
    /// Thrown when a timeout reaches.
    /// </summary>
    class TimeoutException final : public std::exception
    {
    public:
        TimeoutException() = default;
        virtual ~TimeoutException() = default;
        TimeoutException(const TimeoutException&) = default;
        TimeoutException& operator=(const TimeoutException&) = delete;
    };
    
    /// <summary>
    /// Thrown on an attempt to add an entry to a full shared memory buffer.
    /// </summary>
    class InsufficientSharedMemoryException final : public std::exception
    {
    public:
        InsufficientSharedMemoryException() = default;
        virtual ~InsufficientSharedMemoryException() = default;
        InsufficientSharedMemoryException(const InsufficientSharedMemoryException&) = default;
        InsufficientSharedMemoryException& operator=(const InsufficientSharedMemoryException&) = delete;
    };

    /// <summary>
    /// Thrown when a string operation fails.
    /// </summary>
    class StringException final : public std::exception
    {
    public:
        StringException() = default;
        virtual ~StringException() = default;
        StringException(const StringException&) = default;
        StringException& operator=(const StringException&) = delete;
    };
    
    /// <summary>
    /// Thrown on an attempt to lock an abandoned mutex.
    /// </summary>
    class AbandonedMutexException final : public std::exception
    {
    public:
        AbandonedMutexException() = default;
        virtual ~AbandonedMutexException() = default;
        AbandonedMutexException(const AbandonedMutexException&) = default;
        AbandonedMutexException& operator=(const AbandonedMutexException&) = delete;
    };
}