#include "stdafx.h"
#include "ZNHNRegistInfo.h"
#include "MRegistry.h"


ZNHNRegistInfo::ZNHNRegistInfo()
{
}


ZNHNRegistInfo::~ZNHNRegistInfo()
{
}



const char* ZNHNRegistInfo::GetGunzPath()
{
	const static char szRegistPath[]	= "SOFTWARE\\NHN\\";
	const static char szValueName[ 32 ] = "Gunz";

	memset( m_szRegistPath, 0, 1024 );

	if( !MRegistry::Read(HKEY_LOCAL_MACHINE, szRegistPath, szValueName, m_szRegistPath) )
		return 0;

	return m_szRegistPath;
}