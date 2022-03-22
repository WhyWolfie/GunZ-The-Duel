using System;
using System.Runtime.InteropServices;

namespace Launcher
{
	public static class NativeMethods
	{
		[DllImport("kernel32.dll")]
		public static extern bool FreeLibrary(IntPtr hModule);

		[DllImport("kernel32.dll")]
		public static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);

		[DllImport("kernel32.dll", SetLastError = true)]
		public static extern IntPtr LoadLibrary(string dllToLoad);

		[DllImport("kernel32.dll")]
		public static extern int FormatMessage(int dwFlags, int lpSource, int dwMessageId, int dwLanguageId, ref string lpBuffer, int nSize, int Arguments);

		public static string GetErrorMessage(int errorCode)
		{
			int num = 256;
			int num2 = 512;
			int num3 = 4096;
			int nSize = 255;
			string lpBuffer = "";
			int dwFlags = num | num3 | num2;
			int num4 = FormatMessage(dwFlags, 0, errorCode, 0, ref lpBuffer, nSize, 0);
			if (0 == num4)
			{
				return null;
			}
			return lpBuffer;
		}
	}
}
