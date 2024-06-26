/// Pattern.cpp

#include "stdafx.h"
#include "Tierazon.h"

#include "TierazonDoc.h"
#include "TierazonView.h"
#include "Convolut.h"
#include <math.h>
#include "external.h"

void CTierazonView::init_stdcall(DLLINIT func, int nFormula, int nFilter, int nColorMethod, int dBailout, int NMAX, int _jul, int _jul_save, double _dStrands, double dBay100, double dBay1000, double dLower, double dUpper, double *pXTemp, double *pYTemp, double *pXSave, double *pYSave, double *rjData, double *gjData, double *bjData, int nRed, int nGrn, int nBlu, int nRedStart, int nGrnStart, int nBluStart, int nFDOption, int bDimensionVariant, int size_x, int size_y, int nUsingBuffers)
{
	(*func) (nFormula, nFilter, nColorMethod, dBailout, NMAX, jul, jul_save, dStrands, dBay100, dBay1000, dLower, dUpper, pXTemp, pYTemp, pXSave, pYSave, rjData, gjData, bjData, nRed, nGrn, nBlu, nRedStart, nGrnStart, nBluStart, nFDOption, bDimensionVariant, size_x, size_y, nUsingBuffers);
}

RGB_IDATA CTierazonView::color_stdcall(DLLCOLOR func, int px, int py, int nColorMethod, double cx, double cy, double zx, double zy)
{
  return (*func) (px, py, nColorMethod, cx, cy, zx, zy);
}

void CTierazonView::DrawPattern()  // Step 1
{
	if (bDraw) 
	{
		bGlobalDraw = TRUE;
		if (!bAbort)
			GeneratePattern();
		if (!bLaunch || bAbort) 
		{
			// Pattern complete, restore variables
			bDraw = FALSE;
			bAbort = FALSE;
			bTracker = FALSE;
			//GetDocument()->SetModifiedFlag(TRUE);

			if (!bStartMovie)
				bGlobalDraw = FALSE;
			      
			bZoomingMode = FALSE;

			nColorMethodSave = nColorMethod;
			bInitialized = TRUE;
			nFilterSave = nFilter;
			nDistortionSave = nDistortion;
			nFDOptionSave = nFDOption;

			if (dim.cx <= 640 && dim.cy <= 480 && nUsingBuffers)			
				bInitialized = TRUE;

			jul_save = jul;

			CTierazonDoc* pDoc = GetDocument();
			
			szTemp = szInkFileName;						
	    if ( ! outFile.Open( szTemp, 
	   							CFile::modeRead))
		  {
				// If file does not exist, create it
				szTemp = szTemp.GetBufferSetLength(szTemp.GetLength()-3);				
				szTemp+="bmp";
				pDoc->OnSaveDocument(szTemp);
			}
			else
				outFile.Close();				

			// Check for Convolution Processing
			if (nMatrix)
			{
				if (!bAbort)
				{
					BeginWaitCursor();
					// Copy temporary bitmap
					if (!pDoc->m_dib.CopyTemp())
						AfxMessageBox("Error Copying Temporary Bitmap");
					if (m_pConvolutView->bConvoluteContinuous)
						PostMessage(WM_COMMAND, ID_FILTER_CONVOLUTION_APPLY);
						//PostMessage(WM_USER_CONVOLUTE, NULL);
					else
						nMatrix = 0;
					EndWaitCursor();
				}
				else
					nMatrix = 0;

				if (bReduceSize)
				{
					OnConvolveReduce();
				}

				bAutoAntialias_Init = FALSE;
			}						      

			if (bAutoAntialias_Init)
			{
				//bAutoAntialias = FALSE;
				OnConvolveAntialias();
			}
			else
				Invalidate(FALSE);
		}
	}
	else
	{
		if (bStartMovie)
		{
			GenerateAMovie();
			bGlobalDraw = TRUE;
		}
		else
			bGlobalDraw = FALSE;
	}
}

void CTierazonView::adjust_coords()
{
	Radius_x = 2/dMagnification;
	Radius_y = 2/dMagnification;
	
	if (jul == 0 || jul_save == 1)
	{
		CRMAX = CRMID + Radius_x;
		CRMIN = CRMID - Radius_x;
		CIMAX = CIMID + Radius_y;
		CIMIN = CIMID - Radius_y;
	}
	else
	{
		CRMAX = 2;
		CRMIN = -2;
		CIMAX = 2;
		CIMIN = -2;
	}
  	
	rx_ratio = (double) dim.cx/(double) (dim.cy);
  ry_ratio = (double) dim.cy/(double) (dim.cx);

  rx_ratio = rx_ratio + (1-rx_ratio)/2;
  ry_ratio = ry_ratio + (1-ry_ratio)/2;

  CRMAX = CRMAX + (Radius_x * (rx_ratio) - Radius_x);
  CRMIN = CRMIN - (Radius_x * (rx_ratio) - Radius_x);
  CIMAX = CIMAX + (Radius_x * (ry_ratio) - Radius_y);
  CIMIN = CIMIN - (Radius_x * (ry_ratio) - Radius_y);

}

void CTierazonView::GeneratePattern()
{	
	CTierazonDoc* pDoc = GetDocument();

	if (bLaunch)
	{
		LaunchPattern(); 
   	return;
  }  

	if (bAutoAntialias && !bAutoAntialias_Init)
	{
		dim.cx = dim.cx*2;
		dim.cy = dim.cy*2;

		global_width = dim.cx;
		global_height = dim.cy;

		pDoc->m_sizeDoc	= dim;
		bAutoAntialias_Init = TRUE;

		// Create a new DIB
		if (!pDoc->m_dib.CreateDIB((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
		{
			AfxMessageBox("Error Creating DIB");
		}
	}

	// Initialize some variables, Initialize Drawing
	bLaunch = TRUE;

  // Fractal initialization
  ColMax = dim.cx-1;
  RowMax = dim.cy-1;

	size_x = dim.cx;
	size_y = dim.cy;

	if (jul == 1)
	{
		CRMIN = CRMIN_JUL; 
  	CIMIN = CIMIN_JUL;
  	CRMAX = CRMAX_JUL;
  	CIMAX = CIMAX_JUL;
	}
		
	adjust_coords();
	
  Col = 0;

	if ((dim.cx > 640 && dim.cy > 480) || !nUsingBuffers)
	{
		Row = RowMax;
	}
	else
	{
		Row = 0;
		kr = 0;
	}

  CR = CRMIN;
	  
	//if (nFilter != nFilter_save)
		//bInitialized = FALSE;
	
	///////////////////////////////////////////////////////////
	// Initialize color cycling variable
	if (!bInitialized  && nUsingBuffers)
	{
		if (dim.cx <= 640 && dim.cy <= 480 && nUsingBuffers)
		{				
			if (bRed)
				delete bRed;
			if (bGrn)
				delete bGrn;
			if (bBlu)
				delete bBlu;

			//AfxMessageBox("Initializing");
			
			bRed = (BOOL*) new BOOL[dim.cx*dim.cy];
			bGrn = (BOOL*) new BOOL[dim.cx*dim.cy];
			bBlu = (BOOL*) new BOOL[dim.cx*dim.cy];

			if (pXSave)
				delete pXSave;
			if (pYSave)
				delete pYSave;

			pXSave = (double *) new double[dim.cx*dim.cy];
			pYSave = (double *) new double[dim.cx*dim.cy];

			if (rjData)
				delete rjData;
			if (gjData)
				delete gjData;
			if (bjData)
				delete bjData;

			rjData = (double *) new double[dim.cx*dim.cy];
			gjData = (double *) new double[dim.cx*dim.cy];
			bjData = (double *) new double[dim.cx*dim.cy];

			if (iIter_Data)
				delete iIter_Data;

			if (rIter_Data)
				delete rIter_Data;

			if (gIter_Data)
				delete gIter_Data;

			if (bIter_Data)
				delete bIter_Data;
			
			iIter_Data = (int*) new int [dim.cx*dim.cy];
			rIter_Data = (int*) new int [dim.cx*dim.cy];
			gIter_Data = (int*) new int [dim.cx*dim.cy];
			bIter_Data = (int*) new int [dim.cx*dim.cy];
			
			for (i=0; i<dim.cx*dim.cy; i++)
			{
				iIter_Data[i] = 0;
				rIter_Data[i] = 0;
				gIter_Data[i] = 0;
				bIter_Data[i] = 0;
			}

			dim_save = dim;

			for (i=0; i<dim.cx*dim.cy; i++)
			{
				bRed[i] = TRUE;
				bGrn[i] = TRUE;
				bBlu[i] = TRUE;
			}

			bRedStart = TRUE;
			bGrnStart = TRUE;
			bBluStart = TRUE;

		}
		else
			bInitialized = FALSE;
	}
	
	if (dim.cx * dim.cy > 320 * 240)
	{
		// Caculate UBANDS, resolution of update stripes
		UBANDS = (int) ((double) (dim.cx * dim.cy) * .0001);
	}
	else
	{
		UBANDS = 30;
	}

	switch (nFilter)
	{		
		case 27:  // Check for a fractal Dimension filter
		case 28:  // standard deviation filter
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 48:
		case 49:

			bMFilter = TRUE;
			break;

		default:
			bMFilter = FALSE;
	}

	if (bMFilter)
	{
		if (pXTemp)
			delete pXTemp;
		if (pYTemp)
			delete pYTemp;

		pXTemp = (double *) new double[NMAX+1];
		pYTemp = (double *) new double[NMAX+1];

		for (j = 0; j<=NMAX; j++)
		{
			pXTemp[j] = 0;
			pYTemp[j] = 0;
		}
	}			

	///////////////////////////////////////////////////////////
	init_stdcall(lpfnInitialize, nDistortion,
							 nFilter, nColorMethod, dBailout,
							 NMAX,jul, jul_save, dStrands, 
							 dBay100, dBay1000, dLower, dUpper, 
							 pXTemp, pYTemp, pXSave, pYSave, 
							 rjData, gjData, bjData, 
							 nRed, nGrn, nBlu, 
							 nRedStart, nGrnStart, nBluStart, 
							 nFDOption, bDimensionVariant, size_x, size_y,
							 nUsingBuffers);
	///////////////////////////////////////////////////////////

	// Launch The Drawing Pattern for the first time
	LaunchPattern();
}

void CTierazonView::LaunchPattern()
{
	// Mandelbrot Fractal pattern
	TestPattern();

	//if (bAutoAntialias)
		//return;

	if ((dim.cx > 640 && dim.cy > 480)  || !nUsingBuffers)
	{		
		if ((Row % 32) == 0 && !bAutoAntialias)
			Invalidate(FALSE);					///// ?????????

		if ((Row % 32) == 0)  // 2
		{
			Window_Pane(Row);
		}

		if (Row < 0 || dim.cy - Row < 0)
		{
			bDraw = FALSE;
  		bLaunch = FALSE;
				
			char cstr[81];
			wsprintf(cstr, "max iteration = %d", temp_max);
			Status_Bar(cstr);
		}	
	}
	else
	{
		kr++;
		
		Window_Pane(UBANDS - kr);

		if(!bAutoAntialias)
			Invalidate(FALSE);					
	
		if (kr >= UBANDS)
		{
			bDraw = FALSE;
  		bLaunch = FALSE;
				
			char cstr[81];
			wsprintf(cstr, "max iteration = %d", temp_max);
			Status_Bar(cstr);
		}	
	}
}

void CTierazonView::TestPattern()
{
	CTierazonDoc* pDoc = GetDocument();
	
	if ((dim.cx > 640 && dim.cy > 480) || !nUsingBuffers)
	{
		py = Row;
		for (px = 0; px < dim.cx ; px++)
		{
			if (nMatrix)
			{
				if (!pDoc->m_dib.SpatialOperator(px, py, NMAX, bTraceContour))
				{
					AfxMessageBox("Error with Spatial Operator");
					bDraw = FALSE;
					bLaunch = FALSE;
				}
			}
			else
				TestPatternSub();			
		}
		Row--;
	}
	else
	{
		/////////////////////////////////////////////
		// Begin/ continue inner loop

		for (kc=0; kc<UBANDS; kc++)
		{
			for (px = kr; px < dim.cx ; px += UBANDS)
			{
				for (py = kc; py < dim.cy; py += UBANDS)   				
				{
					if (nMatrix)
					{
						if (!pDoc->m_dib.SpatialOperator(px, py, NMAX, bTraceContour))
						{
							AfxMessageBox("Error with Spatial Operator");
							bDraw = FALSE;
							bLaunch = FALSE;
						}
					}
					else				
						TestPatternSub();
				}
			}	
		}
	}
}

void CTierazonView::UpdateColorMethod()
{
	CTierazonDoc* pDoc = GetDocument();

	/////////////////////////////////////////////////////*
	rgbColor = color_stdcall(lpfnColorUpdate, px, py, nColorMethod, c.real(), c.imag(), z.real(), z.imag());			
	/////////////////////////////////////////////////////*/
	
	if (dim.cx <= 640 && dim.cy <= 480 && nUsingBuffers)
		i = iIter_Data[px + py*pDoc->m_sizeDoc.cx];

	Returning_From_DLL();
}
				
void CTierazonView::TestPatternSub()
{
  CTierazonDoc* pDoc = GetDocument();				

	xsquared = ysquared = 0;

	//////////////////////////////////////////////
	// Fractal Initialization
	//

	xO = CRMIN; 
	yO = CIMIN;
	xI = CRMAX;
	yI = CIMAX;

	//xinc = (double)dim.cx/(CRMAX-CRMIN);
	//yinc = (double)dim.cy/(CIMAX-CIMIN);
		
	ldx = (xI - xO) / (double) dim.cx;    /* compute size of pixels */
  ldy = (yI - yO) / (double) dim.cy;
	
	x = xO + (double) px * ldx,  	/* start julia on pixel */
  y = yO + (double) py * ldy;
        
  if (jul == 0)    										// Start mandelbrot set on 0,0 
   	cx = x, cy = y;										// and use pixel for c.
  else if (jul_save == 0) 						// If previous was a mandelbrot
  	cx = CRMID_JUL, cy = CIMID_JUL;  	// A Julia coordinate
  
  xsquared = 0, ysquared = 0;

	// Check minimum and maximum valid limits
	if (cx < zerotol && cx > -zerotol)
	{
		if (cx >= 0)
			cx = zerotol;
		else
			cx = -zerotol;
	}

	if (cy < zerotol && cy > -zerotol)
	{
		if (cy >= 0)
			cy = zerotol;
		else
			cy = -zerotol;
	}
		
	if (x < zerotol && x > -zerotol)
	{
		if (x >= 0)
			x = zerotol;
		else
			x = -zerotol;
	}

	if (y < zerotol && y > -zerotol)
	{
		if (y >= 0)
			y = zerotol;
		else
			y = -zerotol;
	}
	
	// Initialize some complex variables
	z = cmplx (x, y );
	z.set_biomorph(dBiomorph);
	
	c = cmplx(cx, cy);
	c.set_biomorph(dBiomorph);

	z2 = cmplx(0,0);
	z2.set_biomorph(dBiomorph);

	if (jul == 0)
	{
		if (bInvertFractal)
		{
			c = cmplx(1,0)/c;
			z = cmplx(1,0)/z;
		}
		c *= cOrient;
	}
	else if (jul_save == 0)
	{
		if (bInvertFractal) { c = cmplx(1,0)/c; z = cmplx(1,0)/z; }
		c *= cOrient;
		z *= cOrient;
	}
	else
	{
		if (bInvertFractal)
			z = cmplx(1,0)/z;
		z *= cOrient;
	}

	x =  z.real();
	y =  z.imaginary();
	cx = c.real();
	cy = c.imaginary();

  dStrands_HI = sqrt(cx*cx+cy*cy) + dStrands;
  dStrands_LO = sqrt(cx*cx+cy*cy) - dStrands;

	if (bZeroInit && jul == 0)
		z=cmplx(0, 0);
	
	//if (nColorMethod != nColorMethodSave && bInitialized && nColorMethodSave != 0)
	if (nDistortion == nDistortionSave && nFilter == nFilterSave && nFDOption == nFDOptionSave && bInitialized && nColorMethod && !bZoomingMode)
		UpdateColorMethod();
	else					
		TestEquations();
}

/////////////////////////////////////////////

void CTierazonView::OnViewReset() 
{
	CRMID = 0;
	CIMID = 0;
	dMagnification = 1;
	adjust_coords();
	OnViewDraw();	
}

void CTierazonView::OnViewDraw() 
{
	bDraw = TRUE;
	bLaunch = FALSE;
	bInitialized = FALSE;
}

void CTierazonView::OnViewMandel() 
{
	GoDoFractal();
}

void CTierazonView::OnUpdateViewMandel(CCmdUI* pCmdUI) 
{
	if (!jul) pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);	
}

//////////////////////////////////////////////////////////////////////
void CTierazonView::GoDoFractal() 
{
	jul 		 = 0;
	jul_save = 1;
	bDraw = TRUE;
	bLaunch = FALSE;
	bInitialized = FALSE;
}

////////////////////////////////////////////////////////////////

void CTierazonView::OnDraw1() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;
  
	ActiveTitle = "1.) ";

	SaveForUndo();
	nDistortion = 1;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw1(CCmdUI* pCmdUI) 
{
	if (nDistortion == 1) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw2() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "2.) ";
	SaveForUndo();
	nDistortion = 2;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw2(CCmdUI* pCmdUI) 
{
	if (nDistortion == 2) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw3() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "3.) ";
	SaveForUndo();
	nDistortion = 3;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw3(CCmdUI* pCmdUI) 
{
	if (nDistortion == 3) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw4() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "4.) ";
	SaveForUndo();
	nDistortion = 4;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw4(CCmdUI* pCmdUI) 
{
	if (nDistortion == 4) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw5() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "5.) ";
	SaveForUndo();
	nDistortion = 5;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw5(CCmdUI* pCmdUI) 
{
	if (nDistortion == 5) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw6() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "6.) ";
	SaveForUndo();
	nDistortion = 6;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw6(CCmdUI* pCmdUI) 
{
	if (nDistortion == 6) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw7() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "7.) ";
	SaveForUndo();
	nDistortion = 7;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw7(CCmdUI* pCmdUI) 
{
	if (nDistortion == 7) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw8() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "8.) ";
	SaveForUndo();
	nDistortion = 8;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw8(CCmdUI* pCmdUI) 
{
	if (nDistortion == 8) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw9() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "9.) ";
	SaveForUndo();
	nDistortion = 9;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw9(CCmdUI* pCmdUI) 
{
	if (nDistortion == 9) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw10() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "10.) ";
	SaveForUndo();
	nDistortion = 10;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw10(CCmdUI* pCmdUI) 
{
	if (nDistortion == 10) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw11() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "11.) ";
	SaveForUndo();
	nDistortion = 11;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw11(CCmdUI* pCmdUI) 
{
	if (nDistortion == 11) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw12() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "12.) ";
	SaveForUndo();
	nDistortion = 12;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw12(CCmdUI* pCmdUI) 
{
	if (nDistortion == 12) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw13() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "13.) ";
	SaveForUndo();
	nDistortion = 13;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw13(CCmdUI* pCmdUI) 
{
	if (nDistortion == 13) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw14() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "14.) ";
	SaveForUndo();
	nDistortion = 14;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw14(CCmdUI* pCmdUI) 
{
	if (nDistortion == 14) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw15() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "15.) ";
	SaveForUndo();
	nDistortion = 15;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw15(CCmdUI* pCmdUI) 
{
	if (nDistortion == 15) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw16() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "16.) ";
	SaveForUndo();
	nDistortion = 16;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw16(CCmdUI* pCmdUI) 
{
	if (nDistortion == 16) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw17() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "17.) ";
	SaveForUndo();
	nDistortion = 17;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw17(CCmdUI* pCmdUI) 
{
	if (nDistortion == 17) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw18() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "18.) ";
	SaveForUndo();
	nDistortion = 18;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw18(CCmdUI* pCmdUI) 
{
	if (nDistortion == 18) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw19() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "19.) ";
	SaveForUndo();
	nDistortion = 19;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw19(CCmdUI* pCmdUI) 
{
	if (nDistortion == 19) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw20() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "20.) ";
	SaveForUndo();
	nDistortion = 20;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw20(CCmdUI* pCmdUI) 
{
	if (nDistortion == 20) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw21() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "21.) ";
	SaveForUndo();
	nDistortion = 21;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw21(CCmdUI* pCmdUI) 
{
	if (nDistortion == 21) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw22() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "22.) ";
	SaveForUndo();
	nDistortion = 22;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw22(CCmdUI* pCmdUI) 
{
	if (nDistortion == 22) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw23() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "23.) ";
	SaveForUndo();
	nDistortion = 23;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw23(CCmdUI* pCmdUI) 
{
	if (nDistortion == 23) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw24() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "24.) ";
	SaveForUndo();
	nDistortion = 24;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw24(CCmdUI* pCmdUI) 
{
	if (nDistortion == 24) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw25() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "25.) ";
	SaveForUndo();
	nDistortion = 25;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw25(CCmdUI* pCmdUI) 
{
	if (nDistortion == 25) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw26() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "26.) ";
	SaveForUndo();
	nDistortion = 26;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw26(CCmdUI* pCmdUI) 
{
	if (nDistortion == 26) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw27() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "27.) ";
	SaveForUndo();
	nDistortion = 27;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw27(CCmdUI* pCmdUI) 
{
	if (nDistortion == 27) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw28() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "28.) ";
	SaveForUndo();
	nDistortion = 28;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw28(CCmdUI* pCmdUI) 
{
	if (nDistortion == 28) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw29() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "29.) ";
	SaveForUndo();
	nDistortion = 29;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw29(CCmdUI* pCmdUI) 
{
	if (nDistortion == 29) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw30() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "30.) ";
	SaveForUndo();
	nDistortion = 30;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw30(CCmdUI* pCmdUI) 
{
	if (nDistortion == 30) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw31() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "31.) ";
	SaveForUndo();
	nDistortion = 31;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw31(CCmdUI* pCmdUI) 
{
	if (nDistortion == 31) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw32() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "32.) ";
	SaveForUndo();
	nDistortion = 32;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw32(CCmdUI* pCmdUI) 
{
	if (nDistortion == 32) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw33() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "33.) ";
	SaveForUndo();
	nDistortion = 33;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw33(CCmdUI* pCmdUI) 
{
	if (nDistortion == 33) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw34() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "34.) ";
	SaveForUndo();
	nDistortion = 34;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw34(CCmdUI* pCmdUI) 
{
	if (nDistortion == 34) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw35() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "35.) ";
	SaveForUndo();
	nDistortion = 35;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw35(CCmdUI* pCmdUI) 
{
	if (nDistortion == 35) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}


void CTierazonView::OnDraw36() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "36.) ";
	SaveForUndo();
	nDistortion = 36;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw36(CCmdUI* pCmdUI) 
{
	if (nDistortion == 36) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw37() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "37.) ";
	SaveForUndo();
	nDistortion = 37;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw37(CCmdUI* pCmdUI) 
{
	if (nDistortion == 37) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw38() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "38.) ";
	SaveForUndo();
	nDistortion = 38;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw38(CCmdUI* pCmdUI) 
{
	if (nDistortion == 38) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw39() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "39.) ";
	SaveForUndo();
	nDistortion = 39;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw39(CCmdUI* pCmdUI) 
{
	if (nDistortion == 39) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw40() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "40.) ";
	SaveForUndo();
	nDistortion = 40;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw40(CCmdUI* pCmdUI) 
{
	if (nDistortion == 40) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw41() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "41.) ";
	SaveForUndo();
	nDistortion = 41;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw41(CCmdUI* pCmdUI) 
{
	if (nDistortion == 41) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw42() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "42.) ";
	SaveForUndo();
	nDistortion = 42;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw42(CCmdUI* pCmdUI) 
{
	if (nDistortion == 42) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw43() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "43.) ";
	SaveForUndo();
	nDistortion = 43;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw43(CCmdUI* pCmdUI) 
{
	if (nDistortion == 43) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw44() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "44.) ";
	SaveForUndo();
	nDistortion = 44;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw44(CCmdUI* pCmdUI) 
{
	if (nDistortion == 44) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw45() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "45.) ";
	SaveForUndo();
	nDistortion = 45;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw45(CCmdUI* pCmdUI) 
{
	if (nDistortion == 45) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw46() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "46.) ";
	SaveForUndo();
	nDistortion = 46;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw46(CCmdUI* pCmdUI) 
{
	if (nDistortion == 46) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw47() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "47.) ";
	SaveForUndo();
	nDistortion = 47;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw47(CCmdUI* pCmdUI) 
{
	if (nDistortion == 47) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw48() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "48.) ";
	SaveForUndo();
	nDistortion = 48;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw48(CCmdUI* pCmdUI) 
{
	if (nDistortion == 48) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw49() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "49.) ";
	SaveForUndo();
	nDistortion = 49;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw49(CCmdUI* pCmdUI) 
{
	if (nDistortion == 49) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw50() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "50.) ";
	SaveForUndo();
	nDistortion = 50;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw50(CCmdUI* pCmdUI) 
{
	if (nDistortion == 50) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw51() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "51.) ";
	SaveForUndo();
	nDistortion = 51;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw51(CCmdUI* pCmdUI) 
{
	if (nDistortion == 51) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw52() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "52.) ";
	SaveForUndo();
	nDistortion = 52;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw52(CCmdUI* pCmdUI) 
{
	if (nDistortion == 52) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw53() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "53.) ";
	SaveForUndo();
	nDistortion = 53;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw53(CCmdUI* pCmdUI) 
{
	if (nDistortion == 53) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw54() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "54.) ";
	SaveForUndo();
	nDistortion = 54;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw54(CCmdUI* pCmdUI) 
{
	if (nDistortion == 54) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw55() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "55.) ";
	SaveForUndo();
	nDistortion = 55;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw55(CCmdUI* pCmdUI) 
{
	if (nDistortion == 55) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw56() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "56.) ";
	SaveForUndo();
	nDistortion = 56;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw56(CCmdUI* pCmdUI) 
{
	if (nDistortion == 56) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw57() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "57.) ";
	SaveForUndo();
	nDistortion = 57;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw57(CCmdUI* pCmdUI) 
{
	if (nDistortion == 57) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw58() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "58.) ";
	SaveForUndo();
	nDistortion = 58;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw58(CCmdUI* pCmdUI) 
{
	if (nDistortion == 58) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw59() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "59.) ";
	SaveForUndo();
	nDistortion = 59;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw59(CCmdUI* pCmdUI) 
{
	if (nDistortion == 59) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw60() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "60.) ";
	SaveForUndo();
	nDistortion = 60;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw60(CCmdUI* pCmdUI) 
{
	if (nDistortion == 60) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw61() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "61.) ";
	SaveForUndo();
	nDistortion = 61;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw61(CCmdUI* pCmdUI) 
{
	if (nDistortion == 61) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw62() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "62.) ";
	SaveForUndo();
	nDistortion = 62;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw62(CCmdUI* pCmdUI) 
{
	if (nDistortion == 62) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw63() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "63.) ";
	SaveForUndo();
	nDistortion = 63;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw63(CCmdUI* pCmdUI) 
{
	if (nDistortion == 63) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw64() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "64.) ";
	SaveForUndo();
	nDistortion = 64;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw64(CCmdUI* pCmdUI) 
{
	if (nDistortion == 64) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw65() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "65.) ";
	SaveForUndo();
	nDistortion = 65;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw65(CCmdUI* pCmdUI) 
{
	if (nDistortion == 65) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw66() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "66.) ";
	SaveForUndo();
	nDistortion = 66;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw66(CCmdUI* pCmdUI) 
{
	if (nDistortion == 66) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw67() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "67.) ";
	SaveForUndo();
	nDistortion = 67;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw67(CCmdUI* pCmdUI) 
{
	if (nDistortion == 67) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw68() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "68.) ";
	SaveForUndo();
	nDistortion = 68;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw68(CCmdUI* pCmdUI) 
{
	if (nDistortion == 68) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw69() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "69.) ";
	SaveForUndo();
	nDistortion = 69;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw69(CCmdUI* pCmdUI) 
{
	if (nDistortion == 69) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw70() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "70.) ";
	SaveForUndo();
	nDistortion = 70;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw70(CCmdUI* pCmdUI) 
{
	if (nDistortion == 70) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw71() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "71.) ";
	SaveForUndo();
	nDistortion = 71;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw71(CCmdUI* pCmdUI) 
{
	if (nDistortion == 71) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw72() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "72.) ";
	SaveForUndo();
	nDistortion = 72;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw72(CCmdUI* pCmdUI) 
{
	if (nDistortion == 72) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw73() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "73.) ";
	SaveForUndo();
	nDistortion = 73;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw73(CCmdUI* pCmdUI) 
{
	if (nDistortion == 73) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw74() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "74.) ";
	SaveForUndo();
	nDistortion = 74;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw74(CCmdUI* pCmdUI) 
{
	if (nDistortion == 74) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw75() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "75.) ";
	SaveForUndo();
	nDistortion = 75;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw75(CCmdUI* pCmdUI) 
{
	if (nDistortion == 75) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw76() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "76.) ";
	SaveForUndo();
	nDistortion = 76;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw76(CCmdUI* pCmdUI) 
{
	if (nDistortion == 76) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw77() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "77.) ";
	SaveForUndo();
	nDistortion = 77;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw77(CCmdUI* pCmdUI) 
{
	if (nDistortion == 77) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw78() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "78.) ";
	SaveForUndo();
	nDistortion = 78;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw78(CCmdUI* pCmdUI) 
{
	if (nDistortion == 78) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw79() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "79.) ";
	SaveForUndo();
	nDistortion = 79;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw79(CCmdUI* pCmdUI) 
{
	if (nDistortion == 79) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw80() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "80.) ";
	SaveForUndo();
	nDistortion = 80;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw80(CCmdUI* pCmdUI) 
{
	if (nDistortion == 80) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw81() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "81.) ";
	SaveForUndo();
	nDistortion = 81;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw81(CCmdUI* pCmdUI) 
{
	if (nDistortion == 81) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw82() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "82.) ";
	SaveForUndo();
	nDistortion = 82;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw82(CCmdUI* pCmdUI) 
{
	if (nDistortion == 82) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw83() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "83.) ";
	SaveForUndo();
	nDistortion = 83;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw83(CCmdUI* pCmdUI) 
{
	if (nDistortion == 83) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw84() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "84.) ";
	SaveForUndo();
	nDistortion = 84;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw84(CCmdUI* pCmdUI) 
{
	if (nDistortion == 84) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw85() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "85.) ";
	SaveForUndo();
	nDistortion = 85;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw85(CCmdUI* pCmdUI) 
{
	if (nDistortion == 85) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw86() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "86.) ";
	SaveForUndo();
	nDistortion = 86;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw86(CCmdUI* pCmdUI) 
{
	if (nDistortion == 86) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw87() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "87.) ";
	SaveForUndo();
	nDistortion = 87;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw87(CCmdUI* pCmdUI) 
{
	if (nDistortion == 87) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw88() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "88.) ";
	SaveForUndo();
	nDistortion = 88;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw88(CCmdUI* pCmdUI) 
{
	if (nDistortion == 88) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw89() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "89.) ";
	SaveForUndo();
	nDistortion = 89;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw89(CCmdUI* pCmdUI) 
{
	if (nDistortion == 89) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw90() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "90.) ";
	SaveForUndo();
	nDistortion = 90;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw90(CCmdUI* pCmdUI) 
{
	if (nDistortion == 90) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw91() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "91.) ";
	SaveForUndo();
	nDistortion = 91;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw91(CCmdUI* pCmdUI) 
{
	if (nDistortion == 91) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw92() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "92.) ";
	SaveForUndo();
	nDistortion = 92;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw92(CCmdUI* pCmdUI) 
{
	if (nDistortion == 92) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw93() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "93.) ";
	SaveForUndo();
	nDistortion = 93;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw93(CCmdUI* pCmdUI) 
{
	if (nDistortion == 93) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw94() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "94.) ";
	SaveForUndo();
	nDistortion = 94;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw94(CCmdUI* pCmdUI) 
{
	if (nDistortion == 94) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw95() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "95.) ";
	SaveForUndo();
	nDistortion = 95;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw95(CCmdUI* pCmdUI) 
{
	if (nDistortion == 95) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw96() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "96.) ";
	SaveForUndo();
	nDistortion = 96;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw96(CCmdUI* pCmdUI) 
{
	if (nDistortion == 96) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw97() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "97.) ";
	SaveForUndo();
	nDistortion = 97;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw97(CCmdUI* pCmdUI) 
{
	if (nDistortion == 97) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw98() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "98.) ";
	SaveForUndo();
	nDistortion = 98;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw98(CCmdUI* pCmdUI) 
{
	if (nDistortion == 98) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw99() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "99.) ";
	SaveForUndo();
	nDistortion = 99;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw99(CCmdUI* pCmdUI) 
{
	if (nDistortion == 99) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw100() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "100.) ";
	SaveForUndo();
	nDistortion = 100;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw100(CCmdUI* pCmdUI) 
{
	if (nDistortion == 100) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw102() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "102.) magnet1 ";
	SaveForUndo();
	nDistortion = 102;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw102(CCmdUI* pCmdUI) 
{
	if (nDistortion == 102) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw103() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "103.) magnet2 ";
	SaveForUndo();
	nDistortion = 103;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw103(CCmdUI* pCmdUI) 
{
	if (nDistortion == 103) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw104() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "104.) teddy bear ";
	SaveForUndo();
	nDistortion = 104;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw104(CCmdUI* pCmdUI) 
{
	if (nDistortion == 104) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw105() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "105.) ";
	SaveForUndo();
	nDistortion = 105;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw105(CCmdUI* pCmdUI) 
{
	if (nDistortion == 105) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw106() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "106.) ";
	SaveForUndo();
	nDistortion = 106;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw106(CCmdUI* pCmdUI) 
{
	if (nDistortion == 106) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw107() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "107.) ";
	SaveForUndo();
	nDistortion = 107;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw107(CCmdUI* pCmdUI) 
{
	if (nDistortion == 107) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw108() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "108.) ";
	SaveForUndo();
	nDistortion = 108;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw108(CCmdUI* pCmdUI) 
{
	if (nDistortion == 108) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw109() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "109.) ";
	SaveForUndo();
	nDistortion = 109;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw109(CCmdUI* pCmdUI) 
{
	if (nDistortion == 109) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw110() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "110.) ";
	SaveForUndo();
	nDistortion = 110;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw110(CCmdUI* pCmdUI) 
{
	if (nDistortion == 110) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw111() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "111.) ";
	SaveForUndo();
	nDistortion = 111;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw111(CCmdUI* pCmdUI) 
{
	if (nDistortion == 111) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw112() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "112.) ";
	SaveForUndo();
	nDistortion = 112;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw112(CCmdUI* pCmdUI) 
{
	if (nDistortion == 112) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw113() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "113.) ";
	SaveForUndo();
	nDistortion = 113;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw113(CCmdUI* pCmdUI) 
{
	if (nDistortion == 113) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw114() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "114.) ";
	SaveForUndo();
	nDistortion = 114;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw114(CCmdUI* pCmdUI) 
{
	if (nDistortion == 114) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw115() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "115.) ";
	SaveForUndo();
	nDistortion = 115;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw115(CCmdUI* pCmdUI) 
{
	if (nDistortion == 115) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw116() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "116.) ";
	SaveForUndo();
	nDistortion = 116;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw116(CCmdUI* pCmdUI) 
{
	if (nDistortion == 116) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw117() 
{
	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

  ActiveTitle = "117.) ";
	SaveForUndo();
	nDistortion = 117;

  GoDoFractal();
}

void CTierazonView::OnUpdateDraw117(CCmdUI* pCmdUI) 
{
	if (nDistortion == 117) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

///////////////////////////////////////////////////

void CTierazonView::OnDimensionVariant() 
{
	bDimensionVariant ^= 1;
	bDraw = TRUE;
	bLaunch = FALSE;
	bInitialized = FALSE;
}

void CTierazonView::OnUpdateDimensionVariant(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bDimensionVariant);
	if (bMFilter)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTierazonView::OnDrawInsideout() 
{
	bInvertFractal ^= 1;	
	//GoDoFractal();
	bDraw = TRUE;
	bLaunch = FALSE;
	bInitialized = FALSE;
}

void CTierazonView::OnUpdateDrawInsideout(CCmdUI* pCmdUI) 
{
	if (bInvertFractal == TRUE)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

