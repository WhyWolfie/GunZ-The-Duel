
#include "stdafx.h"
#include "NewAppWarnVista.h"



/************************************************************************************
  Dialog
*************************************************************************************/
// 클래스 생성자
CNewAppWarnVista::CNewAppWarnVista( CWnd* pParent) : CDDBDialog( IDD_WARNVISTA, pParent)
{
	//{{AFX_DATA_INIT( CNewAppWarnVista)
	//}}AFX_DATA_INIT

	// 이곳에서 생성할 다이얼로그의 정보를 입력한다
	// 좀 더 자세한 설명을 원하면 CDDBDialog.h 화일의 Structure of CDDBDIALOGINFO 내용을 참고한다
	CDDBDLGINFO DlgInfo;
	DlgInfo.nWidth = 380;
	DlgInfo.nHeight = 230;
	DlgInfo.IDSkinResource = IDR_BMP_POPUPDLG;
	DlgInfo.nTextColor = RGB( 120, 30, 30);
	DlgInfo.nTextBkColor = RGB( 166, 156, 153);
#ifdef LOCALE_NHNUSA
	DlgInfo.nTextColor = RGB( 150, 150, 150);
	DlgInfo.nTextBkColor = RGB( 46, 47, 48);
#endif
	SetDialogInfo( DlgInfo);


	// 변수 초기화
	m_bCheck = false;
}


// DoDataExchange
void CNewAppWarnVista::DoDataExchange( CDataExchange* pDX)
{
	CDDBDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewAppWarnVista)
	DDX_Control(pDX, IDC_MESSAGE, m_cMessage);
	DDX_Control(pDX, IDC_CHECK,	  m_cCheck);
	DDX_Control(pDX, IDOK,        m_cOK);
	DDX_Control(pDX, IDCANCEL,    m_cCancel);
	//}}AFX_DATA_MAP
}


// Message map
BEGIN_MESSAGE_MAP( CNewAppWarnVista, CDDBDialog)
	//{{AFX_MSG_MAP(CNewAppWarnVista)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/************************************************************************************
  클래스 메세지 핸들러
*************************************************************************************/
// OnInitDialog : 다이얼로그를 초기화는 함수
BOOL CNewAppWarnVista::OnInitDialog() 
{
	CDDBDialog::OnInitDialog();


	// 윈도우 이동
	CRect rect;
	GetWindowRect( &rect);
	int x = rect.left + rect.Width() / 2 - GetWidth() / 2;
	int y = rect.top + rect.Height() / 2 - GetHeight() / 2;
	MoveWindow( x, y, GetWidth(), GetHeight());
	

	// 패널 그리기
	DrawPanel( 6, 25, GetWidth()-12, GetHeight()-31);


	// 버튼 초기화
	m_cOK.InitDDBButton( IDR_BMP_BUTTON, IDR_WAV_PUSHBUTTON);
	m_cCancel.InitDDBButton( IDR_BMP_BUTTON, IDR_WAV_PUSHBUTTON);


	// 캡션 표시
	SetWindowText( m_strCaption);
	GetScreen()->PutText(  9, 5, 17, "Arial", m_strCaption, RGB( 0, 0, 0), TS_BOLD);
	GetScreen()->PutText( 10, 6, 17, "Arial", m_strCaption, RGB( 238, 156, 0), TS_BOLD);


	// 메시지 표시
	m_cMessage.SetWindowText( m_strMessage);


	// 체크박스 설정
	m_cCheck.MoveWindow( 25, GetHeight() - 70, 15, 15);
	GetScreen()->PutText( 42, GetHeight() - 70, 15, "Arial", "Do not display this message again.", GetTextColor());


	// 버튼 초기화
	if ( m_nButtonType == MB_OKCANCEL)
	{
		m_cOK.SetWindowText( "OK");
		m_cOK.ShowWindow( SW_SHOW);
		m_cOK.EnableWindow( TRUE);
		m_cOK.MoveWindow( GetWidth() / 2 - m_cOK.GetWidth() - 5, GetHeight() - 35);

		m_cCancel.SetWindowText( "Cancel");
		m_cCancel.ShowWindow( SW_SHOW);
		m_cCancel.EnableWindow( TRUE);
		m_cCancel.MoveWindow( GetWidth() / 2 + 5, GetHeight() - 35);
	}
	else if ( m_nButtonType == MB_YESNO)
	{
		m_cOK.SetWindowText( "Yes");
		m_cOK.ShowWindow( SW_SHOW);
		m_cOK.EnableWindow( TRUE);
		m_cOK.MoveWindow( GetWidth() / 2 - m_cOK.GetWidth() - 5, GetHeight() - 35);

		m_cCancel.SetWindowText( "No");
		m_cCancel.ShowWindow( SW_SHOW);
		m_cCancel.EnableWindow( TRUE);
		m_cCancel.MoveWindow( GetWidth() / 2 + 5, GetHeight() - 35);
	}
	else if ( m_nButtonType == MB_OK)
	{
		m_cOK.SetWindowText( "OK");
		m_cOK.ShowWindow( SW_SHOW);
		m_cOK.EnableWindow( TRUE);
		m_cOK.MoveWindow( GetWidth() / 2 - m_cOK.GetWidth() / 2, GetHeight() - 35);

		m_cCancel.ShowWindow( SW_HIDE);
	}


	return true;
}


// SetDialog
void CNewAppWarnVista::SetDialog( CString strCaption, CString strMessage, UINT nButtonType)
{
	m_strCaption = strCaption;
	m_strMessage = strMessage;
	m_nButtonType = nButtonType;
}


// OK
void CNewAppWarnVista::OnOK()
{
	if ( m_cCheck.GetCheck() > 0)
		m_bCheck = true;
	else
		m_bCheck = false;

	CDDBDialog::OnOK();
}
