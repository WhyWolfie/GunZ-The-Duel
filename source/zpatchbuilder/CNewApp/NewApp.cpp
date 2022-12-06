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
BOOL CNewApp::InitInstance()
{
	AfxEnableControlContainer();

	// Open main dialog box
	CNewAppDlg dlg;
	dlg.DoModal();

	
	return false;
}
