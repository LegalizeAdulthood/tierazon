// Tierazon.h : main header file for the TIERAZON application
//

#if !defined(AFX_TIERAZON_H__09FDBB25_6F08_11D1_9E84_444553540000__INCLUDED_)
#define AFX_TIERAZON_H__09FDBB25_6F08_11D1_9E84_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTierazonApp:
// See Tierazon.cpp for the implementation of this class
//

class CTierazonApp : public CWinApp
{
public:
	CTierazonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTierazonApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTierazonApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#define WM_DOREALIZE          (WM_USER + 0)
#define ID_APPLICATION_IDLE		(WM_USER + 1)
#define ID_SAVE_DIB		        (WM_USER + 2)
#define WM_DLGGRADIENT				(WM_USER + 3)
#define ID_GRADIENT_APPLY			(WM_USER + 4)
#define ID_DLGCLOSE						(WM_USER + 5)
#define ID_APPLY							(WM_USER + 6)
#define WM_DLGSHIFT	  				(WM_USER + 7)
#define ID_SHIFTAPPLY					(WM_USER + 8)
#define ID_SHIFTCLOSE					(WM_USER + 9)
#define ID_SHIFTREVERSE				(WM_USER + 10)
#define ID_SHIFTFORWARD				(WM_USER + 11)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIERAZON_H__09FDBB25_6F08_11D1_9E84_444553540000__INCLUDED_)
