//Create by zwc email:zwc1986@126.com
//last modified by zwc at 2008-8-9 16:32:44


using System;
using System.Collections.Generic;
using System.Text;

using System.IO;
using System.Windows.Forms;

namespace zwcHelper
{
    /// <summary>
    /// 用于将变量保存到文本文件和从文本文件读取变量
    /// </summary>
    class SettingsProvider
    {
        /// <summary>
        /// 
        /// </summary>
        private Dictionary<string, string> m_Items;

        /// <summary>
        /// 
        /// </summary>
        public SettingsProvider()
        {
            m_Items = new Dictionary<string, string>();
        }

        /// <summary>
        /// 从文本文件中读取变量,文本的编码必须是utf-8
        /// </summary>
        /// <param name="FilePath">将要读取的文件的绝对路径</param>
        /// <returns></returns>
        public void LoadSettings(string FilePath)
        {
            if (File.Exists(FilePath))
            {
                StreamReader rd = File.OpenText(FilePath);
                while (!rd.EndOfStream)
                {
                    string line = rd.ReadLine();
                    if (line.Trim() == "" || line[0] == ';')//注释和空行
                    {
                        continue;
                    }
                    else
                    {
                        int i = line.IndexOf("=");
                        string key = line.Substring(0, i).Trim();
                        string value = line.Substring(i + 1).Trim();
                        m_Items.Add(key, value);
                    }
                }
                rd.Close();
            }
            else
            {
                m_Items.Clear();
            }
        }

        /// <summary>
        /// 将变量存储到文本文件中,utf-8编码
        /// </summary>
        /// <param name="FilePath">将要保存的文件的绝对路径</param>
        public void SaveSettings(string FilePath)
        {
            StreamWriter wr = File.CreateText(FilePath);
            wr.WriteLine(";Create at " + DateTime.Now.ToString());
            wr.WriteLine("");
            foreach (string key in m_Items.Keys)
            {
                wr.WriteLine(key + " = " + m_Items[key]);
            }
            wr.Close();
        }

        /// <summary>
        /// 保存着所有的变量
        /// </summary>
        public Dictionary<string, string> Items
        {
            get
            {
                return m_Items;
            }
            set
            {
                m_Items = value;
            }
        }

        /// <summary>
        /// 获取或设置一个变量
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        public string this[string key]
        {
            get
            {
                if (m_Items.ContainsKey(key))
                {
                    return m_Items[key];
                }
                else
                {
                    return null;
                }
            }
            set
            {
                m_Items[key] = value;
            }
        }

        /// <summary>
        /// 添加一个变量
        /// </summary>
        /// <param name="name">变量名字</param>
        /// <param name="value">变量的值</param>
        public void AppendItem(string key, string value)
        {
            m_Items[key] = value;
        }

        public string GetItem(string key)
        {
            return this[key];
        }
    }
    
}
