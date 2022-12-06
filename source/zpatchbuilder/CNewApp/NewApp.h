/*
 CNewApp 클래스(NewApp.h)

  date : 2004년 5월 30일
  comp : 임동환
*/


#ifndef _INCLUDED_CNEWAPP_
#define _INCLUDED_CNEWAPP_



/////////////////////////////////////////////////////////////////////////////
// CNewApp dialog
class CNewApp : public CWinApp
{
public:
	CNewApp();

	//{{AFX_VIRTUAL(CNewAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNewApp)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif
