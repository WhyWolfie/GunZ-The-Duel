#include <windows.h>
#include <stdio.h>
#include <string>

using namespace std;

// GunZ: The Duel July 2008 Runnable Addresses.
#define ROOMNAME				    0x005096D0
#define ROOMNAMECALL			    0x0045B7AB
#define ROOMNAMERETN		    	0x0045B7B0
#define GETHP						0x00476D90
#define GETHPCALL					0x00405D9D
#define GETHPRETN					0x00405DA2
#define GETAP					    0x00476DA0
#define GETAPCALL					0x00405E1C
#define GETAPRETN					0x00405E21
#define RELOADBULLET				0x0047F4AB
#define RELOADBULLETRETN			0x0047F4B0
#define GRAVITY					    0x0048106E
#define GRAVITYRETN				    0x00481074
#define JUMPPOWER					0x00486031
#define JUMPPOWERRETN				0x00486037
#define WALKSPEED				    0x00478000
#define WALKSPEEDRETN			    0x00478005
#define GAMECREATE					0x004AD790
#define GAMECREATECALL				0x004AB97C
#define GAMECREATERETN				0x004AB981
#define GAMEDESTROY				    0x005773EE
#define GAMEDESTROYCALL			    0x004A60D8
#define GAMEDESTROYRETN			    0x004A60DD
#define ROCKETLAUNCHERSWORD1		0x00483EBE
#define ROCKETLAUNCHERSWORD2		0x00481B20
#define ROCKETLAUNCHERSWORD3		0x004A1B83
#define ROCKETLAUNCHERSWORD4		0x004A1C14
#define ROCKETLAUNCHERSWORD5		0x004A1C24
#define ROCKETLAUNCHERSWORD6		0x004A1C40
#define CROSSHAIR					0x00405F47
#define HEADCHARNAME				0x0040A320
#define NOMASSIVE1				    0x0048376C
#define NOMASSIVE2				    0x00483828
#define NOMASSIVE3				    0x00483881
#define INFINITYJUMP				0x00485F8C
#define REVERSEBERSERKER1			0x004B51BA
#define REVERSEBERSERKER2			0x004B5211
#define REVERSEBERSERKER3			0x004B5236
#define INGAMECHAT					0x0042ADC0
#define DESTROYGUNZ				    0x00499620
#define DESTROYGUNZCALL			    0x00498784
#define DESTROYGUNZRETN			    0x00498789
#define ADMIN_WALL                  0x0043706F
#define ZCHAT                       0x0043368C

// Initialize Start.
unsigned long ulOldProtect;

bool InGameCheck = false, BulletBool = false, GravityBool = false, JumpPowerBool = false, WalkSpeedBool = false, 
RLCheck = false, NHCheck = false, NMCheck = false, RBCheck = false, LiveClientCheck = false;

int MyHPValue = 0, MyAPValue = 0;

char *AsmRoomName = "Default RoomName", MyHPAndAP[64] = "^4(%s) ^2[HP:%d, AP:%d]", 
*MyHPAndAPOutput = "^4(--) ^2[HP:--, AP:--]", *MyHPAndAPWithName = "--";

float NormalGravityValue = 1.0, LowGravityValue = 0.25, NormalJumpValue = 900.0, HighJumpValue = 1800.0, 
NormalSpeedValue = 1.0, HighSpeedValue = 1.5;
// Initialize End.

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

void RLSwordOn()	{
	// Rocket launcher sword enable start.
	if(RLCheck != true)	{
	VirtualProtect((void *)ROCKETLAUNCHERSWORD1, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
	FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD1, 4);
	memcpy((void *)ROCKETLAUNCHERSWORD1, "\x3E\xDC\xFF\xFF", 4);
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
	memcpy((void *)ROCKETLAUNCHERSWORD1, "\xCE\xF7\xFF\xFF", 4);
	VirtualProtect((void *)ROCKETLAUNCHERSWORD1, 4, ulOldProtect, &ulOldProtect);

	VirtualProtect((void *)ROCKETLAUNCHERSWORD2, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
	FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD2, 4);
	memcpy((void *)ROCKETLAUNCHERSWORD2, "\x1C\x01\x00\x00", 4);
	VirtualProtect((void *)ROCKETLAUNCHERSWORD2, 4, ulOldProtect, &ulOldProtect);

	VirtualProtect((void *)ROCKETLAUNCHERSWORD3, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
	FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD3, 4);
	memcpy((void *)ROCKETLAUNCHERSWORD3, "\x77\x04\x00\x00", 4);
	VirtualProtect((void *)ROCKETLAUNCHERSWORD3, 4, ulOldProtect, &ulOldProtect);

	VirtualProtect((void *)ROCKETLAUNCHERSWORD4, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
	FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD4, 4);
	memcpy((void *)ROCKETLAUNCHERSWORD4, "\xE6\x03\x00\x00", 4);
	VirtualProtect((void *)ROCKETLAUNCHERSWORD4, 4, ulOldProtect, &ulOldProtect);

	VirtualProtect((void *)ROCKETLAUNCHERSWORD5, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
	FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD5, 4);
	memcpy((void *)ROCKETLAUNCHERSWORD5, "\xD6\x03\x00\x00", 4);
	VirtualProtect((void *)ROCKETLAUNCHERSWORD5, 4, ulOldProtect, &ulOldProtect);

	VirtualProtect((void *)ROCKETLAUNCHERSWORD6, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
	FlushInstructionCache(GetCurrentProcess(), (void *)ROCKETLAUNCHERSWORD6, 4);
	memcpy((void *)ROCKETLAUNCHERSWORD6, "\xBA\x03\x00\x00", 4);
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
	VirtualProtect((void *)NOMASSIVE1, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
	FlushInstructionCache(GetCurrentProcess(), (void *)NOMASSIVE1, 1);
	memcpy((void *)NOMASSIVE1, "\xEB", 1);
	VirtualProtect((void *)NOMASSIVE1, 1, ulOldProtect, &ulOldProtect);

	VirtualProtect((void *)NOMASSIVE2, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
	FlushInstructionCache(GetCurrentProcess(), (void *)NOMASSIVE2, 4);
	memcpy((void *)NOMASSIVE2, "\x00\x00\x00\x00", 4);
	VirtualProtect((void *)NOMASSIVE2, 4, ulOldProtect, &ulOldProtect);

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
	VirtualProtect((void *)NOMASSIVE1, 1, PAGE_EXECUTE_READWRITE, &ulOldProtect);
	FlushInstructionCache(GetCurrentProcess(), (void *)NOMASSIVE1, 1);
	memcpy((void *)NOMASSIVE1, "\x74", 1);
	VirtualProtect((void *)NOMASSIVE1, 1, ulOldProtect, &ulOldProtect);

	VirtualProtect((void *)NOMASSIVE2, 4, PAGE_EXECUTE_READWRITE, &ulOldProtect);
	FlushInstructionCache(GetCurrentProcess(), (void *)NOMASSIVE2, 4);
	memcpy((void *)NOMASSIVE2, "\x82\x00\x00\x00", 4);
	VirtualProtect((void *)NOMASSIVE2, 4, ulOldProtect, &ulOldProtect);

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
	mov dword ptr ds:[ecx + 0x38], edx
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
		mov esp, ebp
		mov eax, WALKSPEEDRETN
		jmp eax
	}
}

__declspec(naked) void GetHP()	{
		// Get my hp and name.
	_asm	{
		mov MyHPAndAPWithName, edx
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
	SetupHook((DWORD)GETHPCALL, (DWORD)GetHP, 5);
	// Setup for get the my ap.
	SetupHook((DWORD)GETAPCALL, (DWORD)GetAP, 5);
	// Setup for destroy gunz check.
	SetupHook((DWORD)DESTROYGUNZCALL, (DWORD)GunzDestroyCheck, 5);
}

// Commands button check start.
void Commands()	{
	if(InGameCheck != false)	{
		if(GetAsyncKeyState(VK_F9) & 0x8000)	{
			sprintf_s(MyHPAndAP, "^4(%s) ^2[HP:%d, AP:%d]", MyHPAndAPWithName, MyHPValue, MyAPValue);
			MyHPAndAPOutput = MyHPAndAP;
			_asm	{
				push 0x0
				push MyHPAndAPOutput
				mov eax, INGAMECHAT
				call eax
			}
				Sleep(1000);
		}
	}
}
// Commands button check end.

// Room name check loop start.
void MainLoop()	{
	bool toggle = false;
	while(LiveClientCheck == false)	{
		string name = AsmRoomName;
	if(name.find("[B]") != string::npos)	{
		BulletBool = true;
	}
	if(name.find("[B]") == string::npos)	{
		BulletBool = false;
	}
	if(name.find("[G]") != string::npos)	{
		GravityBool = true;
	}
	if(name.find("[G]") == string::npos)	{
		GravityBool = false;
	}
	if(name.find("[J]") != string::npos)	{
		/*
		InfJumpOn();
		JCheck = true;
		*/
		JumpPowerBool = true;
	}
	if(name.find("[J]") == string::npos)	{
		/*
		InfJumpOff();
		JCheck = false;
		*/
		JumpPowerBool = false;
	}
	if(name.find("[M]") != string::npos)	{
		NoMassiveOn();
		NMCheck = true;
	}
	if(name.find("[M]") == string::npos)	{
		NoMassiveOff();
		NMCheck = false;
	}
	/// tanos
	if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState("A") & 0x8000))
		{
		toggle = true;
		printf("Admin wall enabled");
		if(strstr("/s %s", ADMIN_WALL))
			{
			ZChat("%s", ADMIN_WALL);
			sleep(20);
			}
		}
		else
		{
			toggle = false;
			printf("admin wall disabled");
		}
	if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState("N") & 0x8000))	{
		ShowNameOn();
		NHCheck = true;
		ZChatOutPut("^9ESP Mode: ^2ON");
	}
	if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState("N") & 0x8000))	{
		ShowNameOff();
		NHCheck = false;
		ZChatOutPut("^9ESP Mode: ^1OFF");
	}
	if(name.find("[RB]") != string::npos)	{
		RevBskOn();
		RBCheck = true;
	}
	if(name.find("[RB]") == string::npos)	{
		RevBskOff();
		RBCheck = false;
	}
	if(name.find("[RL]") != string::npos)	{
		RLSwordOn();
		RLCheck = true;
	}
	if(name.find("[RL]") == string::npos)	{
		RLSwordOff();
		RLCheck = false;
		sleep(500);
	}
	if(name.find("[S]") != string::npos)	{
		WalkSpeedBool = true;
	}
	if(name.find("[S]") == string::npos)	{
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
