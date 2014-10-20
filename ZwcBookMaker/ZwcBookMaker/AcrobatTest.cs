using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing.Imaging;
using System.Threading;
using Acrobat;
using System.IO;
using System.Windows.Forms;
using System.Drawing;

namespace ZwcBookMaker
{
    public class AcrobatTest
    {
        public void Run()
        {
            var mApp = new AcroAppClass();
            mApp.Show();
            

            CAcroAVDoc avDoc = new AcroAVDocClass();

            string path = Path.Combine(Application.StartupPath, "人月神话.pdf");
            if (avDoc.Open(path, ""))
            {
                var pdDoc = (CAcroPDDoc)avDoc.GetPDDoc();
                var iNum = pdDoc.GetNumPages();
                var szName = pdDoc.GetFileName();

                var page = (AcroPDPage)pdDoc.AcquirePage(1);
                var pageSize = (CAcroPoint)page.GetSize();

                short widthPixels = 800;
                short heightPixels = (short)(widthPixels * pageSize.y / pageSize.x);
                short zoom = (short)(((double)widthPixels / pageSize.x) * 100);

                var pdfRect = new AcroRectClass()
                {
                    right = widthPixels,
                    bottom = heightPixels
                };

                page.CopyToClipboard(pdfRect, 0, 0, zoom);

                var clipboardData = (IDataObject)Clipboard.GetDataObject();
                var pdfBitmap = (Bitmap)clipboardData.GetData(DataFormats.Bitmap);

                pdfBitmap.Save("test.png", ImageFormat.Png);

                avDoc.Close(1);
                mApp.CloseAllDocs();
                mApp.Exit();
                MessageBox.Show("Done");
            }
        }
    }
}
