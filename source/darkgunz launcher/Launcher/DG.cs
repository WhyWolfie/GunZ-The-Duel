using System;
using System.IO;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Launcher
{
	public class DG
	{
		public static FileInfo LogFile;

		public static FileStream LogStream;

		public static bool WFLoaded;

		private static bool busy;

		static DG()
		{
			WFLoaded = false;
			busy = false;
			int num = -1;
			while (true)
			{
				try
				{
					if (num != -1)
					{
						LogFile = new FileInfo("DGLauncher" + num + ".log");
					}
					else
					{
						LogFile = new FileInfo("DGLauncher.log");
					}
					LogStream = LogFile.Open(FileMode.OpenOrCreate, FileAccess.ReadWrite);
					Log("File stream initialized.");
					return;
				}
				catch (Exception ex)
				{
					num++;
					if (num == 10)
					{
						MessageBox.Show("Failed to create usable log file.  The launcher will continue to work correctly without logs.  Please submit a picture of this window to DarK GunZ Staff for debugging.\n\nLast error: " + ex.Message + Environment.NewLine + Environment.NewLine + "Source: " + ex.Source, "Log Error");
						return;
					}
				}
			}
		}

		public static void Log(string text)
		{
			int num = 0;
			string text2 = "";
			while (true)
			{
				try
				{
					while (busy)
					{
						Thread.Sleep(2);
					}
					busy = true;
					text2 = $"{Timestamp()}{text}{Environment.NewLine}";
					byte[] bytes = Encoding.ASCII.GetBytes(text2);
					LogStream.Write(bytes, 0, bytes.Length);
					busy = false;
					return;
				}
				catch (Exception)
				{
					if (num >= 10)
					{
						try
						{
							File.WriteAllText(LogFile.FullName, File.ReadAllText(LogFile.FullName) + text2);
						}
						catch
						{
						}
						return;
					}
					num++;
				}
			}
		}

		public static string Timestamp()
		{
			return Timestamp(0);
		}

		public static string Timestamp(int level)
		{
			string result = "";
			DateTime now = DateTime.Now;
			TimeSpan timeOfDay = now.TimeOfDay;
			string text = now.ToString();
			string text2 = text.Split(' ')[0];
			string text3 = text.Substring(text2.Length + 1);
			switch (level)
			{
			case 0:
				result = $"[{text}] ";
				break;
			case 1:
				result = $"[{now.DayOfWeek} {text}] ";
				break;
			}
			return result;
		}

		internal static void Log(string location, Exception E)
		{
			Log(Environment.NewLine + "==========EXCEPTION==========" + Environment.NewLine + "Unhandled exception at " + location + Environment.NewLine + "MSG:" + E.Message + Environment.NewLine + "Trace: " + E.StackTrace + Environment.NewLine + "Source: " + E.Source + Environment.NewLine + "==============END==============");
		}

		internal static void Dispose()
		{
			try
			{
				Log("Logger::Dispose called.  Flushing and closing file stream.");
				LogStream.Flush();
				LogStream.Close();
			}
			catch
			{
			}
			finally
			{
				if (LogStream != null)
				{
					LogStream.Dispose();
				}
			}
		}

		public static string ShortenBytes(long Bytes)
		{
			if (Bytes < 0)
			{
				Bytes *= -1;
			}
			string[] array = new string[9]
			{
				"B",
				"KB",
				"MB",
				"GB",
				"TB",
				"PB",
				"EB",
				"ZB",
				"YB"
			};
			float num = Bytes;
			int num2 = 0;
			while (num > 1024f)
			{
				num /= 1024f;
				num2++;
			}
			return num.ToString("###.00 ") + array[num2];
		}

		public static string[] FindInstancesOf(string Text, string SearchString)
		{
			string str = SearchString;
			str += "=\"";
			string value = "\";";
			int num = Text.IndexOf(str);
			if (num == -1)
			{
				throw new Exception("Syntax error.");
			}
			num += str.Length;
			int num2 = Text.IndexOf(value, num);
			string text = "";
			while (num != -1)
			{
				text = text + Text.Substring(num, num2 - num) + ",";
				num = Text.IndexOf(str, num2 - 1);
				if (num == -1)
				{
					text = text.Remove(text.LastIndexOf(','));
					break;
				}
				num += str.Length;
				num2 = Text.IndexOf(value, num);
			}
			return text.Split(',');
		}
	}
}
