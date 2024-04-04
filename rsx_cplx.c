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

///////////////////////////////////////////////////////////////
// Complex Functions
///////////////////////////////////////////////////////////////

__complex__ double clog_z()
{
   //cmplx(log(ABS(sum_sqrs(Z),atan2(y,x));}

   __real__ Z = log((sqrt(__real__ z*__real__ z + __imag__ z*__imag__ z)));
   __imag__ Z = atan2(__imag__ z, __real__ z);

   return Z;
}

__complex__ double clog_t()
{
   //cmplx(log(ABS(sum_sqrs(Z),atan2(y,x));}

   __real__ Z = log((sqrt(__real__ t*__real__ t + __imag__ t*__imag__ t)));
   __imag__ Z = atan2(__imag__ t, __real__ t);

   return Z;
}

__complex__ double ccos_z()
{
  __real__ Z = .5*(exp(__imag__ z)+1./exp(__imag__ z))*cos(__real__ z);
  __imag__ Z = -sin(__real__ z)*.5*(exp(__imag__ z)-1./exp(__imag__ z));

  return Z;
}

__complex__ double ccos_c()
{
  __real__ C = .5*(exp(__imag__ c)+1./exp(__imag__ c))*cos(__real__ c);
  __imag__ C = -sin(__real__ c)*.5*(exp(__imag__ c)-1./exp(__imag__ c));

  return C;
}

__complex__ double csin_z()
{
  __real__ Z = .5*(exp(__imag__ z)+1./exp(__imag__ z))*sin(__real__ z);
  __imag__ Z = cos(__real__ z)*.5*(exp(__imag__ z)-1./exp(__imag__ z));
  return Z;
}

__complex__ double csin_t()
{
  __real__ Z = .5*(exp(__imag__ t)+1./exp(__imag__ t))*sin(__real__ t);
  __imag__ Z = cos(__real__ t)*.5*(exp(__imag__ t)-1./exp(__imag__ t));
  return Z;
}

double sum_sqrs_z()
{
  return __real__ z * __real__ z  + __imag__ z * __imag__ z;
}

double sum_sqrs_c()
{
  return __real__ c * __real__ c  + __imag__ c * __imag__ c;
}

double magnitude_z()
{
  return sqrt(__real__ z * __real__ z  + __imag__ z * __imag__ z);
}

double sum_sqrs_z1()
{
  return __real__ z1 * __real__ z1  + __imag__ z1 * __imag__ z1;
}

double sum_sqrs_z3()
{
  return __real__ z3 * __real__ z3  + __imag__ z3 * __imag__ z3;
}

double sum_sqrs_zd()
{
  return __real__ zd * __real__ zd  + __imag__ zd * __imag__ zd;
}

double real_csin_z4()
{
	return .5*(exp(__imag__ z4)+1./exp(__imag__ z4))*sin(__real__ z4);
}

double imag_csin_z4()
{
  return cos(__real__ z4)*.5*(exp(__imag__ z4)-1./exp(__imag__ z4));
}

