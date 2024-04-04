// fparams.cpp : implementation file
//

#include "stdafx.h"
#include "Tierazon.h"
#include "fparams.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFParams dialog


CFParams::CFParams(CWnd* pParent /*=NULL*/)
	: CDialog(CFParams::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFParams)
	m_Iterations = 0;
	m_Bailout = 0.0;
	m_BayFact1 = 0.0;
	m_BayFact2 = 0.0;
	m_Strands = 0.0;
	m_Julia_X = 0.0;
	m_Julia_Y = 0.0;
	m_Magnification = 0.0;
	m_X_Mid = 0.0;
	m_Y_Mid = 0.0;
	m_Lower = 0.0;
	m_Upper = 0.0;
	//}}AFX_DATA_INIT
}


void CFParams::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFParams)
	DDX_Text(pDX, IDC_ITERATIONS, m_Iterations);
	DDX_Text(pDX, IDC_BAILOUT, m_Bailout);
	DDX_Text(pDX, IDC_BAY_EDIT1, m_BayFact1);
	DDX_Text(pDX, IDC_BAY_EDIT3, m_BayFact2);
	DDX_Text(pDX, IDC_STRANDS1, m_Strands);
	DDX_Text(pDX, IDC_JULIA_X, m_Julia_X);
	DDX_Text(pDX, IDC_JULIA_Y, m_Julia_Y);
	DDX_Text(pDX, IDC_MAGNIFICATION, m_Magnification);
	DDX_Text(pDX, IDC_X_MID, m_X_Mid);
	DDX_Text(pDX, IDC_Y_MID, m_Y_Mid);
	DDX_Text(pDX, IDC_LOWER, m_Lower);
	DDX_Text(pDX, IDC_UPPER, m_Upper);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFParams, CDialog)
	//{{AFX_MSG_MAP(CFParams)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFParams message handlers
