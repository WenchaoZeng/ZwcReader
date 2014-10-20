using System;

using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.IO;
using zwcHelper;

namespace ZwcReaderWCE
{
    public partial class Form1 : Form
    {
        string configFile
        {
            get
            {
                return IsPC() ? "D:\\ZwcReaderWCE.config" : @"\Storage Card\ZwcReaderWCE.config";
            }
        }

        Rectangle rect = new Rectangle(0, 0, 600, 800);
        Graphics graphics;

        bool isBookOpened = false;
        PageCache cache;

        string filePath = null;
        int totalPages;
        int currentPage;
        SettingsProvider settingProvider = null;

        public Form1()
        {
            InitializeComponent();

            //if (!IsPC())
            //{
            //    IntPtr hDlg;
            //    hDlg = WinAPI.FindWindow(null, "ZwcReaderWCE");
            //    MessageBox.Show(hDlg.ToInt32().ToString());
            //    //WinAPI.SetForegroundWindow(hDlg); 
            //}
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            try
            {
                switch (e.KeyCode)
                {
                    case Keys.D0:
                        Application.Exit();
                        break;
                    case Keys.PageDown:
                        PageDown();
                        break;
                    case Keys.PageUp:
                        PageUp();
                        break;
                    case Keys.D1:
                        UserOpenBook();
                        break;
                    case Keys.D9:
                        Test();
                        break;
                    case Keys.Enter:
                        ShowOrHideMenu();
                        break;
                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                if (IsPC())
                {
                    throw;
                }

                using (StreamWriter writer = File.AppendText(@"\Storage Card\log.txt"))
                {
                    writer.WriteLine(ex.ToString());
                }

                MessageBox.Show(ex.ToString());
                Application.Exit();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            graphics = this.CreateGraphics();

            // Auto load last open
            SettingsProvider appConfig = new SettingsProvider();
            appConfig.LoadSettings(configFile);
            string filePath = appConfig["open"];
            LoadBook(filePath);

            // Show menu
            label1.Visible = false;
            ShowOrHideMenu();
        }

        private void ShowOrHideMenu()
        {
            label1.Visible = !label1.Visible;
            label1.Text = string.Format(@"
0: 退出
1: 打开文件
9: 测试
回车: 显示或隐藏菜单

{0} / {1}
", currentPage, totalPages);
        }
        
        private void Test()
        {

        }

        private void UserOpenBook()
        {
            string filePath = null;
            if (IsPC())
            {
                filePath = @"D:\Desktop\ZwcBookMaker\大数据时代.zwc";
            }
            else
            {
                OpenFileDialog dialog = new OpenFileDialog();
                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    filePath = dialog.FileName;
                }
            }

            SettingsProvider appConfig = new SettingsProvider();
            appConfig["open"] = filePath;
            appConfig.SaveSettings(configFile);

            LoadBook(filePath);
        }

        void LoadBook(string filePath)
        {
            if (string.IsNullOrEmpty(filePath) || Path.GetExtension(filePath) != ".zwc")
            {
                return;
            }

            this.filePath = filePath;

            settingProvider = new SettingsProvider();
            settingProvider.LoadSettings(filePath);

            totalPages = int.Parse(settingProvider["TotalPages"]);
            currentPage = int.Parse(settingProvider["CurrentPage"]);
            string pageFolder = Path.Combine(Path.GetDirectoryName(filePath), Path.GetFileNameWithoutExtension(filePath));
            cache = new PageCache(pageFolder, totalPages);
            isBookOpened = true;
            DrawPage();
        }

        private void PageDown()
        {
            AddPageIndex(1);
        }

        public void PageUp()
        {
            AddPageIndex(-1);
        }

        void AddPageIndex(int count)
        {
            if (isBookOpened)
            {
                currentPage += count;
                if (currentPage > totalPages)
                {
                    currentPage = totalPages;
                }
                else if (currentPage < 1)
                {
                    currentPage = 1;
                }

                DrawPage();

                settingProvider["CurrentPage"] = currentPage.ToString();
                settingProvider.SaveSettings(filePath);
            }
        }

        private void DrawPage()
        {
            if (isBookOpened)
            {
                Bitmap bitmap = cache.GetPage(currentPage);
                graphics.DrawImage(bitmap, rect, rect, GraphicsUnit.Pixel);
            }
        }

        bool IsPC()
        {
            return File.Exists("pc");
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            DrawPage(); 
        }
    }
}