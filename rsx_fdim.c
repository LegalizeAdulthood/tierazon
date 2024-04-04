///////////////////////////////////////////////////////////////
// rsx_file.c
//
// By: stephen c. ferguson
// http://home1.gte.net/itriazon/
// email: itriazon@gte.net
//
/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <math.h>
#include "rsx_file.h"

void FDimension()
{

	maxit_save = maxit;
	if (bDimensionVariant)
		i = maxit = n_color - 2;
	else
		i = maxit = n_color;	

	// Set up to Calculate the Fractal Dimension

	// Initialize the mean with zero
	x_mean = 0;
	y_mean = 0;

	// Initialize the range	with the first value
	x_rmin = pXTemp[0];	// x range min
	x_rmax = pXTemp[0];	// x range max
	y_rmin = pYTemp[0];	// y range min
	y_rmax = pYTemp[0];	// y range max

	switch(filter)
	{
		case 27:			// Fractal Dimension
		case 33:
		case 35:
		case 37:
		case 38:
			if (i < 3)
			{
				rj = gj = bj = i = 0;
				maxit = maxit_save;
				return;
			}
			
			for (i2 = 0 ; i2<maxit ; i2++)
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

			x_mean = x_mean / maxit;
			y_mean = y_mean / maxit;

			x_std = 0;
			y_std = 0;

			for (i2 = 0 ; i2<maxit ; i2++)
			{
				x_std = x_std + (pXTemp[i2] - x_mean)*(pXTemp[i2] - x_mean); 
				y_std = y_std + (pYTemp[i2] - y_mean)*(pYTemp[i2] - y_mean); 
			}

			x_std = sqrt(x_std / (maxit-1));		// Standard Deviation x
			y_std = sqrt(y_std / (maxit-1));		// Standard Deviation y

			// Initialize complex variables
			//cx_std = cmplx(x_std, 0);	// Complex Standard deviation	x
			//cy_std = cmplx(y_std, 0);	// Complex Standard deviation	y

			__real__ cx_std = x_std;
			__imag__ cx_std = 0;

			__real__ cy_std = y_std;
			__imag__ cy_std = 0;

			//cFDx = cmplx (1, 0);				// Complex Fractal Dimension x
			//cFDy = cmplx (1, 0);				// Complex Fractal Dimension y

			__real__ cFDx = 1;
			__imag__ cFDx = 0;

			__real__ cFDy = 1;
			__imag__ cFDy = 0;


			//cRng_x = cmplx (x_rmax - x_rmin, 0);	// Complex Range x
			//cRng_y = cmplx (y_rmax - y_rmin, 0);	// Complex Range y

			__real__ cRng_x = x_rmax - x_rmin;
			__imag__ cRng_x = 0;

			__real__ cRng_y = y_rmax - y_rmin;
			__imag__ cRng_y = 0;

			//cNMAX = cmplx (maxit, 0); 
			
			__real__ cNMAX = maxit; 
			__imag__ cNMAX = 0; 
			
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
			denominator = log((double)(1.0/(double)maxit));
			//while (fabs(da - dm) > .0001 && nDIter_x++ < maxit_Save-2)
			//while (fabs(da - dm) > .0001 && nDIter_x++ < 10000)
			{
				// Calculate Fractal Dimension (real)
				da = dm;
				
				//cFDx = (cRng_x/(cx_std*cNMAX*cFDx)).clog()/denominator;

				t = cRng_x/(cx_std*cNMAX*cFDx);
				t1 = clog_t();
				cFDx = t1/denominator;				
				
				//dm = cFDx.real();

				dm = __real__ cFDx;

				if (nDIter_x == 1)
					dFDx_0 = 2.0 - dm;
			}

			//dFDx = cFDx.real();

			dFDx = __real__ cFDx;

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
			denominator = log((double)(1.0/(double)maxit));
			//while (fabs(da - dm) > .0001 && nDIter_y++ < maxit_Save-2)
			//while (fabs(da - dm) > .0001 && nDIter_y++ < 10000)
			{
				// Calculate Fractal Dimension (real)
				da = dm;

				//cFDy = (cRng_y/(cy_std*cNMAX*cFDy)).clog()/denominator;

				t = cRng_y/(cy_std*cNMAX*cFDy);
				t1 = clog_t();
				cFDy = t1/denominator;												
				
				//dm = cFDy.real();

				dm = __real__ cFDy;

				if (nDIter_y == 1)
					dFDy_0 = 2.0 - dm;
			}

			//dFDy = cFDy.real();

			dFDy = __real__ cFDy;

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
	//						jrw = (int) ((dFDx+dFDy) * 100 * dFactor);
	//						break;
			
				case 1:
					// Fractal Dimension Real Initial (FD_0)
					rj = gj = bj = (dFDx_0 * 200.0 * dFactor);
						
					break;
			
				case 2:
					// Fractal Dimension Imginary	Initial (FD_0)
					rj = gj = bj = (dFDy_0 * 200.0 * dFactor);
					break;
			
				case 3:
					// (FD_0) Addition
					
					rj = ((dFDx_0+dFDy_0) * 200 * dFactor);
					gj = ((dFDx_0) * 200 * dFactor);
					bj = ((dFDy_0) * 200 * dFactor);						

					break;

				case 4:	

					// (FD_0) Sum of magnitude
					rj = ((dFDx_0*dFDx_0+dFDy_0*dFDy_0) * 200 * dFactor);
					gj = ((dFDx_0*dFDx_0) * 200 * dFactor);
					bj = ((dFDy_0*dFDy_0) * 200 * dFactor);
					
					break;

				case 5:
					// (FD_0) Multiplication
					rj = (dFDx_0 * dFDy_0 * 200 * dFactor);
					gj = (dFDx_0 * 200 * dFactor);
					bj = (dFDx_0 * 200 * dFactor);
					
					break;
				
				case 6:
					// Fractal Dimension Real
					rj = gj = bj = (int) (dFDx * 200.0 * dFactor);
					break;
			
				case 7:
					// Fractal Dimension Imaginary
					rj  = gj = bj = (dFDy * 200.0 * dFactor);
					break;
			
				case 8:
					// FD Addition

					//wsprintf (cstr, "step 1");
					//MessageBox(NULL, cstr, "Debug", MB_OK);					

					rj = ((dFDx+dFDy) * 200 * dFactor);
					gj = ((dFDx) * 200 * dFactor);
					bj = ((dFDy) * 200 * dFactor);
					break;

				case 9:	
					// FD Sum of magnitude
					rj = ((dFDx*dFDx+dFDy*dFDy) * 200 * dFactor);
					gj = ((dFDx*dFDx) * 200 * dFactor);
					bj = ((dFDy*dFDy) * 200 * dFactor);
					break;

				case 10:
					// FD Multiplication
					rj = (dFDx * dFDy * 200 * dFactor);
					gj = (dFDx * 200 * dFactor);
					bj = (dFDx * 200 * dFactor);
					break;
								
				default:
					AfxMessageBox("FD Error");
					break;
			}				

			maxit = maxit_save;
			return;

			break;

		case 28:			// Standard deviation
		case 34:			// Strands Std
		case 36:
			if (i < 2)
			{
				rj = gj = bj = i = 0;
				maxit = maxit_save;
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
				rj = (log((x_std)) * 30 * dFactor); // 10
				gj = (log((y_std)) * 30 * dFactor); // 10
				bj = (log((x_std + y_std)/2) * 30 * dFactor); // 10
			}
									
			maxit = maxit_save;
			return;
	}
}
