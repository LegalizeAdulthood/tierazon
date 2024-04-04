//
Complex C++ Utilities

from C Mathematical Function Handbook by Louis Baker
Copyright 1991 by Louis Baker. All rights reserved.

*/

#include "stdafx.h"
#include <math.h>
#include "cmplx.h"

cmplx::cmplx( double xx , double yy) // constructor
         { x=xx;y=yy;}

cmplx::cmplx() // constructor
         { x=0.;y=0.;bio=0;}

//double cmplx::sum_of_sqrs()
//	{ return (x*x+y*y);}

//double cmplx::abs()
//	{ return sqrt(x*x+y*y);}

//double cmplx::real()
//	{ return x; }

//double cmplx::imag()
//	{ return y; }

//double cmplx::imaginary()
//	{ return y; }

double cmplx::squares()
{
	if (bio)	
	{
		if (bio == 1)
		{
			if (fabs(x) > fabs(y))
				return sqrt(2*x*x);
			else
				return sqrt(2*y*y);
		}
		else
		if (bio == 2)
			return sqrt(2*x*y);
		else
		if (bio == 3)
		{
			if (fabs(x) > fabs(y))
				return sqrt(2*y*y);
			else
				return sqrt(2*x*x);
		}
		else
		if (bio == 4)
		{
			if (fabs(x) > fabs(y))
				return 2*x*x;
			else
				return 2*y*y;
		}
		else
		if (bio == 5)
			return 2*x*y;
		else
		{
			if (fabs(x) > fabs(y))
				return 2*y*y;
			else
				return 2*x*x;
		}
	}
	else
		return (x*x+y*y);
}

double cmplx::magnitude()
{
	if (bio)	
	{
		if (bio == 1)
		{
			if (fabs(x) > fabs(y))
				return sqrt(2*x*x);
			else
				return sqrt(2*y*y);
		}
		else
		if (bio == 2)
			return sqrt(2*x*y);
		else
		if (bio == 3)
		{
			if (fabs(x) > fabs(y))
				return sqrt(2*y*y);
			else
				return sqrt(2*x*x);
		}
		else
		if (bio == 4)
		{
			if (fabs(x) > fabs(y))
				return 2*x*x;
			else
				return 2*y*y;
		}
		else
		if (bio == 5)
			return 2*x*y;
		else
		{
			if (fabs(x) > fabs(y))
				return 2*y*y;
			else
				return 2*x*x;
		}
	}
	else
		return sqrt(x*x+y*y);
}

double cmplx::biotest()
	{ return (bio*x*y);}

void cmplx::set_biomorph(double dBiomorph)
	{ bio = dBiomorph;} 

void cmplx::set_real(double set_x)
	{ x = set_x;} 

void cmplx::set_imag(double set_y)
	{ y = set_y;} 

//cmplx cmplx::cexp()
//{
//	static double scale;
//	scale= x;

	//if( x > topexp)
	//	return cmplx( errorcode,0.);
	//if( x<-topexp)
	//	return cmplx( 0.,0.);

//	scale= exp((scale));
//	return cmplx(scale*cos(y),scale*sin(y));

//	return cmplx(exp(x)*cos(y),exp(x)*sin(y));

//}

//cmplx cmplx::clog()
//{
//	static double mant,arg,mag;mag=(*this).abs();
	
//	mag=fabs(mag); // ??

//	if( mag < zerotol )
//		return cmplx(errorcode,0.);

//	mant = log(mag);
//	arg= atan2(y,x);
//	return cmplx(mant,arg);

//	return cmplx(log(fabs((*this).abs())),atan2(y,x));
//}

//cmplx cmplx::operator^(double expon)
//{
	//	static cmplx z;
	//	z= (*this).clog( ) * expon;
	//	return z.cexp();

//	return ((*this).clog( ) * expon).cexp();
//}

//cmplx cmplx::operator^(cmplx expon)
//{
	//	static cmplx z;
	//	z= (*this).clog( ) * expon;
	//	return z.cexp();

//	return ((*this).clog( ) * expon).cexp();
//}

cmplx cmplx::csin()
{
	return cmplx(.5*(exp(y)+1./exp(y))*sin(x),cos(x)*.5*(exp(y)-1./exp(y)));
}

cmplx cmplx::ccos()
{
//	static double z,zi,sinh,cosh,real;
//	static double z,zi;
	//real=x;

	//if( y> topexp)
	// 	return cmplx( errorcode,0.);
	//if( y<-topexp)
	// 	return cmplx( 0.,0.);

//	z=exp(y);
//	zi=1./z;
//	cosh=.5*(z+zi);
//	sinh=.5*(z-zi);

//	return cmplx(cosh*cos(x),-sin(x)*sinh);
	return cmplx(.5*(exp(y)+1./exp(y))*cos(x),-sin(x)*.5*(exp(y)-1./exp(y)));
}

cmplx cmplx::csin_error() 
{
	if( y> topexp)
		return cmplx( errorcode,0.);
	if( y<-topexp) 
		return cmplx( 0.,0.);			
	return cmplx(.5*(exp(y)+1./exp(y))*sin(x),cos(x)*.5*(exp(y)-1./exp(y)));
}

cmplx tangent ( cmplx& x)
{
	return x.csin()/x.ccos();
}

cmplx sinh(cmplx& x)
{
	static cmplx i(0.,1.);
	return  -i * ( x*i).csin();
}

//cmplx tanh(cmplx& x)
//{
//	cmplx i(0.,1.);
//	return -i * tangent( x*i);
//}

cmplx asin(cmplx&x)
{
	//	static cmplx i(0.,1.);
	//	return      -i * (i*x+ ((1.-x*x)^.5)).clog();

	return -cmplx(0.,1.) * (cmplx(0.,1.)*x+ ((1.-x*x)^.5)).clog();
}

cmplx acos(cmplx&x)
{
	//	static cmplx i(0.,1.);
	//	return      -i * (x+ i*((1.-x*x)^.5)).clog();

	return -cmplx(0.,1.) * (x+ cmplx(0.,1.)*((1.-x*x)^.5)).clog();
}

cmplx arctan( cmplx& x)
{
//	static cmplx i(0.,1.),a;
// 	a= ( i+x )/(i-x);
// 	return .5 * i * a.clog();

 	return .5*cmplx(0.,1.)*(cmplx(0.,1.)+x)/(cmplx(0.,1.)-x).clog();
}

