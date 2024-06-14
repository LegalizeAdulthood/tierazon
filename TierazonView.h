// TierazonView.h : interface of the CTierazonView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIERAZONVIEW_H__09FDBB2F_6F08_11D1_9E84_444553540000__INCLUDED_)
#define AFX_TIERAZONVIEW_H__09FDBB2F_6F08_11D1_9E84_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

typedef struct tagRGB_IDATA
{
	double i;
	double rj;
	double gj;
	double bj;
} RGB_IDATA;

typedef RGB_IDATA (WINAPI *DLLFUNC) (double, double, double, double, int, int);
typedef RGB_IDATA (WINAPI *DLLCOLOR) (int, int, int, double, double, double, double);
typedef void (WINAPI *DLLINIT) (int, int, int, int, int, int, int, double, double, double, double, double, double*, double*, double*, double*, double*, double*, double*, int, int, int, int, int, int, int, int, int, int, int);
typedef int (WINAPI *DLLFILTER) (double, double, int);
typedef RGB_IDATA (WINAPI *DLLCOMPLETE) ();

#include "cmplx.h"

class   		CGradient;
class				CConvolut;
class				CMovie;

class CTierazonView : public CScrollView
{
protected: // create from serialization only
	CTierazonView();
	DECLARE_DYNCREATE(CTierazonView)

// Attributes
public:
	CTierazonDoc* GetDocument();

// Operations
public:
	// DLL parameters /////////////////////////
	HINSTANCE			hLib{};

  DLLFUNC				lpfnFormulae;
	DLLCOLOR			lpfnColorUpdate;
	DLLINIT				lpfnInitialize;
	DLLFILTER			lpfnFilter;
	DLLCOMPLETE		lpfnComplete;

	RGB_IDATA			rgbColor;
	
	BOOL					bMFilter;
	BOOL					bColorInvert;
	BOOL					bGrayScale;
	BOOL					bFirstView;
	BOOL					bAutoAntialias;
	BOOL					bAutoAntialias_Init;
	int 					nUsingBuffers;

  char buf[260];

	// AVI File Attributes
	CString				AVIFileName;
	BOOL					bLockStart;
	BOOL					bLockFinish;
	BOOL					bStartMovie;
	BOOL 					bZoomStart;
	BOOL					bPositive;
	BOOL					bPositiveX;
	BOOL					bPositiveY;

	double				CRMID_MovieStart;
	double 				CRMID_MovieFinish;
	double				CIMID_MovieStart;
	double				CIMID_MovieFinish;
	double				CRMID_FrameRatio;
	double				CIMID_FrameRatio;
	double				dMovieMagnifStart;
	double				dMovieMagnifFinish;
	double				dMovieFrameRatio;
	double				dMagnification_Start;
	double				dMagnification_Finish;

	PAVIFILE							pfile;
	PAVIFILE							pf_new;
	PAVISTREAM						pstream;
	PAVISTREAM						ps_new;
	PGETFRAME							pget;
	LPBITMAPINFOHEADER		lpbi;
	LPBITMAPINFOHEADER		biNew;
	HRESULT								hr;
	DWORD									dwMovieRate;

	AVISTREAMINFO					strhdr;
	AVISTREAMINFO					newstr;	

	BITMAPINFOHEADER			bi;
	long									lStreamSize;
	
	BOOL									bAVIFileOpen;
	BOOL									bAVIPlaying;
	BOOL									bMovieView;
	BOOL									bJuliaVideoMode;
	BOOL									bOrientationVideoMode;

	LONG									frame, frames;
	CString								szFrameNumber;
	CString								szTotalFrames;
	UINT									tmillisecs;
	UINT									timer;
	WORD									bitcount;				

	CMovie*								m_pMovieView;

	///////////////////////////////////////////	
	// Fractal dimension variables
	int						i2, jrw, bDimensionVariant;
	double				x_std, y_std, dm, da;
	double				denominator, x_rmin, x_rmax, y_rmin, y_rmax;

	// Data array pointers
	double				*pXTemp;
	double				*pYTemp;

	double				*rjData;
	double				*gjData;
	double				*bjData;

	double				*pXSave;
	double				*pYSave;
	
	cmplx					cx_std;
	cmplx					cy_std;
	cmplx					cFDx;
	cmplx					cFDy;
	cmplx					cRng_x;
	cmplx					cRng_y;
	cmplx					cNMAX;

	double				dFDx;	// Fractal Dimension x
	double				dFDy; // Fractal Dimension y

	double				dFDx_0;	// Initial F Dimension x
	double				dFDy_0; // Initial F Dimension y

	int						nDIter_x;
	int						nDIter_y;
	int						nFDOption;
	int						NMAX_Save;
	int						nColorMethod;
	int						nColorMode;
	int						nColorMethodSave;
	int						min, max;
	int						ntemp;

	int						nFormulaType;

	int						nFilterSave;
	int						nDistortionSave;
	int						nFDOptionSave;

	// Average variables
	double				x_mean;
	double				y_mean;
	////////////////////////////////////////////
	
	CGradient* 		m_pGradView;
	CConvolut*		m_pConvolutView;

	CString				Convo_Title;

	CSize					dim, dim_save;
	CSize					screen;
	CSize					size;

	CRect					clientRect;
	CRect					outputRect;
	CRect					DIBRect;
	CRect					rrect;
	CRect					rsave;

	CPoint				spt;  // Scroll position

	CString				ActiveTitle;
	CString				mClassName;

	long					lOffCenter;

	double				PrtScale;
	double				CrtScale;
	double				dMIN;
	double				dzx, dzy;	
	double				dzx_save, dzy_save;
	double				temp, temp1, temp2;
	double				x_temp, y_temp, length;
	double				x_temp1, y_temp1;
	double				dUpper, dLower;
	double				rr, rn;
	double				deg;

	char					cstr[1024];
	char					ctitle[150];

	CString				szTemp;
  CStdioFile    outFile;

	BOOL					bRedStart, bGrnStart, bBluStart;
	BOOL					bGradient;
	BOOL					bStretchToFit;
	BOOL					bFitToPage;
	BOOL  				bTracker;
	BOOL					*bRed, *bGrn, *bBlu;
	BOOL					bForward;
	BOOL					bInitialized;
	BOOL					bGenesisMode;
	BOOL					bInvertFractal;
	BOOL					bZeroInit;

	BOOL					bEdgeDetect;
	BOOL					bEmboss;
	BOOL					bSharpen;
	BOOL					bBlur;
	BOOL					bAverage;
	BOOL					bTraceContour;
	BOOL					bReduceSize;
	BOOL					bColorize;
	
	double   			rj, gj, bj;
	int						xi, yi, ii;
	int 					red, grn, blu;
	int 					nRed, nGrn, nBlu;
	int  					nRedStart, nGrnStart, nBluStart;

	int						*iIter_Data;
	int						*rIter_Data;
	int						*gIter_Data;
	int						*bIter_Data;

	int						rb_avg;
	int						cxDIB;
	int						cyDIB;
	int						nImageSize;
	int 					nXpix, nYpix;
	int						rb_width;
	int						rb_height;
	int						rb_center_x;
	int						rb_center_y;
	int						dim_avg;
	int						nFilter;
	int						nColorOrder;
	int						kr, kc;
	int						UBANDS;
	int						nMatrix;
	int						n_color_sav;

	BYTE					color;

	HCURSOR				mHCross;
	HCURSOR				mHSize;
	HCURSOR				mWait;

	DWORD					dwColor;
	UINT					uTimer1;

	// Constants used for mandelbrot pattern
	// define Mandelbrot set constants:
	double				CIMAX; 				//  1.2
	double				CIMIN; 				// -1.2
	double				CRMAX; 				//  1.0
	double				CRMIN; 				// -2.0

	double				CIMAX_JUL; 		//  1.5
	double				CIMIN_JUL; 		// -1.5
	double				CRMAX_JUL; 		//  1.5
	double				CRMIN_JUL; 		// -1.5

	double  			CIMAX_OLD; 		//  1.2
	double				CIMIN_OLD; 		// -1.2
	double				CRMAX_OLD; 		//  1.0
	double				CRMIN_OLD; 		// -2.0

	double				CRMID;				// rubber band x mid point
	double				CIMID;				// rubber band y mid point
	double				CRMID_Start;	// rubber band x mid point finish
	double				CIMID_Start;	// rubber band y mid point finish
	double				CRMID_Finish;	// rubber band x mid point finish
	double				CIMID_Finish;	// rubber band y mid point finish

	double  			CIMAX_NEW; 		//  1.2
	double  			CIMIN_NEW; 		// -1.2
	double  			CRMAX_NEW; 		//  1.0
	double 				CRMIN_NEW; 		// -2.0

	double				CRMID_OLD; 		
	double				CIMID_OLD; 
	
	double				CRMID_JUL; 		
	double				CIMID_JUL;
	
	double				dMag_new;
	double				dMagnification;
	double				Radius_x;
	double				Radius_y;

	int						dBiomorph;
	double				rorder_r;
	double				rorder_i;
	double				dBay100, dBay1000;
	double				dStrands, dStrands_HI, dStrands_LO;
	double				limit;

	double				rx_ratio, ry_ratio;
	double				dx_length, dy_length;

	double				zx, zy;
	
	///////////////////////////////////////////////////////
	// Variables for the Mandelbrot fractal
	BOOL bDraw;
	BOOL bLaunch;
	BOOL bAbort;
  BOOL bGeometry;

  int 					RowMax;
	int 					Row;
 	int 					Col;
  int 					ColMax;

	int						size_x, size_y;

  double				CR;
  double  			DCI;
  double				DCR;
	int 					NMAX;
	int 					temp_max;
	int 					Orig_X, Orig_Y;
	int		 				dBailout;
	double				cxx, cyy;
  int  					nDistortion;

	int						nDistortion_sav;
	int						nFilter_sav;
	int						nColorMethod_sav;
	int						nFDOption_sav;

 	int niter,            /* maximum number of iterations */
    px, py,             /* current pixel */
    nx, ny,             /* number of pixels */
    nc,                 /* number of colors to use */
    i, j,               /* counters for miscellaneous use */
    jul,                /* 1 = Julia Set,  0 = Mandelbrot */
    jul_save;

	double ri;

	double        x, y,									/* last point on orbit */
								xsquared, ysquared,		/* used to speed up computations */
								ldx, ldy,          		/* theoretical size of pixels */
								cx, cy,           		/* number to add each iteration */
								xO, yO,           		/* starting x,y */
								xI, yI;           		/* ending x,y */


	cmplx					c;  
	cmplx					cn;  
  cmplx					z;
  cmplx					z1;
  cmplx					z2;
	cmplx					cOrient;
  cmplx         uu;
  cmplx         vv;
  cmplx         ww;

	CRect					rubberBand, rubberBandSave;
	
	double				rb_left;
	double				rb_top;
	double				rb_right;
	double				rb_bottom;
		
	double				sxmin;
  double				symin; 
	double				sxmax;
  double				symax; 
	double				x_size;
	double				y_size;

  // Formulae parser variables 
  double        u_real, v_real, w_real, z_real;
  double        u_imag, v_imag, w_imag, z_imag;
  CString       strFormulae;

  #include "Expression.h"
  MExpression*  ParsedExpr;

// Operations
public:
	void Size_Desktop_Window();
	void Window_Pane(int nStat);
	void Status_Bar(char* bar_txt);
  void Clearselection(BOOL bValid);
  void DrawPattern();
  void GeneratePattern();
  void LaunchPattern();
  void TestPattern();
  void TestPatternSub();
  void GoDoFractal();
  void TestEquations();
	void Apply_The_Color();
	void Shift_Step();
	void Apply_Color();
	void Generalized_Coloring_Method();		
	void Terminate();
	void Saveparameters();
	void Loadparameters();
	void ViewNew();
	void Filter();
	void Filter_Complete();
	void adjust_coords();
	void OnEditUndofractalselection();
	void ConvolutionDialog();
	void UpdateColorMethod();
	void Returning_From_DLL();
	//void FDimension();

	void UpdateMovieData();
	void CloseAVIFile();
	void GenerateAMovie();
	void SaveForUndo();
	void Load_DLL();

	// DLL function calls
	RGB_IDATA save_stdcall(DLLFUNC func, double cx, double cy, double zx, double zy, int px, int py);
	RGB_IDATA color_stdcall(DLLCOLOR func, int px, int py, int nColorMethod, double cx, double cy, double zx, double zy);
	void init_stdcall(DLLINIT func, int nFormula, int nFilter, int nColorMethod, int dBailout, int NMAX, int _jul, int _jul_save, double _dStrands, double _dBay100, double _dBay1000, double _dLower, double _dUpper, double *pXTemp, double *pYTemp, double *pXSave, double *pYSave, double *rjData, double *gjData, double *bjData, int nRed, int nGrn, int nBlu, int nRedStart, int nGrnStart, int nBluStart, int nFDOption, int bDimensionVariant, int size_x, int size_y, int nUsingBuffers);
	int filter_stdcall(DLLFILTER func, double zx, double zy, int i);
	RGB_IDATA complete_stdcall(DLLCOMPLETE func);

	///////////////////////////////////////////////////////////////////
	// Modeless Dialog message routines
	long OnApply_GradView(UINT wParam, LONG lParam);
	long OnApply_ShiftView(UINT wParam, LONG lParam);
	long OnApply_AffineView(UINT wParam, LONG lParam);

  // Formulae Parser Functions
  //cmplx ParseExpression( const char* str, int& index );
  //cmplx ParseOperand( const char* str, int& index );
  MExpression* ParseExpression( const char* str, int& index );
  MExpression* ParseOperand( const char* str, int& index );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTierazonView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTierazonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CTierazonView)
	afx_msg LONG CancelMovie(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSaveDib();
	afx_msg void OnWindowSizedesktop();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnImageSize();
	afx_msg void OnViewZoom();
	afx_msg void OnUpdateViewZoom(CCmdUI* pCmdUI);
	afx_msg void OnViewNew();
	afx_msg void OnUpdateViewNew(CCmdUI* pCmdUI);
	afx_msg void OnFileSavecolors();
	afx_msg void OnFileSaveparameters();
	afx_msg void OnFileLoadcolors();
	afx_msg void OnFileLoadparameters();
	afx_msg void OnViewJulia();
	afx_msg void OnUpdateViewJulia(CCmdUI* pCmdUI);
	afx_msg void OnImageParams();
	afx_msg void OnDrawAbort();
	afx_msg void OnUpdateDrawAbort(CCmdUI* pCmdUI);
	afx_msg void OnShiftStart();
	afx_msg void OnUpdateShiftStart(CCmdUI* pCmdUI);
	afx_msg void OnImageColorparameters();
	afx_msg void OnUpdateImageColorparameters(CCmdUI* pCmdUI);
	afx_msg void OnImageAspectratio();
	afx_msg void OnUpdateImageAspectratio(CCmdUI* pCmdUI);
	afx_msg void OnImageClear();
	afx_msg void OnViewMandel();
	afx_msg void OnUpdateViewMandel(CCmdUI* pCmdUI);
	afx_msg void OnDraw1();
	afx_msg void OnUpdateDraw1(CCmdUI* pCmdUI);
	afx_msg void OnDrawInsideout();
	afx_msg void OnUpdateDrawInsideout(CCmdUI* pCmdUI);
	afx_msg void OnDraw2();
	afx_msg void OnUpdateDraw2(CCmdUI* pCmdUI);
	afx_msg void OnDraw3();
	afx_msg void OnUpdateDraw3(CCmdUI* pCmdUI);
	afx_msg void OnDraw4();
	afx_msg void OnUpdateDraw4(CCmdUI* pCmdUI);
	afx_msg void OnDraw5();
	afx_msg void OnUpdateDraw5(CCmdUI* pCmdUI);
	afx_msg void OnDraw6();
	afx_msg void OnUpdateDraw6(CCmdUI* pCmdUI);
	afx_msg void OnDraw7();
	afx_msg void OnUpdateDraw7(CCmdUI* pCmdUI);
	afx_msg void OnDraw8();
	afx_msg void OnUpdateDraw8(CCmdUI* pCmdUI);
	afx_msg void OnDraw9();
	afx_msg void OnUpdateDraw9(CCmdUI* pCmdUI);
	afx_msg void OnDraw10();
	afx_msg void OnUpdateDraw10(CCmdUI* pCmdUI);
	afx_msg void OnDraw11();
	afx_msg void OnUpdateDraw11(CCmdUI* pCmdUI);
	afx_msg void OnDraw12();
	afx_msg void OnUpdateDraw12(CCmdUI* pCmdUI);
	afx_msg void OnDraw13();
	afx_msg void OnUpdateDraw13(CCmdUI* pCmdUI);
	afx_msg void OnDraw14();
	afx_msg void OnUpdateDraw14(CCmdUI* pCmdUI);
	afx_msg void OnDraw15();
	afx_msg void OnUpdateDraw15(CCmdUI* pCmdUI);
	afx_msg void OnDraw16();
	afx_msg void OnUpdateDraw16(CCmdUI* pCmdUI);
	afx_msg void OnDraw17();
	afx_msg void OnUpdateDraw17(CCmdUI* pCmdUI);
	afx_msg void OnDraw18();
	afx_msg void OnUpdateDraw18(CCmdUI* pCmdUI);
	afx_msg void OnDraw19();
	afx_msg void OnUpdateDraw19(CCmdUI* pCmdUI);
	afx_msg void OnDraw20();
	afx_msg void OnUpdateDraw20(CCmdUI* pCmdUI);
	afx_msg void OnDraw21();
	afx_msg void OnUpdateDraw21(CCmdUI* pCmdUI);
	afx_msg void OnDraw22();
	afx_msg void OnUpdateDraw22(CCmdUI* pCmdUI);
	afx_msg void OnDraw23();
	afx_msg void OnUpdateDraw23(CCmdUI* pCmdUI);
	afx_msg void OnDraw24();
	afx_msg void OnUpdateDraw24(CCmdUI* pCmdUI);
	afx_msg void OnDraw25();
	afx_msg void OnUpdateDraw25(CCmdUI* pCmdUI);
	afx_msg void OnDraw26();
	afx_msg void OnUpdateDraw26(CCmdUI* pCmdUI);
	afx_msg void OnDraw27();
	afx_msg void OnUpdateDraw27(CCmdUI* pCmdUI);
	afx_msg void OnDraw28();
	afx_msg void OnUpdateDraw28(CCmdUI* pCmdUI);
	afx_msg void OnDraw29();
	afx_msg void OnUpdateDraw29(CCmdUI* pCmdUI);
	afx_msg void OnDraw30();
	afx_msg void OnUpdateDraw30(CCmdUI* pCmdUI);
	afx_msg void OnDraw31();
	afx_msg void OnUpdateDraw31(CCmdUI* pCmdUI);
	afx_msg void OnDraw32();
	afx_msg void OnUpdateDraw32(CCmdUI* pCmdUI);
	afx_msg void OnDraw33();
	afx_msg void OnUpdateDraw33(CCmdUI* pCmdUI);
	afx_msg void OnDraw34();
	afx_msg void OnUpdateDraw34(CCmdUI* pCmdUI);
	afx_msg void OnDraw35();
	afx_msg void OnUpdateDraw35(CCmdUI* pCmdUI);
	afx_msg void OnFilter0();
	afx_msg void OnUpdateFilter0(CCmdUI* pCmdUI);
	afx_msg void OnFilter01();
	afx_msg void OnUpdateFilter01(CCmdUI* pCmdUI);
	afx_msg void OnFilter02();
	afx_msg void OnUpdateFilter02(CCmdUI* pCmdUI);
	afx_msg void OnFilter03();
	afx_msg void OnUpdateFilter03(CCmdUI* pCmdUI);
	afx_msg void OnFilter04();
	afx_msg void OnUpdateFilter04(CCmdUI* pCmdUI);
	afx_msg void OnFilter05();
	afx_msg void OnUpdateFilter05(CCmdUI* pCmdUI);
	afx_msg void OnFilter06();
	afx_msg void OnUpdateFilter06(CCmdUI* pCmdUI);
	afx_msg void OnFilter07();
	afx_msg void OnUpdateFilter07(CCmdUI* pCmdUI);
	afx_msg void OnFilter08();
	afx_msg void OnUpdateFilter08(CCmdUI* pCmdUI);
	afx_msg void OnFilter09();
	afx_msg void OnUpdateFilter09(CCmdUI* pCmdUI);
	afx_msg void OnFilter10();
	afx_msg void OnUpdateFilter10(CCmdUI* pCmdUI);
	afx_msg void OnFilter11();
	afx_msg void OnUpdateFilter11(CCmdUI* pCmdUI);
	afx_msg void OnFilter12();
	afx_msg void OnUpdateFilter12(CCmdUI* pCmdUI);
	afx_msg void OnFilter13();
	afx_msg void OnUpdateFilter13(CCmdUI* pCmdUI);
	afx_msg void OnFilter14();
	afx_msg void OnUpdateFilter14(CCmdUI* pCmdUI);
	afx_msg void OnFilter15();
	afx_msg void OnUpdateFilter15(CCmdUI* pCmdUI);
	afx_msg void OnFilter16();
	afx_msg void OnUpdateFilter16(CCmdUI* pCmdUI);
	afx_msg void OnFilter17();
	afx_msg void OnUpdateFilter17(CCmdUI* pCmdUI);
	afx_msg void OnFilter18();
	afx_msg void OnUpdateFilter18(CCmdUI* pCmdUI);
	afx_msg void OnFilter19();
	afx_msg void OnUpdateFilter19(CCmdUI* pCmdUI);
	afx_msg void OnFilter20();
	afx_msg void OnUpdateFilter20(CCmdUI* pCmdUI);
	afx_msg void OnFilter21();
	afx_msg void OnUpdateFilter21(CCmdUI* pCmdUI);
	afx_msg void OnFilter22();
	afx_msg void OnUpdateFilter22(CCmdUI* pCmdUI);
	afx_msg void OnFilter23();
	afx_msg void OnUpdateFilter23(CCmdUI* pCmdUI);
	afx_msg void OnFilter24();
	afx_msg void OnUpdateFilter24(CCmdUI* pCmdUI);
	afx_msg void OnFilter25();
	afx_msg void OnUpdateFilter25(CCmdUI* pCmdUI);
	afx_msg void OnFilter26();
	afx_msg void OnUpdateFilter26(CCmdUI* pCmdUI);
	afx_msg void OnViewZeroinit();
	afx_msg void OnUpdateViewZeroinit(CCmdUI* pCmdUI);
	afx_msg void OnViewOrient();
	afx_msg void OnImageAverage();
	afx_msg void OnUpdateImageAverage(CCmdUI* pCmdUI);
	afx_msg void OnImageBlur();
	afx_msg void OnUpdateImageBlur(CCmdUI* pCmdUI);
	afx_msg void OnImageEdgedetection();
	afx_msg void OnUpdateImageEdgedetection(CCmdUI* pCmdUI);
	afx_msg void OnImageEmboss();
	afx_msg void OnUpdateImageEmboss(CCmdUI* pCmdUI);
	afx_msg void OnImageSharpen();
	afx_msg void OnUpdateImageSharpen(CCmdUI* pCmdUI);
	afx_msg void OnConvolutionDialog();
	afx_msg void OnUpdateConvolutionDialog(CCmdUI* pCmdUI);
	afx_msg void OnConvolutionTracecontour();
	afx_msg void OnUpdateConvolutionTracecontour(CCmdUI* pCmdUI);
	afx_msg void OnFilterConvolutionApply();
	afx_msg void OnFilterConvolutionAuto();
	afx_msg void OnUpdateFilterConvolutionAuto(CCmdUI* pCmdUI);
	afx_msg void OnFilterConvolutionStop();
	afx_msg void OnUpdateFilterConvolutionStop(CCmdUI* pCmdUI);
	afx_msg void OnFilterConvolutionUndo();
	afx_msg void OnConvolveAntialias();
	afx_msg void OnConvolveReduce();
	afx_msg void OnViewReset();
	afx_msg void OnViewDraw();
	afx_msg void OnColorBgr();
	afx_msg void OnUpdateColorBgr(CCmdUI* pCmdUI);
	afx_msg void OnColorBrg();
	afx_msg void OnUpdateColorBrg(CCmdUI* pCmdUI);
	afx_msg void OnColorGbr();
	afx_msg void OnUpdateColorGbr(CCmdUI* pCmdUI);
	afx_msg void OnColorGrb();
	afx_msg void OnUpdateColorGrb(CCmdUI* pCmdUI);
	afx_msg void OnColorRbg();
	afx_msg void OnUpdateColorRbg(CCmdUI* pCmdUI);
	afx_msg void OnColorRgb();
	afx_msg void OnUpdateColorRgb(CCmdUI* pCmdUI);
	afx_msg void OnColorSeparate();
	afx_msg void OnUpdateColorSeparate(CCmdUI* pCmdUI);
	afx_msg void OnOptions1();
	afx_msg void OnUpdateOptions1(CCmdUI* pCmdUI);
	afx_msg void OnOptions2();
	afx_msg void OnUpdateOptions2(CCmdUI* pCmdUI);
	afx_msg void OnOptions3();
	afx_msg void OnUpdateOptions3(CCmdUI* pCmdUI);
	afx_msg void OnOptions4();
	afx_msg void OnUpdateOptions4(CCmdUI* pCmdUI);
	afx_msg void OnOptions5();
	afx_msg void OnUpdateOptions5(CCmdUI* pCmdUI);
	afx_msg void OnOptions6();
	afx_msg void OnUpdateOptions6(CCmdUI* pCmdUI);
	afx_msg void OnOptions7();
	afx_msg void OnUpdateOptions7(CCmdUI* pCmdUI);
	afx_msg void OnOptions8();
	afx_msg void OnUpdateOptions8(CCmdUI* pCmdUI);
	afx_msg void OnOptions9();
	afx_msg void OnUpdateOptions9(CCmdUI* pCmdUI);
	afx_msg void OnOptions10();
	afx_msg void OnUpdateOptions10(CCmdUI* pCmdUI);
	afx_msg void OnFilter28();
	afx_msg void OnUpdateFilter28(CCmdUI* pCmdUI);
	afx_msg void OnDraw36();
	afx_msg void OnUpdateDraw36(CCmdUI* pCmdUI);
	afx_msg void OnDraw37();
	afx_msg void OnUpdateDraw37(CCmdUI* pCmdUI);
	afx_msg void OnDraw38();
	afx_msg void OnUpdateDraw38(CCmdUI* pCmdUI);
	afx_msg void OnDraw39();
	afx_msg void OnUpdateDraw39(CCmdUI* pCmdUI);
	afx_msg void OnDraw40();
	afx_msg void OnUpdateDraw40(CCmdUI* pCmdUI);
	afx_msg void OnDraw41();
	afx_msg void OnUpdateDraw41(CCmdUI* pCmdUI);
	afx_msg void OnDraw42();
	afx_msg void OnUpdateDraw42(CCmdUI* pCmdUI);
	afx_msg void OnDraw43();
	afx_msg void OnUpdateDraw43(CCmdUI* pCmdUI);
	afx_msg void OnDraw44();
	afx_msg void OnUpdateDraw44(CCmdUI* pCmdUI);
	afx_msg void OnDraw45();
	afx_msg void OnUpdateDraw45(CCmdUI* pCmdUI);
	afx_msg void OnDraw46();
	afx_msg void OnUpdateDraw46(CCmdUI* pCmdUI);
	afx_msg void OnDraw47();
	afx_msg void OnUpdateDraw47(CCmdUI* pCmdUI);
	afx_msg void OnDraw48();
	afx_msg void OnUpdateDraw48(CCmdUI* pCmdUI);
	afx_msg void OnDraw49();
	afx_msg void OnUpdateDraw49(CCmdUI* pCmdUI);
	afx_msg void OnDraw50();
	afx_msg void OnUpdateDraw50(CCmdUI* pCmdUI);
	afx_msg void OnDraw51();
	afx_msg void OnUpdateDraw51(CCmdUI* pCmdUI);
	afx_msg void OnFilter29();
	afx_msg void OnUpdateFilter29(CCmdUI* pCmdUI);
	afx_msg void OnFilter30();
	afx_msg void OnUpdateFilter30(CCmdUI* pCmdUI);
	afx_msg void OnFilter31();
	afx_msg void OnUpdateFilter31(CCmdUI* pCmdUI);
	afx_msg void OnFilter32();
	afx_msg void OnUpdateFilter32(CCmdUI* pCmdUI);
	afx_msg void OnFilter33();
	afx_msg void OnUpdateFilter33(CCmdUI* pCmdUI);
	afx_msg void OnFilter27();
	afx_msg void OnUpdateFilter27(CCmdUI* pCmdUI);
	afx_msg void OnFilter34();
	afx_msg void OnUpdateFilter34(CCmdUI* pCmdUI);
	afx_msg void OnFilter35();
	afx_msg void OnUpdateFilter35(CCmdUI* pCmdUI);
	afx_msg void OnFilter36();
	afx_msg void OnUpdateFilter36(CCmdUI* pCmdUI);
	afx_msg void OnFilter37();
	afx_msg void OnUpdateFilter37(CCmdUI* pCmdUI);
	afx_msg void OnFilter38();
	afx_msg void OnUpdateFilter38(CCmdUI* pCmdUI);
	afx_msg void OnDraw52();
	afx_msg void OnUpdateDraw52(CCmdUI* pCmdUI);
	afx_msg void OnDraw53();
	afx_msg void OnUpdateDraw53(CCmdUI* pCmdUI);
	afx_msg void OnDraw54();
	afx_msg void OnUpdateDraw54(CCmdUI* pCmdUI);
	afx_msg void OnDraw55();
	afx_msg void OnUpdateDraw55(CCmdUI* pCmdUI);
	afx_msg void OnDraw56();
	afx_msg void OnUpdateDraw56(CCmdUI* pCmdUI);
	afx_msg void OnDraw57();
	afx_msg void OnUpdateDraw57(CCmdUI* pCmdUI);
	afx_msg void OnDraw58();
	afx_msg void OnUpdateDraw58(CCmdUI* pCmdUI);
	afx_msg void OnDraw59();
	afx_msg void OnUpdateDraw59(CCmdUI* pCmdUI);
	afx_msg void OnDraw60();
	afx_msg void OnUpdateDraw60(CCmdUI* pCmdUI);
	afx_msg void OnColour0();
	afx_msg void OnUpdateColour0(CCmdUI* pCmdUI);
	afx_msg void OnColour01();
	afx_msg void OnUpdateColour01(CCmdUI* pCmdUI);
	afx_msg void OnColour02();
	afx_msg void OnUpdateColour02(CCmdUI* pCmdUI);
	afx_msg void OnColour03();
	afx_msg void OnUpdateColour03(CCmdUI* pCmdUI);
	afx_msg void OnColour04();
	afx_msg void OnUpdateColour04(CCmdUI* pCmdUI);
	afx_msg void OnColour05();
	afx_msg void OnUpdateColour05(CCmdUI* pCmdUI);
	afx_msg void OnColour06();
	afx_msg void OnUpdateColour06(CCmdUI* pCmdUI);
	afx_msg void OnColour07();
	afx_msg void OnUpdateColour07(CCmdUI* pCmdUI);
	afx_msg void OnColour10();
	afx_msg void OnUpdateColour10(CCmdUI* pCmdUI);
	afx_msg void OnColour11();
	afx_msg void OnUpdateColour11(CCmdUI* pCmdUI);
	afx_msg void OnColour12();
	afx_msg void OnUpdateColour12(CCmdUI* pCmdUI);
	afx_msg void OnColour13();
	afx_msg void OnUpdateColour13(CCmdUI* pCmdUI);
	afx_msg void OnColour14();
	afx_msg void OnUpdateColour14(CCmdUI* pCmdUI);
	afx_msg void OnColour15();
	afx_msg void OnUpdateColour15(CCmdUI* pCmdUI);
	afx_msg void OnColour19();
	afx_msg void OnUpdateColour19(CCmdUI* pCmdUI);
	afx_msg void OnColour20();
	afx_msg void OnUpdateColour20(CCmdUI* pCmdUI);
	afx_msg void OnColour21();
	afx_msg void OnUpdateColour21(CCmdUI* pCmdUI);
	afx_msg void OnColour22();
	afx_msg void OnUpdateColour22(CCmdUI* pCmdUI);
	afx_msg void OnColour23();
	afx_msg void OnUpdateColour23(CCmdUI* pCmdUI);
	afx_msg void OnColour24();
	afx_msg void OnUpdateColour24(CCmdUI* pCmdUI);
	afx_msg void OnColour25();
	afx_msg void OnUpdateColour25(CCmdUI* pCmdUI);
	afx_msg void OnColour26();
	afx_msg void OnUpdateColour26(CCmdUI* pCmdUI);
	afx_msg void OnColour27();
	afx_msg void OnUpdateColour27(CCmdUI* pCmdUI);
	afx_msg void OnColour28();
	afx_msg void OnUpdateColour28(CCmdUI* pCmdUI);
	afx_msg void OnColour29();
	afx_msg void OnUpdateColour29(CCmdUI* pCmdUI);
	afx_msg void OnColour30();
	afx_msg void OnUpdateColour30(CCmdUI* pCmdUI);
	afx_msg void OnColour31();
	afx_msg void OnUpdateColour31(CCmdUI* pCmdUI);
	afx_msg void OnColour32();
	afx_msg void OnUpdateColour32(CCmdUI* pCmdUI);
	afx_msg void OnColour33();
	afx_msg void OnUpdateColour33(CCmdUI* pCmdUI);
	afx_msg void OnColour34();
	afx_msg void OnUpdateColour34(CCmdUI* pCmdUI);
	afx_msg void OnColour35();
	afx_msg void OnUpdateColour35(CCmdUI* pCmdUI);
	afx_msg void OnColour36();
	afx_msg void OnUpdateColour36(CCmdUI* pCmdUI);
	afx_msg void OnColour37();
	afx_msg void OnUpdateColour37(CCmdUI* pCmdUI);
	afx_msg void OnColour38();
	afx_msg void OnUpdateColour38(CCmdUI* pCmdUI);
	afx_msg void OnColour39();
	afx_msg void OnUpdateColour39(CCmdUI* pCmdUI);
	afx_msg void OnColour8();
	afx_msg void OnUpdateColour8(CCmdUI* pCmdUI);
	afx_msg void OnColour9();
	afx_msg void OnUpdateColour9(CCmdUI* pCmdUI);
	afx_msg void OnDimensionVariant();
	afx_msg void OnUpdateDimensionVariant(CCmdUI* pCmdUI);
	afx_msg void OnColorGrayscale();
	afx_msg void OnUpdateColorGrayscale(CCmdUI* pCmdUI);
	afx_msg void OnColorInvert();
	afx_msg void OnUpdateColorInvert(CCmdUI* pCmdUI);
	afx_msg void OnDraw61();
	afx_msg void OnUpdateDraw61(CCmdUI* pCmdUI);
	afx_msg void OnDraw62();
	afx_msg void OnUpdateDraw62(CCmdUI* pCmdUI);
	afx_msg void OnDraw63();
	afx_msg void OnUpdateDraw63(CCmdUI* pCmdUI);
	afx_msg void OnDraw64();
	afx_msg void OnUpdateDraw64(CCmdUI* pCmdUI);
	afx_msg void OnDraw65();
	afx_msg void OnUpdateDraw65(CCmdUI* pCmdUI);
	afx_msg void OnDraw66();
	afx_msg void OnUpdateDraw66(CCmdUI* pCmdUI);
	afx_msg void OnDraw67();
	afx_msg void OnUpdateDraw67(CCmdUI* pCmdUI);
	afx_msg void OnDraw68();
	afx_msg void OnUpdateDraw68(CCmdUI* pCmdUI);
	afx_msg void OnDraw69();
	afx_msg void OnUpdateDraw69(CCmdUI* pCmdUI);
	afx_msg void OnDraw70();
	afx_msg void OnUpdateDraw70(CCmdUI* pCmdUI);
	afx_msg void OnDraw71();
	afx_msg void OnUpdateDraw71(CCmdUI* pCmdUI);
	afx_msg void OnDraw72();
	afx_msg void OnUpdateDraw72(CCmdUI* pCmdUI);
	afx_msg void OnDraw73();
	afx_msg void OnUpdateDraw73(CCmdUI* pCmdUI);
	afx_msg void OnDraw74();
	afx_msg void OnUpdateDraw74(CCmdUI* pCmdUI);
	afx_msg void OnDraw75();
	afx_msg void OnUpdateDraw75(CCmdUI* pCmdUI);
	afx_msg void OnDraw76();
	afx_msg void OnUpdateDraw76(CCmdUI* pCmdUI);
	afx_msg void OnDraw77();
	afx_msg void OnUpdateDraw77(CCmdUI* pCmdUI);
	afx_msg void OnDraw78();
	afx_msg void OnUpdateDraw78(CCmdUI* pCmdUI);
	afx_msg void OnDraw79();
	afx_msg void OnUpdateDraw79(CCmdUI* pCmdUI);
	afx_msg void OnDraw80();
	afx_msg void OnUpdateDraw80(CCmdUI* pCmdUI);
	afx_msg void OnDraw81();
	afx_msg void OnUpdateDraw81(CCmdUI* pCmdUI);
	afx_msg void OnDraw82();
	afx_msg void OnUpdateDraw82(CCmdUI* pCmdUI);
	afx_msg void OnDraw83();
	afx_msg void OnUpdateDraw83(CCmdUI* pCmdUI);
	afx_msg void OnDraw84();
	afx_msg void OnUpdateDraw84(CCmdUI* pCmdUI);
	afx_msg void OnDraw85();
	afx_msg void OnUpdateDraw85(CCmdUI* pCmdUI);
	afx_msg void OnDraw86();
	afx_msg void OnUpdateDraw86(CCmdUI* pCmdUI);
	afx_msg void OnDraw87();
	afx_msg void OnUpdateDraw87(CCmdUI* pCmdUI);
	afx_msg void OnDraw88();
	afx_msg void OnUpdateDraw88(CCmdUI* pCmdUI);
	afx_msg void OnDraw89();
	afx_msg void OnUpdateDraw89(CCmdUI* pCmdUI);
	afx_msg void OnDraw90();
	afx_msg void OnUpdateDraw90(CCmdUI* pCmdUI);
	afx_msg void OnDraw91();
	afx_msg void OnUpdateDraw91(CCmdUI* pCmdUI);
	afx_msg void OnDraw92();
	afx_msg void OnUpdateDraw92(CCmdUI* pCmdUI);
	afx_msg void OnDraw93();
	afx_msg void OnUpdateDraw93(CCmdUI* pCmdUI);
	afx_msg void OnDraw94();
	afx_msg void OnUpdateDraw94(CCmdUI* pCmdUI);
	afx_msg void OnDraw95();
	afx_msg void OnUpdateDraw95(CCmdUI* pCmdUI);
	afx_msg void OnDraw96();
	afx_msg void OnUpdateDraw96(CCmdUI* pCmdUI);
	afx_msg void OnDraw97();
	afx_msg void OnUpdateDraw97(CCmdUI* pCmdUI);
	afx_msg void OnDraw98();
	afx_msg void OnUpdateDraw98(CCmdUI* pCmdUI);
	afx_msg void OnDraw99();
	afx_msg void OnUpdateDraw99(CCmdUI* pCmdUI);
	afx_msg void OnDraw100();
	afx_msg void OnUpdateDraw100(CCmdUI* pCmdUI);
	afx_msg void OnDraw101();
	afx_msg void OnUpdateDraw101(CCmdUI* pCmdUI);
	afx_msg void OnDrawUnique();
	afx_msg void OnFilter39();
	afx_msg void OnUpdateFilter39(CCmdUI* pCmdUI);
	afx_msg void OnFilter40();
	afx_msg void OnUpdateFilter40(CCmdUI* pCmdUI);
	afx_msg void OnFilter41();
	afx_msg void OnUpdateFilter41(CCmdUI* pCmdUI);
	afx_msg void OnFilter42();
	afx_msg void OnUpdateFilter42(CCmdUI* pCmdUI);
	afx_msg void OnFilter43();
	afx_msg void OnUpdateFilter43(CCmdUI* pCmdUI);
	afx_msg void OnFractalsMovie();
	afx_msg void OnFractalStartgeneratingamovie();
	afx_msg void OnUpdateFractalStartgeneratingamovie(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFractalsMovie(CCmdUI* pCmdUI);
	afx_msg void OnFractalVideoplayer();
	afx_msg void OnConvolveAutoAntialias();
	afx_msg void OnUpdateConvolveAutoAntialias(CCmdUI* pCmdUI);
	afx_msg void OnViewJuliavideo();
	afx_msg void OnUpdateViewJuliavideo(CCmdUI* pCmdUI);
	afx_msg void OnViewOrientationvideo();
	afx_msg void OnUpdateViewOrientationvideo(CCmdUI* pCmdUI);
	afx_msg void OnDraw102();
	afx_msg void OnUpdateDraw102(CCmdUI* pCmdUI);
	afx_msg void OnDraw103();
	afx_msg void OnUpdateDraw103(CCmdUI* pCmdUI);
	afx_msg void OnDraw104();
	afx_msg void OnUpdateDraw104(CCmdUI* pCmdUI);
	afx_msg void OnFilter44();
	afx_msg void OnUpdateFilter44(CCmdUI* pCmdUI);
	afx_msg void OnFilter45();
	afx_msg void OnUpdateFilter45(CCmdUI* pCmdUI);
	afx_msg void OnFilter46();
	afx_msg void OnUpdateFilter46(CCmdUI* pCmdUI);
	afx_msg void OnFilter47();
	afx_msg void OnUpdateFilter47(CCmdUI* pCmdUI);
	afx_msg void OnDraw105();
	afx_msg void OnUpdateDraw105(CCmdUI* pCmdUI);
	afx_msg void OnDraw106();
	afx_msg void OnUpdateDraw106(CCmdUI* pCmdUI);
	afx_msg void OnDraw107();
	afx_msg void OnUpdateDraw107(CCmdUI* pCmdUI);
	afx_msg void OnDraw108();
	afx_msg void OnUpdateDraw108(CCmdUI* pCmdUI);
	afx_msg void OnDraw109();
	afx_msg void OnUpdateDraw109(CCmdUI* pCmdUI);
	afx_msg void OnDraw110();
	afx_msg void OnUpdateDraw110(CCmdUI* pCmdUI);
	afx_msg void OnDraw111();
	afx_msg void OnUpdateDraw111(CCmdUI* pCmdUI);
	afx_msg void OnDraw112();
	afx_msg void OnUpdateDraw112(CCmdUI* pCmdUI);
	afx_msg void OnDraw113();
	afx_msg void OnUpdateDraw113(CCmdUI* pCmdUI);
	afx_msg void OnDraw114();
	afx_msg void OnUpdateDraw114(CCmdUI* pCmdUI);
	afx_msg void OnDraw115();
	afx_msg void OnUpdateDraw115(CCmdUI* pCmdUI);
	afx_msg void OnDraw116();
	afx_msg void OnUpdateDraw116(CCmdUI* pCmdUI);
	afx_msg void OnDraw117();
	afx_msg void OnUpdateDraw117(CCmdUI* pCmdUI);
	afx_msg void OnFilter48();
	afx_msg void OnUpdateFilter48(CCmdUI* pCmdUI);
	afx_msg void OnFilter49();
	afx_msg void OnUpdateFilter49(CCmdUI* pCmdUI);
	afx_msg void OnOptions11();
	afx_msg void OnUpdateOptions11(CCmdUI* pCmdUI);
	afx_msg void OnOptions12();
	afx_msg void OnUpdateOptions12(CCmdUI* pCmdUI);
	afx_msg void OnOptions13();
	afx_msg void OnUpdateOptions13(CCmdUI* pCmdUI);
	afx_msg void OnOptions14();
	afx_msg void OnUpdateOptions14(CCmdUI* pCmdUI);
	afx_msg void OnOptions15();
	afx_msg void OnUpdateOptions15(CCmdUI* pCmdUI);
	afx_msg void OnOptions16();
	afx_msg void OnUpdateOptions16(CCmdUI* pCmdUI);
	afx_msg void OnOptions17();
	afx_msg void OnUpdateOptions17(CCmdUI* pCmdUI);
	afx_msg void OnOptions18();
	afx_msg void OnUpdateOptions18(CCmdUI* pCmdUI);
	afx_msg void OnOptions19();
	afx_msg void OnUpdateOptions19(CCmdUI* pCmdUI);
	afx_msg void OnOptions20();
	afx_msg void OnUpdateOptions20(CCmdUI* pCmdUI);
	afx_msg void OnDrawUndo();
	afx_msg void OnUpdateDrawUndo(CCmdUI* pCmdUI);
	afx_msg void OnFilter50();
	afx_msg void OnUpdateFilter50(CCmdUI* pCmdUI);
	afx_msg void OnLoadDll();
	afx_msg void OnFilter51();
	afx_msg void OnUpdateFilter51(CCmdUI* pCmdUI);
	afx_msg void OnFilter52();
	afx_msg void OnUpdateFilter52(CCmdUI* pCmdUI);
	afx_msg void OnColorRegular();
	afx_msg void OnUpdateColorRegular(CCmdUI* pCmdUI);
	afx_msg void OnColorLight();
	afx_msg void OnUpdateColorLight(CCmdUI* pCmdUI);
	afx_msg void OnDraw118();
	afx_msg void OnUpdateDraw118(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TierazonView.cpp
inline CTierazonDoc* CTierazonView::GetDocument()
   { return (CTierazonDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIERAZONVIEW_H__09FDBB2F_6F08_11D1_9E84_444553540000__INCLUDED_)
