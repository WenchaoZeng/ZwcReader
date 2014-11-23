using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.IO;
using System.Drawing.Imaging;

namespace ZwcBookMaker
{
    public class PageOutPutter
    {
        string targetFolder = null;

        const int pageWidth = 800;
        const int pageHeight = 600;
        const int canvasHeight = 3000;

        Bitmap canvas = new Bitmap(pageWidth, canvasHeight);
        Graphics graphics;
        int currentY = 0;

        public PageOutPutter(string targetFolder)
        {
            this.targetFolder = targetFolder;
            graphics = Graphics.FromImage(canvas);
        }

        public void AddPage(Bitmap bitmap)
        {
            graphics.DrawImageUnscaled(bitmap, 0, currentY);
            currentY += bitmap.Height;
            SavePage();
        }

        public void Flush()
        {
            currentY += pageHeight;
            SavePage();
        }

        private void SavePage()
        {
            while (currentY >= pageHeight)
            {
                int cutHeight = CalculateCutHeight();

                // Save page
                Bitmap page = new Bitmap(pageWidth, pageHeight);
                Rectangle pageRect = new Rectangle(0, 0, pageWidth, cutHeight);
                Graphics graphics = Graphics.FromImage(page);
                graphics.Clear(Color.White);
                graphics.DrawImage(canvas, pageRect, pageRect, GraphicsUnit.Pixel);
                SaveImage(page);

                // Refresh canvas
                Bitmap newCanvas = new Bitmap(pageWidth, canvasHeight);
                Graphics newGraphics = Graphics.FromImage(newCanvas);
                Rectangle destRect = new Rectangle(0, 0, pageWidth, canvasHeight - cutHeight);
                newGraphics.DrawImage(canvas, destRect, 0, cutHeight, pageWidth, canvasHeight - cutHeight, GraphicsUnit.Pixel);
                this.canvas = newCanvas;
                this.graphics = newGraphics;

                currentY -= cutHeight;
            }
        }

        private void SaveImage(Bitmap page)
        {
            string filePath = GetNewPathParth();
            page.RotateFlip(RotateFlipType.Rotate90FlipNone);

            page.Save(filePath, ImageFormat.Gif);
        }

        int pageIndex = 1;
        private string GetNewPathParth()
        {
            string filePath = Path.Combine(targetFolder, string.Format("{0:D4}.gif", pageIndex));
            ++pageIndex;
            return filePath;
        }

        public int GetOutputPageCount()
        {
            return pageIndex - 1;
        }

        public int CalculateCutHeight()
        {
            for (int yIndex = pageHeight - 1; yIndex >= 0; --yIndex)
            {
                bool isWhiteLine = true;
                for (int xIndex = 0; xIndex < pageWidth; ++xIndex)
                {
                    Color pixel = canvas.GetPixel(xIndex, yIndex);
                    if (pixel.R < 220 || pixel.G < 220 || pixel.B < 220)
                    {
                        isWhiteLine = false;
                        break;
                    }
                }

                if (isWhiteLine)
                {
                    return yIndex + 1;
                }
            }

            return pageHeight;
        }
    }
}
