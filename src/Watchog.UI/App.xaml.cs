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
        private IPCPeer _peer;
        private SharedMemoryListener _sharedMemoryListener;
        private Database _db;

        private readonly NotifyIcon _notifyIcon;
        private MainWindow _mainWindow;
        
        public App()
        {
            ShutdownMode = ShutdownMode.OnExplicitShutdown;

            _notifyIcon = new NotifyIcon
            {
                Text = "Watchog",
                Icon = Watchog.UI.Properties.Resources.WatchogIcon,
                Visible = true,
                ContextMenu = new ContextMenu(new []
                {
                    new MenuItem("Exit", (sender, e) =>
                    {
                        Shutdown();
                    })
                })
            };

            _notifyIcon.MouseClick += NotifyIconOnMouseClick;
            InitializeIpc();
        }

        private void InitializeIpc()
        {
            Task.Run(async () =>
            {
                _peer = new IPCPeer();
                _db = new Database("db.sqlite");

                var movies = await _db.GetAllAsWrappers();
                _peer.Reset(new MovieListWrapper
                {
                    Movies = movies
                });

                foreach (var movie in movies)
                {
                    ShellUtils.RefreshShellIcon(movie.Path);
                }

                _sharedMemoryListener = new SharedMemoryListener(_peer, OnSharedMemoryChanged);
                _sharedMemoryListener.Start();
            });
        }

        private void NotifyIconOnMouseClick(object sender, MouseEventArgs mouseEventArgs)
        {
            if (_mainWindow == null || !_mainWindow.IsLoaded)
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
            _notifyIcon.Dispose();
            _sharedMemoryListener?.Dispose();
            _peer?.Dispose();

            base.OnExit(e);
        }
    }
}
