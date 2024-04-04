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

RGB_IDATA CTierazonView::save_stdcall(DLLFUNC func, double cx, double cy, double zx, double zy, int px, int py)
{
  return (*func) (cx, cy, zx, zy, px, py);
}

int CTierazonView::filter_stdcall(DLLFILTER func, double zx, double zy, int i)
{
  return (*func) (zx, zy, i);
}

RGB_IDATA CTierazonView::complete_stdcall(DLLCOMPLETE func)
{
  return (*func) ();
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
	rgbColor = save_stdcall(lpfnFormulae, 
						 c.real(), c.imag(), z.real(), z.imag(), px, py);			
	/////////////////////////////////////////////////////*/

	if (nDistortion == 101 || nDistortion == 118)  // formula editor
	{		
		// Formula editor/ parser

		switch (nDistortion)
		{
			case 101:  // M-Set
				while( i++ < NMAX
					&& z.abs() < dBailout)
				{
					z = ParsedExpr->Do();              
					if (nFilter) 
						i = filter_stdcall(lpfnFilter, z.real(), z.imag(), i);
				}
				break;

			case 118:  // N-Set
				z2 = cmplx(42,42);
				while ((z-z2).abs() > dMIN && i++ < NMAX)
				{
					z2 = z;
					z = ParsedExpr->Do();              
					if (nFilter) 
						i = filter_stdcall(lpfnFilter, z.real(), z.imag(), i);
				}
				break;
		}

		if (nFilter) 
		{
			rgbColor = complete_stdcall(lpfnComplete); 
		}
		else
		{
			rgbColor.i = i;
			rgbColor.rj = i;
			rgbColor.gj = i;
			rgbColor.bj = i;
		}		
	}

	i = (int) rgbColor.i;
	//i = 1;

	if (dim.cx <= 640 && dim.cy <= 480 && nUsingBuffers)
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
	
	if (dim.cx <= 640 && dim.cy <= 480 && nUsingBuffers)
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
			bStartMovie = FALSE;
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
	bAutoAntialias_Init = FALSE;

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
	if (bGrayScale)
	{
		ntemp = (int) (((double)rj + (double)gj + (double)bj)/3.0);
		red = grn = blu = ntemp;
	}

	if (nColorMode == I_SEE_DA_LIGHT)
	{
		if (red < 0)
			red = 0;

		if (grn < 0)
			grn = 0;

		if (blu < 0)
			blu = 0;
		
		if (red > 255)
			red = 255;

		if (grn > 255)
			grn = 255;

		if (blu > 255)
			blu = 255;
	}

	if ((red & 0x1FF) > 0xFF) 
    red = red ^ 0xFF;    // Invert the color

  if ((grn & 0x1FF) > 0xFF) 
		grn = grn ^ 0xFF;    // Invert the color
      
  if ((blu & 0x1FF) > 0xFF) 
    blu = blu ^ 0xFF;    // Invert the color

	red = red & 0xFF;
	grn = grn & 0xFF;
	blu = blu & 0xFF;

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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	if (nFDOption < 1)
		nFDOption = 8;

	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	if (nFDOption < 1)
		nFDOption = 4;
	
	SaveForUndo();
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
	SaveForUndo();
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
	if (nFDOption < 1)
		nFDOption = 8;

	SaveForUndo();
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
	SaveForUndo();
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
	if (nFDOption < 1)
		nFDOption = 4;

	SaveForUndo();
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
	if (nFDOption < 1)
		nFDOption = 4;

	SaveForUndo();
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

void CTierazonView::OnFilter39() 
{
	SaveForUndo();
	nFilter = 39;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter39(CCmdUI* pCmdUI) 
{
	if (nFilter == 39)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter40() 
{
	SaveForUndo();
	nFilter = 40;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter40(CCmdUI* pCmdUI) 
{
	if (nFilter == 40)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter41() 
{
	SaveForUndo();
	nFilter = 41;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter41(CCmdUI* pCmdUI) 
{
	if (nFilter == 41)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter42() 
{
	SaveForUndo();
	nFilter = 42;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter42(CCmdUI* pCmdUI) 
{
	if (nFilter == 42)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter43() 
{
	SaveForUndo();
	nFilter = 43;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter43(CCmdUI* pCmdUI) 
{
	if (nFilter == 43)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter44() 
{
	SaveForUndo();
	nFilter = 44;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter44(CCmdUI* pCmdUI) 
{
	if (nFilter == 44)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter45() 
{
	SaveForUndo();
	nFilter = 45;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter45(CCmdUI* pCmdUI) 
{
	if (nFilter == 45)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter46() 
{
	SaveForUndo();
	nFilter = 46;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter46(CCmdUI* pCmdUI) 
{
	if (nFilter == 46)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter47() 
{
	SaveForUndo();
	nFilter = 47;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter47(CCmdUI* pCmdUI) 
{
	if (nFilter == 47)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter48() 
{
	if (nFDOption < 1)
		nFDOption = 4;

	SaveForUndo();
	nFilter = 48;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter48(CCmdUI* pCmdUI) 
{
	if (nFilter == 48)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter49() 
{
	if (nFDOption < 1)
		nFDOption = 4;

	SaveForUndo();
	nFilter = 49;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter49(CCmdUI* pCmdUI) 
{
	if (nFilter == 49)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter50() 
{
	SaveForUndo();
	nFilter = 50;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter50(CCmdUI* pCmdUI) 
{
	if (nFilter == 50)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter51() 
{
	SaveForUndo();
	nFilter = 51;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter51(CCmdUI* pCmdUI) 
{
	if (nFilter == 51)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnFilter52() 
{
	SaveForUndo();
	nFilter = 52;	
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateFilter52(CCmdUI* pCmdUI) 
{
	if (nFilter == 52)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// Fractal dimension options to go with filter 27.

void CTierazonView::OnOptions1() 
{
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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
	SaveForUndo();
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


void CTierazonView::OnOptions11() 
{
	SaveForUndo();
	nFDOption = 11;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions11(CCmdUI* pCmdUI) 
{
	if (nFDOption == 11)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions12() 
{
	SaveForUndo();
	nFDOption = 12;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions12(CCmdUI* pCmdUI) 
{
	if (nFDOption == 12)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions13() 
{
	SaveForUndo();
	nFDOption = 13;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions13(CCmdUI* pCmdUI) 
{
	if (nFDOption == 13)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions14() 
{
	SaveForUndo();
	nFDOption = 14;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions14(CCmdUI* pCmdUI) 
{
	if (nFDOption == 14)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions15() 
{
	SaveForUndo();
	nFDOption = 15;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions15(CCmdUI* pCmdUI) 
{
	if (nFDOption == 15)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions16() 
{
	SaveForUndo();
	nFDOption = 16;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions16(CCmdUI* pCmdUI) 
{
	if (nFDOption == 16)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions17() 
{
	SaveForUndo();
	nFDOption = 17;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions17(CCmdUI* pCmdUI) 
{
	if (nFDOption == 17)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions18() 
{
	SaveForUndo();
	nFDOption = 18;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions18(CCmdUI* pCmdUI) 
{
	if (nFDOption == 18)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions19() 
{
	SaveForUndo();
	nFDOption = 19;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions19(CCmdUI* pCmdUI) 
{
	if (nFDOption == 19)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnOptions20() 
{
	SaveForUndo();
	nFDOption = 20;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateOptions20(CCmdUI* pCmdUI) 
{
	if (nFDOption == 20)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

/////////////////////////////////////////////////////////
