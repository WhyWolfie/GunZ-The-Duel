#include <Windows.h>
#include "detours.h"
#ifdef _ANTISB
class cDetour
{
public:
	void* Tramp;
	void* Det;
	void* Target;

	cDetour(void* From, void* To)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttachEx(&From, To, (DETOUR_TRAMPOLINE**)&Tramp, &Target, &Det);
		DetourTransactionCommit();
	}
};

cDetour* GetRawInputDataDetour;
unsigned int __stdcall GetRawInputDataHook(HRAWINPUT hRawInput, unsigned int uiCommand, void* pData, unsigned int* pcbSize, unsigned int cbSizeHeader)
{
	unsigned int RetVal = ((unsigned int(__stdcall *)(HRAWINPUT, unsigned int, void*, unsigned int*, unsigned int))GetRawInputDataDetour->Tramp)(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);

	if (RetVal && pData)
	{
		if (((RAWINPUT*)pData)->header.hDevice == NULL)
			return 0;
	}

	return RetVal;
}
#include "Xor.h"
void AntiSB()
{
	unsigned long address = (unsigned long)GetProcAddress(LoadLibraryA(XorStr<0xC8, 11, 0x3A4724D5>("\xBD\xBA\xAF\xB9\xFF\xFF\xE0\xAB\xBC\xBD" + 0x3A4724D5).s), XorStr<0x30, 16, 0x48CB8D12>("\x77\x54\x46\x61\x55\x42\x7F\x59\x48\x4C\x4E\x7F\x5D\x49\x5F" + 0x48CB8D12).s);
	GetRawInputDataDetour = new cDetour((LPVOID)address, GetRawInputDataHook);
}
#endif