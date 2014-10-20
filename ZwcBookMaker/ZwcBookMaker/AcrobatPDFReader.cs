using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using Acrobat;
using System.IO;
using System.Windows.Forms;

namespace ZwcBookMaker
{
    public class AcrobatPDFReader : IDisposable
    {
        AcroAppClass mApp = null;
        AcroAVDocClass avDoc = null;
        CAcroPDDoc pdDoc = null;

        Action<Action> formInvoke = null;

        public AcrobatPDFReader(string path, Action<Action> formInvoke)
        {
            this.formInvoke = formInvoke;

            mApp = new AcroAppClass();
            mApp.Show();

            avDoc = new AcroAVDocClass();
            avDoc.Open(path, "");

            pdDoc = (CAcroPDDoc)avDoc.GetPDDoc();
        }

        public void Dispose()
        {
            pdDoc.Close();
            avDoc.Close(1);
            mApp.CloseAllDocs();
            mApp.Exit();
        }

        public int GetPageCount()
        {
            return pdDoc.GetNumPages();
        }

        public Bitmap RenderPage(int pageIndex)
        {
            //Bitmap bitmap = new Bitmap(widthPixels, heightPixels);
            //using (Graphics g = Graphics.FromImage(bitmap))
            //{
            //    SolidBrush brush = new SolidBrush(Color.White);
            //    g.FillRectangle(brush, 0, 0, widthPixels, heightPixels);

            //    int hdc = g.GetHdc().ToInt32();
            //    bool result = page.DrawEx(0, hdc, 0, 0, 0, zoom);

            //    g.ReleaseHdc();
            //    g.Flush();
            //}

            Bitmap bitmap = null;
            short widthPixels;
            short heightPixels;
            do
            {
                var page = (AcroPDPage)pdDoc.AcquirePage(pageIndex);
                var pageSize = (CAcroPoint)page.GetSize();

                widthPixels = 800;
                heightPixels = (short)(widthPixels * pageSize.y / pageSize.x);
                short zoom = (short)(((double)widthPixels / pageSize.x) * 100);

                var pdfRect = new AcroRectClass()
                {
                    right = widthPixels,
                    bottom = heightPixels
                };

                IDataObject clipboardData = null;
                page.CopyToClipboard(pdfRect, 0, 0, zoom);

                formInvoke(() =>
                {
                     clipboardData = (IDataObject)Clipboard.GetDataObject();
                });

                bitmap = (Bitmap)clipboardData.GetData(DataFormats.Bitmap);

            } while (bitmap == null || bitmap.Width != widthPixels || bitmap.Height != heightPixels);

            return bitmap;
        }
    }
}
