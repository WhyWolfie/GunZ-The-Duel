<b>Basic Anti-Hack</b> <br>
You must create a .cpp and .header

You can explore a lot more of that there and with you. Good luck. 

ZAntiHack.cpp

    #include "stdafx.h"
    #include "ZAntiHack.h"

    bool IsAddressHooked(unsigned long address){
        BYTE* offsetValue = (BYTE*)address;
        return (*offsetValue == 0xE8 || *offsetValue == 0xE9 || *offsetValue == 0x7E || *offsetValue == 0x74 || *offsetValue == 0xC3);
    }

    void Main(void*)
    {
      SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);
      DWORD getTickCount = (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetTickCount");
      DWORD queryPerformanceCounter = (DWORD)GetProcAddress(GetModuleHandleA("kernel32.dll"), "QueryPerformanceCounter");
      while(1)
      {
       Sleep(RandomNumber(5000, 7000));
       if (IsAddressHooked(getTickCount) || IsAddressHooked(queryPerformanceCounter) || GetModuleHandleA("hook.dll") != NULL)
       {
         ExitProcess(NULL);
       }
      }
    }
    
ZAntiHack.h

    extern void Main(void*);

main.cpp

    (HANDLE)_beginthread(Main, 0, 0);
