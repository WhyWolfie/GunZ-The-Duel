

#pragma once

#include "resource.h"
#include "CDDBDialog.h"
#include "CDDBAniBmp.h"
#include "MPatchNode.h"



/////////////////////////////////////////////////////////////////////////////
// Dialog
class CNewAppDlg : public CDDBDialog
{
// Variables
protected:
	//{{AFX_DATA(CNewAppDlg)
	CButton		m_cStartGame;
	//}}AFX_DATA

	MPatchList				m_PatchList;
	MPatchList::iterator	m_Itr;


// Functions
public:
	CNewAppDlg(CWnd* pParent = NULL);
	virtual ~CNewAppDlg();

	void StartGame();
	
	void ScanDir( const char* szDir);
	
	void Build();

	bool CheckFilteredFile( const char* szFileName);

protected:
	//{{AFX_VIRTUAL(CNewAppDlg)
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNewAppDlg)
	afx_msg void OnBnClickedStartgame();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
