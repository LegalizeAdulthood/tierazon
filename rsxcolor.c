/////////////////////////////////////////////////
// rsxcolor.c
/////////////////////////////////////////////////
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

void Generalized_Coloring_Method1()
{	
	/*
	if (px == 1 && py == 1)
	{
		sprintf(cstr, "step 2, x = %f, y=%f, i = %d, rj = %f, gj = %f",
			x, y, i, rj, gj);
		MessageBox(NULL, cstr, "bug", MB_OK);
	}
	*/
  
	temp = fabs(sin(x * x * 100))*
         fabs(sin(y * y * 100))*
            100*dFactor_2;
	rj+=temp;
	gj+=temp;
	bj+=temp;

}

void Generalized_Coloring_Method2()
{
  temp = fabs(sin(xsav * 50))*
         fabs(sin(ysav * 50))*100*dFactor_2;
	rj+=temp;
	gj+=temp;
	bj+=(rj+gj)/2;

}

void Generalized_Coloring_Method3()
{
  //temp = fabs(sin(1 + __real__ z * __real__ z * 100))*
    //     fabs(sin(1 + __imag__ z * __imag__ z * 100))*
      //      100*dFactor_2;

	//if (magnitude_z() < bailout)
	//temp = 1/atan(fabs(xsav/ysav))*10*dFactor;
		
	temp = atan(1/fabs(xsav/ysav))
			-atan(1/fabs(ysav/xsav))*100*dFactor_2;
		
	rj+=temp;
	gj+=temp;
	bj+=temp;

}

void Generalized_Coloring_Method4()
{
	//z.set_real(x);
	//z.set_imag(y);

	//__real__ z = xsav;
	//__imag__ z = ysav;

	xsav_ = x;
	ysav_ = y;

	//temp = atan(fabs(xsav/ysav))
		//		-atan(fabs(ysav/xsav))*10*dFactor;

	//if (magnitude_z() < bailout)
	temp = atan(1/fabs(xsav_/ysav_))
			-atan(1/fabs(ysav_/xsav_))*100*dFactor_2;
		
	rj+=temp;
	gj+=temp;
	bj+=temp;

}

void Generalized_Coloring_Method5()
{
	dzx = fabs(xsav);
	dzy = fabs(ysav);

	//dzx_save = fabs(__real__ c);
	//dzy_save = fabs(__imag__ c);

	//temp = atan(fabs(dzx/dzy))
		//		-atan(fabs(dzy/dzx))*10*dFactor;
	
	//if (magnitude_z() < bailout)
		temp = atan(1/fabs(dzx/dzy))
					+atan(1/fabs(dzy/dzx))*100*dFactor_2;		
	
	rj+=temp;
	gj+=temp;
	bj+=temp;
	
}

void Generalized_Coloring_Method6()
{
	dzx = fabs(xsav);
	dzy = fabs(ysav);

	//dzx_save = fabs(__real__ c);
	//dzy_save = fabs(__imag__ c);

	temp = atan(fabs(dzx/dzy))*10*dFactor;
	
	rj+=temp;
	gj+=temp;
	bj+=temp;

}

void Generalized_Coloring_Method7()
{
	dzx = fabs(xsav);
	dzy = fabs(ysav);

	dzx_save = fabs(x);
	dzy_save = fabs(y);

	if (xsav * ysav > 0)
		temp = sin(fabs(dzx*dzy*100+dzx_save*dzy_save*10))*100*dFactor_2;
	else
		temp = cos(fabs(dzx*dzy*100+dzx_save*dzy_save*10))*100*dFactor_2;
		
	rj+=temp;
	gj+=temp;
	bj+=temp;
}

void Generalized_Coloring_Method8()
{
	dzx = fabs(xsav);
	dzy = fabs(ysav);

	temp = 0;
	if (dzx < dStrands || dzy < dStrands) 
	{
		if (dzx < dStrands)
			temp =  (1 - dzx/dStrands)*100*dFactor_2;

		if (dzy < dStrands)
			temp += (1 - dzy/dStrands)*100*dFactor_2;

		rj+=temp;
		gj+=temp;
		bj+=temp;
	}
}

void Generalized_Coloring_Method9()
{
	dzx = fabs(xsav);
	dzy = fabs(ysav);

	if (dzy > dzx)
		temp = sin(fabs(dzx*dzx*60))*100*dFactor_2;
	else
		temp = sin(fabs(dzy*dzy*60))*100*dFactor_2;
	
	rj+=temp;
	gj+=temp;
	bj+=temp;

}

void Generalized_Coloring_Method10()
{
	dzx = fabs(xsav);
	dzy = fabs(ysav);

	dzx_save = fabs(x);
	dzy_save = fabs(y);

	temp=magnitude_z()*cos(fabs(dzx*dzx/dzy*dzy))*1000*dFactor_2;
	
	rj+=temp;
	gj+=temp;
	bj+=temp;

}

void Generalized_Coloring_Method11()
{
	dzx = fabs(xsav);
	dzy = fabs(ysav);

	dzx_save = fabs(x);
	dzy_save = fabs(y);

	temp=sin(fabs(dzx*dzx/dzx_save*dzx_save-
		dzy*dzy/dzy_save*dzy_save)*10)*100*dFactor_2;
	
	rj+=temp;
	gj+=temp;
	bj+=temp;

}

void Generalized_Coloring_Method12()
{
	dzx = fabs(xsav);
	dzy = fabs(ysav);

	dzx_save = fabs(x);
	dzy_save = fabs(y);

	temp=cos(fabs(dzx*dzy/dzx_save*dzy_save)*10)*100*dFactor_2;
	
	rj+=temp;
	gj+=temp;
	bj+=temp;

}

void Generalized_Coloring_Method13()
{
	//if (magnitude_c() < bailout)
		
	temp = (atan(1/fabs(x/y))
				-atan(1/fabs(y/x)))*100*dFactor_2;
	//else
		//temp = 0;
		
	rj+=temp;
	gj+=temp;
	bj+=temp;

}

void Generalized_Coloring_Method14()
{
	//z.set_real(x);
	//z.set_imag(y);

	xsav_ = x;
	ysav_ = y;

	temp = 0;
	//if (magnitude_z() < bailout)

	temp = atan(fabs(xsav_/ysav_))*200*dFactor_2;
		
	rj+=temp;
	gj+=temp;
	bj+=temp;
		
}

void Generalized_Coloring_Method15()
{	
	temp = atan(fabs(x/y)) *
				 atan(fabs(xsav/ysav));

	rj+=(temp*200*dFactor_2);
	gj+=(temp*200*dFactor_2);
	bj+=(temp*200*dFactor_2);

}

void Generalized_Coloring_Method19()
{
	//c.set_real(x);
	//c.set_imag(y);
	//xsav_ = x;
	//ysav_ = y;

	// magnitude
	x_size = 4 / (double) maxit;
	y_size = 4 / (double) maxit;
		
	rj += (((fabs(x / x_size) + 
		            fabs(y / y_size)))*dFactor_2);
	gj += (((fabs(x / x_size) + 
		            fabs(y / y_size)))*dFactor_2);
	bj += (((fabs(x / x_size) + 
		            fabs(y / y_size)))*dFactor_2);
		
}

void Generalized_Coloring_Method20()
{
	//c.set_real(x);
	//c.set_imag(y);

	__real__ c = xsav;
	__imag__ c = ysav;

	// Circles
	x_size = 4 / (double) maxit;
	y_size = 4 / (double) maxit;
	
	__real__ c = (fabs(__real__ c / x_size));
	__imag__ c = (fabs(__imag__ c / y_size));	
//	z = c;
	
	xsav_ = (fabs(xsav / x_size));
	ysav_ = (fabs(ysav / y_size));	
	//z = c;
		
	rj += ((sqrt(xsav_*xsav_+ysav_*ysav_))*dFactor);
	rj += ((sqrt(__real__ c*__real__ c+__imag__ c*__imag__ c))*dFactor_2);
		
	gj += ((sqrt(xsav_*xsav_+ysav_*ysav_))*dFactor);
	gj += ((sqrt(__real__ c*__real__ c+__imag__ c*__imag__ c))*dFactor_2);

	bj += ((sqrt(xsav_*xsav_+ysav_*ysav_))*dFactor);
	bj += ((sqrt(__real__ c*__real__ c+__imag__ c*__imag__ c))*dFactor_2);

}

void Generalized_Coloring_Method21()
{
	//c.set_real(x);
	//c.set_imag(y);

	__real__ c = xsav;
	__imag__ c = ysav;

	// Radial
	deg = x_y_to_degrees(__real__ c, __imag__ c);

	temp = ((double) maxit)/180;

	rj += (temp * deg * dFactor_2);
	gj += (temp * deg * dFactor_2);
	bj += (temp * deg * dFactor_2);
		
}

void Generalized_Coloring_Method22()
{
	//c.set_real(x);
	//c.set_imag(y);

	__real__ c = xsav;
	__imag__ c = ysav;

	// magnitude
	x_size = 4 / (double) maxit;
	y_size = 4 / (double) maxit;
	
	rj += (((fabs(__real__ c / x_size) + 
		            fabs(__imag__ c / y_size))))*dFactor_2;

	gj += (((fabs(__real__ c / x_size) + 
		            fabs(__imag__ c / y_size))))*dFactor_2;

	bj += (((fabs(__real__ c / x_size) + 
		            fabs(__imag__ c / y_size))))*dFactor_2;

}

void Generalized_Coloring_Method23()
{
	// Generalized Coloring Method	
	rj = (50*dFactor_2*(xsav*ysav)*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart);
	gj = (50*dFactor_2*(xsav*xsav)*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart);
	bj = (50*dFactor_2*(ysav*ysav)*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart);
  
}

void Generalized_Coloring_Method24()
{
  //wsprintf (cstr, "step 1");
	//MessageBox(NULL, cstr, "Debug", MB_OK);

	__real__ z = xsav;
	__imag__ z = ysav;

	__real__ c = x;
	__imag__ c = y;

  //wsprintf (cstr, "step 2");
	//MessageBox(NULL, cstr, "Debug", MB_OK);

	rj = (50*dFactor_2*fabs(sum_sqrs_z()-
		sum_sqrs_c())*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart);

	//temp = sum_sqrs_z();

  //wsprintf (cstr, "step 2.11");
	//MessageBox(NULL, cstr, "Debug", MB_OK);

	//temp = temp - sum_sqrs_c();

  //wsprintf (cstr, "step 2.12");
	//MessageBox(NULL, cstr, "Debug", MB_OK);

	//temp = fabs(temp);
	
  //wsprintf (cstr, "step 2.2");
	//MessageBox(NULL, cstr, "Debug", MB_OK);

	//rj = 50*dFactor_2*temp*(double)nRed+(double)nRedStart+
	//	rj*(double)nRed+(double)nRedStart;

  //wsprintf (cstr, "step 3");
	//MessageBox(NULL, cstr, "Debug", MB_OK);

	gj = (50*dFactor_2*fabs(xsav*xsav*2-
		sum_sqrs_c())*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart);
	bj = (50*dFactor_2*fabs(ysav*ysav*2-
		sum_sqrs_c())*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart);

  //wsprintf (cstr, "step 4");
	//MessageBox(NULL, cstr, "Debug", MB_OK);


}

void Generalized_Coloring_Method25()
{
	__real__ c = x;
	__imag__ c = y;

	rj += (200*dFactor_2*fabs(ysav*__imag__ c)*(double)nRed+(double)nRedStart);
	gj += (200*dFactor_2*fabs(xsav*__real__ c)*(double)nGrn+(double)nGrnStart);
	bj += (200*dFactor_2*fabs(xsav*ysav)*(double)nBlu+(double)nBluStart);

}

void Generalized_Coloring_Method26()
{
	__real__ c = x;
	__imag__ c = y;

	rj = 200*dFactor_2*xsav*ysav-
		sum_sqrs_c()*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart;

	gj = 200*dFactor_2*xsav*xsav-
		sum_sqrs_c()*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart;

	bj = 200*dFactor_2*ysav*ysav-
		sum_sqrs_c()*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart;
}

void Generalized_Coloring_Method27()
{
	// Generalized Coloring Method	
	rj = (200*dFactor_2*xsav*ysav*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart);
	gj = (200*dFactor_2*xsav*xsav*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart);
	bj = (200*dFactor_2*ysav*ysav*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart);
}

void Generalized_Coloring_Method28()
{
	__real__ z = xsav;
	__imag__ z = ysav;

	__real__ c = x;
	__imag__ c = y;

	rj = (int) (200*dFactor_2*fabs(sum_sqrs_z()-
		sum_sqrs_c())*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart);
	gj = (int) (200*dFactor_2*fabs(xsav*xsav*2-
		sum_sqrs_c())*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart);
	bj = (int) (200*dFactor_2*fabs(ysav*ysav*2-
		sum_sqrs_c())*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart);
}

void Generalized_Coloring_Method29()
{
	rj = (rj*(double)nRed*dFactor_2+(double)nRedStart);
	gj = (gj*(double)nGrn*dFactor_2+(double)nGrnStart);
	bj = (bj*(double)nBlu*dFactor_2+(double)nBluStart);	

}

void Generalized_Coloring_Method30()
{
	gj = (rj*(double)nRed*dFactor_2+(double)nRedStart);
	rj = (gj*(double)nGrn*dFactor_2+(double)nGrnStart);
	bj = (bj*(double)nBlu*dFactor_2+(double)nBluStart);	

}

void Generalized_Coloring_Method31()
{
	// Generalized Coloring Method	
	bj = (200*dFactor*fabs(xsav*ysav)*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart);
	gj = (200*dFactor*fabs(xsav*xsav)*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart);
	rj = (200*dFactor*fabs(ysav*ysav)*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart);

}

void Generalized_Coloring_Method32()
{
	// Generalized Coloring Method	
	bj = (200*dFactor_2*fabs(xsav*ysav)*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart);
	rj = (200*dFactor_2*fabs(xsav*xsav)*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart);
	gj = (200*dFactor_2*fabs(ysav*ysav)*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart);

}

void Generalized_Coloring_Method33()
{
	// Generalized Coloring Method	
	rj = (200*dFactor_2*fabs(xsav*ysav)*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart);
	gj = (200*dFactor_2*fabs(xsav*xsav)*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart);
	bj = (200*dFactor_2*fabs(ysav*ysav)*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart);

}

void Generalized_Coloring_Method34()
{
	rj += (dFactor_2*5*(double)nRed*fabs(xsav+ysav)+(double)nRedStart);
	gj += (dFactor_2*5*(double)nGrn*fabs(xsav+xsav)+(double)nGrnStart);
	bj += (dFactor_2*5*(double)nBlu*fabs(ysav+ysav)+(double)nBluStart);
				
}

void Generalized_Coloring_Method35()
{
	rj += (dFactor_2*5*(double)nRed*fabs(xsav*ysav)+(double)nRedStart);
	gj += (dFactor_2*5*(double)nGrn*fabs(xsav*xsav)+(double)nGrnStart);
	bj += (dFactor_2*5*(double)nBlu*fabs(ysav*ysav)+(double)nBluStart);

}

void Generalized_Coloring_Method36()
{
	rj = (200*dFactor_2*(cos(fabs(xsav*xsav)))*(double)nRed+(double)nRedStart+
			rj*(double)nRed+(double)nRedStart);
	gj = (200*dFactor_2*(cos(fabs(xsav*ysav)))*(double)nGrn+(double)nGrnStart+
			gj*(double)nGrn+(double)nGrnStart);
	bj = (200*dFactor_2*(cos(sum_sqrs_z()))*(double)nBlu+(double)nBluStart+
			bj*(double)nBlu+(double)nBluStart);
						
}

void Generalized_Coloring_Method37()
{
	__real__ z = xsav;
	__imag__ z = ysav;

	rj = (200*dFactor_2*(cos(sum_sqrs_z()))*(double)nRed+(double)nRedStart+
			rj*(double)nRed+(double)nRedStart);
	gj = (200*dFactor_2*(sin(fabs(xsav*ysav)))*(double)nGrn+(double)nGrnStart+
			gj*(double)nGrn+(double)nGrnStart);
	bj = (200*dFactor_2*(cos(fabs(ysav*xsav)))*(double)nBlu+(double)nBluStart+
			bj*(double)nBlu+(double)nBluStart);
}

void Generalized_Coloring_Method38()
{
	rj = (100*dFactor_2*(fabs(atan(xsav/ysav)))*(double)nRed+(double)nRedStart+
			rj*(double)nRed+(double)nRedStart);
	gj = (100*dFactor_2*(fabs(atan(xsav/ysav)))*(double)nGrn+(double)nGrnStart+
			gj*(double)nGrn+(double)nGrnStart);
	bj = (100*dFactor_2*(fabs(atan(ysav/xsav)))*(double)nBlu+(double)nBluStart+
			bj*(double)nBlu+(double)nBluStart);					
}

void Generalized_Coloring_Method39()
{
	rj = (50*dFactor_2*(fabs(xsav*xsav))*(double)nRed+(double)nRedStart+
		rj*(double)nRed+(double)nRedStart);
	gj = (50*dFactor_2*(fabs(xsav*xsav))*(double)nGrn+(double)nGrnStart+
		gj*(double)nGrn+(double)nGrnStart);
	bj = (50*dFactor_2*(fabs(ysav*ysav))*(double)nBlu+(double)nBluStart+
		bj*(double)nBlu+(double)nBluStart);
					
}

///////////////////////////////////////////////
///////////////////////////////////////////////

double x_y_to_degrees(double x_, double y_)
{
	double a;

	if (x_ >= 0 && y_ >= 0)
		a = atan(y_/x_);				// Q0
	else
	if (x_ < 0 && y_ >= 0)
		a = atan(y_/x_)+pi;			// Q1
	else
	if (x_ < 0 && y_ < 0)		
		a = atan(y_/x_)+pi;			// Q3
	else
		a = atan(y_/x_)+2*pi;		// Q4

	return a*rad;
}
