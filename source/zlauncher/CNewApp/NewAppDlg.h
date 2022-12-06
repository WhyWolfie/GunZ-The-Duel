

#pragma once

#include "resource.h"
#include "CDDBDialog.h"
#include "CDDBAniBmp.h"
#include "explorer.h"
#include "ZUpdate.h"
#include "ZFileTransfer.h"



// 윈도우 메시지
#define	WM_FIND_PATCHINFO				(WM_USER + 1)
#define	WM_UPDATE_COMPLETE				(WM_USER + 2)
#define	WM_UPDATE_ERROR					(WM_USER + 3)


// 현재 상태 ID 정의
enum STATUSID
{
	STATUS_NONE			= 0,
	STATUS_READY,
	STATUS_ANALYSE_PATCHINFO,
	STATUS_CANNOT_FIND_PATCHINFO,
	STATUS_FIND_NEW_FILE,
	STATUS_UPDATING,
	STATUS_UPDATE_FAIL,
	STATUS_UPDATE_COMPLETE,
	STATUS_STARTGAME,
};


// 타이머 ID 정의
enum TIMERID
{
	TIMER_UPDATE		= 0,
};



/////////////////////////////////////////////////////////////////////////////
// Dialog
class CNewAppDlg : public CDDBDialog
{
// Variables
protected:
	// 프로세스 종료 예약
	bool			m_bReservedQuit;

	// 게임 프로세스 버젼
	char			m_szClientVersion[ 25];

	// 런쳐 버젼
	char			m_szLauncherVersion[ 25];

	// 윈도우 버젼
	int				m_nMajorVersion;

	// 업데이트를 건너 뛰는지 확인
	bool			m_bSkipUpdate;

	// Alpha 모드인지 확인
	bool			m_bIsAlpha;

	// 웹페이지 로딩이 끝났는지 확인
	bool			m_bNavigationComplete;

	// Controls
	CExplorer		m_cExplorer;
	CDDBAniBmp		m_cAnimation;				// Animation bitmap control

public:
	// 파일 업데이트가 끝났는지 확인
	bool			m_bUpdateComplete;

	//{{AFX_DATA(CNewAppDlg)
	CDDBButton		m_cStartGame;
	CDDBButton		m_cStop;
	//}}AFX_DATA

	// Process status
	int				m_nStatus;

	// Updater
	ZUpdate			m_Update;

	// Update canceled
	bool			m_bUpdateCanceled;

	// thread
	CWinThread*		m_pThreadUpdate;
	bool			m_bThreadContinue;


// Functions
public:
	CNewAppDlg(CWnd* pParent = NULL);

	// update start UI
	void UpdateStartUI();

	// update web loading
	void UpdateWebLoading();

	// update info window
	void UpdateInfo();

	// destroy dialog
	void OnDestroyDialog();

	// start game
	void StartGame();

	// get run information
	void GetRunInfo();

	// run external updater
	void RunExternalUpdater();

	// get file verseion
	void GetFileVersion( const char* pszFileName, char* pszVersion);

	// get OS version
	int GetOSVersion( char* pszBuff);

	// complete explorer
	void DocumentCompleteExplorer(LPDISPATCH pDisp, VARIANT* URL);

	// 라이센스를 보여줌
	bool ShowLicenseDlg();


protected:
	//{{AFX_VIRTUAL(CNewAppDlg)
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNewAppDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedStartgame();
	afx_msg void OnBnClickedStop();
	afx_msg LRESULT OnFindPatchInfo( WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateComplete( WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateError( WPARAM wParam, LPARAM lParam);
	afx_msg void OnAbout();
	afx_msg void OnOK();
	afx_msg void OnCancel();
	afx_msg void OnQuit();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	DECLARE_EVENTSINK_MAP()
};
