// XYSize.cpp : implementation file
//

#include "stdafx.h"
#include "Tierazon.h"
#include "XYSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// XYSize dialog

XYSize::XYSize(CWnd* pParent /*=NULL*/)
	: CDialog(XYSize::IDD, pParent)
{
	//{{AFX_DATA_INIT(XYSize)
	m_ImageSize = -1;
	m_X_Custom = 0;
	m_Y_Custom = 0;
	//}}AFX_DATA_INIT
}


void XYSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(XYSize)
	DDX_Radio(pDX, IDC_RADIO_40_30, m_ImageSize);
	DDX_Text(pDX, IDC_X_CUSTOM, m_X_Custom);
	DDV_MinMaxInt(pDX, m_X_Custom, 1, 32000);
	DDX_Text(pDX, IDC_Y_CUSTOM, m_Y_Custom);
	DDV_MinMaxInt(pDX, m_Y_Custom, 1, 32000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(XYSize, CDialog)
	//{{AFX_MSG_MAP(XYSize)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XYSize message handlers
