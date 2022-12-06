/*
 CNewApp 클래스(NewApp.cpp)

  date : 2004년 5월 30일
  comp : 임동환
*/


#include <stdafx.h>
#include "NewApp.h"
#include "NewAppDlg.h"


// Variables
CNewApp theApp;



/************************************************************************************
  CNewApp
*************************************************************************************/
// CNewApp
CNewApp::CNewApp()
{
}


// Message map
BEGIN_MESSAGE_MAP(CNewApp, CWinApp)
	//{{AFX_MSG_MAP(CNewApp)
	//}}AFX_MSG
END_MESSAGE_MAP()



/************************************************************************************
  CNewApp initialization
*************************************************************************************/
HANDLE g_hMutex = NULL;
BOOL CNewApp::InitInstance()
{
	// Mutex 생성
	BOOL bFound = FALSE; 
	g_hMutex = ::CreateMutex( NULL, TRUE, "ZGunzLauncherMutex");
    
	// 만약 이미 만들어져 있다면 Instance가 이미 존재함
	if( ::GetLastError() == ERROR_ALREADY_EXISTS) 
		bFound = TRUE;

	if( g_hMutex)
		::ReleaseMutex( g_hMutex);

	// 이미 하나의 Instance가 존재하면 프로그램 종료
	if( bFound)
		return FALSE;


	// 컨트롤 초기화
	AfxEnableControlContainer();
	AfxInitRichEdit();


	// Open main dialog box
	CNewAppDlg dlg;
	dlg.DoModal();

	
	return false;
}
