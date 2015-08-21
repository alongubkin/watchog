using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Watchog.UI
{
    
    
    static class ShellUtils
    {
        public const int UpdateItem = 0x2000;
        public const uint SHCNF_PATHW = 0x0005;
        public const uint SHCNF_FLUSHNOWAIT = 0x2000;

        [DllImport("shell32.dll")]
        static extern void SHChangeNotify(int wEventId,
                                          uint uFlags,
                                          IntPtr dwItem1,
                                          IntPtr dwItem2);

        public static void RefreshShellIcon(string path)
        {
            var pathPtr = Marshal.StringToHGlobalUni(path);

            try
            {
                SHChangeNotify(UpdateItem,
                               SHCNF_PATHW|SHCNF_FLUSHNOWAIT,
                               pathPtr,
                               IntPtr.Zero);
            }
            finally
            {
                Marshal.FreeHGlobal(pathPtr);
            }

        }
    }
}
