/******************************************************************
   
   Log.cpp

     Corperation : MAIET entertainment
     Programmer  : Lim Dong Hwan
	 Date        : 22.June.2005

*******************************************************************/


#include "stdafx.h"
#include "Log.h"


void InitLog()
{
	FILE* pFile;
	pFile = fopen( "patchlog.txt", "w");
	if ( pFile == NULL)
		return;


	__time64_t ltime;
	_time64( &ltime);
	fprintf( pFile, "Log start : %s\n", _ctime64( &ltime));


	char szDir[ 512];
	GetCurrentDirectory( sizeof( szDir), szDir);
	fprintf( pFile, "Current Directory : %s\n", szDir);

	fclose( pFile);
}


void PutLog( const char* pszLog)
{
	FILE* pFile;
	pFile = fopen( "patchlog.txt", "a");
	if ( pFile == NULL)
		return;

	fprintf( pFile, pszLog);
	fprintf( pFile, "\n");

	fclose( pFile);
}
