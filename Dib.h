// dib.h : header file
//

#include <vfw.h>

class CDIB : public CObject
{
// Construction
public:
	CDIB();

// Attributes
public:
	BYTE * GetBits();
	BYTE * GetTempBits();

	BOOL IsValid() { return (m_hDrawDib != NULL); }
	CSize GetSize();

	HDRAWDIB m_hDrawDib;
	RGBTRIPLE * lpRGB;       // Pointer to the RGB Color Table 
	RGBTRIPLE * lpRGBTemp;       // Pointer to the RGB Color Table 

	BITMAPFILEHEADER bmpfh;
	CFile file;
	BITMAPINFOHEADER* lpDib;
	
	BYTE *lpDIBBits;           // Pointer to DIB bits
	BYTE *lpDIBTempBits;						// Pointer to DIB bits

	DWORD dwNumColors, dwColorTableSize ;
	WORD  wBitCount;
	int nHeaderSize;

	int nWidth;
	int nHeight;
	int Orig_X, Orig_Y;
	int cxDIB, cyDIB;
	DWORD dwOffbits;
 	DWORD Pixel, dwColorSize;
	CSize colorsize;
	int red, grn, blu;
	double rj, gj, bj;
	DWORD kx, ky;
	char cstr[81];

	// Convolution Kernal Array	variables
	//BYTE RK[9], GK[9], BK[9];
	double  R[9],  G[9],  B[9];				// Temporary color value arrays

	//double C[9];
	double CK[9];		// Temporary color value array

	DWORD dwPixel[9];								// Pixel locations array
	RGBTRIPLE cColor;
	RGBTRIPLE TripleSave;

	long lpx, lpy;

	BOOL bRedChange;
	BOOL bGrnChange;
	BOOL bBluChange;

// Operations
public:
	BOOL Open(const char* pzFileName);
	void Close();
	BOOL Save(LPCTSTR pzFileName);
	void Draw(CDC* pDC, CSize dim, BOOL bStretchToFit, double PrtScale, long lOffCenter);
	BOOL CreateDIB(DWORD cx, DWORD cy);
	BOOL SetPixel (DWORD Xpix, DWORD Ypix, COLORREF Color);

	BOOL ApplyDibColors(int nRed, int nGrn, int nBlu,
									  int nRedStart, int nGrnStart, int nBluStart,
									  int* iIter_Data, int* rIter_Data, int* gIter_Data, int* bIter_Data,
										int nColorOrder, int nColorMethod);

	BOOL CreateDIB_Temp(DWORD cx, DWORD cy);	
	BOOL SetPixelTemp (DWORD Xpix, DWORD Ypix, COLORREF Color);
	BOOL SpatialOperator (DWORD Xpix, DWORD Ypix, int NMAX, BOOL bTraceContour);
	BOOL CopyTemp();
	BOOL ReduceDIBSize();
	BYTE* Get_m_pDIB();

// Implementation
public:
	virtual ~CDIB();

protected:

	BYTE * m_pDIB;
	BYTE * m_pDIB_Temp;

};

