// TierazonDoc.cpp : implementation of the CTierazonDoc class
//

#include "stdafx.h"
#include "Tierazon.h"
#include "TierazonDoc.h"
#include <math.h>
#include "external.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTierazonDoc

IMPLEMENT_DYNCREATE(CTierazonDoc, CDocument)

BEGIN_MESSAGE_MAP(CTierazonDoc, CDocument)
	//{{AFX_MSG_MAP(CTierazonDoc)
	ON_COMMAND(ID_APPLICATION_IDLE, OnApplicationIdle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTierazonDoc construction/destruction

CTierazonDoc::CTierazonDoc()
{
	m_sizeDoc = CSize(1,1);     // dummy value to make CScrollView happy
	doc_PathName = "";

  CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;

	doc_PathName = "";
	m_sizeDoc = CSize(1,1);     // dummy value to make CScrollView happy
	bNewView = TRUE;

	// Initialize Rubber Banding
	m_tracker.m_rect.SetRectEmpty();	
  m_tracker.m_nStyle = CRectTracker::resizeOutside |
  	CRectTracker::hatchedBorder;
}

CTierazonDoc::~CTierazonDoc()
{
}

BOOL CTierazonDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	doc_PathName = "";

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTierazonDoc serialization

void CTierazonDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTierazonDoc diagnostics

#ifdef _DEBUG
void CTierazonDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTierazonDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTierazonDoc commands

void CTierazonDoc::OnApplicationIdle() 
{
	UpdateAllViews(NULL, ID_APPLICATION_IDLE);
}

BOOL CTierazonDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	m_dib.Close();
	doc_PathName = lpszPathName;

	if (!m_dib.Open(lpszPathName))
	{
		AfxMessageBox("error opening file: " + doc_PathName);	
		return FALSE;
	}
		
	m_sizeDoc = m_dib.GetSize();	

	return TRUE;
}

BOOL CTierazonDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
  doc_PathName = lpszPathName;
	CWaitCursor cursor;	// this will automatically display a wait cursor

	if (!m_dib.Save(doc_PathName))
	{
		AfxMessageBox("Error Saving File");
		return FALSE;
	}

	AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_SAVE_DIB);
	return TRUE;	
}

