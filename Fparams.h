// fparams.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFParams dialog

class CFParams : public CDialog
{
// Construction
public:
	CFParams(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFParams)
	enum { IDD = IDD_FRACTAL_PARAMS };
	int		m_Iterations;
	double	m_Bailout;
	double	m_BayFact1;
	double	m_BayFact2;
	double	m_Strands;
	double	m_Julia_X;
	double	m_Julia_Y;
	double	m_Magnification;
	double	m_X_Mid;
	double	m_Y_Mid;
	double	m_Lower;
	double	m_Upper;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFParams)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFParams)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
