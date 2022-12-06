
#include "resource.h"
#include "CDDBDialog.h"



/////////////////////////////////////////////////////////////////////////////
// Dialog
class CNewAppErrorDlg : public CDDBDialog
{
private:
	//{{AFX_DATA( CNewAppErrorDlg)
	CStatic			m_cMessage;
	CListBox		m_cErrorList;
	CDDBButton		m_cOK;
	CDDBButton		m_cShowLog;
	//}}AFX_DATA

	// Variables
	CString			m_strCaption;
	UINT			m_nButtonType;
	CString			m_strMessage;
	CString*		m_pstrErrorMessage;

	CDialog*		m_pParentDialog;


public:
	CNewAppErrorDlg(CWnd* pParent = NULL);

	void SetDialog( CDialog* pDialog, CString strCaption, CString strMessage, CString* pstrErrorMessage, UINT nButtonType = MB_OKCANCEL);

	//{{AFX_VIRTUAL( CNewAppErrorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL


protected:
	//{{AFX_MSG(CNewAppDlg)
	afx_msg void OnBnClickedShowlog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
