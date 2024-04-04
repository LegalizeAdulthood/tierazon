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

/*
    LibMain is called if Windows (un)load the DLL or threads are created

    The function LibMain is also defined in the library
*/

int APIENTRY LibMain(HANDLE hInst, DWORD fdwReason, LPVOID lpReserved)
{	
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		wsprintf (cstr, "LibMain(): DLL loaded");
		//MessageBox(NULL, "LibMain(): DLL loaded", "Attach", MB_OK);
	}
  else if (fdwReason == DLL_PROCESS_DETACH)
	{
		wsprintf (cstr, "LibMain(): DLL unloaded");
    //MessageBox(NULL, "LibMain(): DLL unloaded", "Detach", MB_OK);
	}

  return TRUE;
}

RGB_IDATA CALLBACK _formulae(int nDistortion, int nFilter, int _nColorMethod, int dBailout, int NMAX, double cx, double cy, double zx, double zy, int _px, int _py)
{
	//MessageBox(NULL, "step 1", "bug", MB_OK);
	
	formula			= nDistortion;	
	filter			= nFilter;
	bailout			= dBailout;
	maxit				= NMAX;
	minsize			= 1e-20;
	maxsize			= 1e+20;

	px = _px;
	py = _py;

	nColorMethod = _nColorMethod;

	__real__ c	= cx;
	__imag__ c	= cy;

	x = __real__ z = zx;
	y = __imag__ z = zy;

  limit = sqrt(__real__ z * __real__ z + __imag__ z * __imag__ z);

	n_color=0;
	n_color_x = 0;
	n_color_y = 0;
  n_color_z = 0;
  n_color_z1 = 0;

	rj = gj = bj = 0;

  dt = 0;
	tot = xtot = ytot = ztot = xavg = yavg = zavg = avg = 0;
	zsav1 = zsav = xsav = ysav = d_color_x = d_color_y = d_color_z = 0.0;
	a = b = 0.0;
	t = t1 = t2 = 0;
  
	//MessageBox(NULL, "step 1.3", "bug", MB_OK);

	dStrands_HI = limit + dStrands;
  dStrands_LO = limit - dStrands;

  //return;

	//sprintf (cstr, "1.) dStrands=%f, cx=%f, cy=%f.", dStrands, cx, cy);
	//MessageBox(NULL, cstr, "Debug", MB_OK);

	//__real__ t = -1;
	//__imag__ t = 0;

	//t1 = z * t;

	dStrands_HI_cx = fabs(cx) + dStrands;
  dStrands_HI_cy = fabs(cy) + dStrands;
  dStrands_LO_cx = fabs(cx) - dStrands;
  dStrands_LO_cy = fabs(cy) - dStrands ;

	dStrands_cxd = dStrands_HI_cx - dStrands_LO_cx;
	dStrands_cyd = dStrands_HI_cy - dStrands_LO_cy;

	//sprintf (cstr, "2.) dStrands=%f, cx=%f, cy=%f.", dStrands, cx, cy);
	//MessageBox(NULL, cstr, "Debug", MB_OK);

	dif_save = xdif = ydif = zdif = dif = ssq1 = ssq2 = (double) bailout-1;
		
	n_color = 0;

	//MessageBox(NULL, "step 2", "bug", MB_OK);

	switch (nDistortion)
	{
		case 1:
			Formula_01();
			break;

		case 2:
			Formula_02();
			break;

		case 3:
			Formula_03();
			break;

		case 4:
			Formula_04();
			break;

		case 5:
			Formula_05();
			break;

		case 6:
			Formula_06();
			break;

		case 7:
			Formula_07();
			break;

		case 8:
			Formula_08();
			break;

		case 9:
			Formula_09();
			break;

		case 10:
			Formula_10();
			break;

		case 11:
			Formula_11();
			break;

		case 12:
			Formula_12();
			break;

		case 13:
			Formula_13();
			break;

		case 14:
			Formula_14();
			break;

		case 15:
			Formula_15();
			break;

		case 16:
			Formula_16();
			break;

		case 17:
			Formula_17();
			break;

		case 18:
			Formula_18();
			break;

		case 19:
			Formula_19();
			break;

		case 20:
			Formula_20();
			break;

		case 21:
			Formula_21();
			break;

		case 22:
			Formula_22();
			break;

		case 23:
			Formula_23();
			break;

		case 24:
			Formula_24();
			break;

		case 25:
			Formula_25();
			break;

		case 26:
			Formula_26();
			break;

		case 27:
			Formula_27();
			break;

		case 28:
			Formula_28();
			break;

		case 29:
			Formula_29();
			break;

		case 30:
			Formula_30();
			break;

		case 31:
			Formula_31();
			break;

		case 32:
			Formula_32();
			break;

		case 33:
			Formula_33();
			break;

		case 34:
			Formula_34();
			break;

		case 35:
			Formula_35();
			break;

		case 36:
			Formula_36();
			break;

		case 37:
			Formula_37();
			break;

		case 38:
			Formula_38();
			break;

		case 39:
			Formula_39();
			break;

		case 40:
			Formula_40();
			break;

		case 41:
			Formula_41();
			break;

		case 42:
			Formula_42();
			break;

		case 43:
			Formula_43();
			break;

		case 44:
			Formula_44();
			break;

		case 45:
			Formula_45();
			break;

		case 46:
			Formula_46();
			break;

		case 47:
			Formula_47();
			break;

		case 48:
			Formula_48();
			break;

		case 49:
			Formula_49();
			break;

		case 50:
			Formula_50();
			break;

		case 51:
			Formula_51();
			break;

		case 52:
			Formula_52();
			break;

		case 53:
			Formula_53();
			break;

		case 54:
			Formula_54();
			break;

		case 55:
			Formula_55();
			break;

		case 56:
			Formula_56();
			break;

		case 57:
			Formula_57();
			break;

		case 58:
			Formula_58();
			break;

		case 59:
			Formula_59();
			break;

		case 60:
			Formula_60();
			break;

		case 61:
			Formula_61();
			break;

		case 62:
			Formula_62();
			break;

		case 63:
			Formula_63();
			break;

		case 64:
			Formula_64();
			break;

		case 65:
			Formula_65();
			break;

		case 66:
			Formula_66();
			break;

		case 67:
			Formula_67();
			break;

		case 68:
			Formula_68();
			break;

		case 69:
			Formula_69();
			break;

		case 70:
			Formula_70();
			break;

		case 71:
			Formula_71();
			break;

		case 72:
			Formula_72();
			break;

		case 73:
			Formula_73();
			break;

		case 74:
			Formula_74();
			break;

		case 75:
			Formula_75();
			break;

		case 76:
			Formula_76();
			break;

		case 77:
			Formula_77();
			break;

		case 78:
			Formula_78();
			break;

		case 79:
			Formula_79();
			break;

		case 80:
			Formula_80();
			break;

		case 81:
			Formula_81();
			break;

		case 82:
			Formula_82();
			break;

		case 83:
			Formula_83();
			break;

		case 84:
			Formula_84();
			break;

		case 85:
			Formula_85();
			break;

		case 86:
			Formula_86();
			break;

		case 87:
			Formula_87();
			break;

		case 88:
			Formula_88();
			break;

		case 89:
			Formula_89();
			break;

		case 90:
			Formula_90();
			break;

		case 91:
			Formula_91();
			break;

		case 92:
			Formula_92();
			break;

		case 93:
			Formula_93();
			break;

		case 94:
			Formula_94();
			break;

		case 95:
			Formula_95();
			break;

		case 96:
			Formula_96();
			break;

		case 97:
			Formula_97();
			break;

		case 98:
			Formula_98();
			break;

		case 99:
			Formula_99();
			break;

		case 100:
			Formula_100();
			break;

		default:
			break;

	}

	//MessageBox(NULL, "step 3", "bug", MB_OK);

	if (filter) 
	{
		__real__ z = xsav;
		__imag__ z = ysav;
		Filter_Complete();
	}
	else
	{
		j = rj = gj = bj = n_color;
		xsav = __real__ z;
		ysav = __imag__ z;
	}

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

			FDimension();
			break;

		default:
			break;
	}

	if (size_x <= 1024 && size_y <= 1024)
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

RGB_IDATA CALLBACK _color_update(int _px, int _py, int _nColorMethod, double cx, double cy, double zx, double zy)
{
	nColorMethod = _nColorMethod;

	px = _px;
	py = _py;

	__real__ c	= cx;
	__imag__ c	= cy;

	x = __real__ z = zx;
	y = __imag__ z = zy;

  limit = sqrt(__real__ z * __real__ z + __imag__ z * __imag__ z);

	dStrands_HI = limit + dStrands;
  dStrands_LO = limit - dStrands;

	dStrands_HI_cx = fabs(cx) + dStrands;
  dStrands_HI_cy = fabs(cy) + dStrands;
  dStrands_LO_cx = fabs(cx) - dStrands;
  dStrands_LO_cy = fabs(cy) - dStrands ;

	dStrands_cxd = dStrands_HI_cx - dStrands_LO_cx;
	dStrands_cyd = dStrands_HI_cy - dStrands_LO_cy;

	if (size_x <= 1024 && size_y <= 1024)
	{
		xsav = pXSave[px+py*size_x];
		ysav = pYSave[px+py*size_x];

		rj = rjData[px+py*size_x];
		gj = gjData[px+py*size_x];
		bj = bjData[px+py*size_x];

		/*
		if (px == 30 && py == 120)
		{
			sprintf(cstr, "step 1, xsav = %g, ysav=%g, i = %d, rj = %g, gj = %g, px=%d, py=%d, rgData=%f",
				xsav, ysav, i, rj, gj, px, py, &rjData);
			MessageBox(NULL, cstr, "bug", MB_OK);
			//bug = 0;
		}	
		*/

	}
	
	if (nColorMethod)	
		color_methods();

	//MessageBox(NULL, "step 5", "bug", MB_OK);

	//rgbColor.i  = j;
	rgbColor.rj	= rj;
	rgbColor.gj	= gj;
	rgbColor.bj	= bj;

	return rgbColor;
}

void CALLBACK _initialize(int _jul, int _jul_save, double _dStrands, double dBay100, double dBay1000, double dLower, double dUpper, double *_pXTemp, double *_pYTemp, double *_pXSave, double *_pYSave, double *_rjData, double *_gjData, double *_bjData, int _nRed, int _nGrn, int _nBlu, int _nRedStart, int _nGrnStart, int _nBluStart, int _nFDOption, int _bDimensionVariant, int _size_x, int _size_y)
{	
	bug = 1;

	pXTemp = _pXTemp;
	pYTemp = _pYTemp;

	pXSave = _pXSave;
	pYSave = _pYSave;

	rjData = _rjData;
	gjData = _gjData;
	bjData = _bjData;
	
	jul					= _jul;
	jul_save		= _jul_save;

	size_x = _size_x;
	size_y = _size_y;

	nRed = _nRed;
	nGrn = _nGrn;
	nBlu = _nBlu;
	
	nRedStart = _nRedStart;
	nGrnStart = _nGrnStart;
	nBluStart = _nBluStart;

	dStrands	= _dStrands;
	nFDOption = _nFDOption;

	bDimensionVariant = _bDimensionVariant;

	m_lower		= dLower;  // watermarks
	m_upper		= dUpper;

	dFactor		= dBay100;
	dFactor_2 = dBay1000;
	
  zmin = maxsize;
  zmax = minsize;

	//sprintf (cstr, "dFactor 1 = %f, dFactor 2 = %f",
	//	dFactor, dFactor_2);
	//MessageBox(NULL, cstr, "Debug", MB_OK);
}

//////////////////////////////////////////////////////////
void color_methods()
{
	/*
	if (xsav > 0 && ysav > 0 && bug == 1)
	{
		sprintf(cstr, "step 2, xsav = %g, ysav=%g, i = %d, rj = %g, gj = %g, px=%d, py=%d",
			xsav, ysav, i, rj, gj, px, py);
		MessageBox(NULL, cstr, "bug", MB_OK);
		bug = 0;
	}	
	*/

	switch(nColorMethod)
	{
		case 0:
			break;

		case 1:
			Generalized_Coloring_Method1();
			break;

		case 2:
			Generalized_Coloring_Method2();
			break;

		case 3:
			Generalized_Coloring_Method3();
			break;

		case 4:
			//wsprintf(cstr, "step 2, test method = %d", nColorMethod);
			//MessageBox(NULL, cstr, "bug", MB_OK);

			Generalized_Coloring_Method4();

			//wsprintf(cstr, "step 3, test method = %d", nColorMethod);
			//MessageBox(NULL, cstr, "bug", MB_OK);

			break;

		case 5:
			Generalized_Coloring_Method5();
			break;

		case 6:
			Generalized_Coloring_Method6();
			break;

		case 7:
			Generalized_Coloring_Method7();
			break;

		case 8:
			Generalized_Coloring_Method8();
			break;

		case 9:
			Generalized_Coloring_Method9();
			break;

		case 10:
			Generalized_Coloring_Method10();
			break;

		case 11:
			Generalized_Coloring_Method11();
			break;

		case 12:
			Generalized_Coloring_Method12();
			break;

		case 13:
			Generalized_Coloring_Method13();
			break;

		case 14:
			Generalized_Coloring_Method14();
			break;

		case 15:
			Generalized_Coloring_Method15();
			break;

		case 19:
			Generalized_Coloring_Method19();
			break;

		case 20:
			Generalized_Coloring_Method20();
			break;

		case 21:
			Generalized_Coloring_Method21();
			break;

		case 22:
			Generalized_Coloring_Method22();
			break;

		case 23:
			Generalized_Coloring_Method23();
			break;

		case 24:
			Generalized_Coloring_Method24();
			break;

		case 25:
			Generalized_Coloring_Method25();
			break;

		case 26:
			Generalized_Coloring_Method26();
			break;

		case 27:
			Generalized_Coloring_Method27();
			break;

		case 28:
			Generalized_Coloring_Method28();
			break;

		case 29:
			Generalized_Coloring_Method29();
			break;

		case 30:
			Generalized_Coloring_Method30();
			break;

		case 31:
			Generalized_Coloring_Method31();
			break;

		case 32:
			Generalized_Coloring_Method32();
			break;

		case 33:
			Generalized_Coloring_Method33();
			break;

		case 34:
			Generalized_Coloring_Method34();
			break;

		case 35:
			Generalized_Coloring_Method35();
			break;

		case 36:
			Generalized_Coloring_Method36();
			break;

		case 37:
			Generalized_Coloring_Method37();
			break;

		case 38:
			Generalized_Coloring_Method38();
			break;

		case 39:
			Generalized_Coloring_Method39();
			break;

		default:
			break;
	}
}

