///////////////////////////////////////////
// rsx_file.h
///////////////////////////////////////////
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

#define pi 3.141592653589793238462643383279
#define rad 57.2958

typedef struct tagRGB_IDATA
{
	double i;
	double rj;
	double gj;
	double bj;
} RGB_IDATA;

#define DUAL_BFACTOR 3
#define OFFSET_COLOR 64

// variable declarations
__complex__ double z, z1, z2, z3, z4, z5, z8, zd, z12, z16, z24, z36, z48;
__complex__ double c, c1, c2, c3;
__complex__ double t, t1, t2, t3, X, Y, Z, C, ca, cb, ca2, caa3;

// debug string attributes
char cstr[100];
int bug;

// FDimension Data array pointers
double				*pXTemp;
double				*pYTemp;

// Color method save buffers
double				*pXSave;
double				*pYSave;

double				*rjData;
double				*gjData;
double				*bjData;

int						size_x, size_y;
int						px, py;

// formula attributes
int formula, filter, bailout, maxit, n_color, maxit_save, nFDOption;
int jul, jul_save;

double d, minsize, maxsize;
int nRed, nGrn, nBlu, nRedStart, nGrnStart, nBluStart;

// Color attributes
RGB_IDATA rgbColor;
double rj, gj, bj;
int nColorMethod;

// filter attributes
int i, j, n_color, n_color_x, n_color_y, n_color_z, n_color_z1;
double m_lower, m_upper;

double d_color, d_color_x, d_color_y, d_color_z;
double xavg, yavg, zavg, zsav, xsav, ysav, xdif, ydif, zdif;
double zmin, zmax, zsav1, xsav_, ysav_;
double dt, dif_test, dStrands, dFactor, dFactor_2;
double limit, dStrands_HI, dStrands_LO;
double dStrands_HI_cx, dStrands_LO_cx;
double dStrands_HI_cy, dStrands_LO_cy;
double dStrands_cxd, dStrands_cyd;

double avg, tot, sav, dif, ssq1, ssq2;
double dif_save;
double ztot, xtot, ytot;
double d_real, d_imag;
double dzx, dzy;
double a, b, x, y;
double zx_save, zy_save;

double dzx_save, dzy_save;
double temp, x_size, y_size, deg;

///////////////////////////////////////////	
// Fractal dimension variables
int						i2, jrw, bDimensionVariant;
double				x_std, y_std, dm, da;
double				denominator, x_rmin, x_rmax, y_rmin, y_rmax;

// Data array pointers
double				*pXTemp;
double				*pYTemp;

__complex__		cx_std;
__complex__		cy_std;
__complex__		cFDx;
__complex__		cFDy;
__complex__		cRng_x;
__complex__		cRng_y;
__complex__		cNMAX;

double				dFDx;	// Fractal Dimension x
double				dFDy; // Fractal Dimension y

double				dFDx_0;	// Initial F Dimension x
double				dFDy_0; // Initial F Dimension y

int						nDIter_x;
int						nDIter_y;
int						nFDOption;
int						NMAX_Save;
int						min, max;
int						ntemp;

// Average variables
double				x_mean;
double				y_mean;

///////////////////////////////////
// implementions
///////////////////////////////////

// Filters
void Do_Filter();
void Filter_Complete();

// Complex functions
__complex__ double clog_z();
__complex__ double clog_t();
__complex__ double ccos_z();
__complex__ double ccos_c();
__complex__ double csin_z();
__complex__ double csin_t();

double sum_sqrs_z();
double sum_sqrs_c();
double magnitude_z();
double sum_sqrs_z1();
double sum_sqrs_z3();
double sum_sqrs_zd();
double real_csin_z4();
double imag_csin_z4();

// Formulas
void Formula_01();
void Formula_02();
void Formula_03();
void Formula_04();
void Formula_05();
void Formula_06();
void Formula_07();
void Formula_08();
void Formula_09();
void Formula_10();
void Formula_11();
void Formula_12();
void Formula_13();
void Formula_14();
void Formula_15();
void Formula_16();
void Formula_17();
void Formula_18();
void Formula_19();
void Formula_20();
void Formula_21();
void Formula_22();
void Formula_23();
void Formula_24();
void Formula_25();
void Formula_26();
void Formula_27();
void Formula_28();
void Formula_29();
void Formula_30();
void Formula_31();
void Formula_32();
void Formula_33();
void Formula_34();
void Formula_35();
void Formula_36();
void Formula_37();
void Formula_38();
void Formula_39();
void Formula_40();
void Formula_41();
void Formula_42();
void Formula_43();
void Formula_44();
void Formula_45();
void Formula_46();
void Formula_47();
void Formula_48();
void Formula_49();
void Formula_50();
void Formula_51();
void Formula_52();
void Formula_53();
void Formula_54();
void Formula_55();
void Formula_56();
void Formula_57();
void Formula_58();
void Formula_59();
void Formula_60();
void Formula_61();
void Formula_62();
void Formula_63();
void Formula_64();
void Formula_65();
void Formula_66();
void Formula_67();
void Formula_68();
void Formula_69();
void Formula_70();
void Formula_71();
void Formula_72();
void Formula_73();
void Formula_74();
void Formula_75();
void Formula_76();
void Formula_77();
void Formula_78();
void Formula_79();
void Formula_80();
void Formula_81();
void Formula_82();
void Formula_83();
void Formula_84();
void Formula_85();
void Formula_86();
void Formula_87();
void Formula_88();
void Formula_89();
void Formula_90();
void Formula_91();
void Formula_92();
void Formula_93();
void Formula_94();
void Formula_95();
void Formula_96();
void Formula_97();
void Formula_98();
void Formula_99();
void Formula_100();

void color_methods();
void FDimension();
double x_y_to_degrees(double x_, double y_);
void Generalized_Coloring_Method1();		
void Generalized_Coloring_Method2();		
void Generalized_Coloring_Method3();		
void Generalized_Coloring_Method4();		
void Generalized_Coloring_Method5();		
void Generalized_Coloring_Method6();		
void Generalized_Coloring_Method7();		
void Generalized_Coloring_Method8();		
void Generalized_Coloring_Method9();		
void Generalized_Coloring_Method10();		
void Generalized_Coloring_Method11();		
void Generalized_Coloring_Method12();		
void Generalized_Coloring_Method13();		
void Generalized_Coloring_Method14();		
void Generalized_Coloring_Method15();		
void Generalized_Coloring_Method18();		
void Generalized_Coloring_Method19();		
void Generalized_Coloring_Method20();		
void Generalized_Coloring_Method21();		
void Generalized_Coloring_Method22();		
void Generalized_Coloring_Method23();		
void Generalized_Coloring_Method24();		
void Generalized_Coloring_Method25();		
void Generalized_Coloring_Method26();		
void Generalized_Coloring_Method27();		
void Generalized_Coloring_Method28();		
void Generalized_Coloring_Method29();		
void Generalized_Coloring_Method30();		
void Generalized_Coloring_Method31();		
void Generalized_Coloring_Method32();		
void Generalized_Coloring_Method33();		
void Generalized_Coloring_Method34();		
void Generalized_Coloring_Method35();		
void Generalized_Coloring_Method36();		
void Generalized_Coloring_Method37();		
void Generalized_Coloring_Method38();		
void Generalized_Coloring_Method39();		

