////////////////////////////////////////////////////////////////////////////////
// Talis_g.c                                                                  //
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>

#include "allegro.h"
#include "talis_f.h"
//#include "degui.h"

#define NUMBER_OF_FILTERS  27
#define NUMBER_OF_FORMULA  37
#define NUMBER_OF_PALLETES  5

#define WHITE      0
#define RED        1
#define GREEN      2
#define YELLOW     3
#define BLUE       4
#define MAGENTA    5
#define CYAN       6
#define DARK_GRAY  7
#define GRAY       8
#define ROSEY      9
#define GREEN_2   10

#define BAK       GRAY
#define CLR       240   // 248

PALLETE mypal;

int about_proc();

static char *formula_strings[] =
{
  "00.) Test Pattern",
  "01.) Mandel, z=z*z+c;",
  "02.) Nova, init: z=1; iterate: z=z-((z*z*z-1)/(3*z*z))+c;",
  "03.) Ushiki's Phoenix, z=z*z-.5*z+c; z=z*z-.5*z2+c; z2=z; z=z1",
  "04.) Talis, z=((z*z)/(1+z))+c",
  "05.) Newton variation, z=((z*z*z-z-1)/(3*z*z-1)-z)*c;",
  "06.) z=z-((z*z*z)+(c-1)*z-c)/(3*(z*z)+c-1);",
  "07.) Newton variation, z = z-((z*z*z)+(c-1)*z-c)/(3*(z*z)+c-1);",
  "08.) Nova variant, init: z=1; iterate: z=z-((z*z*z*z-z)/(4*z*z*z-1)+c;",
  "09.) Nova variant, init: z=1; iterate: z=z-((z*z*z*z-z)/(4*z*z*z-z)+c;",
  "10.) z=z*z*z+c;",
  "11.) z=z*z*z*z+c;",
  "12.) z=z*z*z*z*z+c;",
  "13.) z=z*z*z*z*z*z+c;",
  "14.) z1=z*z+c; z=z*z+c*z2; z2=z;",
  "15.) Phoenix II,  z1=z; z=z*z   +   real(c) + imag(c)*z2; z2=z1;",
  "16.) Phoenix III, z1=z; z=z*z*z +   real(c) + imag(c)*z2; z2=z1;",
  "17.) Phoenix IV,  z1=z; z=z*z*z +.5*real(c) + imag(c)*z2; z2=z1;",
  "18.) z=-z/3; iterate: z=z-(z*z*z+z*z*c-z+c)/(3*z*z+2*c*z-1);",
  "19.) z=-z/3; iterate: z=z-(z*z*z+z*z*c+z+c)/(3*z*z+2*c*z+1);",
  "20.) z= z/2; iterate: z=z-(z^4-(z^3)*c-z-c)/(4*(z^3)-3*(z^2)*c-1)",
  "21.) z=-1/(3*z); iterate: z=z-((z^3)*c+z^2+z+c)/(3*(z^2)*c+2*z+1)",
  "22.) z=-.5; iterate: z=z-((z^4)c+(z^3)*c+z+c)/(4*(z^3)*c+3*z*z*c+1)",
  "23.) z=-.5/z; iterate: z=z-((z^4)*c+(z^3)+z+c)/(4*(z^3)*c+3*z*z+1)",
  "24.) z=-z/3;  iterate: z=z-((z^3)+z*z*c +c)/(3*z*z+2*z*c)",
  "25.) z=-z/2;  iterate: z=z-((z^4)+(z^3)*c+c)/(4*(z^3)+3*z*z*c)",
  "26.) 5th order Newton Mset",
  "27.) 7th order Newton Mset",
  "28.) 9th order Newton Mset",
  "29.) 13th order Newton Mset",
  "30.) 8th order Newton Mset",
  "31.) Newton Diamond",
  "32.) Newton Pentagon",
  "33.) Newton Hexagon",
  "34.) Newton Octagon",
  "35.) 9th order Newton Flower",
  "36.) Testing"
};

static char *filter_strings[] =
{
  "00.) none",
  "01.) Stalks I",
  "02.) Bubbles I",
  "03.) Moving Average I",
  "04.) Moving Average II",
  "05.) [Linas Vepstas] n = (n-log(log(sum_sqrs_z()))/log(2))",
  "06.) Combination of Bubbles I and the log(log(..)) algorithm",
  "07.) dual Bubbles I",
  "08.) Bubbles II",
  "09.) Stalks II",
  "10.) Rings I",
  "11.) Rings II",
  "12.) Rings III",
  "13.) Hi Lo Strands I",
  "14.) Hi Lo Strands II",
  "15.) abs(sin(x*x*100)*abs(sin(y*y*100)*30 && log(log(...))",
  "16.) atan method I",
  "17.) atan & stalks II",
  "18.) atan & bubbles III",
  "19.) atan & bubbles IV, factor 2",
  "20.) atan & bubbles V, factor 2",
  "21.) atan & bubbles, flower petals I, factor 2",
  "22.) atan & bubbles, figure 8 I, factor 2",
  "23.) atan & bubbles, figure 8 II modulas 2, factor 2",
  "24.) atan & bubbles, flower petals II, factor 2",
  "25.) sine & bubbles, flower petals I modulas 2, factor 2",
  "26.) atan & bubbles VI, factor 2"
};

static char *pallete_strings[] =
{
  "01.) Default Mix",
  "02.) Cyan, Magenta, Gray, Blue",
  "03.) Scaled",
  "04.) Red, Green, Blue",
  "05.) Pallete IV"
};

char buf1[80], buf2[80], buf3[80], buf4[80];

/* for the d_edit_proc() object */
char the_string[80] = "Sample Text Input";

char the_width[20]  = "320";
char the_heigth[20] = "240";
char the_bailout[20] = "4";

char the_redStart[4] = "73";
char the_grnStart[4] = "57";
char the_bluStart[4] = "86";

char the_redStep[4] = "2";
char the_grnStep[4] = "2";
char the_bluStep[4] = "3";

char the_Strands[25] = ".1";
char the_Factor_1[25]  = "1.0";
char the_Factor_2[25]  = "1.0";

char the_Julia_X[25] = "0";
char the_Julia_Y[25] = "0";
char the_J_Mode[4]   = "0";

char the_Mid_X[25] = "0";
char the_Mid_Y[25] = "0";

char the_Lower[4]  = "32";
char the_Upper[4]  = "96";

char TALIS_TITLE_AUTHOR_STR[80] = "The Talis Project, By: Stephen C. Ferguson";
char TALIS_VERSION_DATE_STR[80] = "November, 1997, Version 3.6";
char TALIS_BUF_01_STR[80]       = "http://home1.gte.net/itriazon/";

/* since we change the font, we need to store a copy of the original one */
//FONT *original_font;

/* callback function to specify the contents of the listbox */
char *listbox_draw(int index, int *list_size)
{
  if (index < 0) 
	{
    *list_size = NUMBER_OF_FORMULA;
    return NULL;
  }
  else
    return formula_strings[index];
}

/* callback function to specify the contents of the listbox */
char *listbox_filter(int index, int *list_size)
{
  if (index < 0) 
	{
    *list_size = NUMBER_OF_FILTERS;
    return NULL;
  }
  else
    return filter_strings[index];
}

/* callback function to specify the contents of the listbox */
char *listbox_pallete(int index, int *list_size)
{
  if (index < 0) 
	{
    *list_size = NUMBER_OF_PALLETES;
    return NULL;
  }
  else
    return pallete_strings[index];
}

MENU test_menu[] =
{
   { "&Graphics mode",           gfx_mode_proc,    NULL },
   { "&About",                   about_proc,       NULL },
   { "&Load PCX File",           load_proc,        NULL },
   { "&Load ZON File",           load_zon_proc,    NULL },
   { "&Save As",                 save_proc,        NULL },
	 { "",                         NULL,             NULL },
   { "&Quit",                    quit_proc,        NULL },
   { NULL,                       NULL,             NULL }
};

MENU menu[] =
{
  { "Options",                  NULL,             test_menu },
	{ NULL,                       NULL,             NULL }
};

DIALOG title_screen[] =
{
   /* (dialog proc)     (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_clear_proc,      0,    0,    0,    0,      0,  BAK,    0,    0,       0,    0,    NULL },
   { d_menu_proc,       0,    0,    0,    0,      0,  BAK,    0,    0,       0,    0,    menu },
   { d_ctext_proc,      0,    0,    0,    0,      0,  BAK,    0,    0,       0,    0,    TALIS_TITLE_AUTHOR_STR },
   { d_ctext_proc,      0,   20,    0,    0,      0,  BAK,    0,    0,       0,    0,    TALIS_VERSION_DATE_STR },
   { d_ctext_proc,      0,   40,    0,    0,      0,  BAK,    0,    0,       0,    0,    TALIS_BUF_01_STR },
	 { d_button_proc,   -20,   60,   40,   20,      0,  BAK,    0,    D_EXIT,  0,    0,    "OK" },
	 { NULL,              0,    0,    0,    0,    255,    0,    0,    0,       0,    0,    NULL }
};

DIALOG the_dialog[] =
{
  /* (dialog proc)    (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
  { d_clear_proc,      0,    0,    0,    0,    0,  CLR,    0,    0,       0,    0,    NULL },
  { d_menu_proc,       0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    menu },

	{ d_button_proc,   200,  400,   60,   20,  255,    0,    0,    D_EXIT,  0,    0,    "Draw" },
	{ d_button_proc,   300,  400,   60,   20,  255,    0,    0,    D_EXIT,  0,    0,    "Cancel" },
	{ d_button_proc,   400,  400,   60,   20,  255,    0,    0,    D_EXIT,  0,    0,    "Pallete" },

	{ d_list_proc,    -100,    0,  600,  100,  255,    0,    0,    0,       1,    0,    listbox_draw },
	{ d_list_proc,    -100,  120,  600,   80,  255,    0,    0,    0,       0,    0,    listbox_filter },
	{ d_list_proc,     200,  220,  300,   40,  255,    0,    0,    0,       0,    0,    listbox_pallete },

	{ d_text_proc,    -100,  220,   60,   15,  255,  CLR,    0,    0,       16,   0,    "Width" },
	{ d_text_proc,     -20,  220,   60,   15,  255,  CLR,    0,    0,       16,   0,    "Heigth" },
	{ d_text_proc,      60,  220,   60,   15,  255,  CLR,    0,    0,       16,   0,    "Bailout" },

	{ d_edit_proc,    -100,  235,   60,   15,  255,    0,    0,    0,       16,   0,    the_width },
	{ d_edit_proc,     -20,  235,   60,   15,  255,    0,    0,    0,       16,   0,    the_heigth },
	{ d_edit_proc,      60,  235,   60,   15,  255,    0,    0,    0,       16,   0,    the_bailout },

	{ d_text_proc,    -100,  280,   60,   15,  255,  CLR,    0,    0,       16,   0,    "Red start" },
	{ d_text_proc,     -20,  280,   60,   15,  255,  CLR,    0,    0,       16,   0,    "Grn Start" },
	{ d_text_proc,      60,  280,   60,   15,  255,  CLR,    0,    0,       16,   0,    "Blu Start" },

	{ d_edit_proc,    -100,  295,   60,   15,  255,    0,    0,    0,       16,   0,    the_redStart},
	{ d_edit_proc,     -20,  295,   60,   15,  255,    0,    0,    0,       16,   0,    the_grnStart},
	{ d_edit_proc,      60,  295,   60,   15,  255,    0,    0,    0,       16,   0,    the_bluStart},

	{ d_text_proc,     200,  280,   60,   15,  255,  CLR,    0,    0,       16,   0,    "Red step" },
	{ d_text_proc,     280,  280,   60,   15,  255,  CLR,    0,    0,       16,   0,    "Grn step" },
	{ d_text_proc,     360,  280,   60,   15,  255,  CLR,    0,    0,       16,   0,    "Blu step" },

	{ d_edit_proc,     200,  295,   60,   15,  255,    0,    0,    0,       16,   0,    the_redStep},
	{ d_edit_proc,     280,  295,   60,   15,  255,    0,    0,    0,       16,   0,    the_grnStep},
	{ d_edit_proc,     360,  295,   60,   15,  255,    0,    0,    0,       16,   0,    the_bluStep},

	{ d_text_proc,    -100,  320,   80,   15,  255,  CLR,    0,    0,       16,   0,    "Radius" },
	{ d_edit_proc,    -100,  335,   80,   15,  255,    0,    0,    0,       16,   0,    the_Strands},

	{ d_text_proc,     -10,  320,   80,   15,  255,  CLR,    0,    0,       16,   0,    "Factor 1"},
	{ d_edit_proc,     -10,  335,   80,   15,  255,    0,    0,    0,       16,   0,    the_Factor_1},

	{ d_text_proc,      80,  320,   80,   15,  255,  CLR,    0,    0,       16,   0,    "Factor 2" },
	{ d_edit_proc,      80,  335,   80,   15,  255,    0,    0,    0,       16,   0,    the_Factor_2},

	{ d_text_proc,     200,  320,   80,   15,  255,  CLR,    0,    0,       16,   0,    "Julia X" },
	{ d_edit_proc,     200,  335,   80,   15,  255,    0,    0,    0,       16,   0,    the_Julia_X},

	{ d_text_proc,     300,  320,   80,   15,  255,  CLR,    0,    0,       16,   0,    "Julia Y" },
	{ d_edit_proc,     300,  335,   80,   15,  255,    0,    0,    0,       16,   0,    the_Julia_Y},

	{ d_text_proc,     400,  320,   80,   15,  255,  CLR,    0,    0,       16,   0,    "Julia Mode" },
	{ d_edit_proc,     400,  335,   80,   15,  255,    0,    0,    0,       16,   0,    the_J_Mode},

	{ d_text_proc,     200,  360,   80,   15,  255,  CLR,    0,    0,       16,   0,    "Mid X" },
	{ d_edit_proc,     200,  375,   80,   15,  255,    0,    0,    0,       16,   0,    the_Mid_X},

	{ d_text_proc,     300,  360,   80,   15,  255,  CLR,    0,    0,       16,   0,    "Mid Y" },
	{ d_edit_proc,     300,  375,   80,   15,  255,    0,    0,    0,       16,   0,    the_Mid_Y},

	{ d_text_proc,    -100,  360,   80,   15,  255,  CLR,    0,    0,       16,   0,    "Lower" },
	{ d_edit_proc,    -100,  375,   80,   15,  255,    0,    0,    0,       16,   0,    the_Lower},

	{ d_text_proc,     -10,  360,   80,   15,  255,  CLR,    0,    0,       16,   0,    "Upper" },
	{ d_edit_proc,     -10,  375,   80,   15,  255,    0,    0,    0,       16,   0,    the_Upper},

	{ NULL,              0,    0,    0,    0,    1,    0,    0,    0,       0,    0,    NULL }
};

int gfx_mode()
{
  int card, w, h;

  if (!gfx_mode_select(&card, &w, &h))
		return -1;

  WIDTH = w;
  HEIGTH = h;

  show_mouse(NULL);

  /* try to set a wide virtual screen... */
  if (set_gfx_mode(card, w, h, (w >= 512) ? 1024 : 512, (w >= 512) ? 1024 : 512) != 0)
  {
		if (set_gfx_mode(card, w, h, (w >= 512) ? 1024 : 512, 0) != 0)
    {
			if (set_gfx_mode(card, w, h, 0, 0) != 0)
	    {
				set_gfx_mode(GFX_VGA, 320, 200, 0, 0);
	      set_pallete(mypal);
	      alert("Error setting mode:", allegro_error, NULL, "Sorry", NULL, 13, 0);
      }
    }
  }

	set_pallete(mypal);
  //set_default_object_colors (235,236,237,238,239,240,241,242);

  centre_dialog(title_screen+2);
  centre_dialog(the_dialog+2);
	
  return 0;
}

int about_proc()
{
  show_mouse(NULL);

  centre_dialog(title_screen+2);

  do_dialog(title_screen, -1);
  
	clear(screen);
	return D_REDRAW;
}

void talis_g_init()
{
  int c;

  /////////

   for (c=0; c<32; c++)
      mypal[c] = desktop_pallete[c];

   for (c=0; c<32; c++) {
      mypal[c+32].r = c*2;
      mypal[c+32].g = mypal[c+32].b = 0;
   }

   for (c=0; c<32; c++) {
      mypal[c+64].g = c*2;
      mypal[c+64].r = mypal[c+64].b = 0;
   }

   for (c=0; c<32; c++) {
      mypal[c+96].b = c*2;
      mypal[c+96].r = mypal[c+96].g = 0;
   }

   for (c=0; c<32; c++) {
      mypal[c+128].r = mypal[c+128].g = c*2;
      mypal[c+128].b = 0;
   }

   for (c=0; c<32; c++) {
      mypal[c+160].r = mypal[c+160].b = c*2;
      mypal[c+160].g = 0;
   }

   for (c=0; c<32; c++) {
      mypal[c+192].g = mypal[c+192].b = c*2;
      mypal[c+192].r = 0;
   }

   for (c=0; c<31; c++)
      mypal[c+224].r = mypal[c+224].g = mypal[c+224].b = c*2;

   mypal[255].r = mypal[255].g = mypal[255].b = 0;

   mypal[240].r = 11;  // special color for talis bakgrnd
   mypal[240].g = 28;
   mypal[240].b = 38;

  //////////////////////////

  gui_fg_color=7;
	gui_bg_color=0;

  set_gfx_mode(GFX_TEXT,80,25,0,0);
  allegro_exit();

  /* initialise everything */
  allegro_init();

  install_keyboard();
  install_mouse();

  install_timer();

  set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
  //set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0);

	set_pallete(mypal);
	//set_pallete(desktop_pallete);

  if (bStartup)
  {
    if (gfx_mode() != 0)
	  {
      show_mouse(NULL);
      set_gfx_mode(GFX_TEXT,80,25,0,0);
      allegro_exit();
      exit(0);
    }
  }

  talis_g();
  set_mouse_speed(0, 0);
}

void talis_g()
{
  bDialog_Mode = TRUE;

	//set_pallete(desktop_pallete);

	//set_pallete(pallete);

	set_pallete(mypal);

  //gui_fg_color=1;
	//gui_bg_color=2;

  //gui_fg_color=128;
	//gui_bg_color=37;

  //set_default_object_colors (235,236,237,238,239,240,241,242);
  //set_default_object_colors (   16, 17, 18, 19, 20, 21, 22, 23);

	centre_dialog(the_dialog+2);

  if (!bStartup)
  {
    update_gui();

    /* do the dialog */
    ret = do_dialog(the_dialog, -1);
  }

  show_mouse(NULL);

  if (ret == CANCEL_BUTTON)
  {
    clear(screen);
    bDialog_Mode = FALSE;
    set_pallete_type();
    return;
  }

  nRedStart = atoi(the_redStart);
  nGrnStart = atoi(the_grnStart);
  nBluStart = atoi(the_bluStart);

  redStep = atoi(the_redStep);
  grnStep = atoi(the_grnStep);
  bluStep = atoi(the_bluStep);

  m_lower = atoi(the_Lower);
  m_upper = atoi(the_Upper);

  pallete_type  = the_dialog[LISTBOX_OBJECT_PALLETE].d1;

  if (ret == PALLETE_BUTTON)
  {
    clear(screen);
    bDialog_Mode = FALSE;
    set_pallete_type();
    return;
  }

  /* and report the results */
  //sprintf(buf1, "do_dialog() returned %d", ret);
  //sprintf(buf2, "the_width '%s'", the_width);
  //sprintf(buf3, "the_heigth '%s'", the_heigth);
  //sprintf(buf4, "listbox selection is %d", the_dialog[LISTBOX_OBJECT_DRAW].d1);
  //alert(buf1, buf2, buf3, "OK", NULL, 0, 0);

  //if (atoi(the_width) != WIDTH_R || atoi(the_heigth) != HEIGTH_R)
  //{
    //if ((double) WIDTH_R/(double) (HEIGTH_R) != rx_ratio)
    //{
      //WIDTH_R  = WIDTH_BM  = atoi(the_width);
      //HEIGTH_R = HEIGTH_BM = atoi(the_heigth);
      //adjust_coords();
   //}
  //}

  /*
  if (the_dialog[LISTBOX_OBJECT_DRAW].d1 != formula)
  {
    // reset coordinates on a new formula
    //adjust_coords();

    jul = jul_save = 0;
    dMagnification = 1;
    CRMID = 0;
    CIMID = 0;
  }
  */


  WIDTH_R  = WIDTH_BM  = atoi(the_width);
  HEIGTH_R = HEIGTH_BM = atoi(the_heigth);

  //adjust_coords();

  bailout = atoi(the_bailout);

  jul = atoi(the_J_Mode);

  if (jul < 0 || jul > 1)
    jul = 0;

  formula       = the_dialog[LISTBOX_OBJECT_DRAW].d1;
  filter        = the_dialog[LISTBOX_OBJECT_FILTER].d1;

  dStrands   = atof(the_Strands);
  dFactor    = atof(the_Factor_1);
  dFactor_2  = atof(the_Factor_2);

  CRMID = atof(the_Mid_X);
  CIMID = atof(the_Mid_Y);

  if (jul == 1)
  {
  	__real__ c = atof(the_Julia_X);
  	__imag__ c = atof(the_Julia_Y);

    if (jul_save == 0)
    {
      CRMID = 0;
      CIMID = 0;
      CRMID_JUL = __real__ c;
      CIMID_JUL = __imag__ c;
    }
  }


  if (WIDTH_BM > WIDTH || HEIGTH_BM > HEIGTH)
  {
    /*
    WIDTH_R = WIDTH;
    //if (HEIGTH_BM > HEIGTH)
    HEIGTH_R = HEIGTH;
    */

    if (WIDTH_BM >= HEIGTH_BM)
    {
      WIDTH_R   = WIDTH;
      HEIGTH_R  = WIDTH * HEIGTH_BM/WIDTH_BM;
    }
    else
    {
      HEIGTH_R = HEIGTH;
      WIDTH_R  = HEIGTH * WIDTH_BM/HEIGTH_BM;
    }
  }

  maxcol=WIDTH_BM;
  maxrow=HEIGTH_BM;

  set_pallete_type();

  bitmap_Created = FALSE;
  clear(screen);
  bDialog_Mode = FALSE;

	adjust_coords();
}

adjust_coords()
{
  Radius_x = 2/dMagnification;
  Radius_y = 2/dMagnification;

  if (jul == 1 && jul_save == 0)
  {
    maxx = 0 + Radius_x;
    minx = 0 - Radius_x;
    maxy = 0 + Radius_y;
    miny = 0 - Radius_y;
  }
  else
  {
    maxx = CRMID + Radius_x;
    minx = CRMID - Radius_x;
    maxy = CIMID + Radius_y;
    miny = CIMID - Radius_y;
  }

  rx_ratio = (double) WIDTH_BM/(double) (HEIGTH_BM);
  ry_ratio = (double) HEIGTH_BM/(double) (WIDTH_BM);

  rx_ratio = rx_ratio + (1-rx_ratio)/2;
  ry_ratio = ry_ratio + (1-ry_ratio)/2;

  maxx = maxx + (Radius_x * (rx_ratio) - Radius_x);
  minx = minx - (Radius_x * (rx_ratio) - Radius_x);
  maxy = maxy + (Radius_x * (ry_ratio) - Radius_y);
  miny = miny - (Radius_x * (ry_ratio) - Radius_y);

  minx_save = minx_init = minx;
  maxx_save = maxx_init = maxx;
  miny_save = miny_init = miny;
  maxy_save = maxy_init = maxy;
}

void set_pallete_type()
{
  // Set the appropriate pallete
  switch(pallete_type)
  {
    case MIX_PALLETE:
      set_mix_palette();
      break;

    case CMGB_PALLETE:
      set_cmgb_palette();
      break;

    case SCALED_PALLETE:
      set_scaled_palette();
      break;

    case RGB_PALLETE:
      set_rgb_palette();
      //set_pallete(mypal);
      break;

    case PALLETE_05:
      palette_05();
      break;

    default:
      break;

  }
}

int gfx_mode_proc()
{
  show_mouse(NULL);
  clear(screen);
  gfx_mode();
  return D_REDRAW;
}

int quit_proc()
{
  show_mouse(NULL);
  set_gfx_mode(GFX_TEXT,80,25,0,0);

  allegro_exit();
	exit(0);
	//return D_CLOSE;
}

int save_proc()
{
	int icode;

  struct date
  {
    short da_year;
    char  da_day;
    char  da_mon;
  };

	char name[80] = "name.pcx";
	char save_mess[80] = "Save File As";

  struct date d;

  //set_default_object_colors (235,236,237,238,239,240,241,242);

  getdate(&d);

  itria=01;

  set_pallete(desktop_pallete);

  do  // Search for a default filename
  {
    sprintf(cname,"%02d_%02d_%02d.pcx",
    d.da_mon, d.da_day, itria);
    stream = fopen(cname, "r+");  // Open file to see if it exists
    fclose(stream);
    itria++;
  } while (stream != NULL);

  icode = file_select(save_mess, cname, "pcx");
  //icode = degui_file_select(mess, cname, "pcx");

  if (icode == 0)
  {
	  set_pallete(pallete);
    return D_REDRAW;
  }


  strcpy(pcx_name, cname);

  i = strcspn(pcx_name, ".");
  length = strlen(pcx_name);

  if (i == length)
  {
    strcpy(par_name, pcx_name);
    strcat(pcx_name,".pcx");
    strcat(par_name,".zon");
  }
  else
  {
    for (j=0; j<sizeof(pcx_newname); j++)
      pcx_newname[j]=0;
    strncpy(pcx_newname, pcx_name, length-4);

    strcpy(pcx_name, pcx_newname);
    strcpy(par_name, pcx_newname);

    strcat(pcx_name,".pcx");
    strcat(par_name,".zon");
  }

	set_pallete(pallete);

	set_pallete(pallete);
  save_bitmap(cname, memory_bitmap, pallete);

  stream = fopen(par_name, "w+");  // Open file to see if it exists

  fprintf(stream,"Formula       = %s\n", formula_strings[formula]);
  fprintf(stream,"Formula #     = %d\n", formula);
  fprintf(stream,"Filter        = %s\n", filter_strings[filter]);
  fprintf(stream,"Filter #      = %d\n", filter);
  fprintf(stream,"Left          = %02.15f\n", minx);
  fprintf(stream,"Top           = %02.15f\n", miny);
  fprintf(stream,"Right         = %02.15f\n", maxx);
  fprintf(stream,"Bottom        = %02.15f\n", maxy);
  fprintf(stream,"Max iter      = %d\n", maxit);
  fprintf(stream,"Bailout       = %d\n", bailout);
  fprintf(stream,"Red Start     = %d\n", nRedStart);
  fprintf(stream,"Green Start   = %d\n", nGrnStart);
  fprintf(stream,"Blue Start    = %d\n", nBluStart);
  fprintf(stream,"Red Steps     = %d\n", redStep);
  fprintf(stream,"Green Steps   = %d\n", grnStep);
  fprintf(stream,"Blue Steps    = %d\n", bluStep);
  fprintf(stream,"Strands       = %02.15f\n", dStrands);
  fprintf(stream,"Factor        = %02.15f\n", dFactor);
  fprintf(stream,"Pallete Type  = %d\n", pallete_type);
  fprintf(stream,"Julia mode    = %d\n", jul);
  fprintf(stream,"Julia X       = %02.15f\n", CRMID_JUL);
  fprintf(stream,"Julia Y       = %02.15f\n", CIMID_JUL);
  fprintf(stream,"Mid X         = %02.15f\n", CRMID);
  fprintf(stream,"Mid Y         = %02.15f\n", CIMID);
  fprintf(stream,"real c        = %02.15f\n", __real__ c);
  fprintf(stream,"imag c        = %02.15f\n", __imag__ c);
  fprintf(stream,"Invert mode   = %d\n", bInvert);
  fprintf(stream,"Lower         = %d\n", m_lower);
  fprintf(stream,"Upper         = %d\n", m_upper);
  fprintf(stream,"Factor 2      = %02.15f\n", dFactor_2);

  fclose(stream);

  if (!bDialog_Mode)
    set_pallete(pallete);

	return D_REDRAW;
}


int load_zon_proc()
{
  if (!bStartup)
  {

  	set_pallete(desktop_pallete);
    //set_default_object_colors (235,236,237,238,239,240,241,242);

    strcpy(cname,"");
    strcpy(mess,"");
    icode = file_select(mess, cname, "zon");

    if (icode == 0)
    {
      /* select the bitmap pallete */
      set_pallete(pallete);
      return D_REDRAW;
    }
  }

  clear(screen);
  show_mouse(NULL);

  strcpy(par_name, cname);
  read_param_file();

  /* select the bitmap pallete */
  set_pallete(pallete);

  bLoading_zon = TRUE;
  return D_CLOSE;

}

int load_proc()
{
  if (!bStartup)
  {
  	set_pallete(desktop_pallete);
    //set_default_object_colors (235,236,237,238,239,240,241,242);

    strcpy(cname,"");
    strcpy(mess,"");
    icode = file_select(mess, cname, "pcx");

    if (icode == 0)
    {
      /* select the bitmap pallete */
      set_pallete(pallete);
      return D_REDRAW;
    }
  }

  clear(screen);
  show_mouse(NULL);

  if (bitmap_Created)
  {
    // free the previous memory bitmap
    destroy_bitmap(memory_bitmap);
    bitmap_Created = FALSE;
  }

  memory_bitmap = load_pcx(cname, pallete);
  if (!memory_bitmap)
  {
  	set_pallete(desktop_pallete);
    //set_default_object_colors (235,236,237,238,239,240,241,242);

    sprintf(mess, "Error reading PCX file '%s'\n", cname);
    alert(mess, cname, cname, "OK", NULL, 0, 0);
    strcpy(cname,"");

    set_pallete(pallete);
    return D_REDRAW;
  }
  else
  {
    bLoadedFile = TRUE;
    bitmap_Created = TRUE;

    // Get the name of the parameter file
    strcpy(pcx_name, cname);

    i = strcspn(pcx_name, ".");
    length = strlen(pcx_name);

    if (i == length)
    {
      strcpy(par_name, pcx_name);
      strcat(pcx_name,".pcx");
      strcat(par_name,".zon");
    }
    else
    {
      for (j=0; j<sizeof(pcx_newname); j++)
          pcx_newname[j]=0;
      strncpy(pcx_newname, pcx_name, length-4);

      strcpy(pcx_name, pcx_newname);
      strcpy(par_name, pcx_newname);

      strcat(pcx_name,".pcx");
      strcat(par_name,".zon");
    }

    read_param_file();

    /* select the bitmap pallete */
    set_pallete(pallete);

    return D_CLOSE;
  }
}

void read_param_file()
{
  char *fp;

		// Read the parameter file info
    stream = fopen(par_name, "r+");  // Open file
    if (stream != NULL)
    {

      fgets(cstr, sizeof(cstr), stream);  // Formula string
      fgets(cstr, sizeof(cstr), stream);  // Formula number
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      formula = atoi(tok);

      fgets(cstr, sizeof(cstr), stream);  // Filter string
      fgets(cstr, sizeof(cstr), stream);  // Filter number
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      filter = atoi(tok);

      fgets(cstr, sizeof(cstr), stream);  // minx (left)
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      minx = atof(tok);

      fgets(cstr, sizeof(cstr), stream);  // miny (left)
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      miny = atof(tok);

      fgets(cstr, sizeof(cstr), stream);  // maxx (right)
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      maxx = atof(tok);

      fgets(cstr, sizeof(cstr), stream);  // maxy (bottom)
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      maxy = atof(tok);

      minx_save = minx_new = minx;
      maxx_save = maxx_new = maxx;
      miny_save = miny_new = miny;
      maxy_save = maxy_new = maxy;

      fgets(cstr, sizeof(cstr), stream);  // Max iter
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      maxit = atoi(tok);

      fgets(cstr, sizeof(cstr), stream);  // Bailout
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      bailout = atoi(tok);

      fgets(cstr, sizeof(cstr), stream);  // Red Start
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      nRedStart = atoi(tok);

      fgets(cstr, sizeof(cstr), stream);  // Green Start
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      nGrnStart = atoi(tok);

      fgets(cstr, sizeof(cstr), stream);  // Blue Start
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      nBluStart = atoi(tok);

      fgets(cstr, sizeof(cstr), stream);  // Red Steps
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      redStep = atoi(tok);

      fgets(cstr, sizeof(cstr), stream);  // Green Steps
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      grnStep = atoi(tok);

      fgets(cstr, sizeof(cstr), stream);  // Blue Steps
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      bluStep = atoi(tok);

      fgets(cstr, sizeof(cstr), stream);  // Strands
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      dStrands = atof(tok);

      fgets(cstr, sizeof(cstr), stream);  // Factor
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      dFactor = atof(tok);

      fgets(cstr, sizeof(cstr), stream);  // Pallete Type
      tok = strtok(cstr, "=");
      tok = strtok(NULL, "");
      pallete_type = atoi(tok);

      if (fgets(cstr, sizeof(cstr), stream))  // Julia mode
      {
        tok = strtok(cstr, "=");
        tok = strtok(NULL, "");
        jul = atoi(tok);
      }
      else
        jul = 0;
      jul_save = jul;


      if (fgets(cstr, sizeof(cstr), stream))  // Julia point X
      {
        tok = strtok(cstr, "=");
        tok = strtok(NULL, "");
        CRMID_JUL = atof(tok);
      }
      else
      {
        CRMID_JUL = 0;
      }

      if (fgets(cstr, sizeof(cstr), stream))  // Julia point Y
      {
        tok = strtok(cstr, "=");
        tok = strtok(NULL, "");
        CIMID_JUL = atof(tok);
      }
      else
        CIMID_JUL = 0;

      if (fgets(cstr, sizeof(cstr), stream))  // Mid point X
      {
        tok = strtok(cstr, "=");
        tok = strtok(NULL, "");
        CRMID = atof(tok);
      }
      else
        CRMID = 0;

      if (fgets(cstr, sizeof(cstr), stream))  // Mid point Y
      {
        tok = strtok(cstr, "=");
        tok = strtok(NULL, "");
        CIMID = atof(tok);
      }
      else
        CIMID = 0;

      if (fgets(cstr, sizeof(cstr), stream))  // real c
      {
        tok = strtok(cstr, "=");
        tok = strtok(NULL, "");
        __real__ c = atof(tok);
      }
      else
        __real__ c = 0;

      if (fgets(cstr, sizeof(cstr), stream))  // imag c
      {
        tok = strtok(cstr, "=");
        tok = strtok(NULL, "");
        __imag__ c = atof(tok);
      }
      else
        __imag__ c = 0;

      if (fgets(cstr, sizeof(cstr), stream))  // Invert mode
      {
        tok = strtok(cstr, "=");
        tok = strtok(NULL, "");
        bInvert = atoi(tok);
      }
      else
        bInvert = 0;

      if (fgets(cstr, sizeof(cstr), stream))  // lower
      {
        tok = strtok(cstr, "=");
        tok = strtok(NULL, "");
        m_lower = atoi(tok);
      }
      else
        m_lower = 32;

      if (fgets(cstr, sizeof(cstr), stream))  // upper
      {
        tok = strtok(cstr, "=");
        tok = strtok(NULL, "");
        m_upper = atoi(tok);
      }
      else
        m_upper = 96;

      if (fgets(cstr, sizeof(cstr), stream))  // Factor 2
      {
        tok = strtok(cstr, "=");
        tok = strtok(NULL, "");
        dFactor_2 = atof(tok);
      }
      else
        dFactor_2 = 1.0;

      //alert(buf1, buf2, "Yep", "OK", NULL, 0, 0);
      fclose(stream);

      update_gui();
      status_line();
    }
    else
    {
    	set_pallete(desktop_pallete);
      //set_default_object_colors (235,236,237,238,239,240,241,242);

      sprintf(buf1, "pcx_name = '%s'", pcx_name);
      sprintf(buf2, "Error, opening parameter file: '%s'", par_name);
      alert(buf1, buf2, "Yep, OK", "OK", NULL, 0, 0);
    }
}

void update_gui()
{
  the_dialog[LISTBOX_OBJECT_DRAW].d1    = formula;
  the_dialog[LISTBOX_OBJECT_FILTER].d1  = filter;
  the_dialog[LISTBOX_OBJECT_PALLETE].d1 = pallete_type;

  itoa(nRedStart, cstr, 10);
  strcpy(the_redStart, cstr);

  itoa(nGrnStart, cstr, 10);
  strcpy(the_grnStart, cstr);

  itoa(nBluStart, cstr, 10);
  strcpy(the_bluStart, cstr);

  itoa(redStep, cstr, 10);
  strcpy(the_redStep, cstr);

  itoa(grnStep, cstr, 10);
  strcpy(the_grnStep, cstr);

  itoa(bluStep, cstr, 10);
  strcpy(the_bluStep, cstr);

  itoa(bailout, cstr, 10);
  strcpy(the_bailout, cstr);

  itoa(m_lower, cstr, 10);
  strcpy(the_Lower, cstr);

  itoa(m_upper, cstr, 10);
  strcpy(the_Upper, cstr);

  sprintf(cstr,"%f", dStrands);
  strcpy(the_Strands, cstr);

  sprintf(cstr,"%f", dFactor);
  strcpy(the_Factor_1, cstr);

  sprintf(cstr,"%f", dFactor_2);
  strcpy(the_Factor_2, cstr);

  sprintf(cstr,"%f", CRMID);
  strcpy(the_Mid_X, cstr);

  sprintf(cstr,"%f", CIMID);
  strcpy(the_Mid_Y, cstr);

  itoa(jul, cstr, 10);
  strcpy(the_J_Mode, cstr);

  if (jul == 1)
  {
    sprintf(cstr,"%f", __real__ c);
    strcpy(the_Julia_X, cstr);

    sprintf(cstr,"%f", __imag__ c);
    strcpy(the_Julia_Y, cstr);

    /*
    if (jul == 0 || jul == 1)
    {
      itoa(jul, cstr, 10);
      strcpy(the_J_Mode, cstr);
    }
    else
    {
      sprintf(cstr,"0");
      strcpy(the_J_Mode, cstr);
    }
    */
  }
  else
  {
    sprintf(cstr,"0", __real__ c);
    strcpy(the_Julia_X, cstr);

    sprintf(cstr,"0", __imag__ c);
    strcpy(the_Julia_Y, cstr);
  }
}



