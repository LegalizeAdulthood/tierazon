#if !defined(AFX_ORIENT_H__C73F19C1_6FFF_11D1_9E84_444553540000__INCLUDED_)
#define AFX_ORIENT_H__C73F19C1_6FFF_11D1_9E84_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Orient.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COrient dialog

class COrient : public CDialog
{
// Construction
public:
	COrient(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COrient)
	enum { IDD = IDD_ORIENT };
	double	m_Imag;
	double	m_Real;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrient)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COrient)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORIENT_H__C73F19C1_6FFF_11D1_9E84_444553540000__INCLUDED_)
