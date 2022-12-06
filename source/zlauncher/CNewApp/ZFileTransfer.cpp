/******************************************************************
   
   ZFileTransfer.cpp

     Corperation : MAIET entertainment
     Programmer  : Lim Dong Hwan
	 Date        : 22.June.2005

*******************************************************************/


#include "stdafx.h"
#include "ZGlobal.h"
#include "ZFileTransfer.h"
#include "FileInfo.h"




// class for MFTSession
MFTSession::MFTSession(LPCTSTR pszAppName, int nMethod)
: CInternetSession(pszAppName, 1, nMethod)
{
	EnableStatusCallback(TRUE);
}

void MFTSession::OnStatusCallback(DWORD dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInfomration, DWORD dwStatusInformationLen)
{
}



// class for ZFileTransfer

// 생성자
ZFileTransfer::ZFileTransfer() : m_Session( "ZUpdate")
{
	// 변수 초기화
	m_bInitialize = false;
	m_szAddress[ 0] = 0;
	m_szDefDir[ 0]  = 0;
	m_nPort = 0;
	m_szID[ 0] = 0;
	m_szPassword[ 0] = 0;
	m_szLastError[0] = 0;

	m_pConnection = NULL;
	m_bOpenConnection = false;
	m_bStopDownload = false;
}


// 소멸자
ZFileTransfer::~ZFileTransfer()
{
	// Check open connection
	if ( m_bOpenConnection)
		CloseConnection();
}


// Create
bool ZFileTransfer::Create( const char* pszAddress, unsigned long nPort, const char* pszID, const char* pszPassword)
{
	PutLog( "[ZFileTransfer] Create.");


	// Set variables
	strcpy( m_szAddress, pszAddress);
	m_nPort = nPort;
	strcpy( m_szID, pszID);
	strcpy( m_szPassword, pszPassword);


	// Success
	m_bInitialize = true;
	PutLog( "[ZFileTransfer] Create successfully complete.");

	return true;
}


// Destroy
bool ZFileTransfer::Destroy()
{
	PutLog( "[ZFileTransfer] Destroy.");


	// Check open connection
	if ( m_bOpenConnection)
	{
		if ( !CloseConnection())
			PutLog( "[ZFileTransfer] WARNING : Destroy FAILED!!!");
	}


	// Set variables
	m_szAddress[ 0] = 0;
	m_nPort = 0;
	m_szID[ 0] = 0;
	m_szPassword[ 0] = 0;

	// Success
	m_bInitialize = false;
	PutLog( "[ZFileTransfer] Destroy successfly complete.");

	return true;
}


// OpenConnection
bool ZFileTransfer::OpenConnection()
{
	PutLog( "[ZFileTransfer] Open connection.");


	// Check open connection
	if ( m_bOpenConnection)
	{
		PutLog( "[ZFileTransfer] ERROR : Already open connection.");
		PutLog( "[ZFileTransfer] ERROR : Open connection FAILED!!!");
		return false;
	}


	// Open connection
	CHttpConnection* pConnection = NULL;
	try
	{
		pConnection = m_Session.GetHttpConnection( m_szAddress, (INTERNET_PORT)m_nPort);
		if ( pConnection != NULL)
		{
			// Success
			m_pConnection = pConnection;
		}
	}
	// Error
	catch ( CInternetException* pEx)
	{
		pEx->GetErrorMessage( m_szLastError, 1024);
		pEx->Delete();

		if ( pConnection)
		{
			pConnection->Close();
			delete pConnection;
		}


		CString str;
		str.Format( "[ZFileTransfer] ERROR : %s", m_szLastError);
		PutLog( str);

		return false;
	}


	// Success
	m_bOpenConnection = true;
	PutLog( "[ZFileTransfer] Open connection successfully complete.");

	return true;
}


// CloseConnection
bool ZFileTransfer::CloseConnection()
{
	PutLog( "[ZFileTransfer] Close connection.");


	// Check open connection
	if ( !m_bOpenConnection)
	{
		PutLog( "[ZFileTransfer] WARNING : Connection are not opened.");
		PutLog( "[ZFileTransfer] WARNING : Close connection FAILED!!!");

		return false;
	}


	// Close connection
	GetConnection()->Close();
	
	delete m_pConnection;
	m_pConnection = NULL;

	// Success
	m_bOpenConnection = false;
	PutLog( "[ZFileTransfer] Close connection successfully complete.");

	return true;
}


// DownloadFile
bool ZFileTransfer::DownloadFile( const char* pszRemoteFileName, const char* pszLocalFileName, DWORD nFileSize)
{
	CString str;
	str.Format( "[ZFileTransfer] Download file : %s  to  %s", pszRemoteFileName, pszLocalFileName);
	PutLog( str);

	
	// Set variables
	CHttpFile* pFile = NULL;
	CFile LocalFile;
	m_bStopDownload = false;


	// Check open connection
	if ( !m_bOpenConnection)
	{
		PutLog( "[ZFileTransfer] ERROR : Connection are not opened.");
		str.Format( "[ZFileTransfer] ERROR : Failed download : %s", pszRemoteFileName);
		PutLog( str);

		return false;
	}


	// MakePath
	if ( !MakePath( pszLocalFileName))
	{
//		PutLog( "[ZFileTransfer] WARNNING : This file cannot made path.");
	}


	// Delete Loacal File
	if ( !DeleteFile( pszLocalFileName))
	{
//		str.Format( "[ZFileTransfer] WARNNING : Cannot delete %s file.", pszLocalFileName);
//		PutLog( str);
	}


	// Prepare Local File
	CFileException ex;
	if ( LocalFile.Open( pszLocalFileName, CFile::modeCreate | CFile::modeWrite, &ex) == FALSE)
	{
		ex.GetErrorMessage( m_szLastError, 1024);

		sprintf( m_szLastError, "%s : %s\n", pszLocalFileName, /*Access denied or unknown error.*/ ZGetString( "STR_148"));
		int i = 0;
		for ( i = (int)strlen( m_szLastError);  i >= 0;  i--)
		{
			if ( (m_szLastError[ i] == '/') || (m_szLastError[ i] == '\\'))
				break;
		}
		memcpy( m_szLastError, m_szLastError + (i + 1), (int)strlen( m_szLastError) - i);
		m_szLastError[ i + 1] = 0;

		str.Format( "[ZFileTransfer] ERROR : %s", m_szLastError);
		PutLog( str);
		str.Format( "[ZFileTransfer] ERROR : Failed download : %s", pszRemoteFileName);
		PutLog( str);


		// Delete file
		DeleteFile( pszLocalFileName);


		return false;
	}


	// Set full path name
	char szFullPathName[ 512];
	sprintf( szFullPathName, "/%s%s", m_szDefDir, pszRemoteFileName + 1);


	try
	{
		// Open request
		pFile = GetConnection()->OpenRequest( CHttpConnection::HTTP_VERB_GET, szFullPathName, NULL, 1, NULL, NULL, INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_NO_AUTO_REDIRECT);
		if ( !pFile)
		{
			str.Format( "[ZFileTransfer] ERROR : Cannot open remote file.");
			PutLog( str);
			str.Format( "[ZFileTransfer] ERROR : Failed download : %s", pszRemoteFileName);
			PutLog( str);


			// Delete file
			DeleteFile( pszLocalFileName);


			return false;
		}
		pFile->SendRequest();


		// if access was denied...
		bool bError = false;
		DWORD dwRet;
		pFile->QueryInfoStatusCode( dwRet);
		if ( dwRet == HTTP_STATUS_DENIED)
		{
			str.Format( "[ZFileTransfer] ERROR : Access denied.");
			PutLog( str);
			sprintf( m_szLastError, "(%03u) %s\n", dwRet, /*Access denied.*/ ZGetString( "STR_143"));

			bError = true;
		}
		else if ( dwRet == HTTP_STATUS_NOT_FOUND)
		{
			str.Format( "[ZFileTransfer] ERROR : File not found.");
			PutLog( str);
			sprintf( m_szLastError, "(%03u) %s\n", dwRet, /*File not found.*/ ZGetString( "STR_144"));

			bError = true;
		}
		else if ( (dwRet >= 300) && (dwRet < 400))
		{
			str.Format( "[ZFileTransfer] ERROR : Information error.");
			PutLog( str);
			sprintf( m_szLastError, "(%03u) %s\n", dwRet, /*Information error.*/ ZGetString( "STR_145"));

			bError = true;
		}
		else if ( (dwRet >= 400) && (dwRet < 500))
		{
			str.Format( "[ZFileTransfer] ERROR : File request error.");
			PutLog( str);
			sprintf( m_szLastError, "(%03u) %s\n", dwRet, /*File request error.*/ ZGetString( "STR_146"));

			bError = true;
		}
		else if ( (dwRet >= 500) && (dwRet < 600))
		{
			str.Format( "[ZFileTransfer] ERROR : Server error.");
			PutLog( str);
			sprintf( m_szLastError, "(%03u) %s\n", dwRet, /*Server error.*/ ZGetString( "STR_147"));

			bError = true;
		}


		// Check error
		if ( bError)
		{
			str.Format( "[ZFileTransfer] ERROR : Failed download : %s", pszRemoteFileName);
			PutLog( str);

			delete pFile;


			// Delete file
			DeleteFile( pszLocalFileName);


			return false;
		}


		// Download file
		m_FileTransferUI.SetDownloadFileName( pszRemoteFileName);
		m_FileTransferUI.SetTotalDownloadSize( nFileSize);
		m_FileTransferUI.ClearCurrDownloadSize();
		#define MBUF_SIZE	2048
		BYTE Buffer[ MBUF_SIZE];
		DWORD dwRead = 0;
		DWORD dwTotalRead = 0;
		do
		{
			dwRead = pFile->Read( Buffer, MBUF_SIZE);
			LocalFile.Write( Buffer, dwRead);

			dwTotalRead += dwRead;
			
			m_FileTransferUI.AddCurrDownloadSize( dwRead);

		} while ( (dwRead > 0) && !m_bStopDownload);
	}
	// Error
	catch ( CInternetException* pEx)
	{
		pEx->GetErrorMessage( m_szLastError, 1024);
		pEx->Delete();

		str.Format( "[ZFileTransfer] ERROR : %s", m_szLastError);
		PutLog( str);

		LocalFile.Close();
		pFile->Close();
		delete pFile;

		DeleteFile( pszLocalFileName);			// Delete file


		return false;
	}



	// Stop download
	if ( m_bStopDownload)
	{
		PutLog( "[ZFileTransfer] Stop download.");
		m_bStopDownload = false;

		LocalFile.Close();
		pFile->Close();
		delete pFile;

		DeleteFile( pszLocalFileName);			// Delete file

		return false;
	}


	// Download complete
	PutLog( "[ZFileTransfer] Download successfully complete.");

	LocalFile.Close();
	pFile->Close();

	delete pFile;

	m_FileTransferUI.ClearDownloadFileName();
	m_FileTransferUI.ClearCurrDownloadSize();
	m_FileTransferUI.SetTotalDownloadSize( 0);

	return true;
}


// ChangeDirectory
bool ZFileTransfer::ChangeDirectory( const char* pszDirectory)
{
	PutLog( "[ZFileTransfer] Change directory.");


	// Check open connection
	if ( !m_bOpenConnection)
	{
		PutLog( "[ZFileTransfer] ERROR : Connection are not opened.");
		PutLog( "[ZFileTransfer] ERROR : Change directory FAILED!!!");

		return false;
	}


	// Change directory
	strcpy( m_szDefDir, pszDirectory);


	// Success
	CString str;
#ifdef _DEBUG
	str.Format( "[ZFileTransfer] Change directory successfully complete. : %s", pszDirectory);
#else
	str.Format( "[ZFileTransfer] Change directory successfully complete.");
#endif
	PutLog( str);

	return true;
}
