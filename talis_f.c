/////////////////////////////////////////////
// Talis_f.c                               //
// A Fractal Generator                     //
// by: Stephen C. Ferguson                 //
// http://home1.gte.net/itriazon/          //
// August 1997 v1.0                        //
// September, 1997 v2.0                    //
/////////////////////////////////////////////

#include "talis_f.h"

void main (int argc, char *argv[])
{
  bStartup = TRUE;
  bLoadedFile = FALSE;
  bLoading_zon = FALSE;

  WIDTH_INIT  = WIDTH_R  = WIDTH_BM  = 320;    // Initial Bitmap width and heigth
  HEIGTH_INIT = HEIGTH_R = HEIGTH_BM = 240;

  maxrow = WIDTH_BM;
  maxcol = HEIGTH_BM;

  i					= 0;
  formula 	= 1;
  filter 		= 0;
  jul 			= 0;
  jul_save 	= 0;
  bInvert 	= 0;

	itab 			= 20;
  bailout 	= 4;
  maxit  		= 256;

  minx=-2; maxx=2; miny=-2; maxy=2;
  dMagnification = 1;
  CRMID = 0;
  CIMID = 0;
  //minx=-2.5; maxx=1.5; miny=-1.5; maxy=1.5;

  //coord_offset = ((maxx - minx) - (maxx - minx)
  //                  * ((double)HEIGTH_BM/(double)WIDTH_BM))/2.0;

  //maxx+=coord_offset;
  //minx-=coord_offset;

  rx_ratio = (double) WIDTH_R/(double) (HEIGTH_R);
  ry_ratio = (double) HEIGTH_R/(double) (WIDTH_R);

  rx_ratio = rx_ratio + (1-rx_ratio)/2;
  ry_ratio = ry_ratio + (1-ry_ratio)/2;

  //dx_length = (maxx - minx) * rx_ratio;
  //dy_length = (maxy - miny) * ry_ratio;

  maxx = maxx * rx_ratio;
  minx = minx * rx_ratio;
  maxy = maxy * ry_ratio;
  miny = miny * ry_ratio;

  minx_new = minx_save = minx_init = minx;
  maxx_new = maxx_save = maxx_init = maxx;
  miny_new = miny_save = miny_init = miny;
  maxy_new = maxy_save = maxy_init = maxy;

  talis_g_init();

  strcpy(cname, "StartUp.pcx");
  load_proc();

  bStartup = FALSE;

  //if (bLoadedFile)
    //loaded_file();

  while (!keypressed() && (!key[KEY_ESC]))
  {
    clear_keybuf();
    plot_fractal();
    do_mouse();
  }

  if (bitmap_Created)
  {
    // free the memory bitmap
    destroy_bitmap(memory_bitmap);
  }

  //show_mouse(screen);
  show_mouse(NULL);
  set_gfx_mode(GFX_TEXT,80,25,0,0);

  /* Shuts down Allegro     */
  allegro_exit();

  /* Exit program           */
  exit(0);
}

void loaded_file()
{
  clear_keybuf();

  show_mouse(NULL);

  WIDTH_BM  = memory_bitmap->w;
  HEIGTH_BM = memory_bitmap->h;

  box_coordinates();
  status_line();

  show_mouse(NULL);

  //Draws an outline rectangle with the two points as its opposite corners.
  rect(screen, LEFT-1, TOP-1, RIGHT, BOTTOM, 255);

  stretch_blit(memory_bitmap, screen,
    0, 0,  WIDTH_BM, HEIGTH_BM,
      LEFT, TOP, WIDTH_R, HEIGTH_R);

  status_bar_complete();

  bLoadedFile = FALSE;

  //do_mouse();
  //readkey();
}

void plot_fractal()
{
	box_coordinates();
  if (!bitmap_Created)
  {
    memory_bitmap = create_bitmap(WIDTH_BM, HEIGTH_BM);

    // free the memory bitmap
    //destroy_bitmap(memory_bitmap);
    bitmap_Created = TRUE;
    clear_to_color(memory_bitmap, 0);
  }

  deltax=(maxx-minx)/(maxcol-1);
  deltay=(maxy-miny)/(maxrow-1);

  maxsize  = 1e20;
  minsize  = 1e-20;
  dif_test = .001;
  num_pixls = 0;
  max_pixls = maxrow*maxcol;

  show_mouse(NULL);
  status_line();
  rect(screen, LEFT-1, TOP-1, RIGHT, BOTTOM, 255);
  show_mouse(screen);

	for (kr=0; kr<4; kr++)
  {
		for (kc=0; kc<4; kc++)
		{
			show_mouse(NULL);

      stretch_blit(memory_bitmap, screen,
						0, 0,  WIDTH_BM, HEIGTH_BM,
							LEFT, TOP, WIDTH_R, HEIGTH_R);

      status_bar();
			show_mouse(screen);

			for (row=kr; row<maxrow; row+=4)
			{
				xsav = 0;
				ysav = 0;

				for (col=kc; col<maxcol; col+=4)
				{
          num_pixls++;

          __real__ z = minx+col*deltax; // Initialize z at each pass.
					__imag__ z = miny+row*deltay;

          if (jul == 0)
            c = z;
          else
          if (jul_save == 0)
          {
            __real__ c = CRMID_JUL;
            __imag__ c = CIMID_JUL;
          }

  				if (jul == 0)
          {
  					if (bInvert)
            {
      				c = 1/c;
              z = 1/z;
            }
          }
  				else
  				if (jul_save == 0)
          {
    				if (bInvert)
            {
      				c = 1/c;
              z = 1/z;

            }
          }
          else
          if (bInvert)
            z = 1/z;

					n_color=2;
					n_color_x = 0;
					n_color_y = 0;
          n_color_z = 0;
          n_color_z1 = 0;

					dif_save = xdif = ydif = zdif = dif = ssq1 = ssq2 = bailout-1;
          dt = 0;
					tot = xtot = ytot = ztot = xavg = yavg = zavg = avg = 0;
					zsav1 = zsav = xsav = ysav = d_color_x = d_color_y = d_color_z = 0.0;

          limit = sqrt(__real__ c * __real__ c + __imag__ c * __imag__ c);
          dStrands_HI = limit + dStrands;
          dStrands_LO = limit - dStrands;

          dStrands_HI_cx = ABS(__real__ c) + dStrands;
          dStrands_HI_cy = ABS(__imag__ c) + dStrands;
          dStrands_LO_cx = ABS(__real__ c) - dStrands;
          dStrands_LO_cy = ABS(__imag__ c) - dStrands ;

          zmin = maxsize;
          zmax = minsize;

					switch(formula)
					{
					case 0:
						Formula_00();  // Test Pattern
						break;

					case 1:
						Formula_01();    // z=z*z+1;
						break;

					case 2:
						Formula_02();    // Julia-Newton-Nova
						break;

					case 3:
						Formula_03();    // Phoenix
						break;

					case 4:
						Formula_04();    // Talis
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

          default:
						break;
					}

					if (filter)
						Filter_Complete();

  				if ((n_color & 0x1FF) > 0xFF)
          {
						n_color = n_color ^ 0xFF;    // Invert
          }
					  //n_color = n_color ^ 0xFF;    // Invert

					n_color = n_color & 0xFF;

					if (n_color <= 0 && n_color_z >= 0)  // Need to fix this
					  n_color = 1;

					if (n_color >= 0xFF)          // Need to fix this
						n_color = 0xFE;

					//if (n_color == 63)          // Need to fix this
						//n_color = 64;

          if (col >= maxcol || row >= maxrow)
          {
            printf("error\n");
            readkey();

            /* Shut down Allegro          */
            allegro_exit ();
            exit (1);
          }
          else
          {
            _putpixel(memory_bitmap, col, row, n_color );
          }

					if (kc == 0 && kr == 0)
					{
						_putpixel(memory_bitmap, col,   row+1, n_color );
						_putpixel(memory_bitmap, col,   row+2, n_color );
						_putpixel(memory_bitmap, col,   row+3, n_color );

						_putpixel(memory_bitmap, col+1, row+0, n_color );
						_putpixel(memory_bitmap, col+1, row+1, n_color );
						_putpixel(memory_bitmap, col+1, row+2, n_color );
						_putpixel(memory_bitmap, col+1, row+3, n_color );

						_putpixel(memory_bitmap, col+2, row+0, n_color );
						_putpixel(memory_bitmap, col+2, row+1, n_color );
						_putpixel(memory_bitmap, col+2, row+2, n_color );
						_putpixel(memory_bitmap, col+2, row+3, n_color );
						
						_putpixel(memory_bitmap, col+3, row+0, n_color );
						_putpixel(memory_bitmap, col+3, row+1, n_color );
						_putpixel(memory_bitmap, col+3, row+2, n_color );
						_putpixel(memory_bitmap, col+3, row+3, n_color );
					
					}
					
					if (kc == 1 && kr == 1)
					{
						_putpixel(memory_bitmap, col,   row+1, n_color );
						_putpixel(memory_bitmap, col,   row+2, n_color );

						_putpixel(memory_bitmap, col+1, row+0, n_color );
						_putpixel(memory_bitmap, col+1, row+1, n_color );
						_putpixel(memory_bitmap, col+1, row+2, n_color );

						_putpixel(memory_bitmap, col+2, row+0, n_color );
						_putpixel(memory_bitmap, col+2, row+1, n_color );
						_putpixel(memory_bitmap, col+2, row+2, n_color );
											
					}

					if (kc == 2 && kr == 2)
					{
						_putpixel(memory_bitmap, col,   row+1, n_color );
						_putpixel(memory_bitmap, col+1, row  , n_color );
						_putpixel(memory_bitmap, col+1, row+1, n_color );
					
					}

					if (key[KEY_SPACE] || key[KEY_ESC]) // Abort on esc or space key
					{
            jul_save = jul;
            do_fractal_abort();
				  }

          if (mouse_b & 1)                        // Detects left mouse button
          {
            jul_save = jul;
            do_fractal_abort();
  					update_the_screen();
            do_mouse();
          }
        }
			}
		}
	}
  jul_save = jul;
  update_the_screen();
}

void update_the_screen()
{
  show_mouse(NULL);

  //Draws an outline rectangle with the two points as its opposite corners.
  rect(screen, LEFT-1, TOP-1, RIGHT, BOTTOM, 255);

  stretch_blit(memory_bitmap, screen,
      0, 0,  WIDTH_BM, HEIGTH_BM,
      LEFT, TOP, WIDTH_R, HEIGTH_R);

  status_bar_complete();
  show_mouse(screen);
}

void do_fractal_abort()
{
  row=HEIGTH_BM;
  col=WIDTH_BM;
  kr = 5;
  kc = 5;
  clear_keybuf();
}

void status_bar()
{
  show_mouse(NULL);
  sprintf(cstr,"%%=%.0f kr=%02d, kc=%02d, Row = %03d                ",
					  100*(num_pixls/max_pixls), kr, kc, row );
  textout(screen, font, cstr, itab, HEIGTH-15, 255);
  show_mouse(screen);
}

void status_bar_complete()
{
  sprintf(cstr,"%%=%.0f kr=%02d, kc=%02d, Row = %03d [Complete]     ",
					  100*(num_pixls/max_pixls), kr, kc, row );
  textout(screen, font, cstr, itab, HEIGTH-15, 255);
}

///////////////////////////////////////////////////////
void do_mouse()
{
  show_mouse(screen);
  bFirst = TRUE;

  do
  {
    if (mouse_b & 1)                        // Detects left mouse button
    {
      x00=mouse_x;                          // Coordinates of the first corner
      y00=mouse_y;                          // of the zoom box, corresponding                                           // to the current mouse coordinates
      x11=mouse_x;                          // Coordinates of the first corner
      y11=mouse_y;                          // of the zoom box, corresponding                                           // to the current mouse coordinates
      x22=mouse_x;                          // Second corner  
      y22=mouse_y;
      x33=mouse_x;                          // The previous value of the second
      y33=mouse_y;                          // corner - used for erasing
      x44=mouse_x;                          // The previous value of the second
      y44=mouse_y;                          // corner - used for erasing

      if (!bFirst)
      {
        show_mouse(NULL);

        //clear(screen);
        status_line();

				stretch_blit(memory_bitmap, screen,
					0, 0,  WIDTH_BM, HEIGTH_BM,
						LEFT, TOP, WIDTH_R, HEIGTH_R);				

        //Draws an outline rectangle with the two points as its opposite corners.
        rect(screen, LEFT-1, TOP-1, RIGHT, BOTTOM, 255);


      }
//      else
//        bFirst = FALSE;

      while (mouse_b&1)                    // While the left mouse button  
      {                                    // is still pressed, track mouse  
         show_mouse(NULL);
         xor_mode(TRUE);                   // Draw nevative image on screen

         x11 = ABS(x00 - (mouse_x - x00));
         x22 = mouse_x;

         y11 = ABS(y00 - (mouse_x - x00)*HEIGTH_BM/WIDTH_BM);
         y22 = ABS(y00 + (mouse_x - x00)*HEIGTH_BM/WIDTH_BM);

         //y11 = ABS(y00 - (mouse_x - x00));
         //y22 = ABS(y00 + (mouse_x - x00));

/*
         x2=mouse_x;                       // Second corner of the zoom box
         y2=y1+(mouse_x-x1)*HEIGTH_BM/WIDTH_BM;           // 3/4 is for the aspect ratio
*/

         rect(screen, x11, y11, x22, y22, 32); // Draw zoom box

         if (!bFirst)
           rect(screen, x33, y33, x44, y44, 32); // Erase old box


         // Draw an X cross section
  			 line (screen, x11, y11, x22, y22, 255);
  		 	 line (screen, x22, y11, x11, y22, 255);

         // erase old zoom cross section
         if (!bFirst)
         {
  			   line (screen, x33, y33, x44, y44, 255);
  		 	   line (screen, x44, y33, x33, y44, 255);
         }


         bFirst = FALSE;

         x33=x11;
         y33=y11;
         x44=x22;
         y44=y22;
                                          // The present coordinates will
         xor_mode(FALSE);                  // erase the box next time
      }                                    // When button is released

      xor_mode(FALSE);                      // erase the box next time
      show_mouse(screen);

      x22=mouse_x;                          // second corner is set  
      //y22=y11+(mouse_x-x11);                  // with square aspect ratio
      //y22=

      box_coordinates();

      deltar=(maxx - minx)/(WIDTH_R);      // Steps in the complex plane
      deltai=(maxy - miny)/(HEIGTH_R);      // corresponding to a pixel on screen

      minx_new = (minx     + (x11-LEFT)*deltar);
      maxx_new = (minx_new + (x22-x11)*deltar);
      miny_new = (miny     + (y11-TOP)*deltai);
      maxy_new = (miny_new + (y22-y11)*deltar);

      //coord_offset = ((maxx - minx) - (maxx - minx)
      //              * ((double)HEIGTH_BM/(double)WIDTH_BM))/2.0;

      //maxx_new+=coord_offset;
      //minx_new-=coord_offset;

      CRMID = minx_new + ABS((maxx_new - minx_new) / 2);
      CIMID = miny_new + ABS((maxy_new - miny_new) / 2);

      status_line();

    }

    if (mouse_b & 2)
    {
      minx_save = minx;
      miny_save = miny;
      maxx_save = maxx;
      maxy_save = maxy;


      if (jul == 1 && jul_save == 0)
      {
        dMagnification = 1;
      }
      else
      {
        minx = minx_new;
        miny = miny_new;
        maxx = maxx_new;
        maxy = maxy_new;
      }

      show_mouse(NULL);
      clear(screen);
      //plot_fractal();
      do_fractal_abort();
      show_mouse(screen);
      return;
    }

    if (key[KEY_K])
    {
      clear_keybuf();
      clear(screen);
    }

    if (key[KEY_J])  // Toggle Julia mode
    {
      if (jul == 0)
      {
        jul = 1;     // set to Julia mode
        jul_save = 0;
        CRMID_JUL = CRMID;
        CIMID_JUL = CIMID;
      }
      else
      {
        jul = 0;     // set to Mandelbrot mode
        jul_save = 0;
        CRMID = 0;
        CIMID = 0;
      }
      clear_keybuf();

      //__real__ c = CRMID;
      //__imag__ c = CIMID;

      minx = -2;
      maxx =  2;
      miny = -2;
      maxy =  2;
      dMagnification = 1;
      adjust_coords();

      status_line();
      do_fractal();
      return;
    }

    if (key[KEY_I])   // Set to Invert mode
    {
      if (bInvert == 0)
        bInvert = 1;
      else
        bInvert = 0;

      clear_keybuf();
      status_line();
      do_fractal();
      return;
    }

    if (key[KEY_1])  // default size
    {
      clear_keybuf();

			WIDTH_BM  = WIDTH_INIT;
      HEIGTH_BM = HEIGTH_INIT;

      do_fractal();
      return;
    }

    if (key[KEY_2])  // size 1920 by 1440
    {
      clear_keybuf();
      WIDTH_BM  = 1920;
      HEIGTH_BM = 1440;
      do_fractal();
      return;
    }

    if (key[KEY_3])  // size 2400 by 1800
    {
      clear_keybuf();
      WIDTH_BM  = 2400;
      HEIGTH_BM = 1800;
      do_fractal();
      return;
    }

    if (key[KEY_R])  // Reset coordinates to default
    {
      clear_keybuf();
      dMagnification = 1;
      CRMID = 0;
      CIMID = 0;
      adjust_coords();
      do_fractal();
      return;
    }

    if (key[KEY_U])  // Reset coordinates to previous coordinates
    {
      clear_keybuf();
      maxx = maxx_save;
      minx = minx_save;
      maxy = maxy_save;
      miny = miny_save;
      do_fractal();
      return;
    }

    if (key[KEY_C])  // Rotate the palette
    {
      clear_keybuf();
      if (pallete_type == 0)
         rotatepal(); // rotate the default mix pallete
      else
         rotatepal_01(); // rotate all other pallettes
    }

    if (key[KEY_S])
    {
      clear_keybuf();
      save_proc();
      status_line();
		  clear(screen);
			update_the_screen();
      status_line();
    }

    if (key[KEY_O])
    {
      clear_keybuf();
      load_proc();

		  //clear(screen);

      //stretch_blit(memory_bitmap, screen,
				//	0, 0,  WIDTH_BM, HEIGTH_BM,
					//	LEFT, TOP, WIDTH_R, HEIGTH_R);

			update_the_screen();
      status_line();
    }

    if (key[KEY_UP])
    {
      clear_keybuf();
      maxit+=10;
      status_line();

    }

    if (key[KEY_DOWN])
    {
      clear_keybuf();
      maxit-=10;
      status_line();

    }

    if (key[KEY_D] || key[KEY_H])
    {
      talis_g();
      clear_keybuf();

      m = D_CLOSE;

      if (ret == DRAW_BUTTON || bLoading_zon)
      {
        bLoading_zon = FALSE;
        do_fractal();
        return;
      }
      else
      {
        status_line();
        update_the_screen();
      }
    }

  }  while (!key[KEY_ESC]);

}

void do_fractal()
{
  destroy_bitmap(memory_bitmap);
  bitmap_Created = FALSE;

  maxx_new = maxx;
  maxy_new = maxy;
  minx_new = minx;
  miny_new = miny;

  show_mouse(NULL);
  clear(screen);
  //plot_fractal();
  do_fractal_abort();
  show_mouse(screen);
}

void box_coordinates()
{
	maxcol=WIDTH_BM, maxrow=HEIGTH_BM; //change these for different resolutions

  LEFT   = WIDTH/2 - WIDTH_R/2;
  TOP    = HEIGTH/2 - HEIGTH_R/2;
  RIGHT  = WIDTH/2 + WIDTH_R/2;
  BOTTOM = HEIGTH/2 + HEIGTH_R/2;
}

void status_line()
{
  text_mode(0);

  show_mouse(NULL);

  //Draws an outline around the entire screen
  rect(screen, 0, 0, WIDTH-1, HEIGTH-1, 255);

  text_pixels = 15;
  this_line = text_pixels;

  dl = minx;
  dt = miny;
  dr = maxx;
  db = maxy;


  // Calculate the Magnification (2 / (average of width & length))
  rx_ratio = (double) WIDTH_R/(double) (HEIGTH_R);
  ry_ratio = (double) HEIGTH_R/(double) (WIDTH_R);

  rx_ratio = rx_ratio + (1-rx_ratio)/2;
  ry_ratio = ry_ratio + (1-ry_ratio)/2;

 	dMagnification = 2 / (((ABS(maxx - minx)/rx_ratio) / 4)
 										  + ((ABS(maxy - miny)/ry_ratio) / 4));

// Calculate the Magnification (2 / (average of width & length))
// 	dMagnification = 2 / ((ABS(maxx - minx) / 4)
// 										  + (ABS(maxy - miny) / 4));

	output_status();

}

void status_line_new()
{

  text_mode(0);

  show_mouse(NULL);

  //Draws an outline around the entire screen
  rect(screen, 0, 0, WIDTH-1, HEIGTH-1, 255);

  text_pixels = 15;
  this_line = text_pixels;

  dl = minx_new;
  dt = miny_new;
  dr = maxx_new;
  db = maxy_new;

  // Calculate the Magnification (2 / (average of width & length))
  //  rx_ratio = (double) WIDTH_R/(double) (HEIGTH_R);
  //  ry_ratio = (double) HEIGTH_R/(double) (WIDTH_R);

  //  rx_ratio = rx_ratio + (1-rx_ratio)/2;
  //  ry_ratio = ry_ratio + (1-ry_ratio)/2;

  // 	dMagnification = 2 / (((ABS(maxx_new - minx_new)/rx_ratio) / 4)
  // 										  + ((ABS(maxy_new - miny_new)/ry_ratio) / 4));

  // Calculate the Magnification (2 / (average of width & length))
 	// dMagnification = 2 / ((ABS(maxx_new - minx_new) / 4)
 	//									  + (ABS(maxy_new - miny_new) / 4));

	output_status();
}

void output_status()
{

	//this_line += text_pixels;
  sprintf(cstr,"Left=%e, Top=%e, xmid=%e, ymid=%e   ", dl, dt, CRMID, CIMID);
  textout(screen, font, cstr, itab, this_line, 255);

  this_line += text_pixels;
  sprintf(cstr,"Right=%e, Bottom=%e, Julia [J]=%d, Invert [I]=%d   "
                                                 , dr, db, jul, bInvert);
  textout(screen, font, cstr, itab, this_line, 255);

  this_line += text_pixels;
  sprintf(cstr,"Magnif=%e, Iterations = %d[^], Bitmap size = %d by %d",
                 dMagnification, maxit, WIDTH_BM, HEIGTH_BM);
  textout(screen, font, cstr, itab, this_line, 255);

  this_line += text_pixels;
  sprintf(cstr,"Dialog [D], Reset [R], Open [O] %s, Save to File [S]", cname);
  textout(screen, font, cstr, itab, this_line, 255);

  this_line += text_pixels;
  sprintf(cstr,"Color Cycle [C], Undo [U], 1920 by 1440 [2], 2400 by 1800 [3]");
  textout(screen, font, cstr, itab, this_line, 255);

  show_mouse(screen);

}


void rotatepal()
{
  static int redFwd=TRUE, grnFwd=TRUE, bluFwd=TRUE;

  while (!keypressed())
  {
    rest(10);
    temp = pallete[1];

    if (redFwd && nRedStart>=255)
    {
       redFwd = FALSE;
       nRedStart--;
    }
    else
    if (redFwd)
       nRedStart++;
    else
    if (!redFwd && nRedStart<=0)
    {
      redFwd = TRUE;
      nRedStart++;
    }
    else
      nRedStart--;

    if (grnFwd && nGrnStart>=255)
    {
       grnFwd = FALSE;
       nGrnStart--;
    }
    else
    if (grnFwd)
       nGrnStart++;
    else
    if (!grnFwd && nGrnStart<=0)
    {
      grnFwd = TRUE;
      nGrnStart++;
    }
    else
      nGrnStart--;

    if (bluFwd && nBluStart>=255)
    {
       bluFwd = FALSE;
       nBluStart--;
    }
    else
    if (bluFwd)
       nBluStart++;
    else
    if (!bluFwd && nBluStart<=0)
    {
      bluFwd = TRUE;
      nBluStart++;
    }
    else
      nBluStart--;

    /* fill our pallete with a gradually altering sequence of colors */
    for (i=0; i<256; i++)
	  {
		  red = i*redStep + nRedStart;
		  grn = i*grnStep + nGrnStart;
		  blu = i*bluStep + nBluStart;
	
		  Apply_The_Color();
		
		  pallete[i].r = red/4;
      pallete[i].g = grn/4;
      pallete[i].b = blu/4;
    }

    pallete[255].r 	= 63;  // This is the color used for the mouse
    pallete[255].g 	= 63;
    pallete[255].b 	= 63;

    pallete[0].r 	= 0;  // This is the color used for the text & Lines
    pallete[0].g 	= 0;
    pallete[0].b 	= 0;

    set_pallete(pallete);
  }

  clear_keybuf();

  pallete[255].r 	= 63;  // This is the color used for the mouse
  pallete[255].g 	= 63;
  pallete[255].b 	= 63;

  pallete[0].r 	= 0;  // This is the color used for the text & Lines
  pallete[0].g 	= 0;
  pallete[0].b 	= 0;

  set_pallete(pallete);

  show_mouse(screen);
}

void rotatepal_01()
{
  int c;
  double count;

/*
  pallete[0].r=0;
  pallete[0].g=0;
  pallete[0].b=0;
  pallete[1].r=63;
  pallete[1].g=63;
  pallete[1].b=63;

  temp=pallete[2];
*/
  show_mouse(NULL);       // Don't show mouse cursor while cycling

  while (!keypressed())
  {
    rest(50);
    temp = pallete[1];

    for (c=1; c<254; c++)
      pallete[c] = pallete[c+1];
    pallete[254] = temp;

    set_pallete(pallete);
   }
  clear_keybuf();

  nRedStart = pallete[254].r;
  nGrnStart = pallete[254].g;
  nBluStart = pallete[254].b;

  show_mouse(screen);
}

void initialize_graphics()
{
  install_keyboard();

  maxcol=WIDTH;
  maxrow=HEIGTH;

  allegro_init();
  install_timer();
  install_mouse();

  //set_gfx_mode(GFX_AUTODETECT, WIDTH, HEIGTH, 0, 0);
  //card = GFX_AUTODETECT;
  //err_vmode = set_gfx_mode(card, WIDTH, HEIGTH, 0, 0);
  /* Checks if any error occured during screen mode initialization   */
  if ( err_vmode != 0 )
  {
    printf("Error setting graphics mode\n%s\n\n", allegro_error);
    readkey();

    /* Shut down Allegro          */
    allegro_exit ();
    exit (1);
  }
}

void set_scaled_palette()
{
	// Create a scaled palette	
	for (i=0, j=63; i<32; i++, j-=2)				// Blues
	{
		//lpBI->bmiColors[i].rgbBlue			= j;
		//lpBI->bmiColors[i].rgbRed				=
		//lpBI->bmiColors[i].rgbGreen			= 0;

    pallete[i].b = j;
    pallete[i].r =
    pallete[i].g = 0;
  }

	for (i=32, j=0; i<96; i++, j+=2)			// Cyan
	{
		//lpBI->bmiColors[i].rgbRed				= 0;
		//lpBI->bmiColors[i].rgbGreen			=
		//lpBI->bmiColors[i].rgbBlue			= j;

    pallete[i].r = 0;
    pallete[i].g =
    pallete[i].b = j;
  }

	for (i=64, j=63; i<96; i++, j-=2)			// Magenta
	{
		//lpBI->bmiColors[i].rgbGreen			= 0;
		//lpBI->bmiColors[i].rgbRed				=
		//lpBI->bmiColors[i].rgbBlue			= j;

    pallete[i].g = 0;
    pallete[i].r =
    pallete[i].b = j;
  }

	for (i=96, j=0; i<128; i++, j+=2)			// Red
	{
		//lpBI->bmiColors[i].rgbRed				= j;
		//lpBI->bmiColors[i].rgbGreen			=
		//lpBI->bmiColors[i].rgbBlue			= 0;

    pallete[i].r = j;
    pallete[i].g =
    pallete[i].b = 0;
	}

	for (i=128, j=63; i<160; i++, j-=2)			// Yellow
	{
		//lpBI->bmiColors[i].rgbBlue			= 0;
		//lpBI->bmiColors[i].rgbRed				=
		//lpBI->bmiColors[i].rgbGreen			= j;

    pallete[i].b = 0;
    pallete[i].r =
    pallete[i].g = j;

	}

	for (i=160, j=0; i<192; i++, j+=2)			// Green
	{
		//lpBI->bmiColors[i].rgbGreen			= j;
		//lpBI->bmiColors[i].rgbRed				=
		//lpBI->bmiColors[i].rgbBlue			= 0;

    pallete[i].g = j;
    pallete[i].r =
    pallete[i].b = 0;

  }

	for (i=192, j=63; i<256; i++, j-=1)			// Grays & Whites
	{
		//lpBI->bmiColors[i].rgbRed				=
		//lpBI->bmiColors[i].rgbGreen			=
		//lpBI->bmiColors[i].rgbBlue			= j;

    pallete[i].r =
    pallete[i].g =
    pallete[i].b = j;
  }

   pallete[255].r 	= 255;  // This is the color used for the mouse
   pallete[255].g 	= 255;
   pallete[255].b 	= 255;

   pallete[0].r 	= 0;  // This is the color used for the desktop
   pallete[0].g 	= 0;
   pallete[0].b 	= 0;

   set_pallete(pallete);
}

void set_rgb_palette()
{
   // fill our pallete with a gradually altering sequence of colors
   for (i=0; i<64; i++)
   {
      pallete[i].r = i;
      pallete[i].g = 0;
      pallete[i].b = 0;
   }

   for (i=64; i<128; i++)
   {
      pallete[i].r = 127-i;
      pallete[i].g = i-64;
      pallete[i].b = 0;
   }

   for (i=128; i<192; i++)
   {
      pallete[i].r = 0;
      pallete[i].g = 191-i;
      pallete[i].b = i-128;
   }

   for (i=192; i<256; i++) {
      pallete[i].r = 0;
      pallete[i].g = 0;
      pallete[i].b = 255-i;
   }

   pallete[255].r 	= 255;  // This is the color used for the mouse
   pallete[255].g 	= 255;
   pallete[255].b 	= 255;

   set_pallete(pallete);
}

void set_cmgb_palette()
{
	for (i=0; i<64; i++)
	{
    pallete[i].g =     // Cyan
    pallete[i].b = 63 - i;
    pallete[i].r = 0;

    pallete[i+64].r =      // Magenta
    pallete[i+64].b = 63 - i;
    pallete[i+64].g = 0;

    pallete[i+128].r =      // Gray
    pallete[i+128].g =
    pallete[i+128].b = 63 - i;

    //pallete[i+128].r =      // Yellow
    //pallete[i+128].g = 63 - i;
    //pallete[i+128].b = 0;

    //pallete[i+192].g =      // Red
    //pallete[i+192].b = 0;
    //pallete[i+192].r = i;
																								
    //pallete[i+128].r =      // Green
    //pallete[i+128].b = 0;
    //pallete[i+128].g = i;

    pallete[i+192].r =      // Blue
    pallete[i+192].g = 0;
    pallete[i+192].b = 63 - i;

  }
  /*
	for (i=0; i<64; i++)
	{
		//lpBI->bmiColors[i+204].rgbRed		= 					// Blue
		//lpBI->bmiColors[i+204].rgbGreen	= 0;
		//lpBI->bmiColors[i+204].rgbBlue	= (int) (i*256 / 48);

    pallete[i+192].r =      // Gray
    pallete[i+192].g =
    pallete[i+192].b = i;

  }
  */

  pallete[255].r 	= 63;  // This is the color used for the mouse
  pallete[255].g 	= 63;
  pallete[255].b 	= 63;

  pallete[0].r 	= 0;  // This is the color used for the text & Lines
  pallete[0].g 	= 0;
  pallete[0].b 	= 0;

  set_pallete(pallete);
}

void set_mix_palette()
{  	
	// fill our pallete with a gradually altering sequence of colors
  for (i=0; i<256; i++) 
	{
		red = i*redStep + nRedStart;
		grn = i*grnStep + nGrnStart;
		blu = i*bluStep + nBluStart;
	
		Apply_The_Color();


    if (red/4 > 63)
      red = 1;
    if (grn/4 > 63)
      grn = 1;
    if (blu/4 > 63)
      blu = 1;

		
		pallete[i].r = red/4;
    pallete[i].g = grn/4;
    pallete[i].b = blu/4;
  }

  pallete[255].r 	= 63;  // This is the color used for the mouse
  pallete[255].g 	= 63;
  pallete[255].b 	= 63;

  pallete[0].r 	= 0;  // This is the color used for the text & Lines
  pallete[0].g 	= 0;
  pallete[0].b 	= 0;

  set_pallete(pallete);

}

void Apply_The_Color()
{  				
	if ((red & 0x1FF) > 0xFF) 
    red = red ^ 0xFF;    // Invert the color

  if ((grn & 0x1FF) > 0xFF) 
		grn = grn ^ 0xFF;    // Invert the color
      
  if ((blu & 0x1FF) > 0xFF) 
    blu = blu ^ 0xFF;    // Invert the color

  red = red & 0xFF;
  grn = grn & 0xFF;
  blu = blu & 0xFF;

}

void palette_05()
{
	for (i=0; i<64; i++)
	{
    pallete[i].r = 0;
    pallete[i].g = 63-i;
    pallete[i].b = 63-i;

    pallete[i+64].r = i;
    pallete[i+64].g = 0;
    pallete[i+64].b = i;

    pallete[i+128].r = 63;
    pallete[i+128].g = i/2;
    pallete[i+128].b = i;

    pallete[i+192].r = i;
    pallete[i+192].g = i/2;
    pallete[i+192].b = 0;
  }

  pallete[255].r 	= 255;  // This is the color used for the mouse
  pallete[255].g 	= 255;
  pallete[255].b 	= 255;

  pallete[0].r 	= 0;  // This is the color used for the text & Lines
  pallete[0].g 	= 0;
  pallete[0].b 	= 0;

  set_pallete(pallete);
}

