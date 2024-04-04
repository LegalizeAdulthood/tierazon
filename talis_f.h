////////////////////////////////////////////////
// Talis_F.h, Header file for Talis_F project //
////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "allegro.h"
#include <math.h>

#define PALSIZE       256

#define MIX_PALLETE     0
#define CMGB_PALLETE    1
#define SCALED_PALLETE  2
#define RGB_PALLETE     3
#define PALLETE_05      4

#define DRAW_BUTTON            2
#define CANCEL_BUTTON          3
#define PALLETE_BUTTON         4
#define LISTBOX_OBJECT_DRAW	   5
#define LISTBOX_OBJECT_FILTER	 6
#define LISTBOX_OBJECT_PALLETE 7

////////////////////////////////////////////////
// Attributes with Lots of global variables   //
////////////////////////////////////////////////

__complex__ double z, z1, z2, z3, z4, z5, z8, zd, z12;
__complex__ double c, c1, c2, c3;
__complex__ double t, t1, t2, t3, X, Y, Z;

BITMAP *memory_bitmap;

PALLETE pallete;
RGB temp, temp_m;
extern FONT *font;
FILE *stream;

char cname[44];
char cstr[200];
char par_name[80];
char pcx_name[80];
char pcx_newname[80];
char mess[80];

char* tok;

int icode;
int bug;
int red, grn, blu;
int i, j, k, l, m, n;
int redStep, grnStep, bluStep;
int nRedStart, nGrnStart, nBluStart;
int x, y;
int n_color, n_color_x, n_color_y, n_color_z, n_color_z1;
int err_vmode;
int WIDTH, HEIGTH;
int WIDTH_BM, HEIGTH_BM;
int WIDTH_R, HEIGTH_R;
int WIDTH_INIT, HEIGTH_INIT;
int col, row, bailout;
int maxcol, maxrow; //change these for different resolutions
int maxit;
int LEFT, TOP, RIGHT, BOTTOM;
int bRed, bGrn, bBlu;
int min, max;
int bitmap_Created;
int bLoadedFile;
int bLoading_zon;
int bDialog_Mode;
int key_entry;
int card;
int bFirst;
int kr, kc;
int itria;
int x00, y00, x11, y11, x22, y22, x33, y33, x44, y44;
int text_pixels, this_line, itab;
int formula, filter;
int length;
int bStartup;
int pallete_type;
int ret;
int jul, jul_save;
int bInvert;
int m_lower, m_upper;

double d_color, d_color_x, d_color_y, d_color_z;
double d, X0, X1, X2, Y0, Y1, Y2;
double deltar, deltai, dlta1, norm1, norm2;
double minx, maxx, miny, maxy;
double minx_init, maxx_init, miny_init, maxy_init;
double minx_new, maxx_new, miny_new, maxy_new;
double minx_save, maxx_save, miny_save, maxy_save;
double deltax, deltay;
double minsize, maxsize;
double xavg, yavg, zavg, zsav, xsav, ysav, xdif, ydif, zdif;
double zmin, zmax, zsav1;
double dt, dif_test, dStrands, dFactor, dFactor_2;
double limit, dStrands_HI, dStrands_LO;
double dStrands_HI_cx, dStrands_LO_cx;
double dStrands_HI_cy, dStrands_LO_cy;
double avg, tot, sav, dif, ssq1, ssq2;
double dif_save;
double ztot, xtot, ytot;
double d_real, d_imag;
double coord_offset;
double rx_ratio, ry_ratio;
double dzx, dzy;
double Radius_x, Radius_y, dMagnification, dMag_new;
double CRMID, CIMID;
double CRMID_JUL, CIMID_JUL;

double a,b,d, A, B, D;

double num_pixls, max_pixls;  // do not make these long_double
double dl, dt, dr, db;        // do not make these long_double



///////////////////////////////////////////
// Implementation
///////////////////////////////////////////

void initialize_graphics();
void Do_Filter();
void set_test_palette();
void set_mix_palette();
void set_cmgb_palette();
void set_scaled_palette();
void set_rgb_palette();
void set_pallete_type();
void pallete_05();
void plot_fractal();
void do_mouse();
void box_coordinates();
void status_line();
void status_line_new();
void output_status();
void status_bar();
void Filter_Complete();
void status_bar_complete();
inline void Do_Filter();
void do_fractal();
void rotatepal();
void Apply_The_Color();
void rotatepal_01();
void talis_g_init();
void talis_g();
void loaded_file();
void read_param_file();
void do_fractal_abort();
int  load_proc();
int  load_zon_proc();
int  save_proc();
int  quit_proc();
int  gfx_mode();
int  gfx_mode_proc();
void update_gui();
void update_the_screen();

void Formula_00();
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


//////////////////////////////////////////////
// Complex functions
inline double sum_sqrs_z();
inline double sum_sqrs_z1();
inline double sum_sqrs_z3();
inline double sum_sqrs_zd();
inline double csin_z4();
//////////////////////////////////////////////

