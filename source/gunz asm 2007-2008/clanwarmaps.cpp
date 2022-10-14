#include <windows.h>

#define WRITEMAPS			0x004799E1
#define WRITEMAPSRETN		0x004799E6
#define MAPSIDCHECK			0x00489617
#define MAPSIDCHECKRETN		0x0048961C
// Change to your maps count.
#define MAPCOUNT		20

int MapID = 0, LastMapID = 0, WriteMapsRetnAddr = WRITEMAPSRETN, MapsIDCheckRetnAddr = MAPSIDCHECKRETN;

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

__declspec(naked) void writemapid()	{
	_asm	{
		mov ebx, MapID
		mov LastMapID, ebx
		push esi
		jmp WriteMapsRetnAddr
	}
}

__declspec(naked) void mapidcheck()	{
	_asm	{
		mov edx, LastMapID
		push edx
		jmp MapsIDCheckRetnAddr
	}
}

void main()	{
	SetupHook((DWORD)WRITEMAPS, (DWORD)writemapid, 5);
	SetupHook((DWORD)MAPSIDCHECK, (DWORD)mapidcheck, 5);

	while(1)	{
		do	{
		MapID++;
		Sleep(1000);
		}	while(MapID != MAPCOUNT);
		MapID = 0;
		Sleep(1000);
	}
}

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
