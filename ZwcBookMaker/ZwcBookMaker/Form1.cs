using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.Threading;
using Acrobat;
using System.IO;
using zwcHelper;

namespace ZwcBookMaker
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //new AcrobatTest().Run();
            Form1_DragLeave(null, null);
        }
        private void Form1_DragEnter(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.None;
            this.BackColor = Color.Gray;
            
            var file = GetFilePath(e);
            if (file != null)
            {
                e.Effect = DragDropEffects.Link;
                label1.Text = Path.GetFileName(file);
            }
        }
        private void Form1_DragLeave(object sender, EventArgs e)
        {
            this.BackColor = Color.White;
            label1.Text = "拖动PDF文件到这里开始生成电子书";
        }
        private void Form1_DragDrop(object sender, DragEventArgs e)
        {
            var file = GetFilePath(e);
            if (file == null)
            {
                Form1_DragLeave(null, null);
                return;
            }

            label1.Text = "开始生成";

            backgroundWorker1.RunWorkerAsync(file);
        }

        string GetFilePath(DragEventArgs e)
        {
            var files = (string[])e.Data.GetData(DataFormats.FileDrop);
            if (files.Length == 1)
            {
                string path = files[0];
                string extension = Path.GetExtension(path);
                if (extension.ToLower() == ".pdf")
                {
                    return path;
                }
            }

            return null;
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            string file = (string)e.Argument;

            string pageFolder = Path.Combine(Path.GetDirectoryName(file), Path.GetFileNameWithoutExtension(file));
            if (!Directory.Exists(pageFolder))
            {
                Directory.CreateDirectory(pageFolder);
            }

            Action<Action> invokeAction = (action) =>
            {
                this.Invoke(action);
            };

            using (var pdfReader = new AcrobatPDFReader(file, invokeAction))
            {
                int totalPageCount = pdfReader.GetPageCount();
                int renderedPageCount = 0;
                PageOutPutter outPutter = new PageOutPutter(pageFolder);

                while (renderedPageCount < totalPageCount && !e.Cancel)
                {
                    Bitmap page = pdfReader.RenderPage(renderedPageCount);

                    //string pagePath = Path.Combine(pageFolder, renderedPageCount.ToString() + ".png");
                    //page.Save(pagePath, ImageFormat.Png);

                    outPutter.AddPage(page);

                    ++renderedPageCount;

                    string progress = string.Format("{0} / {1}", renderedPageCount, totalPageCount);
                    backgroundWorker1.ReportProgress(0, progress);
                }

                outPutter.Flush();

                SettingsProvider settingsProvider = new SettingsProvider();
                settingsProvider["TotalPages"] = outPutter.GetOutputPageCount().ToString();
                settingsProvider["CurrentPage"] = "1";
                settingsProvider.SaveSettings(pageFolder + ".zwc");

                BookPackager.PackageBook(pageFolder, outPutter.GetOutputPageCount());

                backgroundWorker1.ReportProgress(0, "Done");
            }
        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            label1.Text = (string)e.UserState;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            backgroundWorker1.CancelAsync();
        }
    }
}
