/******************************************************************
   
   ZUpdate.cpp

     Corperation : MAIET entertainment
     Programmer  : Lim Dong Hwan
	 Date        : 22.June.2005

*******************************************************************/


#include "stdafx.h"
#include "ZGlobal.h"
#include "ZUpdate.h"
#include "MXml.h"
#include "FileInfo.h"

#include <shlwapi.h>

//Wolfie: Added this.
#include <sstream>
#include <string>
#include "MZip.h"

// 현재 폴더 이름이 필터링된 파일 이름을 구함
CString GetFilteredFileName( const char* szFileName)
{
	CString str = szFileName;

	char szDir[ _MAX_DIR];
	GetCurrentDirectory( sizeof( szDir), szDir);

	if ( strncmp( szFileName, szDir, strlen( szDir)) == 0)
	{
		str = ".";
		str += szFileName + (int)strlen( szDir);
	}

	return str;
}


//Should be better now.
DWORD GetCRC( const char* szFileName, CString* pstrErrorMsg)
{
	// MRS 파일인지 확인
	char *pFileName = _strlwr( _strdup( szFileName));
	bool bIsMRSFile = ( strstr( pFileName, ".mrs") != NULL) ? true : false;
	delete pFileName;

	DWORD dwCRC = 0;
	char szMsg[ 1024];

	if ( bIsMRSFile)
	{
		FILE* fp = fopen( szFileName, "rb");

		// 파일 열기 실패
		if ( fp == NULL)
		{
			sprintf( szMsg, "[ZUpdate:GetCRC] ERROR : Cannot open this file : '%s'", GetFilteredFileName( szFileName));
			PutLog( szMsg);

			sprintf( szMsg, "%s : '%s'\n     [Tip] %s\n",	/*Cannot open file*/ ZGetString( "STR_124"), GetFilteredFileName( szFileName),
															/*Please check for file authorization*/ ZGetString( "STR_125"));
			*pstrErrorMsg += szMsg;
		}

		// 파일 열기 성공
		else
		{
			MZip zMRSFile;
			unsigned long dwReadMode = MZIPREADFLAG_MRS2;
			
			// 파일 초기화 실패
			if ( !zMRSFile.Initialize( fp , dwReadMode ))
			{
				sprintf( szMsg, "[ZUpdate:GetCRC] ERROR : Cannot initialize this file : '%s'", GetFilteredFileName( szFileName));
				PutLog( szMsg);

				sprintf( szMsg, "%s : '%s'\n     [Tip] %s\n     [Tip] %s\n",	/*This file is corrupt or missing*/ ZGetString( "STR_126"), GetFilteredFileName( szFileName),
																				/*Please check for file authorization*/ ZGetString( "STR_125"),
																				/*Try delete this file*/ ZGetString( "STR_127"));
				*pstrErrorMsg += szMsg;

				fclose( fp);
			}

			// 파일 초기화 성공
			else
			{
				for ( int i = 0;  i < zMRSFile.GetFileCount();  i++)
					dwCRC += zMRSFile.GetFileCRC32( i);

				fclose( fp);
			}
		}
	}

	// 그외 파일은 파일 전체를 읽어서 CheckSum을 구한다
	else
		dwCRC = GetFileCheckSum( (char*)szFileName);


	return dwCRC;
}


// 임시 다운로드 폴더 이름 구함
void GetTempFilePathName( const char* szFileName, char* szTmpFileName)
{
	char szDir[ _MAX_DIR];
	GetCurrentDirectory( sizeof( szDir), szDir);


	char drive[ _MAX_PATH], dir[ _MAX_PATH], fname[ _MAX_PATH], ext[ _MAX_PATH];
	_splitpath( szFileName, drive, dir, fname, ext);


	sprintf( szTmpFileName, "%s\\%s\\%s%s_", szDir, STR_TEMP_DOWNLOADFOLDER, fname, ext);
}


// 재부팅을 해야 하는 파일인지 검사
bool IsRebootingFile( const char* szFileName)
{
	bool bIsReboot = false;

	char *pFileName = _strlwr( _strdup( szFileName));

	if ( strstr( pFileName, "gunzlauncher") != NULL)				bIsReboot = true;



	delete pFileName;


	return bIsReboot;
}






// class ZUpdatePatchNode

// 생성자
ZUpdatePatchNode::ZUpdatePatchNode( const char* pszName, unsigned long nSize, unsigned long nChecksum)
{
	strcpy( m_szFileName, pszName);
	m_nSize = nSize;
	m_nCheckSum = nChecksum;
	m_bValidate = false;
	m_bPatchSuccess = true;
}


ZUpdatePatchNode::ZUpdatePatchNode( const char* pszName, unsigned long nSize,  const char*  nChecksum)
{
	strcpy( m_szFileName, pszName);
	m_nSize = nSize;
	strcpy( m_nCheckSumSTR, nChecksum);
	m_bValidate = false;
	m_bPatchSuccess = true;
}


// 소멸자
ZUpdatePatchNode::~ZUpdatePatchNode()
{
}


// CheckValid
bool ZUpdatePatchNode::CheckValid( CString* pstrErrorMsg)
{
	m_bValidate = false;


	// 파일 유무 검사
	WIN32_FIND_DATA FindData;
	HANDLE hFind;
	if( (hFind = FindFirstFile( GetFileName(), &FindData )) == INVALID_HANDLE_VALUE)
	{
		FindClose( hFind );

		char szMsg[ 512];
		sprintf( szMsg, "[ZUpdatePatchNode] Needs to update : %s (not exist)", GetFileName());
		PutLog( szMsg);

		return false;
	}

	
	// Handle close
	FindClose( hFind);


	// CheckSum 구함
	DWORD dwCRC = GetCRC( GetFileName(), pstrErrorMsg);
	std::ostringstream stream;
    stream << dwCRC;

	char szMsg[ 512];
	if(strcmp(stream.str().c_str(),GetChecksumSTR()) !=0)
	//if ( dwCRC != GetChecksum())
	{
		// CRC가 다르면 패치 대상 파일

		
#ifdef _DEBUG
		sprintf( szMsg, "[ZUpdatePatchNode] Needs to update : %s, remote(%s), local(%u)", GetFileName(), GetChecksumSTR(), dwCRC);
#else
		//sprintf( szMsg, "[ZUpdatePatchNode] Needs to update : %s", GetFileName());
		sprintf( szMsg, "[ZUpdatePatchNode] Needs to update : %s, remote(%s), local(%u)", GetFileName(), GetChecksumSTR(), dwCRC);
#endif
		PutLog( szMsg);
	}
	else
	{
		m_bValidate = true;
		//sprintf( szMsg, "[ZUpdate] Alex Needs to update : %s, remote(%u), local(%u)", GetFileName(), GetChecksum(), dwCRC);
		//PutLog( szMsg);
	}


	return true;
}





// class ZUpdate

// 생성자
ZUpdate::ZUpdate()
{
	// 변수 초기화
	m_bInitialize = false;
	m_szAddress[ 0] = 0;
	m_nPort = 0;
	m_szID[ 0] = 0;
	m_szPassword[ 0] = 0;
	m_pUpdatePatchList.clear();
	m_bStopUpdate = false;
	m_bPatchComplete = false;
	m_bReboot = false;
}


// 소멸자
ZUpdate::~ZUpdate()
{
	if ( m_bInitialize)
		Destroy();
}


// Create
bool ZUpdate::Create( const char* pszAddress, unsigned long nPort, const char* pszDefDirectory, const char* pszID, const char* pszPassword)
{
	m_strErrorMsg = "";

	PutLog( "[ZUpdate] Create.");

	// Set variables
	strcpy( m_szAddress, pszAddress);
	m_nPort = nPort;
	strcpy( m_szID, pszID);
	strcpy( m_szPassword, pszPassword);


	// Create File Transfer
	if ( !m_FileTransfer.Create( pszAddress, nPort, pszID, pszPassword))
	{
		char szMsg[ 1024];
		sprintf( szMsg, "%s\n     [Tip] %s\n     [Tip] %s\n",	/*The update server is not responding or is not running right now.*/ ZGetString( "STR_128"),
																/*Please check your firewall.*/ ZGetString( "STR_129"),
																/*Please try again after a while.*/ ZGetString( "STR_130"));
		m_strErrorMsg += szMsg;

		PutLog( "[ZUpdate] ERROR : Cannot create file transfer.");
		PutLog( "[ZUpdate] ERROR : Create FAILED!!!");

		return false;
	}


	// Create Open Connection
	if ( !m_FileTransfer.OpenConnection())
	{
		char szMsg[ 1024];
		sprintf( szMsg, "%s\n     [Tip] %s\n     [Tip] %s\n",	/*Internet connection failed.*/ ZGetString( "STR_131"),
																/*Please check your firewall.*/ ZGetString( "STR_129"),
																/*Please check your internet connection.*/ ZGetString( "STR_132"));
		m_strErrorMsg += szMsg;

		PutLog( "[ZUpdate] ERROR : Cannot open file transfer.");
		PutLog( "[ZUpdate] ERROR : Create FAILED!!!");

		return false;
	}


	// Set default directory
	if ( !m_FileTransfer.ChangeDirectory( pszDefDirectory))
	{
		char szMsg[ 1024];
		sprintf( szMsg, "%s\n     [Tip] %s\n     [Tip] %s\n",	/*The update server is not responding or is not running right now.*/ ZGetString( "STR_128"),
																/*Please check your firewall.*/ ZGetString( "STR_129"),
																/*Please try again after a while.*/ ZGetString( "STR_130"));
		m_strErrorMsg += szMsg;

		PutLog( "[ZUpdate] ERROR : Cannot change default directory.");
		PutLog( "[ZUpdate] ERROR : Create FAILED!!!");

		return false;
	}


	// Success
	m_UpdateInfo.SetTransferUI( m_FileTransfer.GetFileTransferUI());
	m_bInitialize = true;
	PutLog( "[ZUpdate] Create successfully compete.");

	return true;
}


// Destroy
bool ZUpdate::Destroy()
{
	PutLog( "[ZUpdate] Destroy.");

	// Close Connection
	if ( !m_FileTransfer.Destroy())
	{
		PutLog( "[ZUpdate] WARNING : Destroy FAILED!!!");
	}

	// Clear varialbes
	m_szAddress[ 0] = 0;
	m_nPort = 0;
	m_szID[ 0] = 0;
	m_szPassword[ 0] = 0;
	m_bInitialize = false;

	for ( ZUpdatePatchList::iterator itr = m_pUpdatePatchList.begin();  itr != m_pUpdatePatchList.end();  itr++)
		delete (*itr);

	m_pUpdatePatchList.clear();

    
	// Success
	PutLog( "[ZUpdate] Destroy successfully complete.");

	return true;
}


// CheckUpdate
bool ZUpdate::CheckUpdate( const char* pszPatchFileName)
{
	m_strErrorMsg = "";

	// Check Initialized
	if ( !m_bInitialize)
	{
		PutLog( "[ZUpdate] ERROR : Do not Created.");
		PutLog( "[ZUpdate] ERROR : Start update FAILED!!!");

		return false;
	}
	PutLog( "[ZUpdate] Start update.");

	
	// Set variables
	m_bStopUpdate = false;
	m_bPatchComplete = false;
	m_bReboot = false;
	m_UpdateInfo.ClearTotalPatchFileSize();
	m_UpdateInfo.ClearCurrPatchedFileSize();
	m_UpdateInfo.ClearTotalPatchFileCount();
	m_UpdateInfo.ClearCurrPatchedFileCount();
	m_UpdateInfo.ClearPatchFailedCount();

	
	// Download patch info file
	if ( !m_FileTransfer.DownloadFile( pszPatchFileName, pszPatchFileName, 0))
	{
		char szMsg[ 1024];
		sprintf( szMsg, "%s\n     [Tip] %s\n     [Tip] %s\n",	/*The update server is not responding or is not running right now.*/ ZGetString( "STR_128"),
																/*Please check your firewall.*/ ZGetString( "STR_129"),
																/*Please try again after a while.*/ ZGetString( "STR_130"));
		m_strErrorMsg += szMsg;

		PutLog( "[ZUpdate] ERROR : Start update FAILED!!!");
		return false;
	}


	// Get update info
	if ( !GetUpdateInfo( pszPatchFileName))
	{
		PutLog( "[ZUpdate] ERROR : Start update FAILED!!!");
		return false;
	}


	// Update files
	if ( !CheckValidFromPatchList())
	{
		PutLog( "[ZUpdate] ERROR : Start update FAILED!!!");
		return false;
	}


	return true;
}


// StartUpdate
bool ZUpdate::StartUpdate()
{
	m_strErrorMsg = "";

	// Patch files
	if ( !PatchFiles())
	{
		PutLog( "[ZUpdate] ERROR : Start update FAILED!!!");
		return false;
	}


	// 임시 폴더에 저장된 파일을 원래 디렉토리로 옮긴다
	if ( !MovePatchFiles())
	{
		PutLog( "[ZUpdate] ERROR : Cannot move patch files.");
		return false;
	}


	// Update complete
	PutLog( "[ZUpdate] Start update successfully complete.");

	m_bPatchComplete = true;

	return true;
}


// StopUpdate
bool ZUpdate::StopUpdate()
{
	PutLog( "[ZUpdate] Stop update.");


	// Stop file transfer
	m_FileTransfer.StopDownload();
	m_bStopUpdate = true;


	// Update complete
	PutLog( "[ZUpdate] Stop update successfully complete.");


	// Log
	char szMsg[ 1024];
	sprintf( szMsg, "%s\n     [Tip] %s\n",	/*Update canceled.*/ ZGetString( "STR_133"),
											/*Please retry updating.*/ ZGetString( "STR_134"));
	m_strErrorMsg += szMsg;

	return true;
}



// GetUpdatePatchFileInfo
#define MPTOK_PATCHINFO		"PATCHINFO"
#define MPTOK_VERSION		"VERSION"
#define MPTOK_PATCHNODE		"PATCHNODE"
#define MPTOK_SIZE			"SIZE"
#define MPTOK_WRITETIMEHIGH	"WRITETIMEHIGH"
#define MPTOK_WRITETIMELOW	"WRITETIMELOW"
#define MPTOK_CHECKSUM		"CHECKSUM"
#define MPTOK_ATTR_FILE		"file"

bool ZUpdate::GetUpdateInfo( const char* pszPatchFileName)
{
	PutLog( "[ZUpdate] Get update info.");


	// Clear patch list
	for ( ZUpdatePatchList::iterator itr = m_pUpdatePatchList.begin();  itr != m_pUpdatePatchList.end();  itr++)
		delete (*itr);

	m_pUpdatePatchList.clear();


	// Read patch file
	MXmlDocument	xmlConfig;
	MXmlElement		rootElement, aPatchInfo;

	xmlConfig.Create();
	if ( !xmlConfig.LoadFromFile( pszPatchFileName)) 
	{
		xmlConfig.Destroy();
		PutLog( "[ZUpdate] ERROR : Get update info FAILED!!!");

		return false;
	}

	rootElement = xmlConfig.GetDocumentElement();
	if ( rootElement.IsEmpty())
	{
		xmlConfig.Destroy();
		PutLog( "[ZUpdate] ERROR : Get update info FAILED!!!");

		return false;
	}

	if ( rootElement.FindChildNode( MPTOK_PATCHINFO, &aPatchInfo) == false)
	{
		xmlConfig.Destroy();
		PutLog( "[ZUpdate] ERROR : Get update info FAILED!!!");

		return false;
	}

	int iCount = aPatchInfo.GetChildNodeCount();
	for ( int i = 0;  i < iCount;  i++)
	{
		MXmlElement aPatchNode = aPatchInfo.GetChildNode(i);
		
		char szBuf[256];
		aPatchNode.GetTagName(szBuf);
		if (szBuf[0] == '#') continue;

		if ( !stricmp(szBuf, MPTOK_PATCHNODE))
		{
			char szFileName[_MAX_DIR] = "";
			int nSize = 0;
			FILETIME tmWrite;
			int nCheckSum = 0;

			char nCheckSumSTR[256]  = "";
		//	char * pEnd="";
		//	DWORD ncheckFilexx =0;
			 
			// File
			if ( aPatchNode.GetAttribute( szFileName, MPTOK_ATTR_FILE) == false)
				continue;

			// Size
			if ( aPatchNode.GetChildContents( &nSize, MPTOK_SIZE) == false)
				continue;

			// Date
//			if ( aPatchNode.GetChildContents( (int*)&tmWrite.dwHighDateTime, MPTOK_WRITETIMEHIGH) == false)
//				continue;

//			if ( aPatchNode.GetChildContents( (int*)&tmWrite.dwLowDateTime, MPTOK_WRITETIMELOW) == false)
//				continue;

			// Checksum
			if ( aPatchNode.GetChildContents( &nCheckSum, MPTOK_CHECKSUM) == false)
				continue;

			if ( aPatchNode.GetChildContents(nCheckSumSTR, MPTOK_CHECKSUM) == false)
				continue;

#ifdef _DEBUG
			// 만약 디버그 모드에서 건즈 런쳐 파일이면 그냥 통과한다
			if ( strstr( szFileName, "GunzLauncher.exe") != NULL)
				continue;
#endif
			
			//std::string myString = nCheckSumSTR;
   //         int valuetest = atol(myString.c_str()); //value = 45 


			//char szMsg[512];
			//sprintf( szMsg, "File %s:%s\n",szFileName,nCheckSumSTR);

			//PutLog(szMsg);
//			m_pUpdatePatchList.push_back( new ZUpdatePatchNode( szFileName, nSize, nCheckSum));
			m_pUpdatePatchList.push_back( new ZUpdatePatchNode( szFileName, nSize, nCheckSumSTR));
		}
		else if ( !stricmp( szBuf, MPTOK_VERSION))
		{
			char szVersion[ 128] = "";
			aPatchNode.GetContents( szVersion);

			// Get version here...
		}
	}
	xmlConfig.Destroy();


	// Success
	PutLog( "[ZUpdate] Get update info successfully complete.");

	return true;
}


// CheckValidFromPatchList
bool ZUpdate::CheckValidFromPatchList()
{
	PutLog( "[ZUpdate] Check valid from patch list.");


	// Get valid
	for ( ZUpdatePatchList::iterator itr = m_pUpdatePatchList.begin();  itr != m_pUpdatePatchList.end();  itr++)
	{
		(*itr)->CheckValid( &m_strErrorMsg);

		if ( m_bStopUpdate)
		{
			PutLog( "[ZUpdate] ERROR : Check valid STOPED!!!");
			PutLog( "[ZUpdate] ERROR : Check valid FAILED!!!");

			return false;
		}
	}


	// Get patch files information
	for ( ZUpdatePatchList::iterator itr = m_pUpdatePatchList.begin();  itr != m_pUpdatePatchList.end();  itr++)
	{
		if ( !(*itr)->IsValid())
		{
			m_UpdateInfo.AddTotalPatchFileSize( (*itr)->GetSize());
			m_UpdateInfo.AddTotalPatchFileCount( 1);
		}
	}


	// Success
	PutLog( "[ZUpdate] Check valid from patch list successfully complete.");
	CString str;
	str.Format( "[ZUpdate] + Total patch file count : %u", m_UpdateInfo.GetTotalPatchFileCount());
	PutLog( str);
	str.Format( "[ZUpdate] + Total patch file size : %u bytes", m_UpdateInfo.GetTotalPatchFileSize());
	PutLog( str);

	return true;
}


// PatchFiles
bool ZUpdate::PatchFiles()
{
	PutLog( "[ZUpdate] Patch files.");

	int numErrores =0;

	// Get patch files information
	char szMsg[ 1024];
	for ( ZUpdatePatchList::iterator itr = m_pUpdatePatchList.begin();  itr != m_pUpdatePatchList.end();  itr++)
	{
		if ( !(*itr)->IsValid())
		{
			// Get file name
			TCHAR szFullPath[ _MAX_DIR];
			GetTempFilePathName( (*itr)->GetFileName(), szFullPath);


			// Check if exist file
			bool bExistFile = false;
			WIN32_FIND_DATA findfile;
			HANDLE hFind = FindFirstFile( _T( szFullPath), &findfile);

			std::ostringstream stream;
			stream<<NULL;
  
			if ( hFind != INVALID_HANDLE_VALUE)
			{
				// CRC 검사를 해서 올바른 CRC이면 패스함
				DWORD dwCRCs = GetCRC( szFullPath, &m_strErrorMsg);
			    stream<<dwCRCs;
				//if ( (*itr)->GetChecksum() == GetCRC( szFullPath, &m_strErrorMsg))
				if(strcmp(stream.str().c_str(),(*itr)->GetChecksumSTR()) ==0)
				{
					sprintf( szMsg, "[ZUpdate] Already exist patch file : %s", GetFilteredFileName( szFullPath));
					PutLog( szMsg);

					bExistFile = true;
				}

				FindClose( hFind);
			}


			// Start download
			if ( !bExistFile)
			{
				#define DOWNLOAD_RETRY_COUNT	2
				for ( int nRetry = 1;  nRetry <= DOWNLOAD_RETRY_COUNT;  nRetry++)
				{
					if ( m_bStopUpdate)
						break;


					if ( m_FileTransfer.DownloadFile( (*itr)->GetFileName(), szFullPath, (*itr)->GetSize()))
					{
						sprintf( szMsg, "[ZUpdate] Successfully download '%s'", GetFilteredFileName( szFullPath));
						PutLog( szMsg);

						break;
					}
					// Fail
					else if ( nRetry == DOWNLOAD_RETRY_COUNT)
					{
						m_UpdateInfo.AddPatchFailedCount( 1);
						(*itr)->SetPatchSuccess( false);


						sprintf( szMsg, "[ZUpdate] ERROR : Fail to download file '%s'", GetFilteredFileName( szFullPath));
						PutLog( szMsg);


						sprintf( szMsg, "%s : %s\n     [Tip] %s\n",	/*Internet connection closed or this file is read-only*/ ZGetString( "STR_135"), GetFilteredFileName( szFullPath),
																	/*Please check your internet connection or delete this file*/ ZGetString( "STR_136"));
						m_strErrorMsg += szMsg;
						numErrores = numErrores+1;
					}
					// Retry
					else
					{
						sprintf( szMsg, "[ZUpdate] WARNNING : Retry patch file : %s , %d retry", GetFilteredFileName( szFullPath), nRetry);
						PutLog( szMsg);
					}
				}
			}


			// Update information
			m_UpdateInfo.AddCurrPatchedFileSize( (*itr)->GetSize());
			m_UpdateInfo.AddCurrPatchedFileCount( 1);
		}


		// Check stop
		if ( m_bStopUpdate)
		{
			PutLog( "[ZUpdate] Patch files STOP!!!");

			return false;
		}
	}


    // Success
	PutLog( "[ZUpdate] Patch files successfully complete.");

	if(numErrores>0){
		return false;
	}

	return true;
}


// 패치 파일을 원래 폴더로 옮김
bool ZUpdate::MovePatchFiles()
{
	PutLog( "[ZUpdate] Move patch files.");


	// Get patch files information
	char szMsg[ 1024];
	bool bFail = false;
	for ( ZUpdatePatchList::iterator itr = m_pUpdatePatchList.begin();  itr != m_pUpdatePatchList.end();  itr++)
	{
		if ( !(*itr)->IsValid() && (*itr)->IsPatchSuccess())
		{
			// 원본 파일명을 구한다
			TCHAR szFullPath[ _MAX_DIR];
			PathSearchAndQualify( (*itr)->GetFileName(), szFullPath, _MAX_DIR);

			// 다운로드 받은 패치 파일의 파일명을 구한다
			TCHAR szTmpFullPath[ _MAX_DIR];
			GetTempFilePathName( (*itr)->GetFileName(), szTmpFullPath);


			// 다운로드 받은 패치 파일의 CRC를 구한다
			DWORD dwCRC = GetCRC( szTmpFullPath, &m_strErrorMsg);

			std::ostringstream stream;
            stream << dwCRC;
          //  std::string str = stream.str();
		   // sprintf( szMsg, "[CRCTEST] %s,%s",(*itr)->GetFileName(),str.c_str());
		//	PutLog( szMsg);

//
//			// CRC 검사
			//crcalex
			//if ( (*itr)->GetChecksum() != dwCRC)

			if(strcmp(stream.str().c_str(),(*itr)->GetChecksumSTR()) !=0){
				// CRC 오류
#ifdef _DEBUG
				sprintf( szMsg, "[ZUpdate] ERROR : Invalid CRC : '%s' (org:%u / curr:%u)", GetFilteredFileName( szTmpFullPath), (*itr)->GetChecksum(), dwCRC);
#else
				sprintf( szMsg, "[ZUpdate] ERROR : Invalid CRC '%s'", GetFilteredFileName( szTmpFullPath));
#endif
				PutLog( szMsg);


				sprintf( szMsg, "%s : %s\n     [Tip] %s\n",	/*Invalid CRC from the downloaded patch file.*/ ZGetString( "STR_137"), GetFilteredFileName( szTmpFullPath),
															/*Please check for anti-virus program or firewall running on your system.*/ ZGetString( "STR_138"));
				m_strErrorMsg += szMsg;


				// 패치 실패 설정
				bFail = true;

				continue;
			}


			// 재부팅이 필요한 파일인지 검사한다
			if ( IsRebootingFile( szTmpFullPath))
			{
				// 로그 출력
				sprintf( szMsg, "[ZUpdate] This file is must restart : '%s'", GetFilteredFileName( szTmpFullPath));
				PutLog( szMsg);


				// 재부팅 설정
				m_bReboot = true;

				continue;
			}


			// 로그 출력
			sprintf( szMsg, "[ZUpdate] Copy patch file from '%s'  to  '%s'", GetFilteredFileName( szTmpFullPath), GetFilteredFileName( szFullPath));
			PutLog( szMsg);


			// Copy file
			if ( !MakePath( szFullPath))
			{
				sprintf( szMsg, "[ZUpdate] WARNNING : This file cannot made path : %s", GetFilteredFileName( szFullPath));
				PutLog( szMsg);

				sprintf( szMsg, "%s : %s\n     [Tip] %s\n",	/*WARNNING : This file cannot made path.*/ ZGetString( "STR_139"), GetFilteredFileName( szFullPath),
															/*Please check for directory authorization*/ ZGetString( "STR_140"));
				m_strErrorMsg += szMsg;
			}

			BOOL bRetVal = CopyFile( szTmpFullPath, szFullPath, FALSE);

			// 복사 실패면...
			if ( bRetVal == FALSE)
			{
				LPVOID lpMsgBuf;
				DWORD error = GetLastError();
				FormatMessage(	FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
								NULL, error, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT),
								(LPTSTR)&lpMsgBuf, 0, NULL);

				// 에러 메시지 작성
				sprintf( szMsg, "[ZUpdate] ERROR : File copy error : %s : %s", GetFilteredFileName( szFullPath), lpMsgBuf);
				PutLog( szMsg);

				sprintf( szMsg, "%s : %s : %s\n     [Tip] %s\n",	/*File copy error*/ ZGetString( "STR_141"), GetFilteredFileName( szFullPath), lpMsgBuf,
																	/*Please check for file authorization*/ ZGetString( "STR_125"));
				m_strErrorMsg += szMsg;


				LocalFree( lpMsgBuf);


				// 패치 실패
				bFail = true;

				continue;
			}

			
			// 패치된 파일이 정상인지 다시 확인한다
			dwCRC = GetCRC( szFullPath, &m_strErrorMsg);

			std::ostringstream stream2;
            stream2 << dwCRC;

			// CRC 검사
			//if ( (*itr)->GetChecksum() != dwCRC)

			if(strcmp(stream2.str().c_str(),(*itr)->GetChecksumSTR()) !=0){
				// CRC 오류
#ifdef _DEBUG
				sprintf( szMsg, "[ZUpdate] ERROR : CRC error '%s' (current : %u  /  original : %u)", GetFilteredFileName( szFullPath), dwCRC, (*itr)->GetChecksum());
#else
				//sprintf( szMsg, "[ZUpdate] ERROR : CRC error '%s'", GetFilteredFileName( szFullPath));
				sprintf( szMsg, "[ZUpdate] ERROR : CRC error '%s' (current : %u  /  original : %s)", GetFilteredFileName( szFullPath), dwCRC, (*itr)->GetChecksumSTR());
#endif
				PutLog( szMsg);

				sprintf( szMsg, "%s : %s\n     [Tip] %s\n",	/*This file is currently cannot be modified*/ ZGetString( "STR_142"), GetFilteredFileName( szFullPath),
															/*Please check for file authorization*/ ZGetString( "STR_125"));
				m_strErrorMsg += szMsg;


				// 패치 실패
				bFail = true;
			}

			 //이상 없으면 패치 파일을 삭제함
			else
				DeleteFile( szTmpFullPath);
		}
	}

    // Success
	PutLog( "[ZUpdate] Move patch files successfully complete.");


	if ( bFail)
		return false;

	return true;
}
