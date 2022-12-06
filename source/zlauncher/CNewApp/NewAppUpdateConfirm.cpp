
#include "stdafx.h"
#include "NewAppUpdateConfirm.h"
#include <Mmsystem.h>


/************************************************************************************
  Dialog
*************************************************************************************/
// 클래스 생성자
CNewAppUpdateConfirm::CNewAppUpdateConfirm( CWnd* pParent) : CDDBDialog( IDD_UPDATE_CONFIRM, pParent)
{
	//{{AFX_DATA_INIT( CNewAppUpdateConfirm)
	//}}AFX_DATA_INIT

	// 이곳에서 생성할 다이얼로그의 정보를 입력한다
	// 좀 더 자세한 설명을 원하면 CDDBDialog.h 화일의 Structure of CDDBDIALOGINFO 내용을 참고한다
	CDDBDLGINFO DlgInfo;
	DlgInfo.nWidth = 330;
	DlgInfo.nHeight = 180;
	DlgInfo.IDSkinResource = IDR_BMP_POPUPDLG;
	DlgInfo.nTextColor = RGB( 30, 30, 30);
	DlgInfo.nTextBkColor = RGB( 166, 156, 153);
#ifdef LOCALE_NHNUSA
	DlgInfo.nTextColor = RGB( 150, 150, 150);
	DlgInfo.nTextBkColor = RGB( 46, 47, 48);
#endif
	SetDialogInfo( DlgInfo);


	m_pParentDialog = NULL;
}


// DoDataExchange
void CNewAppUpdateConfirm::DoDataExchange( CDataExchange* pDX)
{
	CDDBDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewAppUpdateConfirm)
	DDX_Control(pDX, IDC_MESSAGE, m_cMessage);
	DDX_Control(pDX, IDOK,        m_cOK);
	DDX_Control(pDX, IDCANCEL,    m_cCancel);
	//}}AFX_DATA_MAP
}


// Message map
BEGIN_MESSAGE_MAP( CNewAppUpdateConfirm, CDDBDialog)
	//{{AFX_MSG_MAP(CNewAppUpdateConfirm)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/************************************************************************************
  클래스 메세지 핸들러
*************************************************************************************/
// OnInitDialog : 다이얼로그를 초기화는 함수
BOOL CNewAppUpdateConfirm::OnInitDialog() 
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
	m_cMessage.MoveWindow( 13, 35, GetWidth() - 26, GetHeight() - 70);
	PutMessage( 10);


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


	// 경과 시간 초기화
	m_dwTime = timeGetTime();


	// 타이머 시작
	SetTimer( 0, 500, NULL);


	return true;
}


// SetDialog
void CNewAppUpdateConfirm::SetDialog( CDialog* pDialog, CString strCaption, CString strMessage, UINT nButtonType)
{
	m_pParentDialog = pDialog;
	m_strCaption = strCaption;
	m_strMessage = strMessage;
	m_nButtonType = nButtonType;
}


// Timer
void CNewAppUpdateConfirm::OnTimer(UINT nIDEvent)
{
	// 업데이트 타이머
	if ( nIDEvent == 0)
	{
		// 경과 시간을 구한다
		DWORD dwCurrTime = timeGetTime() - m_dwTime;

		if ( dwCurrTime > 10000)
		{
			KillTimer( 0);

			// 종료
			OnOK();

			return;
		}

		// 메시지 표시
		PutMessage( 10 - (dwCurrTime / 1000) - 1);
	}

	CDDBDialog::OnTimer(nIDEvent);
}


// 메시지 출력
void CNewAppUpdateConfirm::PutMessage( int nTime)
{
	// 메시지 표시
	CString strMsg;
	strMsg.Format( m_strMessage.GetBuffer(), nTime);
	m_cMessage.SetWindowText( strMsg);
}
