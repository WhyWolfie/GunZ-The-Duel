using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Xml.XPath;
using System.IO;
using System.Text.RegularExpressions;

namespace Gunz_Tool
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        String Dict;
        private String stringsparser(String Name, String dictionary)
        {
            XmlReader reader = XmlReader.Create(dictionary);
            String name= "";
            while (reader.Read())
            {
                name = reader.GetAttribute(Name);
            }
            return name;
        }
        private void zitemparser(String dictionary)
        {
            richTextBox1.AppendText("<?xml version=" + a.Text + "1.0" + a.Text + "encoding=" + a.Text + "UTF-8" + a.Text + "?>" + Environment.NewLine + "<XML id=" + a.Text + "shop" + a.Text + ">" + Environment.NewLine);
            XmlReader reader = XmlReader.Create(dictionary);
            int i = 0;
            while (reader.Read())
            {
                if (reader.Name.Equals("ITEM"))
                {
                    String line = "<SELL itemid=" + a.Text;
                    int id = Convert.ToInt32(reader.GetAttribute("id"));
                    line += id + a.Text + "/> <!--";
                    String name = reader.GetAttribute("name");
                    name = Regex.Replace(name, "STR:", "");
                    name += a.Text;
                    if (reader.GetAttribute("name").Contains("STR:ZITEM_NAME_"))
                    {
                                    StreamReader file = null;
                                    String line1;
                                    file = new StreamReader(Dict + "Strings.xml");
                                    try
                                    {
                                        while ((line1 = file.ReadLine()) != null)
                                        {
                                            if (Regex.IsMatch(line1, name))
                                            {
                                                String temp = Regex.Replace(line1, name, "");
                                                temp = Regex.Replace(temp, "<", "");
                                                temp = Regex.Replace(temp, ">", "");
                                                temp = Regex.Replace(temp, "/", "");
                                                temp = Regex.Replace(temp, a.Text, "");
                                                temp = Regex.Replace(temp, "id", "");
                                                temp = Regex.Replace(temp, "=", "");
                                                temp = Regex.Replace(temp, "STR", "");
                                                line += temp + "-->";
                                            }
                                        }
                                    }
                                    finally
                                    {
                                        if (file != null)
                                            file.Close();
                                    }
                    } else {
                        line += reader.GetAttribute("name") + a.Text + "-->";
                    }
                    if (!line.Contains("-->"))
                    {
                        line += "Not Found -->";
                    }
                    richTextBox1.AppendText(line + Environment.NewLine);
                    i++;
                }
            }
            richTextBox1.AppendText("</XML>");
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.Clear();
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                Dict = Path.GetDirectoryName(openFileDialog1.FileName) + "\\";
                zitemparser(openFileDialog1.FileName);
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFile1 = new SaveFileDialog();
            saveFile1.DefaultExt = "shop.xml";
            saveFile1.Filter = "Shop|shop.xml";
            saveFile1.FileName = "shop.xml";
            if (saveFile1.ShowDialog() == DialogResult.OK)
            {
                if (File.Exists(saveFile1.FileName))
                {
                    File.Delete(saveFile1.FileName);
                }
                richTextBox1.SaveFile(saveFile1.FileName, RichTextBoxStreamType.PlainText);
            }

        }
        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
