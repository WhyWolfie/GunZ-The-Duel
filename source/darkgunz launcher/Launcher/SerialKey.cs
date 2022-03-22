using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Launcher
{
	internal class SerialKey
	{
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate bool MakeSerialKey();

		public static bool Create()
		{
			IntPtr intPtr = NativeMethods.LoadLibrary("SKGen.dll");
			if (intPtr != IntPtr.Zero)
			{
				IntPtr procAddress = NativeMethods.GetProcAddress(intPtr, "MakeSerialKey");
				bool result = ((MakeSerialKey)Marshal.GetDelegateForFunctionPointer(procAddress, typeof(MakeSerialKey)))();
				NativeMethods.FreeLibrary(intPtr);
				return result;
			}
			MessageBox.Show(NativeMethods.GetErrorMessage(Marshal.GetLastWin32Error()));
			return false;
		}
	}
}
