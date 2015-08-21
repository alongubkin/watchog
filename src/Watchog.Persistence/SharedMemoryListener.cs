using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Watchog.IPC;

namespace Watchog.Persistence
{
    public class SharedMemoryListener : IDisposable
    {
        private const string EventName = "WatchogChangeEvent";
        private static readonly int EventTimeout = (int) TimeSpan.FromHours(10).TotalMilliseconds;

        private readonly EventWaitHandle _waitHandle;
        private RegisteredWaitHandle _registeredWaitHandle;
        private readonly IPCPeer _peer;
        private readonly Action<List<MovieWrapper>> _callback;
        private uint? _lastSyncedVersion;

        public SharedMemoryListener(IPCPeer peer, Action<List<MovieWrapper>> callback)
        {
            _peer = peer;
            _lastSyncedVersion = null;
            _waitHandle = new EventWaitHandle(false, EventResetMode.ManualReset, EventName);
            _callback = callback;
        }

        public void Start()
        {
            if (_registeredWaitHandle != null)
            {
                Stop();
            } 

            _registeredWaitHandle = ThreadPool.RegisterWaitForSingleObject(_waitHandle,
                OnSharedMemoryChange, null, EventTimeout, true);
        }

        public void Stop()
        {
            _registeredWaitHandle.Unregister(_waitHandle);
        }

        private void OnSharedMemoryChange(object state, bool timedOut)
        {
            if (timedOut)
            {
                Start();
                return;
            }

            var list = _peer.GetAll();
            
            if (!_lastSyncedVersion.HasValue || _lastSyncedVersion < list.Version)
            {
                _callback(list.Movies);
                _lastSyncedVersion = list.Version;
            }

            _waitHandle.Reset();
            Start();
        }

        public void Dispose()
        {
            Stop();
        }
    }
}
