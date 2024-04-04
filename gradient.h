// gradient.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGradient dialog

class CGradient : public CDialog
{
// Construction
public:
	CGradient(CWnd* pParent = NULL);	// standard constructor
	CView* m_pGradView;
	CGradient(CView* pGradView);
	
	//CScrollBar* pRedSB;
	//CScrollBar* pGrnSB;
	//CScrollBar* pBluSB;

// Implementation	
	BOOL Create();
	void ScrollBarInit();
	void ScrollBarUpdate();
	
	int m_Red_Scroll;
	int m_Grn_Scroll;
	int m_Blu_Scroll;

	enum { nMin = 0 };
	enum { nMax = 255 };

// Dialog Data
	//{{AFX_DATA(CGradient)
	enum { IDD = IDD_GRADIENT };
	CButton	m_Reverse;
	CButton	m_Invert;
	CButton	m_Forward;
	CButton	m_Cycle_Button;
	int		m_Inc_Blue;
	int		m_Inc_Green;
	int		m_Inc_Red;
	int		m_Start_Blue;
	int		m_Start_Green;
	int		m_Start_Red;
	CString	m_Status;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CGradient)
	afx_msg void OnClose();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnInvert();
	afx_msg void OnCycle();
	afx_msg void OnReverse();
	afx_msg void OnForward();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
