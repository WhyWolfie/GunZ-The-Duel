
#include "resource.h"
#include "CDDBDialog.h"



/////////////////////////////////////////////////////////////////////////////
// Dialog
class CNewAppAboutBox : public CDDBDialog
{
private:
	//{{AFX_DATA( CNewAppAboutBox)
	CStatic			m_cMessage;
	CDDBButton		m_cOK;
	CDDBButton		m_cCancel;
	//}}AFX_DATA

	// Variables
	CString			m_strCaption;
	CString			m_strMessage;
	UINT			m_nButtonType;

	CDialog*		m_pParentDialog;


public:
	CNewAppAboutBox(CWnd* pParent = NULL);

	void SetDialog( CDialog* pDialog, CString strCaption, CString strMessage, UINT nButtonType = MB_OKCANCEL);

	//{{AFX_VIRTUAL( CNewAppAboutBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL


protected:
	DECLARE_MESSAGE_MAP()
};
