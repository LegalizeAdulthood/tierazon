///////////////////////////////////////////////////////////////
// Formula.c
//
// By: stephen c. ferguson
// http://home1.gte.net/itriazon/
// email: itriazon@gte.net
//
/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

#include <math.h>
#include "Talis_F.h"

#define DUAL_BFACTOR 3
#define OFFSET_COLOR 64

///////////////////////////////////////////////////////////////
// Complex Functions
///////////////////////////////////////////////////////////////

inline __complex__ double clog(__complex__ double Z)
{
   //cmplx(log(ABS(sum_sqrs(Z),atan2(y,x));}

   __real__ Z = log((sqrt(__real__ z*__real__ z + __imag__ z*__imag__ z)));
   __imag__ Z = atan2(__imag__ z, __real__ z);

   return Z;
}

inline __complex__ double ccos(__complex__ double Z)
{
  __real__ Z = .5*(exp(__imag__ z)+1./exp(__imag__ z))*cos(__real__ z);
  __imag__ Z = -sin(__real__ z)*.5*(exp(__imag__ z)-1./exp(__imag__ z));
  return Z;
}

inline __complex__ double csin(__complex__ double Z)
{
  __real__ Z = .5*(exp(__imag__ z)+1./exp(__imag__ z))*sin(__real__ z);
  __imag__ Z = cos(__real__ z)*.5*(exp(__imag__ z)-1./exp(__imag__ z));
  return Z;
}

inline double sum_sqrs_z()
{
  return __real__ z * __real__ z  + __imag__ z * __imag__ z;
}

inline double sum_sqrs_z1()
{
  return __real__ z1 * __real__ z1  + __imag__ z1 * __imag__ z1;
}

inline double sum_sqrs_z3()
{
  return __real__ z3 * __real__ z3  + __imag__ z3 * __imag__ z3;
}

inline double sum_sqrs_zd()
{
  return __real__ zd * __real__ zd  + __imag__ zd * __imag__ zd;
}

inline double real_csin_z4()
{
	return .5*(exp(__imag__ z4)+1./exp(__imag__ z4))*sin(__real__ z4);
}

inline double imag_csin_z4()
{
  return cos(__real__ z4)*.5*(exp(__imag__ z4)-1./exp(__imag__ z4));
}

////////////////////////////////////////////////////////////////
void Formula_00()
{
  ytot = xtot = (double)4/(double)PALSIZE;
  n_color = ABS(__real__ c / xtot) + ABS(__imag__ c / ytot);
  if (filter) Do_Filter();
}

void Formula_01()  // z=z*z+1;
{
  while( n_color++ < maxit
    && sum_sqrs_z() < bailout)
  {
    if (filter) Do_Filter();
    z=z*z+c;
  }
}

////////////////////////////////////////////////////
void Formula_02()  // Newton-Julia-Nova
{
  z = 1;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
    z1 = z*z;
    z=z-((z*z1-1)/(3*z1))+c;
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_03()  // Phoenix
{
  __real__ c1 = 0;
  __imag__ c1 = 1;

  if (jul == 0)
  {
    c*=c1;
    z*=c1;           // ??
  }
  else
  if (jul_save == 0)
  {
    //__imag__ c = -0.564;  // -.563
    //__real__ c = 0;

    c*=c1;
    z*=c1;
  }
  else
  {
    z*=c1;
  }

  //__real__ c = 0.563;   // Paul Carlson's point
  //__real__ c = 0.56667; // Ushiki's / Pickover's point

  z2=0;

  while( n_color++ < maxit
    && sum_sqrs_z() < bailout)
  {
    z  = z*z - .5*z  + c;
    z1 = z*z - .5*z2 + c;
    z2 = z;
    z  = z1;

    if (filter) Do_Filter();
  }
}

void Formula_04()  // Talis
{
  while( n_color++ < maxit
    && sum_sqrs_z() < bailout)
  {
    z=(z*z)/(1+z)+c;
    if (filter) Do_Filter();
  }
}

void Formula_05()  // 
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
    z1 = z*z;
		z=((z*z1-z-1)/(3*z1-1)-z)*c;  //
    z3 = z-z2;
		d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_06()  // 
{
  if (jul == 0)
	  z = 0;
	d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
		z1=z*z;
		z = z-((z*z1)+(c-1)*z-c)/(3*(z1)+c-1);
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_07()
{
  z=0;
  d=1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
		z = z-((z*z*z)+(c-1)*z-c)/(3*(z*z)+c-1);					
		z=z+c;
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_08()
{
  z = 1;
	d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
    z1=z*z*z;
    z=z-(z*z1-z)/(4*z1-1)+c;				
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_09()
{
	z = 1;
	d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
    z1=z*z*z;
    z=z-(z*z1-z)/(4*z1-z)+c;
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_10()
{
	while( n_color++ < maxit
    && sum_sqrs_z() < bailout)
  {
    z=z*z*z+c;
    if (filter) Do_Filter();
  }
}

void Formula_11()
{
	while( n_color++ < maxit
    && sum_sqrs_z() < bailout)
  {
    z=z*z*z*z+c;
    if (filter) Do_Filter();
  }
}

void Formula_12()
{
	while( n_color++ < maxit
    && sum_sqrs_z() < bailout)
  {
    z=z*z*z*z*z+c;
    if (filter) Do_Filter();
  }
}

void Formula_13()
{
	while( n_color++ < maxit
    && sum_sqrs_z() < bailout)
  {
    z=z*z*z*z*z*z+c;
    if (filter) Do_Filter();
  }
}

void Formula_14()
{
  z2 = 1;
	while( n_color++ < maxit
    && sum_sqrs_z() < bailout)
  {
    z1 = z*z+c;
    z  = z*z+c*z2;
    z2 = z1;
    if (filter) Do_Filter();
  }
}

void Formula_15()  // Phoenix II, from Roger T. Stevens
{
  __real__ c1 = 0;
  __imag__ c1 = 1;

  if (jul == 0)
  {
    c*=c1;
    z*=c1;           // ??
  }
  else
  if (jul_save == 0)
  {
    c*=c1;
    z*=c1;
  }
  else
  {
    z*=c1;
  }

  z2 = 0;
	while( n_color++ < maxit
    && sum_sqrs_z() < bailout)
  {
    z1 = z;
    z = z*z+__real__ c+__imag__ c*z2;
    z2 = z1;

    if (filter) Do_Filter();
  }
}

void Formula_16()  // Phoenix III, variation
{
  __real__ c1 = 0;
  __imag__ c1 = 1;

  if (jul == 0)
  {
    c*=c1;
    z*=c1;           // ??
  }
  else
  if (jul_save == 0)
  {
    c*=c1;
    z*=c1;
  }
  else
  {
    z*=c1;
  }

  z2 = 0;
	while( n_color++ < maxit
    && sum_sqrs_z() < bailout)
  {
    z1 = z;
    z = z*z*z + __real__ c + __imag__ c * z2;
    //z = z*z + __real__ c + __imag__ c * z2;
    z2 = z1;

    if (filter) Do_Filter();
  }
}

void Formula_17()  // Phoenix IV, variation
{
  __real__ c1 = 0;
  __imag__ c1 = 1;

  //z2 = z;

  if (jul == 0)
  {
    c*=c1;
  }
  else
  if (jul_save == 0)
  {
    c*=c1;
    z*=c1;
  }
  else
  {
    z*=c1;
  }

  z2 = z;

	while( n_color++ < maxit
    && sum_sqrs_z() < bailout)
  {
    z1 = z;
    z = z*z*z + .5 * __real__ c + __imag__ c * z2;
    z2 = z1;
    if (filter) Do_Filter();
  }
}

void Formula_18()  // Newton M-Set, Explanation by Paul Carlson
{
  /*
From - Sun Nov 09 16:15:28 1997
Path: news.gte.net!newsfeed.gte.net!europa.clark.net!199.0.154.56!ais.net!ix.netcom.com!news
From: pjcarlsn@ix.netcom.com (Paul and/or Joyce Carlson)
Newsgroups: alt.binaries.pictures.fractals
Subject: Fractal: Newton Msets Explained
Date: Sun, 09 Nov 1997 21:54:12 GMT
Organization: Netcom
Lines: 72
Expires: 30 days
Message-ID: <6457u5$p8p@sjx-ixn2.ix.netcom.com>
NNTP-Posting-Host: ftc-co2-12.ix.netcom.com
X-NETCOM-Date: Sun Nov 09 12:54:29 PM PST 1997
X-Newsreader: Forte Free Agent 1.0.82
Xref: news.gte.net alt.binaries.pictures.fractals:9670

Quite often in the past when I've posted a zoom into a
Newton Mset I've received a message or two asking me exactly
what a Newton Mset is, and how to go about programming
or writing a formula for one.  Because I plan on posting
several of them in the near future, I thought I'd save
some time by posting an explanation in advance.

The Newton method is a numerical method of solving for
the roots of real or complex valued polynomial equations.
An initial guess is made at a root and then the method is
iterated, producing new values that (hopefully) converge
to a root of the equation.

The traditional Newton fractal is similar to a Julia set
in that the pixel values are used as the initial values
(or guesses).  A typical equation that is used to produce
a traditional Newton fractal is:

    Z^3 - 1 = 0

On the other hand, what I call the Newton Mset method
solves for the roots of an equation in which the pixel
value appears in the equation.  For example, in this
equation the pixel value is denoted as C:

    Z^3 + C*Z^2 - Z + C = 0

Because C has a different value for every pixel, the
method actually solves a different equation for every
pixel.  Now the question is what to use for the initial
guess for each solution.  The answer is to use one of
the "critical points."  These are the values of Z for
which the second derivative vanishes and can be found
by setting the second derivative of the equation to
zero and solving for Z.  In the example equation
above:

    The function:          f(Z)   = Z^3 + C*Z^2 - Z + C
    The first derivative:  f'(Z)  = 3*Z^2 + 2*C*Z - 1
    The second derivative: f''(Z) = 6*Z + 2*C
    Therefore,  setting 6*Z + 2*C = 0 we have Z = -C/3

The variable Z is initialized to -C/3 prior to the
iteration loop.  From there, everything proceeds as
usual using the general Newton Method formula:

    Z[n+1] = Z[n] - f(Z[n]) / f'(Z[n])

A root is assumed to be found when Z[n] and Z[n+1] are
very close together.

In the Newton Mset fractals that I will be posting the
colors of the pixels have nothing to do with which
root a pixel converged to, unlike the more traditional
coloring method.

I hope this helps someone.

Regards,

Paul Carlson
------------------------------------------------------------------
                email   pjcarlsn@ix.netcom.com

WWW Fractal Galleries   http://sprott.physics.wisc.edu/carlson.htm
                        http://fractal.mta.ca/fractals/carlson/
                        http://www.cnam.fr/fractals/carlson.html

        anonymous FTP   ftp.cnam.fr   /pub/Fractals/carlson
------------------------------------------------------------------
*/

  z = -z/3;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
    z1 = z*z;
    z=z-(z*z1+z1*c-z+c)/(3*z1+2*c*z-1);
    //z=z1*z1+c;
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_19()
{
  z = -z/3;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;

    z=z-(z*z*z+c*z*z+z+c)/(3*z*z+2*c*z+1);

    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_20()  // testing
{

  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z*z*z*z - z*z*z*c - z - c;  // the function
  z'  = 4*z*z*z - 3*z*z*c - 1;      // 1st derivative
  z'' = 12*z*z - 6*z*c;             // 2nd derivative

  12*z*z = 6*z*c;
  z   = (6*z*c)/(12*z);             // solve for z
  z   = c/2;

  */

  z = z/2;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
    z1 = z*z;
    z=z-(z1*z1 - z1*z*c - z - c)/(4*z*z1 - 3*z1*c - 1);
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_21()  // testing
{

  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z*z*z*c + z*z + z + c;  // the function
  z'  = 3*z*z*c + 2*z + 1;      // 1st derivative
  z'' = 6*z*c   + 2;            // 2nd derivative

  6*z*c = -2;
  z     = -2/(6*c);             // solve for z
  z     = -1/(3*c)

  */

  z = -1/(3*z);
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
    z1 = z*z;
    z =z-(z*z1*c + z1 + z + c)/(3*z1*c + 2*z + 1);
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_22()  // testing
{
  /*
  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z*z*z*z*c + z*z*z*c + z + c;  // the function
  z'  = 4*z*z*z*c + 3*z*z*c + 1    ;  // 1st derivative
  z'' = 12*z*z*c  + 6*z*c          ;  // 2nd derivative

  6*z*c = -12*z*z*c;
  z     = -(12*z*z*c)/(6*c);
  z     = -2*z*z;

	12*z*z*c = -6*z*c;

  z     = -(6*z*c)/(12*z*c);


  */

  //z     = -2*z*z;
  //z     = -(6*z*c)/(12*z*c);

  if (jul == 0)
    z = -.5;

  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
    z1 = z*z;
    z  = z2;
    z =z-(z1*z1*c + z1*z*c + z + c)/(4*z1*z*c + 3*z1*c + 1);
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_23()  // testing
{
  /*
  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z*z*z*z*c + z*z*z + z + c;  // the function
  z'  = 4*z*z*z*c + 3*z*z + 1    ;  // 1st derivative
  z'' = 12*z*z*c  + 6*z          ;  // 2nd derivative

	12*z*z*c = -6*z;

  z     = -(6*z)/(12*z*c);
  z     = =z/(2*z*c);
  z     = -.5/c;

  */

  z = -.5/z;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
    z1 = z*z;
    z =z-(z1*z1*c + z1*z + z + c)/(4*z1*z*c + 3*z1 + 1);
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_24()  // testing
{
  /*
  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z*z*z + z*z*c + c;  // the function
  z'  = 3*z*z + 2*z*c    ;  // 1st derivative
  z'' = 6*z + 2*c        ;  // 2nd derivative

	6*z = -2*c;
  z     = -2*c/6;

  */

  z = -z/3;

  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
    z1 = z*z;
    z =z-(z1*z + z1*c + c)/(3*z1 + 2*z*c);
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_25()  // testing
{
  /*
  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z*z*z*z + z*z*z*c + c;  // the function
  z'  = 4*z*z*z + 3*z*z*c    ;  // 1st derivative
  z'' = 12*z*z  + 6*z*c      ;  // 2nd derivative

	12*z*z = -6*z*c;
  z      = -(6*z*c)/(12*z);
  z      = -c/2;

  */

  z = -z/2;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
    z1 = z*z;
    z =z-(z1*z1 + z1*z*c + c)/(4*z1*z + 3*z*z*c);
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_26()  // testing
{
  /*
  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z*z*z*z*z + z*z*z*z*c + c;  // the function
  z'  = 5*z*z*z*z + 4*z*z*z*c    ;  // 1st derivative
  z'' = 20*z*z*z  + 12*z*z*c      ;  // 2nd derivative

	20*z*z*z = -12*z*z*c;
  z        = -(12*z*z*c)/(20*z*z);
  z        = -(6*c)/10;
  z        = -(3*c)/5;


  */

  //if (jul == 0)

  z = -(3*z)/5;

  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z2 = z;
    z1 = z*z;
    z4 = z1*z1;
    z =z-(z4*z + z4*c + c)/(5*z4 + 4*z1*z*c);
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_27()  // testing
{
  /*
  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z*z*z*z*z*z*z + z*z*z*z*z*z*c + c;  // the function
  z'  = 7*z*z*z*z*z*z + 6*z*z*z*z*z*c    ;  // 1st derivative
  z'' = 42*z*z*z*z*z  + 30*z*z*z*z*c     ;  // 2nd derivative

	42*z*z*z*z*z = -30*z*z*z*z*c;
  z            = -(30*z*z*z*z*c)/(42*z*z*z*z);
  z            = -(15*c)/21;
  z            = -(5*c)/7;

  */

  //if (jul == 0)

  z = -(5*z)/7;

  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z1 = z;
    z2 = z*z;
    z5 = z2*z2*z;
    z =z-(z5*z2 + z5*z*c + c)/(7*z5*z + 6*z5*c);
    z3 = z-z1;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}


void Formula_28()  // 9th order Newton Mset
{
  /*
  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z*z*z*z*z*z*z*z*z + z*z*z*z*z*z*z*z*c + c;  // the function
  z'  = 9*z*z*z*z*z*z*z*z + 8*z*z*z*z*z*z*z*c    ;  // 1st derivative
  z'' = 72*z*z*z*z*z*z*z  + 56*z*z*z*z*z*z*c     ;  // 2nd derivative

	72*z*z*z*z*z*z*z = -56*z*z*z*z*z*z*c;
  z                = -(56*z*z*z*z*z*z*c)/(72*z*z*z*z*z*z);
  z                = -(7*c)/9;

  */

  //if (jul == 0)

  z = -(7*z)/9;

  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    z5 = z2*z2*z;
    z8 = z4*z4;
    z =z-(z5*z4 + z8*c + c)/(9*z8 + 8*z5*z2*c);
    z3 = z-z1;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_29()  // 13th order Newton Mset
{
  /*
  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z^13         + (z^12)*c + c;    // the function
  z'  = 13*(z^12)    + 12*(z^11)*c;     // 1st derivative
  z'' = 12*13*(z^11) + 11*12*(z^10)*c;  // 2nd derivative

  12*13*(z^11) = -11*12*(z^10)*c;
  z            = -(11*12*(z^10)*c)/(12*13*(z^10));
               = -(11*12*c)/(12*13);
               = -11*c/13;

  */

  //if (jul == 0)

  z = -(11*z)/13;

  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    z5 = z2*z2*z;
    z8 = z4*z4;
    z =z-(z8*z4*z + z8*z4*c + c)/(13*z8*z4 + 12*z8*z2*z*c);
    z3 = z-z1;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_30()  // Testing again
{
  /*
  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z^9          + (z^8)*c + c;     // the function
  z'  = 9*(z^8)      + 8*(z^7)*c;       // 1st derivative
  z'' = 72*(z^6)     + 56*(z^6)*c;      // 2nd derivative

  72*(z^6)     = -56*(z^6)*c;
  z            = -(56*(z^6)*c)/(72*(z^6));
               = -(28*c)/36;
               = -(14*c)/18;
               = -(7*c)/9;

  */

  //if (jul == 0)

  z = -(z*7)/9;

  //z=0;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z1 = z;
    z2 = z*z;
    z3 = z2*z;
    z4 = z2*z2;
    z =z-(z4*z4*z + z4*z4*c + c)/(9*z4*z4 + 8*z4*z3*c);
    zd = z-z1;
    d  = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_31()  // Newton Diamond
{

  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z^5      + (z^4)*c   + z + c;  // the function
  z'  = 5*(z^4)  + 4*(z^3)*c + 1;      // 1st derivative
  z'' = 20*(z^3) + 12*(z^2)*c;         // 2nd derivative

  20*(z^3) = -12*(z^2)*c;
  z   = -(12*(z^2)*c)/(20*(z^2));       // solve for z
  z   = -(3*c)/5;

  */

  z = -(3*z)/5;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z1 = z;
    z2 = z*z;
    z=z-(z2*z2*z + z2*z2*c + z + c)/(5*z2*z2 + 4*z2*z*c + 1);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_32()  // Newton Pentagon
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z^6      + (z^5)*c   + z + c;  // the function
  z'  = 6*(z^5)  + 5*(z^4)*c + 1;      // 1st derivative
  z'' = 30*(z^4) + 20*(z^3)*c;         // 2nd derivative

  30*(z^4) = -20*(z^3)*c;
  z   = -(20*(z^3)*c)/(30*(z^3));      // solve for z
  z   = -(2*c)/3;

  */

  z = -(2*z)/3;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    z=z-(z4*z2 + z4*z*c + z + c)/(6*z4*z + 5*z4*c + 1);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_33()  // Newton Hexagon
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z^7      + (z^6)*c   + z + c;  // the function
  z'  = 7*(z^6)  + 6*(z^5)*c + 1;      // 1st derivative
  z'' = 42*(z^5) + 30*(z^4)*c;         // 2nd derivative

  42*(z^5) = -30*(z^4)*c;
  z   = -(30*(z^4)*c)/(42*(z^4));      // solve for z
  z   = -(5*c)/7;

  */

  z = -(5*z)/7;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    z=z-(z4*z2*z + z4*z2*c + z + c)/(7*z4*z2 + 6*z4*z*c + 1);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_34()  // Newton Octagon
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  f(z) = z - z/z'

  z   = z^9      + (z^8)*c   + z + c;  // the function
  z'  = 9*(z^8)  + 8*(z^7)*c + 1;      // 1st derivative
  z'' = 72*(z^7) + 56*(z^6)*c;         // 2nd derivative

  72*(z^7) = -56*(z^6)*c;
  z   = -(56*(z^6)*c)/(72*(z^6));      // solve for z
  z   = -(7*c)/9;

  */

  z = -(7*z)/9;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    z=z-(z4*z4*z + z4*z4*c + z + c)/(9*z4*z4 + 8*z4*z2*z*c + 1);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_35()  // Testing
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  z = z - f(z)/f(z')

  z   =  z^13         + z^12*c - z;        // the function
  z'  =  13*z^12      + 12*(z^11)*c - 1;        // 1st derivative
  z'' =  12*13*(z^11) + 12*11*(z^10)*c;       // 2nd derivative

  12*13*(z^11) = -12*11*(z^10)*c;
  z            = -11*(z^10)*c/(13*(z^10));
  z            = -11*c/13;

  */

  z = -11*z/13;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
    && d < maxsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    z8 = z4*z4;
    z12= z8*z4;
    z  = z-(z12*z + z12*c - z)/(13*z12 + 12*z4*z4*z2*z*c - 1);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_36()  // Testing
{

  //a = 1;
  //b = 1;

  __real__ c = .1;
  __imag__ c = .1;
  z=c;

  //__real__ z = 1;
  //__imag__ z = 1;

  while( n_color++ < maxit )
//    && sum_sqrs_z() < bailout)
  {
    //if (filter) Do_Filter();

    a=__real__ z;
    b=__imag__ z;

    z=z+z;


    //z=z+c;

  }
}


