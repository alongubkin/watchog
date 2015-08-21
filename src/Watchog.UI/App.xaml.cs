using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Forms;
using Watchog.IPC;
using Watchog.Persistence;
using Application = System.Windows.Application;

namespace Watchog.UI
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private readonly IPCPeer _peer;
        private readonly SharedMemoryListener _sharedMemoryListener;
        private readonly Database _db;

        private NotifyIcon _notifyIcon;
        private MainWindow _mainWindow;
        
        public App()
        {
            _peer = new IPCPeer();
            _db = new Database("db.sqlite");

            _sharedMemoryListener = new SharedMemoryListener(_peer, OnSharedMemoryChanged);
            _sharedMemoryListener.Start();

            _db.GetAllAsWrappers().ContinueWith((movies) =>
            {
                _peer.Reset(new MovieListWrapper()
                {
                    Version = 1,
                    Movies = movies.Result
                });
            });

            InitializeTrayIcon();
        }

        void InitializeTrayIcon()
        {
            _notifyIcon = new NotifyIcon
            {
                Text = "Watchog",
                Icon = Watchog.UI.Properties.Resources.WatchogIcon,
                Visible = true
            };
            _notifyIcon.MouseClick += NotifyIconOnMouseClick;
        }

        private void NotifyIconOnMouseClick(object sender, MouseEventArgs mouseEventArgs)
        {
            if (_mainWindow == null)
            {
                _mainWindow = new MainWindow();
            }

            _mainWindow.Show();
            _mainWindow.Activate();

            if (_mainWindow.WindowState == WindowState.Minimized)
            {
                _mainWindow.WindowState = WindowState.Normal;
            }
        }

        private void OnSharedMemoryChanged(List<MovieWrapper> movies)
        {
            _db.ApplyChanges(movies).Wait();
        }

        protected override void OnExit(ExitEventArgs e)
        {
            _sharedMemoryListener.Dispose();
            _peer.Dispose();

            base.OnExit(e);
        }
    }
}
