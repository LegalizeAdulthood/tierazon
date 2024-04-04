////////////////////////////////////////////////////////////////
// rsx_math.c
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

void Formula_01()
{
  while( n_color++ < maxit
    && sum_sqrs_z() < bailout)
	//d = 1;
  //while( n_color++ < maxit
    //&& d > minsize)
		//&& d < bailout)
  {
		//z1 = z;
    z=z*z+c;
    //z3 = z-z1;
		//d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

////////////////////////////////////////////////////
void Formula_02()  // Newton-Julia-Nova
{
  if (jul == 0)	
		z = 1;

  d = 1;

  while( n_color++ < maxit
    && d > minsize)
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

	// Rotate it so its pointing upward
	z*=c1;
  c*=c1;

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
    && d > minsize)
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
    && d > minsize)
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
	if (jul == 0)
		z=0;
  d=1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z2 = z;
		//z = z-((z*z*z)+(c-1)*z-c)/(3*(z*z)+c-1);					
		//z=z+c;
		z = (z-((z*z*z+c*z-z-c)/(3*z*z+c-1)))+c;					
		//z=z+c;
    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_08()
{
	if (jul == 0)
		z = 1;
	d = 1;
  while( n_color++ < maxit
    && d > minsize)
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
	if (jul == 0)
  	z = 1;
	d = 1;
  while( n_color++ < maxit
    && d > minsize)
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
  __imag__ c1 = -1;

	// Rotate it so its pointing upward
	z*=c1;
  c*=c1;

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
  __imag__ c1 = -1;

	// Rotate it so its pointing upward
	z*=c1;
  c*=c1;

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
  __imag__ c1 = -1;

	// Rotate it so its pointing upward
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
		c*=c1;
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
    && d > minsize)
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
    && d > minsize)
  {
    z2 = z;

    z=z-(z*z*z+c*z*z+z+c)/(3*z*z+2*c*z+1);

    z3 = z-z2;
    d = sum_sqrs_z3();
    if (filter) Do_Filter();
  }
}

void Formula_20()
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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
    && d > minsize)
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

///////////////////////////////////////

void Formula_36()  // 70
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
	{
		z1 = z;	
		z3 = z*z*z;
		z=z-(z3*z*c-z+c)/(4*z3*c);
    zd = z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_37()  // 71
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
	{
		z1 = z;	
		z2 = z*z;
		z=z-(z*z2-z+c)/(3*z2);
    zd = z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_38()  // 72
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
	{
		z1 = z;	
		z2 = z*z;
		z=z-(z*z2*c-z*c-1)/(3*z2*c);
    zd = z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_39()  // 73
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
	{
		z1 = z;	
		z2 = z*z;
		z=z-(z*z2*c-z*z*c-1)/(3*z2*c);
    zd = z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_40()  // 74
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
	{
		z1 = z;	
		z2 = z*z;
		z=z-(z*z2*c-1)/(3*z2*c);
		z=z*z*c+c;
    zd = z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_41()  // 75
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
	{
		z1 = z;	
		z2 = z*z;
		z=z-(z*z2*c-z-1)/(3*z2*c-z);
    zd = z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_42()  // 76
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
	{
		z1 = z;	
		z2 = z*z;
		z=z-(z*z2*c-z*c-1)/(3*z2*c-z);
    zd = z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_43()  // 77
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
	{
		z1 = z;	
		z2 = z*z;
		z=z-(z*z2*c-z2-1)/(3*z2*c-3*z2-3*z);
    zd = z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_44()  // 78
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
	{
		z1 = z;	
		z2 = z*z;
		z=z-(z*z2*c-z2*c-1)/(3*z2*c-z*c-z);
    zd = z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_45()  // 105
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
	{
		z1 = z;
		z2=z*z;
		z=(z-(z*z2-z)/(3*z2-1));
		z=z*z*c;
    zd = z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_46()  // 16 Iterations
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize
		&& d < maxsize)
	{
		z1=z;
		z=z*c;
		z = ccos_z();
		z=z*c;
		zd = z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_47()  // Sharon 14
{
	//				z2	= z;
	//				z1	= ((z*z).csin())*z/2;
	//				z		= z1*z1 + c;

  d = 1;
  while( n_color++ < maxit
    && d > minsize
		&& d < maxsize)
  {
		z1=z;
		z = z*z;
		z = csin_z();
		z = z*z/2;
		z = z*z+c;
		zd = z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_48() 
{
	//  z=((z*z).csin()).clog()+c;			
  d = 1;
  while( n_color++ < maxit
    && d > minsize
		&& d < maxsize)
  {
		z1=z;
		z=z*z;
		z=csin_z();
		z=clog_z();
		z=z+c;
		zd=z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_49() 
{
	//  z = z*z*sin(z.real()) + c*z*cos(z.imag()) + c;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
		&& d < maxsize)
  {
		z1=z;
		z = z*z*sin(__real__ z) + c*z*cos(__imag__ z) + c; 
		zd=z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_50() 
{
	//  z=csin(z)*ccos(c);
	c=ccos_c();
  d = 1;
  while( n_color++ < maxit
    && d > minsize
		&& d < maxsize)
  {
		z1=z;
		z=csin_z();
		z=z*c;
		zd=z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

void Formula_51() 
{
	//  z=c*csin(z*z*z*z);
  d = 1;
  while( n_color++ < maxit
    && d > minsize
		&& d < maxsize)
  {
		z1=z;
		z=z*z;
		z=z*z;
		z=csin_z();
		z=z*c;
		zd=z-z1;
    d = sum_sqrs_zd();
		if (filter) Do_Filter();
	}
}

////////////////////////////////////////
void Formula_52()  // More Testing with the Newton Flower
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  z = z - f(z)/f(z')

  z   =  z^8        + z^7*c - z;        // the function
  z'  =  8*z^7      + 7*(z^6)*c - 1;        // 1st derivative
  z'' =  7*8*(z^6)  + 7*6*(z^5)*c;       // 2nd derivative

  7*8*(z^6) = -7*6*(z^5)*c;
  z            = -(6*(z^5)*c)/(8*(z^5));
  z            = -(6*c)/8;
  z            = -(3*c)/4;

  */

  z = -(3*z)/4;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    //z8 = z4*z4;
    //z12= z8*z4;
    z  = z-(z4*z4 + z4*z2*z1*c - z)/(8*z4*z2*z1 + 7*z4*z2*c - 1);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_53()  // More Testing with the Newton Flower
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  z = z - f(z)/f(z')

  z			=  (z^6)       + (z^5)*c - 1;        // the function
  z'		=  6*(z^5)     + 5*(z^4)*c;    // 1st derivative
  z''		=  30*(z^4)    + 20*(z^3)*c;							// 2nd derivative

  30*(z^3)	  = -20*(z^3)*c;
	z						= -20*c/30;
	z						= -2*c/3;

  */

	z				 = -(2*z)/3;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
		z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    //z8 = z4*z4;
    //z12= z8*z4;
    z = z-(z4*z2 + z4*z*c - 1)/(6*z4*z + 5*z2*z2*c);
    zd = z-z1;

    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_54()  // More Testing with the Newton Flower
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  z = z - f(z)/f(z')

  z   =  z^15        + z^14*c - z;        // the function
  z'  =  15*z^14      + 14*(z^13)*c - 1;        // 1st derivative
  z'' =  15*14*(z^13)  + 14*13*(z^12)*c;       // 2nd derivative

  15*14*(z^13) = -14*13*(z^12)*c;
  z            = -(13*(z^12)*c)/(15*(z^12));
  z            = -(13*c)/15;
  z            = -(13*c)/15;

  */

  z = -(13*z)/15;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    z8 = z4*z4;
    z12= z8*z4;
    z  = z-(z12*z2*z + z12*z2*c - z)/(15*z12*z2 + 14*z12*z*c - 1);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_55()  // A derivation of Newtons apple
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  z = z - f(z)/f(z')

  z   =  (z^4)*c        - z^3 - z^2;        // the function
  z'  =  4*(z^3)*c      - 3*(z^2) - 2*z;		// 1st derivative
  z'' =  12*(z^2)*c     - 6*z - 2;					// 2nd derivative
	z'' =  24*z*c - 6;												// 3rd derivative

  24*z*c = 6;
  z      = 6/24*c   
  z      = 1/(4*c)

  */

  z = 1/(4*z);
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    //z8 = z4*z4;
    //z12= z8*z4;
    z  = z-(4*z2*z*c - 3*z2 - 2*z)/(12*z2*c - 6*z - 2);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_56()  // More Testing with the Newton Flower
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  z = z - f(z)/f(z')

  z   =  z^25        + z^24*c - z;        // the function
  z'  =  25*z^24      + 24*(z^23)*c - 1;        // 1st derivative
  z'' =  25*24*(z^23)  + 24*23*(z^22)*c;       // 2nd derivative

  25*24*(z^23) = -24*23*(z^22)*c;
  z            = -(23*(z^22)*c)/(25*(z^22));
  z            = -(23*c)/25;
  z            = -(23*c)/25;

  */

  z = -(23*z)/25;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    z8 = z4*z4;
    z12 = z8*z4;
		z24 = z12*z12;
    z  = z-(z24*z + z24*c - z)/(25*z24 + 24*z12*z8*z2*z*c - 1);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_57()  // More Testing with the Newton Flower
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  z = z - f(z)/f(z')

  z   =  z^38        + z^37*c - z;        // the function
  z'  =  38*z^37      + 37*(z^36)*c - 1;        // 1st derivative
  z'' =  38*37*(z^36)  + 37*36*(z^35)*c;       // 2nd derivative

  38*37*(z^36) = -37*36*(z^35)*c;
  z            = -(36*(z^35)*c)/(38*(z^35));
  z            = -(36*c)/38;
  z            = -(18*c)/19;

  */

  z = -(18*z)/19;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    z8 = z4*z4;
    z12 = z8*z4;
		z24 = z12*z12;
		z36 = z24*z12;
    z  = z-(z36*z2 + z36*z*c - z)/(38*z36*z + 37*z36*c - 1);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_58()  // More Testing with the Newton Flower
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  z = z - f(z)/f(z')

  z   =  z^50        + z^49*c - z;        // the function
  z'  =  50*z^49      + 49*(z^48)*c - 1;        // 1st derivative
  z'' =  50*49*(z^48)  + 49*48*(z^47)*c;       // 2nd derivative

  50*49*(z^48) = -49*48*(z^47)*c;
  z            = -(48*(z^47)*c)/(50*(z^47));
  z            = -(48*c)/50;
  z            = -(24*c)/25;

  */

  z = -(24*z)/25;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    z8 = z4*z4;
    z12 = z8*z4;
		z24 = z12*z12;
		//z36 = z24*z12;
		z48 = z24*z24;
    z  = z-(z48*z2 + z48*z*c - z)/(50*z48*z + 49*z48*c - 1);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_59()  // A derivation of Newtons apple
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  z = z - f(z)/f(z')

  z'    =  6*(z^5)*c      + 5*(z^4) - 1;
  z''   =  30*(z^4)*c     + 20*(z^3);
	z''   =  120*(z^3)*c    + 60*(z^2);

  120*(z^3)*c = -60*(z^2);
  z       = -60/120*c   
  z       = -1/(2*c)

  */

  z = -1/(2*z);
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
    z2 = z*z;
    z4 = z2*z2;
    //z8 = z4*z4;
    //z12= z8*z4;
    z  = z-(6*z4*z*c + 5*z4 - 1)/(30*z4*c + 20*z2*z);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_60()  // A derivation of Newtons apple
{
  /*

  Solve the roots of the function.
  Initialize z to one of the roots.
  Apply Newton's method for solving roots.
  z = z - f(z)/f(z')

  z'    =  19*(z^18)*c      + 18*(z^17);
  z''   =  342*(z^17)*c     + 306*(z^16);
	z''   =  5814*(z^16)*c    + 4896*(z^15);

  5814*(z^16)*c = -4896*(z^15);
  z             = -4896/(5814*c);   

  */

  z = -4896/(5814*z);
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1  = z;
    z2  = z*z;
    z4  = z2*z2;
    z8  = z4*z4;
    //z12 = z8*z4;
		z16 = z8*z8; 
    z  = z-(19*z16*z2*c + 18*z16*z - z)/(342*z16*z*c + 306*z16 - 1);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

//////////////////////////////////

void Formula_61()
{
	if (jul == 0)
		z = 0;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1  = z;
    z=z*z+c;
		temp = __real__ z;
		__real__ z = __imag__ z;
		__imag__ z = temp;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_62()  // Flarium 94
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z2 = z*z;
    z=((z*z2-z-1)/(z2*z-1)-z)*c;   // 3rd order M-Set
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_63()		// Flarium 95
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z2 = z*z;
		z=((z2*z2-z2-1)/(4*z2-1)-z)*c;  // 
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_64()		// Flarium 96
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z2 = z*z;
    z=(z-(z*z2-1)/(3*z2-fabs(z)-1))*c;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_65()   // Flarium 97
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z2 = z*z;
		z=(z-(z*z2-1)/(3*z2-z-1))*c;  // Almost makes a connection
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_66()  // Flarium 98
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z3 = z*z*z;
    z=((z*z3-z-1)/(4*z3-z-1)-z)*c;  // Some strange curls
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_67()  // Inkblot 2
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z2 = z*z;
		z=z-((z*z2-z)/((3*z2-1)))+c;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_68()		// // Flarium 100
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z2 = z*z;
    z=(z-(z*z2-1)/(4*z2-z-1))*c;  
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_69()  // Flarium 101
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z2 = z*z;
 		z=(z-(z*z2-1)/(3*z2-z))*c;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_70()  // Flarium 102
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z3 = z*z*z;
		z=(z-(z*z3-1)/(4*z3-z))*c;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_71()  // Flarium 103
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z3 = z*z*z;
		z=(z-(z*z3-1)/(3*z3-z))*c;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_72()  // Flarium 104
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z3 = z*z*z;
		z=(z-(z*z3-z-1)/(3*z3-z))*c;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_73()  // Flarium 105
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
    z=c*(z-(z*z*z-z)/(3*z*z-1));  // 105
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_74()  // Flarium 106
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z3 = z*z*z;
    z=((1-z-z3*z)/(z-(4*z3))-z)*c;  // sort of a good one
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_75()  // Flarium 107
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z3 = z*z*z;
		z=((z-z3*z)/(z-(3*z3))-z)*c;  // 107
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_76()  // Flarium 108
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z3 = z*z*z;
		z=((z-z3)/(z-(3*z3))-z)*c;  // 108
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_77() // Flarium 109
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z2 = z*z;
	  z=((z2*z-1)/(2*z2-1)-z)*c;  // 109
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_78()  // Flarium 110
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z2 = z*z;
		z=((z*z2-z-1)/(3*z*z2-1)-z)*c; // 2nd Order M-Set 110
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_79()  // CBAP  F(z) = Z^3 - 3*(A^2)*Z + B(MOD 2)
{
	t=z;
	t3=3*t;
	t2=t*t;
	ca=(t2+1)/t3;
	//cb=2*ca*ca*ca+(t2-cmplx(2,0))/t3;
	cb=2*ca*ca*ca+(t2-2)/t3;
	caa3=ca*ca*3;

	if (jul == 0)
		z=-ca;
  
	d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z = z*z*z-caa3*z+cb;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_80()  // Flarium 22
{
	z2 = .5;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {		
		z1 = z;
		
		z  = z*z-z2*z2+c;
		z2 = z1;

		zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_81()  // Flarium 23
{
	z2 = z;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z=z*z*z*z+z2+c;
		z2=z1;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_82()  // Flarium 24
{
	z2 = z;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z=z*z*z*z+5*z2*c;
		z2=z1;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_83()  // Flarium 87
{
	t = 0;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z=z*z*z-t*t*t+c;
		t=z1;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_84()  // Flarium 88
{
	t = 0;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z=z*z*z*z-t*t*t*t+c;
		t=z1;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_85()		// Flarium 142, quartet
{
	z2 = z;
  d = 1;
  while( n_color++ < maxit
    && d > minsize
		&& d < maxsize)
  {
    z1 = z;

		z2	= z;
		z		= z*z*z*z+c;
		c		= z2;

    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_86()  // Flarium 65
{
	z = 1/z;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z3=z*z*z;
		z=z-(z*z3-z)/(4*z3-1);
		z=z*z*c;
		zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_87()  // Flarium 67
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z2=z*z;
		z=z-(z*z2-1)/(3*z2);
		z=z*z*z*c;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_88()  // Flarium 68
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z3=z*z*z;
		z=z-(z*z3-1)/(4*z3);
		z=z*z*z*z*c;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_89()  // Flarium 69
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z4=z*z*z*z;
		z=z-(z*z4-1)/(5*z4);
		z=z*z*z*z*z*c;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_90()  // Inkblot 9
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize
		&& d < bailout)
  {
    z1 = z;
    
		z = z + c;
			
		if (__real__ z >= 0)
			__real__ z = __real__ z - 2;
		else
			__real__ z = __real__ z + 2;
			

		if (__imag__ z >= 0)
			__imag__ z = __imag__ z - 2;
		else
			__imag__ z = __imag__ z + 2;
		    		
		zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_91()  // Iterations 108 CCAP
{
	t=c;
	ca=t;
	cb=t+2*t*t*t;
	caa3=ca*ca*3;

	if (jul == 0)
		z=-ca;

	d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z = z*z*z-caa3*z+cb;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_92()  // Iterations 109 CFAP
{
	t=c;
	ca=t;			
	cb=2*t*t*t-2*t;
	caa3=ca*ca*3;
	ca2=ca+ca;

	if (jul == 0)
		z=-ca;
  
	d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z = z*z*z-caa3*z+cb;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_93()  // Iterations 139
{
	z2 = z;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z=z*z*z*z-z2+c;
		z2 = z1;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_94()  // Iterations
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z = c*z*(2 - z*z);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_95()  // Iterations 133
{
	t = (1+c);
	t1 = csin_t();

  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z = z*z*z*z/t1+c;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_96()  // Iterations 141
{
	z2 = z;
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z=z*z*z*z+z2/2+c;
    z2=z1;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_97()  // Iterations 6
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z2 = sum_sqrs_z();
		z = z*z+c*(1+z2);
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_98()  // Iterations 156
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
    z=z*z*z*z/(1+z)+c;
    c=z1;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_99()  // Iterations 97
{
	//z2 = c-c.csin();

	z2 = csin_z();
	z2 = z - z2;

  d = 1;
  while( n_color++ < maxit
    && d > minsize)
  {
    z1 = z;
		z2=c+z2/z-z;
		z=z*c+z2/c;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

void Formula_100()
{
  d = 1;
  while( n_color++ < maxit
    && d > minsize
		&& d < maxsize)
  {
    z1 = z;
		__imag__ z += sin(__imag__ z);
    z=z*z+c;
		//temp = __real__ z;
		//__imag__ z = __real__ z;
    zd = z-z1;
    d = sum_sqrs_zd();
    if (filter) Do_Filter();
  }
}

