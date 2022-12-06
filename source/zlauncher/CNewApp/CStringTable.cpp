
#include "stdafx.h"
#include "CStringTable.h"
#include <map>
#include <string>
using namespace std;



//#define _OUTPUT_STRING


// List of string
map<string,string>		g_MapList;



// Destroy
void STDestroy()
{
	// 메모리 해제
	if ( !g_MapList.empty())
		g_MapList.clear();
}


// Load string from a file
bool STLoadFromFile( const char* szFileName)
{
	// 메모리 초기화
	if ( !g_MapList.empty())
		g_MapList.clear();


	// 파일 열기
	CFile file;
	CFileException ex;
	if ( file.Open( szFileName, CFile::modeRead, &ex) == FALSE)
		return false;


	// 파일 읽기
	char* szBuff = new char[ (unsigned int)file.GetLength()];
	file.Read( szBuff, (UINT)file.GetLength());


	// Load string from memory string
	bool bRetVal = STLoadFromMemory( szBuff);


	// 메모리, 파일 해제
	delete [] szBuff;
	file.Close();

	return bRetVal;
}


// Load string from memory string
bool STLoadFromMemory( const char* szMemString)
{
	// 스트링 출력 초기화
#ifdef _OUTPUT_STRING
	DeleteFile( "str_out.txt");
#endif

	// 스트링 읽기
	char ch;
	while ( 1)
	{
		// Skip block
		while ( 1)
		{
			ch = *szMemString++;
			if ( ch == 0)
				return true;

			if ( (ch == '\n') || (ch == '\r') || (ch == ' '))
				continue;

			break;
		}


		// Get name
		char szName[ 64];
		int nNameCount = 0;
		while ( 1)
		{
			szName[ nNameCount++] = ch;

			ch = *szMemString++;
			if ( (ch == 0) || (nNameCount >= 64))
				return true;

			if ( ch == ',')
				break;
		}
		szName[ nNameCount] = 0;


		// Get string
		char szString[ 512];
		int nStringCount = 0;
		while ( 1)
		{
			ch = *szMemString++;
			if ( (ch == 0) || ( nStringCount >= 512))
				return true;

			if ( (ch == '\n') || (ch == '\r'))
				break;

			szString[ nStringCount++] = ch;
		}
		szString[ nStringCount] = 0;



		// 해당 스트링이 존재하면 그냥 통과
		if ( g_MapList.find( szName) != g_MapList.end())
		{
			ASSERT( 0);

			continue;
		}


		// 스트링 추가
		g_MapList.insert( map<string,string>::value_type( szName, szString));


		// 스트링 출력
#ifdef _OUTPUT_STRING
		FILE* pFile = fopen( "str_out.txt", "a");
		if ( fopen)
		{
			fprintf( pFile, "%s , %s\n",szName, szString);
			fclose( pFile);
		}
#endif
	}
}


// Get string with name
const char* STGetString( const char* szName)
{
	// 스트링 찾기
	map<string,string>::iterator itr = g_MapList.find( szName);
	if ( itr == g_MapList.end())
		// 찾지 못함
		return NULL;


	// 스트링 리턴
	return (char*)(*itr).second.data();
}


// Get string with name
void STGetString( const char* szName, char* szString)
{
	// 초기화
	strcpy( szString, "NO_MSG");


	// 스트링 찾기
	map<string,string>::iterator itr = g_MapList.find( szName);
	if ( itr == g_MapList.end())
		// 찾지 못함
		return;


	// 스트링 복사
	strcpy( szString, (char*)(*itr).second.data());
}
