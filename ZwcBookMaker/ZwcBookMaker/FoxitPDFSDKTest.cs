using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;

namespace ZwcBookMaker
{
    public class FoxitPDFSDKTest
    {
        public void Run()
        {
            using (var foxiPdf = new FoxitPDFSDK())
            {
                var doc = FoxitPDFSDK.FPDF_LoadDocument(@"人月神话.pdf", null);
                var page = FoxitPDFSDK.FPDF_LoadPage(doc, 0);

                double width = FoxitPDFSDK.FPDF_GetPageWidth(page);
                double height = FoxitPDFSDK.FPDF_GetPageHeight(page);

                int widthPixels = 800;
                int heightPixels = (int)(widthPixels * height / width);

                Bitmap bitmap = new Bitmap(widthPixels, heightPixels);

                using (Graphics g = Graphics.FromImage(bitmap))
                {
                    SolidBrush brush = new SolidBrush(Color.White);
                    g.FillRectangle(brush, 0, 0, widthPixels, heightPixels);

                    FoxitPDFSDK.FPDF_RenderPage(g.GetHdc(), page, 0, 0, widthPixels, heightPixels, 0, PageRenderingFlags.FPDF_NO_GDIPLUS);
                    g.ReleaseHdc();
                    g.Flush();
                    bitmap.Save("test.bmp", ImageFormat.Bmp);

                    MessageBox.Show("Done");
                }
            }
        }
    }
}
