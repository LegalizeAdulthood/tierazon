// TierazonDoc.h : interface of the CTierazonDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIERAZONDOC_H__09FDBB2D_6F08_11D1_9E84_444553540000__INCLUDED_)
#define AFX_TIERAZONDOC_H__09FDBB2D_6F08_11D1_9E84_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "dib.h"

class CTierazonDoc : public CDocument
{
protected: // create from serialization only
	CTierazonDoc();
	DECLARE_DYNCREATE(CTierazonDoc)

// Attributes
public:
	CDIB m_dib;
	CSize m_sizeDoc;
	CString doc_PathName;

	CRectTracker m_tracker;
	char cstr[81];

// Operations
public:
	CSize GetDocSize() const
		{ return m_sizeDoc; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTierazonDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTierazonDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTierazonDoc)
	afx_msg void OnApplicationIdle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIERAZONDOC_H__09FDBB2D_6F08_11D1_9E84_444553540000__INCLUDED_)
