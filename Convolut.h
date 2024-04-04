// Convolut.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConvolut dialog

class CConvolut : public CDialog
{
public:
	BOOL bConvoluteContinuous;

// Construction
public:
	CConvolut(CWnd* pParent = NULL);   // standard constructor
	CView* m_pConvolutView;
	CConvolut(CView* pConvolutView);
	BOOL Create();

// Dialog Data
	//{{AFX_DATA(CConvolut)
	enum { IDD = IDD_CONVOLUTION };
	CButton	m_Stop;
	CButton	m_Auto;
	double	m_CK0;
	double	m_CK1;
	double	m_CK2;
	double	m_CK3;
	double	m_CK4;
	double	m_CK5;
	double	m_CK6;
	double	m_CK7;
	double	m_CK8;
	CString	m_Title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvolut)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConvolut)
	afx_msg void OnClose();
	afx_msg void OnAuto();
	afx_msg void OnApply();
	afx_msg void OnUndo();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
