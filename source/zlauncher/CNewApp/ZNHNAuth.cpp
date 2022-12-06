#include "stdafx.h"
#include "ZGlobal.h"
#include "ZNHNAuth.h"
#include "HanAuthForClient.h"
#include "HanReportForclient.h"
#include "MDebug.h"


#ifdef LOCALE_NHNUSA
#ifndef _DEBUG
#pragma comment( lib, "HanAuthForClient.lib" )
#pragma comment( lib, "HanReportForClient.lib" )
#else
#pragma comment( lib, "HanAuthForClientD.lib" )
#pragma comment( lib, "HanReportForClientD.lib" )
#endif
#endif

ZNHNAuth::ZNHNAuth()
{
	m_bIsCompleted = false;

	memset( m_szAuthString, 0, NHN_AUTH_LENGTH );
}
	


ZNHNAuth::~ZNHNAuth()
{
}


void ZNHNAuth::InitTok()
{
	m_Tok.clear();

	m_Tok.push_back( "GunzLauncher.EXE" );
	m_Tok.push_back( "GunzLauncher.exe" );
	m_Tok.push_back( "gunzlauncher.EXE" );
	m_Tok.push_back( "gunzlauncher.exe" );
	m_Tok.push_back( "GunzLauncher" );
	m_Tok.push_back( "gunzlauncher" );
	m_Tok.push_back( "NewApp" );
}


bool ZNHNAuth::GetGameStr( const string& strCmdLine, char* szOutGameStr, const int nOutGameStrLen )
{
#ifdef _DEBUG
#define _GAMESTR_DEBUG
#endif

#ifdef _DEBUG
	//mlog( "CmdLine : %s\n\n", strCmdLine.c_str() );
#endif

	if( strCmdLine.empty() || (0 == szOutGameStr) )
		return false;

#define MAX_FULLPATH_LEN 256
#define MAX_FILENAME_LEN 32
	
	vector< string >::iterator	it, end;
	size_t						nPos = 0;
	char						szFullPath[ MAX_FULLPATH_LEN ] = {0,};
	char						szFileName[ MAX_FILENAME_LEN ] = {0,};
	string						strFileName;
	int							nFullPathLen = 0;

	if( 0 == _fullpath( szFullPath, "", MAX_FULLPATH_LEN )  )
	{
		//mlog( "Get full path fail\n" );
		return false;
	}

	if( string::npos != strCmdLine.find(szFullPath) )
	{

#ifdef _GAMESTR_DEBUG
		//mlog( "full path : %s\n\n", szFullPath );
#endif

		nFullPathLen = strlen( szFullPath );
	}

	const size_t nGameStrPos = strCmdLine.find( " ", nFullPathLen );
	if( string::npos == nGameStrPos )
	{
		ASSERT( 0 );
		return false;
	}

	if( nOutGameStrLen < (strCmdLine.length() - nGameStrPos) )
	{
		//mlog( "game string is longer then output buffer...\n" );
		return false;
	}
	
	strncpy( szFileName, strCmdLine.c_str() + nFullPathLen, MAX_FILENAME_LEN );
	szFileName[ MAX_FILENAME_LEN - 1 ] = '\0';

#ifdef _GAMESTR_DEBUG
	//mlog( "file name : %s\n\n", szFileName );
#endif

	strFileName = szFileName;
	end = m_Tok.end();
	for( it = m_Tok.begin(); it != end; ++it )
	{
#ifdef _GAMESTR_DEBUG
		//mlog( "Tok : %s\n\n", it->c_str() );
#endif
		nPos = strFileName.find( *it );
		if( string::npos != nPos )
		{
			strncpy( szOutGameStr, strCmdLine.c_str() + nGameStrPos, strCmdLine.length() - nGameStrPos );
#ifdef _GAMESTR_DEBUG
			//mlog( "Out game string : %s\n\n", szOutGameStr );
#endif
			return true;
		}
	}

	return false;	
}


bool ZNHNAuth::InitAuth()
{
	if( true == m_bIsCompleted ) 
	{
		//mlog( "duplated init NHNAuth...\n\n" );
		return true;
	}

	//mlog( "Tag : errorcode 003");


	//InitLog( MLOGSTYLE_DEBUGSTRING|MLOGSTYLE_FILE );

	char szGameStr[ NHN_AUTH_LENGTH ] = {0,};

	const char* pszCmdLine = GetCommandLine();
	if(	0 == pszCmdLine )
		return false;

	const int nCmdLen = strlen( pszCmdLine );

	//mlog( "Tag : errorcode 002");


	if( NHN_AUTH_LENGTH < nCmdLen )
	{

		return false;
	}

	InitTok();

	//mlog( "Tag : errorcode 001");

	if( !GetGameStr(pszCmdLine, szGameStr, NHN_AUTH_LENGTH) )
	{
		//mlog( "Get second game string fail. CmdlIne(%s)\n", pszCmdLine );
		return false;
	}

	const int nRetAuthInit = HanAuthInitGameString( szGameStr );
	if( 0 != nRetAuthInit )
	{
		//mlog( "Init Auth HanAuthInit fail : err code(%d)\n", nRetAuthInit );
		return false;
	}

	char szGameStringNew[4096]	={0x00};
	char szMemberId[25]			={0x00}; 

	const int nRetAuthClien = HanAuthForClientGameString( szGameStr );
	if( 0 != nRetAuthClien )
	{
		//mlog( "Init Auth HanAuthForClient fail : err code(%d)\n", nRetAuthClien );
		return false;
	}
	
	const int nRetGetId = HanAuthGetId( szGameStr, szMemberId, 25 );
	if( 0 != nRetGetId )
	{
		//mlog( "Init Auth HanAuthGetId fail : err code(%d)\n", nRetGetId );
		return false;
	}

	const int nRetAuthRefresh = HanAuthRefresh( szMemberId );
	if( 0 != nRetAuthRefresh )
	{
		//mlog( "Init Auth HanAuthRefresh fail : err code(%d)\n", nRetAuthRefresh );
		return false;
	}

	const int nRetUpdate = UpdateGameString( szGameStr, szGameStringNew, sizeof(szGameStringNew) );
	if( 0 != nRetUpdate )
	{
		//mlog( "Init Auth UpdateGameString fail : err code(%d)\n", nRetUpdate );
		return false;
	}

	strcpy( m_szAuthString, szGameStr );

	//mlog( "Init Auth success.\n" );

	m_bIsCompleted = true;

	return true;
}


const bool ZNHNAuth::IsAlpha()
{
	int nCode = 0; 
	HanAuthGetServiceTypeCode( m_szAuthString, &nCode ); 
	if( SERVICE_ALPHA != nCode )
		return false;
	return true;
}


const bool ZNHNAuth::IsReal()
{
	int nCode = 0; 
	HanAuthGetServiceTypeCode( m_szAuthString, &nCode ); 
	if( SERVICE_REAL != nCode )
		return false;
	return true;
}