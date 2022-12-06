/*
 CDDBDialog 클래스(CDDBDialog.h)

  desc : CDialog를 상속받아서 GUI 다이얼로그를 사용할 수 있게 해주는 클래스.
  date : 2004년 5월 30일
  comp : 고려대학교 제어계측연구회(KUCIRA) - 임동환
         http://www.kucira.com
  text : MFC를 공부하는 사람 누구나 자유 배포 및 수정이 가능합니다. 단, 특정 개인이나
         단체의 이익을 위한 목적으로 사용되는 것은 금합니다.
*/


#ifndef _INCLUDED_CDDBDLG_
#define _INCLUDED_CDDBDLG_


#include "CDDB.h"								// Include CDDB
#include "CDDBButton.h"							// Include CDDB Button
#include "CSound.h"								// Include CSound
#include <afxcmn.h>								// Include afxcmn.h


// Define button ID resource name
#define WM_MOUSEDRAG		(WM_USER + 100)		// Message of drag mouse
#define WM_TRAYICON_NOTIFY	(WM_USER + 101)		// Message of m_TrayIcon
#define IDC_ABOUTBOX		(WM_USER + 200)		// Control button Aboutbox
#define IDC_MINIMIZE		(WM_USER + 201)		// Control button Minimize
#define IDC_MAXIMIZE		(WM_USER + 202)		// Control button Maximize
#define IDC_QUIT			(WM_USER + 203)		// Control button Quit



/////////////////////////////////////////////////////////////////////////////
// CDDBDialog dialog
class CDDBDialog : public CDialog
{
// Structure of CDDBDIALOGINFO
public:
	struct CDDBDLGINFO
	{
		// 다이얼로그 설정 변수
		UINT		nWidth;						// 생성할 다이얼로그의 넓이를 지정한다.
		UINT		nHeight;					// 생성할 다이얼로그의 높이를 지정한다.
		UINT		IDSkinResource;				// 다이얼로그에 입힐 스킨 리소스의 ID를 지정한다.
		UINT		IDIconResource;				// 다이얼로그에 사용할 아이콘의 리소스의 ID를 지정한다.
		UINT		IDWaveResource;				// 다이얼로그에 사용되는 버튼들의 눌림 사운드 리소스 ID를 지정한다.
		COLORREF	nTextColor;					// 다이얼로그 및 콘트롤에 사용할 텍스트의 색상을 지정한다.
		COLORREF	nTextBkColor;				// 다이얼로그 및 콘트롤에 사용할 텍스트 배경 색상을 지정한다.

		// 타이틀바 관련 설정 변수
		BOOL		bUseTitlebar;				// 이 항목을 TRUE로 설정하면 다이얼로그 윗부분에 타이틀바를 만든다.
		BOOL		bUseBmpTitle;				// 이 항목을 TRUE로 설정하면 타이틀바의 제목을 비트맵 이미지를 사용해서 그린다.
		BOOL		bUseIconSystemMenu;			// 이 항목을 TRUE로 설정하면 타이틀바의 시스템 메뉴 영역에 아이콘(IDIconResource)을 그린다.

		// 시스템버튼 사용 플래그
		BOOL		bUseAboutboxButton;			// 이 항목을 TRUE로 설정하면 Aboutbox 버튼을 사용할 수 있다.
		BOOL		bUseMinimizeButton;			// 이 항목을 TRUE로 설정하면 Minimize 버튼을 사용할 수 있다.
		BOOL		bUseMaximizeButton;			// 이 항목을 TRUE로 설정하면 Maximize 버튼을 사용할 수 있다.
		BOOL		bUseQuitButton;				// 이 항목을 TRUE로 설정하면 Quit 버튼을 사용할 수 있다.

		// 기타 옵션
		BOOL		bEnableMoveDlg;				// 이 항목을 TRUE로 설정하면 다이얼로그를 드래그해서 이동시킬 수 있다.
		BOOL		bEnableDragAndDrop;			// 이 항목을 TRUE로 설정하면 다이얼로그에 파일을 드래그 앤 드롭할 수 있다.
		BOOL		bEnableRenderingLayer;		// 이 항목을 TRUE로 설정하면 Rendering용 DDB를 이용할 수 있다.


		// 초기화
		CDDBDLGINFO()
		{
			nWidth					= 320;
			nHeight					= 240;
			IDSkinResource			= NULL;
			IDIconResource			= NULL;
			IDWaveResource			= NULL;
			nTextColor				= RGB( 61,  99,  184);
			nTextBkColor			= RGB( 255, 255, 255);
			bUseTitlebar			= false;
			bUseBmpTitle			= false;
			bUseIconSystemMenu		= false;
			bUseAboutboxButton		= false;
			bUseMinimizeButton		= false;
			bUseMaximizeButton		= false;
			bUseQuitButton			= false;
			bEnableMoveDlg			= false;
			bEnableDragAndDrop		= false;
			bEnableRenderingLayer	= false;
		}
	};


// Variables
private:
	CDDB			m_Screen,					// DDB of drawing screen
					m_Skin,						// DDB of skin
					m_Render;					// DDB to rendering

	CSound			m_Sound;					// Play sound

	CDDBButton		m_cButtonAbout,				// About button
					m_cButtonMinimize,			// Minimize button
					m_cButtonMaximize,			// Maximize button
					m_cButtonQuit;				// Quit button

	CDDBDLGINFO		m_DlgInfo;					// Informations of this dialog

	HICON			m_hIcon;					// Handle of icon
	CBrush			m_brushCtlColor;			// Window color brush
	CRgn			m_Rgn;						// Window Region
	CToolTipCtrl	m_Tooltip;					// Tooltip

	bool			m_bInitialized;				// Is Initialized

	BOOL			m_bMouseLButton;			// Mouse left button check flag
	CPoint			m_nMouseLBtnDownPos;		// Mouse left button position
	NOTIFYICONDATA	m_TrayIcon;					// Handle of trayIcon


// Functions
public:
	CDDBDialog( UINT nIDTemplate, CWnd* pParentWnd);
	virtual ~CDDBDialog();

	void SetWindowText( LPCTSTR lpszString);
	
	UINT GetWidth()									{ return m_DlgInfo.nWidth;  }
	UINT GetHeight()								{ return m_DlgInfo.nHeight; }

	COLORREF GetTextColor()							{ return m_DlgInfo.nTextColor;   }
	COLORREF GetTextBkColor()						{ return m_DlgInfo.nTextBkColor; }


	//{{AFX_VIRTUAL(CDDBDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void DrawDialogWindow();
	virtual void DrawPanel( int x, int y, int width, int height, LPCTSTR lpszTitle=NULL);
	virtual void CreateAboutButton( int x, int y);
	virtual void CreateMaximizeButton( int x, int y);
	virtual void CreateMinimizeButton( int x, int y);
	virtual void CreateQuitButton( int x, int y);
	virtual void DropFiles( LPCTSTR szFileName);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL


protected:
	void Rendering();
	void Rendering( int x, int y, int width, int height);
	
	void GetDialogInfo( CDDBDLGINFO* DlgInfo)		{ *DlgInfo = m_DlgInfo; }
	void SetDialogInfo( CDDBDLGINFO DlgInfo)		{ if ( !m_bInitialized)  m_DlgInfo = DlgInfo;  }

	CDDB* GetScreen()								{ return &m_Screen; }
	CDDB* GetSkin()									{ return &m_Skin;   }
	CDDB* GetRender()								{ return &m_Render; }

	CDC* GetScreenDC()								{ return m_Screen.GetDC(); }
	CDC* GetSkinDC()								{ return m_Skin.GetDC();   }
	CDC* GetRenderDC()								{ return m_Render.GetDC(); }

	void AddTooltip( CWnd* pWnd, LPCTSTR lpszMsg)	{ if ( !m_bInitialized)  m_Tooltip.AddTool( pWnd, _T( lpszMsg)); }

	void CreateTrayicon( LPCTSTR lpszTooltip);
	void DeleteTrayicon();

	void PlayEffectSound( UINT IDWaveResource)		{ m_Sound.PlayWavSound( IDWaveResource); }


protected:
	//{{AFX_MSG(CDDBDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseDrag( WPARAM wParam, LPARAM lParam);
	afx_msg void OnAboutbox();
	afx_msg void OnMaximize();
	afx_msg void OnMinimize();
	afx_msg void OnQuit();
	afx_msg LRESULT OnTrayNotification( WPARAM wParam, LPARAM lParam);
	afx_msg void OnDropFiles( HDROP hDropInfo);
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()
};

#endif
