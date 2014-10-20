using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace ZwcBookMaker
{
    public class FoxitPDFSDK : IDisposable
    {
        const string dllPath = "Lib/Foxit_PDF_SDK_DLL_3.1_Cracked/fpdfsdk.dll";

        public FoxitPDFSDK()
        {
            FPDF_UnlockDLL("SDKRDTEMP", "921315A06BD486EBC0792D60A826A5C4455E33A8");
            FoxitPDFSDK.FPDF_InitLibrary(new IntPtr(0));
        }

        public void Dispose()
        {
            FoxitPDFSDK.FPDF_DestroyLibrary();
        }

        [DllImport(dllPath)]
        public static extern void FPDF_UnlockDLL(string licenseId, string unlockCode);

        [DllImport(dllPath)]
        public extern static void FPDF_InitLibrary(IntPtr hWnd);
        
        [DllImport(dllPath)]
        public extern static void FPDF_DestroyLibrary();

        [DllImport(dllPath)]
        public extern static IntPtr FPDF_LoadDocument(string path, string pwd);

        [DllImport(dllPath)]
        public extern static IntPtr FPDF_LoadPage(IntPtr doc, int pageIndex);

        [DllImport(dllPath)]
        public static extern void FPDF_RenderPage(System.IntPtr hdc, IntPtr page, int start_x, int start_y, int size_x, int size_y, int rotate, PageRenderingFlags flags);

        [DllImport(dllPath)]
        public extern static double FPDF_GetPageWidth(IntPtr page);

        [DllImport(dllPath)]
        public extern static double FPDF_GetPageHeight(IntPtr page);
    }

    public enum PageRenderingFlags
    {
        FPDF_ANNOT = 1,
        FPDF_LCD_TEXT = 2,
        FPDF_NO_GDIPLUS = 4,
        FPDF_GRAYSCALE = 8,
        FPDF_DEBUG_INFO = 128,
        FPDF_NO_CATCH = 256,
    }
}
