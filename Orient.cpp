// Orient.cpp : implementation file
//

#include "stdafx.h"
#include "tierazon.h"
#include "Orient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrient dialog


COrient::COrient(CWnd* pParent /*=NULL*/)
	: CDialog(COrient::IDD, pParent)
{
	//{{AFX_DATA_INIT(COrient)
	m_Imag = 0.0;
	m_Real = 0.0;
	//}}AFX_DATA_INIT
}


void COrient::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COrient)
	DDX_Text(pDX, IDC_IMAG, m_Imag);
	DDX_Text(pDX, IDC_REAL, m_Real);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COrient, CDialog)
	//{{AFX_MSG_MAP(COrient)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrient message handlers
