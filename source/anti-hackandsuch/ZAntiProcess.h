#pragma comment (lib, "libcurl.lib")

#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <fstream>
#include <string.h>
#include "curl/curl.h"

using namespace std;

void killProcessByName(const char *filename)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes)
	{
		if (strcmp(pEntry.szExeFile, filename) == 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
			if (hProcess != NULL)
			{
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
			}
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}
void readFile()
{
	CURL *curl;
	FILE *fp;
	CURLcode res;

	char winDir[MAX_PATH] = { 0 };
	GetSystemWindowsDirectory(winDir, MAX_PATH);

	char outfilename[FILENAME_MAX] = { 0 };
	sprintf(outfilename, "%s//pList.txt", winDir);

	char szProcess[256] = { 0 };

	curl = curl_easy_init();
	if (curl) {
		fp = fopen(outfilename, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, "http://playgunz.net/pList.txt");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);

		ifstream file(outfilename);
		for (string line; getline(file, line);)
		{
			try
			{
				sprintf(szProcess, "%s.exe", line.c_str());
				killProcessByName(szProcess);
			}
			catch (int e)
			{
				return;
			}
		}
	}
}

void SearchandDestroy()
{
	while (true)
	{
		readFile();
		Sleep(3000);
	}
}