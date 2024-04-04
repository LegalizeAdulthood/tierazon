// Unique.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUnique dialog

class CUnique : public CDialog
{
// Construction
public:
	CUnique(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUnique)
	enum { IDD = IDD_UNIQUE };
	double	m_u_imag;
	double	m_u_real;
	double	m_v_real;
	double	m_w_real;
	CString	m_Formulae;
	double	m_v_imag;
	double	m_w_imag;
	int		m_Radio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnique)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUnique)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
