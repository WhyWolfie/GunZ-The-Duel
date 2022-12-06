
#include "resource.h"
#include "CDDBDialog.h"



/////////////////////////////////////////////////////////////////////////////
// Dialog
class CNewAppUpdateConfirm : public CDDBDialog
{
private:
	//{{AFX_DATA( CNewAppUpdateConfirm)
	CStatic			m_cMessage;
	CDDBButton		m_cOK;
	CDDBButton		m_cCancel;
	//}}AFX_DATA

	// Variables
	CString			m_strCaption;
	CString			m_strMessage;
	UINT			m_nButtonType;

	CDialog*		m_pParentDialog;

	DWORD			m_dwTime;


public:
	CNewAppUpdateConfirm(CWnd* pParent = NULL);

	void SetDialog( CDialog* pDialog, CString strCaption, CString strMessage, UINT nButtonType = MB_OKCANCEL);

	void PutMessage( int nTime);


	//{{AFX_VIRTUAL( CNewAppUpdateConfirm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNewAppUpdateConfirm)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
