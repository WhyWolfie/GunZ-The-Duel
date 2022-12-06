
#include "resource.h"
#include "CDDBDialog.h"



/////////////////////////////////////////////////////////////////////////////
// Dialog
class CNewAppWarnVista : public CDDBDialog
{
private:
	//{{AFX_DATA( CNewAppWarnVista)
	CStatic			m_cMessage;
	CButton			m_cCheck;
	CDDBButton		m_cOK;
	CDDBButton		m_cCancel;
	//}}AFX_DATA

	// Variables
	CString			m_strCaption;
	CString			m_strMessage;
	UINT			m_nButtonType;

	bool			m_bCheck;


public:
	CNewAppWarnVista(CWnd* pParent = NULL);

	void SetDialog( CString strCaption, CString strMessage, UINT nButtonType = MB_OKCANCEL);

	bool GetChecked()		{ return m_bCheck;	}


	//{{AFX_VIRTUAL( CNewAppWarnVista)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CNewAppWarnVista)
	afx_msg void OnOK();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
