/////////////////////////////////////////////////////
//
// Filters.c
// By: stephen c. ferguson
// http://home1.gte.net/itriazon/
// email: itriazon@gte.net
//
/////////////////////////////////////////////////////

#include <math.h>
#include "Talis_F.h"

#define DUAL_BFACTOR 3
#define OFFSET_COLOR 64

//////////////////////////////////////////////////////
// Filters
//////////////////////////////////////////////////////
inline void Do_Filter()
{
 switch (filter)
 {
   case 1:  // Stalks I
     if (ABS(__real__ z) < dStrands)
     {
       xsav = __real__ z;
       n_color_x = n_color;
     }

     if (ABS(__imag__ z) < dStrands)
     {
       ysav = __imag__ z;
       n_color_y = n_color;
     }
     break;

   case 2:  // Bubbles I
   case 8:  // Bubbles II
     if (sum_sqrs_z() < dStrands)
     {
       zsav = sum_sqrs_z();
       n_color_z = n_color;
     }
     break;

   case 3:
     if (sum_sqrs_z() >= 1e6)
       return;

     xtot = xtot + ABS(__real__ z);
     xavg = xtot/n_color;
     xdif = xavg - xsav;
     xsav = xavg;
     if (ABS(xdif) < dStrands)
       d_color_x = ABS(xdif);

     ytot = ytot + ABS(__imag__ z);
     yavg = ytot/n_color;
     ydif = yavg - ysav;
     ysav = yavg;
     if (ABS(ydif) < dStrands)
       d_color_y = ABS(ydif);
     break;

   case 4:
     if (sum_sqrs_z() >= 1e6)
       return;

     ztot = ztot + sum_sqrs_z();
     zavg = ztot/n_color;
     zdif = zavg - zsav;
     zsav = zavg;
     if (ABS(zdif) < dStrands)
       d_color_z = ABS(zdif);
     break;

	 case 5:  // log(log(...))
     break;

   case 6:  // Bubbles I
     if (sum_sqrs_z() < dStrands)
     {
       zsav = sum_sqrs_z();
       n_color_z = n_color;
     }
     break;

   case 7:  // dual bubbles
     if (sum_sqrs_z() < dStrands)
     {
       zsav = sum_sqrs_z();
       n_color_z = n_color;
     }

     if (sum_sqrs_z() < dStrands/DUAL_BFACTOR)
     {
       {
         zsav1 = sum_sqrs_z();
         n_color_z1 = n_color;
       }
     }

     break;

   case 9:  // Stalks II
     if (ABS(__real__ z) < dStrands)
     {
       //if (ABS(xsav) < ABS(__real__ z))
       {
         xsav = __real__ z;
         n_color_x = n_color;
       }
     }

     if (ABS(__imag__ z) < dStrands)
     {
       //if (ABS(ysav) < ABS(__imag__ z))
       {
         ysav = __imag__ z;
         n_color_y = n_color;
       }
     }
     break;

   case 10:  // Rings I
     ssq1 = sqrt(sum_sqrs_z());
     if (ssq1 < dStrands_HI && ssq1 > dStrands_LO && zsav < ssq1)
     //if (ssq1 < dStrands_HI && ssq1 > dStrands_LO)
     {
       zsav = ssq1;
       n_color_z = n_color;
     }
     break;

   case 11:  // Rings II
   case 12:  // Rings III
     ssq1 = 1/sum_sqrs_z();
     if (ssq1 < dStrands_HI && ssq1 > dStrands_LO && zsav < ssq1)
     //if (ssq1 < dStrands_HI && ssq1 > dStrands_LO)
     {
       zsav = ssq1;
       n_color_z = n_color;
     }
     break;

   case 13: // Hi Lo I
     dzx = ABS(__real__ z);
     dzy = ABS(__imag__ z);

     if (dzx < dStrands_HI_cx &&
         dzx > dStrands_LO_cx)
     {
       xtot = dzx;
       n_color_x = n_color;
     }

     if (dzy < dStrands_HI_cy &&
         dzy > dStrands_LO_cy)
     {
       ytot = dzy;
       n_color_y = n_color;
     }

     break;

   case 14:  // testing
     ssq1 = (sqrt((sum_sqrs_z())));

     //if (ssq1 < dStrands_HI && ssq1 > dStrands_LO && zsav < ssq1)
     if (ssq1 < dStrands_HI && ssq1 > dStrands_LO)
     {
       zsav = ssq1;
       n_color_z = n_color;
       //dzx = __real__ z;
       //dzy = __imag__ z;
     }
     break;


   case 17:
     //ssq1 = sum_sqrs_z();
     if ((ABS(__real__ z)) < dStrands && xtot == 0)
     {
        xtot = 1;
        xsav += atan(ABS(__real__ z / __imag__ z))*
                atan(ABS(__imag__ z / __real__ z));
        n_color_x = n_color;
     }

     if ((ABS(__imag__ z)) < dStrands && ytot == 0)
     {
        ytot = 1;
        ysav += atan(ABS(__real__ z / __imag__ z))*
                atan(ABS(__imag__ z / __real__ z));
        n_color_y = n_color;
     }

     break;

   case 18:
     if (sum_sqrs_z() < dStrands)
     {
       zsav += atan(ABS(__real__ z / __imag__ z))*
                atan(ABS(__imag__ z / __real__ z))*2;
     }
     break;

   case 19:  //
   	 ssq1 = sqrt(sum_sqrs_z());
     if (ssq1 < dStrands && ssq1 > zsav)
     {
       ztot += atan(ABS(__real__ z / __imag__ z))*
               atan(ABS(__imag__ z / __real__ z))*4*dFactor_2;
       zsav = ssq1;
       n_color_z = n_color;
     }

     break;

   case 20:
   	 ssq1 = sqrt(sum_sqrs_z());
     if (ssq1 < dStrands && ssq1 > zsav)
     {
       ztot += atan(ABS(__real__ z / __imag__ z))*
                atan(ABS(__imag__ z / __real__ z))*4*dFactor_2;
       zsav = ssq1;
       n_color_z = n_color;
     }
     break;

   case 21:  // Flowers I
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     {
       zsav = ssq1;
       n_color_z = n_color;
       ztot = atan(ABS(__real__ z / __imag__ z))*
               atan(ABS(__imag__ z / __real__ z))*100;

       dif_test = (ztot+(dStrands - zsav)*1000*dFactor_2);  // 1300
       if (dif_test < m_lower || dif_test > m_upper)
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
       }
     }
     break;

   case 22:  // Flowers II
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     {
       zsav = ssq1;
       n_color_z = n_color;
       ztot = (atan(ABS(__real__ z / __imag__ z))-
               atan(ABS(__imag__ z / __real__ z)))*30;

       dif_test = ztot + (dStrands - zsav)*1000*dFactor_2;
       if (dif_test < m_lower || dif_test > m_upper)
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
       }
     }
     break;

   case 23:  // Flowers III
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     {
       zsav = ssq1;
       n_color_z = n_color;
       ztot = (atan(ABS(__real__ z / __imag__ z)))*30;
       dt = __real__ z * __imag__ z;

       dif_test = ztot + (dStrands - zsav)*1000*dFactor_2;
       if (dif_test < m_lower || dif_test > m_upper)
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
       }
     }
     break;

   case 24:  // Flowers IV
     ssq1 = sum_sqrs_z();
     if (ssq1 < dStrands && zsav == 0)
     {
       zsav = ssq1;
       n_color_z = n_color;
       ztot = atan(ABS(__real__ z / __imag__ z))*
               atan(ABS(__imag__ z / __real__ z))*100;
       dt = __real__ z * __imag__ z;

       dif_test = ztot+(dStrands - zsav)*1000*dFactor_2;  // 1300
       if (dif_test < m_lower || dif_test > m_upper)
       {
         ztot = 0;
         zsav = 0;
         n_color_z = 0;
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
       }
     }
     break;

   case 26:  // testing
   	 ssq1 = sqrt(sum_sqrs_z());
     if (ssq1 < dStrands && zsav == 0)
     {
       ztot += atan(ABS(__real__ z / __imag__ z))*
               atan(ABS(__imag__ z / __real__ z))*4*dFactor_2;
       zsav = ssq1;
       n_color_z = n_color;
     }

     break;

   default:  // last z values (gradients)
     // Case 15, 16, 17
     break;
 }
}

void Filter_Complete()
{
	n_color = 0;
  switch (filter)
  {
    case 1:

			/*
      if (n_color_x)			
			{
        xtot = (dStrands - ABS(xsav))*10000*dFactor;
				n_color = n_color_x;
			}

      if (n_color_y)
			{
        ytot = (dStrands - ABS(ysav))*10000*dFactor;
				n_color = n_color_y;
			}
			*/

      break;

    case 2:
      if (n_color_z)
      {
        ztot = (dStrands - zsav)*1000*dFactor;
        if (n_color < maxit)
          n_color = (n_color + ztot)/2;
        else
          n_color += (n_color + ztot)/2;
      }
      break;

    case 3:
      if (d_color_x)
        xtot = (dStrands - d_color_x)*10000*dFactor;

      if (d_color_y)
        ytot = (dStrands - d_color_y)*10000*dFactor;

      n_color = n_color + (xtot + ytot)/2;
      break;

    case 4:  // Moving average II
      if (d_color_z)
        ztot = (dStrands - d_color_z)*10000*dFactor;

      n_color = n_color + ztot;
      break;

	  case 5:
			if (n_color<maxit)
        if (sum_sqrs_z() > 1)
          n_color = (n_color - log (log (sum_sqrs_z())) / log (2))*10*dFactor;
	    break;

    case 6:
      if (n_color<maxit)
        if (sum_sqrs_z() > 1)
          n_color = (n_color - log (log (sum_sqrs_z())) / log (2))*10*dFactor;

      if (n_color_z)
      {
        ztot = (dStrands - zsav)*10000*dFactor;
        if (n_color_z%2==0)
          n_color = ztot;
        else
          n_color = ztot+16;
      }

      break;

    case 7:
      if (n_color >= maxit)
      {
         n_color = 0;
         n_color_z = n_color_z1 = 0;
      }
      else
        n_color = 0;

      if (n_color_z)
      {
        ztot = (dStrands - zsav)*3000*dFactor;
        n_color = ztot;
        if (n_color_z%2==0)
          n_color+=OFFSET_COLOR;
      }

      if (n_color_z1)
      {
        ztot = (dStrands/DUAL_BFACTOR - zsav1)*3000*dFactor;
        n_color = ztot+OFFSET_COLOR;
        if (n_color_z1%2==0)
          n_color += OFFSET_COLOR;
      }

      break;

    case 8:   // Bubbles II
      if (n_color_z)
      {
        ztot = (dStrands - zsav)*1000*dFactor;
        if (n_color < maxit)
        {
          n_color = ztot;
          if (n_color_z%2==0)
            n_color+=OFFSET_COLOR;
        }
				else
        {
          n_color += ztot;
          if (n_color_z%2==0)
            n_color+=OFFSET_COLOR;
        }
      }
      else
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }

      break;

    case 9:
      if (!n_color_x && !n_color_y)
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }
      else
      {
        if (n_color_x)
        {
          xtot = n_color_x + (dStrands - ABS(xsav))*1000*dFactor;
          if (n_color_x%2==0)
            xtot+=OFFSET_COLOR;
        }

        if (n_color_y)
        {
          ytot = n_color_y + (dStrands - ABS(ysav))*1000*dFactor+OFFSET_COLOR;
          if (n_color_y%2==0)
            ytot+=OFFSET_COLOR;
        }

        if (xtot > ytot)
          n_color = xtot;
        else
        if (ytot > xtot)
          n_color = ytot;
        else
        if (ytot && xtot)
          n_color = (xtot+ytot)/2;
      }

      break;

    case 10:   // Rings I
      if (n_color_z > 2)
      {
        ztot = ABS(limit - zsav)*1000*dFactor;
        n_color = ztot;

        //if (n_color_z%2==0)
          //n_color+=OFFSET_COLOR;
      }
      else
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }
      break;

    case 11:   // Rings II
      if (n_color_z > 2)
      {
        ztot = ABS(limit - zsav)*1000*dFactor;
        if (n_color_z%2==0)
          n_color = ztot;
        else
          n_color = ztot + OFFSET_COLOR;
      }
      else
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }
      break;

    case 12:  // Rings III
      if (n_color_z > 2)
      {
        ztot = ABS(limit - zsav)*1000*dFactor;
        if (n_color_z%2==0)
          n_color = ztot;
        else
          n_color = ztot + OFFSET_COLOR;
      }
      else
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }
      break;

    case 13: // Hi Lo I
      if (n_color_x || n_color_y)
      {
        //if (n_color_x >= n_color_y)
        if (xtot >= ytot)
        {
          n_color += (dStrands_HI_cx-xtot)*10000*dFactor;;
          //n_color = n_color_x;
          if (n_color_x%2==0)
            n_color+=OFFSET_COLOR;
        }
        else
        {
          n_color += (dStrands_HI_cy-ytot)*10000*dFactor;;
          //n_color = n_color_y;
          if (n_color_y%2==0)
            n_color+=OFFSET_COLOR;
        }
      }
      else
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }

      break;

    case 14:   // Rings I w/ sin
      if (n_color_z > 3)
      {
        //ztot = ABS(limit - zsav)*1000*dFactor;

        //ztot = ((limit - zsav))*1000*dFactor;

        ztot = (ABS(dStrands_HI - zsav))*200*dFactor;
        n_color = ztot;

        if (n_color_z%2==0)
        	n_color = ztot;
        else
          n_color = ztot + OFFSET_COLOR;

        //dt = ABS(dzx*dzx-dzy*dzy);
        //n_color += dt*100*dFactor;

      }
      else
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }

      break;

    case 15:
      if (n_color >= maxit)
      {
        n_color = ABS(sin(__real__ z * __real__ z*100))*
                  ABS(sin(__imag__ z * __imag__ z*100))*
                  //ABS(sin(__imag__ z * __real__ z*100))*
                  200*dFactor;
      }
      else
      {
        ssq1 = sum_sqrs_z();
        if (ssq1 <= 2)
          ssq1 = 2;
        n_color = (n_color - log (log (ssq1)) / log (2))*10*dFactor;

        //n_color = 0;
        //n_color_z = -1;
      }

      n_color_z = 0;

      break;

    case 16:
      if (n_color < maxit)
      {
        ztot = atan(ABS(__real__ z / __imag__ z))-
               atan(ABS(__imag__ z / __real__ z))*
               60*dFactor;

        if (n_color%2==0)
          n_color = ztot;
        else
          n_color = ztot + OFFSET_COLOR;
      }
      else
      {
        n_color = 0;
        n_color_z = -1;
      }
      break;

    case 17:
      //if ((n_color_x || n_color_y) && n_color < maxit)
      if (n_color_x || n_color_y)
      {
        if (n_color_x)
          xtot = xsav*200*dFactor;

        if (n_color_y)
          ytot = ysav*200*dFactor;

        if (n_color < maxit)
          n_color = sqrt(xtot*xtot+ytot*ytot);
				else
          n_color += sqrt(xtot*xtot+ytot*ytot);
      }
      else
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }
      break;

    case 18:
      n_color += zsav*10*dFactor;
      break;

    case 19:
      if (n_color_z && n_color > 1)
      {
        if (n_color_z%2==0)
          n_color = n_color_z*2 + ztot*10*dFactor;
        else
          n_color = n_color_z*2 + ztot*10*dFactor + OFFSET_COLOR;
      }
      else
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }
      break;

    case 20:
      if (n_color_z && n_color > 1)
      {
      	ztot += (dStrands - zsav)*1000*dFactor;
        if (n_color_z%2==0)
      	  n_color = (n_color_z*2 + ztot)/2;
        else
      	  n_color = (n_color_z*2 + ztot)/2 + OFFSET_COLOR;
      }
      else
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }

      break;

    case 21:   // Flowers I
    	if (n_color < maxit && n_color_z == 0)
      {
         n_color = 0;
         n_color_z = -1;  // sets the background to black
      }

      if (n_color_z == 0)
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }

      if (n_color_z > 0)
      {
        ztot = n_color_z*3
          + ztot + (dStrands - zsav)*1000*dFactor;  // 1300
        if (n_color < maxit-1)
          n_color = ztot;
        else
          n_color += ztot;
        if (n_color_z%2==0)
          n_color+=OFFSET_COLOR;
      }
      break;


    case 22:   // Flowers II
    	if (n_color < maxit && n_color_z == 0)
      {
         n_color = 0;
         n_color_z = -1;
      }

      if (n_color_z == 0)
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }

      if (n_color_z > 0)
      {
        ztot = n_color_z*3
          + ztot + (dStrands - zsav)*1000*dFactor;  // 1300

        if (n_color < maxit-1)
          n_color = ztot;
        else
          n_color += ztot;

        if (n_color_z%2==0)
          n_color+=OFFSET_COLOR;
      }
      break;

    case 23:   // Flowers III
    	if (n_color < maxit && n_color_z == 0)
      {
         n_color = 0;
         n_color_z = -1;
      }

      if (n_color_z == 0)
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }

      if (n_color_z > 0)
      {
        ztot = n_color_z*3
          + ztot + (dStrands - zsav)*1000*dFactor;  // 1300

        if (n_color < maxit-1)
          n_color = ztot;
        else
          n_color += ztot;

        if (n_color_z%2==0)
          n_color+=OFFSET_COLOR;

        if (dt > 0)
          n_color+=OFFSET_COLOR;
      }
      break;

    case 24:   // Flowers IV
    	if (n_color < maxit && n_color_z == 0)
      {
         n_color = 0;
         n_color_z = -1;
      }

      if (n_color_z == 0)
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }

      if (n_color_z > 0)
      {
        ztot = n_color_z*3
          + ztot + (dStrands - zsav)*1000*dFactor;  // 1300

        if (n_color < maxit-1)
          n_color = ztot;
        else
          n_color += ztot;

        if (n_color_z%2==0)
          n_color+=OFFSET_COLOR;
        if (dt > 0)
          n_color+=OFFSET_COLOR;
      }
      break;

    case 25:   // Flowers V
    	if (n_color < maxit && n_color_z == 0)
      {
         n_color = 0;
         n_color_z = -1;
      }

      if (n_color_z == 0)
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }

      if (n_color_z > 0)
      {
        ztot = n_color_z*3
          + ztot + (dStrands - zsav)*1000*dFactor;  // 1300

        if (n_color < maxit-1)
          n_color = ztot;
        else
          n_color += ztot;

        if (n_color_z%2==0)
          n_color+=OFFSET_COLOR;
        if (dt > 0)
          n_color+=OFFSET_COLOR;
      }
      break;

    case 26:  // testing
      if (n_color_z && n_color > 1)
      {
        if (n_color_z%2==0)
          n_color = n_color_z + ztot*10*dFactor;
        else
          n_color = n_color_z + ztot*10*dFactor + OFFSET_COLOR;
      }
      else
      {
        if (n_color < maxit)
        {
          n_color = 0;
          n_color_z = -1;
        }
      }
      break;

    default:
      break;


  }

  //n_color += (atan(ABS(__real__ z /__imag__ z))*100*dFactor);

	if (xsav == 0 && ysav == 0)
		n_color = 0;
}

