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

			//return;

			if (fabs(__real__ z) < dStrands && fabs(__imag__ z) < dStrands)
			{				     
				//if (fabs(__real__ z) < dStrands && !n_color_x)
				if (fabs(__real__ z) < dStrands)
				{
  				//wsprintf (cstr, "step 1");
					//MessageBox(NULL, cstr, "Debug", MB_OK);
					n_color_x++;
					//n_color = maxit;
					xsav = __real__ z;
				}

				if (fabs(__imag__ z) < dStrands)
				{
					n_color_y++;
					//n_color = maxit;
					ysav = __imag__ z;
				}
			}
     
			break;

   case 2:  // Bubbles I
   case 8:  // Bubbles II
     if (sum_sqrs_z() < dStrands*4 && n_color_z == 0)
     {
       n_color_z++;
			 n_color = maxit;
			 zsav = sum_sqrs_z();
			 ysav = __imag__ z;
     }

			if (fabs(__real__ z) < dStrands && n_color_x == 0)
			{
				n_color_x++;
	      n_color = maxit;
				xsav = __real__ z;
			}
		
			if (fabs(__imag__ z) < dStrands && n_color_y == 0)
			{
				n_color_y++;
	      n_color = maxit;
				ysav = __imag__ z;
			}

     break;

   case 3:
     if (sum_sqrs_z() >= 1e6)
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
     if (sum_sqrs_z() >= 1e6)
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
     if (sum_sqrs_z() < dStrands)
     {
       zsav = sum_sqrs_z();
       n_color_z = n_color;
			 xsav = __real__ z;
			 ysav = __imag__ z;		 
     }
     break;

   case 7:  // dual bubbles
     if (sum_sqrs_z() < dStrands)
     {
       zsav = sum_sqrs_z();
       n_color_z = n_color;
			 xsav = __real__ z;
			 ysav = __imag__ z;		 
     }

     if (sum_sqrs_z() < dStrands/DUAL_BFACTOR)
     {
       {
         zsav1 = sum_sqrs_z();
         n_color_z1 = n_color;
				 xsav = __real__ z;
				 ysav = __imag__ z;		 
       }
     }

     break;

   case 9:  // Stalks II
     if (fabs(__real__ z) < dStrands)
     {
       {
         xsav = __real__ z;
         n_color_x = n_color;
       }
     }

     if (fabs(__imag__ z) < dStrands)
     {
       {
         ysav = __imag__ z;
         n_color_y = n_color;
       }
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
       xtot = dzx;
       n_color_x = n_color;
			 n_color = maxit;
			 xsav = __real__ z;
     }

     if (dzy < dStrands_HI_cy &&
         dzy > dStrands_LO_cy)
     {
       ytot = dzy;
       n_color_y = n_color;
			 n_color = maxit;
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
     //ssq1 = sum_sqrs_z();
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
                atan(fabs(__imag__ z / __real__ z))*2*dFactor_2;
			 xsav = __real__ z;
			 ysav = __imag__ z;		 
     }
     break;

   case 19:  //
   	 ssq1 = sqrt(sum_sqrs_z());
     if (ssq1 < dStrands && ssq1 > zsav)
     {
       ztot += atan(fabs(__real__ z / __imag__ z))*
               atan(fabs(__imag__ z / __real__ z))*20*dFactor_2;
       zsav = ssq1;
       n_color_z = n_color;
			 xsav = __real__ z;
			 ysav = __imag__ z;		 
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
     {
       zsav = ssq1;
       n_color_z = n_color;
       ztot = atan(fabs(__real__ z / __imag__ z))*
               atan(fabs(__imag__ z / __real__ z))*100;

       dif_test = (ztot+(dStrands - zsav)*1000*dFactor_2);  // 1300
       if (dif_test < m_lower || dif_test > m_upper)
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
				 xsav = __real__ z;
				 ysav = __imag__ z;		 
       }
     }
     break;

   case 22:  // Flowers II
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     {
       zsav = ssq1;
       n_color_z = n_color;
       ztot = (atan(fabs(__real__ z / __imag__ z))-
               atan(fabs(__imag__ z / __real__ z)))*30;

       dif_test = ztot + (dStrands - zsav)*1000*dFactor_2;
       if (dif_test < m_lower || dif_test > m_upper)
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
				 xsav = __real__ z;
				 ysav = __imag__ z;		 
       }
     }
     break;

   case 23:  // Flowers III
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     {
       zsav = ssq1;
       n_color_z = n_color;
       ztot = (atan(fabs(__real__ z / __imag__ z)))*30;
       dt = __real__ z * __imag__ z;

       dif_test = ztot + (dStrands - zsav)*1000*dFactor_2;
       if (dif_test < m_lower || dif_test > m_upper)
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
				 xsav = __real__ z;
				 ysav = __imag__ z;		 
       }
     }
     break;

   case 24:  // Flowers IV
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     {
       zsav = ssq1;
       n_color_z = n_color;
       ztot = atan(fabs(__real__ z / __imag__ z))*
               atan(fabs(__imag__ z / __real__ z))*100;
       dt = __real__ z * __imag__ z;

       dif_test = ztot+(dStrands - zsav)*1000*dFactor_2;  // 1300
       if (dif_test < m_lower || dif_test > m_upper)
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
				 xsav = __real__ z;
				 ysav = __imag__ z;		 
       }
     }
     break;

   case 25:  // Flowers V
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     {
       zsav = ssq1;
       n_color_z = n_color;
       ztot = (sin(__real__ z * __real__ z*100)*
               sin(__imag__ z * __imag__ z*100))*100;
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
		 pXTemp[n_color] = __real__ z;
		 pYTemp[n_color] = __imag__ z;	
		 xsav = __real__ z;
		 ysav = __imag__ z;		 
		 break;
		
	 case 29:  // Stalks & Bubbles			
	 case 30:
     if (fabs(__real__ z) < dStrands)
     {
       xsav = __real__ z;
       n_color_x = n_color;
			 //n_color_x++;
     }

     if (fabs(__imag__ z) < dStrands)
     {
       ysav = __imag__ z;
       n_color_y = n_color;
			 //n_color_y++;
     }

     if (sum_sqrs_z() < dStrands)
     {
       zsav = sum_sqrs_z();
       //n_color_z = n_color;
			 n_color_z++;
       ysav = __imag__ z;
       xsav = __real__ z;
     }     
		 break;
		
		case 31:
		case 32:

/*
From: earl@spyke.com (Earl Hinrichs)
To: "'itriazon@gte.net'" <itriazon@gte.net>
Subject: RE: fractal - a027 [800x600, 189k] - a027.jpg (1/1)
Date: Sun, 28 Dec 1997 15:31:37 -0700

Some pointers if you try to implement this.

I said the saturation is based on 'how often' the orbit hits the trap
region. I do not use a simple count. Each 'hit' is scored with a number
between 0 and 1. A 1 being a hit right on the center of the trap region. For
example if the trap is a circle of radius r centered at the origin, then the
weight is: 1.0 - |z| / r. I add up these weighted scores.

When adding the weights, I want a result in the range 0-1. I use a modified
addition. If a is the accumulated score so far, and I want to add b, then a
"+" b = a + b - a*b. If a and b are in the range (0,1) then this sum is also
in the range.

Also, you will find that as you increase the interation limit, the image
tends to get too white. So you need to do something to dampen the
saturation. I do this in one of two ways. One is to do the sum as above,
then replace the result, a, with a^d. d is a dampening factor. Larger d
means less white. Another way is to limit how much is added at each step.
The accumulation formula is a + d*b - d*a*b. This time smaller d means less
white.

----
earl hinrichs, offering free opinions on everything.
email: earl@spyke.com, web: http://computerart.org/
!!New Domain. New Site. Ten new images 12/20/97!!


Earl Hinrichs wrote:

> It is a variation on an orbit trap method. I do not quit when the trap
condition is met, the iteration continues. The more often the orbit enters
the trap region, the brighter the color. There is a base color that is
determined by the index of the orbits that lie in the trap region. For the
orbits with a few hits you can see the colors, for those with a high number
of hits, the color is totally saturated.
>
> ----
> earl hinrichs, offering free opinions on everything.
> email: earl@spyke.com, web: http://computerart.org/
> !!New Domain. New Site. Ten new images 12/20/97!!
>
> -----Original Message-----
> From:   Stephen C. Ferguson [SMTP:itriazon@gte.net]
> Sent:   Saturday, December 20, 1997 7:08 AM
> To:     Earl Hinrichs
> Subject:        Re: fractal - a027 [800x600, 189k] - a027.jpg (1/1)
*/						

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
				pXTemp[n_color] = (1 - fabs(__real__ z)/dStrands)*100;
				n_color_x++;
        xsav = __real__ z;
			}
			else
				pXTemp[n_color] = 1; ////////////
			
			if (fabs(__imag__ z) < dStrands)
			{
				pYTemp[n_color] = (1 - fabs(__imag__ z)/dStrands)*100;	
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
				pXTemp[n_color] = 1 - (dStrands_HI_cx - ssq1)/(dStrands_HI_cx - dStrands_LO_cx);
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
				pYTemp[n_color] = 1 - (dStrands_HI_cy - ssq1)/(dStrands_HI_cy - dStrands_LO_cy);
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
			pXTemp[n_color] = atan(fabs(__real__ z/__imag__ z));
			pYTemp[n_color] = atan(fabs(__imag__ z/__real__ z));
	 	  xsav = __real__ z;
	  	ysav = __imag__ z;		 
 		
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
void Filter_Complete()
{
	static int nCount = 0;
	
	j = rj = gj = bj = n_color;
  
	switch (filter)
  {
    case 1:

  	 //wsprintf (cstr, "step 3");
	   //MessageBox(NULL, cstr, "Debug", MB_OK);

			//return;

			if (n_color_x || n_color_y)
			{      
				if (n_color_x)
		      //xtot = (dStrands - fabs(xsav))*1000*dFactor;
						xtot = (1 - fabs(xsav)/dStrands)*50*dFactor+n_color_x;
				
				if (n_color_y)
					//ytot = (dStrands - fabs(ysav))*1000*dFactor;
						ytot = (1 - fabs(ysav)/dStrands)*50*dFactor+n_color_y;

				d = (double) n_color + (xtot + ytot)/2;
				//d = sqrt(xtot*xtot + ytot*ytot);

				rj = d + xtot;
				gj = d + ytot;			
				bj = d;
			
			}
			else
				j = rj = gj = bj = 0;

      break;

    case 2:
      if (n_color_z || n_color_x || n_color_y)
      {
        //ztot = (dStrands - zsav)*1000*dFactor;
				ztot = (1 - zsav/dStrands*4)*10*dFactor;
        rj = n_color = n_color_z + ztot;
        //gj = (1 - fabs(xsav)/dStrands)*10000*dFactor;
        //bj = (1 - fabs(ysav)/dStrands)*10000*dFactor;
      }
			else
				j = 0;

			if (n_color_x || n_color_y)
			{      
				if (n_color_x)
		      //xtot = (dStrands - fabs(xsav))*1000*dFactor;
						xtot = (1 - fabs(xsav)/dStrands)*50*dFactor;
				
				if (n_color_y)
					//ytot = (dStrands - fabs(ysav))*1000*dFactor;
						ytot = (1 - fabs(ysav)/dStrands)*50*dFactor;

				d = (double) n_color + (xtot + ytot)/2;
				rj = d + xtot;
				gj = d + ytot;
			}	

			bj = n_color;
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
      if (n_color<maxit)
			{
        if (sum_sqrs_z() > 1)
          n_color = (n_color - log (log (sum_sqrs_z())) / log (2))*50*dFactor;
			}
			
      if (n_color_z)
      {
        ztot = (dStrands - zsav)*1000*dFactor_2;
        if (n_color_z%2==0)
          rj = n_color = ztot;
        else
          gj = n_color = ztot+16;
      }
			else
				rj = gj = n_color;

			bj = rj + gj + n_color;
      break;

    case 7:
      if (n_color >= maxit)
      {
         j = n_color = 0;
         n_color_z = n_color_z1 = 0;
      }
      else
        n_color = 0;

			if (n_color_z || n_color_z1)
			{
				if (n_color_z)
				{
					ztot = (dStrands - zsav)*1000*dFactor;
					rj = n_color = ztot;

					if (n_color_z%2==0)
					{
						n_color+=OFFSET_COLOR;
						gj = n_color;
					}
				}

				if (n_color_z1)
				{
					ztot = (dStrands/DUAL_BFACTOR - zsav1)*1000*dFactor;
					rj = n_color = ztot+OFFSET_COLOR;

					if (n_color_z1%2==0)
					{
						n_color += OFFSET_COLOR;
						gj = n_color;
					}
				}
			}
			else
				j = 0;

			bj = rj + gj + n_color;
      break;

    case 8:   // Bubbles II
      if (n_color_z)
      {
        ztot = (dStrands - zsav)*1000*dFactor;
        if (n_color < maxit)
        {
          rj = n_color = ztot;
          if (n_color_z%2==0)
					{
            n_color+=OFFSET_COLOR;
						gj = n_color;
					}
        }
				else
        {
          rj = n_color += ztot;
          if (n_color_z%2==0)
					{
						n_color+=OFFSET_COLOR;
						gj = n_color;
					}
        }
				bj = rj + bj + n_color;
      }
      else
      {
        if (n_color < maxit)
        {
          j = n_color = 0;
          n_color_z = -1;
        }
				rj = rj = gj = 0;
      }

      break;

    case 9:
      if (!n_color_x && !n_color_y)
      {
        if (n_color < maxit)
        {
          j = n_color = 0;
          n_color_z = -1;
        }
      }
      else
      {
        if (n_color_x)
        {
          xtot = (double) n_color_x + (dStrands - fabs(xsav))*300*dFactor;
          if (n_color_x%2==0)
            xtot+=OFFSET_COLOR;
        }

        if (n_color_y)
        {
          ytot = (double) n_color_y + (dStrands - fabs(ysav))*300*dFactor;
          if (n_color_y%2==0)
            ytot+=OFFSET_COLOR;
        }

        rj = xtot;
        gj = ytot;
        bj = (xtot+ytot)/2;
      }

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

    case 13: // Hi Lo I
      if (n_color_x > n_color_y)
        bj = rj = (((dStrands_HI_cx-xtot)*.5)/(dStrands_cxd))*500*dFactor;
			else
        bj = gj = (((dStrands_HI_cy-ytot)*.5)/(dStrands_cyd))*500*dFactor;

      if (!n_color_x && !n_color_y)
			{
        if (n_color < maxit)
        {
          j = n_color = 0;
          n_color_z = -1;
        }
				rj = gj = bj = n_color;
      }

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
      n_color += zsav*3*dFactor;
			rj = gj = bj = n_color;
      break;

    case 19:
      if (n_color_z && n_color > 1)
      {
        //if (n_color_z%2==0)
          //n_color = n_color_z*2 + ztot*2*dFactor;
        //else
          //n_color = n_color_z*2 + ztot*2*dFactor + OFFSET_COLOR;

        if (n_color_z%2==0)
          rj = n_color = zsav*5 + ztot*2*dFactor;
        else
          gj = n_color = zsav*5 + ztot*2*dFactor + OFFSET_COLOR;

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
        ztot = n_color_z*3
          + ztot + (dStrands - zsav)*1000*dFactor;  // 1300
        if (n_color < maxit-1)
          rj = n_color = n_color + ztot;
        else
          rj = n_color = n_color + ztot;

        if (n_color_z%2==0)
          gj = n_color = n_color + OFFSET_COLOR;

				bj = rj + gj + n_color;
      }
      break;

    case 22:   // Flowers II
    	if (n_color < maxit && n_color_z == 0)
      {
        j = n_color = 0;
        n_color_z = -1;
				rj = gj = bj = n_color;
      }

      if (n_color_z == 0)
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
				rj = gj = bj = n_color;
      }

      if (n_color_z > 0)
      {
        ztot = n_color_z*3
          + ztot + (dStrands - zsav)*1000*dFactor;  // 1300

        if (n_color < maxit-1)
          rj = n_color = ztot;
        else
          gj = n_color = n_color + ztot;

        if (n_color_z%2==0)
          bj = n_color = n_color + OFFSET_COLOR;

				bj = bj + rj + gj;
			}
      break;

    case 23:   // Flowers III
    	if (n_color < maxit && n_color_z == 0)
      {
        j = n_color = 0;
        n_color_z = -1;
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
        ztot = n_color_z*3
          + ztot + (dStrands - zsav)*1000*dFactor;  // 1300

        if (n_color < maxit-1)
          rj = n_color = ztot;
        else
          gj = n_color = n_color + ztot;

        if (n_color_z%2==0)
          bj = n_color = n_color + OFFSET_COLOR;

				bj = bj + rj + gj;

        if (dt > 0)
          rj = gj = bj = n_color = n_color + OFFSET_COLOR;
      }
      break;

    case 24:   // Flowers IV
    	if (n_color < maxit && n_color_z == 0)
      {
        j = n_color = 0;
        n_color_z = -1;
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
        ztot = n_color_z*3
          + ztot + (dStrands - zsav)*1000*dFactor;  // 1300

        if (n_color < maxit-1)
          rj = n_color = n_color + ztot;
        else
          gj = n_color = n_color + ztot;

        if (n_color_z%2==0)
          bj = n_color = n_color + OFFSET_COLOR;
				else
					bj = n_color;

				bj = bj + rj + gj;

        if (dt > 0)
          rj = gj = bj = n_color = n_color + OFFSET_COLOR;
      }

      break;

    case 25:   // Flowers V
    	if (n_color < maxit && n_color_z == 0)
      {
        j = n_color = 0;
        n_color_z = -1;
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
        ztot = n_color_z*3
          + ztot + (dStrands - zsav)*1000*dFactor;  // 1300

        if (n_color < maxit-1)
          rj = n_color = ztot;
        else
          gj = n_color = n_color + ztot;

        if (n_color_z%2==0)
          bj = n_color = n_color + OFFSET_COLOR;

				bj = bj + rj + gj;

        if (dt > 0)
          rj = gj = bj = n_color = n_color + OFFSET_COLOR;
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

		case 30:
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

			/*
			if (rj > 255)
				rj = 255;
				
			if (bj > 255)
				bj = 255;
				
			if (gj > 255)
				gj = 255;
			*/

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

		default:
		  break;
  }
}

