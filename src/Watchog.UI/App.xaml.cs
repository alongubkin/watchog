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
        private readonly NotifyIcon _notifyIcon;
        private MainWindow _mainWindow;
        
        public App()
        {
            ShutdownMode = ShutdownMode.OnExplicitShutdown;

            PersistenceContext.Create("db.sqlite").ContinueWith((task) =>
            {
                PersistenceContext = task.Result;
            });

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

            // _notifyIcon.MouseClick += NotifyIconOnMouseClick;
        }

        public PersistenceContext PersistenceContext { get; private set; }

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

        protected override void OnExit(ExitEventArgs e)
        {
            _notifyIcon.Dispose();
            PersistenceContext?.Dispose();

            base.OnExit(e);
        }
    }
}
