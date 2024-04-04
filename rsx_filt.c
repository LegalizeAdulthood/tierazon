////////////////////////////////////////////////////////////////
// rsx_filt.c
////////////////////////////////////////////////////////////////
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

int CALLBACK _filter(double zx, double zy, int _ncolor)
{
	n_color = _ncolor;
	__real__ z = zx;
	__imag__ z = zy;
	Do_Filter();
	return n_color;
}

//////////////////////////////////////////////////////
// Filters
//////////////////////////////////////////////////////

void Do_Filter()
{
	switch (filter)
	{
		case 1:  // Stalks I			
  		//wsprintf (cstr, "step 1");
			//MessageBox(NULL, cstr, "Debug", MB_OK);

			d_real = fabs(__real__ z/__imag__ z);
			if (d_real < dStrands)
			{
				//if (xtot == 0)
					//xtot = 1;
  			//wsprintf (cstr, "step 1");
				//MessageBox(NULL, cstr, "Debug", MB_OK);
				xtot += 30*pow((1-d_real/dStrands),n_color);
				xsav = __real__ z;
			}

			d_imag = fabs(__imag__ z/__real__ z);
			if (d_imag < dStrands)
			{
				//if (ytot == 0)
					//ytot = 1;
  			//wsprintf (cstr, "step 1");
				//MessageBox(NULL, cstr, "Debug", MB_OK);
				ytot += 30*pow((1-d_imag/dStrands),n_color);
				ysav = __imag__ z;
			}
				     
			break;

		case 2:  // Bubbles I
		case 8:  // Bubbles II
			temp = sum_sqrs_z();
			if (filter == 2)
			{
				if (temp < dStrands)
				{
					ztot += 5*pow((1-temp/dStrands),n_color);
					xsav = ysav = temp;
				}
			}
			else
			{
				if (temp < dStrands)
				{
					ztot += 10*pow((1-temp/dStrands),n_color);
					xsav = ysav = temp;
				}
			}
				
			d_real = fabs(__real__ z)+fabs(__imag__ z);
			if (d_real < dStrands)
			{
				xtot += 2*(1-d_real/dStrands);
				xsav = d_real;
			}

			d_imag = fabs(__imag__ z)+fabs(__real__ z);
			if (d_imag < dStrands)
			{
				ytot += 2*(1-d_imag/dStrands);
				ysav = d_imag;
			}

     break;

		case 3:
			if (sum_sqrs_z() >= maxsize)  // 1e6
				return;

  		xtot = xtot + fabs(__real__ z);
		  xavg = xtot/n_color;
		  xdif = xavg - xsav;
		  xsav = xavg;
		  if (fabs(xdif) < dStrands)
			  d_color_x = fabs(xdif);

		  ytot = ytot + fabs(__imag__ z);
		  yavg = ytot/n_color;
		  ydif = yavg - ysav;
		  ysav = yavg;
		  if (fabs(ydif) < dStrands)
        d_color_y = fabs(ydif);
      break;

    case 4:
      if (sum_sqrs_z() >= maxsize)	// 1e6
        return;

      ztot = ztot + sum_sqrs_z();
      zavg = ztot/n_color;
      zdif = zavg - zsav;
      zsav = zavg;
      if (fabs(zdif) < dStrands)
			{
        d_color_z = fabs(zdif);
			  xsav = __real__ z;
			  ysav = __imag__ z;
			}
      break;

	  case 5:  // log(log(...))
		  xsav = __real__ z;
		  ysav = __imag__ z;		 
      break;
				
    case 6:  // Bubbles I
		 temp = fabs(__real__ z*__imag__ z) *2;
      if (temp < dStrands)
     {
       ztot += 30*pow((1 - temp/dStrands),n_color);
			 xsav = __real__ z;
			 ysav = __imag__ z;
			 n_color_z = n_color;
     }
     break;
		
		case 7:  // dual bubbles
			temp = fabs(__real__ z*__imag__ z) *2;
      if (temp < dStrands)
			{
				ztot += 30*pow((1 - temp/dStrands),n_color);
				xsav = __real__ z;
				ysav = __imag__ z;
	  		n_color_z = n_color;
			}

      if (temp < dStrands/DUAL_BFACTOR)
			{
				ztot += 30*pow((1 - temp/dStrands),n_color);
				xsav = __real__ z;
				ysav = __imag__ z;
			}

			break;

		case 9:  // Stalks II
			d_real = fabs(__real__ z/__imag__ z);
			if (d_real < dStrands)
			{
				xtot += 100*pow((1-d_real/dStrands),n_color);
				xsav = __real__ z;
			}

			d_imag = fabs(__imag__ z/__real__ z);
			if (d_imag < dStrands)
			{
				ytot += 100*pow((1-d_imag/dStrands),n_color);
				ysav = __imag__ z;
			}
     break;

   case 10:  // Rings I
     ssq1 = sqrt(sum_sqrs_z());
     // (ssq1 < dStrands_HI && ssq1 > dStrands_LO && zsav < ssq1)
     if (ssq1 < dStrands_HI && ssq1 > dStrands_LO)
     {
       zsav = ssq1;
       n_color_z = n_color;
			 xsav = __real__ z;
			 ysav = __imag__ z;		 
			 n_color = maxit;
     }
     break;

   case 11:  // Rings II
   case 12:  // Rings III
     ssq1 = 1/sum_sqrs_z();
     //if (ssq1 < dStrands_HI && ssq1 > dStrands_LO && zsav < ssq1)
     if (ssq1 < dStrands_HI && ssq1 > dStrands_LO)
     {
       zsav = ssq1;
       n_color_z = n_color;
			 xsav = __real__ z;
			 ysav = __imag__ z;		 
			 n_color = maxit;
     }
     break;
		
    case 13: // Hi Lo I
			dzx = fabs(__real__ z);
			dzy = fabs(__imag__ z);

			if (dzx < dStrands_HI_cx &&
         dzx > dStrands_LO_cx)
			{
				xtot += (dStrands_HI_cx - dzx)/dStrands_cxd;
				xsav = __real__ z;
			}

			if (dzy < dStrands_HI_cy &&
         dzy > dStrands_LO_cy)
			{
				ytot += (dStrands_LO_cy - dzy)/dStrands_cyd;
				ysav = __imag__ z;		 
			}

			break;

		case 14:  // testing
			ssq1 = (sqrt((sum_sqrs_z())));
			if (ssq1 < dStrands_HI && ssq1 > dStrands_LO && zsav == 0)
			{
				zsav = ssq1;
				n_color_z = n_color;
				xsav = __real__ z;
				ysav = __imag__ z;		 
				n_color = maxit;
			}
			break;

    case 17:
     if ((fabs(__real__ z)) < dStrands && xtot == 0)
     {
        xtot = 1;
        xsav += atan(fabs(__real__ z / __imag__ z))*
                atan(fabs(__imag__ z / __real__ z));
        n_color_x = n_color;
     }

     if ((fabs(__imag__ z)) < dStrands && ytot == 0)
     {
        ytot = 1;
        ysav += atan(fabs(__real__ z / __imag__ z))*
                atan(fabs(__imag__ z / __real__ z));
        n_color_y = n_color;
     }

     break;

   case 18:
     if (sum_sqrs_z() < dStrands)
     {
       zsav += atan(fabs(__real__ z / __imag__ z))*
                atan(fabs(__imag__ z / __real__ z))*dFactor_2;
			 xsav = __real__ z;
			 ysav = __imag__ z;		 
			 n_color_z = n_color;
     }
     break;

   case 19:  //
   	 ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands)
     {
       ztot += atan(fabs(__real__ z / __imag__ z))*
               atan(fabs(__imag__ z / __real__ z))
							 *(1+(1-(ssq1/dStrands)));
			 xsav = __real__ z;
			 ysav = __imag__ z;		 
			 n_color_z = n_color;
     }

     break;

   case 20:
   	 ssq1 = sqrt(sum_sqrs_z());
     if (ssq1 < dStrands && ssq1 > zsav)
     {
       ztot += atan(fabs(__real__ z / __imag__ z))*
                atan(fabs(__imag__ z / __real__ z))*4*dFactor_2;
       zsav = ssq1;
       n_color_z = n_color;
			 xsav = __real__ z;
			 ysav = __imag__ z;		 
     }
     break;

   case 21:  // Flowers I
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     //if (ssq1 < dStrands)
     {
       zsav = ssq1;
       ztot += atan(fabs(__real__ z / __imag__ z))*
               atan(fabs(__imag__ z / __real__ z))*10;

       dif_test = (ztot+(dStrands - zsav)*10*dFactor_2);  // 1300
       if (dif_test < m_lower || dif_test > m_upper)
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
       }
			 else
			 {
	       n_color_z=n_color;
				 zsav = dif_test;
				 n_color = maxit;
			 }

			 xsav = __real__ z;
			 ysav = __imag__ z;		 

     }
     break;

   case 22:  // Flowers II
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     {
       zsav = ssq1;
       n_color_z = n_color;
       ztot += (atan(fabs(__real__ z / __imag__ z))-
               atan(fabs(__imag__ z / __real__ z)))*10;

       dif_test = ztot + (dStrands - zsav)*10*dFactor_2;
       if (dif_test < m_lower || dif_test > m_upper)
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
       }
			 else
			 {
	       n_color_z=n_color;
				 zsav = dif_test;
				 n_color = maxit;
			 }

			 xsav = __real__ z;
			 ysav = __imag__ z;		 

     }
     break;

   case 23:  // Flowers III
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     {
       zsav = ssq1;

       ztot += (atan(fabs(__real__ z / __imag__ z)))*10;

       //dt = __real__ z * __imag__ z;
       dif_test = ztot + (dStrands - zsav)*10*dFactor_2;
       if (dif_test < m_lower || dif_test > m_upper)
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
       }
			 else
			 {
	       n_color_z=n_color;
				 zsav = dif_test;
				 n_color = maxit;
			 }

			 xsav = __real__ z;
			 ysav = __imag__ z;		 

     }
     break;

   case 24:  // Flowers IV
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     {
       zsav = ssq1;
       n_color_z = n_color;

       ztot += (sin(__real__ z * __real__ z*10)-
               sin(__imag__ z * __imag__ z*10)*10);

       dif_test = ztot+(dStrands - zsav)*10*dFactor_2;  // 1300
       if (dif_test < m_lower || dif_test > m_upper)
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
       }
			 else
			 {
	       n_color_z=n_color;
				 zsav = dif_test;
				 n_color = maxit;
			 }

			 xsav = __real__ z;
			 ysav = __imag__ z;		 

     }
     break;

   case 25:  // Flowers V
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     {
       zsav = ssq1;
       n_color_z = n_color;
       ztot += (sin(__real__ z * __real__ z*10)*
               sin(__imag__ z * __imag__ z*10))*10;
       dt = __real__ z * __imag__ z;

			 dif_test = ztot + (dStrands - zsav)*1000*dFactor_2;
       if (dif_test < m_lower || dif_test > m_upper)  // 40
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
				 xsav = __real__ z;
				 ysav = __imag__ z;		 
       }
     }
     break;

   case 26:  // testing
   	 ssq1 = sqrt(sum_sqrs_z());
     if (ssq1 < dStrands && zsav == 0)
     {
       ztot += atan(fabs(__real__ z / __imag__ z))*
               atan(fabs(__imag__ z / __real__ z))*4*dFactor_2;
       zsav = ssq1;
       n_color_z = n_color;
			 xsav = __real__ z;
			 ysav = __imag__ z;		 
     }

     break;

	 case 27:  // fractal dimensions		 
	 case 28:  // standard deviations
		 pXTemp[n_color] = __real__ z*100;
		 pYTemp[n_color] = __imag__ z*100;	
		 xsav = __real__ z;
		 ysav = __imag__ z;		 
		 break;
		
	  case 29:  // Square Stalks & Bubbles			
	  case 30:
			temp = (fabs(__real__ z) + fabs(__imag__ z));
			if (temp < dStrands)
			{
				xtot = 10*(1-temp/dStrands);
				ytot = xtot;
				xsav = __real__ z;
				ysav = __imag__ z;
				n_color_z = n_color;
			}
 
		 break;
		
		case 31:
		case 32:
			if (fabs(__real__ z) < dStrands)
			{
				b = (1 - fabs(__real__ z)/dStrands)*dFactor_2;
				b = b*.3;
				xtot = xtot + b - xtot*b;
				n_color_x++;
			 xsav = __real__ z;
			}

			if (fabs(__imag__ z) < dStrands)
			{
				b = (1 - fabs(__imag__ z)/dStrands)*dFactor_2;
				b = b*.3;
				ytot = ytot + b - ytot*b;
				n_color_y++;
			 ysav = __imag__ z;		 
			}
		 
			break;

	 case 33:  // fractal dimensions of orbit traps			
	 case 34:  // stalks standard deviation
			if (fabs(__real__ z) < dStrands)
			{
				pXTemp[n_color] = (1 - fabs(__real__ z)/dStrands); // 100
				n_color_x++;
        xsav = __real__ z;
			}
			else
				pXTemp[n_color] = 1; ////////////
			
			if (fabs(__imag__ z) < dStrands)
			{
				pYTemp[n_color] = (1 - fabs(__imag__ z)/dStrands); // 100
				n_color_y++;
			  ysav = __imag__ z;		 
			}
			else
				pYTemp[n_color] = 1; /////////

		  break;		

	 case 35:  //  Hi/Lo stalks dimension
	 case 36:
		 ssq1 = fabs(__real__ z);
     if (ssq1 < dStrands_HI_cx && ssq1 > dStrands_LO_cx)
			{
				n_color_z++;				
				pXTemp[n_color] = 1 - (dStrands_HI_cx - ssq1)/(dStrands_HI_cx - dStrands_LO_cx)*100;
			  xsav = __real__ z;
			}
			else
			{
				pXTemp[n_color] = 1;
			}

		 ssq1 = fabs(__imag__ z);
     if (ssq1 < dStrands_HI_cy && ssq1 > dStrands_LO_cy)
			{
				n_color_z++;				
				pYTemp[n_color] = 1 - (dStrands_HI_cy - ssq1)/(dStrands_HI_cy - dStrands_LO_cy)*100;
			  ysav = __imag__ z;		 
			}
			else
			{
				pYTemp[n_color] = 1;
			}

			break;

	  case 37:
			if (fabs(__real__ z) < dStrands_HI_cx && 
					fabs(__real__ z) > dStrands_LO_cx)
			{
				n_color_z++;				
				pXTemp[n_color] = 1 - (dStrands_HI_cx - fabs(__real__ z))/(dStrands_cxd);
			  xsav = __real__ z;
			}			
			else
			{
				pXTemp[n_color] = 1;
			}

			if (fabs(__imag__ z) < dStrands_HI_cy &&
					fabs(__imag__ z) > dStrands_LO_cy)
			{
				n_color_z++;				
				pYTemp[n_color] = 1 - (dStrands_HI_cy - fabs(__imag__ z))/(dStrands_cyd);
			  ysav = __imag__ z;		 
			}
			else
			{
				pYTemp[n_color] = 1;
			}

		 break;

	  case 38:
			pXTemp[n_color] = atan(fabs(__real__ z/__imag__ z))*100;
			pYTemp[n_color] = atan(fabs(__imag__ z/__real__ z))*100;
	 	  xsav = __real__ z;
	  	ysav = __imag__ z;		 
 		
		 break;
		
	 case 39:	// xray stalks
		 if (fabs(__real__ z) < dStrands)
		 {
			 xsav = fabs(__real__ z);
			 temp = dStrands/xsav;
			 xtot += log(temp);	
		 }

		 if (fabs(__imag__ z) < dStrands)
		 {
			 ysav = fabs(__imag__ z);
			 temp = dStrands/ysav;
			 ytot += log(temp);	
		 }

		 //xsav = __real__ z;
		 //ysav = __imag__ z;
		 break;
			
		case 40:		// xray bubbles
		 if (sum_sqrs_z() < dStrands)
		 {
			 zsav = sum_sqrs_z();
			 //n_color_z++;
			
			 temp = log(2+dStrands/zsav);

			 if (n_color%2==0)
				xtot += temp;
			 else
				ytot += temp;
     
			 xsav = __real__ z;
			 ysav = __imag__ z;
		 }     
		 break;
		
		case 41:  // xray rings
			ssq1 = sqrt(sum_sqrs_z());
			if (ssq1 < dStrands_HI && ssq1 > dStrands_LO)
			{
	  		temp = log(2+dStrands_df/(fabs(limit-ssq1)));
				
				if (n_color%2==0)
					xtot += temp;
				else
					ytot += temp;
				
				xsav = fabs(limit-ssq1)*2;
				ysav = fabs(limit-ssq1)*2;		 
			}

			break;

		case 42:
			dzx = fabs(__real__ z);
			dzy = fabs(__imag__ z);

			if (dzx < dStrands_HI_cx &&
         dzx > dStrands_LO_cx)
			{
				xsav = fabs(limit_cxd-dzx);
	  		temp = log(10+limit_cxd/xsav);
				xtot += temp;
				xsav *= 2;
			}

			if (dzy < dStrands_HI_cy &&
         dzy > dStrands_LO_cy)
			{
				ysav = fabs(limit_cyd-dzy);
	  		temp = log(10+limit_cyd/ysav);
				ytot += temp;
				ysav *= 2;
			}

			break;

		case 43:
			if (fabs(__real__ z) < dStrands)
			{
				xsav = fabs(__real__ z);
				xtot += atan(fabs(__imag__ z/__real__ z))*
								atan(fabs(__real__ z/__imag__ z))*2;
			}

			if (fabs(__imag__ z) < dStrands)
			{
				ysav = fabs(__imag__ z);
				ytot += atan(fabs(__imag__ z/__real__ z))*
								atan(fabs(__real__ z/__imag__ z))*2;
			}

			break;

		case 44:
			if (  fabs(__real__ z) < dStrands
				 || fabs(__imag__ z) < dStrands)
			{
 				/*
				if (n_color >= m_upper)
				{
					wsprintf (cstr, "step 1");
					MessageBox(NULL, cstr, "Debug", MB_OK);
				}
				*/
				
				if (fabs(__real__ z) < dStrands)
					xtot += 100*(1 - fabs(__real__ z) /dStrands);

				if (fabs(__imag__ z) < dStrands)
					ytot += 100*(1 - fabs(__imag__ z) /dStrands);

				if (xtot > maxit*dFactor_2 || ytot > maxit*dFactor_2)
					n_color = maxit;
			
				xsav = __real__ z;
	  		ysav = __imag__ z;		 
			}

			break;

		case 45:
			if (  fabs(__real__ z) * fabs(__imag__ z) < dStrands)
			{
				ztot += 100*(1 - (fabs(__real__ z) * fabs(__imag__ z)/dStrands));
					
				if (ztot > maxit*dFactor_2)
					n_color = maxit;

				xsav = __real__ z;
	  		ysav = __imag__ z;		 
			}

			break;

		case 46:
			if (  sum_sqrs_z() < dStrands)
			{
				ztot += 30*(30*dFactor_2/(n_color))*(1 - (sum_sqrs_z()/dStrands));

				n_color_z = n_color;
				if (ztot > maxit*10)
					n_color = maxit;

				xsav = __real__ z;
	  		ysav = __imag__ z;		 
			}

			break;

		case 47:
			temp = sum_sqrs_z();
			if (temp < dStrands)
			{
				ztot += 10*dFactor_2*(100/(n_color))*
					(1 - (temp/dStrands));

				n_color_z = n_color;
				if (ztot > maxit*10)
					n_color = maxit;

				xsav = __real__ z;
	  		ysav = __imag__ z;		 
			}

			break;

	  case 48:
			ztot = sum_sqrs_z();
			if (ztot < dStrands)
			{
				pYTemp[n_color] = pXTemp[n_color] = (dStrands/ztot)*100;
				n_color_z = n_color;
			}
			else
			{
				pXTemp[n_color] = 0;
				pYTemp[n_color] = 0;
			}
	 		xsav = __real__ z;
	  	ysav = __imag__ z;		 

			break; 		

		case 49:
			ztot = sum_sqrs_z();
			if (ztot < dStrands)
			{
				pYTemp[n_color] = pXTemp[n_color] = log(dStrands*100/ztot)*100000;
				n_color_z = n_color;
			}
			else
			{
				pXTemp[n_color] = 0;
				pYTemp[n_color] = 0;
			}
	 		xsav = __real__ z;
	  	ysav = __imag__ z;		 

			break; 		

		case 50:
			d_real = fabs(__real__ z/__imag__ z);
			d_imag = fabs(__imag__ z/__real__ z);
			
			if (d_real <= dStrands)
			{
				xtot += (1-d_real/dStrands);
				//xsav = __real__ z;
				xsav = d_real;
			}

			if (d_imag < dStrands)
			{
				ytot += (1-d_imag/dStrands);
				//ysav = __imag__ z;		 
				ysav = d_imag;
			}

			break;

	 case 51:  // Stalks & Bubbles			
	 case 52:
     if (fabs(__real__ z) < dStrands
			 && n_color > m_lower && n_color < m_upper)
     {
       xsav = __real__ z;
       n_color_x = n_color;
			 //n_color_x++;
     }

     if (fabs(__imag__ z) < dStrands
			 && n_color > m_lower && n_color < m_upper)
     {
       ysav = __imag__ z;
       n_color_y = n_color;
			 //n_color_y++;
     }

     if (sum_sqrs_z() < dStrands
			 && n_color > m_lower && n_color < m_upper)
     {
       zsav = sum_sqrs_z();
       //n_color_z = n_color;
			 n_color_z++;
       ysav = __imag__ z;
       xsav = __real__ z;
     }     
		 break;
			
		default:  // last z values (gradients)
			// Case 15, 16, 17
	 	  xsav = __real__ z;
	  	ysav = __imag__ z;		 
			break;
 }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

RGB_IDATA CALLBACK _filter_complete()
{
	__real__ z = xsav;
	__imag__ z = ysav;

	Filter_Complete();

	if (fabs(xsav) < minsize)
	{
		if (xsav > 0)
			xsav = minsize;
		else
			xsav = -minsize;
	}

	if (fabs(ysav) < minsize)
	{
		if (ysav > 0)
			ysav = minsize;
		else
			ysav = -minsize;
	}

	if (fabs(xsav) > maxsize)
	{
		if (xsav > 0)
			xsav = maxsize;
		else
			xsav = -maxsize;
	}

	if (fabs(ysav) > maxsize)
	{
		if (ysav > 0)
			ysav = maxsize;
		else
			ysav = -maxsize;
	}

	switch (filter)
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

			FDimension();
			break;

		default:
			break;
	}

	if (size_x <= 640 && size_y <= 480 && nUsingBuffers)
	{
		pXSave[px+py*size_x] = xsav;
		pYSave[px+py*size_x] = ysav;
		
		/*
		if (px == 1 && py == 1)
		{
			sprintf(cstr, "step 1, xsav = %f, ysav=%f, i = %d, rj = %f, gj = %f",
				xsav, ysav, i, rj, gj);
			MessageBox(NULL, cstr, "bug", MB_OK);
		}
		*/
				
		rjData[px+py*size_x] = rj;
		gjData[px+py*size_x] = gj;
		bjData[px+py*size_x] = bj;
	}

	if (nColorMethod)	
		color_methods();
	
	//MessageBox(NULL, "step 5", "bug", MB_OK);

	rgbColor.i  = j;
	rgbColor.rj	= rj;
	rgbColor.gj	= gj;
	rgbColor.bj	= bj;

	return rgbColor;

}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void Filter_Complete()
{
	static int nCount = 0;
	
	j = rj = gj = bj = n_color;
  
	switch (filter)
  {
    case 1:
    case 9:
		case 13:
		case 39:
		case 40:
		case 41:
		case 42:
		case 43:

  	 //wsprintf (cstr, "step 3");
	   //MessageBox(NULL, cstr, "Debug", MB_OK);

			//return;

			if (xsav || ysav)
			{      
				xtot*=dFactor;
				ytot*=dFactor;
				d = sqrt(xtot*xtot + ytot*ytot);

				rj = d + xtot;
				gj = d + ytot;			
				bj = d;
			
			}
			else
				j = rj = gj = bj = 0;

      break;

    case 2:
		case 8:
      if (ztot)
      {
        rj = gj = bj = ztot*dFactor;
      }
			else
				j = 0;

			if (xtot || ytot)
			{      
				d = sqrt(xtot*xtot + ytot*ytot);
				gj = d + xtot*dFactor;
				bj = d + ytot*dFactor;
			}	

      break;

    case 3:
			if (d_color_x || d_color_y)
			{
				if (d_color_x)
					rj = xtot = (dStrands - d_color_x)*1000*dFactor;

				if (d_color_y)
					gj = ytot = (dStrands - d_color_y)*1000*dFactor;
				
				n_color = n_color + (xtot + ytot)/2;
				bj = n_color;
			}
			else
				j = 0;

      break;

    case 4:  // Moving average II
      if (d_color_z)
			{
        ztot = (dStrands - d_color_z)*1000*dFactor;

	      n_color = n_color + ztot;
			}
			else
				j = 0;

			rj = gj = bj = n_color;
      break;

	  case 5:
			if (n_color<maxit)
			{
        if (sum_sqrs_z() > 1)
          n_color = (n_color - log (log (sum_sqrs_z())) / log (2))*50*dFactor;
			}
			else
				j = 0;

			rj = gj = bj = n_color;
	    break;

    case 6:			
      rj = ztot*dFactor;
			gj = rj+xsav*10*dFactor+n_color_z;
			bj = rj+ysav*10*dFactor+n_color_z;

      break;

		case 7:
      rj = ztot*dFactor;
			gj = rj+xsav*10*dFactor+n_color_z;
			bj = rj+ysav*10*dFactor+n_color_z;


      break;

    case 10:   // Rings I
      //if (n_color_z > 2)
      if (n_color_z)
      {
        ztot = fabs(limit - zsav)*3000*dFactor;  // 500
        n_color = ztot;
				rj = gj = bj = n_color;
      }
      else
      {
        if (n_color < maxit)
        {
          j = n_color = 0;
          n_color_z = -1;
					rj = gj = bj = 0;
        }
      }
      break;

    case 11:   // Rings II
      //if (n_color_z > 2)
			if (n_color_z)
      {
        ztot = fabs(limit - zsav)*3000*dFactor;  // 500
        if (n_color_z%2==0)
          rj = bj = gj = n_color = ztot;
        else
          rj = bj = gj = n_color = ztot + OFFSET_COLOR;
      }
      else
      {
        if (n_color < maxit)
        {
          j = n_color = 0;
          n_color_z = -1;
					rj = gj = bj = 0;
        }
      }
      break;

    case 12:  // Rings III
      //if (n_color_z >= 1)
      if (n_color_z)
      {
        ztot = fabs(limit - zsav)*3000*dFactor;  // 500
        if (n_color_z%2==0)
				{
          rj = n_color = ztot;
				}
        else
				{			
          gj = n_color = ztot + OFFSET_COLOR;
				}
      }
      else
      {
        if (n_color < maxit)
        {
          j = n_color = 0;
          n_color_z = -1;
					rj = gj = bj = n_color;
        }
      }
			
			bj = rj + gj;

      break;

    case 14:   // Rings I
      if (n_color_z)
      {
        //ztot = (fabs(dStrands_HI - zsav))*50*dFactor;
				ztot = (((dStrands_HI - zsav)*.5)/(dStrands_HI- dStrands_LO))*500*dFactor;
        rj = ztot * xsav;
        gj = ztot * ysav;
				bj = (rj + gj)/2;
      }
      else
      {
        if (n_color < maxit)
        {
          j = n_color = 0;
          n_color_z = -1;
        }
				rj = gj = bj = n_color;
      }
      break;

    case 15:
      if (n_color >= maxit)
      {
        n_color = fabs(sin(__real__ z * __real__ z*100))*
                  fabs(sin(__imag__ z * __imag__ z*100))*
                  200*dFactor;
      }
      else
      {
        ssq1 = sum_sqrs_z();
        if (ssq1 <= 2)
          ssq1 = 2;
        n_color = (n_color - log (log (ssq1)) / log (2))*10*dFactor_2;
      }
			rj = gj = bj = n_color;
      break;

    case 16:
      if (n_color >= maxit)
      {
        n_color = fabs(sin(__real__ z * __real__ z*100))*
                  fabs(sin(__imag__ z * __imag__ z*100))*
                  200*dFactor;
				rj = gj = bj = n_color;
      }
      else
      {
        ztot = atan(fabs(__real__ z / __imag__ z))-
               atan(fabs(__imag__ z / __real__ z))*
               60*dFactor_2;

        if (n_color%2==0)
          rj = n_color = ztot;
        else
          gj = n_color = ztot + OFFSET_COLOR;

				bj = rj + gj + n_color;
      }
      break;

    case 17:
      if (n_color_x || n_color_y)
      {
        if (n_color_x)
          xtot = xsav*200*dFactor;

        if (n_color_y)
          ytot = ysav*200*dFactor;

        if (n_color < maxit)
          rj = n_color = sqrt(xtot*xtot+ytot*ytot);
				else
          gj = n_color = n_color + sqrt(xtot*xtot+ytot*ytot);

				bj = rj + gj + n_color;
      }
      else
      {
        if (n_color < maxit)
        {
          j = n_color = 0;
          n_color_z = -1;
        }
				rj = gj = bj = n_color;
      }
      
			break;

    case 18:
      n_color_z += zsav*3*dFactor;
			rj = gj = bj = n_color_z;
      break;

    case 19:
      if (n_color_z)
      {
        //if (n_color_z%2==0)
          //n_color = n_color_z*2 + ztot*2*dFactor;
        //else
          //n_color = n_color_z*2 + ztot*2*dFactor + OFFSET_COLOR;

        if (n_color_z%2==0)
				{
          rj = ztot*2*dFactor;
          gj = ztot*2*dFactor + OFFSET_COLOR;
				}
        else
				{
          rj = ztot*2*dFactor + OFFSET_COLOR;
          gj = ztot*2*dFactor;
				}

				bj = (rj + gj)/2;
      }
      else
      {
        if (n_color < maxit)
        {
          j = n_color = 0;
          n_color_z = -1;
        }
				rj = gj = bj = n_color;
      }
      break;

    case 20:
      if (n_color_z && n_color > 1)
      {
      	ztot += (dStrands - zsav)*1000*dFactor;
        if (n_color_z%2==0)
      	  rj = n_color = (n_color_z*2 + ztot)/2;
        else
      	  gj = n_color = (n_color_z*2 + ztot)/2 + OFFSET_COLOR;
				bj = rj + gj + n_color;
      }
      else
      {
        if (n_color < maxit)
        {
          j = n_color = 0;
          n_color_z = -1;
        }
				rj = gj = bj = n_color;
      }

      break;

    case 21:   // Flowers I
    case 22:   // Flowers II
    case 23:   // Flowers III
    case 24:   // Flowers IV
    case 25:   // Flowers V
    	if (n_color < maxit && n_color_z == 0)
      {
        j = n_color = 0;
        n_color_z = -1;  // sets the background to black
				rj = gj = bj = n_color;
      }

      if (n_color_z == 0)
      {
        if (n_color < maxit)
        {
          j = n_color = 0;
          n_color_z = -1;
        }
				rj = gj = bj = n_color;
      }

      if (n_color_z > 0)
      {
        //ztot += n_color_z
          //+ (1 - zsav/dStrands)*1000*dFactor;  // 1300

				if (n_color_z%2 == 0)
					ztot = dif_test*2*dFactor;
				else
					ztot = dif_test*2*dFactor + OFFSET_COLOR;

        rj = ztot;
				gj = ztot;
				bj = ztot;

      }
      break;

    case 26:  // testing
      if (n_color_z && n_color > 1)
      {
        if (n_color_z%2==0)
          rj = n_color = n_color_z + ztot*10*dFactor;
        else
          gj = n_color = n_color_z + ztot*10*dFactor + OFFSET_COLOR;
				bj = rj + gj + n_color;
      }
      else
      {
        if (n_color < maxit)
        {
          j = n_color = 0;
          n_color_z = -1;
        }
				rj = gj = bj = n_color;
      }
      break;

		case 27:  // Fractal Dimension
			break;

		case 29:  
			xtot *= dFactor;
			ytot *= dFactor;

			rj = (xtot*xtot+ytot*ytot);
			gj = rj;
			bj = rj;
				
			break;

		case 30:
			xtot *= dFactor;
			ytot *= dFactor;

			rj = xtot*xtot;
			gj = (xtot*xtot+ytot*ytot);
			bj = ytot*ytot;

			break;

		case 31:
			rj = gj = bj = 0;
			n_color_x = xtot*1000*dFactor;
			n_color_y = ytot*1000*dFactor;

			if (n_color_x || n_color_y)
			{
				if (n_color_x > n_color_y)
				{
					if (n_color_x < 256)
					{
						rj = n_color_x;
					}
					else
					if (n_color_x >= 256 && n_color_x < 512)
					{
						rj = 255;
						gj = n_color_x - 256;
					}
					else
					if (n_color_x >= 512 && n_color_x < 768)
					{
						rj = gj = 255;
						bj = n_color_x - 512;
					}
					else
					if (n_color_x >= 768)
					{
						rj = gj = bj = 255;
					}
				}
				else
				{
					if (n_color_y < 256)
					{
						bj = n_color_y;
					}
					else
					if (n_color_y >= 256 && n_color_y < 512)
					{
						bj = 255;
						rj = n_color_y - 256;
					}
					else
					if (n_color_y >= 512 && n_color_y < 768)
					{
						bj = rj = 255;
						gj = n_color_y - 512;
					}
					else
					if (n_color_y >= 768)
					{
						rj = gj = bj = 255;
					}
				}
			}
			else
				j = 0;

			break;		
		
		case 32:
			rj = gj = bj = 0;
	
			if (n_color_x || n_color_y)
			{
				if (n_color_x)
					xtot = n_color_x + xtot*100*dFactor;

				if (n_color_y)
					ytot = n_color_y + ytot*100*dFactor;
	
				d = (xtot + ytot)/2;

				rj = d + xtot;
				gj = d + ytot;			
				bj = d;
			}
			else
				j = 0;

			break;		

		case 33:  // FD Strands
		case 34:
			if (n_color_x || n_color_y)
				j = n_color;
			else
				j = 0;

			break;

		case 35:
		case 36:
			if (n_color_z)
				j = n_color;
			else
				j = 0;
			break;

		case 37:
			if (n_color_z)
				j = n_color;
			else
				j = 0;
			break;

		case 38:
			j = n_color;
			break;

		case 45:
			xtot = ztot;
			ytot = ztot;

		case 44:  // diamonds
			if (xtot || ytot )
			{      
				rj = xtot*dFactor;
				gj = ytot*dFactor;			
				bj = (rj + gj)/2;
			}
			else
				rj = gj = bj = 0;

			break;

		case 46:		
		case 47:
			xtot = ztot;
			ytot = ztot;
			if (xtot || ytot)
			{      
				if (n_color_z%2 == 0)
				{
					rj = xtot*dFactor;
					gj = ytot*dFactor;			
					bj = (rj + gj)/2;
				}
				else
				{
					gj = xtot*dFactor+OFFSET_COLOR;
					bj = ytot*dFactor+OFFSET_COLOR;			
					rj = (bj + gj)/2;
				}
			}
			else
				rj = gj = bj = 0;

			break;

		case 48:
		case 49:
			if (n_color_z)
				j = n_color;
			else
				j = 0;
			break;

		case 50:

			if (xtot || ytot)
			{      
				rj = xtot*dFactor*5;  // *5
				gj = ytot*dFactor*5;	// *5		
				//bj = sqrt(rj*rj + gj*gj);
				bj = (rj + gj)/2;
			}
			else
				rj = gj = bj = 0;
		
		/*
			if (xsav || ysav)
			{      
				xtot*=dFactor;
				ytot*=dFactor;

				d = n_color + (xtot + ytot)/2;
				//d = sqrt(xtot*xtot + ytot*ytot);

				rj = d + xtot;
				gj = d + ytot;			
				bj = d;
			
			}
			else
				j = rj = gj = bj = 0;
		

			xtot = sqrt(xtot*xtot + ytot*ytot);
			if (xtot)
			{
				if (xtot < 256)
				{
					rj += xtot;
				}
				else
				if (xtot >= 256 && xtot < 512)
				{
					rj = 255;
					gj += xtot - 256;
				}
				else
				if (xtot >= 512 && xtot < 768)
				{
					rj = gj = 255;
					bj += xtot - 512;
				}
			}
			else
				j = 0;

			*/
	
      break;

		case 51:  
			if (n_color_x || n_color_y)
			{      
				if (n_color_x)
		      //xtot = (dStrands - fabs(xsav))*1000*dFactor;
		      xtot = (1 - fabs(xsav)/dStrands)*100*dFactor;

				if (n_color_y)
					//ytot = (dStrands - fabs(ysav))*1000*dFactor;
					ytot = (1 - fabs(ysav)/dStrands)*100*dFactor;
	      
				d = (double) n_color + (xtot + ytot)/2;

				rj = d + (xtot)/2;
				gj = d + (ytot)/2;			
				bj = d;
			}
			else
				j = 0;

      if (n_color_z)
      {
        ztot = (1 - zsav/dStrands)*100*dFactor;
        rj += ztot;
				gj += ztot;
				bj += ztot;
      }
			break;

		case 52:
			if (n_color_x || n_color_y)
			{      
				if (n_color_x)
		      //xtot = (dStrands - fabs(xsav))*1000*dFactor;
		      xtot = (1 - fabs(xsav)/dStrands)*100*dFactor;

				if (n_color_y)
					//ytot = (dStrands - fabs(ysav))*1000*dFactor;
					ytot = (1 - fabs(ysav)/dStrands)*100*dFactor;
	      
				//d = (double) (n_color_y + n_color_x) + (xtot + ytot)/2;

				rj = xtot;
				bj = ytot;			

				if (rj > bj)
					gj = rj;
				else
					gj = bj;

			}
			
      if (n_color_z)
      {
        //ztot = (dStrands - zsav)*1000*dFactor;
        ztot = (1 - zsav/dStrands)*100*dFactor;
        rj += ztot;
				gj += ztot;
				bj += ztot;
      }
			
			if (n_color_x || n_color_y)
			{
				if (n_color_x > n_color_y)
				{
					if (n_color_x < 256)
					{
						rj += n_color_x;
					}
					else
					if (n_color_x >= 256 && n_color_x < 512)
					{
						rj = 255;
						gj += n_color_x - 256;
					}
					else
					if (n_color_x >= 512 && n_color_x < 768)
					{
						rj = gj = 255;
						bj += n_color_x - 512;
					}
					//else
					//if (n_color_x >= 768)
					//{
					//	rj = gj = bj = 255;
					//}
				}
				else
				{
					if (n_color_y < 256)
					{
						bj += n_color_y;
					}
					else
					if (n_color_y >= 256 && n_color_y < 512)
					{
						bj = 255;
						rj += n_color_y - 256;
					}
					else
					if (n_color_y >= 512 && n_color_y < 768)
					{
						bj = rj = 255;
						gj += n_color_y - 512;
					}
					//else
					//if (n_color_y >= 768)
					//{
					//	rj = gj = bj = 255;
					//}
				}
			}
			else
				j = 0;

			break;

		default:
		  break;
  }
}

