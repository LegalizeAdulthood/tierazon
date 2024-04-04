// Movie.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMovie dialog

class CMovie : public CDialog
{
// Construction
public:
	CMovie(CWnd* pParent = NULL);   // standard constructor
	CView* m_pMovieView;
	CMovie(CView* pMovieView);
	BOOL Create();
	BOOL bStartButton;

// Dialog Data
	//{{AFX_DATA(CMovie)
	enum { IDD = IDD_MOVIE };
	CButton	m_CancelMovie;
	CButton	m_OKButton;
	long	m_Frames;
	double	m_Magnification_Finish;
	double	m_Magnification;
	CString	m_Output_File;
	int		m_Width;
	double	m_X_Finish;
	double	m_X_Start;
	double	m_Y_Finish;
	double	m_Y_Start;
	int		m_Height;
	BOOL	m_LockFinish;
	BOOL	m_LockStart;
	long	m_MovieRate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovie)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMovie)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnLockfinish();
	afx_msg void OnLockstart();
	afx_msg void OnCancelmovie();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
