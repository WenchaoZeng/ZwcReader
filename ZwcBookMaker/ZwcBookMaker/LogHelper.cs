/// Author : 曾文超
/// Create Date : 2009年7月24日

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace Glassesol.Common
{
    /// <summary>
    /// 日志生成类, 用于格式话编写日志文件
    /// </summary>
    public class LogHelper
    {
        /// <summary>
        /// 获得日志目录
        /// 修改：
        /// time:2009年9月4日13:51:17
        /// ahthor:XL
        /// </summary>
        public string LogPath
        {
            get
            {
                return _dir;
            }
        }
        /// <summary>
        /// 用于保存日志的目录
        /// </summary>
        private string _dir;

        /// <summary>
        /// 构造一个日志生成类
        /// </summary>
        /// <param name="dir">用于保存日志的目录, 后面不加 '/' 或 '\' </param>
        public LogHelper(string dir)
        {
            Directory.CreateDirectory(dir);
            _dir = dir;
        }

        /// <summary>
        /// 写日志信息到日志文件中
        /// </summary>
        /// <param name="msg">将要写入的信息内容,类会格式化它的显示</param>
        public void WriteLog(string msg)
        {
            // 创建日志内容
            StringBuilder builder = new StringBuilder();
            builder.AppendLine("[" + DateTime.Now.ToString() + "]");
            builder.AppendLine(string.IsNullOrEmpty(msg) ? "There is no message !" : msg);
            builder.AppendLine(); // 用一个空行分割每个单独的日志事件

            // 写入日志文件
            string filePath = _dir + "/" + DateTime.Now.ToString("yyyy_MM_dd") + ".txt";
            File.AppendAllText(filePath, builder.ToString(), Encoding.UTF8);
        }
    }
}
