// Convolut.cpp : implementation file
//

#include "stdafx.h"
#include "Tierazon.h"
#include "Convolut.h"
#include "Tierazondoc.h"
#include "TierazonView.h"
#include "external.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConvolut dialog


CConvolut::CConvolut(CWnd* pParent /*=NULL*/)
	: CDialog(CConvolut::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConvolut)
	m_CK0 = 1.5;
	m_CK1 = 1;
	m_CK2 = 1;
	m_CK3 = 1;
	m_CK4 = 1;
	m_CK5 = 1;
	m_CK6 = 1;
	m_CK7 = 1;
	m_CK8 = 1;
	m_Title = _T("");
	//}}AFX_DATA_INIT
}

// Modeless Constructor
CConvolut::CConvolut(CView* pConvolutView)
	: CDialog()
{
	m_pConvolutView	= pConvolutView;
	bConvoluteContinuous = FALSE;
	m_CK0 = 1.5;
	m_CK1 = 1;
	m_CK2 = 1;
	m_CK3 = 1;
	m_CK4 = 1;
	m_CK5 = 1;
	m_CK6 = 1;
	m_CK7 = 1;
	m_CK8 = 1;
	m_Title = _T("");
}

void CConvolut::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConvolut)
	DDX_Control(pDX, IDC_STOP, m_Stop);
	DDX_Control(pDX, IDC_AUTO, m_Auto);
	DDX_Text(pDX, IDC_CK0, m_CK0);
	DDX_Text(pDX, IDC_CK1, m_CK1);
	DDX_Text(pDX, IDC_CK2, m_CK2);
	DDX_Text(pDX, IDC_CK3, m_CK3);
	DDX_Text(pDX, IDC_CK4, m_CK4);
	DDX_Text(pDX, IDC_CK5, m_CK5);
	DDX_Text(pDX, IDC_CK6, m_CK6);
	DDX_Text(pDX, IDC_CK7, m_CK7);
	DDX_Text(pDX, IDC_CK8, m_CK8);
	DDX_Text(pDX, IDC_TITLE, m_Title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConvolut, CDialog)
	//{{AFX_MSG_MAP(CConvolut)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_AUTO, OnAuto)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_BN_CLICKED(IDC_UNDO, OnUndo)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvolut message handlers

void CConvolut::OnApply() 
{
	AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FILTER_CONVOLUTION_APPLY);
	//m_pConvolutView->PostMessage(WM_USER_CONVOLUTE, NULL);
}

void CConvolut::OnUndo() 
{
	AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FILTER_CONVOLUTION_UNDO);
	//m_pConvolutView->PostMessage(WM_USER_UNDOCONVOLUTE, NULL);
}

void CConvolut::OnClose() 
{
	CDialog::OnClose();
	AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_CONVOLUTION_DIALOG);
	//m_pConvolutView->PostMessage(WM_USER_ABORTCONVOLUTE, NULL);
	
}

BOOL CConvolut::Create()
{
	return CDialog::Create(CConvolut::IDD);
}

void CConvolut::OnAuto() 
{
	m_Auto.SetState(TRUE);
	m_Stop.SetState(FALSE);
	bConvoluteContinuous = TRUE;
	AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FILTER_CONVOLUTION_AUTO);
	//m_pConvolutView->PostMessage(WM_USER_CONVOLUTE, NULL);
	//m_pConvolutView->PostMessage(WM_USER_CONVOLUTECONTINUOUS, NULL);
	//UpdateData(TRUE);
}

void CConvolut::OnStop() 
{
	m_Auto.SetState(FALSE);
	m_Stop.SetState(TRUE);
	bConvoluteContinuous = FALSE;
	AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FILTER_CONVOLUTION_STOP);
	//m_pConvolutView->PostMessage(WM_USER_ABORTCONVOLUTE, NULL);
	UpdateData();
}

/////////////////////////////////////////////////////////////////////////////
// Itiera Message handlers

void CTierazonView::OnConvolutionTracecontour() 
{
	bEdgeDetect = FALSE;
	bEmboss     = FALSE;
	bSharpen    = FALSE;
	bBlur				= FALSE;
	bAverage    = FALSE;

	bTraceContour ^= TRUE;
	OnFilterConvolutionApply();
}

void CTierazonView::OnUpdateConvolutionTracecontour(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bTraceContour);	
}

void CTierazonView::OnFilterConvolutionApply() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	nMatrix = 1;

	if (m_pConvolutView->GetSafeHwnd() != 0)
		m_pConvolutView->UpdateData();

	pDoc->m_dib.CK[0] = m_pConvolutView->m_CK0;
	pDoc->m_dib.CK[1] = m_pConvolutView->m_CK1;
	pDoc->m_dib.CK[2] = m_pConvolutView->m_CK2;
	pDoc->m_dib.CK[3] = m_pConvolutView->m_CK3;
	pDoc->m_dib.CK[4] = m_pConvolutView->m_CK4;
	pDoc->m_dib.CK[5] = m_pConvolutView->m_CK5;
	pDoc->m_dib.CK[6] = m_pConvolutView->m_CK6;
	pDoc->m_dib.CK[7] = m_pConvolutView->m_CK7;
	pDoc->m_dib.CK[8] = m_pConvolutView->m_CK8;

	if (!pDoc->m_dib.CreateDIB_Temp((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
	{
		AfxMessageBox("Error Creating DIB_Temp");
		return;
	}

	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnFilterConvolutionUndo() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Copy temporary bitmap
	// AfxMessageBox("Undo");
	BeginWaitCursor();
	if (!pDoc->m_dib.CopyTemp())
	{
		AfxMessageBox("Error Copying Temporary Bitmap");
	}
	EndWaitCursor();
	m_pConvolutView->bConvoluteContinuous = FALSE;
	m_pConvolutView->m_Auto.SetState(FALSE);
	Invalidate(FALSE);
	//m_pConvolutView->UpdateData(TRUE);
}

void CTierazonView::OnFilterConvolutionAuto() 
{
	m_pConvolutView->bConvoluteContinuous = TRUE;
	OnFilterConvolutionApply(); 
}

void CTierazonView::OnUpdateFilterConvolutionAuto(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_pConvolutView->bConvoluteContinuous);
}

void CTierazonView::OnFilterConvolutionStop() 
{
	m_pConvolutView->bConvoluteContinuous = FALSE;
}

void CTierazonView::OnUpdateFilterConvolutionStop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_pConvolutView->bConvoluteContinuous);
}

void CTierazonView::OnConvolutionDialog() 
{
	//if (nMatrix == 0)
		//nMatrix = 99;

	Convo_Title = "Custom";
	ConvolutionDialog();
}

void CTierazonView::OnUpdateConvolutionDialog(CCmdUI* pCmdUI) 
{
	if (nMatrix)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::ConvolutionDialog()
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (m_pConvolutView->GetSafeHwnd() == 0)
	{
		// Create the Convolution Dialog
		m_pConvolutView->Create();
			
		m_pConvolutView->m_CK0 = pDoc->m_dib.CK[0];
		m_pConvolutView->m_CK1 = pDoc->m_dib.CK[1];
		m_pConvolutView->m_CK2 = pDoc->m_dib.CK[2];
		m_pConvolutView->m_CK3 = pDoc->m_dib.CK[3];
		m_pConvolutView->m_CK4 = pDoc->m_dib.CK[4];
		m_pConvolutView->m_CK5 = pDoc->m_dib.CK[5];
		m_pConvolutView->m_CK6 = pDoc->m_dib.CK[6];
		m_pConvolutView->m_CK7 = pDoc->m_dib.CK[7];
		m_pConvolutView->m_CK8 = pDoc->m_dib.CK[8];

		m_pConvolutView->m_Title = Convo_Title;

		m_pConvolutView->m_Stop.SetState(FALSE);
		m_pConvolutView->UpdateData(FALSE);
		m_pConvolutView->ShowWindow(SW_SHOW);

	}
	else
	{
		// Destroy the Convolution dlg		
		//bAbort = TRUE;
		m_pConvolutView->bConvoluteContinuous = FALSE;
		m_pConvolutView->DestroyWindow();

		bEdgeDetect = FALSE;
		bEmboss     = FALSE;
		bSharpen    = FALSE;
		bBlur				= FALSE;
		bAverage    = FALSE;
		bTraceContour = FALSE;

		if (!bDraw)
			nMatrix = 0;
	}
}

void CTierazonView::OnImageEdgedetection() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//nMatrix = 1;
	bEdgeDetect = TRUE;

	/////////////////////////////
	// 3x3 Pixel numbering scheme
	// Edge Detection Kernel
 	/////////////////////////////
	//  0 -1  0
	// -1	 4 -1
	//  0	-1	0
	/////////////////////////////
	
	// Initialize Convolution Kernel for Edge Detection
	pDoc->m_dib.CK[0] = 4;
	pDoc->m_dib.CK[1] = 0;	
	pDoc->m_dib.CK[2] = -1;	
	pDoc->m_dib.CK[3] = 0;	
	pDoc->m_dib.CK[4] = -1;
	pDoc->m_dib.CK[5] = -1;
	pDoc->m_dib.CK[6] = 0;
	pDoc->m_dib.CK[7] = -1;
	pDoc->m_dib.CK[8] = 0;

	Convo_Title = "Edge Detection";
	ConvolutionDialog();
}

void CTierazonView::OnUpdateImageEdgedetection(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bEdgeDetect);
}

void CTierazonView::OnImageSharpen() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//nMatrix = 2;
	bSharpen = TRUE;

	/////////////////////////////
	// 3x3 Pixel numbering scheme
	// Sharpen Kernel
 	/////////////////////////////
	//  0 -1  0
	// -1	 5 -1
	//  0	-1	0
	/////////////////////////////
	
	// Initialize Convolution Kernel for the Sharpen Kernel
	pDoc->m_dib.CK[0] = 5;
	pDoc->m_dib.CK[1] = 0;	
	pDoc->m_dib.CK[2] = -1;	
	pDoc->m_dib.CK[3] = 0;	
	pDoc->m_dib.CK[4] = -1;
	pDoc->m_dib.CK[5] = -1;
	pDoc->m_dib.CK[6] = 0;
	pDoc->m_dib.CK[7] = -1;
	pDoc->m_dib.CK[8] = 0;

	Convo_Title = "Sharpen";
	ConvolutionDialog();
}

void CTierazonView::OnUpdateImageSharpen(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bSharpen);
}

void CTierazonView::OnImageEmboss() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//nMatrix = 3;
	bEmboss = TRUE;

	/////////////////////////////
	// 3x3 Pixel numbering scheme
	// Emboss Kernel
 	/////////////////////////////
	// -1  0  0
	//  0	 0  0
	//  0	 0	1
	/////////////////////////////
	
	// Initialize Convolution Kernel for the Emboss Kernel
	pDoc->m_dib.CK[0] = 1;
	pDoc->m_dib.CK[1] = -1;	
	pDoc->m_dib.CK[2] = 0;	
	pDoc->m_dib.CK[3] = 0;	
	pDoc->m_dib.CK[4] = 0;
	pDoc->m_dib.CK[5] = 0;
	pDoc->m_dib.CK[6] = 0;
	pDoc->m_dib.CK[7] = 0;
	pDoc->m_dib.CK[8] = 1;

	Convo_Title = "Emboss";
	ConvolutionDialog();
}

void CTierazonView::OnUpdateImageEmboss(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bEmboss);
}

void CTierazonView::OnImageBlur() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//nMatrix = 4;
	bBlur = TRUE;
	
	/////////////////////////////
	// 3x3 Pixel numbering scheme
	// Blur Kernal
 	/////////////////////////////
	//  0.05  0.15  0.05
	//  0.15	0.20  0.15
	//  0.05	0.15	0.05
	/////////////////////////////
	
	// Initialize Convolution for the Blur Kernel
	pDoc->m_dib.CK[0] = 0.20;
	pDoc->m_dib.CK[1] = 0.05;	
	pDoc->m_dib.CK[2] = 0.15;	
	pDoc->m_dib.CK[3] = 0.05;	
	pDoc->m_dib.CK[4] = 0.15;
	pDoc->m_dib.CK[5] = 0.15;
	pDoc->m_dib.CK[6] = 0.05;
	pDoc->m_dib.CK[7] = 0.15;
	pDoc->m_dib.CK[8] = 0.05;

	Convo_Title = "Blur";
	ConvolutionDialog();
}

void CTierazonView::OnUpdateImageBlur(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bBlur);
}

void CTierazonView::OnImageAverage() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//nMatrix = 5;
	bAverage = TRUE;
	
	/////////////////////////////
	// 3x3 Pixel numbering scheme
	// Average Kernal
 	/////////////////////////////
	//  1  1  1
	//  1  1  1
	//  1  1  1
	/////////////////////////////
	
	// Initialize Convolution for the Average Kernel
	pDoc->m_dib.CK[0] = .111;   // 1.5
	pDoc->m_dib.CK[1] = .111;	
	pDoc->m_dib.CK[2] = .111;	
	pDoc->m_dib.CK[3] = .111;	
	pDoc->m_dib.CK[4] = .111;
	pDoc->m_dib.CK[5] = .111;
	pDoc->m_dib.CK[6] = .111;
	pDoc->m_dib.CK[7] = .111;
	pDoc->m_dib.CK[8] = .111;

	Convo_Title = "Average";
	ConvolutionDialog();
}

void CTierazonView::OnUpdateImageAverage(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bAverage);
}

void CTierazonView::OnConvolveAntialias() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Anti-alias the image by bluring (low-pass filter), 
	// then reducing the image to one-falf its size

	//nMatrix = 4;

	bEdgeDetect = FALSE;
	bEmboss     = FALSE;
	bSharpen    = FALSE;
	bAverage    = FALSE;
	bTraceContour = FALSE;
	
	bBlur = TRUE;
	
	/////////////////////////////
	// 3x3 Pixel numbering scheme
	// Blur Kernal
 	/////////////////////////////
	//  0.05  0.15  0.05
	//  0.15	0.20  0.15
	//  0.05	0.15	0.05
	/////////////////////////////
	
	// Initialize Convolution for the Blur Kernel
	pDoc->m_dib.CK[0] = 0.20;
	pDoc->m_dib.CK[1] = 0.05;	
	pDoc->m_dib.CK[2] = 0.15;	
	pDoc->m_dib.CK[3] = 0.05;	
	pDoc->m_dib.CK[4] = 0.15;
	pDoc->m_dib.CK[5] = 0.15;
	pDoc->m_dib.CK[6] = 0.05;
	pDoc->m_dib.CK[7] = 0.15;
	pDoc->m_dib.CK[8] = 0.05;

	if (!pDoc->m_dib.CreateDIB_Temp((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
	{
		AfxMessageBox("Error Creating DIB_Temp");
		return;
	}

	nMatrix = 1;
	
	bDraw = TRUE;
	bLaunch = FALSE;
	
	bReduceSize = TRUE;
}

void CTierazonView::OnConvolveReduce() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// First lets create a temp buffer that is one half the size
	if (!pDoc->m_dib.CreateDIB_Temp((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
	{
		AfxMessageBox("Error Creating DIB_Temp");
		return;
	}

	// Second lets transfer every other pixel to the temp buffer
	if (!pDoc->m_dib.ReduceDIBSize())
	{
		AfxMessageBox("Error reducing DIB size");
		return;
	}

	// New lets create a new bitmap that is one-half the size
	if (!pDoc->m_dib.CreateDIB((DWORD) dim.cx/2, (DWORD) dim.cy/2))	// Create a bitmap
	{
		AfxMessageBox("Error Creating DIB_Temp");
		return;
	}

	// Copy temporary bitmap
	BeginWaitCursor();
	if (!pDoc->m_dib.CopyTemp())
	{
		AfxMessageBox("Error Copying Temporary Bitmap");
	}
	EndWaitCursor();

	dim.cx = dim.cx/2;
	dim.cy = dim.cy/2;

	global_width = dim.cx;
	global_height = dim.cy;

	pDoc->m_sizeDoc	= dim;

	bReduceSize = FALSE;
  OnWindowSizedesktop();
}

