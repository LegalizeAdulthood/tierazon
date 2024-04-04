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

	__real__ z_mean = 0;
	__imag__ z_mean = 0;

	// Initialize the range	with the first value
	x_rmin = pXTemp[0];	// x range min
	x_rmax = pXTemp[0];	// x range max
	y_rmin = pYTemp[0];	// y range min
	y_rmax = pYTemp[0];	// y range max

	__real__ z_rmin = x_rmin;
	__imag__ z_rmin = y_rmin;

	__real__ z_rmax = x_rmax;
	__imag__ z_rmax = y_rmax;

	switch(filter)
	{
		case 27:			// Fractal Dimension
		case 33:
		case 35:
		case 37:
		case 38:
			if (i < 1)
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

			__real__ cx_std = x_std;
			__imag__ cx_std = 0;

			__real__ cy_std = y_std;
			__imag__ cy_std = 0;

			__real__ cRng_x = x_rmax - x_rmin;
			__imag__ cRng_x = 0;

			__real__ cRng_y = y_rmax - y_rmin;
			__imag__ cRng_y = 0;
			
			//////////////////////////////////////////////////////////////
			// Fractal Dimension Equation ...
			// Ju = Upper Jaenisch coefficient 
			// Initialize Ju=1;
			// Iterate Ju = [log(R/S*N*J]/[log(1/N)] until abs(Ju+1)-Ju < .0001.
			// if ( 0  <= J <= .5,) D(j) = 1/(1-Ju)
			// if (.5  <=	J <= 1.0) D(j) = 1/Ju.
			///////////////////////////////////////////////////////////////
			//	
			//	steve's simple dimension = [log(R/S*N]/[log(1/N)];
			//	R = range
			//	S = standard deviation
			//	N = number of samples

			//////////////////////////////////////////////////////////////
			// Real
			////////////////////////////////////////////////////////////				
			denominator = log((double)(1.0/(double)maxit));

			// Calculate Fractal Dimension (real)
			t = cRng_x/(cx_std*maxit);
			t1 = clog_t();
			cFDx = t1/denominator;							
			dFDx		= __real__ cFDx;

			////////////////////////////////////////////////////////////				
			// Imaginary
			////////////////////////////////////////////////////////////				

			// Calculate Fractal Dimension (imag)

			t = cRng_y/(cy_std*maxit);
			t1 = clog_t();
			cFDy = t1/denominator;												
			
			dFDy = __real__ cFDy;
			
			////////////////////////////////////////////////////////////
			// Apply Fractal Dimension to a color
			
			switch (nFDOption)
			{
	//					case 0:
	//						// Addition
	//						jrw = (int) ((dFDx+dFDy) * 100 * dFactor);
	//						break;
			
				case 1:
					rj = dFDx * 100.0 * dFactor;
					gj = dFDy * 100.0 * dFactor;
					bj = rj * gj;
					xsav = dFDx;
					ysav = dFDy;
					break;
			
				case 2:
					rj = dFDx * 500.0 * dFactor;
					gj = dFDy * 500.0 * dFactor;
					bj = fabs(rj - gj);
					xsav = dFDx;
					ysav = dFDy;
					break;
			
				case 3:
					rj = dFDx * 500.0 * dFactor;
					gj = dFDy * 500.0 * dFactor;
					bj = (rj + gj)/2;
					xsav = dFDx;
					ysav = dFDy;
					break;

				case 4:						
					rj = fabs(__real__ t) * 500.0 * dFactor;
					gj = fabs(__imag__ t) * 500.0 * dFactor;
					bj = (rj + gj)/2;
					break;

				case 5:					
					rj = fabs(__real__ t) * 500.0 * dFactor;
					gj = fabs(__imag__ t) * 500.0 * dFactor;
					bj = fabs(rj - gj)*2;
					break;
				
				case 6:
					// Fractal Dimension Real
					rj = gj = bj = (int) (dFDx * 400.0 * dFactor);
					break;
			
				case 7:
					// Fractal Dimension Imaginary
					rj  = gj = bj = (dFDy * 400.0 * dFactor);
					break;
			
				case 8:
					// FD Addition

					//wsprintf (cstr, "step 1");
					//MessageBox(NULL, cstr, "Debug", MB_OK);					

					rj = ((dFDx+dFDy)/2 * 400 * dFactor);
					gj = ((dFDx) * 400 * dFactor);
					bj = ((dFDy) * 400 * dFactor);
					break;

				case 9:	
					// FD Sum of magnitude
					rj = ((dFDx*dFDx+dFDy*dFDy) * 400 * dFactor);
					gj = ((dFDx*dFDx) * 400 * dFactor);
					bj = ((dFDy*dFDy) * 400 * dFactor);

					break;

				case 10:
					// FD Multiplication
					rj = (dFDx * dFDy * 400 * dFactor);
					gj = (dFDx * 400 * dFactor);
					bj = (dFDx * 400 * dFactor);
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
