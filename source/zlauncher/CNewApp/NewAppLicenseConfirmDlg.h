
#include "resource.h"
#include "CDDBDialog.h"
#include "explorer.h"


/////////////////////////////////////////////////////////////////////////////
// Dialog
class CNewAppLicenseConfirmDlg : public CDDBDialog
{
private:
	//{{AFX_DATA( CNewAppLicenseConfirmDlg)
	CExplorer		m_cLicense;
	CStatic			m_cMessage;
	CDDBButton		m_cAgree;
	CDDBButton		m_cDeny;
	//}}AFX_DATA

	// Variables
	CDialog*		m_pParentDialog;

	CString			m_strCaption;
	CString			m_strFileName;
	CString			m_strMessage;
	CString			m_strAgree;
	CString			m_strDeny;


public:
	CNewAppLicenseConfirmDlg( CWnd* pParent = NULL);

	void SetDialog( CDialog* pDialog, CString strCaption, CString strFileName, CString strMessage, CString strAgree, CString strDeny);


	//{{AFX_VIRTUAL( CNewAppLicenseConfirmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

	DECLARE_MESSAGE_MAP()
};
