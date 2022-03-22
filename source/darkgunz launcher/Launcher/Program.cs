using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace Launcher
{
	internal static class Program
	{
		[STAThread]
		private static void Main()
		{
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(defaultValue: true);
			try
			{
				Application.Run(new MainForm());
			}
			catch (Exception ex)
			{
				DG.Log("Main(2)", ex);
				DG.Dispose();
				string message = ex.Message;
				MessageBox.Show("Unhandled exception: " + message + Environment.NewLine + "Trace: " + ex.StackTrace + Environment.NewLine + "Source: " + ex.Source);
			}
			DG.Dispose();
		}

		public static void Exit()
		{
			try
			{
				DG.Dispose();
			}
			catch
			{
			}
			Process.GetCurrentProcess().Kill();
		}
	}
}
