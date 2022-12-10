#include "stdafx.h"
#ifndef _PLAYGUNZ
Lenguando que y apenas una parte mejorada del antihacker no finalizado.
Esto es algo privado y no debe compartir a nadie.
Se agregará en breve protección MD5
Actualizado por Orby.
#endif

/// PlayGunZ: <PlayProtect>
/*
__forceinline void KillPlay()
{
	ExitProcess(0);
}

bool IsAddressHooked(unsigned long address)
{

	BYTE* offsetValue = (BYTE*)address;
	return (*offsetValue == 0xE8 || *offsetValue == 0xE9 || *offsetValue == 0x7E || *offsetValue == 0x74);

}

void PlayProtect()
{
	DWORD getTickCount = (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetTickCount");
	DWORD timeGetTime = (DWORD)GetProcAddress(GetModuleHandleA("Winmm.dll"), "timeGetTime");
	DWORD timeSetEventTime = (DWORD)GetProcAddress(GetModuleHandleA("Winmm.dll"), "timeSetEvent");
	DWORD queryPerformanceCounter = (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "QueryPerformanceCounter");
	DWORD sendAddress = (DWORD)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "send");
	DWORD recvAddress = (DWORD)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "recv");
	DWORD sendToAddress = (DWORD)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "sendto");
	DWORD recvFromAddress = (DWORD)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "recvfrom");
	DWORD setTimerAddress = (DWORD)GetProcAddress(GetModuleHandleA("user32.dll"), "SetTimer");

	while (true)
	{
		if (getTickCount != (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetTickCount") ||
			timeGetTime != (DWORD)GetProcAddress(GetModuleHandleA("Winmm.dll"), "timeGetTime") ||
			timeSetEventTime != (DWORD)GetProcAddress(GetModuleHandleA("Winmm.dll"), "timeSetEvent") ||
			queryPerformanceCounter != (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "QueryPerformanceCounter") ||
			sendAddress != (DWORD)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "send") ||
			recvAddress != (DWORD)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "recv") ||
			sendToAddress != (DWORD)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "sendto") ||
			recvFromAddress != (DWORD)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "recvfrom"))
		{
			MLog("0");
			KillPlay();
		}

		if (IsAddressHooked(timeSetEventTime) 
			|| IsAddressHooked(setTimerAddress) 
			|| IsAddressHooked(getTickCount) 
			|| IsAddressHooked(queryPerformanceCounter) 
			|| GetModuleHandleA("Hook.dll") != NULL 
			|| GetModuleHandleA("SpeedHack.dll") != NULL 
			|| GetModuleHandleA("softsp.dll") != NULL 
			|| GetModuleHandleA("MyHookDll.dll") != NULL 
			|| IsAddressHooked(sendAddress) 
			|| IsAddressHooked(recvAddress)
			|| IsAddressHooked(sendToAddress) 
			|| IsAddressHooked(recvFromAddress))
		{
			MLog("1");
			KillPlay();
		}

		Sleep(3000);
	}
}

/// PlayGunZ: <AntiSB>
HHOOK MouseHook;

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	return CallNextHookEx(MouseHook, nCode, wParam, lParam);
	if (nCode == HC_ACTION)
	{
		if (wParam == WM_RBUTTONDOWN || wParam == WM_LBUTTONDOWN)
		{
			MSLLHOOKSTRUCT *info = (MSLLHOOKSTRUCT*)lParam;
			if ((info->flags & LLMHF_INJECTED) == LLMHF_INJECTED)
			{
				ExitProcess(-1);
			}
		}
	}

	return CallNextHookEx(MouseHook, nCode, wParam, lParam);
}

void AntiShotbotLogger()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	MouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, hInstance, NULL);
	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) 
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(MouseHook);
	return;
}
*/
#ifndef _PLAYGUNZ
Protección MD5 y no para la edición de archivos de PlayGunZ.
Se agregará la base MD5Wrapper y MD5.
#endif
void MD5Check()
{
	/// <En breve se añadirá.>
}