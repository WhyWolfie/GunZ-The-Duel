#include "stdafx.h"
#include "GunZConsole.h"
#include <TlHelp32.h>
#include <iostream>
#include <stdio.h>
#include "MDebug.h"
#include <windows.h>
#include <io.h>
#include <fcntl.h>

using namespace std;



void InitGunZConsole()
{
	if (!EnableConsole) return;
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	sprintf(dt, "%s -%s", __DATE__, __TIME__);
	sprintf(logger, "[%s] [GunZ Debug Console] ::Version :: %s ",dt, zMyBuildVersion);
	cout << logger << endl;
	mlog(logger);

}

void LogToConsole(char* input)
{
	
	if (!EnableConsole) return;

	sprintf(transderm, "[Debug] (" __DATE__" " __TIME__"):: %s\n",input);
	std::cout << transderm << std::endl;
	
	
}