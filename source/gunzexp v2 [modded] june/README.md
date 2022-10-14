Since I noticed that the current GunzEXP v2 was telling your hp / ap in the public chat I decided to change that and make it tell you client sided.
GUNZ2830 for the original dll file.

Game room codes : <br>
[IA] = Infinite Ammo <br>
[SR] = Sword rocket <br>
[SN] = Show names <br>
[G] = gravity 25% <br>
[DM] = Disable Massive <br>
[IJ] = Infinite Jump <br>
[RB] = Reverse Berserker <br>
[FW] = Fast walk [150%] <br>

Ingame options : <br>
F9 = Shows your current hp & ap client sided. <br>


    #include <windows.h>
    #include <stdio.h>
    #include <string>

    using namespace std;

    // (GunZ) The Duel addresses for "Juny 13 2007".
    #define ROOMNAME						0x005084F0
    #define ROOMNAMECALL				0x0045B9F8
    #define ROOMNAMERETN			0x0045B9FD
    #define GETHP						0x00473730
    #define GETHPCALL					0x00405ED0
    #define GETHPRETN					0x00405ED7
    #define GETAP							0x00473740
    #define GETAPCALL						0x00405F5D
    #define GETAPRETN						0x00405F62
    #define RELOADBULLET			0x0047C44B
    #define RELOADBULLETRETN			0x0047C450
    #define GRAVITY					0x0047DBF8
    #define GRAVITYRETN					0x0047DBFE
    #define JUMPPOWER					0x004834BD
    #define JUMPPOWERRETN				0x004834C3
    #define WALKSPEED				0x0047463C
    #define GAMECREATE						0x004ABCE0
    #define GAMECREATECALL					0x004A9C80
    #define GAMECREATERETN					0x004A9C85
    #define GAMEDESTROY				0x0057112E
    #define GAMEDESTROYCALL			0x004A40A1
    #define GAMEDESTROYRETN			0x004A40A6
    #define ROCKETLAUNCHERSWORD1			0x004810F8
    #define ROCKETLAUNCHERSWORD2			0x0047E94D
    #define ROCKETLAUNCHERSWORD3			0x0049F316
    #define ROCKETLAUNCHERSWORD4			0x0049F38E
    #define ROCKETLAUNCHERSWORD5			0x0049F3A0
    #define ROCKETLAUNCHERSWORD6			0x0049F3C0
    #define CROSSHAIR					0x00406071
    #define HEADCHARNAME					0x0040A04C
    #define NOMASSIVE1					0x00480A49
    #define NOMASSIVE2					0x00480AF4
    #define NOMASSIVE3					0x00480B4A
    #define INFINITYJUMP					0x004833F2
    #define REVERSEBERSERKER1			0x004B3838
    #define REVERSEBERSERKER2			0x004B3893
    #define REVERSEBERSERKER3			0x004B38BA
    #define INGAMECHAT					0x004297F0
    #define INGAMETOSELFCHAT			0x0042A230
    #define DESTROYGUNZ				0x00497360
    #define DESTROYGUNZCALL			0x00495FB5
    #define DESTROYGUNZRETN			0x00495FBA
    #define Addr_ZChatOutput		0x0042A230  //0x00429E60


    // Initialize start.
    unsigned long ulOldProtect;

    bool InGameCheck = false, BulletBool = false, GravityBool = false, JumpPowerBool = false, WalkSpeedBool = false, 
    RLCheck = false, NHCheck = false, NMCheck = false, RBCheck = false, LiveClientCheck = false;

    int MyHPValue = 0, MyAPValue = 0;

    char *AsmRoomName = "Default RoomName", MyHPAndAP[64] = "^N%s his/her [^1HP = %d^N] and [^2AP = %d^N]", 
    *MyHPAndAPOutput = "^N-- his/her [^1HP = --^N] and [^2AP = --^N]", *MyHPAndAPWithName = "--";



    float NormalGravityValue = 1.0, LowGravityValue = 0.25, NormalJumpValue = 900.0, HighJumpValue = 1800.0, 
    NormalSpeedValue = 1.0, HighSpeedValue = 1.5;
    // Initialize end.

    // Edit memory jump to this dll. start.
    void CopyBuffer(BYTE *Buffer, int Size, DWORD *Address)	{
        DWORD pPrevious = 0;
        VirtualProtect(Address, Size, PAGE_EXECUTE_READWRITE, &pPrevious);
        memcpy(Address, Buffer, Size);
        VirtualProtect(Address, Size, pPrevious, &pPrevious);
        }

    void SetupHook(DWORD Function, DWORD Hook, int Size)	{
          Hook = Hook - Function - 5;
          BYTE bHook[4];
          memcpy(bHook,(void*)&Hook,4);
          BYTE Buffer[10];
          memset(Buffer,0x90,10);
            Buffer[0] = 0xE9;
            Buffer[1] = bHook[0];
            Buffer[2] = bHook[1];
            Buffer[3] = bHook[2];
            Buffer[4] = bHook[3];
          CopyBuffer(Buffer, Size, (DWORD*)Function);
      }
    // Edit memory jump to this dll. end.

    // Memory hack start.
    void RLSwordOn()	{
      // Rocket launcher sword enable start.
      if(RLCheck != true)	{
      VirtualProtect((void *)ROCKETLAUNCHERSWORD1, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD1, 4);
      memcpy((void *)ROCKETLAUNCHERSWORD1, "\x34\xD8\xFF\xFF", 4);
      VirtualProtect((void *)ROCKETLAUNCHERSWORD1, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)ROCKETLAUNCHERSWORD2, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD2, 4);
      memcpy((void *)ROCKETLAUNCHERSWORD2, "\x00\x00\x00\x00", 4);
      VirtualProtect((void *)ROCKETLAUNCHERSWORD2, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)ROCKETLAUNCHERSWORD3, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD3, 4);
      memcpy((void *)ROCKETLAUNCHERSWORD3, "\x00\x00\x00\x00", 4);
      VirtualProtect((void *)ROCKETLAUNCHERSWORD3, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)ROCKETLAUNCHERSWORD4, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD4, 4);
      memcpy((void *)ROCKETLAUNCHERSWORD4, "\x00\x00\x00\x00", 4);
      VirtualProtect((void *)ROCKETLAUNCHERSWORD4, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)ROCKETLAUNCHERSWORD5, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD5, 4);
      memcpy((void *)ROCKETLAUNCHERSWORD5, "\x00\x00\x00\x00", 4);
      VirtualProtect((void *)ROCKETLAUNCHERSWORD5, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)ROCKETLAUNCHERSWORD6, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD6, 4);
      memcpy((void *)ROCKETLAUNCHERSWORD6, "\x00\x00\x00\x00", 4);
      VirtualProtect((void *)ROCKETLAUNCHERSWORD6, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)CROSSHAIR, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)CROSSHAIR, 1);
      memcpy((void *)CROSSHAIR, "\xEB", 1);
      VirtualProtect((void *)CROSSHAIR, 1, ulOldProtect, &ulOldProtect);
      }
      // Rocket launcher sword enable end.
        }
    void RLSwordOff()	{
      // Rocket launcher sword disable start.
      if(RLCheck != false)	{
      VirtualProtect((void *)ROCKETLAUNCHERSWORD1, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD1, 4);
      memcpy((void *)ROCKETLAUNCHERSWORD1, "\x74\xF8\xFF\xFF", 4);
      VirtualProtect((void *)ROCKETLAUNCHERSWORD1, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)ROCKETLAUNCHERSWORD2, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD2, 4);
      memcpy((void *)ROCKETLAUNCHERSWORD2, "\x46\x01\x00\x00", 4);
      VirtualProtect((void *)ROCKETLAUNCHERSWORD2, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)ROCKETLAUNCHERSWORD3, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD3, 4);
      memcpy((void *)ROCKETLAUNCHERSWORD3, "\x78\x04\x00\x00", 4);
      VirtualProtect((void *)ROCKETLAUNCHERSWORD3, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)ROCKETLAUNCHERSWORD4, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD4, 4);
      memcpy((void *)ROCKETLAUNCHERSWORD4, "\x00\x04\x00\x00", 4);
      VirtualProtect((void *)ROCKETLAUNCHERSWORD4, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)ROCKETLAUNCHERSWORD5, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD5, 4);
      memcpy((void *)ROCKETLAUNCHERSWORD5, "\xEE\x03\x00\x00", 4);
      VirtualProtect((void *)ROCKETLAUNCHERSWORD5, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)ROCKETLAUNCHERSWORD6, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD6, 4);
      memcpy((void *)ROCKETLAUNCHERSWORD6, "\xCE\x03\x00\x00", 4);
      VirtualProtect((void *)ROCKETLAUNCHERSWORD6, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)CROSSHAIR, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)CROSSHAIR, 1);
      memcpy((void *)CROSSHAIR, "\x75", 1);
      VirtualProtect((void *)CROSSHAIR, 1, ulOldProtect, &ulOldProtect);
      }
      // Rocket launcher sword disable end.
        }
    void ShowNameOn()	{
      // Name hack enable start.
      if(NHCheck != true)	{
      VirtualProtect((void *)HEADCHARNAME, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)HEADCHARNAME, 1);
      memcpy((void *)HEADCHARNAME, "\x00", 1);
      VirtualProtect((void *)HEADCHARNAME, 1, ulOldProtect, &ulOldProtect);
      }
      // Name hack enable end.
    }
    void ShowNameOff()	{
      // Name hack disable start.
      if(NHCheck != false)	{
      VirtualProtect((void *)HEADCHARNAME, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)HEADCHARNAME, 1);
      memcpy((void *)HEADCHARNAME, "\x08", 1);
      VirtualProtect((void *)HEADCHARNAME, 1, ulOldProtect, &ulOldProtect);
      }
      // Name hack disable end.
    }
    void NoMassiveOn()	{
      // No massive enable start.
      if(NMCheck != true)	{
      VirtualProtect((void *)NOMASSIVE1, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)NOMASSIVE1, 4);
      memcpy((void *)NOMASSIVE1, "\x00\x00\x00\x00", 4);
      VirtualProtect((void *)NOMASSIVE1, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)NOMASSIVE2, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)NOMASSIVE2, 1);
      memcpy((void *)NOMASSIVE2, "\x00", 1);
      VirtualProtect((void *)NOMASSIVE2, 1, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)NOMASSIVE3, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)NOMASSIVE3, 1);
      memcpy((void *)NOMASSIVE3, "\xEB", 1);
      VirtualProtect((void *)NOMASSIVE3, 1, ulOldProtect, &ulOldProtect);
      }
      // No massive enable end.
    }
    void NoMassiveOff()	{
      // No massive disable start.
      if(NMCheck != false)	{
      VirtualProtect((void *)NOMASSIVE1, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)NOMASSIVE1, 4);
      memcpy((void *)NOMASSIVE1, "\x2D\x01\x00\x00", 4);
      VirtualProtect((void *)NOMASSIVE1, 4, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)NOMASSIVE2, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)NOMASSIVE2, 1);
      memcpy((void *)NOMASSIVE2, "\x7A", 1);
      VirtualProtect((void *)NOMASSIVE2, 1, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)NOMASSIVE3, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)NOMASSIVE3, 1);
      memcpy((void *)NOMASSIVE3, "\x74", 1);
      VirtualProtect((void *)NOMASSIVE3, 1, ulOldProtect, &ulOldProtect);
      }
      // No massive disable end.
    }
    void RevBskOn()	{
      // Reverse berserker enable start.
      if(RBCheck != true)	{
      VirtualProtect((void *)REVERSEBERSERKER1, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)REVERSEBERSERKER1, 1);
      memcpy((void *)REVERSEBERSERKER1, "\xEB", 1);
      VirtualProtect((void *)REVERSEBERSERKER1, 1, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)REVERSEBERSERKER2, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)REVERSEBERSERKER2, 1);
      memcpy((void *)REVERSEBERSERKER2, "\xC0", 1);
      VirtualProtect((void *)REVERSEBERSERKER2, 1, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)REVERSEBERSERKER3, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)REVERSEBERSERKER3, 1);
      memcpy((void *)REVERSEBERSERKER3, "\xC0", 1);
      VirtualProtect((void *)REVERSEBERSERKER3, 1, ulOldProtect, &ulOldProtect);
      }
      // Reverse berserker enable end.
    }
    void RevBskOff()	{
      // Reverse berserker disable start.
      if(RBCheck != false)	{
      VirtualProtect((void *)REVERSEBERSERKER1, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)REVERSEBERSERKER1, 1);
      memcpy((void *)REVERSEBERSERKER1, "\x7E", 1);
      VirtualProtect((void *)REVERSEBERSERKER1, 1, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)REVERSEBERSERKER2, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)REVERSEBERSERKER2, 1);
      memcpy((void *)REVERSEBERSERKER2, "\xE8", 1);
      VirtualProtect((void *)REVERSEBERSERKER2, 1, ulOldProtect, &ulOldProtect);

      VirtualProtect((void *)REVERSEBERSERKER3, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
      FlushInstructionCache(GetCurrentProcess(), (void *)REVERSEBERSERKER3, 1);
      memcpy((void *)REVERSEBERSERKER3, "\xE8", 1);
      VirtualProtect((void *)REVERSEBERSERKER3, 1, ulOldProtect, &ulOldProtect);
      }
      // Reverse berserker disable end.
    }
    // Memory hack end.

    // Assembler start.
    __declspec(naked) void RoomName()	{
        // Get the room name.
      _asm	{
        mov AsmRoomName, edi
        mov eax, ROOMNAME
        call eax
        mov ecx, ROOMNAMERETN
        jmp ecx
      }
    }

    __declspec(naked) void Bullet()	{
        // Bullet infinity.
      if(BulletBool == false)	{
        _asm	{
          mov dword ptr ds:[ecx + 0x2c], edx
        }
    }
        _asm	{
          mov al, 0x1
          mov eax, RELOADBULLETRETN
          jmp eax
        }
      }

    __declspec(naked) void Gravity()	{
        // Low gravity.
      if(GravityBool == false)	{
        _asm	{
          fld NormalGravityValue
        }
      }
      else	{
        _asm	{
          fld LowGravityValue
        }
      }
      _asm	{
        mov eax, GRAVITYRETN
        jmp eax
      }
    }

    __declspec(naked) void JumpPower()	{
        // High jump.
      if(JumpPowerBool == false)	{
        _asm	{
          fadd NormalJumpValue
        }
      }
      else	{
        _asm	{
          fadd HighJumpValue
        }
      }
      _asm	{
        mov eax, JUMPPOWERRETN
        jmp eax
      }
    }

    __declspec(naked) void WalkSpeed()	{
        // High speed.
      if(WalkSpeedBool == false)	{
        _asm	{
          fmul NormalSpeedValue
        }
      }
      else	{
        _asm	{
          fmul HighSpeedValue
        }
      }
      _asm	{
        pop ecx
        retn
      }
    }

    __declspec(naked) void GetHP()	{
        // Get my hp and name.
      _asm	{
        mov MyHPAndAPWithName, ecx
        mov ecx, ebp
        mov eax, GETHP
        call eax
        mov MyHPValue, eax
        mov ecx, GETHPRETN
        jmp ecx
      }
    }

    __declspec(naked) void GetAP()	{
        // Get my ap.
      _asm	{
        mov eax, GETAP
        call eax
        mov MyAPValue, eax
        mov ecx, GETAPRETN
        jmp ecx
      }
    }

    __declspec(naked) void GameCreateCheck()	{
        // In-game create check.
      MyHPAndAPWithName = "--";
      MyHPValue = 0;
      MyAPValue = 0;
      InGameCheck = true;
      _asm	{
        mov eax, GAMECREATE
        call eax
        mov ecx, GAMECREATERETN
        jmp ecx
      }
    }



    __declspec(naked) void GameDestroyCheck()	{
        // In-game destroy check.
      InGameCheck = false;
      _asm	{
        mov eax, GAMEDESTROY
        call eax
        mov ecx, GAMEDESTROYRETN
        jmp ecx
      }
    }

    __declspec(naked) void GunzDestroyCheck()	{
        // Client down check.
      LiveClientCheck = true;
      _asm	{
        mov eax, DESTROYGUNZ
        call eax
        mov ecx, DESTROYGUNZRETN
        jmp ecx
      }
    }
    // ZChatOutput
    typedef void(__cdecl* ZChatOutputFunc)(const char* lpcMsg, int iType ,int iLoc,  DWORD dwColor);
    ZChatOutputFunc ZChatOutput = (ZChatOutputFunc)Addr_ZChatOutput;

    void Print(const char* lpcFmt, ...){
      char szBuf[0x4000];
      va_list vaArgs;
      va_start(vaArgs, lpcFmt);
      _vsnprintf(szBuf, sizeof(szBuf), lpcFmt, vaArgs);
      va_end(vaArgs);
      ZChatOutput(szBuf, 2, 0, 0xFFFFFFFF);
    }


    // Assembler end.

    void MemoryEdit()	{
      // Setup for get the room name.
      SetupHook((DWORD)ROOMNAMECALL, (DWORD)RoomName, 5);
      // Setup for in-game create check.
      SetupHook((DWORD)GAMECREATECALL, (DWORD)GameCreateCheck, 5);
      // Setup for in-game destroy check.
      SetupHook((DWORD)GAMEDESTROYCALL, (DWORD)GameDestroyCheck, 5);
      // Setup for infinity bullet.
      SetupHook((DWORD)RELOADBULLET, (DWORD)Bullet, 5);
      // Setup for low gravity.
      SetupHook((DWORD)GRAVITY, (DWORD)Gravity, 6);
      // Setup for high jump.
      SetupHook((DWORD)JUMPPOWER, (DWORD)JumpPower, 6);
      // Setup for high speed.
      SetupHook((DWORD)WALKSPEED, (DWORD)WalkSpeed, 5);
      // Setup for get the my hp.
      SetupHook((DWORD)GETHPCALL, (DWORD)GetHP, 7);
      // Setup for get the my ap.
      SetupHook((DWORD)GETAPCALL, (DWORD)GetAP, 5);
      // Setup for destroy gunz check.
      SetupHook((DWORD)DESTROYGUNZCALL, (DWORD)GunzDestroyCheck, 5);
    }

    // Commands button check start.   
    void Commands()	{
      if(InGameCheck != false)	{
        if(GetAsyncKeyState(VK_F9) & 0x8000)	{
          Print("^N%s his/her [^1HP = %d^N] and [^2AP = %d^N]",MyHPAndAPWithName,MyHPValue,MyAPValue);


            Sleep(1000);
                            }

                    }
            }
    // Commands button check end.





    // Room name check loop start.
    void MainLoop()	{
      while(LiveClientCheck == false)	{
        string name = AsmRoomName;
      if(name.find("[IA]") != string::npos)	{
        BulletBool = true;
      }
      if(name.find("[IA]") == string::npos)	{
        BulletBool = false;
      }
      if(name.find("[G]") != string::npos)	{
        GravityBool = true;
      }
      if(name.find("[G]") == string::npos)	{
        GravityBool = false;
      }
      if(name.find("[IJ]") != string::npos)	{
        JumpPowerBool = true;
      }
      if(name.find("[IJ]") == string::npos)	{
        JumpPowerBool = false;
      }
      if(name.find("[DM]") != string::npos)	{
        NoMassiveOn();
        NMCheck = true;
      }
      if(name.find("[DM]") == string::npos)	{
        NoMassiveOff();
        NMCheck = false;
      }
      if(name.find("[SN]") != string::npos)	{
        ShowNameOn();
        NHCheck = true;
      }
      if(name.find("[SN]") == string::npos)	{
        ShowNameOff();
        NHCheck = false;
      }
      if(name.find("[RB]") != string::npos)	{
        RevBskOn();
        RBCheck = true;
      }
      if(name.find("[RB]") == string::npos)	{
        RevBskOff();
        RBCheck = false;
      }
      if(name.find("[SR]") != string::npos)	{
        RLSwordOn();
        RLCheck = true;
      }
      if(name.find("[SR]") == string::npos)	{
        RLSwordOff();
        RLCheck = false;
      }
      if(name.find("[FW]") != string::npos)	{
        WalkSpeedBool = true;
      }
      if(name.find("[FW]") == string::npos)	{
        WalkSpeedBool = false;
      }
        Commands();
          Sleep(50);
      }
    }
    // Room name check loop end.

    // Dll main. start.
    void main()	{
      MemoryEdit();
      MainLoop();
      }
    // Dll main. end.

    extern "C"
    {
      __declspec(dllexport) BOOL __stdcall DllMain(HINSTANCE hInst,DWORD reason,LPVOID lpv)
      {
        if (reason == DLL_PROCESS_ATTACH)
        {
          DisableThreadLibraryCalls(hInst);
      CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)&main,NULL,0,NULL);
        }
      return true;
      }
    }
