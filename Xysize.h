// XYSize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// XYSize dialog

class XYSize : public CDialog
{
// Construction
public:
	XYSize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(XYSize)
	enum { IDD = IDD_DIMENSIONS };
	int		m_ImageSize;
	int		m_X_Custom;
	int		m_Y_Custom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(XYSize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(XYSize)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
