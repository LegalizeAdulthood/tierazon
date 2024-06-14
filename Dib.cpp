// dib.cpp : implementation file
//

#include "stdafx.h"
#include "Tierazon.h"
#include "dib.h"

#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIB

CDIB::CDIB()
{
	m_hDrawDib	= NULL;
	m_pDIB			= NULL;
	m_pDIB_Temp = NULL;
}

CDIB::~CDIB()
{
	Close();

	if (m_pDIB)
	{
		delete m_pDIB;
	}

	if (m_pDIB_Temp)
	{
		delete m_pDIB_Temp;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CDIB message handlers

void CDIB::Draw(CDC* pDC, CSize screen, BOOL bStretchToFit,
								double PrtScale, long lOffCenter)
{
	ASSERT(IsValid());

	cxDIB = ((BITMAPINFOHEADER*) m_pDIB)->biWidth; 
	cyDIB = ((BITMAPINFOHEADER*) m_pDIB)->biHeight;

	// Calculate the coordinates to center the object
	if (screen.cx > cxDIB)
		Orig_X = screen.cx/2 - cxDIB/2;
	else
		Orig_X = 0;

	if (screen.cy > cyDIB)
		Orig_Y = screen.cy/2 - cyDIB/2;
	else
		Orig_Y = 0;

	if (Orig_X == 0 && Orig_Y == 0)
	{
		nWidth	= -1;		// Display actual size
		nHeight = -1;
	}		

	if (bStretchToFit)
	{
		Orig_X = (int) lOffCenter/2;
		Orig_Y = (int) lOffCenter/2;
		nWidth	= screen.cx - (int) lOffCenter;    // Stretch to screen size
		nHeight = screen.cy - (int) lOffCenter;
	}
	else
	{
		nWidth	= -1;    // Don't stretch
		nHeight = -1;
	}

	DrawDibDraw (m_hDrawDib, pDC->GetSafeHdc(),
		Orig_X,			// dest left
		Orig_Y,			// dest top
		nWidth,	  		//nWidth,  ("-1" for 1 to 1)
		nHeight,			//nHeight, ("-1" for 1 to 1)
		(BITMAPINFOHEADER*) m_pDIB,
		(LPVOID) GetBits(),
		0, 			// source left
		0,			// source top
		((BITMAPINFOHEADER*) m_pDIB)->biWidth,
		((BITMAPINFOHEADER*) m_pDIB)->biHeight,
		0);
}

CSize CDIB::GetSize()
{
	return CSize( ((BITMAPINFOHEADER*) m_pDIB)->biWidth,
		((BITMAPINFOHEADER*) m_pDIB)->biHeight);
}

void CDIB::Close()
{
	if (m_hDrawDib != NULL)
	{
		DrawDibClose(m_hDrawDib);
		m_hDrawDib = NULL;
	}		
}

BOOL CDIB::Open(const char* pzFileName)
{
	Close();

	// DrawDibOpen initializes the DrawDib library and
	// returns a handle for all DrawDib operations
	if (!(m_hDrawDib = DrawDibOpen()))
		goto bail;

	// Open and read the DIB file header
	nHeaderSize = sizeof(BITMAPFILEHEADER);

	if (!file.Open(pzFileName, CFile::modeRead | CFile::typeBinary))
		goto bail;

	if (file.Read((void *) &bmpfh, nHeaderSize) != (UINT) nHeaderSize)
		goto bail;

	// Validate the DIB file header by checking the first
	// two characters for the signature "BM"
	if (bmpfh.bfType != *((WORD*) "BM"))
		goto bail;

	if (m_pDIB)
		delete m_pDIB;

	// Allocate a big chunk of global memory to store the DIB
	m_pDIB = (BYTE *) new char[bmpfh.bfSize - nHeaderSize];

	if (!m_pDIB)
		goto bail;

	// Read the DIB into the buffer 32K at a time using ReadHuge
	file.Read(m_pDIB, bmpfh.bfSize - nHeaderSize);

/*	
	if (((BITMAPINFOHEADER *) m_pDIB)->biSizeImage == 0)
	{
		// Whoever created this bitmap didn't set the biSizeImage
		// field.  It's easy to calculate, plus, the DrawDib functions
		// require it.
		BITMAPINFOHEADER huge * pDib = (BITMAPINFOHEADER * huge) m_pDIB;

      	pDib->biSizeImage = 
      		((((pDib->biWidth * pDib->biBitCount) + 31) & ~31) >> 3) * pDib->biHeight;
	}
*/
	file.Close();
	return TRUE;

bail:
	Close();
	return FALSE;
}

BOOL CDIB::Save(LPCTSTR pzFileName)
{
	lpDib = (BITMAPINFOHEADER *) m_pDIB;

	nHeaderSize = sizeof(BITMAPFILEHEADER);

	ASSERT(IsValid());

	if (!file.Open(pzFileName, CFile::modeCreate |
		CFile::modeWrite ))
	{
		AfxMessageBox("Error creating file");
		return FALSE;
	}

	// The size of the color map is determined by the number of
	// RGBQUAD structures present.  It also depends on the bit-depth
	// of the DIB.

	wBitCount = lpDib->biBitCount ;

	if (lpDib->biSize >= 36)
		dwNumColors = lpDib->biClrUsed ;
	else
		dwNumColors = 0 ;

	if (dwNumColors == 0)
	{
		if (wBitCount != 24)
		    dwNumColors = 1L << wBitCount ;
		else
		    dwNumColors = 0 ;
	}

	dwColorTableSize = dwNumColors * sizeof (RGBQUAD) ;

	// Initialize BITMAPFILEHEADER
	bmpfh.bfType				= DIB_HEADER_MARKER;  // "BM";
	bmpfh.bfSize				= lpDib->biSizeImage + 
												sizeof(BITMAPINFOHEADER) +
												nHeaderSize + dwColorTableSize;
	bmpfh.bfReserved1		= 0;
	bmpfh.bfReserved2		= 0;
	bmpfh.bfOffBits			= (DWORD)sizeof(BITMAPFILEHEADER) + 
												(DWORD)sizeof(BITMAPINFOHEADER) + dwColorTableSize;

	dwOffbits = bmpfh.bfOffBits;
		
	TRY
	{
		// Write the file header
		file.Write((LPSTR) &bmpfh, nHeaderSize);

		// Write the DIB header and the bits
		file.Write(m_pDIB, bmpfh.bfSize - nHeaderSize);
	}
	CATCH (CFileException, e)
	{
		AfxMessageBox("Error writing file");
		file.Close();
		return FALSE;
	}
	END_CATCH

	file.Close();

	return TRUE;
}

BYTE * CDIB::GetBits()
{
	// The size of the color map is determined by the number of
	// RGBQUAD structures present.  It also depends on the bit-depth
	// of the DIB.

	BITMAPINFOHEADER* lpDib = (BITMAPINFOHEADER *) m_pDIB;

	wBitCount = lpDib->biBitCount ;

	if (lpDib->biSize >= 36)
		dwNumColors = lpDib->biClrUsed ;
	else
		dwNumColors = 0 ;

	if (dwNumColors == 0)
	{
		if (wBitCount != 24)
		    dwNumColors = 1L << wBitCount ;
		else
		    dwNumColors = 0 ;
	}

	dwColorTableSize = dwNumColors * sizeof (RGBQUAD) ;

	return m_pDIB + lpDib->biSize + dwColorTableSize ;
}

BOOL CDIB::CreateDIB(DWORD cx, DWORD cy)
{
	if (m_hDrawDib != NULL)
	{
		Close();
	}

	// DrawDibOpen initializes the DrawDib library and
	// returns a handle for all DrawDib operations
	if (!(m_hDrawDib = DrawDibOpen()))
	{
		Close();
		return FALSE;
	}

	if (m_pDIB)
		delete m_pDIB;
		
	CWaitCursor cursor;	// this will automatically display a wait cursor
	// Allocate a big chunk of global memory to store the DIB
	m_pDIB = (BYTE *) new char[cx*cy*3 + sizeof(BITMAPINFOHEADER)];

	if (m_pDIB)
	{

		// Initialize BITMAPINFOHEADER
		((BITMAPINFOHEADER *) m_pDIB)->biSize 						= sizeof(BITMAPINFOHEADER);
		((BITMAPINFOHEADER *) m_pDIB)->biWidth 						= cx;
		((BITMAPINFOHEADER *) m_pDIB)->biHeight 					= cy;
		((BITMAPINFOHEADER *) m_pDIB)->biPlanes 					= 1;
		((BITMAPINFOHEADER *) m_pDIB)->biBitCount 				= 24;
		((BITMAPINFOHEADER *) m_pDIB)->biCompression			= 0;
		((BITMAPINFOHEADER *) m_pDIB)->biSizeImage				= cx * cy * 3;  // cx * cy; //cx * cy * 3;
		((BITMAPINFOHEADER *) m_pDIB)->biXPelsPerMeter		= 0;	// 3779
		((BITMAPINFOHEADER *) m_pDIB)->biYPelsPerMeter		= 0;	// 3779
		((BITMAPINFOHEADER *) m_pDIB)->biClrUsed  		    = 0;
		((BITMAPINFOHEADER *) m_pDIB)->biClrImportant			= 0;
	
		// Write something into the initial new bitmap
		for (ky = 0 ; ky < cy ; ky++)
		{
			for (kx = 0 ; kx < cx ; kx++)
			{
				//red = 128 + kx;
				//grn = ky;
				//blu = ky;

				red = grn = blu = 0; // black

				// create a grayscale
				//ntemp = (int) (((double)red + (double)blu));
				//red = ntemp;

				if ((red & 0x1FF) > 0xFF) 
					red = (red ^ 0x1FF) + 0;    // Invert the color

				if ((grn & 0x1FF) > 0xFF) 
					grn = (grn ^ 0x1FF) + 0;    // Invert the color
      
				if ((blu & 0x1FF) > 0xFF) 
					blu = (blu ^ 0x1FF) + 0;    // Invert the color

				if (!SetPixel(kx, ky, RGB(red, grn, blu)))
					return FALSE;
			}
		}

		return TRUE;
	}
	else
	{
		Close();
		return FALSE;
	}
}

BOOL CDIB::CreateDIB_Temp(DWORD cx, DWORD cy)
{
	//if (m_hDrawDib != NULL)
	//{
	//	Close();
	//}

	// DrawDibOpen initializes the DrawDib library and
	// returns a handle for all DrawDib operations
	//if (!(m_hDrawDib = DrawDibOpen()))
	//	goto bail;

	if (m_pDIB_Temp)
		delete m_pDIB_Temp;
		
	CWaitCursor cursor;	// this will automatically display a wait cursor
	// Allocate a big chunk of global memory to store the Temp DIB
	//m_pDIB_Temp = (BYTE huge *) new char[(cx+1) * (cy+1) * 3 + sizeof(BITMAPINFOHEADER)];
	m_pDIB_Temp = (BYTE *) new char[cx*cy*3 + sizeof(BITMAPINFOHEADER)];

	if (m_pDIB_Temp)
	{

		// Initialize BITMAPINFOHEADER
		((BITMAPINFOHEADER *) m_pDIB_Temp)->biSize 						= sizeof(BITMAPINFOHEADER);
		((BITMAPINFOHEADER *) m_pDIB_Temp)->biWidth 					= cx;
		((BITMAPINFOHEADER *) m_pDIB_Temp)->biHeight 					= cy;
		((BITMAPINFOHEADER *) m_pDIB_Temp)->biPlanes 					= 1;
		((BITMAPINFOHEADER *) m_pDIB_Temp)->biBitCount 				= 24;
		((BITMAPINFOHEADER *) m_pDIB_Temp)->biCompression			= 0;
		((BITMAPINFOHEADER *) m_pDIB_Temp)->biSizeImage				= cx * cy * 3;
		((BITMAPINFOHEADER *) m_pDIB_Temp)->biXPelsPerMeter		= 0;
		((BITMAPINFOHEADER *) m_pDIB_Temp)->biYPelsPerMeter		= 0;
		((BITMAPINFOHEADER *) m_pDIB_Temp)->biClrUsed  		    = 0;
		((BITMAPINFOHEADER *) m_pDIB_Temp)->biClrImportant		= 0;
	
		// Write something into the initial new bitmap
		for (ky = 0 ; ky < cy ; ky++)
		{
			for (kx = 0 ; kx < cx ; kx++)
			{
				red = kx;
				grn = 128;
				blu = ky;

				if ((red & 0x1FF) > 0xFF) 
					red = red ^ 0xFF;    // Invert the color

				if ((grn & 0x1FF) > 0xFF) 
					grn = grn ^ 0xFF;    // Invert the color
      
				if ((blu & 0x1FF) > 0xFF) 
					blu = blu ^ 0xFF;    // Invert the color

				if (!SetPixelTemp(kx, ky, RGB(red, grn, blu)))
					return FALSE;
			}
		}


		return TRUE;
	}
	else
	{
		Close();
		return FALSE;
	}
}


////////////////////////////////////////////////////////////
// Setpixel will write to a single bit (similiar to Setpixel)
//

BOOL CDIB::SetPixel (DWORD px, DWORD py, COLORREF Color)
{
	ASSERT(IsValid());
	
	cxDIB = ((BITMAPINFOHEADER*) m_pDIB)->biWidth; 
	cyDIB = ((BITMAPINFOHEADER*) m_pDIB)->biHeight;

	if (px >= (DWORD)cxDIB || px < 0)
	{
		wsprintf(cstr,"Error, X Pixel = %ld, out of range", px);
		AfxMessageBox(cstr);
		return FALSE;
	}

	if (py >= (DWORD)cyDIB || py < 0)
	{
		wsprintf(cstr,"Error, Y Pixel = %ld, out of range", py);
		AfxMessageBox(cstr);
		return FALSE;
	}
	
  lpDIBBits = GetBits();
  lpRGB = (RGBTRIPLE *) lpDIBBits;
  
	//DWORD Pixel = (DWORD) (((DWORD) (dim.cy - 1 - py)
	//	 																	* (DWORD) dim.cx) + (DWORD) px);

 	Pixel = px + py * cxDIB;

	//lpDIBBits[Pixel] = Color;
	
	lpRGB[Pixel].rgbtRed   = GetRValue(Color);
  lpRGB[Pixel].rgbtGreen = GetGValue(Color);
  lpRGB[Pixel].rgbtBlue  = GetBValue(Color);

 	return TRUE;
}

////////////////////////////////////////////////////////////
// SetPixelTemp will write to a single bit (similiar to Setpixel)
//
BOOL CDIB::SetPixelTemp (DWORD px, DWORD py, COLORREF Color)
{
	ASSERT(IsValid());

	cxDIB = ((BITMAPINFOHEADER*) m_pDIB_Temp)->biWidth; 
	cyDIB = ((BITMAPINFOHEADER*) m_pDIB_Temp)->biHeight;

	if (px >= (DWORD)cxDIB || px < 0)
	{
		wsprintf(cstr,"Error, X Pixel = %ld, out of range", px);
		AfxMessageBox(cstr);
		return FALSE;
	}

	if (py >= (DWORD)cyDIB || py < 0)
	{
		wsprintf(cstr,"Error, Y Pixel = %ld, out of range", py);
		AfxMessageBox(cstr);
		return FALSE;
	}
	
  lpDIBTempBits = GetTempBits();
  lpRGBTemp = (RGBTRIPLE *) lpDIBTempBits;
  
	//DWORD Pixel = (DWORD) (((DWORD) (dim.cy - 1 - py)
	//	 																	* (DWORD) dim.cx) + (DWORD) px);

 	Pixel = px + py * cxDIB;

	//lpDIBTempBits[Pixel] = Color;
	
	lpRGBTemp[Pixel].rgbtRed   = GetRValue(Color);
  lpRGBTemp[Pixel].rgbtGreen = GetGValue(Color);
  lpRGBTemp[Pixel].rgbtBlue  = GetBValue(Color);

 	return TRUE;
}

//////////////////////////////////////////////////////
// ApplyDibColors

BOOL CDIB::ApplyDibColors(int nRed, int nGrn, int nBlu,
	int nRedStart, int nGrnStart, int nBluStart,
	int *iIter_Data, int* rIter_Data, int* gIter_Data, int* bIter_Data,
	int nColorOrder, int nColorMode)
{
	ASSERT(IsValid());
	
	cxDIB = ((BITMAPINFOHEADER*) m_pDIB)->biWidth; 
	cyDIB = ((BITMAPINFOHEADER*) m_pDIB)->biHeight;
	
  lpDIBBits = GetBits();
  lpRGB = (RGBTRIPLE *) lpDIBBits;
  
	colorsize = GetSize();
	dwColorSize = (DWORD) (colorsize.cx * colorsize.cy);

	for (Pixel = 0; Pixel< dwColorSize; Pixel++)
	{
		rj = (double)rIter_Data[Pixel];
		gj = (double)gIter_Data[Pixel];
		bj = (double)bIter_Data[Pixel];
		
//		red = r*nRed+nRedStart;  // Generalized Coloring Method
//		grn = g*nGrn+nGrnStart;
//		blu = b*nBlu+nBluStart;

		//if (iIter_Data[Pixel] == 0 && nColorMethod == 0)
		if (iIter_Data[Pixel] == 0)
		{			
			lpRGB[Pixel].rgbtRed		= 0;
			lpRGB[Pixel].rgbtGreen	= 0;
			lpRGB[Pixel].rgbtBlue		= 0;
		}
		else
		{
			switch (nColorOrder)
			{
			case 0:		// rgb
				red = (int) (rj*(double)(nRed))+nRedStart;
				grn = (int) (gj*(double)(nGrn))+nGrnStart;
				blu = (int) (bj*(double)(nBlu))+nBluStart;
				break;

			case 1:		// rbg
				red = (int) (rj*(double)(nRed))+nRedStart;
				grn = (int) (bj*(double)(nGrn))+nGrnStart;
				blu = (int) (gj*(double)(nBlu))+nBluStart;
				break;

			case 2:		// grb
				red = (int) (gj*(double)(nRed))+nRedStart;
				grn = (int) (rj*(double)(nGrn))+nGrnStart;
				blu = (int) (bj*(double)(nBlu))+nBluStart;
				break;

			case 3:		// gbr
				red = (int) (gj*(double)(nRed))+nRedStart;
				grn = (int) (bj*(double)(nGrn))+nGrnStart;
				blu = (int) (rj*(double)(nBlu))+nBluStart;
				break;

			case 4:		// brg
				red = (int) (bj*(double)(nRed))+nRedStart;
				grn = (int) (rj*(double)(nGrn))+nGrnStart;
				blu = (int) (gj*(double)(nBlu))+nBluStart;
				break;

			case 5:		// bgr
				red = (int) (bj*(double)(nRed))+nRedStart;
				grn = (int) (gj*(double)(nGrn))+nGrnStart;
				blu = (int) (rj*(double)(nBlu))+nBluStart;
				break;
			}

			if (nColorMode == I_SEE_DA_LIGHT)
			{
				if (red < 0)
					red = 0;

				if (grn < 0)
					grn = 0;

				if (blu < 0)
					blu = 0;
				
				if (red > 255)
					red = 255;

				if (grn > 255)
					grn = 255;

				if (blu > 255)
					blu = 255;
			}

			if ((red & 0x1FF) > 0xFF) 
				red = red ^ 0xFF;    // Invert the color

			if ((grn & 0x1FF) > 0xFF) 
				grn = grn ^ 0xFF;    // Invert the color
      
			if ((blu & 0x1FF) > 0xFF) 
				blu = blu ^ 0xFF;    // Invert the color

			lpRGB[Pixel].rgbtRed		= (BYTE) red;
			lpRGB[Pixel].rgbtGreen	= (BYTE) grn;
			lpRGB[Pixel].rgbtBlue		= (BYTE) blu;
		}
	}
	return TRUE;
}

////////////////////////////////////////////////////////////
// Spatial Operator
//
BOOL CDIB::SpatialOperator (DWORD px, DWORD py, int NMAX, BOOL bTraceContour)
{
	ASSERT(IsValid());

	if (NMAX > 0) NMAX -= 1;
	
	//BYTE cColor;	

	lpx = (long) px;
	lpy = (long) py;

	cxDIB = ((BITMAPINFOHEADER*) m_pDIB)->biWidth; 
	cyDIB = ((BITMAPINFOHEADER*) m_pDIB)->biHeight;

	if (lpx >= (long) cxDIB || lpx < 0)
	{
		wsprintf(cstr,"Error, X Pixel = %ld, out of range", lpx);
		AfxMessageBox(cstr);
		return FALSE;
	}

	if (lpy >= (long) cyDIB || lpy < 0)
	{
		wsprintf(cstr,"Error, Y Pixel = %ld, out of range", lpy);
		AfxMessageBox(cstr);
		return FALSE;
	}
	
  lpDIBBits = GetBits();
  lpRGB = (RGBTRIPLE *) lpDIBBits;
  
	// Temp buffer pointer
	lpDIBTempBits = GetTempBits();
  lpRGBTemp = (RGBTRIPLE *) lpDIBTempBits;
	
 	// Get the Current Pixel Position
	Pixel = px + py * cxDIB;

	// Get the current color
	//cColor = lpDIBBits[Pixel];		
	cColor.rgbtRed		= lpRGB[Pixel].rgbtRed;
	cColor.rgbtGreen	= lpRGB[Pixel].rgbtGreen;
	cColor.rgbtBlue		= lpRGB[Pixel].rgbtBlue;

	/////////////////////////////
	// 3x3 Pixel numbering scheme
 	/////////////////////////////
	// 1  2  3
	// 4	0	 5
	// 6	7	 8
	/////////////////////////////
	
	dwPixel[0] = lpx + lpy * (long) cxDIB;		// Get center pixel offset

	//if (cColor != 1)
		//BYTE bug = cColor;
		
	// Get center pixel current value
	R[0] = cColor.rgbtRed;
	G[0] = cColor.rgbtGreen;
	B[0] = cColor.rgbtBlue;

	// Get dwPixel[1] (left, top)
	if (lpx - 1 < 0 || lpy + 1 >= (long) cyDIB)
	{
		// Out of range, set to center color
		R[1]   = cColor.rgbtRed;
		G[1]   = cColor.rgbtGreen;
		B[1]   = cColor.rgbtBlue;
	}
	else
	{
		dwPixel[1] = lpx - 1 + ((lpy + 1) * (long) cxDIB);
		//R[1] = lpDIBBits[dwPixel[1]];
		R[1] = lpRGB[dwPixel[1]].rgbtRed;
		G[1] = lpRGB[dwPixel[1]].rgbtGreen;
		B[1] = lpRGB[dwPixel[1]].rgbtBlue;
	}		
		
	// Get dwPixel[2] (center, top)
	if (lpy + 1 >= (long) cyDIB)
	{
		// Out of range, set to center color
		R[2] = cColor.rgbtRed;
		G[2] = cColor.rgbtGreen;
		B[2] = cColor.rgbtBlue;
	}
	else
	{
		dwPixel[2] = lpx + ((lpy + 1) * (long) cxDIB);
		//R[2] = lpDIBBits[dwPixel[2]];
		R[2] = lpRGB[dwPixel[2]].rgbtRed;
		G[2] = lpRGB[dwPixel[2]].rgbtGreen;
		B[2] = lpRGB[dwPixel[2]].rgbtBlue;
	}		
		
	// Get dwPixel[3] (right, top)
	if (lpx + 1 >= (long)cxDIB || lpy + 1 >= (long)cyDIB)
	{
		// Out of range, set to center color
		R[3] = cColor.rgbtRed;
		G[3] = cColor.rgbtGreen;
		B[3] = cColor.rgbtBlue;
	}
	else
	{
		dwPixel[3] = lpx + ((lpy + 1) * (long)cxDIB);
		//R[3] = lpDIBBits[dwPixel[3]];
		R[3] = lpRGB[dwPixel[3]].rgbtRed;
		G[3] = lpRGB[dwPixel[3]].rgbtGreen;
		B[3] = lpRGB[dwPixel[3]].rgbtBlue;
	}		
		
	// Get dwPixel[4] (left, center)
	if (lpx - 1 < 0)
	{
		// Out of range, set to center color
		R[4] = cColor.rgbtRed;
		G[4] = cColor.rgbtGreen;
		B[4] = cColor.rgbtBlue;
	}
	else
	{
		dwPixel[4] = lpx - 1 + (lpy * (long)cxDIB);
		//R[4] = lpDIBBits[dwPixel[4]];
		R[4] = lpRGB[dwPixel[4]].rgbtRed;
		G[4] = lpRGB[dwPixel[4]].rgbtGreen;
		B[4] = lpRGB[dwPixel[4]].rgbtBlue;
	}		
		
	// Get dwPixel[5] (right, center)
	if (lpx + 1 >= (long)cxDIB)
	{
		// Out of range, set to center color
		R[5] = cColor.rgbtRed;
		G[5] = cColor.rgbtGreen;
		B[5] = cColor.rgbtBlue;
	}
	else
	{
		dwPixel[5] = lpx + 1 + (lpy * (long)cxDIB);
		//R[5] = lpDIBBits[dwPixel[5]];
		R[5] = lpRGB[dwPixel[5]].rgbtRed;
		G[5] = lpRGB[dwPixel[5]].rgbtGreen;
		B[5] = lpRGB[dwPixel[5]].rgbtBlue;
	}		
		
	// Get dwPixel[6] (left, bottom)
	if (lpx - 1 < 0 || lpy - 1 < 0)
	{
		// Out of range, set to center color
		R[6] = cColor.rgbtRed;
		G[6] = cColor.rgbtGreen;
		B[6] = cColor.rgbtBlue;
	}
	else
	{
		dwPixel[6] = lpx - 1 + ((lpy - 1) * (long)cxDIB);
		//R[6] = lpDIBBits[dwPixel[6]];
		R[6] = lpRGB[dwPixel[6]].rgbtRed;
		G[6] = lpRGB[dwPixel[6]].rgbtGreen;
		B[6] = lpRGB[dwPixel[6]].rgbtBlue;
	}		
		
	// Get dwPixel[7] (center, bottom)
	if (lpy - 1 < 0)
	{
		// Out of range, set to center color
		R[7] = cColor.rgbtRed;
		G[7] = cColor.rgbtGreen;
		B[7] = cColor.rgbtBlue;
	}
	else
	{
		dwPixel[7] = lpx + ((lpy - 1) * (long)cxDIB);
		//R[7] = lpDIBBits[dwPixel[7]];
		R[7] = lpRGB[dwPixel[7]].rgbtRed;
		G[7] = lpRGB[dwPixel[7]].rgbtGreen;
		B[7] = lpRGB[dwPixel[7]].rgbtBlue;
	}		
		
	// Get dwPixel[8] (right, bottom)
	if (lpx + 1 >= (long)cxDIB || lpy - 1 < 0)
	{
		// Out of range, set to center color
		R[8] = cColor.rgbtRed;
		G[8] = cColor.rgbtGreen;
		B[8] = cColor.rgbtBlue;
	}
	else
	{
		dwPixel[8] = lpx + 1 + ((lpy - 1) * (long)cxDIB);
		//R[8] = lpDIBBits[dwPixel[8]];
		R[8] = lpRGB[dwPixel[8]].rgbtRed;
		G[8] = lpRGB[dwPixel[8]].rgbtGreen;
		B[8] = lpRGB[dwPixel[8]].rgbtBlue;
	}		
		
	/////////////////////////////
	// 3x3 Pixel numbering scheme
 	/////////////////////////////
	// 1  2  3
	// 4	0	 5
	// 6	7	 8
	/////////////////////////////
	
	/////////////////////////////
	// 3x3 Pixel numbering scheme
	// Emboss Kernal
 	/////////////////////////////
	// -1  0  0
	//  0	 0	0
	//  0	 0	1
	/////////////////////////////
	
//	// check Pixels for change
	bRedChange = FALSE;
	bGrnChange = FALSE;
	bBluChange = FALSE;

	for (int l=0 ; l<9 ; l++)
	{
		if (cColor.rgbtRed		!= R[l])
			bRedChange = TRUE;
		if (cColor.rgbtGreen	!= G[l])
			bGrnChange = TRUE;
		if (cColor.rgbtBlue		!= B[l])
			bBluChange = TRUE;
	}	

	if (!bTraceContour)
	{
		bRedChange = TRUE;
		bGrnChange = TRUE;
		bBluChange = TRUE;
	}

	if (bRedChange)
	{
		// Define Convolution Kernel weights
		R[0] = (R[0]*CK[0] + 
				  R[1]*CK[1] +	
				  R[2]*CK[2] +	
				  R[3]*CK[3] +	
				  R[4]*CK[4] +	
				  R[5]*CK[5] +	
				  R[6]*CK[6] +	
				  R[7]*CK[7] +	
				  R[8]*CK[8]);	

		red = (int) R[0];

		if (red < 0)
			red = 0;

		if (red > 255)
			red = 255;

		lpRGBTemp[Pixel].rgbtRed		= red;

	}
	else
		lpRGBTemp[Pixel].rgbtRed		= cColor.rgbtRed;

	if (bGrnChange)
	{
		G[0] = (G[0]*CK[0] + 
				  G[1]*CK[1] +	
				  G[2]*CK[2] +	
				  G[3]*CK[3] +	
				  G[4]*CK[4] +	
				  G[5]*CK[5] +	
				  G[6]*CK[6] +	
				  G[7]*CK[7] +	
				  G[8]*CK[8]);	

		grn = (int) G[0];

		if (grn < 0)
			grn = 0;

		if (grn > 255)
			grn = 255;

		lpRGBTemp[Pixel].rgbtGreen	= grn;

	}
	else
		lpRGBTemp[Pixel].rgbtGreen	= cColor.rgbtGreen;

	if (bBluChange)
	{
		B[0] = (B[0]*CK[0] + 
				  B[1]*CK[1] +	
				  B[2]*CK[2] +	
				  B[3]*CK[3] +	
				  B[4]*CK[4] +	
				  B[5]*CK[5] +	
				  B[6]*CK[6] +	
				  B[7]*CK[7] +	
				  B[8]*CK[8]);
		
		blu = (int) B[0];
		
		if (blu < 0)
			blu = 0;

		if (blu > 255)
			blu = 255;

		lpRGBTemp[Pixel].rgbtBlue		= blu;
	}
	else
		lpRGBTemp[Pixel].rgbtBlue		= cColor.rgbtBlue;
	
	return TRUE;
}

BOOL CDIB::CopyTemp()
{
	ASSERT(IsValid());
	
	//BYTE ByteSave;

	cxDIB = ((BITMAPINFOHEADER*) m_pDIB)->biWidth; 
	cyDIB = ((BITMAPINFOHEADER*) m_pDIB)->biHeight;

	if (m_pDIB_Temp && m_pDIB)
	{

		lpDIBBits = GetBits();
		lpRGB = (RGBTRIPLE *) lpDIBBits;
  
		// Temp buffer pointer
		lpDIBTempBits = GetTempBits();
		lpRGBTemp = (RGBTRIPLE *) lpDIBTempBits;
	
		// Swap bits with the temp buffer
		for (int y = 0 ; y<cxDIB*cyDIB ; y++)
		{
			//ByteSave = lpDIBBits[y];
			//lpDIBBits[y] = lpDIBTempBits[y];
			//lpDIBTempBits[y] = ByteSave;

			TripleSave.rgbtRed		= lpRGB[y].rgbtRed;
			TripleSave.rgbtGreen	= lpRGB[y].rgbtGreen;
			TripleSave.rgbtBlue		= lpRGB[y].rgbtBlue;
			
			lpRGB[y].rgbtRed		= lpRGBTemp[y].rgbtRed;
			lpRGB[y].rgbtGreen	= lpRGBTemp[y].rgbtGreen;
			lpRGB[y].rgbtBlue		= lpRGBTemp[y].rgbtBlue;

			lpRGBTemp[y] = TripleSave;

		}
		
		//delete m_pDIB;
		//m_pDIB = m_pDIB_Temp;
		//m_pDIB_Temp = NULL;

		return TRUE;
	}	
	else
		return FALSE;		
}

BYTE * CDIB::GetTempBits()
{
	// The size of the color map is determined by the number of
	// RGBQUAD structures present.  It also depends on the bit-depth
	// of the DIB.

	lpDib = (BITMAPINFOHEADER *) m_pDIB_Temp;

	wBitCount = lpDib->biBitCount ;

	if (lpDib->biSize >= 36)
		dwNumColors = lpDib->biClrUsed ;
	else
		dwNumColors = 0 ;

	if (dwNumColors == 0)
	{
		if (wBitCount != 24)
		    dwNumColors = 1L << wBitCount ;
		else
		    dwNumColors = 0 ;
	}

	dwColorTableSize = dwNumColors * sizeof (RGBQUAD) ;

	return m_pDIB_Temp + lpDib->biSize + dwColorTableSize ;
}

BOOL CDIB::ReduceDIBSize()
{
	// Reduce the size of the image by one-half
	ASSERT(IsValid());
	
	cxDIB = ((BITMAPINFOHEADER*) m_pDIB)->biWidth; 
	cyDIB = ((BITMAPINFOHEADER*) m_pDIB)->biHeight;

	if (m_pDIB_Temp && m_pDIB)
	{
		lpDIBBits = GetBits();
		lpRGB = (RGBTRIPLE *) lpDIBBits;
  
		// Temp buffer pointer
		lpDIBTempBits = GetTempBits();
		lpRGBTemp = (RGBTRIPLE *) lpDIBTempBits;
	
		// Swap bits with the temp buffer

		int x_temp = 0;
		int y_temp = 0;
		int Pixel_temp;
		for (int y = 0 ; y<cyDIB ; y+=2)
		{		
			x_temp = 0;
			for (int x = 0 ; x<cxDIB ; x+=2)
			{
			 	Pixel = x + y * cxDIB;
				Pixel_temp = x_temp + y_temp * cxDIB/2;
				lpRGBTemp[Pixel_temp] = lpRGB[Pixel];
				x_temp++;
			}
			y_temp++;
		}
		
		return TRUE;
	}	
	else
		return FALSE;		
}

// Used by AVI file routines
BYTE* CDIB::Get_m_pDIB()
{
	return m_pDIB;
}
