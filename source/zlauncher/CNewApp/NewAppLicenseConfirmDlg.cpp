
#include "stdafx.h"
#include "NewAppLicenseConfirmDlg.h"
#include <Mmsystem.h>


/************************************************************************************
  Dialog
*************************************************************************************/
// 클래스 생성자
CNewAppLicenseConfirmDlg::CNewAppLicenseConfirmDlg( CWnd* pParent) : CDDBDialog( IDD_LICENSE_CONFIRM, pParent)
{
	//{{AFX_DATA_INIT( CNewAppLicenseConfirmDlg)
	//}}AFX_DATA_INIT

	// 이곳에서 생성할 다이얼로그의 정보를 입력한다
	// 좀 더 자세한 설명을 원하면 CDDBDialog.h 화일의 Structure of CDDBDIALOGINFO 내용을 참고한다
	CDDBDLGINFO DlgInfo;
	DlgInfo.nWidth = 640;
	DlgInfo.nHeight = 400;
	DlgInfo.IDSkinResource = IDR_BMP_POPUPDLG;
	DlgInfo.bEnableMoveDlg = TRUE;
	DlgInfo.nTextColor = RGB( 166, 156, 153);
	DlgInfo.nTextBkColor = RGB( 36, 33, 32);
#ifdef LOCALE_NHNUSA
	DlgInfo.nTextColor = RGB( 46, 47, 48);
	DlgInfo.nTextBkColor = RGB( 150, 150, 150);
#endif
	SetDialogInfo( DlgInfo);

	m_pParentDialog = NULL;
}


// DoDataExchange
void CNewAppLicenseConfirmDlg::DoDataExchange( CDataExchange* pDX)
{
	CDDBDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewAppLicenseConfirmDlg)
	DDX_Control(pDX, IDC_LICENSE, m_cLicense);
	DDX_Control(pDX, IDC_MESSAGE, m_cMessage);
	DDX_Control(pDX, IDOK,        m_cAgree);
	DDX_Control(pDX, IDCANCEL,    m_cDeny);
	//}}AFX_DATA_MAP
}


// Message map
BEGIN_MESSAGE_MAP( CNewAppLicenseConfirmDlg, CDDBDialog)
	//{{AFX_MSG_MAP(CNewAppLicenseConfirmDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/************************************************************************************
  클래스 메세지 핸들러
*************************************************************************************/
// OnInitDialog : 다이얼로그를 초기화는 함수
BOOL CNewAppLicenseConfirmDlg::OnInitDialog() 
{
	CDDBDialog::OnInitDialog();


	// 윈도우 이동
	if ( m_pParentDialog != NULL)
	{
		CRect rect;
		m_pParentDialog->GetWindowRect( &rect);
		int x = rect.left + rect.Width() / 2 - GetWidth() / 2;
		int y = rect.top + rect.Height() / 2 - GetHeight() / 2;
		MoveWindow( x, y, GetWidth(), GetHeight());
	}
	else
	{
		//현재 컴퓨터 창 크기
		int sx = GetSystemMetrics( SM_CXSCREEN) - GetSystemMetrics( SM_CXICON);
		int sy = GetSystemMetrics( SM_CYSCREEN) - GetSystemMetrics( SM_CYICON);

		MoveWindow( (sx - GetWidth()) / 2, (sy - GetHeight()) / 2, GetWidth(), GetHeight());
	}


	// 버튼 초기화
	m_cAgree.InitDDBButton( IDR_BMP_BUTTON, IDR_WAV_PUSHBUTTON);
	m_cDeny.InitDDBButton( IDR_BMP_BUTTON, IDR_WAV_PUSHBUTTON);


	// 캡션 표시
	SetWindowText( m_strCaption);
	GetScreen()->PutText(  9, 5, 17, "Arial", m_strCaption, RGB( 0, 0, 0), TS_BOLD);
	GetScreen()->PutText( 10, 6, 17, "Arial", m_strCaption, RGB( 238, 156, 0), TS_BOLD);


	// 텍스트 출력
	GetScreen()->PutText( 0, 0, GetWidth(), GetHeight(), 20, "Arial", "Cannot find the license file.", GetTextColor(), 0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	// 라이센스 표시
	char szCurrDir[ 512];
	GetCurrentDirectory( sizeof( szCurrDir), szCurrDir);

	char szAddress[ _MAX_DIR];
	sprintf( szAddress, "file://%s\\%s", szCurrDir, m_strFileName.GetBuffer());

	char szFullPath[ _MAX_DIR];
	sprintf( szFullPath, "%s\\%s", szCurrDir, m_strFileName.GetBuffer());

	WIN32_FIND_DATA findfile;
	HANDLE hFind = FindFirstFile( szFullPath, &findfile);

	if ( hFind != INVALID_HANDLE_VALUE)
	{
		m_cLicense.Navigate( szAddress, NULL, NULL, NULL, NULL);
		m_cLicense.MoveWindow( 13, 31, GetWidth() - 26, GetHeight() - 120);
	}
	else
	{
		// 파일이 없으면
		m_cLicense.MoveWindow( 13, 31, 0, 0);
	}
	FindClose( hFind);


	// 메시지 표시
	m_cMessage.MoveWindow( 13, GetHeight() - 80, GetWidth() - 26, 40);
	m_cMessage.SetWindowText( m_strMessage);


	// 버튼 초기화
	m_cAgree.SetWindowText( m_strAgree);
	m_cAgree.ShowWindow( SW_SHOW);
	m_cAgree.EnableWindow( TRUE);
	m_cAgree.SetBlanking( TRUE, 500);
	m_cAgree.MoveWindow( GetWidth() / 2 - m_cAgree.GetWidth() - 5, GetHeight() - 35);

	m_cDeny.SetWindowText( m_strDeny);
	m_cDeny.ShowWindow( SW_SHOW);
	m_cDeny.EnableWindow( TRUE);
	m_cDeny.MoveWindow( GetWidth() / 2 + 5, GetHeight() - 35);


	return true;
}


// SetDialog
void CNewAppLicenseConfirmDlg::SetDialog( CDialog* pDialog, CString strCaption, CString strFileName, CString strMessage, CString strAgree, CString strDeny)
{
	m_pParentDialog = pDialog;
	m_strCaption = strCaption;
	m_strFileName = strFileName;
	m_strMessage = strMessage;
	m_strAgree = strAgree;
	m_strDeny = strDeny;
}
