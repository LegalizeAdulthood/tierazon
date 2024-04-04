// FDimension.cpp

#include "stdafx.h"
#include "Tierazon.h"

#include "TierazonDoc.h"
#include "TierazonView.h"
#include "mainfrm.h"
#include <math.h>
#include "external.h"

void CTierazonView::FDimension()
{
		//static nCount = 0;

		//if (i >= NMAX)
			//i = NMAX - 1;

		NMAX = i;

		// Set up to Calculate the Fractal Dimension
		//if (i <= NMAX)
		//{
		//	// Finish out the array with the last value
		//	for (i2 = i ; i2<NMAX ; i2++)
		//	{
		//		pXTemp[i2] = z.real();
		//		pYTemp[i2] = z.imag();
		//	}
		//}
		
		// Initialize the mean with zero
		x_mean = 0;
		y_mean = 0;

		// Initialize the range	with the first value
		x_rmin = pXTemp[0];	// x range min
		x_rmax = pXTemp[0];	// x range max
		y_rmin = pYTemp[0];	// y range min
		y_rmax = pYTemp[0];	// y range max

		switch(nFilter)
		{
			case 27:			// Fractal Dimension
			case 33:
			case 35:
			case 37:
			case 38:
				if (i < 3)
				{
					rj = gj = bj = i = 0;
					NMAX = NMAX_Save;
					return;
				}

				//if (bQuickMode)
				//{
				//	iQuickAbort = NMAX;
				//	JMAX = NMAX = i;
				//}
				
				for (i2 = 0 ; i2<NMAX ; i2++)
				{
					// Get sum x and y
					x_mean += pXTemp[i2];											
					y_mean += pYTemp[i2];

					// Get min x
					if (pXTemp[i2] < x_rmin)
						x_rmin = pXTemp[i2];

					// Get max x
					if (pXTemp[i2] > x_rmax)
						x_rmax = pXTemp[i2];

					// Get min y
					if (pYTemp[i2] < y_rmin)
						y_rmin = pYTemp[i2];

					// Get max y
					if (pYTemp[i2] > y_rmax)
						y_rmax = pYTemp[i2];
				}

				//if (NMAX >= 128 && nCount++ < 5)
				//{			
				//	sprintf (cstr, "NMAX = %d, x_rmin=%f, x_rmax=%f, y_rmin=%f, y_rmax=%f",
				//		NMAX, x_rmin, x_rmax, y_rmin, y_rmax);
				//	AfxMessageBox(cstr);
				//}

				x_mean = x_mean / NMAX;
				y_mean = y_mean / NMAX;

				x_std = 0;
				y_std = 0;

				for (i2 = 0 ; i2<NMAX ; i2++)
				{
					x_std = x_std + (pXTemp[i2] - x_mean)*(pXTemp[i2] - x_mean); 
					y_std = y_std + (pYTemp[i2] - y_mean)*(pYTemp[i2] - y_mean); 
				}

				x_std = sqrt(x_std / (NMAX-1));		// Standard Deviation x
				y_std = sqrt(y_std / (NMAX-1));		// Standard Deviation y

				// Initialize complex variables
				cx_std = cmplx(x_std, 0);	// Complex Standard deviation	x
				cy_std = cmplx(y_std, 0);	// Complex Standard deviation	y

				cFDx = cmplx (1, 0);				// Complex Fractal Dimension x
				cFDy = cmplx (1, 0);				// Complex Fractal Dimension y

				cRng_x = cmplx (x_rmax - x_rmin, 0);	// Complex Range x
				cRng_y = cmplx (y_rmax - y_rmin, 0);	// Complex Range y

				cNMAX = cmplx (NMAX, 0); 
				
				//////////////////////////////////////////////////////////////
				// Fractal Dimension Equation ...
				// Ju = Upper Jaenisch coefficient 
				// Initialize Ju=1;
				// Iterate Ju = [log(R/S*N*J]/[log(1/N)] until abs(Ju+1)-Ju < .0001.
				// if ( 0  <= J <= .5,) D(j) = 1/(1-Ju)
				// if (.5  <=	J <= 1.0) D(j) = 1/Ju.
				///////////////////////////////////////////////////////////////

				//////////////////////////////////////////////////////////////
				// Real
				////////////////////////////////////////////////////////////				
				dm = 99;
				da = 0;
				nDIter_x = 1;
				denominator = log((double)(1.0/(double)NMAX));
				//while (fabs(da - dm) > .0001 && nDIter_x++ < NMAX_Save-2)
				//while (fabs(da - dm) > .0001 && nDIter_x++ < 10000)
				{
					// Calculate Fractal Dimension (real)
					da = dm;
					cFDx = (cRng_x/(cx_std*cNMAX*cFDx)).clog()/denominator;
					dm = cFDx.real();
					if (nDIter_x == 1)
						dFDx_0 = 2.0 - dm;
				}

				dFDx = cFDx.real();

				if (dFDx <= .5)
					dFDx = 1 / (1 - dFDx);
				else
					dFDx = 1 / dFDx;

				////////////////////////////////////////////////////////////				
				// Imaginary
				////////////////////////////////////////////////////////////				
				dm = 99;
				da = 0;
				nDIter_y = 1;
				denominator = log((double)(1.0/(double)NMAX));
				//while (fabs(da - dm) > .0001 && nDIter_y++ < NMAX_Save-2)
				//while (fabs(da - dm) > .0001 && nDIter_y++ < 10000)
				{
					// Calculate Fractal Dimension (real)
					da = dm;
					cFDy = (cRng_y/(cy_std*cNMAX*cFDy)).clog()/denominator;
					dm = cFDy.real();
					if (nDIter_y == 1)
						dFDy_0 = 2.0 - dm;
				}

				dFDy = cFDy.real();

				if (dFDy <= .5)
					dFDy = 1 / (1 - dFDy);
				else
					dFDy = 1 / dFDy;
				////////////////////////////////////////////////////////////				
				
				////////////////////////////////////////////////////////////
				// Apply Fractal Dimension to a color
				
				switch (nFDOption)
				{
//					case 0:
//						// Addition
//						jrw = (int) ((dFDx+dFDy) * 100 * dBay100);
//						break;
				
					case 1:
						// Fractal Dimension Real Initial (FD_0)
						jrw = (int) (dFDx_0 * 200.0 * dBay100);
						rj = gj = bj = (dFDx_0 * 200.0 * dBay100);
							
						break;
				
					case 2:
						// Fractal Dimension Imginary	Initial (FD_0)
						jrw = (int) (dFDy_0 * 200.0 * dBay100);
						rj = gj = bj = (dFDy_0 * 200.0 * dBay100);
						break;
				
					case 3:
						// (FD_0) Addition
						jrw = (int) ((dFDx_0+dFDy_0) * 200 * dBay100);
						rj = ((dFDx_0+dFDy_0) * 200 * dBay100);
						gj = ((dFDx_0) * 200 * dBay100);
						bj = ((dFDy_0) * 200 * dBay100);						

						break;

					case 4:	
						// (FD_0) Sum of magnitude
						jrw = (int) ((dFDx_0*dFDx_0+dFDy_0*dFDy_0) * 200 * dBay100);
						rj = ((dFDx_0*dFDx_0+dFDy_0*dFDy_0) * 200 * dBay100);
						gj = ((dFDx_0*dFDx_0) * 200 * dBay100);
						bj = ((dFDy_0*dFDy_0) * 200 * dBay100);
						
						break;

					case 5:
						// (FD_0) Multiplication
						jrw = (int) (dFDx_0 * dFDy_0 * 200 * dBay100);
						rj = (dFDx_0 * dFDy_0 * 200 * dBay100);
						gj = (dFDx_0 * 200 * dBay100);
						bj = (dFDx_0 * 200 * dBay100);
						
						break;
					
					case 6:
						// Fractal Dimension Real
						jrw = (int) (dFDx * 200.0 * dBay100);
						rj = gj = bj = (int) (dFDx * 200.0 * dBay100);
						break;
				
					case 7:
						// Fractal Dimension Imaginary
						jrw = (int) (dFDy * 200.0 * dBay100);
						rj  = gj = bj = (dFDy * 200.0 * dBay100);
						break;
				
					case 8:
						// FD Addition
						jrw = (int) ((dFDx+dFDy) * 200 * dBay100);
						rj = ((dFDx+dFDy) * 200 * dBay100);
						gj = ((dFDx) * 200 * dBay100);
						bj = ((dFDy) * 200 * dBay100);
						break;

					case 9:	
						// FD Sum of magnitude
						jrw = (int) ((dFDx*dFDx+dFDy*dFDy) * 200 * dBay100);
						rj = ((dFDx*dFDx+dFDy*dFDy) * 200 * dBay100);
						gj = ((dFDx*dFDx) * 200 * dBay100);
						bj = ((dFDy*dFDy) * 200 * dBay100);
						break;

					case 10:
						// FD Multiplication
						jrw = (int) (dFDx * dFDy * 200 * dBay100);
						rj = (dFDx * dFDy * 200 * dBay100);
						gj = (dFDx * 200 * dBay100);
						bj = (dFDx * 200 * dBay100);
						break;
									
					default:
						AfxMessageBox("FD Error");
						break;
				}				

				i += abs(jrw);

				NMAX = NMAX_Save;
				return;

				break;

			case 28:			// Standard deviation
			case 34:			// Strands Std
			case 36:
				if (i < 2)
				{
					rj = gj = bj = i = 0;
					NMAX = NMAX_Save;
					return;
				}

				for (i2 = 0 ; i2<i ; i2++)
				{
					// Get sum x and y
					x_mean += pXTemp[i2];											
					y_mean += pYTemp[i2];

					// Get min x
					if (pXTemp[i2] < x_rmin)
						x_rmin = pXTemp[i2];

					// Get max x
					if (pXTemp[i2] > x_rmax)
						x_rmax = pXTemp[i2];

					// Get min y
					if (pYTemp[i2] < y_rmin)
						y_rmin = pYTemp[i2];

					// Get max y
					if (pYTemp[i2] > y_rmax)
						y_rmax = pYTemp[i2];
				}

				if (i != 0)
				{
					x_mean = x_mean / (double)i;
					y_mean = y_mean / (double)i;
				}

				x_std = 0;
				y_std = 0;

				for (i2 = 0 ; i2<i ; i2++)
				{
					x_std = x_std + (pXTemp[i2] - x_mean)*(pXTemp[i2] - x_mean); 
					y_std = y_std + (pYTemp[i2] - y_mean)*(pYTemp[i2] - y_mean); 
				}
								
				if (i>1)
				{
					x_std = (x_std / i);
					y_std = (y_std / i);
				}
				else
				{
					x_std = 0;
					y_std = 0;
				}				

				if (x_std == 0 && y_std == 0)
				{
					jrw = 0;
					rj = gj = bj = 0;
				}
				else
				{
					jrw = (int) (log((x_std + y_std)/2) * 30 * dBay100); // 10
					//rj = (int) (log((x_std + y_std)/2) * 30 * dBay100); // 10
					rj = (log((x_std)) * 30 * dBay100); // 10
					gj = (log((y_std)) * 30 * dBay100); // 10
					bj = (log((x_std + y_std)/2) * 30 * dBay100); // 10
				}

				i += abs(jrw);
										
				NMAX = NMAX_Save;
				return;
		}
}