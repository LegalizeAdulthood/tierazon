// Movie.cpp : implementation file
//
 
#include "stdafx.h"
#include "tierazon.h"
#include "Tierazondoc.h"
#include "Movie.h"
#include "tierazonview.h"
#include "external.h"
#include "math.h"
#include <dos.h>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMovie dialog

CMovie::CMovie(CWnd* pParent /*=NULL*/)
	: CDialog(CMovie::IDD, pParent)
{
	//Create(CMovie::IDD, pParent);
	//{{AFX_DATA_INIT(CMovie)
	m_Frames = 0;
	m_Magnification_Finish = 0.0;
	m_Magnification = 0.0;
	m_Output_File = _T("");
	m_Width = 0;
	m_X_Finish = 0.0;
	m_X_Start = 0.0;
	m_Y_Finish = 0.0;
	m_Y_Start = 0.0;
	m_Height = 0;
	m_LockFinish = FALSE;
	m_LockStart = FALSE;
	m_MovieRate = 0;
	//}}AFX_DATA_INIT
	m_pMovieView = NULL;
}

CMovie::CMovie(CView* pMovieView)  // Modeless constructor
	: CDialog()
{
	m_pMovieView = pMovieView;
}	 

void CMovie::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMovie)
	DDX_Control(pDX, ID_CANCELMOVIE, m_CancelMovie);
	DDX_Control(pDX, IDOK, m_OKButton);
	DDX_Text(pDX, IDC_FRAMES, m_Frames);
	DDX_Text(pDX, IDC_Magnif_Finish, m_Magnification_Finish);
	DDX_Text(pDX, IDC_Magnif_Start, m_Magnification);
	DDX_Text(pDX, IDC_Output_File, m_Output_File);
	DDX_Text(pDX, IDC_WIDTH, m_Width);
	DDV_MinMaxInt(pDX, m_Width, 1, 16000);
	DDX_Text(pDX, IDC_X_Finish, m_X_Finish);
	DDX_Text(pDX, IDC_X_Start, m_X_Start);
	DDX_Text(pDX, IDC_Y_Finish, m_Y_Finish);
	DDX_Text(pDX, IDC_Y_Start, m_Y_Start);
	DDX_Text(pDX, IDC_Height, m_Height);
	DDV_MinMaxInt(pDX, m_Height, 1, 16000);
	DDX_Check(pDX, IDC_LOCKFINISH, m_LockFinish);
	DDX_Check(pDX, IDC_LOCKSTART, m_LockStart);
	DDX_Text(pDX, IDC_MOVIERATE, m_MovieRate);
	DDV_MinMaxLong(pDX, m_MovieRate, 1, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMovie, CDialog)
	//{{AFX_MSG_MAP(CMovie)
	ON_BN_CLICKED(IDC_LOCKFINISH, OnLockfinish)
	ON_BN_CLICKED(IDC_LOCKSTART, OnLockstart)
	ON_BN_CLICKED(ID_CANCELMOVIE, OnCancelmovie)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMovie message handlers

BOOL CMovie::Create()
{
	return CDialog::Create(CMovie::IDD);
	bStartButton = FALSE;
}

void CMovie::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
	//DestroyWindow();
	//SetWindowText("Start");

	//if (m_OKButton.GetState())
	//	AfxMessageBox("TRUE");
	//else
	//	AfxMessageBox("FALSE");

	if (bStartButton)
	{
		m_OKButton.SetState(TRUE);
		return;
	}

	UpdateData();
	if (m_LockStart && m_LockFinish)
	{
		bStartButton = TRUE;
		AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FRACTAL_STARTGENERATINGAMOVIE);
	}
	else
	{
		AfxMessageBox("Start and Finish Positions have not been Locked");
		return;
	}	
}

void CMovie::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
	//DestroyWindow();
	AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FRACTALS_MOVIE);
}

void CMovie::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	//delete this;
	//AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FRACTALS_MOVIE);
}

void CMovie::OnLockfinish() 
{
	UpdateData();
}

void CMovie::OnLockstart() 
{
	UpdateData();
}

void CMovie::OnCancelmovie() 
{
	m_pMovieView->PostMessage(WM_USER_CANCELMOVIE, NULL);
	m_OKButton.SetState(FALSE);
	bStartButton = FALSE;
}

//////////////////////////////////////////////////////////////////
// CTierazon message handlers

void CTierazonView::OnFractalsMovie() 
{
	//if (!bMovieView)
	if (m_pMovieView->GetSafeHwnd() == 0)
	{
		bNewViewSave = bNewView;
		bNewView = FALSE;		// Don't want new views in movie preparation
		bMovieView = TRUE;
		bGlobalDraw = TRUE;
		m_pMovieView->Create();

		m_pMovieView->m_Frames = frames;
		m_pMovieView->bStartButton = FALSE;

		if (AVIFileName == "")
		{
			szTemp = GetDocument()->GetTitle();
			//szTemp.GetBufferSetLength(szTemp.GetLength()-3);
			AVIFileName	= szTemp + ".avi";
		}

		m_pMovieView->m_Output_File		= AVIFileName;
		m_pMovieView->m_Width 				= dim.cx;
		m_pMovieView->m_Height 				= dim.cy;
		m_pMovieView->m_MovieRate     = dwMovieRate;
		
		// Fill disk free information
		CString strFreeDiskSpace;
		CString strFmt;
		struct _diskfree_t diskfree;
		int nDrive = _getdrive(); // use current default drive
		if (_getdiskfree(nDrive, &diskfree) == 0)
		{
			strFmt.LoadString(CG_IDS_DISK_SPACE);
			strFreeDiskSpace.Format(strFmt,
				(DWORD)diskfree.avail_clusters *
				(DWORD)diskfree.sectors_per_cluster *
				(DWORD)diskfree.bytes_per_sector / (DWORD)1024L,
				nDrive-1 + _T('A'));
		}
 		else
 			strFreeDiskSpace.LoadString(CG_IDS_DISK_SPACE_UNAVAIL);
		m_pMovieView->SetWindowText(strFreeDiskSpace);

		UpdateMovieData();
		m_pMovieView->ShowWindow(SW_SHOW);

		bAVIFileOpen = FALSE;
	}
	else
	{
		bStartMovie = FALSE;
		bNewView = bNewViewSave;
		bMovieView = FALSE;
		// Destroy the movie dlg
		m_pMovieView->DestroyWindow();
		//bLockStart = FALSE;
		//bLockFinish = FALSE;

		if (bAVIFileOpen)
			CloseAVIFile();
		
	}
}

void CTierazonView::OnUpdateFractalsMovie(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bMovieView);
}

void CTierazonView::UpdateMovieData()
{
	m_pMovieView->m_Output_File == AVIFileName;  // ??
	
	bGlobalDraw = TRUE;
	if (!bLockStart)
	{
		m_pMovieView->m_Magnification	= dMagnification_Start;
		m_pMovieView->m_X_Start				= CRMID_Start;
		m_pMovieView->m_Y_Start				= CIMID_Start;
	}		
		
	if (!bLockFinish)	
	{
		m_pMovieView->m_Magnification_Finish = dMagnification_Finish;
		m_pMovieView->m_X_Finish			= CRMID_Finish;
		m_pMovieView->m_Y_Finish			= CIMID_Finish;
	}

	// FALSE indicates data is being initialized
	m_pMovieView->UpdateData(FALSE);
	// TRUE indicates that data is being retrieved
	m_pMovieView->UpdateData(TRUE);

	bLockStart										= m_pMovieView->m_LockStart;
	bLockFinish										= m_pMovieView->m_LockFinish;
	frames												= m_pMovieView->m_Frames;
	dwMovieRate					          = m_pMovieView->m_MovieRate;
}

void CTierazonView::OnFractalStartgeneratingamovie() 
{
	// TRUE indicates that data is being retrieved
	m_pMovieView->UpdateData(TRUE);
	bGlobalDraw = TRUE;

	if (bLockStart && bLockFinish)
	{
		frames = m_pMovieView->m_Frames;
		dim.cx = m_pMovieView->m_Width;
		dim.cy = m_pMovieView->m_Height;
		AVIFileName = m_pMovieView->m_Output_File;

		CRMID_MovieStart	= m_pMovieView->m_X_Start;
		CRMID_MovieFinish = m_pMovieView->m_X_Finish;

		CIMID_MovieStart	= m_pMovieView->m_Y_Start;
		CIMID_MovieFinish = m_pMovieView->m_Y_Finish;

		if (bOrientationVideoMode)
		{
			CRMID_MovieStart	= 0;
			CRMID_MovieFinish = 1;

			CIMID_MovieStart	= 1	;
			CIMID_MovieFinish = 0;

			bZeroInit = TRUE;
		}

		dMovieMagnifStart  = m_pMovieView->m_Magnification;
		dMovieMagnifFinish = m_pMovieView->m_Magnification_Finish;

		dMagnification_Finish = dMovieMagnifFinish;
		dMagnification = dMovieMagnifStart; 

		if (dMovieMagnifStart == 0 || dMovieMagnifFinish == 0)
		{
			AfxMessageBox("Start or Finish magnifications cannot be zero");
			return;
		}	

		//if (dMovieMagnifStart > dMovieMagnifFinish)
		//	dMovieFrameRatio = 1 - (dMovieMagnifStart-dMovieMagnifFinish)/dMovieMagnifStart;
		//else
		//if (dMovieMagnifStart < dMovieMagnifFinish)
		//	dMovieFrameRatio = 1 - (dMovieMagnifFinish-dMovieMagnifStart)/dMovieMagnifFinish;
		//else
		//	dMovieFrameRatio = 0;

		dMovieFrameRatio = fabs(dMovieMagnifStart-dMovieMagnifFinish)/(double)(frames-1);

		// Don't let start at zero
		if (CRMID_MovieStart < 1E-10 && CRMID_MovieStart > -1E-10)
			CRMID_MovieStart = 1E-10;

		if (CIMID_MovieStart < 1E-10 && CIMID_MovieStart > -1E-10)
			CIMID_MovieStart = 1E-10;
		
		// Don't let finish at zero
		if (CRMID_MovieFinish < 1E-10 && CRMID_MovieFinish > -1E-10)
			CRMID_MovieFinish = 1E-10;

		if (CIMID_MovieFinish < 1E-10 && CIMID_MovieFinish > -1E-10)
			CIMID_MovieFinish = 1E-10;
		
		// Calculate Movie Center Frame Ratios
		CRMID_FrameRatio = fabs(CRMID_MovieStart-CRMID_MovieFinish)/(double)(frames-1);
		CIMID_FrameRatio = fabs(CIMID_MovieStart-CIMID_MovieFinish)/(double)(frames-1);
					
		frame = 0;
		bStartMovie = TRUE;
		m_pMovieView->m_OKButton.SetState(TRUE);

		// AVI File Creation starts here	
		//if (!m_dib.CreateDIB(128, 128))	// Create a bitmap
		//{
		//	AfxMessageBox("Error Creating DIB");
		//}

		// Initiaize AVI File parameters	
		pfile = NULL;
		pf_new = NULL;
		//frames = 0;
		frame = 0;
		timer = 0;
		tmillisecs = 10;
		bAVIPlaying = FALSE;
		szTotalFrames = "";
		szFrameNumber = "";

		// Initialize the stream info for new AVI Files
		newstr.fccType									= streamtypeVIDEO;								// "vids"
		//newstr.fccHandler								= mmioFOURCC('I','V','3','2'); 	// "IV32"
		newstr.fccHandler								= NULL; 													// "IV32"
		newstr.dwFlags									= 0;															// 0
		newstr.dwCaps										= 0;															// 0
		newstr.wPriority								= 0;															// 0
		newstr.wLanguage								= 0;															// 0
		newstr.dwScale									= 1;															// 33365 , 66512
		newstr.dwRate                		= dwMovieRate;										// 15
		newstr.dwStart									= 0;															// 0
		newstr.dwLength									= 1;															// 120
		newstr.dwInitialFrames					= 0;															// 0
		newstr.dwSuggestedBufferSize		= 0;															// 49152
		newstr.dwQuality								= 0;															// 8500	, 7500
		newstr.dwSampleSize							= strhdr.dwSampleSize;						// 0
		SetRect(&newstr.rcFrame, 0, 0, dim.cx, dim.cy);										// 0,180,240
		newstr.dwEditCount							= 0;															// 0
		newstr.dwFormatChangeCount			= 0;															// 0
		//strcpy (newstr.szName,"Junk Video #1");														// $(FILENAME) Video #1
		strcpy (newstr.szName,AVIFileName);														// AVIFileName
							
		AVIFileInit();

		char newFileName[81];
		strcpy(newFileName,AVIFileName);

		hr = AVIFileOpen(&pf_new, (LPCTSTR) newFileName, OF_WRITE | OF_CREATE, NULL);
		if (hr != 0)
		{
			AfxMessageBox("Failed to create new file");
			AVIFileExit();
			return;
		}

		bAVIFileOpen = TRUE;

		hr = AVIFileCreateStream(pf_new, &ps_new, &newstr);
		if (hr != 0)
		{
			AfxMessageBox("Failed to create stream");
			AVIFileRelease(pf_new);	
			AVIFileExit();
			bAVIFileOpen = FALSE;
			return;
		}
	}
	else
	{
		AfxMessageBox("Start and Finish Positions have not been Locked");
		return;
	}	
		
	m_pMovieView->SetWindowText("Start");
}

void CTierazonView::OnUpdateFractalStartgeneratingamovie(CCmdUI* pCmdUI) 
{
	if (m_pMovieView->GetSafeHwnd() == 0)
 		pCmdUI->Enable(FALSE);
	else
	{
		m_pMovieView->UpdateData(FALSE);
		bGlobalDraw = TRUE;

		bLockStart		= m_pMovieView->m_LockStart;
		bLockFinish		= m_pMovieView->m_LockFinish;
		
		if (bLockStart && bLockFinish && !bStartMovie)
 			pCmdUI->Enable(TRUE);
		else
		{
			pCmdUI->Enable(FALSE);

		}		
	}

	pCmdUI->SetCheck(bStartMovie);
}

void CTierazonView::GenerateAMovie()
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	LONG nSamples = 1;
	bGlobalDraw = TRUE;

	if (frame > 0)
	{
		if (frame == 1)
		{
			// Create the first stream
			pDoc->m_pDIB_doc = pDoc->m_dib.Get_m_pDIB();
			biNew = (LPBITMAPINFOHEADER) pDoc->m_pDIB_doc;

			//bitcount = biNew->biBitCount;
			//char cstr[81];
			//wsprintf(cstr,"bitcount = %d",bitcount);
			//AfxMessageBox(cstr);

			//hr = AVIStreamSetFormat(ps_new, 0, biNew, sizeof(BITMAPINFOHEADER) + 1024);
			hr = AVIStreamSetFormat(ps_new, 0, biNew, sizeof(BITMAPINFOHEADER)); // Rev 19
			if (hr != 0)
			{
				AfxMessageBox("AVI Stream error setting format");
				AVIStreamRelease(ps_new);
				AVIFileRelease(pf_new);	
				AVIFileExit();
				bStartMovie = FALSE;
				m_pMovieView->m_OKButton.SetState(FALSE);
				m_pMovieView->bStartButton = FALSE;
				bAVIFileOpen = FALSE;
				return;
			}
			// Save the data
			hr = AVIStreamWrite(ps_new, frame-1, nSamples, (LPVOID) pDoc->m_dib.GetBits(), 
				biNew->biSizeImage,
						AVIIF_KEYFRAME, NULL, NULL);
			if (hr != 0)
			{
				AfxMessageBox("AVI file error writing to stream");
				AVIStreamRelease(ps_new);
				AVIFileRelease(pf_new);	
				AVIFileExit();
				bStartMovie = FALSE;
				m_pMovieView->m_OKButton.SetState(FALSE);
				m_pMovieView->bStartButton = FALSE;
				bAVIFileOpen = FALSE;
				return;
			}
		}
		else
		{
			// Save the data
			hr = AVIStreamWrite(ps_new, frame-1, nSamples, (LPVOID) pDoc->m_dib.GetBits(), 
				biNew->biSizeImage,
						AVIIF_KEYFRAME, NULL, NULL);
		}

		if (hr != 0)
		{
			AfxMessageBox("AVI file error writing to stream");
			AVIStreamRelease(ps_new);
			AVIFileRelease(pf_new);	
			AVIFileExit();
			bStartMovie = FALSE;
			m_pMovieView->m_OKButton.SetState(FALSE);
			m_pMovieView->bStartButton = FALSE;
			bAVIFileOpen = FALSE;
			return;
		}
	}
	
	/*
	// Do calculation as a function of frame #
	if (dMovieMagnifFinish >= dMovieMagnifStart)
		dMagnification = dMovieMagnifStart + dMovieFrameRatio * frame;
	else
		dMagnification = dMovieMagnifStart - dMovieFrameRatio * frame;

	*/

	//dMagnification = dMovieMagnifStart * (dMovieMagnifFinish / dMovieMagnifStart) ^ (frame/frames);


	//x = dMovieMagnifFinish / dMovieMagnifStart;
	//y = (double) frame / (double) frames;
	//temp = pow(x, y);
	//dMagnification = dMovieMagnifStart * temp;

	dMagnification = dMovieMagnifStart * 
		pow((dMovieMagnifFinish / dMovieMagnifStart) , ((double)frame/(double)frames));
	
	if (CRMID_MovieFinish >= CRMID_MovieStart)
		CRMID = CRMID_MovieStart + CRMID_FrameRatio * frame;
	else
		CRMID = CRMID_MovieStart - CRMID_FrameRatio * frame;

	if (CIMID_MovieFinish >= CIMID_MovieStart)
		CIMID = CIMID_MovieStart + CIMID_FrameRatio * frame;
	else
		CIMID = CIMID_MovieStart - CIMID_FrameRatio * frame;

	if (bJuliaVideoMode)
	{
		/////////
		// A julia option
		//

		jul = 1;
		jul_save = 1;

		cx = CRMID_JUL = CRMID;
		cy = CIMID_JUL = CIMID;
		CIMID = 0;
		CRMID = 0;

		////////////////////
	}

	if (bOrientationVideoMode)
	// An Orientation option
	{
		cOrient.set_real(CRMID);
		cOrient.set_imag(CIMID);
		CIMID = 0;
		CRMID = 0;
	}

	char cstr[81];
	//sprintf(cstr,"Frame: %ld, Magnif: %f, X_Center: %f, Y_Center: %f",
	//	frame, dMagnification, CRMID, CIMID);
	sprintf(cstr,"Frame: %ld of %ld", frame, frames);

	m_pMovieView->SetWindowText(cstr);
	m_pMovieView->UpdateData();

	// Increment the frame
	frame++;

	if (frame > frames)
	{
		// Finished
		bStartMovie = FALSE;
		m_pMovieView->m_OKButton.SetState(FALSE);
		m_pMovieView->bStartButton = FALSE;
		CloseAVIFile();
		return;
	}
	
	//AfxMessageBox("Step 8");

	//GoDoFractal();
	if (!bAbort)
	{
		bDraw = TRUE;
		bLaunch = FALSE;
		bInitialized = FALSE;
		bGlobalDraw = TRUE;
	}
	else
		AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FRACTALS_MOVIE);
		
}

void CTierazonView::CloseAVIFile()
{
	// Close the stream and file
	AVIStreamRelease(ps_new);
	AVIFileRelease(pf_new);	

	AVIFileExit();
		
	bAVIFileOpen = FALSE;
}

void CTierazonView::OnFractalVideoplayer() 
{
	if (WinExec ("aviedi32.exe", SW_SHOWNORMAL) <= 32)
		AfxMessageBox("Error executing 'aviedi32.exe'");
}

LONG CTierazonView::CancelMovie(WPARAM wParam, LPARAM lParam)
{
	bStartMovie = FALSE;
	bGlobalDraw = FALSE;
	bNewView = bNewViewSave;
	bMovieView = FALSE;

	if (bAVIFileOpen)
		CloseAVIFile();
			
	return 0L;
}
	
void CTierazonView::OnViewJuliavideo() 
{
	bJuliaVideoMode ^= 1;	
}

void CTierazonView::OnUpdateViewJuliavideo(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bJuliaVideoMode);
}

void CTierazonView::OnViewOrientationvideo() 
{
	bOrientationVideoMode ^= 1;
}

void CTierazonView::OnUpdateViewOrientationvideo(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bOrientationVideoMode);
}

