#include "stdafx.h"
#include "ZAntiHack.h"


DWORD WINAPI AntiMem()
{
	//	SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_BEGIN);
	CRITICAL_SECTION m_cs;
	InitializeCriticalSection(&m_cs);
	EnterCriticalSection(&m_cs);
	unsigned long Start = (unsigned long)GetModuleHandle(NULL) + 0x1000;
	unsigned long End = Start + 0x34d3f9;
	int cnt = 0, cnt2 = 0;
	unsigned long EndAddy = 0;
	bool foundend = false;
	for (unsigned long s = Start; s <= End; s++)
	{
		unsigned char n = *((unsigned char*)s);
		if (n >= 0x00 && n <= 0xff) cnt++;
		if (n == 0x00) cnt2++; else cnt2 = 0;
		if (cnt2 >= 16 && foundend == false)
		{
			EndAddy = s - Start;
			foundend = true;
		}
	}
	PBYTE Mem = new BYTE[EndAddy];
	memcpy(Mem, (LPVOID)Start, EndAddy);
	unsigned long int TimeTest1 = 0, TimeTest2 = 0;
	LeaveCriticalSection(&m_cs);
	while (true)
	{
		EnterCriticalSection(&m_cs);
		if (memcmp(Mem, (LPVOID)Start, EndAddy) != 0)
		{
			//mlog(MemoryBreak);
			//ZApplication::GetGameInterface()->ShowMessage(MemoryBreakMsg);
			ZPostDisconnect();
			FatalExit(-1);
		}
		TimeTest1 = TimeTest2;
		TimeTest2 = timeGetTime();
		if (TimeTest1 != 0)
		{
			if ((TimeTest2 - TimeTest1) > 110000)
			{
				//ZApplication::GetGameInterface()->ShowMessage(MemoryBreakMsg);
				ZPostDisconnect();
				FatalExit(-1);
			}
		}
		LeaveCriticalSection(&m_cs);
		Sleep(24000);
	}
	//	SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_END);
}