Hi there, well I am sharing a simple hooking check and OC & UC detecting example with this function. <br>
*Make sure the OC & UC scan is only against softwares, like xSpeed and etc. (Not Hardware detect) <br>

    DWORD getDwordFromBytes(byte *b)
    {
      return (b[0]) | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
    }

    void GetModulePos(DWORD dwAddr)
    {
      HMODULE hMods[1024];
      DWORD cbNeeded;
      unsigned int i;
      TCHAR szModName[MAX_PATH];
      HANDLE hMyHandle = GetCurrentProcess();

      if (EnumProcessModules(hMyHandle, hMods, sizeof(hMods), &cbNeeded))
      {
        for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
        {
          MODULEINFO mi;
          //Get Module Information
          GetModuleInformation(hMyHandle, hMods[i], &mi, sizeof(mi));
          if ((DWORD)mi.lpBaseOfDll <= dwAddr && dwAddr <= ((DWORD)mi.lpBaseOfDll + mi.SizeOfImage))
          {
            // Get the full path to the module's file.

            if (GetModuleFileNameEx(hMyHandle, hMods[i], szModName,
              sizeof(szModName) / sizeof(TCHAR)))
            {
              // Print the module name and handle value.				
              break;
            }
          }
        }
      }
    }
    bool IsHooked(BYTE* pbtArray, DWORD dwAddress)
    {
      DWORD dwJmpAddr = 0;
      BYTE btJmp[4];
      for (int i = 0; i < 7; i++)
      {
        if (pbtArray[i] == 0xE9)
        {
          btJmp[0] = pbtArray[i + 1];
          btJmp[1] = pbtArray[i + 2];
          btJmp[2] = pbtArray[i + 3];
          btJmp[3] = pbtArray[i + 4];
          dwJmpAddr = getDwordFromBytes(btJmp);
          if (dwJmpAddr>0x80000000)
          {
            dwJmpAddr = 0xFFFFFFFF - dwJmpAddr + 1;
          }
          dwJmpAddr = dwAddress + i + 4 - dwJmpAddr;
          break;
        }
      }
      if (dwJmpAddr)
      {
        GetModulePos(dwJmpAddr);
        return true;
      }
      return false;
    }
    
Part 2
    
    HMODULE hKenlDll = GetModuleHandleA("kernel32.dll");
    DWORD dwAddr = (DWORD)GetProcAddress(hKenlDll, "GetTickCount");

    BYTE curTick[7];
    memcpy(curTick, (LPVOID)dwAddr, 7);
    if (IsHooked(curTick, dwAddr))
    {
     //Your crash
     //Don't be stupid and use ExitProcess or any Windows API function.
     //make your own crash code.
    }

    dwAddr = (DWORD)GetProcAddress(hKenlDll, "QueryPerformanceCounter"); //Please encrypt QueryPerformanceCounter string
    memcpy(curTick, (LPVOID)dwAddr, 7);
    if (IsHooked(curTick, dwAddr))
    {
     //Your crash
     //Don't be stupid and use ExitProcess or any Windows API function.
     //make your own crash code.
    }
    
    
Thanks too Sahar042
    
