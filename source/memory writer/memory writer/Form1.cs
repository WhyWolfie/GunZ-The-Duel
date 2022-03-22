using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.IO;
using System.Management;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Globalization;

namespace Memory_Writer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        [DllImport("USER32.DLL")]
        public static extern IntPtr FindWindow( string lpClassName, string lpWindowName); 
        [DllImport("user32.dll", SetLastError = true)]
        static extern uint GetWindowThreadProcessId(IntPtr hWnd,out uint lpdwProcessId);
        [DllImport("kernel32.dll")]
        static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, UIntPtr nSize, out IntPtr lpNumberOfBytesWritten);
        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(UInt32 dwDesiredAccess, Int32 bInheritHandle, UInt32 dwProcessId);
        [DllImport("Kernel32.dll")]
        public static extern bool ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, UIntPtr nSize, out IntPtr lpNumberOfBytesWritten);


        private void Form1_Load(object sender, EventArgs e)
        {
            Process[] processlist = Process.GetProcesses();
            foreach (Process process in processlist)
            {
                if (!String.IsNullOrEmpty(process.MainWindowTitle))
                {
                    ListViewItem item = new ListViewItem(process.MainWindowTitle);
                    item.SubItems.Add(process.MainWindowTitle);
                    item.Tag = process;
                    listView1.Items.Add(item);
                }
            }
        }

        private void listView1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            var selectedItems = listView1.SelectedItems;
            foreach (ListViewItem selectedItem in selectedItems)
            {
                textBox1.Text = selectedItem.Text.ToString();
            }
        }

        private void button1_Click(object sender, System.EventArgs e)
        {
            listView1.Clear();
            Process[] processlist = Process.GetProcesses();
            foreach (Process process in processlist)
            {
                if (!String.IsNullOrEmpty(process.MainWindowTitle))
                {
                    ListViewItem item = new ListViewItem(process.MainWindowTitle);
                    item.SubItems.Add(process.MainWindowTitle);
                    item.Tag = process;
                    listView1.Items.Add(item);
                }
            }
        }
        public Int32 GetProcessId(String proc)
        {
            Process[] ProcList;
            ProcList = Process.GetProcessesByName(proc);
            return ProcList[0].Id;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (textBox1.Text.Trim().Length == 0)
            {
                MessageBox.Show("Couldn't find window target", "Error");
                return;
            }
            if (textBox2.Text.Trim().Length == 0)
            {
                MessageBox.Show("Empty Address", "Error");
                return;
            }
            if (textBox3.Text.Trim().Length == 0)
            {
                MessageBox.Show("Empty Bytes", "Error");
                return;
            }

            UInt32 ProcID; IntPtr bytesout;
            
            IntPtr WindowHandle = FindWindow(null, textBox1.Text.ToString());
            if (WindowHandle == null)
            {
                MessageBox.Show("Window handle seems to be offline", "Error");
                return;
            }

            string hex = textBox2.Text.ToString();
            long ptr = Convert.ToInt64(hex, 16);
            IntPtr newPtr = new IntPtr(ptr);

            string hexbytes = textBox3.Text.ToString();
            long ptrbytes = Convert.ToInt64(hexbytes, 16);

            GetWindowThreadProcessId(WindowHandle, out ProcID);
            IntPtr ProcessHandle = OpenProcess(0x1F0FFF, 1, ProcID);

            byte [] NewVal = {0x11, 0x11};

            WriteProcessMemory(ProcessHandle, (IntPtr)newPtr, BitConverter.GetBytes(NewVal[1]), (UIntPtr)1, out bytesout); 
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (textBox1.Text.Trim().Length == 0)
                return;

            MessageBox.Show(textBox1.Text.ToString(), "Full window name");
        }

        private void textBox3_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != '.')
            {
                e.Handled = true;
            }

            if (e.KeyChar == '.' && (sender as TextBox).Text.IndexOf('.') > -1)
            {
                e.Handled = true;
            }
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                MessageBox.Show("©Copyright 2013 ,\nCoded By George Qupty.\nPowered By GeorgeNetworks.", "©Copyright 2013 - GeorgeNetworks");
            }
        }

    }
}
