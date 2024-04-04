// gradient.cpp : implementation file
//

#include "stdafx.h"
#include "Tierazon.h"
#include "gradient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGradient dialog


CGradient::CGradient(CWnd* pParent /*=NULL*/)
	: CDialog(CGradient::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGradient)
	m_Inc_Blue = 0;
	m_Inc_Green = 0;
	m_Inc_Red = 0;
	m_Start_Blue = 0;
	m_Start_Green = 0;
	m_Start_Red = 0;
	//}}AFX_DATA_INIT
	m_pGradView = NULL;
}

CGradient::CGradient(CView* pGradView)  // Modeless constructor
	: CDialog()
{
	m_pGradView = pGradView;
}	 

void CGradient::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGradient)
	DDX_Control(pDX, IDC_REVERSE, m_Reverse);
	DDX_Control(pDX, IDC_INVERT, m_Invert);
	DDX_Control(pDX, IDC_FORWARD, m_Forward);
	DDX_Control(pDX, IDC_CYCLE, m_Cycle_Button);
	DDX_Text(pDX, IDC_INC_BLUE, m_Inc_Blue);
	DDV_MinMaxInt(pDX, m_Inc_Blue, 0, 255);
	DDX_Text(pDX, IDC_INC_GREEN, m_Inc_Green);
	DDV_MinMaxInt(pDX, m_Inc_Green, 0, 255);
	DDX_Text(pDX, IDC_INC_RED, m_Inc_Red);
	DDV_MinMaxInt(pDX, m_Inc_Red, 0, 255);
	DDX_Text(pDX, IDC_START_BLUE, m_Start_Blue);
	DDV_MinMaxInt(pDX, m_Start_Blue, 0, 255);
	DDX_Text(pDX, IDC_START_GREEN, m_Start_Green);
	DDV_MinMaxInt(pDX, m_Start_Green, 0, 255);
	DDX_Text(pDX, IDC_START_RED, m_Start_Red);
	DDV_MinMaxInt(pDX, m_Start_Red, 0, 255);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGradient, CDialog)
	//{{AFX_MSG_MAP(CGradient)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_INVERT, OnInvert)
	ON_BN_CLICKED(IDC_CYCLE, OnCycle)
	ON_BN_CLICKED(IDC_REVERSE, OnReverse)
	ON_BN_CLICKED(IDC_FORWARD, OnForward)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGradient message handlers

BOOL CGradient::Create()
{
	return CDialog::Create(CGradient::IDD);
}

void CGradient::OnClose()
{
	m_pGradView->PostMessage(WM_DLGGRADIENT, ID_DLGCLOSE);
	
	CDialog::OnClose();
}

//void CGradient::OnGradientApply()
//{
//	UpdateData(TRUE);
//	if (m_pGradView != NULL)
//	{
//		m_pGradView->PostMessage(WM_DLGGRADIENT, ID_APPLY);
//	}		
//}

void CGradient::OnOK()
{
	UpdateData(TRUE);
	m_pGradView->PostMessage(WM_DLGGRADIENT, ID_APPLY);
	ScrollBarInit();
}

BOOL CGradient::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CScrollBar* pSB = (CScrollBar*) GetDlgItem(IDC_REDSCROLL);
	pSB->SetScrollRange(nMin, nMax);
	
	pSB = (CScrollBar*) GetDlgItem(IDC_GRNSCROLL);
	pSB->SetScrollRange(nMin, nMax);

	pSB = (CScrollBar*) GetDlgItem(IDC_BLUSCROLL);	
	pSB->SetScrollRange(nMin, nMax);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGradient::ScrollBarInit()
{
	CScrollBar* pSB;

	pSB = (CScrollBar*) GetDlgItem(IDC_REDSCROLL);
	pSB->SetScrollPos(GetDlgItemInt(IDC_START_RED));

	pSB = (CScrollBar*) GetDlgItem(IDC_GRNSCROLL);	
	pSB->SetScrollPos(GetDlgItemInt(IDC_START_GREEN));

	pSB = (CScrollBar*) GetDlgItem(IDC_BLUSCROLL);	
	pSB->SetScrollPos(GetDlgItemInt(IDC_START_BLUE));
}

void CGradient::OnInvert() 
{
	UpdateData(TRUE);

	m_Start_Red		= GetDlgItemInt(IDC_START_RED);
	m_Start_Green = GetDlgItemInt(IDC_START_GREEN);
	m_Start_Blue	= GetDlgItemInt(IDC_START_BLUE);

	m_Start_Red		=	m_Start_Red		^ 0xFF;
	m_Start_Green	= m_Start_Green ^ 0xFF;
	m_Start_Blue	= m_Start_Blue	^ 0xFF;
	
	SetDlgItemInt(IDC_START_RED, m_Start_Red);
	SetDlgItemInt(IDC_START_GREEN, m_Start_Green);
	SetDlgItemInt(IDC_START_BLUE, m_Start_Blue);

	m_pGradView->SendMessage(WM_DLGGRADIENT, ID_APPLY);
	ScrollBarInit();
}

void CGradient::OnCycle() 
{
	UpdateData(TRUE);
	//m_pGradView->PostMessage(WM_DLGGRADIENT, ID_APPLY);
	//ScrollBarUpdate();
	m_pGradView->PostMessage(WM_COMMAND, ID_SHIFT_START);	
}

void CGradient::OnReverse() 
{
	UpdateData(TRUE);
	m_pGradView->SendMessage(WM_DLGSHIFT, ID_SHIFTREVERSE);
	ScrollBarInit();
}

void CGradient::OnForward() 
{
	UpdateData(TRUE);
	m_pGradView->SendMessage(WM_DLGSHIFT, ID_SHIFTFORWARD);
	ScrollBarInit();
}

void CGradient::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int nTemp1, nTemp2;
	
	nTemp1 = pScrollBar->GetScrollPos();
	switch(nSBCode)
	{
		case SB_THUMBPOSITION:
			pScrollBar->SetScrollPos(nPos);
			ScrollBarUpdate();
			break;
		
		case SB_LINEUP:		// Left arrow button
			nTemp2 = (nMax - nMin) / 128;
			if ((nTemp1 - nTemp2) > nMin)
			{
				nTemp1 -= nTemp2;
			}
			else
			{
				nTemp1 = nMin;
			}
			pScrollBar->SetScrollPos(nTemp1);
			ScrollBarUpdate();
			break;
	
		case SB_LINEDOWN:  // right arrow button
			nTemp2 = (nMax - nMin) / 128;
			if ((nTemp1 + nTemp2) < nMax)
				nTemp1 += nTemp2;
			else
				nTemp1 = nMax;
			pScrollBar->SetScrollPos(nTemp1);

			ScrollBarUpdate();
			break;
	}
	

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGradient::ScrollBarUpdate()
{
	CScrollBar* pSB;

	UpdateData(TRUE);

	pSB = (CScrollBar*) GetDlgItem(IDC_REDSCROLL);
	m_Start_Red = pSB->GetScrollPos();

	pSB = (CScrollBar*) GetDlgItem(IDC_GRNSCROLL);
	m_Start_Green = pSB->GetScrollPos();

	pSB = (CScrollBar*) GetDlgItem(IDC_BLUSCROLL);
	m_Start_Blue = pSB->GetScrollPos();

	SetDlgItemInt(IDC_START_RED, m_Start_Red);
	SetDlgItemInt(IDC_START_GREEN, m_Start_Green);
	SetDlgItemInt(IDC_START_BLUE, m_Start_Blue);

	UpdateData(TRUE);

	m_pGradView->SendMessage(WM_DLGSHIFT, ID_APPLY);

}

void CGradient::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int nTemp1, nTemp2;
	
	nTemp1 = pScrollBar->GetScrollPos();
	switch(nSBCode)
	{
		case SB_THUMBPOSITION:
			pScrollBar->SetScrollPos(nPos);
			ScrollBarUpdate();
			break;
		
		case SB_LINEUP:		// Left arrow button
			nTemp2 = (nMax - nMin) / 128;
			if ((nTemp1 - nTemp2) > nMin)
			{
				nTemp1 -= nTemp2;
			}
			else
			{
				nTemp1 = nMin;
			}
			pScrollBar->SetScrollPos(nTemp1);
			ScrollBarUpdate();
			break;
	
		case SB_LINEDOWN:  // right arrow button
			nTemp2 = (nMax - nMin) / 128;
			if ((nTemp1 + nTemp2) < nMax)
				nTemp1 += nTemp2;
			else
				nTemp1 = nMax;
			pScrollBar->SetScrollPos(nTemp1);

			ScrollBarUpdate();
			break;
	}
		
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
