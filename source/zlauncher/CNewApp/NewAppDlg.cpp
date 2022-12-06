#include "stdafx.h"
#include "ZGlobal.h"
#include "NewAppDlg.h"
#include "NewAppAboutBox.h"
#include "NewAppLicenseConfirmDlg.h"
#include "NewAppUpdateConfirm.h"
#include "NewAppUpdateCompleteDlg.h"
#include "NewAppErrorDlg.h"
#include "NewAppWarnVista.h"
#include "CGLEncription.h"
#include <math.h>
#include <Mmsystem.h>

//Wolfie: Fix
#include <iostream>

// Settings of USA
#ifdef LOCALE_NHNUSA
#include "ZNHNModule.h"
#define STR_GUNZ_PROCESS_NAME				"TheDuel"
#define STR_GUNZ_EXCUTE_FILENAME			"TheDuel.exe"
#define STR_LAUNCHER_EXCUTE_FILENAME		"GunzLauncher.exe"
#define STR_PATCHINFO_FILENAME				"patch.xml"
#define STR_WEBPAGE_URL						"http://jurienhamaker.net" //Your launcher start page url.
#define STR_ADDRESS_REAL					"127.0.0.1" //Your ip address here
#define STR_ADDRESS_ALPHA					"127.0.0.1" //Your ip address here
#define STR_GUNZ_PROCESS_NAME				"Gunz"
#define STR_GUNZ_EXCUTE_FILENAME			"Gunz.exe"
#define STR_LAUNCHER_EXCUTE_FILENAME		"GunzLauncher.exe"
#define STR_PATCHINFO_FILENAME				"patch.xml"
#define STR_WEBPAGE_URL						"http://80.128.57.169" //Your launcher start page url.
#define STR_ADDRESS_REAL					"80.128.57.169" //Your ip address here
#define STR_ADDRESS_ALPHA					"80.128.57.169" //Your ip address here
#define STR_DIRECTORY_REAL					"GunZUpdate" //Your path for yout patch
#define STR_DIRECTORY_ALPHA					"GunZUpdate" //Your path for yout patch test
#endif LOCALE_NHNUSA

// Settings of Brazil Launcher: Use THIS.
#ifdef LOCALE_BRAZIL
#define STR_GUNZ_PROCESS_NAME				"GunZ"
#define STR_GUNZ_EXCUTE_FILENAME			"GunZ.exe"
#define STR_LAUNCHER_EXCUTE_FILENAME		"GunzLauncher.exe"
#define STR_PATCHINFO_FILENAME				"patch.xml"
#define STR_WEBPAGE_URL						"http://jurienhamaker.net" //Your launcher start page url.
#define STR_ADDRESS_REAL					"127.0.0.1" //Your ip address here
#define STR_ADDRESS_ALPHA					"127.0.0.1" //Your ip address here
#define STR_GUNZ_PROCESS_NAME				"Gunz"
#define STR_GUNZ_EXCUTE_FILENAME			"Gunz.exe"
#define STR_LAUNCHER_EXCUTE_FILENAME		"GunzLauncher.exe"
#define STR_PATCHINFO_FILENAME				"patch.xml"
#define STR_WEBPAGE_URL						"http://jurienhamaker.net" //Your launcher start page url.
#define STR_ADDRESS_REAL					"80.128.57.169" //Your ip address here
#define STR_ADDRESS_ALPHA					"80.128.57.169" //Your ip address here
#define STR_DIRECTORY_REAL					"GunZUpdate" //Your path for yout patch
#define STR_DIRECTORY_ALPHA					"GunZUpdate" //Your path for yout patch test
#endif LOCALE_BRAZIL

// Settings of India
#ifdef LOCALE_INDIA
#define STR_GUNZ_PROCESS_NAME				"TheDuel"
#define STR_GUNZ_EXCUTE_FILENAME			"TheDuel.exe"
#define STR_LAUNCHER_EXCUTE_FILENAME		"GunzLauncher.exe"
#define STR_PATCHINFO_FILENAME				"patch.xml"
#define STR_WEBPAGE_URL						"http://jurienhamaker.net" //Your launcher start page url.
#define STR_ADDRESS_REAL					"127.0.0.1" //Your ip address here
#define STR_ADDRESS_ALPHA					"127.0.0.1" //Your ip address here
#define STR_GUNZ_PROCESS_NAME				"Gunz"
#define STR_GUNZ_EXCUTE_FILENAME			"Gunz.exe"
#define STR_LAUNCHER_EXCUTE_FILENAME		"GunzLauncher.exe"
#define STR_PATCHINFO_FILENAME				"patch.xml"
#define STR_WEBPAGE_URL						"http://jurienhamaker.net" //Your launcher start page url.
#define STR_ADDRESS_REAL					"80.128.57.169" //Your ip address here
#define STR_ADDRESS_ALPHA					"80.128.57.169" //Your ip address here
#define STR_DIRECTORY_REAL					"GunZUpdate" //Your path for yout patch
#define STR_DIRECTORY_ALPHA					"GunZUpdate" //Your path for yout patch test
#endif LOCALE_INDIA

// Common
#define STR_EXT_UPDATER_FILENAME			"updater.exe"




// Thread
UINT ThreadUpdate( LPVOID pParam);


// DoDataExchange
void CNewAppDlg::DoDataExchange( CDataExchange* pDX)
{
	CDDBDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewAppDlg)
	DDX_Control(pDX, IDC_STARTGAME, m_cStartGame);
	DDX_Control(pDX, IDC_STOP, m_cStop);
	DDX_Control(pDX, IDC_EXPLORER, m_cExplorer);
	DDX_Control(pDX, IDC_ANIMATION, m_cAnimation);
	//}}AFX_DATA_MAP
}


// Message map
BEGIN_MESSAGE_MAP( CNewAppDlg, CDDBDialog)
	//{{AFX_MSG_MAP(CNewAppDlg)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_STARTGAME, OnBnClickedStartgame)
	ON_BN_CLICKED(IDC_STOP, OnBnClickedStop)
	ON_BN_CLICKED(IDC_ABOUTBOX, OnAbout)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_MESSAGE(WM_FIND_PATCHINFO, OnFindPatchInfo)
	ON_MESSAGE(WM_UPDATE_COMPLETE, OnUpdateComplete)
	ON_MESSAGE(WM_UPDATE_ERROR, OnUpdateError)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/************************************************************************************
  Dialog
*************************************************************************************/
// 클래스 생성자
CNewAppDlg::CNewAppDlg( CWnd* pParent) : CDDBDialog( IDD_DIALOG_MAINDLG, pParent)
{
	// 이곳에서 생성할 다이얼로그의 정보를 입력한다
	// 좀 더 자세한 설명을 원하면 CDDBDialog.h 화일의 Structure of CDDBDIALOGINFO 내용을 참고한다
	CDDBDLGINFO DlgInfo;
	DlgInfo.nWidth  = 750;
	DlgInfo.nHeight = 541;
	DlgInfo.IDSkinResource = IDR_BMP_MAINDLG;
	DlgInfo.IDIconResource = IDR_ICO_MAINFRAME;
	DlgInfo.IDWaveResource = IDR_WAV_PUSHBUTTON;
	DlgInfo.bEnableMoveDlg = true;
	DlgInfo.bUseAboutboxButton = true;
	DlgInfo.bUseMinimizeButton = true;
	DlgInfo.bUseQuitButton = true;
	DlgInfo.bUseTitlebar = true;
	DlgInfo.bUseBmpTitle = true;
	DlgInfo.nTextColor = RGB( 30, 30, 30);
	DlgInfo.nTextBkColor = RGB( 150, 150, 150);
#ifdef LOCALE_NHNUSA
	DlgInfo.nTextColor = RGB( 150, 150, 150);
	DlgInfo.nTextBkColor = RGB( 38, 38, 38);
#endif
	SetDialogInfo( DlgInfo);


	// 변수 초기화
	m_nStatus = STATUS_NONE;

	m_pThreadUpdate = NULL;
	m_bThreadContinue = false;
	
	m_nMajorVersion = 0;

	m_bUpdateCanceled = false;

	m_bReservedQuit = false;

	m_bSkipUpdate = false;
	m_bIsAlpha = false;
	
	m_bNavigationComplete = false;

	m_bUpdateComplete = false;
}


/************************************************************************************
  클래스 메세지 핸들러
*************************************************************************************/
// OnInitDialog : 다이얼로그를 초기화는 함수
BOOL CNewAppDlg::OnInitDialog() 
{
	CDDBDialog::OnInitDialog();


	// 스트링 테이블 초기화
	HRSRC hRes = ::FindResource( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_STRING), _T( "TXT"));
	if ( hRes != NULL)
	{
		HGLOBAL hData = ::LoadResource( AfxGetResourceHandle(), hRes);
		if ( hData != NULL)
		{
			LPVOID lpData= LockResource( hData);

			// Read string table
			STLoadFromMemory( (char*)lpData);

			FreeResource( hData);
		}
	}


	// 로그 파일 초기화
	InitLog();


	// NHN 인증 처리 작업
#ifndef _DEBUG
#ifdef LOCALE_NHNUSA
//	if ( !GetNHNModule().GetAuth().InitAuth())
//	{
//		// 로그 출력
//		PutLog( "[APP] Cannot find a command.");
//
//		// 사이트 오픈
//		WinExec( "explorer.exe \"http://gunz.ijji.com/?from=desktop\"", SW_SHOW);
//
//		// 프로그램 종료
//		exit( 0);
//	}
#endif LOCALE_NHNUSA
#endif


	// 윈도우 버젼 확인
	char szVersion[ 128];
	m_nMajorVersion = GetOSVersion( szVersion);
	
	CString strBuff;
	strBuff.Format( "[APP] OS version : %s", szVersion);
	PutLog( strBuff);


	// 윈도우 비스타에서 특정 폴더(My Documents, Program Files, WINDOWS)에서 실행되면 경고를 출력한다
	if ( m_nMajorVersion >= 6)
	{
		// 비스타 경고 메시지를 표시하는지 확인
		if ( AfxGetApp()->GetProfileInt( "Flag", "DoNotDisplayVistaWarnning", 0) == 0)
		{
			// 현재 폴더가 경고 대상 폴더인지 확인
			char szCurrDir[ 512],  szPath[ 512];
			GetCurrentDirectory( sizeof( szCurrDir), szCurrDir);
			bool bInvalid = false;
			LPITEMIDLIST pidl;


			// Windows 폴더
			memset( szPath, 0, sizeof( szPath));
			SHGetSpecialFolderLocation( NULL, CSIDL_WINDOWS, &pidl);
			SHGetPathFromIDList( pidl, szPath);
			if ( strstr( szCurrDir, szPath) != NULL)	bInvalid = true;

			// Program Files 폴더
			memset( szPath, 0, sizeof( szPath));
			ZeroMemory( szPath, sizeof( szPath));
			SHGetSpecialFolderLocation( NULL, CSIDL_PROGRAM_FILES, &pidl);
			SHGetPathFromIDList( pidl, szPath);
			if ( strstr( szCurrDir, szPath) != NULL)	bInvalid = true;

			// My Documents 폴더
			memset( szPath, 0, sizeof( szPath));
			SHGetSpecialFolderLocation( NULL, CSIDL_PERSONAL, &pidl);
			SHGetPathFromIDList( pidl, szPath);
			if ( strstr( szCurrDir, szPath) != NULL)	bInvalid = true;


			// 비스타 경고창을 띄움
			if ( bInvalid)
			{
				CNewAppWarnVista dlg;
				dlg.SetDialog( /*Warning*/ ZGetString( "STR_100"), /*In Windows Vista, GunZ will not operate normally if installed at current directory.\n\nIf the patch fails, we advise you to uninstall GunZ and reinstall to its default setting.*/ ZGetString( "STR_101"), MB_OK);
				dlg.DoModal();

				if ( dlg.GetChecked())
					AfxGetApp()->WriteProfileInt( "Flag", "DoNotDisplayVistaWarnning", 1);
			}
		}
	}


    // 다이얼로그 타이틀 변경
	SetWindowText( /*GunZ Launcher*/ ZGetString( "STR_102"));


	// 다이얼로그 위치 이동 및 크기 조절
	CRect rect; 
	GetWindowRect( &rect);
	int nWidth = rect.Width(), nHeight = rect.Height();
	rect.left = AfxGetApp()->GetProfileInt( "Window Position", "x", 50);
	rect.top  = AfxGetApp()->GetProfileInt( "Window Position", "y", 50);
	rect.right  = rect.left + nWidth;
	rect.bottom = rect.top  + nHeight;
	MoveWindow( rect, true);


	// 웹페이지 컨트롤 초기화
	m_cExplorer.MoveWindow( 1, 1, 0, 0, false);


	// 시작 버튼 초기화
	m_cStartGame.InitDDBButton( IDR_BMP_STARTBTN, IDR_WAV_PUSHBUTTON);
	m_cStartGame.MoveWindow( 518, 461);
	m_cStartGame.EnableWindow( FALSE);


	// 중지 버튼 초기화
	m_cStop.InitDDBButton( IDR_BMP_BUTTON, IDR_WAV_PUSHBUTTON);
	m_cStop.MoveWindow( 530, 510);
	m_cStop.ShowWindow( SW_HIDE);		// 안보이게 감춰둠


	// 애니메이션 비트맵 초기화
	m_cAnimation.InitDDBAniBmp( IDR_BMP_ANIMATION, 6);
	m_cAnimation.SetTimerValue( 200);
	m_cAnimation.MoveWindow( 25, 470, 10, 10);
	m_cAnimation.EnableAnimate( FALSE);
	m_cAnimation.ShowScene( 0);


	// 화면 그리기
	GetScreen()->PutBitmap( 28,  20,  IDR_BMP_GUNZBG, 0, 0, 694, 434);
#ifndef LOCALE_NHNUSA
	GetScreen()->PutBitmap( 0,   140, GetSkin()->GetDC(), 490, 0, 18, 165);
	GetScreen()->PutBitmap( 732, 140, GetSkin()->GetDC(), 509, 0, 18, 165);
#endif


	// 현재 상태 설정
	m_nStatus = STATUS_NONE;


	// 정보 창을 업데이트 한다
	UpdateInfo();


	// 실행 정보를 얻는다
	GetRunInfo();


	// 게임 프로세서 버젼 구함
	GetFileVersion( STR_GUNZ_EXCUTE_FILENAME, m_szClientVersion);


	// 런쳐 버젼 구함
	GetFileVersion( STR_LAUNCHER_EXCUTE_FILENAME, m_szLauncherVersion);


	// 로그 출력
	PutLog( "[APP] Window created successfully.");


	// 외부 업데이터가 있으면 삭제한다
	WIN32_FIND_DATA FindData;
	HANDLE hFind = FindFirstFile( STR_EXT_UPDATER_FILENAME, &FindData);
	if ( hFind != INVALID_HANDLE_VALUE)
		DeleteFile( STR_EXT_UPDATER_FILENAME);


	// 업데이트 타이머 가동
	SetTimer( TIMER_UPDATE, 100, NULL);


	return true;
}


/************************************************************************************
  타이머
*************************************************************************************/
void CNewAppDlg::OnTimer(UINT nIDEvent)
{
	// 업데이트 타이머
	if ( nIDEvent == TIMER_UPDATE)
	{
		// 프로세스 종료 예약 상태인지 확인한다
		if ( m_bReservedQuit)
		{
			// 현재 상태 검사
			switch ( m_nStatus)
			{
				case STATUS_NONE :
				case STATUS_READY :
				case STATUS_CANNOT_FIND_PATCHINFO :
				case STATUS_FIND_NEW_FILE :
				case STATUS_UPDATE_FAIL :
				case STATUS_UPDATE_COMPLETE :
				case STATUS_STARTGAME :
					// 프로세스 종료
					OnDestroyDialog();
					break;
			}
		}


		// 프로세스 시작 이후 UI 수정
		UpdateStartUI();


		// 웹페이지 로딩
		UpdateWebLoading();


		// InfoBox를 업데이트 한다
		UpdateInfo();


		// 게임 시작 상태이면 게임 프로세스를 실행시킨다
		if ( m_nStatus == STATUS_STARTGAME)
			StartGame();
	}


	CDDBDialog::OnTimer(nIDEvent);
}


/************************************************************************************
  업데이트 시작
*************************************************************************************/
void CNewAppDlg::OnBnClickedStartgame()
{
	// 업데이트 완료 상태이면 게임을 실행시킨다
	if ( (m_bSkipUpdate == true) || (m_bUpdateComplete == true))
	{
		// 라이센스 확인창 표시

		if ( ShowLicenseDlg() == false)
			return;


		// 게임 시작
		m_nStatus = STATUS_STARTGAME;

		StartGame();
	}
	else
	{
		// 포트 열기
		if ( !m_Update.IsCreated())
		{
			// 알파 모드이면...
			if ( m_bIsAlpha)
				m_Update.Create( _T( STR_ADDRESS_ALPHA), 80, STR_DIRECTORY_ALPHA, "", "");

			// 리얼 모드이면...
			else
				m_Update.Create( _T( STR_ADDRESS_REAL), 80, STR_DIRECTORY_REAL, "", "");
		}


		// 사용자 쓰레드 선언

		// 쓰레드가 아직 안끝났을 수가 있으니 잠시 대기
		int i = 0;
		while ( m_bThreadContinue == true)
		{
			// 일정 시간 후에도 쓰레드가 종료되지 않으면 리턴
			if ( i > 10)
			{
				PutLog( "[APP] ERROR - The thread is not terminating.");

				m_nStatus = STATUS_READY;

				return;
			}

			Sleep( 100);

			i++;
		}


		m_bThreadContinue = true;
		m_pThreadUpdate = AfxBeginThread( ThreadUpdate, (LPVOID*)this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
		m_pThreadUpdate->ResumeThread();				// Run thread


		// 윈도우가 포커스를 잃어버려서 메시지를 못받는 경우가 생기므로 윈도우의 다른 컨트롤을 포커싱 해준다
		m_cExplorer.SetFocus();
	}
}


/************************************************************************************
  업데이트 쓰레드
*************************************************************************************/
UINT ThreadUpdate( LPVOID pParam)
{
	// pDlg를 통해서 NewAppDlg 클래스의 멤버 변수/함수(public일 경우에만)를
	// 참조할 수 있다.
	CNewAppDlg *pDlg = (CNewAppDlg*)pParam;


	// 대기 상태였었으면 업데이트 파일을 다운 받는다
	if ( (pDlg->m_nStatus == STATUS_READY) || (pDlg->m_nStatus == STATUS_CANNOT_FIND_PATCHINFO) || (pDlg->m_nStatus == STATUS_UPDATE_FAIL))
	{
		// 로그 출력
		PutLog( "[APP] Download patch info file");

		// 상태 설정
		pDlg->m_nStatus = STATUS_ANALYSE_PATCHINFO;


		// 패치 파일 이름을 구한다
		CString strMessageSecond;
		strMessageSecond.Format( "./%s", STR_PATCHINFO_FILENAME);


		// 패치 정보를 받는다
		bool bRetVal = pDlg->m_Update.CheckUpdate( strMessageSecond.GetBuffer());


		// 패치 정보를 받지 못했다면...
		if ( bRetVal == false)
		{
			// 로그 출력
			PutLog( "[APP] ERROR - Cannot download patch info file");


			// 상태 설정
			pDlg->m_nStatus = STATUS_CANNOT_FIND_PATCHINFO;


			// 메시지 보내기
			pDlg->PostMessage( WM_UPDATE_ERROR, 0, 0);


			// 종료
			pDlg->m_bThreadContinue = false;

			return true;
		}

		// 패치 정보를 받았다면...

		// 패치할 파일이 있는 경우,
		if ( pDlg->m_Update.GetUpdateInfo().GetTotalPatchFileCount() > 0)
		{
			// 로그 출력
			PutLog( "[APP] Exist patch file(s)");


			// 상태 설정
			pDlg->m_nStatus = STATUS_FIND_NEW_FILE;


			// 메시지 보내기
			pDlg->PostMessage( WM_FIND_PATCHINFO, 0, 0);
		}

		// 패치할 파일이 없는 경우,
		else
		{
			// 상태 설정
			pDlg->m_bUpdateComplete = true;
			pDlg->m_nStatus = STATUS_READY;
		}

	}


	// 업데이트 정보를 확인했으면 패치 파일을 다운받는다
	else if ( pDlg->m_nStatus == STATUS_FIND_NEW_FILE)
	{
		// 로그 출력
		PutLog( "[APP] Start file updating...");


		// 상태 설정
		pDlg->m_nStatus = STATUS_UPDATING;


		// 업데이트 시작
		bool bRetVal = bRetVal = pDlg->m_Update.StartUpdate();


		// 업데이트 실패일 경우...
		if ( bRetVal == false)
		{
			// 로그 출력
			PutLog( "[APP] ERROR - Update fail");


			// 상태 설정
			pDlg->m_nStatus = STATUS_UPDATE_FAIL;


			// 메시지 보내기
			pDlg->PostMessage( WM_UPDATE_ERROR, 0, 0);
		}

		// 업데이트 성공일 경우...
		else
		{
			// 로그 출력
			PutLog( "[APP] Update complete.");


			// 상태 설정
			pDlg->m_nStatus = STATUS_UPDATE_COMPLETE;


			// 메시지 보내기
			pDlg->PostMessage( WM_UPDATE_COMPLETE, 0, 0);
		}
	}


	pDlg->m_bThreadContinue = false;

	return true;
}


/************************************************************************************
  업데이트를 중지한다
*************************************************************************************/
void CNewAppDlg::OnBnClickedStop()
{
	// 로그 출력
	PutLog( "[APP] Update canceled...");


	// 업데이트 취소 플래그 설정
	m_bUpdateCanceled = true;


	// 업데이트 중지
	m_Update.StopUpdate();


	// 윈도우가 포커스를 잃어버려서 메시지를 못받는 경우가 생기므로 윈도우의 다른 컨트롤을 포커싱 해준다
	m_cExplorer.SetFocus();
}


/************************************************************************************
  프로세스 시작 이후 UI 업데이트
*************************************************************************************/
void CNewAppDlg::UpdateStartUI()
{
	static bool bUpdateStartUI = true;
	if ( !bUpdateStartUI)
		return;


	// 시작 이후의 경과시간
	static DWORD dwTime = timeGetTime();
	DWORD currTime = timeGetTime() - dwTime;


	// 일정 시간 뒤에 start game 버튼을 활성화 시킨다
	if ( currTime > 2000)
	{
		m_nStatus = STATUS_READY;

		if ( m_bSkipUpdate == true)
		{
			m_bUpdateComplete = true;

			m_cStartGame.EnableWindow( TRUE);
		}
		else
			OnBnClickedStartgame();


		bUpdateStartUI = false;
	}
}


/************************************************************************************
  웹페이지를 로딩한다
*************************************************************************************/
void CNewAppDlg::UpdateWebLoading()
{
	// 웹페이지 로딩이 끝났는지 확인
	static bool bCompleteOpenWeb = false;
	if ( bCompleteOpenWeb)
		return;


	// 웹페이지를 열었는지 확인
	static bool bOpenWeb = false;

	// 프로세서가 실행되고 일정 시간 후에 웹페이지를 연다. 프로세스 시작 직후엔 CPU 사용률이 높을 수 있으므로...
	static DWORD dwTime = timeGetTime() + 1000;
	if ( !bOpenWeb && (timeGetTime() > dwTime))
	{
		// 웹페이지 오픈
		m_cExplorer.Navigate( _T( STR_WEBPAGE_URL), NULL, NULL, NULL, NULL);
		bOpenWeb = true;
	}


	// 로딩 후 프로세스 사용률이 낮아질때까지 기다린다. 대충 1초면 충분함
	static bool bLoadingComplete = false;
	if ( !bLoadingComplete && m_bNavigationComplete)
	{
		bLoadingComplete = true;
		dwTime = timeGetTime() + 1000;
	}


	// 웹페이지 로드가 끝났으면 웹페이지 보임
	if ( !bCompleteOpenWeb && bOpenWeb && bLoadingComplete && (timeGetTime() > dwTime))
	{
#define SIZE_WEBPAGE_X		720
#define SIZE_WEBPAGE_Y		425

//		m_cExplorer.MoveWindow( 15, 25, SIZE_WEBPAGE_X, SIZE_WEBPAGE_Y, FALSE);
//		bCompleteOpenWeb = true;


		// 창이 스크롤 되면서 열리게 한다
		CRect rect;
		m_cExplorer.GetClientRect( &rect);


		// 넓이
		float size = (float)(SIZE_WEBPAGE_X - rect.Width()) * 0.7f + 0.5f;
		size = (size > 150.0f) ? 150.0f : size;

		int width = rect.Width() + (int)size;
		width = (width > SIZE_WEBPAGE_X) ? SIZE_WEBPAGE_X : width;


		// 높이
		int height = SIZE_WEBPAGE_Y;


		// 웹 컨트롤 창의 크기를 변경한다
		m_cExplorer.MoveWindow( 15 + SIZE_WEBPAGE_X - width, 25, width, height, FALSE);


		if ( (width == SIZE_WEBPAGE_X) && (height == SIZE_WEBPAGE_Y))
			bCompleteOpenWeb = true;

		return;
	}


	// 작은 원들을 출력함
	int x = 690, y = 415, r = 18;
	float gap = 6.28f / 10.0f;
	for ( int i = 0;  i < 10;  i++)
	{
		float value = gap * (float)i;

		int dx = x + (int)( (float)r * sin( value));
		int dy = y + (int)( (float)r * cos( value));


		int color = (int)( 70.0f * sin( value + (double)timeGetTime() / 300.0f) + 70.0f);

		GetScreen()->PutFillCircle( dx, dy, 3, RGB( color, color, color));
	}


	// 화면 복원
	Rendering( x - r - 20,  y - r - 5,  r * 2 + 40,  r * 2 + 10);
}


/************************************************************************************
  패치 정보 발견
*************************************************************************************/
LRESULT CNewAppDlg::OnFindPatchInfo( WPARAM wParam, LPARAM lParam)
{
	// 종료 예약 대기면 그냥 리턴
	if ( m_bReservedQuit)
		return TRUE;


// 	// 확인창 열기
// 	CNewAppUpdateConfirm dlg;
// 	CString str;
// 	str.Format( /*There are %d file(s) to update. The game must go through updating process for normal operation.  It will update automatically after %%d second(s)...*/ ZGetString( "STR_104"),  m_Update.GetUpdateInfo().GetTotalPatchFileCount());
// 	dlg.SetDialog( this, /*Update Confirm*/ ZGetString( "STR_103"), str, MB_YESNO);
// 	this->SetFocus();			// 포커싱 다시 획득
// 	int nRetVal = dlg.DoModal();
// 
// 
// 	// Yes 버튼을 누르면 업데이트 시작
// 	if ( nRetVal == IDOK)
// 		OnBnClickedStartgame();
// 
// 	// No 버튼을 누름
// 	else
// 		m_nStatus = STATUS_UPDATE_FAIL;
	

	OnBnClickedStartgame();

	return TRUE;
}


/************************************************************************************
  업데이트 완료
*************************************************************************************/
LRESULT CNewAppDlg::OnUpdateComplete( WPARAM wParam, LPARAM lParam)
{
	// 종료 예약 대기면 그냥 리턴
	if ( m_bReservedQuit)
		return TRUE;


	// update complete box 열기
	CNewAppUpdateCompleteDlg dlg;


	// 재부팅이 필요한 경우
	this->SetFocus();			// 포커싱 다시 획득
	if ( m_Update.IsReboot())
	{
		// 다이얼로그 박스를 띄움
		dlg.SetDialog( this, /*Update Complete*/ ZGetString( "STR_105"), /*The launcher has to restart in order to finish file update.  The launcher will restart in %d second(s)...*/ ZGetString( "STR_106"), MB_OK);
		dlg.DoModal();


		// 외부 업데이트 프로세서를 실행한다
		RunExternalUpdater();


		// 프로세스 종료
		OnQuit();
	}

	// 바로 게임을 시작하는 경우라면...
	else
	{
		// 업데이트 완료 확인
		m_bUpdateComplete = true;


//		// 확인창을 띄운다
// 		dlg.SetDialog( this, /*Update Complete*/ ZGetString( "STR_105"), /*The Update is successfully finished.  The game will start automatically in %d second(s)...*/ ZGetString( "STR_107"), MB_OK);
// 		dlg.DoModal();
// 
// 		// 상태 설정
// 		m_nStatus = STATUS_STARTGAME;

		m_nStatus = STATUS_READY;
	}


	return TRUE;
}


/************************************************************************************
  업데이트 에러 발생
*************************************************************************************/
LRESULT CNewAppDlg::OnUpdateError( WPARAM wParam, LPARAM lParam)
{
	// 종료 예약 대기면 그냥 리턴
	if ( m_bReservedQuit)
		return TRUE;


	// 로그로 남기기
	CString strLog;
	strLog.Format( "[APP] Updater error message :\n\n%s", m_Update.GetErrorMsg()->GetBuffer());
	PutLog( strLog);

	strLog.Format( "[App] File transfer error message :\n\n%s", m_Update.GetFileTransferError());
	PutLog( strLog);


	// Error dialog 열기
	CNewAppErrorDlg dlg;
	dlg.SetDialog( this, /*Error Report*/ ZGetString( "STR_108"), /*There was an error on the process.  We appologize for your inconvenience.  Please check the error report below and elimate the source or error manually.*/ ZGetString( "STR_109"), m_Update.GetErrorMsg(), MB_OK);
	this->SetFocus();			// 포커싱 다시 획득
	int nRetVal = dlg.DoModal();


	return TRUE;
}


/************************************************************************************
  게임 시작
*************************************************************************************/
void CNewAppDlg::StartGame()
{
	static DWORD dwStartTime = timeGetTime();
	DWORD curr_time = timeGetTime() - dwStartTime;


	// 1초 뒤에 게임 프로세스를 실행시킨다
	static bool bRunGameProcess = false;
	if ( !bRunGameProcess && (curr_time > 1000))
	{
		// 암호키 설정
		CGLEncription cEncription;
		if ( m_bIsAlpha)
			cEncription.CreateSerialKey( 2);			// Alpha testing mode
		else
			cEncription.CreateSerialKey( 0);


		// 프로세스 실행
		char szCmdLine[ 4096] = { 0, };

#ifdef LOCALE_NHNUSA
		sprintf( szCmdLine, ".\\%s \"%s\"", STR_GUNZ_EXCUTE_FILENAME, GetNHNModule().GetAuth().GetAuthStr());
#else
		sprintf( szCmdLine, ".\\%s", STR_GUNZ_EXCUTE_FILENAME);
#endif

		// 게임 프로세스를 실행시킨다
		WinExec( szCmdLine, SW_SHOW);

		bRunGameProcess = true;
		dwStartTime = timeGetTime();

		return;
	}


	// 게임 프로세스가 실행되면 종료한다
	static bool bQuit = false;
	if ( bRunGameProcess && !bQuit && (curr_time > 5000))
	{
		// 프로세스 종료
		OnQuit();

		bQuit = true;
	}
}


/************************************************************************************
  정보 창 업데이트
*************************************************************************************/
void CNewAppDlg::UpdateInfo()
{
	ZUpdateUIInfo info = m_Update.GetUpdateInfo();
	CString strMessageFirst = "";
	CString strMessageSecond = "";
	float fPercent = 0.0f;


	// 상태 및 작업에 따른 분기
	switch ( m_nStatus)
	{
		// 아직 윈도우가 만들어지지 않은 상태
		case STATUS_NONE :
		{
			// 표시 설정
			strMessageFirst = /*Initializing...*/ ZGetString( "STR_110");
			DWORD dwTime = (timeGetTime() / 120) % 15;
			for ( int i = 0;  i < (int)dwTime;  i++)	strMessageFirst += ".";

			break;
		}

		// 유저가 스타트 버튼을 누를때까지 대기
		case STATUS_READY :
		{
			// 에니메이션 중지
			m_cAnimation.EnableAnimate( FALSE);
			m_cAnimation.ShowScene( 0);

			// 표시 설정
			strMessageFirst = /*Ready to start.*/ ZGetString( "STR_111");

			// UI 설정
			if ( m_bUpdateComplete == true)
			{
				m_cStartGame.SetBlanking( TRUE, 800);
				m_cStartGame.EnableWindow( TRUE);
			}
			else
			{
				m_cStartGame.SetBlanking( FALSE);
				m_cStartGame.EnableWindow( FALSE);
			}
			m_cStop.EnableWindow( FALSE);
			break;
		}

		// 업데이트 정보 분석중
		case STATUS_ANALYSE_PATCHINFO :
		{
			// 에니메이션 시작
			m_cAnimation.EnableAnimate( TRUE);

			// 표시 설정
			strMessageFirst = /*Analyzing patch info*/ ZGetString( "STR_114");
			DWORD dwTime = (timeGetTime() / 120) % 15;
			for ( int i = 0;  i < (int)dwTime;  i++)	strMessageFirst += ".";

			// UI 설정
			m_cStartGame.EnableWindow( FALSE);
			m_cStop.EnableWindow( FALSE);
			break;
		}

		// 업데이트 정보를 받아오지 못했을 경우
		case STATUS_CANNOT_FIND_PATCHINFO :
		{
			// 에니메이션 중지
			m_cAnimation.EnableAnimate( FALSE);
			m_cAnimation.ShowScene( 0);

			// 표시 설정
			strMessageFirst = /*Cannot find patch info.*/ ZGetString( "STR_115");

			// UI 설정
			m_cStartGame.SetBlanking( FALSE);
			m_cStartGame.EnableWindow( TRUE);
			m_cStop.EnableWindow( FALSE);
			break;
		}

		// 업데이트 할 파일이 있을 경우
		case STATUS_FIND_NEW_FILE:
		{
			// 표시 설정
			strMessageFirst = /*Find new patch files.*/ ZGetString( "STR_116");

			// UI 설정
			m_cStartGame.EnableWindow( FALSE);
			m_cStop.EnableWindow( FALSE);
			break;
		}

		// 파일 업데이트 중
		case STATUS_UPDATING :
		{
			// 표시 설정
			unsigned long nCount = info.GetCurrPatchedFileCount() + 1;
			if ( nCount > info.GetTotalPatchFileCount())
			{
				strMessageFirst = /*Patching files*/ ZGetString( "STR_117");
				strMessageSecond = /*Please wait while the file duplication process takes place.*/ ZGetString( "STR_118");

				fPercent = 100.0f;
			}
			else
			{
				strMessageFirst.Format( "%s (%d / %d)", /*Updating files*/ ZGetString( "STR_119"), nCount, info.GetTotalPatchFileCount());


				// 현재 업데이트하는 파일이 있을 때
				if ( (int)strlen( info.GetCurrPatchFileName()) > 2)
				{
					float _fPercent = (float)info.GetCurrDownloadSize() / (float)info.GetTotalDownloadSize() * 100.0f;
					if ( _fPercent < 0.0f)		_fPercent = 0.0f;
					if ( _fPercent > 100.0f)	_fPercent = 100.0f;

					strMessageSecond.Format( "'%s'    %.1f%%   (%d / %d byte)", info.GetCurrPatchFileName(), _fPercent, info.GetCurrDownloadSize(), info.GetTotalDownloadSize());
				}
				else
				{
					strMessageSecond = /*Read patch file info*/ ZGetString( "STR_120");
					DWORD dwTime = (timeGetTime() / 500) % 5;
					for ( int i = 0;  i < (int)dwTime;  i++)	strMessageFirst += ".";
				}
				fPercent = (float)(info.GetCurrPatchedFileSize() + info.GetCurrDownloadSize()) / (float)info.GetTotalPatchFileSize() * 100.0f + 0.5f;
			}

			DWORD dwTime = (timeGetTime() / 500) % 5;
			for ( int i = 0;  i < (int)dwTime;  i++)	strMessageFirst += ".";


			// UI 설정
			m_cStartGame.EnableWindow( FALSE);
			m_cStop.EnableWindow( TRUE);
			break;
		}

		// 파일 업데이트 실패
		case STATUS_UPDATE_FAIL :
		{
			// 에니메이션 중지
			m_cAnimation.EnableAnimate( FALSE);
			m_cAnimation.ShowScene( 0);

			// 표시 설정
			strMessageFirst = /*Update failed.*/ ZGetString( "STR_121");

			// UI 설정
			m_cStartGame.SetBlanking( FALSE);
			m_cStartGame.EnableWindow( TRUE);
			m_cStop.EnableWindow( FALSE);
			break;
		}

		// 파일 업데이트 완료
		case STATUS_UPDATE_COMPLETE :
		{
			// 에니메이션 중지
			m_cAnimation.EnableAnimate( FALSE);
			m_cAnimation.ShowScene( 0);

			// 표시 설정
			strMessageFirst = /*Update complete.*/ ZGetString( "STR_122");
			strMessageSecond = /*Update complete.*/ ZGetString( "STR_122");
			fPercent = 100.0f;

			// UI 설정
			m_cStartGame.EnableWindow( FALSE);
			m_cStop.EnableWindow( FALSE);
			break;
		}

		// 게임 시작
		case STATUS_STARTGAME :
		{
			// 에니메이션 중지
			m_cAnimation.EnableAnimate( FALSE);
			m_cAnimation.ShowScene( 0);


			// 표시 설정
			strMessageFirst = /*Starting game*/ ZGetString( "STR_123");
			DWORD dwTime = (timeGetTime() / 500) % 5;
			for ( int i = 0;  i < (int)dwTime;  i++)	strMessageFirst += ".";

			fPercent = 0.0f;

			// UI 설정
			m_cStartGame.EnableWindow( FALSE);
			m_cStop.EnableWindow( FALSE);
			break;
		}
	}


	if ( strMessageSecond.GetLength() == 0)
	{
		if ( m_bSkipUpdate)
			strMessageSecond += /*Skip update.*/ ZGetString( "STR_112");
		strMessageSecond += "    ";

		if ( m_bIsAlpha)
			strMessageSecond += /*Alpha testing mode.*/ ZGetString( "STR_113");
		strMessageSecond += "    ";
	}



	// 퍼센트가 0보다 작거나 100을 넘지 않도록 조정
	if ( fPercent < 0.0f)		fPercent = 0.0f;
	if ( fPercent > 100.0f)		fPercent = 100.0f;


	// 바탕 패널 복원
	strMessageFirst = "     " + strMessageFirst;
	DrawPanel( 10, 460, 500, 70, strMessageFirst);


	// 현재 다운받는 파일 이름 표시
#ifdef LOCALE_NHNUSA
	GetScreen()->PutText( 23, 489, 15, "Arial", strMessageSecond, GetTextColor());
#else
	GetScreen()->PutText( 20, 489, 15, "Arial", strMessageSecond, GetTextColor());
#endif


	// 게이지 바 표시
	float fGausse = 489.0f * (fPercent / 100.0f) + 1.5f * (float)sin( (double)timeGetTime() / 100.0f);
	if ( (fGausse < 0.0f) || (fPercent < 0.01f))		fGausse = 0.0f;
	if ( (fGausse > 489.0f) || (fPercent > 99.99f)) 	fGausse = 489.0f;

	GetScreen()->PutBitmap( 16, 506, GetSkin()->GetDC(), 0, 86, 489, 19);
	GetScreen()->PutBitmap( 16, 506, GetSkin()->GetDC(), 0, 63, (int)fGausse, 19);


	// 전체 다운로드 퍼센테이지 표시
	if ( fPercent > 0.0f)
	{
		CString strPercent;
		strPercent.Format( "%.1f%%", fPercent);
#ifdef LOCALE_NHNUSA
		GetScreen()->PutText( 17, 507, 489, 19, 15, "Arial", strPercent.GetBuffer(), RGB( 50, 50, 50), TS_NORMAL, DT_CENTER);
		GetScreen()->PutText( 16, 506, 489, 19, 15, "Arial", strPercent.GetBuffer(), RGB( 200, 200, 200), TS_NORMAL, DT_CENTER);
#else
		GetScreen()->PutText( 16, 508, 489, 19, 15, "Arial", strPercent.GetBuffer(), GetTextColor(), TS_NORMAL, DT_CENTER);
#endif
	}


	// 화면 복원
	Rendering( 10, 460, 500, 70);
}


/************************************************************************************
  Run external updater
*************************************************************************************/
void CNewAppDlg::RunExternalUpdater()
{
	HRSRC hRes = ::FindResource( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_UPDATER), _T( "EXE"));
	if ( hRes == NULL)
		return;

	HGLOBAL hData = ::LoadResource( AfxGetResourceHandle(), hRes);
	if ( hData == NULL)
		return;

	LPVOID lpData= LockResource( hData);

	DWORD dwSize = SizeofResource( AfxGetInstanceHandle(), hRes);
	DWORD dwWriteSize = 0;
	HANDLE hFile = ::CreateFile( STR_EXT_UPDATER_FILENAME, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if ( hFile != INVALID_HANDLE_VALUE)
	{
		// Make 'updater.exe' file
		::WriteFile( hFile, lpData, dwSize, &dwWriteSize, NULL);
		::CloseHandle( hFile);


		// Wait...
		Sleep( 1000);


		// Run updater
		if ( dwSize == dwWriteSize)
		{
			PutLog( "[APP] Run external updater");

			char szCmdLine[ 4096] = { 0, };

#ifdef LOCALE_NHNUSA
			sprintf( szCmdLine, ".\\%s \"%s\"", STR_EXT_UPDATER_FILENAME, GetNHNModule().GetAuth().GetAuthStr());
#else
			sprintf( szCmdLine, ".\\%s", STR_EXT_UPDATER_FILENAME);
#endif

			// Run updater
			WinExec( szCmdLine, SW_SHOW);
		}

		else
			PutLog( "[APP] Invalid updater file");
	}

	else
		PutLog( "[APP] Cannot create updater file");


	FreeResource( hData);
}


/************************************************************************************
  Get run information
*************************************************************************************/
void CNewAppDlg::GetRunInfo()
{



	// INI 파일 열기
	CFile file;
	CFileException ex;
	if ( file.Open( "GunzLauncher.ini", CFile::modeRead, &ex) == TRUE)
	{
		char* szBuff = new char[ (unsigned int)file.GetLength()];
		file.Read( szBuff, (UINT)file.GetLength());


		// 업데이트를 하지 않는지 검사
		if ( strstr( szBuff, "@SKIP_UPDATE") != NULL)
			m_bSkipUpdate = true;

		// Alpha 모드인지 검사
		if ( strstr( szBuff, "@TEST_LAUNCH") != NULL)
			m_bIsAlpha = true;


		// 메모리, 파일 해제
		delete [] szBuff;
		file.Close();
	}










	// USA의 경우 인증 스트링에서 구한다
#ifdef LOCALE_NHNUSA

	m_bIsAlpha = false;

	if ( GetNHNModule().GetAuth().IsAlpha())
		m_bIsAlpha = true;

#endif


	// 로그 출력
	if ( m_bIsAlpha)
		PutLog( "[APP] Set alpha mode");
}


/************************************************************************************
  About box
*************************************************************************************/
void CNewAppDlg::OnAbout()
{
	// 메시지 작성
	CString strMsg;
	strMsg.Format( "%s Launcher\nCopyright (c) 2022 Gunz, Inc.\n\nGunz Version : 1.0.0\nLauncher Version : 1.0.0",
		STR_GUNZ_PROCESS_NAME, STR_GUNZ_PROCESS_NAME, m_szClientVersion, m_szLauncherVersion);

	// About box 열기
	CNewAppAboutBox dlg;
	dlg.SetDialog( this, "About", strMsg, MB_OK);
	this->SetFocus();			// 포커싱 다시 획득
	dlg.DoModal();
}


/************************************************************************************
  종료 처리
*************************************************************************************/
// OnOK : 엔터 키로 종료 되는것 방지
void CNewAppDlg::OnOK()
{
}

// OnCancel : ESC 키를 누름
void CNewAppDlg::OnCancel()
{
	// 업데이트 중이면 업데이트를 중지한다
	if ( m_nStatus == STATUS_UPDATING)
		OnBnClickedStop();

	// 아니면 바로 종료한다
	else
		OnQuit();
}

// OnQuit
void CNewAppDlg::OnQuit()
{
	// 프로세스 종료 예약을 한다. 업데이트 타이머에서 종료시킨다
	m_bReservedQuit = true;


	// 업데이트 중이면 업데이트를 중지한다
	if ( m_nStatus == STATUS_UPDATING)
		OnBnClickedStop();
}

// OnDestroyDialog
void CNewAppDlg::OnDestroyDialog()
{
	// 업데이터 종료
	m_Update.Destroy();


	// 다이얼로그의 현재 위치를 저장
	CRect rect;
	GetWindowRect( rect);
	AfxGetApp()->WriteProfileInt( "Window Position", "x", rect.left);
	AfxGetApp()->WriteProfileInt( "Window Position", "y", rect.top);


	// 윈도우 종료
	CDialog::OnOK();
}
/************************************************************************************
  파일 버젼을 구함
*************************************************************************************/
void CNewAppDlg::GetFileVersion( const char* pszFileName, char* pszVersion)
{
	strcpy( pszVersion, "unknown");


	DWORD dwHandle;
	DWORD dwLength = GetFileVersionInfoSize( pszFileName, &dwHandle);

	if ( !dwLength)
		return;

	std::auto_ptr<BYTE> lpBlock(new BYTE[dwLength]);
	
	if ( !GetFileVersionInfo( pszFileName, dwHandle, dwLength, lpBlock.get()))
		return;


	LPVOID pVersion = NULL;
	DWORD uLength;
	if ( !VerQueryValue( lpBlock.get(), "\\VarFileInfo\\Translation", (LPVOID*)&pVersion, (UINT*)&uLength))
		return;


	CString rVersion;
	if ( uLength == 4)
	{
		DWORD langD;
		memcpy( &langD, pVersion, 4);            

		rVersion.Format( "\\StringFileInfo\\%02X%02X%02X%02X\\ProductVersion",
							( langD & 0xff00) >> 8,
							( langD & 0xff),
							( langD & 0xff000000) >> 24,
							( langD & 0xff0000) >> 16);
	}
	else
	{
		rVersion.Format( "\\StringFileInfo\\%04X04B0\\ProductVersion", GetUserDefaultLangID());
	}


	if ( VerQueryValue( lpBlock.get(), (LPSTR)(LPCTSTR)rVersion, (LPVOID*)&pVersion, (UINT *)&uLength) == 0)
		return;


	// Success
	strcpy( pszVersion, (char*)pVersion);
}


/************************************************************************************
  OS 버젼을 구함
*************************************************************************************/
#define SM_SERVERR2		89
typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);

int CNewAppDlg::GetOSVersion( char* pszBuff)
{
	int nMajorID = -1;

	memset( pszBuff, 0, sizeof( pszBuff));

	OSVERSIONINFOEX osvi;
	SYSTEM_INFO si;
	PGNSI pGNSI;
	BOOL bOsVersionInfoEx;

	ZeroMemory( &si, sizeof( SYSTEM_INFO));
	ZeroMemory( &osvi, sizeof( OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof( OSVERSIONINFOEX);
	if ( !(bOsVersionInfoEx = GetVersionEx( (OSVERSIONINFO*) &osvi)))
	{
		osvi.dwOSVersionInfoSize = sizeof( OSVERSIONINFO);
		if ( !GetVersionEx( (OSVERSIONINFO*)&osvi)) 
			return -1;
	}

	pGNSI = (PGNSI)GetProcAddress( GetModuleHandle( TEXT( "kernel32.dll")), "GetNativeSystemInfo");
	if ( NULL != pGNSI)		pGNSI( &si);
	else					GetSystemInfo( &si);

	nMajorID = osvi.dwMajorVersion;

	switch ( osvi.dwPlatformId)
	{
		case VER_PLATFORM_WIN32_NT:
			if ( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
			{
				if ( osvi.wProductType == VER_NT_WORKSTATION)					strcat( pszBuff, "Windows Vista ");
				else															strcat( pszBuff, "Windows Server \"Longhorn\" ");
			}
			if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
			{
				if ( GetSystemMetrics( SM_SERVERR2))							strcat( pszBuff, "Microsoft Windows Server 2003 \"R2\" ");
				else if ( osvi.wProductType == VER_NT_WORKSTATION && si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
																				strcat( pszBuff, "Microsoft Windows XP Professional x64 Edition ");
				else															strcat( pszBuff, "Microsoft Windows Server 2003, ");
			}
			if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)			strcat( pszBuff, "Microsoft Windows XP ");
			if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)			strcat( pszBuff, "Microsoft Windows 2000 ");
			if ( osvi.dwMajorVersion <= 4)										strcat( pszBuff, "Microsoft Windows NT ");

			if ( bOsVersionInfoEx)
			{
				if ( osvi.wProductType == VER_NT_WORKSTATION && si.wProcessorArchitecture!=PROCESSOR_ARCHITECTURE_AMD64)
				{
					if ( osvi.dwMajorVersion == 4)								strcat( pszBuff, "Workstation 4.0 ");
					else if ( osvi.wSuiteMask & VER_SUITE_PERSONAL)				strcat( pszBuff, "Home Edition ");
					else														strcat( pszBuff, "Professional ");
				}

				else if ( osvi.wProductType == VER_NT_SERVER || osvi.wProductType == VER_NT_DOMAIN_CONTROLLER)
				{
					if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
					{
						if ( si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
						{
							if ( osvi.wSuiteMask & VER_SUITE_DATACENTER)		strcat( pszBuff, "Datacenter Edition for Itanium-based Systems ");
							else if ( osvi.wSuiteMask & VER_SUITE_ENTERPRISE)	strcat( pszBuff, "Enterprise Edition for Itanium-based Systems ");
						}
						else if ( si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
						{
							if ( osvi.wSuiteMask & VER_SUITE_DATACENTER)		strcat( pszBuff, "Datacenter x64 Edition ");
							else if ( osvi.wSuiteMask & VER_SUITE_ENTERPRISE)	strcat( pszBuff, "Enterprise x64 Edition ");
							else												strcat( pszBuff, "Standard x64 Edition ");
						}
						else
						{
							if ( osvi.wSuiteMask & VER_SUITE_DATACENTER)		strcat( pszBuff, "Datacenter Edition ");
							else if ( osvi.wSuiteMask & VER_SUITE_ENTERPRISE)	strcat( pszBuff, "Enterprise Edition ");
							else if ( osvi.wSuiteMask & VER_SUITE_BLADE)		strcat( pszBuff, "Web Edition ");
							else												strcat( pszBuff, "Standard Edition ");
						}
					}
					else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
					{
						if ( osvi.wSuiteMask & VER_SUITE_DATACENTER)			strcat( pszBuff, "Datacenter Server ");
						else if ( osvi.wSuiteMask & VER_SUITE_ENTERPRISE)		strcat( pszBuff, "Advanced Server ");
						else													strcat( pszBuff, "Server ");
					}
					else  // Windows NT 4.0 
					{
						if ( osvi.wSuiteMask & VER_SUITE_ENTERPRISE)			strcat( pszBuff, "Server 4.0, Enterprise Edition ");
						else													strcat( pszBuff, "Server 4.0 ");
					}
				}
			}

#define BUFSIZE		80
			else  
			{
				HKEY hKey;
				TCHAR szProductType[ BUFSIZE];
				DWORD dwBufLen = BUFSIZE * sizeof( TCHAR);
				LONG lRet;

				lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE, TEXT( "SYSTEM\\CurrentControlSet\\Control\\ProductOptions"), 0, KEY_QUERY_VALUE, &hKey);
				if ( lRet != ERROR_SUCCESS)
					return -1;

				lRet = RegQueryValueEx( hKey, TEXT( "ProductType"), NULL, NULL, (LPBYTE) szProductType, &dwBufLen);
				RegCloseKey( hKey);

				if ( (lRet != ERROR_SUCCESS) || (dwBufLen > BUFSIZE * sizeof( TCHAR)))
					return -1;

				if ( lstrcmpi( TEXT( "WINNT"), szProductType) == 0)				strcat( pszBuff, "Workstation ");
				if ( lstrcmpi( TEXT( "LANMANNT"), szProductType) == 0)			strcat( pszBuff, "Server ");
				if ( lstrcmpi( TEXT( "SERVERNT"), szProductType) == 0)			strcat( pszBuff, "Advanced Server ");
				
				
				char szTmp[ 128];
				sprintf( szTmp, "%d.%d ", osvi.dwMajorVersion, osvi.dwMinorVersion);
				strcat( pszBuff, szTmp);
			}

			// Display service pack (if any) and build number.
			if ( osvi.dwMajorVersion == 4 && lstrcmpi( osvi.szCSDVersion, TEXT( "Service Pack 6")) == 0)
			{
				HKEY hKey;
				LONG lRet;

				// Test for SP6 versus SP6a.
				lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE, TEXT( "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009"), 0, KEY_QUERY_VALUE, &hKey);
				if ( lRet == ERROR_SUCCESS)
				{
					char szTmp[ 128];
					sprintf( szTmp, "Service Pack 6a (Build %d)", osvi.dwBuildNumber & 0xFFFF);
					strcat( pszBuff, szTmp);
				}
				else // Windows NT 4.0 prior to SP6a
				{
					char szTmp[ 128];
					sprintf( szTmp, "%s (Build %d)", osvi.szCSDVersion, osvi.dwBuildNumber & 0xFFFF);
					strcat( pszBuff, szTmp);
				}

				RegCloseKey( hKey);
			}
			else // not Windows NT 4.0 
			{
				char szTmp[ 128];
				sprintf( szTmp, "%s (Build %d)", osvi.szCSDVersion, osvi.dwBuildNumber & 0xFFFF);
				strcat( pszBuff, szTmp);
			}

			break;


		// Test for the Windows Me/98/95.
		case VER_PLATFORM_WIN32_WINDOWS:
			if ( osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
			{
				strcat( pszBuff, "Microsoft Windows 95 ");
				if ( osvi.szCSDVersion[ 1] == 'C' || osvi.szCSDVersion[ 1] == 'B')
					strcat( pszBuff, "OSR2");
			} 
			if ( osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
			{
				strcat( pszBuff, "Microsoft Windows 98 ");
				if ( osvi.szCSDVersion[ 1] == 'A' || osvi.szCSDVersion[ 1] == 'B')
					strcat( pszBuff, "SE");
			} 
			if ( osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
				strcat( pszBuff, "Microsoft Windows Millennium Edition");
			break;


		case VER_PLATFORM_WIN32s:
			strcat( pszBuff, "Microsoft Win32s");
			break;
	}

	return nMajorID;
}


// 웹페이지 로딩 완료
BEGIN_EVENTSINK_MAP(CNewAppDlg, CDDBDialog)
	ON_EVENT(CNewAppDlg, IDC_EXPLORER, 259, DocumentCompleteExplorer, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()


void CNewAppDlg::DocumentCompleteExplorer(LPDISPATCH pDisp, VARIANT* URL)
{
	HRESULT		hr;
	LPUNKNOWN	lpUnknown;
	LPUNKNOWN	lpUnknownWB = NULL;
	LPUNKNOWN	lpUnknownDC = NULL;

	lpUnknown = m_cExplorer.GetControlUnknown();
	if ( lpUnknown)
	{
		// Get the pointer to the IUnknown interface of the WebBrowser 
		// control being hosted. The pointer to the IUnknown returned from 
		// GetControlUnknown is not the pointer to the IUnknown of the 
		// WebBrowser control. It's actually a pointer to the IOleObject.
		hr = lpUnknown->QueryInterface( IID_IUnknown, (LPVOID*)&lpUnknownWB);
		if ( FAILED( hr))
			return;


		// Get the pointer to the IUnknown of the object that fired this 
		// event.
		hr = pDisp->QueryInterface( IID_IUnknown, (LPVOID*)&lpUnknownDC);
		if ( FAILED( hr))
			return;


		if ( lpUnknownWB == lpUnknownDC)
		{
			// The document has finished loading.
			m_bNavigationComplete = true;
		}


		if ( lpUnknownWB)
			lpUnknownWB->Release();

		if ( lpUnknownDC)
			lpUnknownDC->Release();
	}
}


/************************************************************************************
  라이센스를 보여줌
*************************************************************************************/

bool CNewAppDlg::ShowLicenseDlg()
{
	return true;


	// 다이얼로그를 띄움
	CNewAppLicenseConfirmDlg dlg;
	dlg.SetDialog( this, ZGetString( "STR_149"), "license.htm", ZGetString( "STR_150"), ZGetString( "STR_151"), ZGetString( "STR_152"));

	int nRetVal = dlg.DoModal();
	if ( nRetVal == IDOK)
	return true;


	return false;
}

