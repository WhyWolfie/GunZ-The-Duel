
#include "stdafx.h"
#include "NewAppErrorDlg.h"



/************************************************************************************
  Dialog
*************************************************************************************/
// 클래스 생성자
CNewAppErrorDlg::CNewAppErrorDlg( CWnd* pParent) : CDDBDialog( IDD_ERRORDLG, pParent)
{
	//{{AFX_DATA_INIT( CNewAppErrorDlg)
	//}}AFX_DATA_INIT

	// 이곳에서 생성할 다이얼로그의 정보를 입력한다
	// 좀 더 자세한 설명을 원하면 CDDBDialog.h 화일의 Structure of CDDBDIALOGINFO 내용을 참고한다
	CDDBDLGINFO DlgInfo;
	DlgInfo.nWidth = 600;
	DlgInfo.nHeight = 430;
	DlgInfo.IDSkinResource = IDR_BMP_POPUPDLG;
	DlgInfo.nTextColor = RGB( 30, 30, 30);
	DlgInfo.nTextBkColor = RGB( 196, 186, 183);
#ifdef LOCALE_NHNUSA
	DlgInfo.nTextColor = RGB( 150, 150, 150);
	DlgInfo.nTextBkColor = RGB( 46, 47, 48);
#endif
	SetDialogInfo( DlgInfo);


	m_pParentDialog = NULL;
	m_pstrErrorMessage = NULL;
}


// DoDataExchange
void CNewAppErrorDlg::DoDataExchange( CDataExchange* pDX)
{
	CDDBDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewAppErrorDlg)
	DDX_Control(pDX, IDC_MESSAGE, m_cMessage);
	DDX_Control(pDX, IDC_ERRORLIST, m_cErrorList);
	DDX_Control(pDX, IDOK, m_cOK);
	DDX_Control(pDX, IDC_SHOWLOG, m_cShowLog);
	//}}AFX_DATA_MAP
}


// Message map
BEGIN_MESSAGE_MAP( CNewAppErrorDlg, CDDBDialog)
	//{{AFX_MSG_MAP(CNewAppErrorDlg)
	ON_BN_CLICKED(IDC_SHOWLOG, OnBnClickedShowlog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/************************************************************************************
  클래스 메세지 핸들러
*************************************************************************************/
// OnInitDialog : 다이얼로그를 초기화는 함수
BOOL CNewAppErrorDlg::OnInitDialog() 
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


	// 컨트롤 초기화
	char szString[ 512];
	m_cMessage.SetWindowText( m_strMessage);


	// 에러 메시지 출력
	m_cErrorList.ResetContent();
	m_cErrorList.SetHorizontalExtent( 1000);
	if ( m_pstrErrorMessage)
	{
		int nCount = 0;
		for ( int i = 0;  i < m_pstrErrorMessage->GetLength();  i++)
		{
			szString[ nCount] = m_pstrErrorMessage->GetAt( i);
			if ( szString[ nCount] == '\n')
			{
				szString[ nCount] = '\0';
				m_cErrorList.AddString( szString);
				nCount = 0;
			}
			else
				nCount++;
		}
	}


	// 콘트롤 이동
	GetDlgItem( IDC_MESSAGE)->MoveWindow( 18, 40, 564, 57, TRUE);
	GetDlgItem( IDC_ERRORLIST)->MoveWindow( 14, 125, 572, 252, TRUE);


	// 패널 그리기
	DrawPanel( 6, 25, GetWidth()-12, GetHeight()-31);
	GetScreen()->PutFillBox( 13, 39, 574, 59, GetTextBkColor());
	GetScreen()->PutBox( 13, 39, 574, 59, RGB( 120, 120, 120));
	GetScreen()->PutText( 14, 107, 15, "Arial", "Error messages :", GetTextColor(), TS_BOLD);
	GetScreen()->PutBox( 13, 124, 574, 254, RGB( 120, 120, 120));

	// 버튼 초기화
	m_cOK.InitDDBButton( IDR_BMP_BUTTON, IDR_WAV_PUSHBUTTON);
	m_cShowLog.InitDDBButton( IDR_BMP_BUTTON, IDR_WAV_PUSHBUTTON);


	// 캡션 표시
	SetWindowText( m_strCaption);
	GetScreen()->PutText(  9, 5, 17, "Arial", m_strCaption, RGB( 0, 0, 0), TS_BOLD);
	GetScreen()->PutText( 10, 6, 17, "Arial", m_strCaption, RGB( 220, 30, 30), TS_BOLD);


	// 버튼 초기화
	m_cShowLog.SetWindowText( "Show log...");
	m_cShowLog.ShowWindow( SW_SHOW);
	m_cShowLog.EnableWindow( TRUE);
	m_cShowLog.MoveWindow( GetWidth() / 2 - m_cOK.GetWidth() - 10, GetHeight() - 35);

	m_cOK.SetWindowText( "OK");
	m_cOK.ShowWindow( SW_SHOW);
	m_cOK.EnableWindow( TRUE);
	m_cOK.MoveWindow( GetWidth() / 2 + 10, GetHeight() - 35);


	return true;
}


// SetDialog
void CNewAppErrorDlg::SetDialog( CDialog* pDialog, CString strCaption, CString strMessage, CString* pstrErrorMessage, UINT nButtonType)
{
	m_pParentDialog = pDialog;
	m_strCaption = strCaption;
	m_strMessage = strMessage;
	m_pstrErrorMessage = pstrErrorMessage;
	m_nButtonType = nButtonType;
}


// OnBnClickedShowlog
void CNewAppErrorDlg::OnBnClickedShowlog()
{
	WinExec( "notepad.exe patchlog.txt", SW_SHOW);
}