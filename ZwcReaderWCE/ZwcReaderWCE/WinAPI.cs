using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;  

namespace ZwcReaderWCE
{
    public static class WinAPI
    {
        [DllImport("coredll.dll")]
        public static extern IntPtr FindWindow(String classname, String title);

        [DllImport("coredll.dll")]
        public static extern void SetForegroundWindow(IntPtr hwnd); 
    }
}
