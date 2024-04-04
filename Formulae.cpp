///////////////////////////////////////////
// Formulae.cpp

#include "stdafx.h"
#include "Tierazon.h"
 
#include "TierazonDoc.h"
#include "TierazonView.h"
#include "mainfrm.h"
#include <math.h>
#include "external.h"
#include "xysize.h"

RGB_IDATA CTierazonView::save_stdcall(DLLFUNC func, int nFormula, int nFilter, int nColorMethod, int dBailout, int NMAX, double cx, double cy, double zx, double zy, int px, int py)
{
  return (*func) (nFormula, nFilter, nColorMethod, dBailout, NMAX, cx, cy, zx, zy, px, py);
}

//////////////////////////////////////////////////////////////////////
void CTierazonView::TestEquations()
{
  CTierazonDoc* pDoc = GetDocument();
	i = xi = yi = ii = 0;
	
	rj = bj = gj = 0;
	x_temp = 0;
	y_temp = 0;	
	temp = 0;
	z2=cmplx(1e12,0);
	NMAX_Save = NMAX;

	//limit = sqrt(cx*cx+cy*cy);
	//dStrands_HI = limit + dStrands;
	//dStrands_LO = limit - dStrands;

	//zx = z.real();
	//zy = z.imag();
		
	/////////////////////////////////////////////////////*
	rgbColor = save_stdcall(lpfnFormulae, nDistortion,
				     nFilter, nColorMethod, dBailout, NMAX,
				     c.real(), c.imag(), z.real(), z.imag(), px, py);			
	/////////////////////////////////////////////////////*/

	i = (int) rgbColor.i;
	//i = 1;

	if (dim.cx <= 1024 && dim.cy <= 1024)
		iIter_Data[px + py*pDoc->m_sizeDoc.cx] = i;

	Returning_From_DLL();

}

void CTierazonView::Returning_From_DLL()
{
  CTierazonDoc* pDoc = GetDocument();

	if (px < 0 || px >= dim.cx)
		AfxMessageBox("1. Error, px is out of range");
	if (py < 0 || py >= dim.cy)
		AfxMessageBox("1. Error, py is out of range");

	//i = (int) rgbColor.i;
	//i = 1;

	/*
	if (bMFilter)
	{
		FDimension();
		rgbColor.rj = rj;
		rgbColor.gj = gj;
		rgbColor.bj = bj;
	}
	*/

	if (bColorize)
	{
		rj = rgbColor.rj;
		gj = rgbColor.gj;
		bj = rgbColor.bj;
	}
	else
	{
		rj = gj = bj = rgbColor.i;
	}

	if (i == 0)
	{
		rj = gj = bj = 0;
		red = grn = blu = 0;
	}
	else
		Generalized_Coloring_Method();		
	
	if (dim.cx <= 1024 && dim.cy <= 1024)
	{
		//iIter_Data[px + py*pDoc->m_sizeDoc.cx] = i;
		rIter_Data[px + py*pDoc->m_sizeDoc.cx] = (int) rj;
		gIter_Data[px + py*pDoc->m_sizeDoc.cx] = (int) gj;
		bIter_Data[px + py*pDoc->m_sizeDoc.cx] = (int) bj;
	}
		
	//if (i == 0)
		//red = grn = blu = 0;

  if (bDraw)
  { 
		if (!pDoc->m_dib.SetPixel(px, py, RGB(red, grn, blu)))
    {
		  AfxMessageBox("Error writing to DIB");  
		  Row = RowMax;
		  Col = ColMax;
			px = dim.cx;
			py = dim.cy;
			bAbort = TRUE;
		  bDraw = FALSE;
		  bLaunch = FALSE;
	  }              
  }
}

void CTierazonView::Terminate()
{
	::SetCursor(mHCross);

	Row = RowMax;
	Col = ColMax;
	px = dim.cx-1;
	py = dim.cy-1;
	bAbort = TRUE;
}

/////////////////////////////////////////////////
void CTierazonView::Generalized_Coloring_Method()
{
	switch (nColorOrder)
	{
		case 0:		// rgb
			red = (int) (rj*(double)(nRed))+nRedStart;
			grn = (int) (gj*(double)(nGrn))+nGrnStart;
			blu = (int) (bj*(double)(nBlu))+nBluStart;
			break;

		case 1:		// rbg
			red = (int) (rj*(double)(nRed))+nRedStart;
			grn = (int) (bj*(double)(nGrn))+nGrnStart;
			blu = (int) (gj*(double)(nBlu))+nBluStart;
			break;

		case 2:		// grb
			red = (int) (gj*(double)(nRed))+nRedStart;
			grn = (int) (rj*(double)(nGrn))+nGrnStart;
			blu = (int) (bj*(double)(nBlu))+nBluStart;
			break;

		case 3:		// gbr
			red = (int) (gj*(double)(nRed))+nRedStart;
			grn = (int) (bj*(double)(nGrn))+nGrnStart;
			blu = (int) (rj*(double)(nBlu))+nBluStart;
			break;

		case 4:		// brg
			red = (int) (bj*(double)(nRed))+nRedStart;
			grn = (int) (rj*(double)(nGrn))+nGrnStart;
			blu = (int) (gj*(double)(nBlu))+nBluStart;
			break;

		case 5:		// bgr
			red = (int) (bj*(double)(nRed))+nRedStart;
			grn = (int) (gj*(double)(nGrn))+nGrnStart;
			blu = (int) (rj*(double)(nBlu))+nBluStart;
			break;
	}
		
  Apply_The_Color();
}

void CTierazonView::Apply_The_Color()
{  				
	
	if ((red & 0x1FF) > 0xFF) 
    red = red ^ 0xFF;    // Invert the color

  if ((grn & 0x1FF) > 0xFF) 
		grn = grn ^ 0xFF;    // Invert the color
      
  if ((blu & 0x1FF) > 0xFF) 
    blu = blu ^ 0xFF;    // Invert the color

	if (bGrayScale)
	{
		ntemp = (red + grn + blu)/3;
		red = grn = blu = ntemp;
	}

	if (bColorInvert)
	{
		red ^= 0xFF;
		grn ^= 0xFF;
		blu ^= 0xFF;
	}	

}

/////////////////////////////////////////////////////

void CTierazonView::OnColorSeparate() 
{
	bColorize ^= 1;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColorSeparate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bColorize);
}

void CTierazonView::OnColorRgb() 
{
	nColorOrder = 0;	
	//Generalized_Coloring_Method();		
	//Apply_Color();
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColorRgb(CCmdUI* pCmdUI) 
{
	if (nColorOrder == 0)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	
	pCmdUI->Enable(bColorize);
}

void CTierazonView::OnColorRbg() 
{
	nColorOrder = 1;	
	//Generalized_Coloring_Method();		
	//Apply_Color();
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColorRbg(CCmdUI* pCmdUI) 
{
	if (nColorOrder == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(bColorize);
}

void CTierazonView::OnColorGrb() 
{
	nColorOrder = 2;	
	//Generalized_Coloring_Method();		
	//Apply_Color();
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColorGrb(CCmdUI* pCmdUI) 
{
	if (nColorOrder == 2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(bColorize);
}

void CTierazonView::OnColorGbr() 
{
	nColorOrder = 3;	
	//Generalized_Coloring_Method();		
	//Apply_Color();
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColorGbr(CCmdUI* pCmdUI) 
{
	if (nColorOrder == 3)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(bColorize);
}

void CTierazonView::OnColorBrg() 
{
	nColorOrder = 4;	
	//Generalized_Coloring_Method();		
	//Apply_Color();
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColorBrg(CCmdUI* pCmdUI) 
{
	if (nColorOrder == 4)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(bColorize);
}

void CTierazonView::OnColorBgr() 
{
	nColorOrder = 5;	
	//Generalized_Coloring_Method();		
	//Apply_Color();
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColorBgr(CCmdUI* pCmdUI) 
{
	if (nColorOrder == 5)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(bColorize);
}


void CTierazonView::OnColorGrayscale() 
{
	bGrayScale ^= TRUE;	
	//Generalized_Coloring_Method();		
	//Apply_Color();
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColorGrayscale(CCmdUI* pCmdUI) 
{
	if (bGrayScale)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColorInvert() 
{
	bColorInvert ^= TRUE;	
	//Generalized_Coloring_Method();		
	//Apply_Color();
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColorInvert(CCmdUI* pCmdUI) 
{
	if (bColorInvert)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

/////////////////////////////////////////////////////

void CTierazonView::OnFilter0() 
{
	nFilter = 0;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter0(CCmdUI* pCmdUI) 
{
	if (nFilter == 0)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter01() 
{
	nFilter = 1;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter01(CCmdUI* pCmdUI) 
{
	if (nFilter == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter02() 
{
	nFilter = 2;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter02(CCmdUI* pCmdUI) 
{
	if (nFilter == 2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter03() 
{
	nFilter = 3;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter03(CCmdUI* pCmdUI) 
{
	if (nFilter == 3)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter04() 
{
	nFilter = 4;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter04(CCmdUI* pCmdUI) 
{
	if (nFilter == 4)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter05() 
{
	nFilter = 5;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter05(CCmdUI* pCmdUI) 
{
	if (nFilter == 5)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter06() 
{
	nFilter = 6;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter06(CCmdUI* pCmdUI) 
{
	if (nFilter == 6)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter07() 
{
	nFilter = 7;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter07(CCmdUI* pCmdUI) 
{
	if (nFilter == 7)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter08() 
{
	nFilter = 8;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter08(CCmdUI* pCmdUI) 
{
	if (nFilter == 8)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter09() 
{
	nFilter = 9;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter09(CCmdUI* pCmdUI) 
{
	if (nFilter == 9)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter10() 
{
	nFilter = 10;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter10(CCmdUI* pCmdUI) 
{
	if (nFilter == 10)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter11() 
{
	nFilter = 11;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter11(CCmdUI* pCmdUI) 
{
	if (nFilter == 11)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter12() 
{
	nFilter = 12;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter12(CCmdUI* pCmdUI) 
{
	if (nFilter == 12)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter13() 
{
	nFilter = 13;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter13(CCmdUI* pCmdUI) 
{
	if (nFilter == 13)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter14() 
{
	nFilter = 14;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter14(CCmdUI* pCmdUI) 
{
	if (nFilter == 14)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter15() 
{
	nFilter = 15;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter15(CCmdUI* pCmdUI) 
{
	if (nFilter == 15)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter16() 
{
	nFilter = 16;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter16(CCmdUI* pCmdUI) 
{
	if (nFilter == 16)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter17() 
{
	nFilter = 17;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter17(CCmdUI* pCmdUI) 
{
	if (nFilter == 17)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter18() 
{
	nFilter = 18;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter18(CCmdUI* pCmdUI) 
{
	if (nFilter == 18)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter19() 
{
	nFilter = 19;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter19(CCmdUI* pCmdUI) 
{
	if (nFilter == 19)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter20() 
{
	nFilter = 20;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter20(CCmdUI* pCmdUI) 
{
	if (nFilter == 20)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter21() 
{
	nFilter = 21;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter21(CCmdUI* pCmdUI) 
{
	if (nFilter == 21)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter22() 
{
	nFilter = 22;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter22(CCmdUI* pCmdUI) 
{
	if (nFilter == 22)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter23() 
{
	nFilter = 23;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter23(CCmdUI* pCmdUI) 
{
	if (nFilter == 23)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter24() 
{
	nFilter = 24;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter24(CCmdUI* pCmdUI) 
{
	if (nFilter == 24)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter25() 
{
	nFilter = 25;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter25(CCmdUI* pCmdUI) 
{
	if (nFilter == 25)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter26() 
{
	nFilter = 26;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter26(CCmdUI* pCmdUI) 
{
	if (nFilter == 26)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter27() 
{
	if (nFDOption < 1 || nFDOption > 10)
		nFDOption = 8;

	nFilter = 27;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter27(CCmdUI* pCmdUI) 
{
	if (nFilter == 27)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter28() // Standard Deviation
{
	nFilter = 28;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter28(CCmdUI* pCmdUI) 
{
	if (nFilter == 28)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CTierazonView::OnFilter29() 
{
	nFilter = 29;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter29(CCmdUI* pCmdUI) 
{
	if (nFilter == 29)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter30() 
{
	nFilter = 30;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter30(CCmdUI* pCmdUI) 
{
	if (nFilter == 30)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter31() 
{
	nFilter = 31;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter31(CCmdUI* pCmdUI) 
{
	if (nFilter == 31)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter32() 
{
	nFilter = 32;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter32(CCmdUI* pCmdUI) 
{
	if (nFilter == 32)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter33() 
{
	if (nFDOption < 1 || nFDOption > 10)
		nFDOption = 4;
	
	nFilter = 33;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter33(CCmdUI* pCmdUI) 
{
	if (nFilter == 33)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter34() 
{
	nFilter = 34;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter34(CCmdUI* pCmdUI) 
{
	if (nFilter == 34)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter35() 
{
	if (nFDOption < 1 || nFDOption > 10)
		nFDOption = 4;

	nFilter = 35;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter35(CCmdUI* pCmdUI) 
{
	if (nFilter == 35)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CTierazonView::OnFilter36() 
{
	nFilter = 36;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter36(CCmdUI* pCmdUI) 
{
	if (nFilter == 36)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter37() 
{
	if (nFDOption < 1 || nFDOption > 10)
		nFDOption = 4;

	nFilter = 37;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter37(CCmdUI* pCmdUI) 
{
	if (nFilter == 37)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter38() 
{
	if (nFDOption < 1 || nFDOption > 10)
		nFDOption = 4;

	nFilter = 38;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter38(CCmdUI* pCmdUI) 
{
	if (nFilter == 38)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// Fractal dimension options to go with filter 27.

void CTierazonView::OnOptions1() 
{
	nFDOption = 1;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions1(CCmdUI* pCmdUI) 
{
	if (nFDOption == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions2() 
{
	nFDOption = 2;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions2(CCmdUI* pCmdUI) 
{
	if (nFDOption == 2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions3() 
{
	nFDOption = 3;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions3(CCmdUI* pCmdUI) 
{
	if (nFDOption == 3)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions4() 
{
	nFDOption = 4;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions4(CCmdUI* pCmdUI) 
{
	if (nFDOption == 4)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions5() 
{
	nFDOption = 5;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions5(CCmdUI* pCmdUI) 
{
	if (nFDOption == 5)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions6() 
{
	nFDOption = 6;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions6(CCmdUI* pCmdUI) 
{
	if (nFDOption == 6)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions7() 
{
	nFDOption = 7;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions7(CCmdUI* pCmdUI) 
{
	if (nFDOption == 7)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions8() 
{
	nFDOption = 8;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions8(CCmdUI* pCmdUI) 
{
	if (nFDOption == 8)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions9() 
{
	nFDOption = 9;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions9(CCmdUI* pCmdUI) 
{
	if (nFDOption == 9)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions10() 
{
	nFDOption = 10;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions10(CCmdUI* pCmdUI) 
{
	if (nFDOption == 10)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

/////////////////////////////////////////////////////////
