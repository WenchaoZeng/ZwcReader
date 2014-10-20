using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace ZwcBookMaker
{
    public class BookPackager
    {
        public static void PackageBook(string pageFolder, int totalPageCount)
        {
            MemoryStream header = new MemoryStream();
            MemoryStream body = new MemoryStream();

            int location = (totalPageCount +  2) * 4;
            WriteInt(header, 0);
            for (int pageIndex = 1; pageIndex <= totalPageCount; ++pageIndex)
            {
                string pageFilePath = Path.Combine(pageFolder, string.Format("{0:D4}.gif", pageIndex));
                var content = File.ReadAllBytes(pageFilePath);

                WriteInt(header, location);
                WriteBytes(body, content);

                location += content.Length;
            }

            WriteInt(header, location);

            body.Seek(0, SeekOrigin.Begin);
            body.CopyTo(header);

            var bookPackage = header.ToArray();

            string bookPath = pageFolder + ".zwc_data";
            File.WriteAllBytes(bookPath, bookPackage);
        }

        static void WriteBytes(Stream stream, byte[] bytes)
        {
            stream.Write(bytes, 0, bytes.Length);
        }

        static void WriteInt(Stream stream, int value)
        {
            WriteBytes(stream, BitConverter.GetBytes(value));
        }
    }
}
