/*
 CDDBDialog 클래스(CDDBDialog.cpp)

  desc : CDialog를 상속받아서 GUI 다이얼로그를 사용할 수 있게 해주는 클래스.
  date : 2004년 5월 30일
  comp : 고려대학교 제어계측연구회(KUCIRA) - 임동환
         http://www.kucira.com
  text : MFC를 공부하는 사람 누구나 자유 배포 및 수정이 가능합니다. 단, 특정 개인이나
         단체의 이익을 위한 목적으로 사용되는 것은 금합니다.
*/


#include "stdafx.h"										// Include stdafx
#include "CDDBDialog.h"									// Include CDDBDialog
#include ".\cddbdialog.h"


// Functions
static int GetX( int x, int y)					{ return x; }
static int GetY( int x, int y)					{ return y; }



/********************************************************************
 Skin map
*********************************************************************/
// Dialog의 이미지 좌표 및 크기
#define IMG_DIALOGDEFAULT						0,   0
#define SIZE_DIALOGDEFAULT						20,  20

// Dialog titlebar의 이미지 좌표 및 크기
#define IMG_TITLEBARDEFAULT						126, 0
#define SIZE_TITLEBARDEFAULT					21,  21

// Dialog captionbar의 이미지 좌표 및 크기
#define IMG_CAPTIONBARDEFAULT					126, 22
#define SIZE_CAPTIONBARDEFAULT					16, 16

// Dialog title의 이미지 좌표 및 크기
#define IMG_BMPTITLEDEFAULT						180, 26
#ifdef LOCALE_NHNUSA
#define SIZE_BMPTITLEDEFAULT					115, 20
#elif LOCALE_BRAZIL
#define SIZE_BMPTITLEDEFAULT					134, 15
#else
#define SIZE_BMPTITLEDEFAULT					115, 15
#endif

// Panel의 이미지 좌표 및 크기
#define IMG_PANELDEFAULT						63,  0
#define SIZE_PANELDEFAULT						20,  20

// Panel title bar의 이미지 좌표 및 크기
#define IMG_PANELTITLEBARDEFAULT				126, 39
#define SIZE_PANELTITLEBARDEFAULT				17,  16

// Panel icons의 이미지 좌표 및 크기
#define IMG_PANELICONDEFAULT					0,   63
#define SIZE_PANELICONDEFAULT					84,  80

// About button의 이미지 좌표 및 크기
#define IMG_ABOUTBUTTONDEFAULT					192, 0
#define SIZE_ABOUTBUTTONDEFAULT					12,  12

// Minimize button의 이미지 좌표 및 크기
#define IMG_MINIMIZEBUTTONDEFAULT				244, 0
#define SIZE_MINIMIZEBUTTONDEFAULT				12,  12

// Maximize button의 이미지 좌표 및 크기
#define IMG_MAXIMIZEBUTTONDEFAULT				192, 13
#define SIZE_MAXIMIZEBUTTONDEFAULT				12,  12

// Quit button의 이미지 좌표 및 크기
#define IMG_QUITBUTTONDEFAULT					244, 13
#define SIZE_QUITBUTTONDEFAULT					12,  12

// Menu button의 이미지 좌표 및 크기
#define IMG_MENUBUTTONDEFAULT					336, 0
#define SIZE_MENUBUTTONDEFAULT					26,  28


/************************************************************************************
  CDDBDialog
*************************************************************************************/
// CDDBDialog
CDDBDialog::CDDBDialog( UINT nIDTemplate, CWnd* pParentWnd)
{
	m_pParentWnd			= pParentWnd;
	m_lpszTemplateName		= MAKEINTRESOURCE( nIDTemplate);
	m_nIDHelp				= nIDTemplate;
	m_bMouseLButton			= false;
	m_bInitialized			= false;
}


// ~CDDBDialog
CDDBDialog::~CDDBDialog()
{
	// Delete DC
	m_Screen.DeleteDDB();								// Delete DDB of screen
	m_Render.DeleteDDB();								// Delete DDB of rendering
	m_Skin.DeleteDDB();									// Delete DDB of skin


	// Delete m_TrayIcon
	DeleteTrayicon();
}


// DoDataExchange
void CDDBDialog::DoDataExchange( CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDDBDialog)
	//}}AFX_DATA_MAP
}


// Message map
BEGIN_MESSAGE_MAP(CDDBDialog, CDialog)
	//{{AFX_MSG_MAP(CDDBDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_WINDOWPOSCHANGING()
	//ON_WM_NCHITTEST()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_ABOUTBOX, OnAboutbox)
	ON_BN_CLICKED(IDC_MAXIMIZE, OnMaximize)
	ON_BN_CLICKED(IDC_MINIMIZE, OnMinimize)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_MESSAGE(WM_MOUSEDRAG, OnMouseDrag)
	ON_MESSAGE(WM_TRAYICON_NOTIFY, OnTrayNotification)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/************************************************************************************
  CDDBDialog message handlers
*************************************************************************************/
// OnInitDialog
BOOL CDDBDialog::OnInitDialog()
{
	CDialog::OnInitDialog();


	// DDB를 생성한다.
	if ( m_DlgInfo.IDSkinResource != NULL)
	{
		// Create skin m_Screen
		if ( !m_Skin.CreateDDB( m_Screen.GetDC(), m_DlgInfo.IDSkinResource))
		{
			OutputDebugString( "ERROR : 스킨 DDB를 생성할 수 없습니다.\n");
			MessageBox( "초기화 하는 도중에 오류가 발생하였습니다.   ", "Error", MB_OK);
			return false;
		}
	}
	else
	{
		// Create skin m_Screen
		if ( !m_Skin.CreateDDB( m_Screen.GetDC(), m_DlgInfo.nWidth, m_DlgInfo.nHeight, RGB( 200, 200, 200)))
		{
			OutputDebugString( "ERROR : 스킨 DDB를 생성할 수 없습니다.\n");
			MessageBox( "초기화 하는 도중에 오류가 발생하였습니다.   ", "Error", MB_OK);
			return false;
		}
	}


	// Create rendering m_Screen
	if ( m_DlgInfo.bEnableRenderingLayer)
	{
		if ( !m_Render.CreateDDB( GetDC(), m_DlgInfo.nWidth, m_DlgInfo.nHeight, RGB( 200, 200, 200)))
		{
			OutputDebugString( "ERROR : Rendering DDB를 생성할 수 없습니다.\n");
			MessageBox( "초기화 하는 도중에 오류가 발생하였습니다.   ", "Error", MB_OK);
			return false;
		}
	}


	// Create drawing m_Screen
	if ( !m_Screen.CreateDDB( GetDC(), m_DlgInfo.nWidth, m_DlgInfo.nHeight, RGB( 200, 200, 200)))
	{
		OutputDebugString( "ERROR : Screen DDB를 생성할 수 없습니다.\n");
		MessageBox( "초기화 하는 도중에 오류가 발생하였습니다.   ", "Error", MB_OK);
		return false;
	}


	// 윈도우 스타일 변경
	ModifyStyle( WS_CAPTION, WS_MINIMIZEBOX | WS_POPUP | WS_CLIPCHILDREN | WS_SYSMENU);
	ModifyStyleEx( WS_EX_DLGMODALFRAME, 0);


	// 윈도우 위치 및 모양 크기 초기화
#ifndef LOCALE_NHNUSA
	m_Rgn.CreateRoundRectRgn( 0, 0, GetWidth()+1, GetHeight()+1, 15, 15);
	SetWindowRgn( m_Rgn, TRUE);
#endif

	CRect rect;
	GetWindowRect( &rect);
	rect.right  = rect.left + m_DlgInfo.nWidth;
	rect.bottom = rect.top  + m_DlgInfo.nHeight;
	MoveWindow( rect, true);


	// 윈도우 오브젝트 배경 및 글씨 색상 설정
	m_brushCtlColor.CreateSolidBrush(m_DlgInfo.nTextBkColor);


	// 다이얼로그 윈도우 그리기
	DrawDialogWindow();


	// 윈도우 타이틀 그리기
	CString strTitle;
	GetWindowText( strTitle);
	SetWindowText( strTitle);


	// 다이얼로그 아이콘 설정
	if ( m_DlgInfo.IDIconResource != NULL)
	{
		m_hIcon = AfxGetApp()->LoadIcon( m_DlgInfo.IDIconResource);
		SetIcon( m_hIcon, true);
		SetIcon( m_hIcon, false);
	}


	// 시스템 버튼 생성
	m_Tooltip.Create( this);
	int pos = m_DlgInfo.nWidth - 4;
	if ( m_DlgInfo.bUseQuitButton)						// Create quit button
	{
		pos -= GetX(SIZE_QUITBUTTONDEFAULT);
		CreateQuitButton( pos, 4);
	}
	if ( m_DlgInfo.bUseMaximizeButton)					// Create maximize button
	{
		pos -= GetX(SIZE_MAXIMIZEBUTTONDEFAULT);
		CreateMaximizeButton( pos, 4);
	}
	if ( m_DlgInfo.bUseMinimizeButton)					// Create minimize button
	{
		pos -= GetX(SIZE_MINIMIZEBUTTONDEFAULT);
		CreateMinimizeButton( pos, 4);
	}
	if ( m_DlgInfo.bUseAboutboxButton)					// Create about button
	{
		pos -= GetX(SIZE_ABOUTBUTTONDEFAULT);
		CreateAboutButton( pos, 4);
	}


	// 파일 드래그 앤 드롭 사용 여부
	DragAcceptFiles( m_DlgInfo.bEnableDragAndDrop);


	// Rendering
	Rendering();


	// Complete initialize
	m_bInitialized = true;


	return true;
}


// CreateAboutButton
void CDDBDialog::CreateAboutButton( int x, int y)
{
	// Create button
	m_cButtonAbout.Create( _T( ""),
		                   WS_CHILD|WS_VISIBLE | BS_PUSHBUTTON,
		                   CRect( x, y, x+GetX(SIZE_ABOUTBUTTONDEFAULT), y+GetY(SIZE_ABOUTBUTTONDEFAULT)),
						   this, IDC_ABOUTBOX);
	m_cButtonAbout.InitDDBButton( m_Skin.GetDC(), IMG_ABOUTBUTTONDEFAULT, SIZE_ABOUTBUTTONDEFAULT, m_DlgInfo.IDWaveResource);


	// Tooltip
	m_Tooltip.AddTool( &m_cButtonAbout, _T( "About"));
}


// CreateMinimizeButton
void CDDBDialog::CreateMinimizeButton( int x, int y)
{
	// Create button
	m_cButtonMinimize.Create( _T( ""),
			                    WS_CHILD|WS_VISIBLE | BS_PUSHBUTTON,
			                    CRect( x, y, x+GetX(SIZE_MINIMIZEBUTTONDEFAULT), y+GetY(SIZE_MINIMIZEBUTTONDEFAULT)),
								this, IDC_MINIMIZE);
	m_cButtonMinimize.InitDDBButton( m_Skin.GetDC(), IMG_MINIMIZEBUTTONDEFAULT, SIZE_MINIMIZEBUTTONDEFAULT, m_DlgInfo.IDWaveResource);


	// Tooltip
	m_Tooltip.AddTool( &m_cButtonMinimize, _T( "Minimize"));
}


// CreateMaximizeButton
void CDDBDialog::CreateMaximizeButton( int x, int y)
{
	// Create button
	m_cButtonMaximize.Create( _T( ""),
			                    WS_CHILD|WS_VISIBLE | BS_PUSHBUTTON,
			                    CRect( x, y, x+GetX(SIZE_MAXIMIZEBUTTONDEFAULT), y+GetY(SIZE_MAXIMIZEBUTTONDEFAULT)),
								this, IDC_MAXIMIZE);
	m_cButtonMaximize.InitDDBButton( m_Skin.GetDC(), IMG_MAXIMIZEBUTTONDEFAULT, SIZE_MAXIMIZEBUTTONDEFAULT, m_DlgInfo.IDWaveResource);


	// Tooltip
	m_Tooltip.AddTool( &m_cButtonMaximize, _T( "Maximize"));
}


// CreateQuitButton
void CDDBDialog::CreateQuitButton( int x, int y)
{
	// Create button
	m_cButtonQuit.Create( _T( ""),
			                WS_CHILD|WS_VISIBLE | BS_PUSHBUTTON,
			                CRect( x, y, x+GetX(SIZE_QUITBUTTONDEFAULT), y+GetY(SIZE_QUITBUTTONDEFAULT)),
							this, IDC_QUIT);
	m_cButtonQuit.InitDDBButton( m_Skin.GetDC(), IMG_QUITBUTTONDEFAULT, SIZE_QUITBUTTONDEFAULT, m_DlgInfo.IDWaveResource);


	// Tooltip
	m_Tooltip.AddTool( &m_cButtonQuit, _T( "Quit"));
}


// DrawDialogWindow
void CDDBDialog::DrawDialogWindow()
{
	// 다이얼로그 배경 그림
	int dy = 0;
	if ( m_DlgInfo.bUseTitlebar)
		dy = GetY( SIZE_TITLEBARDEFAULT);

	CRect rect;
	GetWindowRect( &rect);
	m_Screen.FillTiledBitmap( 0, 0, rect.Width(), rect.Height(), m_Skin.GetDC(), GetX(IMG_DIALOGDEFAULT)+GetX(SIZE_DIALOGDEFAULT)+1, GetY(IMG_DIALOGDEFAULT)+GetY(SIZE_DIALOGDEFAULT)+1, SIZE_DIALOGDEFAULT);
	m_Screen.FillTiledBitmap( 0, GetY(SIZE_DIALOGDEFAULT), GetX(SIZE_DIALOGDEFAULT), rect.Height()-2*GetY(SIZE_DIALOGDEFAULT), m_Skin.GetDC(), GetX(IMG_DIALOGDEFAULT), GetY(IMG_DIALOGDEFAULT)+GetY(SIZE_DIALOGDEFAULT)+1, SIZE_DIALOGDEFAULT);
	m_Screen.FillTiledBitmap( rect.Width()-GetX(SIZE_DIALOGDEFAULT), GetY(SIZE_DIALOGDEFAULT), GetX(SIZE_DIALOGDEFAULT), rect.Height()-2*GetY(SIZE_DIALOGDEFAULT), m_Skin.GetDC(), GetX(IMG_DIALOGDEFAULT)+GetX(SIZE_DIALOGDEFAULT)+1+GetX(SIZE_DIALOGDEFAULT)+1, GetY(IMG_DIALOGDEFAULT)+GetY(SIZE_DIALOGDEFAULT)+1, SIZE_DIALOGDEFAULT);
	m_Screen.FillTiledBitmap( 0, 0, rect.Width(), GetY(SIZE_DIALOGDEFAULT), m_Skin.GetDC(), GetX(IMG_DIALOGDEFAULT)+GetX(SIZE_DIALOGDEFAULT)+1, GetY(IMG_DIALOGDEFAULT), SIZE_DIALOGDEFAULT);
	m_Screen.FillTiledBitmap( 0, rect.Height()-GetY(SIZE_DIALOGDEFAULT), rect.Width(), GetY(SIZE_DIALOGDEFAULT), m_Skin.GetDC(), GetX(IMG_DIALOGDEFAULT)+GetX(SIZE_DIALOGDEFAULT)+1, GetY(IMG_DIALOGDEFAULT)+GetY(SIZE_DIALOGDEFAULT)+1+GetY(SIZE_DIALOGDEFAULT)+1, SIZE_DIALOGDEFAULT);
	m_Screen.PutBitmap( 0, 0, m_Skin.GetDC(), GetX(IMG_DIALOGDEFAULT), GetY(IMG_DIALOGDEFAULT), SIZE_DIALOGDEFAULT, SRCCOPY);
	m_Screen.PutBitmap( rect.Width()-GetX(SIZE_DIALOGDEFAULT), 0, m_Skin.GetDC(), GetX(IMG_DIALOGDEFAULT)+GetX(SIZE_DIALOGDEFAULT)+1+GetX(SIZE_DIALOGDEFAULT)+1, GetY(IMG_DIALOGDEFAULT), SIZE_DIALOGDEFAULT, SRCCOPY);
	m_Screen.PutBitmap( 0, rect.Height()-GetY(SIZE_DIALOGDEFAULT), m_Skin.GetDC(), GetX(IMG_DIALOGDEFAULT), GetY(IMG_DIALOGDEFAULT)+GetY(SIZE_DIALOGDEFAULT)+1+GetY(SIZE_DIALOGDEFAULT)+1, SIZE_DIALOGDEFAULT, SRCCOPY);
	m_Screen.PutBitmap( rect.Width()-GetX(SIZE_DIALOGDEFAULT), rect.Height()-GetY(SIZE_DIALOGDEFAULT), m_Skin.GetDC(), GetX(IMG_DIALOGDEFAULT)+GetX(SIZE_DIALOGDEFAULT)+1+GetX(SIZE_DIALOGDEFAULT)+1, GetY(IMG_DIALOGDEFAULT)+GetX(SIZE_DIALOGDEFAULT)+1+GetY(SIZE_DIALOGDEFAULT)+1, SIZE_DIALOGDEFAULT, SRCCOPY);
}


// DrawPanel
void CDDBDialog::DrawPanel( int x, int y, int width, int height, LPCTSTR lpszTitle)
{
	// Draw Panel
	m_Screen.FillTiledBitmap( x, y, width, height, m_Skin.GetDC(), GetX(IMG_PANELDEFAULT)+GetX(SIZE_PANELDEFAULT)+1, GetY(IMG_PANELDEFAULT)+GetY(SIZE_PANELDEFAULT)+1, SIZE_PANELDEFAULT);
	m_Screen.FillTiledBitmap( x, y, GetX(SIZE_PANELDEFAULT), height, m_Skin.GetDC(), GetX(IMG_PANELDEFAULT), GetY(IMG_PANELDEFAULT)+GetY(SIZE_PANELDEFAULT)+1, SIZE_PANELDEFAULT);
	m_Screen.FillTiledBitmap( x+width-GetX(SIZE_PANELDEFAULT), y, GetX(SIZE_PANELDEFAULT), height, m_Skin.GetDC(), GetX(IMG_PANELDEFAULT)+GetX(SIZE_PANELDEFAULT)+1+GetX(SIZE_PANELDEFAULT)+1, GetY(IMG_PANELDEFAULT)+GetY(SIZE_PANELDEFAULT)+1, SIZE_PANELDEFAULT);
	m_Screen.FillTiledBitmap( x, y, width, GetY(SIZE_PANELDEFAULT), m_Skin.GetDC(), GetX(IMG_PANELDEFAULT)+GetX(SIZE_PANELDEFAULT)+1, GetY(IMG_PANELDEFAULT), SIZE_PANELDEFAULT);
	m_Screen.FillTiledBitmap( x, y+height-GetX(SIZE_PANELDEFAULT), width, GetY(SIZE_PANELDEFAULT), m_Skin.GetDC(), GetX(IMG_PANELDEFAULT)+GetX(SIZE_PANELDEFAULT)+1, GetY(IMG_PANELDEFAULT)+GetY(SIZE_PANELDEFAULT)+1+GetY(SIZE_PANELDEFAULT)+1, SIZE_PANELDEFAULT);
	m_Screen.PutBitmap( x, y, m_Skin.GetDC(), GetX(IMG_PANELDEFAULT), GetY(IMG_PANELDEFAULT), SIZE_PANELDEFAULT, SRCCOPY);
	m_Screen.PutBitmap( x+width-GetX(SIZE_PANELDEFAULT), y, m_Skin.GetDC(), GetX(IMG_PANELDEFAULT)+GetX(SIZE_PANELDEFAULT)+1+GetX(SIZE_PANELDEFAULT)+1, GetY(IMG_PANELDEFAULT), SIZE_PANELDEFAULT, SRCCOPY);
	m_Screen.PutBitmap( x, y+height-GetX(SIZE_PANELDEFAULT), m_Skin.GetDC(), GetX(IMG_PANELDEFAULT), GetY(IMG_PANELDEFAULT)+GetY(SIZE_PANELDEFAULT)+1+GetY(SIZE_PANELDEFAULT)+1, SIZE_PANELDEFAULT, SRCCOPY);
	m_Screen.PutBitmap( x+width-GetX(SIZE_PANELDEFAULT), y+height-GetY(SIZE_PANELDEFAULT), m_Skin.GetDC(), GetX(IMG_PANELDEFAULT)+GetX(SIZE_PANELDEFAULT)+1+GetX(SIZE_PANELDEFAULT)+1, GetY(IMG_PANELDEFAULT)+GetY(SIZE_PANELDEFAULT)+1+GetY(SIZE_PANELDEFAULT)+1, SIZE_PANELDEFAULT, SRCCOPY);


	// Draw panel title
	if ( lpszTitle != "")
	{
		// Draw Panel titlebar
		m_Screen.FillTiledBitmap( x+6, y+7, width-100-GetX(SIZE_PANELTITLEBARDEFAULT), GetY(SIZE_PANELTITLEBARDEFAULT), m_Skin.GetDC(), GetX(IMG_PANELTITLEBARDEFAULT)+GetX(SIZE_PANELTITLEBARDEFAULT)+1, GetY(IMG_PANELTITLEBARDEFAULT), SIZE_PANELTITLEBARDEFAULT);
		m_Screen.PutBitmap( x+6, y+7, m_Skin.GetDC(), GetX(IMG_PANELTITLEBARDEFAULT), GetY(IMG_PANELTITLEBARDEFAULT), SIZE_PANELTITLEBARDEFAULT, SRCCOPY);
		m_Screen.PutBitmap( x+width-100-GetX(SIZE_PANELTITLEBARDEFAULT), y+7, m_Skin.GetDC(), GetX(IMG_PANELTITLEBARDEFAULT)+GetX(SIZE_PANELTITLEBARDEFAULT)+1+GetX(SIZE_PANELTITLEBARDEFAULT)+1, GetY(IMG_PANELTITLEBARDEFAULT), SIZE_PANELTITLEBARDEFAULT, SRCCOPY);

		// Draw Panel Title
#ifdef LOCALE_NHNUSA
		m_Screen.PutText( x+6+7, y+7, x+width-100, GetY(SIZE_PANELTITLEBARDEFAULT), 15, "Arial", lpszTitle, RGB(150,150,150), TS_BOLD);
#else
		m_Screen.PutText( x+6+7, y+7, x+width-100, GetY(SIZE_PANELTITLEBARDEFAULT), 15, "Arial", lpszTitle, RGB(30,30,30), TS_BOLD);
#endif
	}
}


// SetWindowText
void CDDBDialog::SetWindowText( LPCTSTR lpszString)
{
	// 다이얼로그 타이틀바 그림
	if ( m_DlgInfo.bUseTitlebar)
	{
		m_Screen.FillTiledBitmap( 0, 0, m_DlgInfo.nWidth, GetY(SIZE_TITLEBARDEFAULT), m_Skin.GetDC(), GetX(IMG_TITLEBARDEFAULT)+GetX(SIZE_TITLEBARDEFAULT)+1, GetY(IMG_TITLEBARDEFAULT), SIZE_TITLEBARDEFAULT);
		m_Screen.PutBitmap( 0, 0, m_Skin.GetDC(), IMG_TITLEBARDEFAULT, SIZE_TITLEBARDEFAULT, SRCCOPY);
		m_Screen.PutBitmap( m_DlgInfo.nWidth-GetX(SIZE_TITLEBARDEFAULT), 0, m_Skin.GetDC(), GetX(IMG_TITLEBARDEFAULT)+GetX(SIZE_TITLEBARDEFAULT)+1+GetX(SIZE_TITLEBARDEFAULT)+1, GetY(IMG_TITLEBARDEFAULT), SIZE_TITLEBARDEFAULT, SRCCOPY);

		m_Screen.FillTiledBitmap( m_DlgInfo.nWidth*0.2f, 1, m_DlgInfo.nWidth-(m_DlgInfo.nWidth*0.2f*2.0f), GetY(SIZE_CAPTIONBARDEFAULT), m_Skin.GetDC(), GetX(IMG_CAPTIONBARDEFAULT)+GetX(SIZE_CAPTIONBARDEFAULT)+1, GetY(IMG_CAPTIONBARDEFAULT), SIZE_CAPTIONBARDEFAULT);
		m_Screen.PutBitmap( m_DlgInfo.nWidth*0.2f, 1, m_Skin.GetDC(), IMG_CAPTIONBARDEFAULT, SIZE_CAPTIONBARDEFAULT, SRCCOPY);
		m_Screen.PutBitmap( m_DlgInfo.nWidth-m_DlgInfo.nWidth*0.2f-GetX(SIZE_CAPTIONBARDEFAULT), 1, m_Skin.GetDC(), GetX(IMG_CAPTIONBARDEFAULT)+GetX(SIZE_CAPTIONBARDEFAULT)+1+GetX(SIZE_CAPTIONBARDEFAULT)+1, GetY(IMG_CAPTIONBARDEFAULT), SIZE_CAPTIONBARDEFAULT, SRCCOPY);

		if ( m_DlgInfo.bUseBmpTitle)
			m_Screen.PutBitmap( m_DlgInfo.nWidth/2-GetX(SIZE_BMPTITLEDEFAULT)/2, 1, m_Skin.GetDC(), IMG_BMPTITLEDEFAULT, SIZE_BMPTITLEDEFAULT, SRCCOPY);
		else
		{
			m_Screen.PutText( 1, 1, m_DlgInfo.nWidth, GetY(SIZE_CAPTIONBARDEFAULT), 15, "Arial", lpszString, RGB(42,98,154), TS_BOLD, DT_CENTER);
			m_Screen.PutText( 0, 0, m_DlgInfo.nWidth, GetY(SIZE_CAPTIONBARDEFAULT), 15, "Arial", lpszString, RGB(250,250,250), TS_BOLD, DT_CENTER);
		}


		// 타이틀바에 시스템메뉴 아이콘을 그림
		if ( m_DlgInfo.bUseIconSystemMenu && (m_DlgInfo.IDIconResource != NULL))
		{
			HICON hIcon;
			hIcon = AfxGetApp()->LoadIcon( m_DlgInfo.IDIconResource);
			DrawIconEx( m_Screen.GetDC()->m_hDC, 3, 3, hIcon, 16, 16, 0, NULL, DI_NORMAL);
		}
	}


	// Rendering
	Rendering( 0, 0, m_DlgInfo.nWidth, GetY(SIZE_TITLEBARDEFAULT));


	// Set window text
	CDialog::SetWindowText( lpszString);
}


// OnPaint
void CDDBDialog::OnPaint() 
{
	CPaintDC dc(this);
	
	CDC* pDC = GetDC();


	// Paint dialog screen
	if ( m_DlgInfo.bEnableRenderingLayer)
		m_Render.Rendering( pDC);
	else
		m_Screen.Rendering( pDC);

	ReleaseDC( pDC);
}


// Rendering
// 현재 그린 이미지 전부를 렌더링한다.
void CDDBDialog::Rendering()
{
	// Paint bitmap to dialog screen
	CDC* pDC = GetDC();
	m_Screen.Rendering( pDC);
	ReleaseDC( pDC);


	// Paint bitmap to rendering screen
	if ( m_DlgInfo.bEnableRenderingLayer)
		m_Render.PutBitmap( 0, 0, m_Screen.GetDC(), 0, 0, m_DlgInfo.nWidth, m_DlgInfo.nHeight);
}


// Rendering
// 현재 그린 이미지 일부를 렌더링한다.
void CDDBDialog::Rendering( int x, int y, int width, int height)
{
	// Paint bitmap to dialog screen
	CDC* pDC = GetDC();
	m_Screen.Rendering( pDC, x, y, x, y, width, height);
	ReleaseDC( pDC);


	// Paint bitmap to rendering screen
	if ( m_DlgInfo.bEnableRenderingLayer)
		m_Render.PutBitmap( x, y, m_Screen.GetDC(), x, y, width, height);
}


// OnCtlColor
HBRUSH CDDBDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	pDC->SetTextColor( m_DlgInfo.nTextColor);
	pDC->SetBkColor( m_DlgInfo.nTextBkColor);

	return (HBRUSH)m_brushCtlColor.m_hObject;
}


// PreTranslateMessage
BOOL CDDBDialog::PreTranslateMessage(MSG* pMsg)
{
	// Add tooltip list
	m_Tooltip.RelayEvent( pMsg);


	return CDialog::PreTranslateMessage(pMsg);
}


// OnWindowPosChanging
void CDDBDialog::OnWindowPosChanging( WINDOWPOS FAR* lpwndpos) 
{
	// 윈도우 스태칭 : 윈도우 이동시 화면 가장자리에 가까이 오면 자동으로 붙는다.
	CRect rc;
	SystemParametersInfo( SPI_GETWORKAREA, 0, &rc, NULL );
	int nScreenX = rc.Width();
	int nScreenY = rc.Height();
 
	CRect rcWin;
	rcWin.left = lpwndpos->x;
	rcWin.right = rcWin.left + m_DlgInfo.nWidth;
	rcWin.top = lpwndpos->y;
	rcWin.bottom = rcWin.top + m_DlgInfo.nHeight;


	// 윈도우가 현재의 위치를 유지하고 있지 않은 상태에서
	if(  (lpwndpos->flags & SWP_NOMOVE) != SWP_NOMOVE)
	{
		if( (rcWin.left < 10) || (rcWin.left < 0))
			lpwndpos->x = 0;
		if( ((nScreenX - rcWin.right) < 10) || (rcWin.right > nScreenX))
			lpwndpos->x = nScreenX - lpwndpos->cx;
		if( (rcWin.top < 10) || (rcWin.top < 0))
			lpwndpos->y = 0;
		if( ((nScreenY - rcWin.bottom) <= 10) || (rcWin.bottom > nScreenY))
			lpwndpos->y = nScreenY - lpwndpos->cy;
	}
}


// OnNcHitTest
UINT CDDBDialog::OnNcHitTest(CPoint point) 
{
	UINT hit = CDialog::OnNcHitTest( point);

	if ( (hit == HTCLIENT) && m_DlgInfo.bEnableMoveDlg)
	{
		CRect rect;
		GetWindowRect( rect);


		// 현재 마우스의 좌표를 윈도우에 대한 상대좌표로 변환하여 구한다.
		CPoint pos;
		pos.x = point.x - rect.left;
		pos.y = point.y - rect.top;


		// Caption 영역 검사
		if ( m_DlgInfo.bUseTitlebar)
		{
			if ( pos.y <= GetY(SIZE_TITLEBARDEFAULT))
			{
				if ( pos.x <= 20)
					return  HTSYSMENU;
				else
					return  HTCAPTION;
			}
			else
				return  HTCAPTION;
		}
		else
			return  HTCAPTION;
	}
	
	return CDialog::OnNcHitTest(point);
}


// OnLButtonDown
void CDDBDialog::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bMouseLButton = true;								// 눌림 플래그 비트 셋
	m_nMouseLBtnDownPos = point;						// 현재 눌린 좌표 기억
	SetCapture();
	
	CDialog::OnLButtonDown(nFlags, point);
}


// OnLButtonUp
void CDDBDialog::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	m_bMouseLButton = false;							// 눌림 플래그 비트 리셋
	
	CDialog::OnLButtonUp(nFlags, point);
}


// OnMouseMove
void CDDBDialog::OnMouseMove(UINT nFlags, CPoint point) 
{
	// 마우스 드래그 검출 
	if ( m_bMouseLButton)
	{
		if ( ( point.x != m_nMouseLBtnDownPos.x) || ( point.y != m_nMouseLBtnDownPos.y))
		{
			PostMessage( WM_MOUSEDRAG, (m_nMouseLBtnDownPos.x-point.x), (m_nMouseLBtnDownPos.y-point.y));
			m_nMouseLBtnDownPos = point;
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}


// OnMouseDrag
LRESULT CDDBDialog::OnMouseDrag( WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	return -1;
}


// OnAboutbox
void CDDBDialog::OnAboutbox() 
{
	// TODO: Add your command handler code here
}


// OnMinimize
void CDDBDialog::OnMinimize()
{
	// Minimize window
	ShowWindow( SW_MINIMIZE);
}

// OnMaximize
void CDDBDialog::OnMaximize()
{
	// TODO: Add your command handler code here
}


// OnQuit
void CDDBDialog::OnQuit()
{
	// Quit application
	PostMessage( WM_QUIT, 0, 0);
}


// CreateTrayicon
void CDDBDialog::CreateTrayicon( LPCTSTR lpszTooltip)
{
	if ( m_DlgInfo.IDIconResource == NULL)
	{
		MessageBox( "트레이 아이콘 리소스를 지정하지 않았기 때문에 트레이를    \n생성할 수 없습니다.", "Error", MB_OK);
		return ;
	}


	// 트레이아이콘과 핸들을 등록
	HICON hIcon;
	hIcon = (HICON)LoadIcon((HINSTANCE)GetWindowLong( GetSafeHwnd(), GWL_HINSTANCE), MAKEINTRESOURCE( m_DlgInfo.IDIconResource));

	m_TrayIcon.cbSize = sizeof( NOTIFYICONDATA);
	m_TrayIcon.hWnd   = GetSafeHwnd();
	m_TrayIcon.uID    = m_DlgInfo.IDIconResource;
	m_TrayIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_TrayIcon.hIcon  = hIcon;
	m_TrayIcon.uCallbackMessage = WM_TRAYICON_NOTIFY;
	strcpy( m_TrayIcon.szTip, lpszTooltip);
	Shell_NotifyIcon( NIM_ADD, &m_TrayIcon);
}


// DeleteTrayicon
void CDDBDialog::DeleteTrayicon()
{
	m_TrayIcon.uFlags = 0;
	Shell_NotifyIcon( NIM_DELETE, &m_TrayIcon);
}


// OnTrayNotification
LRESULT CDDBDialog::OnTrayNotification( WPARAM wParam, LPARAM lParam)
{
	if ( LOWORD(lParam) == WM_LBUTTONDBLCLK)
	{
		WINDOWPLACEMENT wndPl;
		GetWindowPlacement( &wndPl);

		if ( wndPl.showCmd & SW_SHOW)
		{
			ShowWindow( SW_MINIMIZE);
			ShowWindow( SW_HIDE);
		}
		else
		{
			ShowWindow( SW_SHOW);
			ShowWindow( SW_RESTORE);
		}
	}

	return 1;
}


// OnDropFiles
void CDDBDialog::OnDropFiles( HDROP hDropInfo)
{
	int nNumOfFiles;
	char szPathName[ MAX_PATH];

	nNumOfFiles = DragQueryFile( hDropInfo, 0xFFFFFFFF, szPathName, MAX_PATH);

	for ( int index = 0;  index < nNumOfFiles;  index++)
	{
		DragQueryFile( hDropInfo, index, szPathName, MAX_PATH);
		
		DropFiles( szPathName);
	}

	DragFinish( hDropInfo);
}


// DropFiles
void CDDBDialog::DropFiles( LPCTSTR szFileName)
{
	// TODO: Add your command handler code here
}
