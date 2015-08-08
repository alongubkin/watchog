using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace Tracko.TrayApp
{
    class Tray : Form
    {
        private NotifyIcon trayIcon;

        public Tray()
        {
            ContextMenu trayMenu = new ContextMenu();
            trayMenu.MenuItems.Add("Open Recently Watched");
            trayMenu.MenuItems.Add("Config");
            trayMenu.MenuItems.Add("-");
            trayMenu.MenuItems.Add("Exit", OnExit);

            trayIcon = new NotifyIcon();
            trayIcon.Text = "Tracko";
            trayIcon.Icon = new Icon(SystemIcons.Application, 40, 40);
            trayIcon.ContextMenu = trayMenu;
            trayIcon.Visible = true;
        }

        private void OnExit(object sender, EventArgs e)
        {
            Application.Exit();
        }

        protected override void OnLoad(EventArgs e)
        {
            Visible = false;
            ShowInTaskbar = false;

            base.OnLoad(e);
        }

        protected override void Dispose(bool isDisposing)
        {
            if (isDisposing)
                trayIcon.Dispose();

            base.Dispose(isDisposing);
        }
    }
}
