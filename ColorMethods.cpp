/////////////////////////////////////////////////////
// ColorMethods.cpp
/////////////////////////////////////////////////////
#include "stdafx.h"
#include "Tierazon.h"

#include "TierazonDoc.h"
#include "TierazonView.h"
#include "Convolut.h"
#include <math.h>
#include "external.h"


///////////////////////////////////////////////
///////////////////////////////////////////////

void CTierazonView::OnColour0() 
{
	nColorMethod = 0;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour0(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 0)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour01() 
{
	nColorMethod = 1;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour01(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour02() 
{
	nColorMethod = 2;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour02(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour03() 
{
	nColorMethod = 3;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour03(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 3)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour04() 
{
	nColorMethod = 4;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour04(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 4)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour05() 
{
	nColorMethod = 5;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour05(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 5)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour06() 
{
	nColorMethod = 6;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour06(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 6)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour07() 
{
	nColorMethod = 7;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour07(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 7)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour8() 
{
	nColorMethod = 8;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour8(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 8)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour9() 
{
	nColorMethod = 9;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour9(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 9)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour10() 
{
	nColorMethod = 10;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour10(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 10)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour11() 
{
	nColorMethod = 11;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour11(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 11)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour12() 
{
	nColorMethod = 12;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour12(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 12)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour13() 
{
	nColorMethod = 13;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour13(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 13)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour14() 
{
	nColorMethod = 14;
	//bColorChange = TRUE;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour14(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 14)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour15() 
{
	nColorMethod = 15;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour15(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 15)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
	//pCmdUI->Enable(bInitialized);
}

void CTierazonView::OnColour19() 
{
	/*
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
		rn = rw.m_RW1_n;
	else
		return;
	*/
	rn = 2;
	
	nColorMethod = 19;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour19(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 19)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour20() 
{
	/*
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
		rn = rw.m_RW1_n;
	else
		return;
	*/
	
	rn = 2;

	nColorMethod = 20;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour20(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 20)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour21() 
{
	/*
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
		rn = rw.m_RW1_n;
	else
		return;
	*/
	rn =2;

	nColorMethod = 21;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour21(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 21)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour22() 
{
	/*
	COneNum rw;
	rw.m_RW1_n = rn;

	if (rw.DoModal() == IDOK)
		rn = rw.m_RW1_n;
	else
		return;
	*/
	rn = 2;

	nColorMethod = 22;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour22(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 22)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour23() 
{
	nColorMethod = 23;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour23(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 23)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour24() 
{
	nColorMethod = 24;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour24(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 24)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour25() 
{
	nColorMethod = 25;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour25(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 25)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour26() 
{
	nColorMethod = 26;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour26(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 26)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour27() 
{
	nColorMethod = 27;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour27(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 27)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour28() 
{
	nColorMethod = 28;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour28(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 28)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour29() 
{
	nColorMethod = 29;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour29(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 29)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour30() 
{
	nColorMethod = 30;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour30(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 30)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour31() 
{
	nColorMethod = 31;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour31(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 31)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour32() 
{
	nColorMethod = 32;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour32(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 32)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour33() 
{
	nColorMethod = 33;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour33(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 33)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour34() 
{
	nColorMethod = 34;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour34(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 34)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour35() 
{
	nColorMethod = 35;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour35(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 35)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour36() 
{
	nColorMethod = 36;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour36(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 36)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour37() 
{
	nColorMethod = 37;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour37(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 37)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour38() 
{
	nColorMethod = 38;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour38(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 38)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnColour39() 
{
	nColorMethod = 39;
	bDraw = TRUE;
	bLaunch = FALSE;
}

void CTierazonView::OnUpdateColour39(CCmdUI* pCmdUI) 
{
	if (nColorMethod == 39)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

////////////////////////////////////////
////////////////////////////////////////
