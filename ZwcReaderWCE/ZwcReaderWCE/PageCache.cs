using System;

using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.IO;
using System.Threading;

namespace ZwcReaderWCE
{
    public class PageCache
    {
        Timer timer;

        int totalPages;
        string pageFolder = null;
        int currentPageIndex;

        object cacheLock = new object();
        Dictionary<int, Bitmap> cachePages = new Dictionary<int, Bitmap>();

        FileStream bookPackage = null;

        public PageCache(string pageFolder, int totalPages)
        {
            string packagePath = pageFolder + ".zwc_data";
            if (File.Exists(packagePath))
            {
                bookPackage = File.Open(packagePath, FileMode.Open, FileAccess.Read);
            }

            this.totalPages = totalPages;
            this.pageFolder = pageFolder;
        }

        public Bitmap GetPage(int index)
        {
            lock (cacheLock)
            {
                // Get page from cache or file
                Bitmap page = GetPageFromCacheOrFile(index);

                // Refresh timer for caching pages in background thread.
                if (currentPageIndex != index)
                {
                    currentPageIndex = index;
                    RefreshTimer();
                }

                return page;
            }
        }

        void RefreshTimer()
        {
            if (this.timer != null)
            {
                this.timer.Dispose();
            }

            this.timer = new Timer(this.CachingPages, null, 500, Timeout.Infinite);
        }

        void CachingPages(object state)
        {
            lock (cacheLock)
            {
                GetPageFromCacheOrFile(currentPageIndex - 1);
                GetPageFromCacheOrFile(currentPageIndex + 1);
                ReleasePages();
            }
        }

        void ReleasePages()
        {
            int[] keys = new int[cachePages.Keys.Count];
            cachePages.Keys.CopyTo(keys, 0);

            foreach (int key in keys)
            {
                if (key < currentPageIndex - 1 || key > currentPageIndex + 1)
                {
                    cachePages[key].Dispose();
                    cachePages.Remove(key);
                }
            }
        }

        Bitmap GetPageFromCacheOrFile(int index)
        {
            if (cachePages.ContainsKey(index))
            {
                return cachePages[index];
            }

            var page = LoadPageFromFile(index);
            if (page != null)
            {
                cachePages[index] = page;
            }

            return page;
        }

        Bitmap LoadPageFromFile(int index)
        {
            // Load page from book package.
            if (bookPackage != null)
            {
                if (index < 1 || index > totalPages)
                {
                    return null;
                }

                bookPackage.Seek(index * 4, SeekOrigin.Begin);
                int pageOffset = ReadInt(bookPackage);
                int nextPageOffset = ReadInt(bookPackage);
                int pageSize = nextPageOffset - pageOffset;

                bookPackage.Seek(pageOffset, SeekOrigin.Begin);
                byte[] bookContent = new byte[pageSize];
                bookPackage.Read(bookContent, 0, pageSize);

                return new Bitmap(new MemoryStream(bookContent));
            }

            // Load from gif file.
            string filePath = Path.Combine(pageFolder, string.Format("{0:D4}.gif", index));
            if (File.Exists(filePath))
            {
                using (FileStream fileStream = File.Open(filePath, FileMode.Open, FileAccess.Read))
                {
                    return new Bitmap(fileStream);
                }
            }

            return null;
        }

        int ReadInt(Stream stream)
        {
            byte[] bytes = new byte[4];
            stream.Read(bytes, 0, bytes.Length);
            return BitConverter.ToInt32(bytes, 0);
        }
    }
}