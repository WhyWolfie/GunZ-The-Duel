#include "stdafx.h"
#include "ZAnticheat.h"
using namespace std;
BOOL CALLBACK EnumWindowsHandler(HWND hwnd, bool* retVal);
HANDLE SystemProcessScan();
bool ScanProcessMemory(HANDLE hProcessHandle);
typedef struct PROCESS_DUMP {
	unsigned int m_aOffset;
	unsigned char m_aMemDump[MAX_DUMP_SIZE];
} *PPROCESS_DUMP;
extern PROCESS_DUMP MEMORY_PROCESS_DUMP[MAX_PROCESS_DUMP];


PROCESS_DUMP MEMORY_PROCESS_DUMP[MAX_PROCESS_DUMP] = {
	{ 0x417770, { 0xE8, 0xC4, 0xAF, 0x00, 0x00, 0xE9, 0x79, 0xFE, 0xFF, 0xFF, 0x8B, 0xFF, 0x55, 0x8B, 0xEC, 0x8B, 0xC1, 0x8B, 0x4D, 0x08, 0xC7, 0x00, 0x88, 0xDA, 0x47, 0x00, 0x8B, 0x09, 0x83, 0x60, 0x08, 0x00 } }, //SHOTBOT.EXE + SHOTBOT.AU3
	{ 0x462000, { 0x00, 0x00, 0x00, 0x00, 0x07, 0x0A, 0x44, 0x00, 0xAE, 0x62, 0x45, 0x00, 0xBA, 0x62, 0x45, 0x00, 0xD0, 0x62, 0x45, 0x00, 0xDA, 0x62, 0x45, 0x00, 0x01, 0x63, 0x45, 0x00, 0x1F, 0x63, 0x45, 0x00 } }, //GUNZ MOUSE REBINDER 1.19 - 1.20
	{ 0x445CF4, { 0x6A, 0x60, 0x68, 0x90, 0x36, 0x45, 0x00, 0xE8, 0x60, 0xF8, 0xFF, 0xFF, 0xBF, 0x94, 0x00, 0x00, 0x00, 0x8B, 0xC7, 0xE8, 0xE4, 0xED, 0xFF, 0xFF, 0x89, 0x65, 0xE8, 0x8B, 0xF4, 0x89, 0x3E, 0x56 } } //GUNZ MOUSE REBINDER 1.18
};


void AutoitHax(){

	while (1){
		if (SystemProcessScan() != INVALID_HANDLE_VALUE){
			ExitProcess(0); //detecta shotbot autoit 
		}
		Sleep(10000); // Cada 10 segundos
	}

}


HANDLE SystemProcessScan(){
	DWORD dwProcesses[MAX_PATH];
	DWORD dwTotal;
	HANDLE hProcessHandle;
	if (!EnumProcesses(dwProcesses, sizeof(dwProcesses), &dwTotal))
		return INVALID_HANDLE_VALUE;
	for (int i = 0; i < (dwTotal / 4); i++){
		hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, false, dwProcesses[i]);
		if (hProcessHandle == INVALID_HANDLE_VALUE)
			continue;
		if (ScanProcessMemory(hProcessHandle))
			return hProcessHandle;
		CloseHandle(hProcessHandle);
	}
	return INVALID_HANDLE_VALUE;
}


bool ScanProcessMemory(HANDLE hProcessHandle) {
	for (int i = 0; i < MAX_PROCESS_DUMP; i++){
		char aTmpBuffer[MAX_DUMP_SIZE];
		SIZE_T aBytesRead = 0;
		ReadProcessMemory(hProcessHandle, (LPCVOID)MEMORY_PROCESS_DUMP[i].m_aOffset, (LPVOID)aTmpBuffer, sizeof(aTmpBuffer), &aBytesRead);
		if (memcmp(aTmpBuffer, MEMORY_PROCESS_DUMP[i].m_aMemDump, MAX_DUMP_SIZE) == 0){
			return true;
			break;
		}
	}
	return false;
}


HHOOK MouseHook;

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
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
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(MouseHook);
	return;
}