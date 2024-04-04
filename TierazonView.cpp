// TierazonView.cpp : implementation of the CTierazonView class
//

#include "stdafx.h"
#include "Tierazon.h"

#include "TierazonDoc.h"
#include "TierazonView.h"
#include "gradient.h"
#include "fparams.h"
#include <math.h>
#include "external.h"
#include "xysize.h"
#include "resource.h"
#include "orient.h"
#include "convolut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTierazonView

IMPLEMENT_DYNCREATE(CTierazonView, CScrollView)

BEGIN_MESSAGE_MAP(CTierazonView, CScrollView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CTierazonView)
	ON_COMMAND(ID_SAVE_DIB, OnSaveDib)
	ON_COMMAND(ID_WINDOW_SIZEDESKTOP, OnWindowSizedesktop)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_IMAGE_SIZE, OnImageSize)
	ON_COMMAND(ID_VIEW_ZOOM, OnViewZoom)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM, OnUpdateViewZoom)
	ON_COMMAND(ID_VIEW_NEW, OnViewNew)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NEW, OnUpdateViewNew)
	ON_COMMAND(ID_FILE_SAVECOLORS, OnFileSavecolors)
	ON_COMMAND(ID_FILE_SAVEPARAMETERS, OnFileSaveparameters)
	ON_COMMAND(ID_FILE_LOADCOLORS, OnFileLoadcolors)
	ON_COMMAND(ID_FILE_LOADPARAMETERS, OnFileLoadparameters)
	ON_COMMAND(ID_VIEW_JULIA, OnViewJulia)
	ON_UPDATE_COMMAND_UI(ID_VIEW_JULIA, OnUpdateViewJulia)
	ON_COMMAND(ID_IMAGE_PARAMS, OnImageParams)
	ON_COMMAND(ID_DRAW_ABORT, OnDrawAbort)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ABORT, OnUpdateDrawAbort)
	ON_COMMAND(ID_SHIFT_START, OnShiftStart)
	ON_UPDATE_COMMAND_UI(ID_SHIFT_START, OnUpdateShiftStart)
	ON_COMMAND(ID_IMAGE_COLORPARAMETERS, OnImageColorparameters)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_COLORPARAMETERS, OnUpdateImageColorparameters)
	ON_COMMAND(ID_IMAGE_ASPECTRATIO, OnImageAspectratio)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_ASPECTRATIO, OnUpdateImageAspectratio)
	ON_COMMAND(ID_IMAGE_CLEAR, OnImageClear)
	ON_COMMAND(ID_VIEW_MANDEL, OnViewMandel)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MANDEL, OnUpdateViewMandel)
	ON_COMMAND(ID_DRAW_1, OnDraw1)
	ON_UPDATE_COMMAND_UI(ID_DRAW_1, OnUpdateDraw1)
	ON_COMMAND(ID_DRAW_INSIDEOUT, OnDrawInsideout)
	ON_UPDATE_COMMAND_UI(ID_DRAW_INSIDEOUT, OnUpdateDrawInsideout)
	ON_COMMAND(ID_DRAW_2, OnDraw2)
	ON_UPDATE_COMMAND_UI(ID_DRAW_2, OnUpdateDraw2)
	ON_COMMAND(ID_DRAW_3, OnDraw3)
	ON_UPDATE_COMMAND_UI(ID_DRAW_3, OnUpdateDraw3)
	ON_COMMAND(ID_DRAW_4, OnDraw4)
	ON_UPDATE_COMMAND_UI(ID_DRAW_4, OnUpdateDraw4)
	ON_COMMAND(ID_DRAW_5, OnDraw5)
	ON_UPDATE_COMMAND_UI(ID_DRAW_5, OnUpdateDraw5)
	ON_COMMAND(ID_DRAW_6, OnDraw6)
	ON_UPDATE_COMMAND_UI(ID_DRAW_6, OnUpdateDraw6)
	ON_COMMAND(ID_DRAW_7, OnDraw7)
	ON_UPDATE_COMMAND_UI(ID_DRAW_7, OnUpdateDraw7)
	ON_COMMAND(ID_DRAW_8, OnDraw8)
	ON_UPDATE_COMMAND_UI(ID_DRAW_8, OnUpdateDraw8)
	ON_COMMAND(ID_DRAW_9, OnDraw9)
	ON_UPDATE_COMMAND_UI(ID_DRAW_9, OnUpdateDraw9)
	ON_COMMAND(ID_DRAW_10, OnDraw10)
	ON_UPDATE_COMMAND_UI(ID_DRAW_10, OnUpdateDraw10)
	ON_COMMAND(ID_DRAW_11, OnDraw11)
	ON_UPDATE_COMMAND_UI(ID_DRAW_11, OnUpdateDraw11)
	ON_COMMAND(ID_DRAW_12, OnDraw12)
	ON_UPDATE_COMMAND_UI(ID_DRAW_12, OnUpdateDraw12)
	ON_COMMAND(ID_DRAW_13, OnDraw13)
	ON_UPDATE_COMMAND_UI(ID_DRAW_13, OnUpdateDraw13)
	ON_COMMAND(ID_DRAW_14, OnDraw14)
	ON_UPDATE_COMMAND_UI(ID_DRAW_14, OnUpdateDraw14)
	ON_COMMAND(ID_DRAW_15, OnDraw15)
	ON_UPDATE_COMMAND_UI(ID_DRAW_15, OnUpdateDraw15)
	ON_COMMAND(ID_DRAW_16, OnDraw16)
	ON_UPDATE_COMMAND_UI(ID_DRAW_16, OnUpdateDraw16)
	ON_COMMAND(ID_DRAW_17, OnDraw17)
	ON_UPDATE_COMMAND_UI(ID_DRAW_17, OnUpdateDraw17)
	ON_COMMAND(ID_DRAW_18, OnDraw18)
	ON_UPDATE_COMMAND_UI(ID_DRAW_18, OnUpdateDraw18)
	ON_COMMAND(ID_DRAW_19, OnDraw19)
	ON_UPDATE_COMMAND_UI(ID_DRAW_19, OnUpdateDraw19)
	ON_COMMAND(ID_DRAW_20, OnDraw20)
	ON_UPDATE_COMMAND_UI(ID_DRAW_20, OnUpdateDraw20)
	ON_COMMAND(ID_DRAW_21, OnDraw21)
	ON_UPDATE_COMMAND_UI(ID_DRAW_21, OnUpdateDraw21)
	ON_COMMAND(ID_DRAW_22, OnDraw22)
	ON_UPDATE_COMMAND_UI(ID_DRAW_22, OnUpdateDraw22)
	ON_COMMAND(ID_DRAW_23, OnDraw23)
	ON_UPDATE_COMMAND_UI(ID_DRAW_23, OnUpdateDraw23)
	ON_COMMAND(ID_DRAW_24, OnDraw24)
	ON_UPDATE_COMMAND_UI(ID_DRAW_24, OnUpdateDraw24)
	ON_COMMAND(ID_DRAW_25, OnDraw25)
	ON_UPDATE_COMMAND_UI(ID_DRAW_25, OnUpdateDraw25)
	ON_COMMAND(ID_DRAW_26, OnDraw26)
	ON_UPDATE_COMMAND_UI(ID_DRAW_26, OnUpdateDraw26)
	ON_COMMAND(ID_DRAW_27, OnDraw27)
	ON_UPDATE_COMMAND_UI(ID_DRAW_27, OnUpdateDraw27)
	ON_COMMAND(ID_DRAW_28, OnDraw28)
	ON_UPDATE_COMMAND_UI(ID_DRAW_28, OnUpdateDraw28)
	ON_COMMAND(ID_DRAW_29, OnDraw29)
	ON_UPDATE_COMMAND_UI(ID_DRAW_29, OnUpdateDraw29)
	ON_COMMAND(ID_DRAW_30, OnDraw30)
	ON_UPDATE_COMMAND_UI(ID_DRAW_30, OnUpdateDraw30)
	ON_COMMAND(ID_DRAW_31, OnDraw31)
	ON_UPDATE_COMMAND_UI(ID_DRAW_31, OnUpdateDraw31)
	ON_COMMAND(ID_DRAW_32, OnDraw32)
	ON_UPDATE_COMMAND_UI(ID_DRAW_32, OnUpdateDraw32)
	ON_COMMAND(ID_DRAW_33, OnDraw33)
	ON_UPDATE_COMMAND_UI(ID_DRAW_33, OnUpdateDraw33)
	ON_COMMAND(ID_DRAW_34, OnDraw34)
	ON_UPDATE_COMMAND_UI(ID_DRAW_34, OnUpdateDraw34)
	ON_COMMAND(ID_DRAW_35, OnDraw35)
	ON_UPDATE_COMMAND_UI(ID_DRAW_35, OnUpdateDraw35)
	ON_COMMAND(ID_FILTER_0, OnFilter0)
	ON_UPDATE_COMMAND_UI(ID_FILTER_0, OnUpdateFilter0)
	ON_COMMAND(ID_FILTER_01, OnFilter01)
	ON_UPDATE_COMMAND_UI(ID_FILTER_01, OnUpdateFilter01)
	ON_COMMAND(ID_FILTER_02, OnFilter02)
	ON_UPDATE_COMMAND_UI(ID_FILTER_02, OnUpdateFilter02)
	ON_COMMAND(ID_FILTER_03, OnFilter03)
	ON_UPDATE_COMMAND_UI(ID_FILTER_03, OnUpdateFilter03)
	ON_COMMAND(ID_FILTER_04, OnFilter04)
	ON_UPDATE_COMMAND_UI(ID_FILTER_04, OnUpdateFilter04)
	ON_COMMAND(ID_FILTER_05, OnFilter05)
	ON_UPDATE_COMMAND_UI(ID_FILTER_05, OnUpdateFilter05)
	ON_COMMAND(ID_FILTER_06, OnFilter06)
	ON_UPDATE_COMMAND_UI(ID_FILTER_06, OnUpdateFilter06)
	ON_COMMAND(ID_FILTER_07, OnFilter07)
	ON_UPDATE_COMMAND_UI(ID_FILTER_07, OnUpdateFilter07)
	ON_COMMAND(ID_FILTER_08, OnFilter08)
	ON_UPDATE_COMMAND_UI(ID_FILTER_08, OnUpdateFilter08)
	ON_COMMAND(ID_FILTER_09, OnFilter09)
	ON_UPDATE_COMMAND_UI(ID_FILTER_09, OnUpdateFilter09)
	ON_COMMAND(ID_FILTER_10, OnFilter10)
	ON_UPDATE_COMMAND_UI(ID_FILTER_10, OnUpdateFilter10)
	ON_COMMAND(ID_FILTER_11, OnFilter11)
	ON_UPDATE_COMMAND_UI(ID_FILTER_11, OnUpdateFilter11)
	ON_COMMAND(ID_FILTER_12, OnFilter12)
	ON_UPDATE_COMMAND_UI(ID_FILTER_12, OnUpdateFilter12)
	ON_COMMAND(ID_FILTER_13, OnFilter13)
	ON_UPDATE_COMMAND_UI(ID_FILTER_13, OnUpdateFilter13)
	ON_COMMAND(ID_FILTER_14, OnFilter14)
	ON_UPDATE_COMMAND_UI(ID_FILTER_14, OnUpdateFilter14)
	ON_COMMAND(ID_FILTER_15, OnFilter15)
	ON_UPDATE_COMMAND_UI(ID_FILTER_15, OnUpdateFilter15)
	ON_COMMAND(ID_FILTER_16, OnFilter16)
	ON_UPDATE_COMMAND_UI(ID_FILTER_16, OnUpdateFilter16)
	ON_COMMAND(ID_FILTER_17, OnFilter17)
	ON_UPDATE_COMMAND_UI(ID_FILTER_17, OnUpdateFilter17)
	ON_COMMAND(ID_FILTER_18, OnFilter18)
	ON_UPDATE_COMMAND_UI(ID_FILTER_18, OnUpdateFilter18)
	ON_COMMAND(ID_FILTER_19, OnFilter19)
	ON_UPDATE_COMMAND_UI(ID_FILTER_19, OnUpdateFilter19)
	ON_COMMAND(ID_FILTER_20, OnFilter20)
	ON_UPDATE_COMMAND_UI(ID_FILTER_20, OnUpdateFilter20)
	ON_COMMAND(ID_FILTER_21, OnFilter21)
	ON_UPDATE_COMMAND_UI(ID_FILTER_21, OnUpdateFilter21)
	ON_COMMAND(ID_FILTER_22, OnFilter22)
	ON_UPDATE_COMMAND_UI(ID_FILTER_22, OnUpdateFilter22)
	ON_COMMAND(ID_FILTER_23, OnFilter23)
	ON_UPDATE_COMMAND_UI(ID_FILTER_23, OnUpdateFilter23)
	ON_COMMAND(ID_FILTER_24, OnFilter24)
	ON_UPDATE_COMMAND_UI(ID_FILTER_24, OnUpdateFilter24)
	ON_COMMAND(ID_FILTER_25, OnFilter25)
	ON_UPDATE_COMMAND_UI(ID_FILTER_25, OnUpdateFilter25)
	ON_COMMAND(ID_FILTER_26, OnFilter26)
	ON_UPDATE_COMMAND_UI(ID_FILTER_26, OnUpdateFilter26)
	ON_COMMAND(ID_VIEW_ZEROINIT, OnViewZeroinit)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZEROINIT, OnUpdateViewZeroinit)
	ON_COMMAND(ID_VIEW_ORIENT, OnViewOrient)
	ON_COMMAND(ID_IMAGE_AVERAGE, OnImageAverage)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_AVERAGE, OnUpdateImageAverage)
	ON_COMMAND(ID_IMAGE_BLUR, OnImageBlur)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_BLUR, OnUpdateImageBlur)
	ON_COMMAND(ID_IMAGE_EDGEDETECTION, OnImageEdgedetection)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_EDGEDETECTION, OnUpdateImageEdgedetection)
	ON_COMMAND(ID_IMAGE_EMBOSS, OnImageEmboss)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_EMBOSS, OnUpdateImageEmboss)
	ON_COMMAND(ID_IMAGE_SHARPEN, OnImageSharpen)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_SHARPEN, OnUpdateImageSharpen)
	ON_COMMAND(ID_CONVOLUTION_DIALOG, OnConvolutionDialog)
	ON_UPDATE_COMMAND_UI(ID_CONVOLUTION_DIALOG, OnUpdateConvolutionDialog)
	ON_COMMAND(ID_CONVOLUTION_TRACECONTOUR, OnConvolutionTracecontour)
	ON_UPDATE_COMMAND_UI(ID_CONVOLUTION_TRACECONTOUR, OnUpdateConvolutionTracecontour)
	ON_COMMAND(ID_FILTER_CONVOLUTION_APPLY, OnFilterConvolutionApply)
	ON_COMMAND(ID_FILTER_CONVOLUTION_AUTO, OnFilterConvolutionAuto)
	ON_UPDATE_COMMAND_UI(ID_FILTER_CONVOLUTION_AUTO, OnUpdateFilterConvolutionAuto)
	ON_COMMAND(ID_FILTER_CONVOLUTION_STOP, OnFilterConvolutionStop)
	ON_UPDATE_COMMAND_UI(ID_FILTER_CONVOLUTION_STOP, OnUpdateFilterConvolutionStop)
	ON_COMMAND(ID_FILTER_CONVOLUTION_UNDO, OnFilterConvolutionUndo)
	ON_COMMAND(ID_CONVOLVE_ANTIALIAS, OnConvolveAntialias)
	ON_COMMAND(ID_CONVOLVE_REDUCE, OnConvolveReduce)
	ON_COMMAND(ID_VIEW_RESET, OnViewReset)
	ON_COMMAND(ID_VIEW_DRAW, OnViewDraw)
	ON_COMMAND(ID_COLOR_BGR, OnColorBgr)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BGR, OnUpdateColorBgr)
	ON_COMMAND(ID_COLOR_BRG, OnColorBrg)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BRG, OnUpdateColorBrg)
	ON_COMMAND(ID_COLOR_GBR, OnColorGbr)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GBR, OnUpdateColorGbr)
	ON_COMMAND(ID_COLOR_GRB, OnColorGrb)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GRB, OnUpdateColorGrb)
	ON_COMMAND(ID_COLOR_RBG, OnColorRbg)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RBG, OnUpdateColorRbg)
	ON_COMMAND(ID_COLOR_RGB, OnColorRgb)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RGB, OnUpdateColorRgb)
	ON_COMMAND(ID_COLOR_SEPARATE, OnColorSeparate)
	ON_UPDATE_COMMAND_UI(ID_COLOR_SEPARATE, OnUpdateColorSeparate)
	ON_COMMAND(ID_OPTIONS_1, OnOptions1)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_1, OnUpdateOptions1)
	ON_COMMAND(ID_OPTIONS_2, OnOptions2)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_2, OnUpdateOptions2)
	ON_COMMAND(ID_OPTIONS_3, OnOptions3)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_3, OnUpdateOptions3)
	ON_COMMAND(ID_OPTIONS_4, OnOptions4)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_4, OnUpdateOptions4)
	ON_COMMAND(ID_OPTIONS_5, OnOptions5)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_5, OnUpdateOptions5)
	ON_COMMAND(ID_OPTIONS_6, OnOptions6)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_6, OnUpdateOptions6)
	ON_COMMAND(ID_OPTIONS_7, OnOptions7)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_7, OnUpdateOptions7)
	ON_COMMAND(ID_OPTIONS_8, OnOptions8)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_8, OnUpdateOptions8)
	ON_COMMAND(ID_OPTIONS_9, OnOptions9)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_9, OnUpdateOptions9)
	ON_COMMAND(ID_OPTIONS_10, OnOptions10)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_10, OnUpdateOptions10)
	ON_COMMAND(ID_FILTER_28, OnFilter28)
	ON_UPDATE_COMMAND_UI(ID_FILTER_28, OnUpdateFilter28)
	ON_COMMAND(ID_DRAW_36, OnDraw36)
	ON_UPDATE_COMMAND_UI(ID_DRAW_36, OnUpdateDraw36)
	ON_COMMAND(ID_DRAW_37, OnDraw37)
	ON_UPDATE_COMMAND_UI(ID_DRAW_37, OnUpdateDraw37)
	ON_COMMAND(ID_DRAW_38, OnDraw38)
	ON_UPDATE_COMMAND_UI(ID_DRAW_38, OnUpdateDraw38)
	ON_COMMAND(ID_DRAW_39, OnDraw39)
	ON_UPDATE_COMMAND_UI(ID_DRAW_39, OnUpdateDraw39)
	ON_COMMAND(ID_DRAW_40, OnDraw40)
	ON_UPDATE_COMMAND_UI(ID_DRAW_40, OnUpdateDraw40)
	ON_COMMAND(ID_DRAW_41, OnDraw41)
	ON_UPDATE_COMMAND_UI(ID_DRAW_41, OnUpdateDraw41)
	ON_COMMAND(ID_DRAW_42, OnDraw42)
	ON_UPDATE_COMMAND_UI(ID_DRAW_42, OnUpdateDraw42)
	ON_COMMAND(ID_DRAW_43, OnDraw43)
	ON_UPDATE_COMMAND_UI(ID_DRAW_43, OnUpdateDraw43)
	ON_COMMAND(ID_DRAW_44, OnDraw44)
	ON_UPDATE_COMMAND_UI(ID_DRAW_44, OnUpdateDraw44)
	ON_COMMAND(ID_DRAW_45, OnDraw45)
	ON_UPDATE_COMMAND_UI(ID_DRAW_45, OnUpdateDraw45)
	ON_COMMAND(ID_DRAW_46, OnDraw46)
	ON_UPDATE_COMMAND_UI(ID_DRAW_46, OnUpdateDraw46)
	ON_COMMAND(ID_DRAW_47, OnDraw47)
	ON_UPDATE_COMMAND_UI(ID_DRAW_47, OnUpdateDraw47)
	ON_COMMAND(ID_DRAW_48, OnDraw48)
	ON_UPDATE_COMMAND_UI(ID_DRAW_48, OnUpdateDraw48)
	ON_COMMAND(ID_DRAW_49, OnDraw49)
	ON_UPDATE_COMMAND_UI(ID_DRAW_49, OnUpdateDraw49)
	ON_COMMAND(ID_DRAW_50, OnDraw50)
	ON_UPDATE_COMMAND_UI(ID_DRAW_50, OnUpdateDraw50)
	ON_COMMAND(ID_DRAW_51, OnDraw51)
	ON_UPDATE_COMMAND_UI(ID_DRAW_51, OnUpdateDraw51)
	ON_COMMAND(ID_FILTER_29, OnFilter29)
	ON_UPDATE_COMMAND_UI(ID_FILTER_29, OnUpdateFilter29)
	ON_COMMAND(ID_FILTER_30, OnFilter30)
	ON_UPDATE_COMMAND_UI(ID_FILTER_30, OnUpdateFilter30)
	ON_COMMAND(ID_FILTER_31, OnFilter31)
	ON_UPDATE_COMMAND_UI(ID_FILTER_31, OnUpdateFilter31)
	ON_COMMAND(ID_FILTER_32, OnFilter32)
	ON_UPDATE_COMMAND_UI(ID_FILTER_32, OnUpdateFilter32)
	ON_COMMAND(ID_FILTER_33, OnFilter33)
	ON_UPDATE_COMMAND_UI(ID_FILTER_33, OnUpdateFilter33)
	ON_COMMAND(ID_FILTER_27, OnFilter27)
	ON_UPDATE_COMMAND_UI(ID_FILTER_27, OnUpdateFilter27)
	ON_COMMAND(ID_FILTER_34, OnFilter34)
	ON_UPDATE_COMMAND_UI(ID_FILTER_34, OnUpdateFilter34)
	ON_COMMAND(ID_FILTER_35, OnFilter35)
	ON_UPDATE_COMMAND_UI(ID_FILTER_35, OnUpdateFilter35)
	ON_COMMAND(ID_FILTER_36, OnFilter36)
	ON_UPDATE_COMMAND_UI(ID_FILTER_36, OnUpdateFilter36)
	ON_COMMAND(ID_FILTER_37, OnFilter37)
	ON_UPDATE_COMMAND_UI(ID_FILTER_37, OnUpdateFilter37)
	ON_COMMAND(ID_FILTER_38, OnFilter38)
	ON_UPDATE_COMMAND_UI(ID_FILTER_38, OnUpdateFilter38)
	ON_COMMAND(ID_DRAW_52, OnDraw52)
	ON_UPDATE_COMMAND_UI(ID_DRAW_52, OnUpdateDraw52)
	ON_COMMAND(ID_DRAW_53, OnDraw53)
	ON_UPDATE_COMMAND_UI(ID_DRAW_53, OnUpdateDraw53)
	ON_COMMAND(ID_DRAW_54, OnDraw54)
	ON_UPDATE_COMMAND_UI(ID_DRAW_54, OnUpdateDraw54)
	ON_COMMAND(ID_DRAW_55, OnDraw55)
	ON_UPDATE_COMMAND_UI(ID_DRAW_55, OnUpdateDraw55)
	ON_COMMAND(ID_DRAW_56, OnDraw56)
	ON_UPDATE_COMMAND_UI(ID_DRAW_56, OnUpdateDraw56)
	ON_COMMAND(ID_DRAW_57, OnDraw57)
	ON_UPDATE_COMMAND_UI(ID_DRAW_57, OnUpdateDraw57)
	ON_COMMAND(ID_DRAW_58, OnDraw58)
	ON_UPDATE_COMMAND_UI(ID_DRAW_58, OnUpdateDraw58)
	ON_COMMAND(ID_DRAW_59, OnDraw59)
	ON_UPDATE_COMMAND_UI(ID_DRAW_59, OnUpdateDraw59)
	ON_COMMAND(ID_DRAW_60, OnDraw60)
	ON_UPDATE_COMMAND_UI(ID_DRAW_60, OnUpdateDraw60)
	ON_COMMAND(ID_COLOUR_0, OnColour0)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_0, OnUpdateColour0)
	ON_COMMAND(ID_COLOUR_01, OnColour01)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_01, OnUpdateColour01)
	ON_COMMAND(ID_COLOUR_02, OnColour02)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_02, OnUpdateColour02)
	ON_COMMAND(ID_COLOUR_03, OnColour03)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_03, OnUpdateColour03)
	ON_COMMAND(ID_COLOUR_04, OnColour04)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_04, OnUpdateColour04)
	ON_COMMAND(ID_COLOUR_05, OnColour05)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_05, OnUpdateColour05)
	ON_COMMAND(ID_COLOUR_06, OnColour06)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_06, OnUpdateColour06)
	ON_COMMAND(ID_COLOUR_07, OnColour07)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_07, OnUpdateColour07)
	ON_COMMAND(ID_COLOUR_10, OnColour10)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_10, OnUpdateColour10)
	ON_COMMAND(ID_COLOUR_11, OnColour11)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_11, OnUpdateColour11)
	ON_COMMAND(ID_COLOUR_12, OnColour12)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_12, OnUpdateColour12)
	ON_COMMAND(ID_COLOUR_13, OnColour13)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_13, OnUpdateColour13)
	ON_COMMAND(ID_COLOUR_14, OnColour14)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_14, OnUpdateColour14)
	ON_COMMAND(ID_COLOUR_15, OnColour15)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_15, OnUpdateColour15)
	ON_COMMAND(ID_COLOUR_19, OnColour19)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_19, OnUpdateColour19)
	ON_COMMAND(ID_COLOUR_20, OnColour20)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_20, OnUpdateColour20)
	ON_COMMAND(ID_COLOUR_21, OnColour21)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_21, OnUpdateColour21)
	ON_COMMAND(ID_COLOUR_22, OnColour22)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_22, OnUpdateColour22)
	ON_COMMAND(ID_COLOUR_23, OnColour23)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_23, OnUpdateColour23)
	ON_COMMAND(ID_COLOUR_24, OnColour24)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_24, OnUpdateColour24)
	ON_COMMAND(ID_COLOUR_25, OnColour25)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_25, OnUpdateColour25)
	ON_COMMAND(ID_COLOUR_26, OnColour26)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_26, OnUpdateColour26)
	ON_COMMAND(ID_COLOUR_27, OnColour27)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_27, OnUpdateColour27)
	ON_COMMAND(ID_COLOUR_28, OnColour28)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_28, OnUpdateColour28)
	ON_COMMAND(ID_COLOUR_29, OnColour29)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_29, OnUpdateColour29)
	ON_COMMAND(ID_COLOUR_30, OnColour30)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_30, OnUpdateColour30)
	ON_COMMAND(ID_COLOUR_31, OnColour31)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_31, OnUpdateColour31)
	ON_COMMAND(ID_COLOUR_32, OnColour32)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_32, OnUpdateColour32)
	ON_COMMAND(ID_COLOUR_33, OnColour33)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_33, OnUpdateColour33)
	ON_COMMAND(ID_COLOUR_34, OnColour34)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_34, OnUpdateColour34)
	ON_COMMAND(ID_COLOUR_35, OnColour35)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_35, OnUpdateColour35)
	ON_COMMAND(ID_COLOUR_36, OnColour36)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_36, OnUpdateColour36)
	ON_COMMAND(ID_COLOUR_37, OnColour37)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_37, OnUpdateColour37)
	ON_COMMAND(ID_COLOUR_38, OnColour38)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_38, OnUpdateColour38)
	ON_COMMAND(ID_COLOUR_39, OnColour39)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_39, OnUpdateColour39)
	ON_COMMAND(ID_COLOUR_8, OnColour8)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_8, OnUpdateColour8)
	ON_COMMAND(ID_COLOUR_9, OnColour9)
	ON_UPDATE_COMMAND_UI(ID_COLOUR_9, OnUpdateColour9)
	ON_COMMAND(ID_DIMENSION_VARIANT, OnDimensionVariant)
	ON_UPDATE_COMMAND_UI(ID_DIMENSION_VARIANT, OnUpdateDimensionVariant)
	ON_COMMAND(ID_COLOR_GRAYSCALE, OnColorGrayscale)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GRAYSCALE, OnUpdateColorGrayscale)
	ON_COMMAND(ID_COLOR_INVERT, OnColorInvert)
	ON_UPDATE_COMMAND_UI(ID_COLOR_INVERT, OnUpdateColorInvert)
	ON_COMMAND(ID_DRAW_61, OnDraw61)
	ON_UPDATE_COMMAND_UI(ID_DRAW_61, OnUpdateDraw61)
	ON_COMMAND(ID_DRAW_62, OnDraw62)
	ON_UPDATE_COMMAND_UI(ID_DRAW_62, OnUpdateDraw62)
	ON_COMMAND(ID_DRAW_63, OnDraw63)
	ON_UPDATE_COMMAND_UI(ID_DRAW_63, OnUpdateDraw63)
	ON_COMMAND(ID_DRAW_64, OnDraw64)
	ON_UPDATE_COMMAND_UI(ID_DRAW_64, OnUpdateDraw64)
	ON_COMMAND(ID_DRAW_65, OnDraw65)
	ON_UPDATE_COMMAND_UI(ID_DRAW_65, OnUpdateDraw65)
	ON_COMMAND(ID_DRAW_66, OnDraw66)
	ON_UPDATE_COMMAND_UI(ID_DRAW_66, OnUpdateDraw66)
	ON_COMMAND(ID_DRAW_67, OnDraw67)
	ON_UPDATE_COMMAND_UI(ID_DRAW_67, OnUpdateDraw67)
	ON_COMMAND(ID_DRAW_68, OnDraw68)
	ON_UPDATE_COMMAND_UI(ID_DRAW_68, OnUpdateDraw68)
	ON_COMMAND(ID_DRAW_69, OnDraw69)
	ON_UPDATE_COMMAND_UI(ID_DRAW_69, OnUpdateDraw69)
	ON_COMMAND(ID_DRAW_70, OnDraw70)
	ON_UPDATE_COMMAND_UI(ID_DRAW_70, OnUpdateDraw70)
	ON_COMMAND(ID_DRAW_71, OnDraw71)
	ON_UPDATE_COMMAND_UI(ID_DRAW_71, OnUpdateDraw71)
	ON_COMMAND(ID_DRAW_72, OnDraw72)
	ON_UPDATE_COMMAND_UI(ID_DRAW_72, OnUpdateDraw72)
	ON_COMMAND(ID_DRAW_73, OnDraw73)
	ON_UPDATE_COMMAND_UI(ID_DRAW_73, OnUpdateDraw73)
	ON_COMMAND(ID_DRAW_74, OnDraw74)
	ON_UPDATE_COMMAND_UI(ID_DRAW_74, OnUpdateDraw74)
	ON_COMMAND(ID_DRAW_75, OnDraw75)
	ON_UPDATE_COMMAND_UI(ID_DRAW_75, OnUpdateDraw75)
	ON_COMMAND(ID_DRAW_76, OnDraw76)
	ON_UPDATE_COMMAND_UI(ID_DRAW_76, OnUpdateDraw76)
	ON_COMMAND(ID_DRAW_77, OnDraw77)
	ON_UPDATE_COMMAND_UI(ID_DRAW_77, OnUpdateDraw77)
	ON_COMMAND(ID_DRAW_78, OnDraw78)
	ON_UPDATE_COMMAND_UI(ID_DRAW_78, OnUpdateDraw78)
	ON_COMMAND(ID_DRAW_79, OnDraw79)
	ON_UPDATE_COMMAND_UI(ID_DRAW_79, OnUpdateDraw79)
	ON_COMMAND(ID_DRAW_80, OnDraw80)
	ON_UPDATE_COMMAND_UI(ID_DRAW_80, OnUpdateDraw80)
	ON_COMMAND(ID_DRAW_81, OnDraw81)
	ON_UPDATE_COMMAND_UI(ID_DRAW_81, OnUpdateDraw81)
	ON_COMMAND(ID_DRAW_82, OnDraw82)
	ON_UPDATE_COMMAND_UI(ID_DRAW_82, OnUpdateDraw82)
	ON_COMMAND(ID_DRAW_83, OnDraw83)
	ON_UPDATE_COMMAND_UI(ID_DRAW_83, OnUpdateDraw83)
	ON_COMMAND(ID_DRAW_84, OnDraw84)
	ON_UPDATE_COMMAND_UI(ID_DRAW_84, OnUpdateDraw84)
	ON_COMMAND(ID_DRAW_85, OnDraw85)
	ON_UPDATE_COMMAND_UI(ID_DRAW_85, OnUpdateDraw85)
	ON_COMMAND(ID_DRAW_86, OnDraw86)
	ON_UPDATE_COMMAND_UI(ID_DRAW_86, OnUpdateDraw86)
	ON_COMMAND(ID_DRAW_87, OnDraw87)
	ON_UPDATE_COMMAND_UI(ID_DRAW_87, OnUpdateDraw87)
	ON_COMMAND(ID_DRAW_88, OnDraw88)
	ON_UPDATE_COMMAND_UI(ID_DRAW_88, OnUpdateDraw88)
	ON_COMMAND(ID_DRAW_89, OnDraw89)
	ON_UPDATE_COMMAND_UI(ID_DRAW_89, OnUpdateDraw89)
	ON_COMMAND(ID_DRAW_90, OnDraw90)
	ON_UPDATE_COMMAND_UI(ID_DRAW_90, OnUpdateDraw90)
	ON_COMMAND(ID_DRAW_91, OnDraw91)
	ON_UPDATE_COMMAND_UI(ID_DRAW_91, OnUpdateDraw91)
	ON_COMMAND(ID_DRAW_92, OnDraw92)
	ON_UPDATE_COMMAND_UI(ID_DRAW_92, OnUpdateDraw92)
	ON_COMMAND(ID_DRAW_93, OnDraw93)
	ON_UPDATE_COMMAND_UI(ID_DRAW_93, OnUpdateDraw93)
	ON_COMMAND(ID_DRAW_94, OnDraw94)
	ON_UPDATE_COMMAND_UI(ID_DRAW_94, OnUpdateDraw94)
	ON_COMMAND(ID_DRAW_95, OnDraw95)
	ON_UPDATE_COMMAND_UI(ID_DRAW_95, OnUpdateDraw95)
	ON_COMMAND(ID_DRAW_96, OnDraw96)
	ON_UPDATE_COMMAND_UI(ID_DRAW_96, OnUpdateDraw96)
	ON_COMMAND(ID_DRAW_97, OnDraw97)
	ON_UPDATE_COMMAND_UI(ID_DRAW_97, OnUpdateDraw97)
	ON_COMMAND(ID_DRAW_98, OnDraw98)
	ON_UPDATE_COMMAND_UI(ID_DRAW_98, OnUpdateDraw98)
	ON_COMMAND(ID_DRAW_99, OnDraw99)
	ON_UPDATE_COMMAND_UI(ID_DRAW_99, OnUpdateDraw99)
	ON_COMMAND(ID_DRAW_100, OnDraw100)
	ON_UPDATE_COMMAND_UI(ID_DRAW_100, OnUpdateDraw100)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)

	// non-modal dialogs
	ON_MESSAGE(WM_DLGGRADIENT, OnApply_GradView)
	ON_MESSAGE(WM_DLGSHIFT, OnApply_ShiftView)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTierazonView construction/destruction

CTierazonView::CTierazonView()
{
	m_pGradView			= new CGradient(this);
	m_pConvolutView = new CConvolut(this);

	bFitToPage = FALSE;
	bStretchToFit = FALSE;
	lOffCenter = 0;
	PrtScale = 1.0; // Print Scaling, (1= 1:1 Resolution, 2 = 2:1, etc.)
	CrtScale = 1.0; // CrtScaling Scaling, (1= 1:1 Resolution, 2 = 2:1, etc.)

	nImageSize = 0;
	dim.cx = global_width;
	dim.cy = global_height;
	dim_save.cx = 0;
	dim_save.cy = 0;

	nRedStart = 143;
	nGrnStart = 58;
	nBluStart = 27;

	nColorOrder = 4;
	nColorMethod = 0;
	nColorMethodSave = 0;
	nFilterSave = 0;
	nDistortionSave = 0;
	nFDOptionSave = 0;

	min = 0;
	max = 64;

	uTimer1 = NULL;

	nRed = 2;
	nGrn = 2;
	nBlu = 2;

	bRed = NULL;
	bGrn = NULL;
	bBlu = NULL;

	bRedStart = TRUE;
	bGrnStart = TRUE;
	bBluStart = TRUE;

	bGenesisMode = TRUE;

	bEdgeDetect		= FALSE;
	bEmboss				= FALSE;
	bSharpen			= FALSE;
	bBlur					= FALSE;
	bAverage			= FALSE;
	bReduceSize		= FALSE;

	Convo_Title   = "";
	nMatrix = 0;
	m_pConvolutView->bConvoluteContinuous = FALSE;
	bTraceContour = FALSE;

	iIter_Data = NULL;
	rIter_Data = NULL;
	gIter_Data = NULL;
	bIter_Data = NULL;

	pXTemp = NULL;	// pointer to x temp array
	pYTemp = NULL;  // pointer to y temp array

	rjData = NULL;
	gjData = NULL;
	bjData = NULL;

	pXSave = NULL;
	pYSave = NULL;
	
	bDraw	= FALSE;
	bLaunch = FALSE;
	bAbort = FALSE;
	bGradient	= FALSE;

	ActiveTitle = "";

	CRMIN  	= -2; //-2.0;			//		// left
	CIMIN  	= -2; //-1.33333;	//    // top
	CRMAX  	=  2; // 1.0;			//	  // right
	CIMAX  	=  2; // 1.33333;	//	  // bottom
	dMagnification = 1;

	dMIN		= 1e-11;
		
	CRMID = CRMID_Finish = ((CRMAX - CRMIN) / 2.0) + CRMIN;
  CIMID	= CIMID_Finish = ((CIMAX - CIMIN) / 2.0) + CIMIN;
 	CRMIN_JUL = -1.5;
	CIMIN_JUL = -1.5;
	CRMAX_JUL =  1.5;
  CIMAX_JUL =  1.5;

	CRMIN_NEW = 0;
	CIMIN_NEW = 0;
	CRMAX_NEW = 0;
  CIMAX_NEW = 0;

	CRMIN_OLD = 0;
	CIMIN_OLD = 0;
	CRMAX_OLD = 0;
  CIMAX_OLD = 0;

	NMAX = 128;
	NMAX_Save = 0;
	dBailout = 4;

	dLower   = 20;
	dUpper	 = 150;

	jul 		 = 0;
	jul_save = 1;

  mHSize  = AfxGetApp ()->LoadStandardCursor (IDC_UPARROW);
  mHCross = AfxGetApp ()->LoadStandardCursor (IDC_CROSS);
	mWait   = AfxGetApp ()->LoadStandardCursor (IDC_WAIT);

	bTracker				= FALSE;
	bStretchToFit		= FALSE;
	bInvertFractal	= FALSE;
  
	nDistortion = 1;
	nFilter = 0;
	bInitialized = FALSE;		
	bZeroInit = FALSE;
	bColorize = TRUE;
	bColorInvert = FALSE;
	bGrayScale = FALSE;

	dStrands	= .08;
	dBiomorph = 0;
	dBay100		= 1;
	dBay1000	= 1;

	nFDOption = 0;
	bDimensionVariant = 0;

	cOrient.set_real(1);
	cOrient.set_imag(0);

  // Formulae Parser Variables
  u_real = 0;
  v_real = 0;
  w_real = 0;
  z_real = 0;

  u_imag = 0;
  v_imag = 0;
  w_imag = 0;
  z_imag = 0;
  
  strFormulae = "z*z+c";

	// DLL initialization

  hLib = LoadLibrary("rsx_file.dll");
  if (!hLib) 
	{
		DWORD err = GetLastError();
    wsprintf(buf, "Cannot load dll fails err=0x%lX = %ld", err, err);
		AfxMessageBox(buf);
        return;
  }

  lpfnFormulae = (DLLFUNC) GetProcAddress(hLib, "_formulae");
  if (!lpfnFormulae) 
	{
		wsprintf(buf, "Error: GetProcAddress(_formulae)");
		AfxMessageBox(buf);
		return;
  }

  lpfnColorUpdate = (DLLCOLOR) GetProcAddress(hLib, "_color_update");
  if (!lpfnColorUpdate) 
	{
		wsprintf(buf, "Error: GetProcAddress(_color_update)");
		AfxMessageBox(buf);
		return;
  }

  lpfnInitialize = (DLLINIT) GetProcAddress(hLib, "_initialize");
  if (!lpfnFormulae) 
	{
		wsprintf(buf, "Error: GetProcAddress(_initialize)");
		AfxMessageBox(buf);
		return;
  }
}

CTierazonView::~CTierazonView()
{
	delete m_pGradView;
	delete m_pConvolutView;

	if (bRed)
		delete bRed;
	if (bGrn)
		delete bGrn;
	if (bBlu)
		delete bBlu;

	if (iIter_Data)
		delete iIter_Data;
	if (rIter_Data)
		delete rIter_Data;
	if (gIter_Data)
		delete gIter_Data;
	if (bIter_Data)
		delete bIter_Data;

	if (rjData)
		delete rjData;
	if (gjData)
		delete gjData;
	if (bjData)
		delete bjData;

	if (pXSave)
		delete pXSave;
	if (pYSave)
		delete pYSave;

	if (pXTemp)
		delete pXTemp;
	if (pYTemp)
		delete pYTemp;

  FreeLibrary(hLib);
}

BOOL CTierazonView::PreCreateWindow(CREATESTRUCT& cs)
{
	mClassName = AfxRegisterWndClass
		(CS_HREDRAW | CS_VREDRAW,					// Class styles
		0,																// No cursor
		(HBRUSH)::GetStockObject(WHITE_BRUSH),		// Set White background brush
		0);																// No Icon

	cs.lpszClass = mClassName;

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTierazonView drawing

void CTierazonView::OnDraw(CDC* pDC)
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CSize size;
	size = pDoc->m_dib.GetSize();	
	
	int cxDIB = size.cx;
	int cyDIB = size.cy;

	CRect rcDIB;
	rcDIB.top = rcDIB.left = 0;
	rcDIB.right = cxDIB;
	rcDIB.bottom = cyDIB;

	CRect rcDest;

	GetClientRect(rrect);
	screen.cx = rrect.Width();
	screen.cy = rrect.Height();

	if (pDoc->m_dib.m_hDrawDib)
	{
		//Set the output and DIB rectangle sizes to be
		//equal to the bitmap size.

		size = pDoc->m_dib.GetSize();	
	
		int cxDIB = size.cx;
		int cyDIB = size.cy;

		DIBRect.left = DIBRect.top = 0;
		DIBRect.right = size.cx;
		DIBRect.bottom = size.cy;    
		outputRect = DIBRect;
				
		GetClientRect(clientRect); // device coords
		nXpix = clientRect.right;
		nYpix = clientRect.bottom;

		if (bStretchToFit)
		{
			outputRect.top = outputRect.left = 0;
			outputRect.right	= nXpix;
			outputRect.bottom = nYpix;
		}
		else
		{			
			// Calculate the coordinates to center the object
			if (nXpix > ((double) DIBRect.right * CrtScale))
				Orig_X = (int) ((double) nXpix/2 - 
									((double) DIBRect.right * CrtScale)/2);
			else
				Orig_X = 0;
			if (nYpix > ((double) DIBRect.bottom * CrtScale))
				Orig_Y = (int) ((double) nYpix/2 - 
									((double) DIBRect.bottom * CrtScale)/2);
			else
				Orig_Y = 0;

			outputRect.left  	= Orig_X;
  		outputRect.top   	= Orig_Y;
    	outputRect.right 	= (int) ((double) Orig_X +
    											((double) DIBRect.right * CrtScale));
    	outputRect.bottom	= (int) ((double) Orig_Y +
     											((double) DIBRect.bottom * CrtScale));				
		}

		SetScrollSizes(MM_TEXT, 
			CSize(outputRect.right - outputRect.left, 
				outputRect.bottom - outputRect.top));		

		GetClientRect(rrect);
		screen.cx = rrect.Width();
		screen.cy = rrect.Height();
		
		if (DIBRect.right > 1024 || DIBRect.bottom > 1024)
		{
			//CWaitCursor cursor;	// this will automatically display a wait cursor		
			if (pDoc->m_dib.m_hDrawDib)
				pDoc->m_dib.Draw(pDC, screen, bStretchToFit, PrtScale, lOffCenter);
			else
				AfxMessageBox("m_dib.hDrawDib Error");
		}
		else
		{
			if (pDoc->m_dib.m_hDrawDib)
				pDoc->m_dib.Draw(pDC, screen, bStretchToFit, PrtScale, lOffCenter);
			else
				AfxMessageBox("m_dib.hDrawDib Error");
		}

	///////////////////////////////////////////////////////////////////////////////////////////////////////

		if (!bDraw && bGenesisMode && bTracker)
		{  		
			spt = GetScrollPosition();

			rb_width = rubberBand.right - rubberBand.left;
			rb_height = rubberBand.bottom - rubberBand.top;
			
			// Redraw the tracking rectangle
			// Transform to display coordinates
	 		
			rb_center_x = ((rubberBand.right - rubberBand.left) / 2)
												+ rubberBand.left;
			rb_center_y = ((rubberBand.bottom - rubberBand.top) / 2)
												+ rubberBand.top;

			// calculate the average width & height
	    rb_avg = (((rubberBand.right - rubberBand.left) +
									 (rubberBand.bottom - rubberBand.top)) / 2);
			rb_avg -= 6;
			
			dim_avg = (dim.cx + dim.cy) / 2;

			// Calculate transformed points			
	 		rubberBand.left = pDoc->m_tracker.m_rect.left = rb_center_x - 
	 			(int) (((double) rb_avg * ((double) dim.cx / (double) dim_avg)) / 2);
	 			
	 		rubberBand.right = pDoc->m_tracker.m_rect.right = rb_center_x + 
	 			(int) (((double) rb_avg * ((double) dim.cx / (double) dim_avg)) / 2);

	 		rubberBand.top = pDoc->m_tracker.m_rect.top = rb_center_y - 
	 			(int) (((double) rb_avg * ((double) dim.cy / (double) dim_avg)) / 2);

	 		rubberBand.bottom = pDoc->m_tracker.m_rect.bottom = rb_center_y + 
	 			(int) (((double) rb_avg * ((double) dim.cy / (double) dim_avg)) / 2);

			pDoc->m_tracker.m_rect = rubberBand;

			// Draw new Tracking Rectangle.
			if (rb_avg > 4)
				pDoc->m_tracker.Draw(pDC);
			else
				pDoc->m_tracker.m_rect.SetRectEmpty();	
		}

	///////////////////////////////////////////////////////////////////////////////////////////////////////

		if (!bDraw && uTimer1 == NULL)
		{
			GetParent()->SetWindowText(pDoc->GetTitle() + " - " +  ActiveTitle);
			if (bTracker && !bStretchToFit && !bDraw)
			{
				bTracker = FALSE;
				pDoc->m_tracker.GetTrueRect(rubberBand);
				pDoc->m_tracker.Draw(pDC);
			
				rb_left 	 	= (double) rubberBand.left 	/ CrtScale;
				rb_top  		= (double) rubberBand.top  	/ CrtScale;
				rb_right  	= (double) rubberBand.right 	/ CrtScale;
				rb_bottom 	= (double) rubberBand.bottom / CrtScale;

				rubberBand.left 	 = (int) rb_left		+ spt.x;
				rubberBand.top  	 = (int) rb_top			+ spt.y;
				rubberBand.right 	 = (int) rb_right		+ spt.x;
				rubberBand.bottom  = (int) rb_bottom  + spt.y;
																
				// Scale the Screen coordinates
				sxmin = 
					((double ) rubberBand.left / CrtScale - 
					(double ) Orig_X) / ((double ) (dim.cx+1)); 
					//(double ) Orig_X) / ((double ) (dim.cx + 1)); 
				sxmax =
					((double ) rubberBand.right / CrtScale -
					(double ) Orig_X) / ((double ) (dim.cx+1));
					//(double ) Orig_X) / ((double ) (dim.cx + 1));
				symin = 
					((double ) rubberBand.bottom / CrtScale - 
		 			(double ) Orig_Y) / ((double ) (dim.cy+1));
		 			//(double ) Orig_Y) / ((double ) (dim.cy + 1));		
				symax = 
   	 			((double ) rubberBand.top / CrtScale - 
    			(double ) Orig_Y) / ((double ) (dim.cy+1));
    			//(double ) Orig_Y) / ((double ) (dim.cy + 1));

				x_size = CRMAX - CRMIN;
				y_size = CIMAX - CIMIN;

				// Get new fractal coordinates
				CRMIN_NEW = x_size * sxmin + CRMIN;
				CRMAX_NEW = x_size * sxmax + CRMIN;

 				CIMIN_NEW = CIMAX - y_size * symin;
				CIMAX_NEW = CIMAX - y_size * symax;

				CRMID_OLD = CRMID;
				CIMID_OLD = CIMID;
		
				CRMID = ((CRMAX_NEW - CRMIN_NEW) / 2.0) + CRMIN_NEW;
				CIMID	= ((CIMAX_NEW - CIMIN_NEW) / 2.0) + CIMIN_NEW;

				// Calculate the Magnification (2 / average of width & length)
 				dMag_new = ((fabs(CRMAX_NEW - CRMIN_NEW) / 2) 
 										+ (fabs(CIMAX_NEW - CIMIN_NEW) / 2)) / 2;
				if (dMag_new) 
					dMag_new = (1 / dMag_new) * 2;
 			   				
				if (!pDC->IsPrinting())   // if not printer DC
					sprintf(cstr, 
						"Center_R=%f, Center_I=%f, L=%f, T=%f, R=%f, B=%f, Mn=%f",
							CRMID, CIMID, CRMIN_NEW, CIMAX_NEW, CRMAX_NEW, CIMIN_NEW, dMag_new);

				// Draw an X inside the Rubber Band
				CPen penBlackDash(PS_DOT, 0, (COLORREF) 0);
				CPen *ppenDefault = pDC->SelectObject(&penBlackDash);

				pDC->MoveTo(rubberBand.left, rubberBand.top);
				pDC->LineTo(rubberBand.right, rubberBand.bottom);
				pDC->MoveTo(rubberBand.right, rubberBand.top);
				pDC->LineTo(rubberBand.left, rubberBand.bottom);
		  
				pDC->SelectObject(ppenDefault);		
			}	
			else
			{								
				// Calculate the Magnification (2 / average of width & length)
 				//dMagnification = ((fabs(CRMAX - CRMIN) / 2) 
 				//						+ (fabs(CIMAX - CIMIN) / 2)) / 2;
				//if (dMagnification) 
				//	dMagnification = (1 / dMagnification) * 2;

				sprintf(cstr, 
					"Center_R=%f, Center_I=%f, L=%f, T=%f, R=%f, B=%f, M=%f",
						CRMID, CIMID, CRMIN, CIMAX, CRMAX, CIMIN, dMagnification);		
			}
			
			Status_Bar(cstr);

			if (m_pGradView->GetSafeHwnd() != 0)
			{
				m_pGradView->SetDlgItemInt(IDC_START_RED, nRedStart);
				m_pGradView->SetDlgItemInt(IDC_START_GREEN, nGrnStart);
				m_pGradView->SetDlgItemInt(IDC_START_BLUE, nBluStart);

				m_pGradView->SetDlgItemInt(IDC_INC_RED, nRed);
				m_pGradView->SetDlgItemInt(IDC_INC_GREEN, nGrn);
				m_pGradView->SetDlgItemInt(IDC_INC_BLUE, nBlu);

			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTierazonView printing

BOOL CTierazonView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTierazonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTierazonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTierazonView diagnostics

#ifdef _DEBUG
void CTierazonView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTierazonView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTierazonDoc* CTierazonView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTierazonDoc)));
	return (CTierazonDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTierazonView message handlers

void CTierazonView::OnContextMenu(CWnd*, CPoint point)
{
	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_TIERAZON_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CTierazonView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (bActivate)
	{
		// Realize my palette if necessary
		CDC* pDC = GetDC();

		UINT nColorsRealized = 
			DrawDibRealize(GetDocument()->m_dib.m_hDrawDib, pDC->GetSafeHdc(), FALSE);

		ReleaseDC(pDC);

		if (nColorsRealized > 0)
			Invalidate(TRUE);
	}
	
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CTierazonView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	CTierazonDoc* pDoc = GetDocument();

	if (bNewView && bZoomingMode)
	{
    if ( ! outFile.Open( szTempFileName, CFile::modeRead ))
    {
      bZoomingMode = FALSE;
      AfxMessageBox ( "Error, Opening File:" + szTempFileName );
			outFile.Close();
			return;
    }
    else
    {
			bNewView = FALSE;
			// Read the parameters from the ASCII file
			Loadparameters();

			// Look for the two common sizes
			if ((nImageSize == 0 && dim.cx == 160 && dim.cy == 120))
			{
				// Do Nothing
			}
			else
			if ((nImageSize == 1 && dim.cx == 256 && dim.cy == 256))
			{
				// Do Nothing
			}
			else
				nImageSize = 10; // Set to custom size

			// Create a new DIB
			if (!pDoc->m_dib.CreateDIB((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
			{
				AfxMessageBox("Error Creating DIB");
			}

			//if (nMatrix)
			//{
			//	if (!pDoc->m_dib.CreateDIB_Temp((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
			//	{
			//		AfxMessageBox("Error Creating DIB_Temp");
			//		return;
			//	}
			//}

			GetParentFrame()->SetWindowPos(NULL, 0, 0, dim.cx+40, dim.cy+60,
				SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_DRAWFRAME);

			///////////////////////////////////
			//AfxMessageBox("Step 1");
			bDraw = TRUE;
			bLaunch = FALSE;
		}
		outFile.Close();

		//if (bAutoTile)
	    //AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_WINDOW_TILE_HORZ);
	}

	else if (pDoc->doc_PathName == "")
	{
		// Initial size of new bitmap
		pDoc->m_sizeDoc.cx = global_width;
		pDoc->m_sizeDoc.cy = global_height;

		dim = pDoc->m_sizeDoc;

		if (!pDoc->m_dib.CreateDIB((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
		{
			AfxMessageBox("Error Creating DIB");
		}
		
		//if (nMatrix)
		//{
		//	if (!pDoc->m_dib.CreateDIB_Temp((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
		//	{
		//		AfxMessageBox("Error Creating DIB_Temp");
		//		return;
		//	}
		//}

		dim = pDoc->GetDocSize();

    if (outFile.Open( szInkFileName, CFile::modeRead ))	
		{
			bNewView = FALSE;
			Loadparameters();
			outFile.Close();

			szTemp = szTempFileName;
			szTemp.GetBufferSetLength(szTempFileName.GetLength()-3);
			szTemp += "bmp";
			
			if (!pDoc->OnOpenDocument(szTemp))
			{
				bDraw = TRUE;
				bLaunch = FALSE;
			}
			else
			{
		    //OnWindowSizedesktop();
				dim = pDoc->GetDocSize();
				bInitialized = FALSE;
			}
		}
		else
		{
			////////////////////////////////////////////////////////////
			
			// Open the default color file
			if ( ! outFile.Open( szColorFileName, CFile::modeRead ))
			{
				// Create the initial color file
				szTemp = "Jungle.clr";

				// File "Save As" Routine

				if ( ! outFile.Open( szTemp, 
     							CFile::modeWrite | CFile::modeCreate))
				{
					AfxMessageBox ( "Error, Creating File:" + szTemp );
					return;
				}	

				szColorFileName = outFile.GetFilePath();

				// Write the Colours out to an ASCII file
			
				// Write nRedStart
				sprintf(cstr,"%d", nRedStart);
				szTemp = cstr;
				outFile.WriteString(szTemp + '\n');			

				// Write nGrnStart
				sprintf(cstr,"%d", nGrnStart);
				szTemp = cstr;
				outFile.WriteString(szTemp + '\n');			

				// Write nBluStart
				sprintf(cstr,"%d", nBluStart);
				szTemp = cstr;
				outFile.WriteString(szTemp + '\n');			

				// Write nRed
				sprintf(cstr,"%d", nRed);
				szTemp = cstr;
				outFile.WriteString(szTemp + '\n');			

				// Write nGrn
				sprintf(cstr,"%d", nGrn);
				szTemp = cstr;
				outFile.WriteString(szTemp + '\n');			

				// Write nBlu
				sprintf(cstr,"%d", nBlu);
				szTemp = cstr;
				outFile.WriteString(szTemp + '\n');			
		
				outFile.Close();

				AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_DRAW_1);		
			
				GetParentFrame()->SetWindowPos(NULL, 0, 0, dim.cx+40, dim.cy+60,
					SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_DRAWFRAME);
				
				SetScrollSizes(MM_TEXT, GetDocument()->GetDocSize());	

				Invalidate();		
				return;
			}

			// Read nRedStart
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nRedStart);

			// Read nGrnStart
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nGrnStart);

			// Read nBluStart
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nBluStart);

			// Read nRed
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nRed);

			// Read nGrn
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nGrn);

			// Read nBlu
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nBlu);

			outFile.Close();
			
			//////////////////////////////////////////////////////////			
			SetScrollSizes(MM_TEXT, GetDocument()->GetDocSize());	

			AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_DRAW_1);		
			//OnViewBackground();
			//AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_PALETTE_SCALED);		
			
		}

		GetParentFrame()->SetWindowPos(NULL, 0, 0, dim.cx+40, dim.cy+60,
			SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_DRAWFRAME);

		//outFile.Close();

		//if (!(nImageSize == 1 && dim.cx == 256 && dim.cy == 256))
		//	nImageSize = 10; // Set to custom size

		// Look for the two common sizes
		if ((nImageSize == 0 && dim.cx == 160 && dim.cy == 120))
		{
			// Do Nothing
		}
		else
		if ((nImageSize == 1 && dim.cx == 256 && dim.cy == 256))
		{
			// Do Nothing
		}
		else
			nImageSize = 10; // Set to custom size
		
	}
	else
	{
		// Get the size of the bitmap
		dim = pDoc->m_sizeDoc;

		// Opening Bitmap from file
    OnWindowSizedesktop();

		// Open the equivalent parameters file, if one exists
		CString szTemp;

		szTemp = pDoc->doc_PathName;
		szTemp = szTemp.GetBufferSetLength(szTemp.GetLength()-3);
		szTemp += "zar";
    
		if ( outFile.Open( szTemp, CFile::modeRead ))
    {
			// Read the parameters from the ASCII file
			Loadparameters();			
			outFile.Close();

			//bDraw = TRUE;
			//bLaunch = FALSE; // Redraw to initialize the temp buffers.
			bInitialized = FALSE;		
		}
	}

	SetScrollSizes(MM_TEXT, GetDocument()->GetDocSize());	
	bZoomingMode = FALSE;

  Invalidate();		

}

void CTierazonView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
  switch (lHint)
	{
		case ID_APPLICATION_IDLE:
			if (!bDraw && uTimer1)
				Shift_Step();	
			else
				DrawPattern();
			break;

    default:
      break;
  }			
}

void CTierazonView::OnWindowSizedesktop() 
{
	int ccx, ccy;

	CRect rParentArea;
	GetActiveWindow()->GetWindowRect(rParentArea);

 	ccx = rParentArea.right - rParentArea.left - 20;
 	ccy = rParentArea.bottom - rParentArea.top - 45;

	//char cstr[81];
	//wsprintf(cstr,"top=%d, left=%d, ccx=%d,  ccy=%d",
	//	rParentArea.top, rParentArea.left, ccx, ccy);
	//AfxMessageBox(cstr);	

	if (dim.cx + 40 > ccx)
		ccx = ccx - 100;
	else
		ccx = dim.cx;

	if (dim.cy + 60 > ccy)
		ccy = ccy - 150;
	else
		ccy = dim.cy;

	GetParentFrame()->SetWindowPos(NULL, 0, 0, ccx+40, ccy+60,
		SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_DRAWFRAME);
		//SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);	
	
	GetParentFrame()->PostMessage(WM_SIZE);

}

void CTierazonView::Window_Pane(int nStat)
{
  ////////////////////////////////////////////////////////////////////
  // Output something to the Window Caption Bar
	//
	char cstr[81];
	wsprintf(cstr, "%d",nStat);
	GetParent()->SetWindowText(cstr);
}

void CTierazonView::Status_Bar(char* bar_txt)
{
  ////////////////////////////////////////////////////////////////////
  // Output something to the status bar
	//
 	CStatusBar* pStatus = (CStatusBar*)
   	AfxGetApp()->m_pMainWnd->GetDlgItem(AFX_IDW_STATUS_BAR);
  if (pStatus) 
  {
  	pStatus->SetPaneText(0, bar_txt);
  }
}

void CTierazonView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Get Pointer to Document
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  
	//rubberBand.left = point.x;
  //rubberBand.top  = point.y;
  
	// If clicked inside, drag or resize it. Otherwise create a 
	// rubber band rectangle
	BOOL bResult = pDoc->m_tracker.HitTest(point) != CRectTracker::hitNothing;

	// Tracker rectangle changed so update views.
  if (bResult)
		pDoc->m_tracker.Track(this, point, TRUE);
	else
		 pDoc->m_tracker.TrackRubberBand(this, point, TRUE);

	// pDoc->SetModifiedFlag();

	pDoc->m_tracker.GetTrueRect(rubberBand);

	if (rubberBand.right - rubberBand.left > 10 && 
			rubberBand.bottom - rubberBand.top > 10)
  {
		if (CrtScale == 1) 
			bTracker = TRUE;
		else
			bTracker = FALSE;
  }
  
	pDoc->UpdateAllViews(NULL);  

	if (rsave.left		< Orig_X ||
			rsave.right		> Orig_X + dim.cx ||
			rsave.bottom	> Orig_Y + dim.cy ||
			rsave.top			< Orig_Y)
		Invalidate(TRUE);  	
	else
		Invalidate(FALSE);  	

	rsave.left		= rubberBand.left;
	rsave.right		= rubberBand.right;
	rsave.bottom	= rubberBand.bottom;
	rsave.top			= rubberBand.top;
		
	//bBDown = TRUE;
	//bTracker = TRUE;
	
	CScrollView::OnLButtonDown(nFlags, point);
}

void CTierazonView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  
	// If moving inside the rectangle, drag or resize it. Otherwise
	// show a Cross-hair Cursor
	BOOL bResult = pDoc->m_tracker.HitTest(point) != CRectTracker::hitNothing;

	// Tracker rectangle changed so update views.
  if (bResult)
		::SetCursor(mHSize);
	else
		::SetCursor(mHCross);
	
	CScrollView::OnMouseMove(nFlags, point);
}

void CTierazonView::OnImageSize() 
{
	CTierazonDoc* pDoc = GetDocument();
	XYSize px;
	dim = pDoc->m_sizeDoc;

	px.m_ImageSize = nImageSize;
	px.m_X_Custom = dim.cx;
	px.m_Y_Custom = dim.cy;
	if (px.DoModal() == IDOK)
	{		
		nImageSize = px.m_ImageSize;
		bInitialized = FALSE;
	  switch (nImageSize)
  	{
  		case 0:
  			dim.cx = 160;
  			dim.cy = 120;
  			break;
  		case 1:
  			dim.cx = 256;
  			dim.cy = 256;
  			break;
  		case 2:
	 			dim.cx = 320;
  			dim.cy = 240;
  			break;
  		case 3:
  			dim.cx = 640;
  			dim.cy = 480;
  			break;
  		case 4:
  			dim.cx = 800;
  			dim.cy = 600;
  			break;
  		case 5:
  			dim.cx = 1024;    //
  			dim.cy =  768;    //
  			break;
  		case 6:
  			dim.cx = 1280;    //  640*2
  			dim.cy =  960;    //	480*2
  			break;
  		case 7:
  			dim.cx = 1600;    //  800*2
  			dim.cy = 1200;    //	600*2
  			break;
  		case 8:
  			dim.cx = 2560;    //  640*4
  			dim.cy = 1920;    //  480*4
	  		break;
  		case 9:
				dim.cx = 3564;
				dim.cy = 2784;

  			break;

	  	case 10:
  			//	dim.cx = 3072;    // This size gets a creation error
  		 	//	dim.cy = 2304;    // 

				// Get custom sizes
				dim.cx = px.m_X_Custom & 0x7FFC; // Make even bitmap sizes
				dim.cy = px.m_Y_Custom & 0x7FFC;
					
				break;

  		default:
  			AfxMessageBox("Shouldn't Get Here - OnImageSize");
				return;
  	}
		
		global_width = dim.cx;
		global_height = dim.cy;

		pDoc->m_sizeDoc	= dim;

		// Create a new DIB
		if (!pDoc->m_dib.CreateDIB((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
		{
			AfxMessageBox("Error Creating DIB");
		}

		//if (nMatrix)
		//{
		//	if (!pDoc->m_dib.CreateDIB_Temp((DWORD) dim.cx, (DWORD) dim.cy))	// Create a bitmap
		//	{
		//		AfxMessageBox("Error Creating DIB_Temp");
		//		return;
		//	}
		//}

		OnWindowSizedesktop();

    //if (nDistortion == (-1))
  		//OnViewBackground();

    if (nDistortion >= 0)
    {
      bDraw = TRUE;
		  bLaunch = FALSE;
    }
	}
}

void CTierazonView::OnViewZoom() 
{
	// Get Pointer to Document
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  pDoc->m_tracker.m_rect.SetRectEmpty();	
		
	if (CRMIN_NEW < CRMAX_NEW &&
			CIMIN_NEW < CIMAX_NEW)
	{		
		bZoomingMode = TRUE;

		CRMIN_OLD = CRMIN;
		CIMIN_OLD = CIMIN;
		CRMAX_OLD = CRMAX;
		CIMAX_OLD = CIMAX;
			
		CRMIN = CRMIN_NEW;
		CIMIN = CIMIN_NEW;
		CRMAX = CRMAX_NEW;
		CIMAX = CIMAX_NEW;
		
		CRMIN_JUL = CRMIN_NEW;
		CIMIN_JUL = CIMIN_NEW;
		CRMAX_JUL = CRMAX_NEW;
		CIMAX_JUL = CIMAX_NEW;

		CRMIN_NEW = 0;
		CIMIN_NEW = 0;
		CRMAX_NEW = 0;
		CIMAX_NEW = 0;

		//////////////////////////////////////////
		if (bNewView)
		{
			// Create new view and return			
			ViewNew();
			OnEditUndofractalselection();
			return;
		}	
		else
		{
			if (jul == 0 || jul_save == 1)
			{
				rx_ratio = (double) dim.cx/(double) (dim.cy);
				ry_ratio = (double) dim.cy/(double) (dim.cx);

				rx_ratio = rx_ratio + (1-rx_ratio)/2;
				ry_ratio = ry_ratio + (1-ry_ratio)/2;

				// Calculate the Magnification (2 / average of width & length)
 				dMagnification = ((fabs((CRMAX - CRMIN)/rx_ratio) / 2) 
 							+ (fabs((CIMAX - CIMIN)/ry_ratio) / 2)) / 2;
				if (dMagnification) 
					dMagnification = (1 / dMagnification) * 2;

			}			
			//OnViewBackground();
			bDraw = TRUE;			
			bLaunch = FALSE;
		}
 	}	
}

void CTierazonView::OnUpdateViewZoom(CCmdUI* pCmdUI) 
{
	if (CRMIN_NEW < CRMAX_NEW &&
			CIMIN_NEW < CIMAX_NEW)
	{		
		pCmdUI->Enable(TRUE);	
	}	
	else
		pCmdUI->Enable(FALSE);	
}

void CTierazonView::OnViewNew() 
{
	bNewView ^= 1;
}

void CTierazonView::OnUpdateViewNew(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bNewView);	
}

void CTierazonView::ViewNew() 
{	
  if (!outFile.Open( szTempFileName, 
     		CFile::modeWrite | CFile::modeCreate))
  {
    AfxMessageBox ( "Error, Opening File:" + szTempFileName );
		outFile.Close();
		return;
	}	
	else
	{
		// Write the parameters out to an ASCII file
		Saveparameters();                                    
	}
	outFile.Close();

	// Close the Gradient window to avoid confusion if one is open
	if (m_pGradView->GetSafeHwnd())
		m_pGradView->DestroyWindow();	
	
	GetParent()->SendMessage(WM_COMMAND, ID_FILE_NEW);	

}

void CTierazonView::OnSaveDib() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Save Parameters File
	szTemp =
	pDoc->doc_PathName.GetBufferSetLength(pDoc->doc_PathName.GetLength()-3);
	szTemp = szTemp + "zar";

	// Write the parameters out to an ASCII file
	if (!outFile.Open( szTemp, 
     		CFile::modeWrite | CFile::modeCreate))
  {
    AfxMessageBox ( "Error, Opening File:" + szTemp );
		return;
	}	
	else
	{
		// Write the parameters out to an ASCII file
		Saveparameters();                                    
	}
	outFile.Close();

}

void CTierazonView::OnFileSavecolors() 
{
  szTemp = "Jungle.clr";

	// File "Save As" Routine

	CFileDialog dlg
	    (FALSE,
	   	"clr",
	   	szTemp,          
	    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	    "Tierazon Colors (*.clr)|*.clr|All Files (*.*)|*.*||");

  if (dlg.DoModal() == IDOK)
  {
  	szTemp = dlg.GetPathName();              
    if ( ! outFile.Open( szTemp, 
     							CFile::modeWrite | CFile::modeCreate))
    {
      AfxMessageBox ( "Error, Opening File:" + szTemp );
			return;
		}	
		else
		{
			// Write the parameters out to an ASCII file
			
			// Write nRedStart
			sprintf(cstr,"%d", nRedStart);
			szTemp = cstr;
			outFile.WriteString(szTemp + '\n');			

			// Write nGrnStart
			sprintf(cstr,"%d", nGrnStart);
			szTemp = cstr;
			outFile.WriteString(szTemp + '\n');			

			// Write nBluStart
			sprintf(cstr,"%d", nBluStart);
			szTemp = cstr;
			outFile.WriteString(szTemp + '\n');			

			// Write nRed
			sprintf(cstr,"%d", nRed);
			szTemp = cstr;
			outFile.WriteString(szTemp + '\n');			

			// Write nGrn
			sprintf(cstr,"%d", nGrn);
			szTemp = cstr;
			outFile.WriteString(szTemp + '\n');			

			// Write nBlu
			sprintf(cstr,"%d", nBlu);
			szTemp = cstr;
			outFile.WriteString(szTemp + '\n');			
		
		}
		outFile.Close();
	}	
}

void CTierazonView::OnFileSaveparameters() 
{
  szTemp = "Tiaraz.zar";

	// File "Save As" Routine

	CFileDialog dlg
	    (FALSE,
	   	"zar",
	   	szTemp,          
	    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	    "Fractal Parameters (*.zar)|*.zar|All Files (*.*)|*.*||");

  if (dlg.DoModal() == IDOK)
  {
  	szTemp = dlg.GetPathName();              
    if ( ! outFile.Open( szTemp, 
     							CFile::modeWrite | CFile::modeCreate))
    {
      AfxMessageBox ( "Error, Opening File:" + szTemp );
			return;
		}	
		else
		{
			// Write the parameters out to an ASCII file
			Saveparameters();                                    
		}
		outFile.Close();
	}
}

void CTierazonView::Saveparameters() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	global_width	= dim.cx;
	global_height = dim.cy;
	
	// Write the parameters out to an ASCII file

	outFile.WriteString(ActiveTitle + '\n');			

	// Write the fractal type
	sprintf(cstr,"%d", nDistortion);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the 'jul' variable
	sprintf(cstr,"%d", jul);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the 'jul_save' variable
	sprintf(cstr,"%d", jul_save);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
						
	// Write the maximum iterations
	sprintf(cstr,"%d", NMAX);			// max iterations
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nRedStart Variable
	sprintf(cstr,"%d", nRedStart);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nGrnStart Variable
	sprintf(cstr,"%d", nGrnStart);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nBluStart Variable
	sprintf(cstr,"%d", nBluStart);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nRed Variable
	sprintf(cstr,"%d", nRed);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nGrn Variable
	sprintf(cstr,"%d", nGrn);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nBluStart Variable
	sprintf(cstr,"%d", nBlu);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	sprintf(cstr,"%f", (double) dBailout);		// 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CRMIN);		// x left
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CIMIN);    // y top
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CRMAX);    // x right
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CIMAX);    // y bottom
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CRMIN_JUL);		// x left
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CIMIN_JUL);    // y top
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CRMAX_JUL);    // x right
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CIMAX_JUL);    // y bottom
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CRMID);    //
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", CIMID);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", cx);    //
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", cy);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	////////////////////////////////////
	sprintf(cstr,"%f", dBay100);	// 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%f", dBay1000);	// 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
	
	sprintf(cstr,"%f", (double) dBiomorph);	// 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%f", dStrands);		// 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the bInvertFractal BOOL variable
	sprintf(cstr,"%d", bInvertFractal);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

  // Write bZeroInit BOOL Variable
	sprintf(cstr,"%d", bZeroInit);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');  

	sprintf(cstr,"%.16Lg", dMIN);		// dMIN
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the nFilter Variable
	sprintf(cstr,"%d", nFilter);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
	// Write the nColorOrder Variable
	sprintf(cstr,"%d", nColorOrder);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			
			
  ////////////////////////////////////////
  // Watermark variables
	sprintf(cstr,"%.16Lg", dLower);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", dUpper);    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

  ////////////////////////////////////////
  // Orientation variables
	sprintf(cstr,"%.16Lg", cOrient.real());    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	sprintf(cstr,"%.16Lg", cOrient.imag());    // 
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the bNewView BOOL variable
	sprintf(cstr,"%d", bNewView);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the bColorize BOOL variable
	sprintf(cstr,"%d", bColorize);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the nFDOption variable
	sprintf(cstr,"%d", nFDOption);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the nColorMethod variable
	sprintf(cstr,"%d", nColorMethod);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

	// Write the bDimensionVariant variable
	sprintf(cstr,"%d", bDimensionVariant);
	szTemp = cstr;
	outFile.WriteString(szTemp + '\n');			

}

void CTierazonView::OnFileLoadcolors() 
{
	CString szTemp;

	// File "Load From Parameters" Routine

	CFileDialog dlg
	    (TRUE,
	   	"*.clr",
	   	szTemp,          
	     OFN_HIDEREADONLY,
	    "Color Parameters (*.clr)|*.clr|All Files (*.*)|*.*||");

  if (dlg.DoModal() == IDOK)
  {
  	szTemp = dlg.GetPathName();              

    if ( ! outFile.Open( szTemp, CFile::modeRead ))
    {
      AfxMessageBox ( "Error, Opening File:" + szTemp );
			return;
    }
    else
    {
			// Read the parameters from the ASCII file

			// Read nRedStart
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nRedStart);

			// Read nGrnStart
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nGrnStart);

			// Read nBluStart
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nBluStart);

			// Read nRed
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nRed);
		
			// Read nGrn
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nGrn);
		
			// Read nBlu
			outFile.ReadString ( cstr, (sizeof(cstr)-1));
			sscanf (cstr, "%d", &nBlu);
				
		}
		outFile.Close();

		//PostMessage(WM_DLGGRADIENT, ID_APPLY);

		bDraw = TRUE;
		bLaunch = FALSE;
		//bColorChange = TRUE;

		if (m_pGradView->GetSafeHwnd() != 0)
		{		
			m_pGradView->SetDlgItemInt(IDC_START_RED, nRedStart);
			m_pGradView->SetDlgItemInt(IDC_START_GREEN, nGrnStart);
			m_pGradView->SetDlgItemInt(IDC_START_BLUE, nBluStart);

			m_pGradView->SetDlgItemInt(IDC_INC_RED, nRed);
			m_pGradView->SetDlgItemInt(IDC_INC_GREEN, nGrn);
			m_pGradView->SetDlgItemInt(IDC_INC_BLUE, nBlu);

			m_pGradView->ScrollBarInit();

			if (bForward)
				m_pGradView->SetDlgItemText(IDC_STATUS, "Forward");
			else
				m_pGradView->SetDlgItemText(IDC_STATUS, "Reverse");

			m_pGradView->UpdateData(TRUE);
			m_pGradView->ScrollBarInit();

		}
	}	
}

void CTierazonView::OnFileLoadparameters() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString szTemp;

	// File "Load From Parameters" Routine

	CFileDialog dlg
	    (TRUE,
	   	"*.zar",
	   	szTemp,          
	     OFN_HIDEREADONLY,
	    "Fractal Parameters (*.zar)|*.zar|All Files (*.*)|*.*||");

  if (dlg.DoModal() == IDOK)
  {
  	szTemp = dlg.GetPathName();              

    if ( ! outFile.Open( szTemp, CFile::modeRead ))
    {
      AfxMessageBox ( "Error, Opening File:" + szTemp );
			return;
    }
    else
    {
			// Read the parameters from the ASCII file
			Loadparameters();
			if (!(nImageSize == 1 && dim.cx == 256 && dim.cy == 256))
				nImageSize = 10; // Set to custom size
		}
		outFile.Close();

		szTemp.GetBufferSetLength(szTemp.GetLength()-3);
		szTemp += "bmp";
		
		pDoc->doc_PathName = szTemp;
		pDoc->SetTitle(szTemp);
		pDoc->SetPathName(szTemp);

		if (nDistortion)
		{
			//sprintf(cstr,"CRMID=%f,CIMID=%f",CRMID,CIMID);
			//szTemp = cstr;
			//AfxMessageBox(ActiveTitle + ": " + szTemp);

			bDraw = TRUE;
			bLaunch = FALSE;
		}	
	}
}

void CTierazonView::Loadparameters() 
{
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// Read the parameters from the ASCII file

	if (outFile.ReadString ( ctitle, (sizeof(cstr)-1)) == NULL)
	{
		AfxMessageBox("Error Reading from Parameter File:" + szTemp);
    return;
  }
      	
	ActiveTitle = ctitle;
	pDoc->doc_PathName = ActiveTitle;

	// Search for the Line Feed loacation 
	int iLFLoc = ActiveTitle.ReverseFind('\n');
	// Replace the Line Feed character with NULL for viewing
	if (iLFLoc >= 0) 
	ActiveTitle.GetBufferSetLength(ActiveTitle.GetLength()-1); 

	// Read the 'fractal type
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nDistortion);
			
	// Read the 'jul' variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &jul);

	// Read the 'jul_save' variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &jul_save);

	// Read maximum iterations
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &NMAX);     // max iterations
			
	// Read nRedStart
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nRedStart);   

	// Read nGrnStart
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nGrnStart);   

	// Read nBluStart
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nBluStart);   

	// Read nRed
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nRed);   

	// Read nGrn
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nGrn);   

	// Read nBlu
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nBlu);   

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dBailout = (int) atof(cstr);			

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CRMIN = atof(cstr);							// x left

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CIMIN = atof(cstr);							// y top

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CRMAX = atof(cstr);							// x right

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CIMAX = atof(cstr);							// y bottom

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CRMIN_JUL = atof(cstr);							// x left

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CIMIN_JUL = atof(cstr);							// y top

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CRMAX_JUL = atof(cstr);							// x right

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CIMAX_JUL = atof(cstr);							// y bottom
  
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CRMID = atof(cstr);							//

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  CIMID = atof(cstr);							//

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  cx = atof(cstr);							//

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  cy = atof(cstr);							//

	if (jul == 1)
	{
		CRMID_JUL = ((CRMAX_JUL - CRMIN_JUL) / 2.0) + CRMIN_JUL;
    CIMID_JUL	= ((CIMAX_JUL - CIMIN_JUL) / 2.0) + CIMIN_JUL;

    if (bJuliaMode)
    {
			CRMIN_JUL  	= -2.0;	//	-2.0;		// left
			CIMIN_JUL  	= -2.0;	//	-1.2;   // top
			CRMAX_JUL  	=  2.0;	//	1.0;    // right
			CIMAX_JUL  	=  2.0;	//	1.2;    // bottom
			bJuliaMode = FALSE;
		}	
	}


  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dBay100 = atof(cstr);			

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dBay1000 = atof(cstr);			

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dBiomorph = (int) atof(cstr);			

  outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dStrands = atof(cstr);

	// Read bInvertFractal BOOL variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bInvertFractal);

	// Read bZeroInit BOOL Variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bZeroInit);
			
	// Read the dMIN variable
	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dMIN = atof(cstr);							// x left

	if (dMIN == 0)
		dMIN = 1e-11;

	// Read nFilter
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nFilter);   
	
	// Read nColorOrder
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nColorOrder);   
	
	pDoc->m_sizeDoc = dim;

  ///////////////////////////////////
  // Watermark Variables
	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dLower = atof(cstr);	

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  dUpper = atof(cstr);	
  	
  ///////////////////////////////////
  // Orientation Variables
	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  cOrient.set_real(atof(cstr));	

	outFile.ReadString ( cstr, (sizeof(cstr)-1));
  cOrient.set_imag(atof(cstr));	
  		
	//if (jul != 1)
	if (jul == 0 || jul_save == 1)
	{
	  rx_ratio = (double) dim.cx/(double) (dim.cy);
	  ry_ratio = (double) dim.cy/(double) (dim.cx);

	  rx_ratio = rx_ratio + (1-rx_ratio)/2;
	  ry_ratio = ry_ratio + (1-ry_ratio)/2;

	  // Calculate the Magnification (2 / average of width & length)
 	  dMagnification = ((fabs((CRMAX - CRMIN)/rx_ratio) / 2) 
 							+ (fabs((CIMAX - CIMIN)/ry_ratio) / 2)) / 2;
	  if (dMagnification) 
		  dMagnification = (1 / dMagnification) * 2;

	}

	if (jul == 1 && jul_save == 0)
	{
		CRMID = 0;
		CIMID = 0;
	}

	// Read bNewView BOOL Variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bNewView);
			
	// Read bColorize BOOL Variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bColorize);
			
	// Read the nFDOption Variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nFDOption);
			
	// Read the nColorMethod Variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &nColorMethod);
			
	// Read the bDimensionVariant Variable
  outFile.ReadString ( cstr, (sizeof(cstr)-1));
	sscanf (cstr, "%d", &bDimensionVariant);
			
}

void CTierazonView::OnEditUndofractalselection() 
{
	if (CRMIN_OLD < CRMAX_OLD &&
			CIMIN_OLD < CIMAX_OLD)
	{		
		CRMIN = CRMIN_OLD;
		CIMIN = CIMIN_OLD;
		CRMAX = CRMAX_OLD;
		CIMAX = CIMAX_OLD;
		
		CRMID = CRMID_OLD;
		CIMID = CIMID_OLD;
		
		CRMIN_JUL = CRMIN_OLD;
		CIMIN_JUL = CIMIN_OLD;
		CRMAX_JUL = CRMAX_OLD;
		CIMAX_JUL = CIMAX_OLD;

		// Get Pointer to Document
		CTierazonDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		CRMIN_NEW = 0;
		CIMIN_NEW = 0;
		CRMAX_NEW = 0;
		CIMAX_NEW = 0;

		pDoc->m_tracker.m_rect.SetRectEmpty();	
		
		//bDraw = TRUE;
		//bLaunch = FALSE;
	}
}
	
void CTierazonView::OnViewJulia() 
{
	int jul_t1 = jul;
	int jul_save_t1 = jul_save;

	jul = 1;
	jul_save = 0;

	dMagnification = 1;
	CRMID_OLD = 0;
	CIMID_OLD = 0;

	//////////////////////////////////////////
	if (bNewView)
	{
		// Create new view and return			
		bZoomingMode = TRUE;
		bJuliaMode = TRUE;

		CRMIN_OLD = CRMIN;
		CIMIN_OLD = CIMIN;
		CRMAX_OLD = CRMAX;
		CIMAX_OLD = CIMAX;
			
		CRMIN  	= -1.0;	//		// left
		CIMIN  	= -1.0;	//    // top
		CRMAX  	=  1.0;	//	  // right
		CIMAX  	=  1.0;	//	  // bottom
		
		//CRMIN = CRMIN_NEW;
		//CIMIN = CIMIN_NEW;
		//CRMAX = CRMAX_NEW;
		//CIMAX = CIMAX_NEW;

		//CRMIN = CRMIN_JUL; 
  	//CIMIN = CIMIN_JUL;
  	//CRMAX = CRMAX_JUL;
  	//CIMAX = CIMAX_JUL;

		CRMIN_JUL = CRMIN_NEW;
		CIMIN_JUL = CIMIN_NEW;
		CRMAX_JUL = CRMAX_NEW;
		CIMAX_JUL = CIMAX_NEW;

		CRMIN_NEW = 0;
		CIMIN_NEW = 0;
		CRMAX_NEW = 0;
		CIMAX_NEW = 0;

		ViewNew();
		
		bZoomingMode = FALSE;
		bJuliaMode = FALSE;

		OnEditUndofractalselection();		// ??

		jul = jul_t1;
		jul_save = jul_save_t1;

		//dMagnification = 1;

		//CRMID_JUL = CRMID;
		//CIMID_JUL = CIMID;
	
		//CRMID = 0;
		//CIMID = 0;
		
		return;
	}	
	//else
	//	OnViewBackground();
	
	//////////////////////////////////////////
		
	CRMIN  	= -1.0;	//		// left
	CIMIN  	= -1.0;	//    // top
	CRMAX  	=  1.0;	//	  // right
	CIMAX  	=  1.0;	//	  // bottom

	CRMIN_JUL  	= -1.5;	//		// left
	CIMIN_JUL  	= -1.5;	//    // top
	CRMAX_JUL  	=  1.5;	//	  // right
	CIMAX_JUL  	=  1.5;	//	  // bottom

	dMagnification = 1;
	
	CRMID_JUL = CRMID;
	CIMID_JUL = CIMID;
	
	CRMID = 0;
	CIMID = 0;

	//nSaveDistortion = nDistortion;

	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_tracker.m_rect.SetRectEmpty();	

	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateViewJulia(CCmdUI* pCmdUI) 
{
	if (CRMIN_NEW < CRMAX_NEW &&
			CIMIN_NEW < CIMAX_NEW)
	{		
		if (jul == 0)
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}

	if (jul == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnImageParams() 
{
  CFParams fparam;
	//fparam.m_Top 				= (double) CIMAX;
	//fparam.m_Bottom 		= (double) CIMIN;
	//fparam.m_Left   		= (double) CRMIN;
	//fparam.m_Right   		= (double) CRMAX;

	fparam.m_Magnification = dMagnification;
	fparam.m_X_Mid = CRMID;
	fparam.m_Y_Mid = CIMID;

	fparam.m_Iterations	=	NMAX;
	//fparam.m_dMIN				=	dMIN;
	fparam.m_Bailout    = (double) dBailout;

	fparam.m_Upper  = dUpper;
	fparam.m_Lower  = dLower;

	fparam.m_BayFact1 = (double) dBay100;
	fparam.m_BayFact2 = (double) dBay1000;

	fparam.m_Strands = dStrands;

	if (jul == 1)
	{
		fparam.m_Julia_X = cx;
		fparam.m_Julia_Y = cy;
	}
	else
	{
		fparam.m_Julia_X = 0;
		fparam.m_Julia_Y = 0;
	}

	if (fparam.DoModal() == IDOK)
	{
		//CIMAX = fparam.m_Top;
		//CIMIN = fparam.m_Bottom;
		//CRMIN = fparam.m_Left;
		//CRMAX = fparam.m_Right;

		dMagnification = fparam.m_Magnification;
		CRMID = fparam.m_X_Mid;
		CIMID = fparam.m_Y_Mid;

		//CIMAX_JUL = fparam.m_Top;
		//CIMIN_JUL = fparam.m_Bottom;
		//CRMIN_JUL = fparam.m_Left;
		//CRMAX_JUL = fparam.m_Right;
				
		NMAX  = fparam.m_Iterations;
		//dMIN  = fparam.m_dMIN;
		dBailout = (int) fparam.m_Bailout;

		dUpper = fparam.m_Upper;
		dLower = fparam.m_Lower;	
		
		//cn.set_real(rorder_r);
		//cn.set_imag(rorder_i);

		dBay100  = fparam.m_BayFact1;
		dBay1000 = fparam.m_BayFact2;
		//nFF      = fparam.m_FilterFactor;
		dStrands = fparam.m_Strands;

		if (jul == 1)
		{
			cx = fparam.m_Julia_X;
			cy = fparam.m_Julia_Y;
		}
		else
		{
			if (fparam.m_Julia_X || fparam.m_Julia_Y)
			{
				CRMID = cx = fparam.m_Julia_X;
				CIMID = cy = fparam.m_Julia_Y;

				CRMIN_NEW = cx - 1;	//	-2.0;		// left
				CIMIN_NEW = cy - 1;	//	-1.2;   // top
				CRMAX_NEW = cx + 1;	//	1.0;    // right
				CIMAX_NEW = cy + 1;	//	1.2;    // bottom
				
				//jul = 1;
				//jul_save = 0;

				OnViewJulia();

				return;
			}
			else
			{	
				cx = 0;
				cy = 0;
			}
			
		}

		bDraw = TRUE;
		bLaunch = FALSE;
		bInitialized = FALSE;
	}	
}

void CTierazonView::OnDrawAbort() 
{
	bAbort = TRUE;
}

void CTierazonView::OnUpdateDrawAbort(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(bDraw);	
}

long CTierazonView::OnApply_ShiftView(UINT wParam, LONG lParam)
{
	if (dim.cx > 1024 || dim.cy > 1024)
		return 0L;
	
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (wParam == ID_SHIFTCLOSE)
	{
		bGradient = FALSE;
		m_pGradView->DestroyWindow();
	}	
	else
	{		
		nRed = 
			m_pGradView->GetDlgItemInt(IDC_INC_RED);
		nGrn = 
			m_pGradView->GetDlgItemInt(IDC_INC_GREEN);
		nBlu = 
			m_pGradView->GetDlgItemInt(IDC_INC_BLUE);

		nRedStart = 
			m_pGradView->GetDlgItemInt(IDC_START_RED);
		nGrnStart = 
			m_pGradView->GetDlgItemInt(IDC_START_GREEN);
		nBluStart = 
			m_pGradView->GetDlgItemInt(IDC_START_BLUE);

		if (wParam == ID_SHIFTREVERSE && bForward == TRUE)
		{			
			bRedStart ^= TRUE;
			bGrnStart ^= TRUE;
			bBluStart ^= TRUE;

			for (i=0; i<dim.cx*dim.cy; i++)
			{
				bRed[i] ^= TRUE;
				bGrn[i] ^= TRUE;
				bBlu[i] ^= TRUE;
			}
			bForward = FALSE;
		}
		else
		if (wParam == ID_SHIFTFORWARD && bForward == FALSE)
		{			
			bRedStart ^= TRUE;
			bGrnStart ^= TRUE;
			bBluStart ^= TRUE;

			for (i=0; i<dim.cx*dim.cy; i++)
			{
				bRed[i] ^= TRUE;
				bGrn[i] ^= TRUE;
				bBlu[i] ^= TRUE;
			}
			bForward = TRUE;						
		}		
		
		if (bForward)
			m_pGradView->SetDlgItemText(IDC_STATUS, "Forward");
		else
			m_pGradView->SetDlgItemText(IDC_STATUS, "Reverse");

		UpdateData(TRUE);

		if ( wParam == ID_SHIFTFORWARD || wParam == ID_SHIFTREVERSE )
			Shift_Step();
		else
			Apply_Color();
	}
	return 0L;
}

void CTierazonView::Apply_Color() 
{
	if (dim.cx > 1024 || dim.cy > 1024)
		return;
	
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);			

//	if (nFilter)
//	{
//		bLaunch = FALSE;
//		bDraw   = TRUE;	
//	}
//	else
	{
		if (!pDoc->m_dib.ApplyDibColors(nRed, nGrn, nBlu, nRedStart, 
																nGrnStart, nBluStart,
																iIter_Data, rIter_Data, gIter_Data, bIter_Data,
																nColorOrder, nColorMethod))
			AfxMessageBox("Color shift error");
	}

	if (m_pGradView->GetSafeHwnd() != 0)
	{		
		m_pGradView->SetDlgItemInt(IDC_START_RED, nRedStart);
		m_pGradView->SetDlgItemInt(IDC_START_GREEN, nGrnStart);
		m_pGradView->SetDlgItemInt(IDC_START_BLUE, nBluStart);
		m_pGradView->UpdateData(TRUE);
		m_pGradView->ScrollBarInit();
	}

	Invalidate(FALSE);
}

void CTierazonView::Shift_Step() 
{
	if (dim.cx > 1024 || dim.cy > 1024)
		return;
	
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Apply color shift algorithm
	
	if (bRedStart)
	{
		if (nRedStart + nRed <= 255)
		{			
			nRedStart	+= nRed;
		}
		else
		{						
			nRedStart	-= nRed;
			bRedStart = FALSE;
		}
	}
	else
	{
		if (nRedStart - nRed >= 0)
		{			
			nRedStart -= nRed;
		}
		else
		{			
			nRedStart += nRed;
			bRedStart = TRUE;
		}			
	}
		
	if (bGrnStart)
	{
		if (nGrnStart + nGrn <= 255)
		{			
			nGrnStart	+= nGrn;
		}
		else
		{			
			nGrnStart	-= nGrn;
			bGrnStart = FALSE;
		}
	}
	else
	{
		if (nGrnStart - nGrn >= 0)
		{			
			nGrnStart -= nGrn;
		}
		else
		{			
			nGrnStart += nGrn;
			bGrnStart = TRUE;
		}			
	}

	if (bBluStart)
	{
		if (nBluStart + nBlu <= 255)
		{			
			nBluStart	+= nBlu;
		}
		else
		{			
			nBluStart	-= nBlu;
			bBluStart = FALSE;
		}
	}
	else
	{
		if (nBluStart - nBlu >= 0)
		{			
			nBluStart -= nBlu;
		}
		else
		{			
			nBluStart += nBlu;
			bBluStart = TRUE;
		}			
	}
			
	if (!pDoc->m_dib.ApplyDibColors(nRed, nGrn, nBlu, nRedStart, 
														nGrnStart, nBluStart,
														iIter_Data, rIter_Data, gIter_Data, bIter_Data,
														nColorOrder, nColorMethod))
		AfxMessageBox("Color shift error");

	if (m_pGradView->GetSafeHwnd() != 0)
	{		
		m_pGradView->SetDlgItemInt(IDC_START_RED, nRedStart);
		m_pGradView->SetDlgItemInt(IDC_START_GREEN, nGrnStart);
		m_pGradView->SetDlgItemInt(IDC_START_BLUE, nBluStart);
		m_pGradView->UpdateData(TRUE);	
		m_pGradView->ScrollBarInit();
	}

	Invalidate(FALSE);
}


void CTierazonView::OnShiftStart() 
{
	if (dim.cx > 1024 || dim.cy > 1024)
		return;

	if (!bDraw && uTimer1 == NULL)
	{
		uTimer1 = 1;
		bGlobalDraw = TRUE;
		m_pGradView->m_Cycle_Button.SetState(TRUE);
	}
	else
	{
		uTimer1 = 0;
		if (!bDraw)
			bGlobalDraw = FALSE;

		if (m_pGradView->GetSafeHwnd() != 0)
		{		
			m_pGradView->m_Cycle_Button.SetState(FALSE);
			m_pGradView->SetDlgItemInt(IDC_START_RED, nRedStart);
			m_pGradView->SetDlgItemInt(IDC_START_GREEN, nGrnStart);
			m_pGradView->SetDlgItemInt(IDC_START_BLUE, nBluStart);

			if (bForward)
				m_pGradView->SetDlgItemText(IDC_STATUS, "Forward");
			else
				m_pGradView->SetDlgItemText(IDC_STATUS, "Reverse");

			m_pGradView->UpdateData(TRUE);
			m_pGradView->ScrollBarInit();
		}
	}	
}

void CTierazonView::OnUpdateShiftStart(CCmdUI* pCmdUI) 
{
	if (uTimer1 == NULL)
		pCmdUI->SetCheck(FALSE);
	else
		pCmdUI->SetCheck(TRUE);	

	pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnImageColorparameters() 
{
	if (m_pGradView->GetSafeHwnd() == 0)
	{
		// Create the non-modal dialog
		bGradient = TRUE;

		m_pGradView->Create();

		// m_pGradView->SetWindowText(ActiveTitle);
		m_pGradView->SetDlgItemInt(IDC_START_RED, nRedStart);
		m_pGradView->SetDlgItemInt(IDC_START_GREEN, nGrnStart);
		m_pGradView->SetDlgItemInt(IDC_START_BLUE, nBluStart);

		m_pGradView->SetDlgItemInt(IDC_INC_RED, nRed);
		m_pGradView->SetDlgItemInt(IDC_INC_GREEN, nGrn);
		m_pGradView->SetDlgItemInt(IDC_INC_BLUE, nBlu);

		//m_pGradView->SetDlgItemInt(IDC_MIN, min);
		//m_pGradView->SetDlgItemInt(IDC_MAX, max);

		m_pGradView->ScrollBarInit();
				
		if (bForward)
			m_pGradView->SetDlgItemText(IDC_STATUS, "Forward");
		else
			m_pGradView->SetDlgItemText(IDC_STATUS, "Reverse");
	}	
	else
	{
		bGradient = FALSE;
		m_pGradView->DestroyWindow();
	}		
}

void CTierazonView::OnUpdateImageColorparameters(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bGradient);	
	pCmdUI->Enable(bInitialized);
}

long CTierazonView::OnApply_GradView(UINT wParam, LONG lParam)
{
	if (dim.cx > 1024 || dim.cy > 1024)
		return 0L;
	
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (wParam == ID_DLGCLOSE)
	{
		bGradient = FALSE;
		m_pGradView->DestroyWindow();
	}	
	else
	{		
		m_pGradView->UpdateData(TRUE);

		nRedStart = m_pGradView->GetDlgItemInt(IDC_START_RED);
		nGrnStart = m_pGradView->GetDlgItemInt(IDC_START_GREEN);
		nBluStart = m_pGradView->GetDlgItemInt(IDC_START_BLUE);

		nRed  = m_pGradView->GetDlgItemInt(IDC_INC_RED);
		nGrn  = m_pGradView->GetDlgItemInt(IDC_INC_GREEN);
		nBlu  = m_pGradView->GetDlgItemInt(IDC_INC_BLUE);

		//min	  = m_pGradView->GetDlgItemInt(IDC_MIN);
		//max 	= m_pGradView->GetDlgItemInt(IDC_MAX);
		
		if (bForward)
			m_pGradView->SetDlgItemText(IDC_STATUS, "Forward");
		else
			m_pGradView->SetDlgItemText(IDC_STATUS, "Reverse");

		if (!pDoc->m_dib.ApplyDibColors(nRed, nGrn, nBlu, nRedStart, 
																nGrnStart, nBluStart,
																iIter_Data, rIter_Data, gIter_Data, bIter_Data,
																nColorOrder, nColorMethod))
			AfxMessageBox("Color shift error");

		Invalidate(FALSE);
	}
	return 0L;
}

void CTierazonView::OnImageAspectratio() 
{
	bGenesisMode ^= TRUE;	
}

void CTierazonView::OnUpdateImageAspectratio(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bGenesisMode);	
}

void CTierazonView::OnImageClear() 
{
	Clearselection(TRUE);	
}

void CTierazonView::Clearselection(BOOL bValid)
{
	// Get Pointer to Document
	CTierazonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRMIN_NEW = 0;
	CIMIN_NEW = 0;
	CRMAX_NEW = 0;
	CIMAX_NEW = 0;

	CRMID = ((CRMAX - CRMIN) / 2.0) + CRMIN;
	CIMID	= ((CIMAX - CIMIN) / 2.0) + CIMIN;

	pDoc->m_tracker.m_rect.SetRectEmpty();	
	bTracker = FALSE;
	
	if (!bDraw) Invalidate(bValid);
}

void CTierazonView::OnViewZeroinit() 
{
	bZeroInit ^= 1;	
}

void CTierazonView::OnUpdateViewZeroinit(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(bZeroInit);	
}

void CTierazonView::OnViewOrient() 
{
	COrient co;

	co.m_Real = cOrient.real();
	co.m_Imag = cOrient.imag();

	if (co.DoModal() == IDOK)
	{
		cOrient.set_real(co.m_Real);
		cOrient.set_imag(co.m_Imag);
		bZeroInit = TRUE;

		bDraw = TRUE;
		bLaunch = FALSE;
	}	
}

