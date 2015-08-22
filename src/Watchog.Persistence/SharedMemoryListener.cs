using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Watchog.IPC;

namespace Watchog.Persistence
{
    public sealed class SharedMemoryListener : IDisposable
    {
        private const string EventName = "WatchogChangeEvent";
        public static readonly TimeSpan EventTimeout = TimeSpan.FromSeconds(5);

        private readonly EventWaitHandle _waitHandle;
        private volatile bool _exit;
        private readonly IPCPeer _peer;
        private uint? _lastSyncedVersion;

        public event Action<List<MovieWrapper>> SharedMemoryChanged;

        public SharedMemoryListener(IPCPeer peer)
        {
            _waitHandle = new EventWaitHandle(false, EventResetMode.ManualReset, EventName);
            _exit = false;
            _peer = peer;
            _lastSyncedVersion = null;   
        }

        public void Start()
        {
            new Thread(() =>
            {
                _waitHandle.WaitOne(EventTimeout);

                while (!_exit)
                {
                    var list = _peer.GetAll();

                    if (!_lastSyncedVersion.HasValue || _lastSyncedVersion < list.Version)
                    {
                        OnSharedMemoryChanged(list.Movies);
                        _lastSyncedVersion = list.Version;
                    }

                    _waitHandle.Reset();
                    _waitHandle.WaitOne(EventTimeout);
                }
            }).Start();
        }

        public void Stop()
        {
            _exit = true;
        }

        public void Dispose()
        {
            Stop();
        }

        private void OnSharedMemoryChanged(List<MovieWrapper> movies)
        {
            SharedMemoryChanged?.Invoke(movies);
        }
    }
}
