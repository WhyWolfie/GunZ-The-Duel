#include <Windows.h>

bool IsAddressHooked(unsigned long address)
{
	BYTE* offsetValue = (BYTE*)address;
	return (*offsetValue == 0xE8 || *offsetValue == 0xE9 || *offsetValue == 0x7E || *offsetValue == 0x74 || *offsetValue == 0xFF);
}

void ZProtect28()
{
	DWORD getTickCount = (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetTickCount");
	DWORD queryPerformanceCounter = (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "QueryPerformanceCounter");

	while (true)
	{
		if (IsAddressHooked(getTickCount) || IsAddressHooked(queryPerformanceCounter) || 
			GetModuleHandleA("shotbot.dll") || 
			GetModuleHandleA("Craig's (Beast) ESP.dll") || 
			GetModuleHandleA("NKR Universal.Shottie.dll") || 
			GetModuleHandleA("shellapi.dll") || 
			GetModuleHandleA("newk.dll") || 
			GetModuleHandleA("WallHack_3.dll") || 
			GetModuleHandleA("WallHack_2.dll") || 
			GetModuleHandleA("WallHack_1.dll") || 
			GetModuleHandleA("Tm.dll") ||
			GetModuleHandleA("Acorn (3).dll") ||
			GetModuleHandleA("Craigs (Beast) ESP.dll") ||
			GetModuleHandleA("fxpdll.dll") ||
			GetModuleHandleA("SB32bit.dll") ||
			GetModuleHandleA("SB64bit.dll") ||
			GetModuleHandleA("WallHack_1.dll") ||
			GetModuleHandleA("Wall Hack ByEvilgamerz.dll") || 
			GetModuleHandleA("SpeedHack.dll") != NULL)
		{
			mlog("Error Initialization Client : 487\n");
			//MessageBox(NULL, "The application could not start successfully (0xc012547b). Click OK to close it.", NULL, MB_OK | MB_ICONERROR);
			FatalExit(-1);
		}
		Sleep(0);
	}
}