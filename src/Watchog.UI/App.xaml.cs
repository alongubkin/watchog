using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Forms;
using Application = System.Windows.Application;

namespace Watchog.UI
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private NotifyIcon _notifyIcon;
        private MainWindow _mainWindow;

        public App()
        {
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
    }
}
