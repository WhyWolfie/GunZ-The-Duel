#include "stdafx.h"
#define PSAPI_VERSION 1
#include "psapi.h"
#pragma comment( lib, "Psapi.lib" )
#pragma comment(lib, "kernel32.lib")

void AntiShotbotLogger();
void AutoitHax();
bool ProcessReadHax(DWORD address, DWORD binary, int bytes);
bool IsProcessRunning(int pid);
#define MAX_DUMP_SIZE 32
#define MAX_PROCESS_DUMP 3