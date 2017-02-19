////////////////////////////////////////////////////////////////
// MSDN Magazine -- December 2004
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual Studio .NET 2003 on Windows XP. Tab size=3.
//
// CColorTabCtrl implements a CTabCtrl with colored tabs.

#include "StdAfx.h"
#include "ColorTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CColorTabCtrl, CTabCtrl)
BEGIN_MESSAGE_MAP(CColorTabCtrl, CTabCtrl)
END_MESSAGE_MAP()

CColorTabCtrl::CColorTabCtrl()
{
	SetColors(GetSysColor(COLOR_3DFACE), GetSysColor(COLOR_BTNTEXT));
}

CColorTabCtrl::~CColorTabCtrl()
{
}

//////////////////
// Set bg/gf colors
//
void CColorTabCtrl::SetColors(COLORREF bg, COLORREF fg)
{
	m_clrBackground = bg;
	m_clrForeground = fg;
}

//////////////////
// Subclass the tab control: also make ownder-draw
// 
CColorTabCtrl::SubclassDlgItem(UINT nID, CWnd* pParent)
{
	if (!CTabCtrl::SubclassDlgItem(nID, pParent))
		return FALSE;
	ModifyStyle(0, TCS_OWNERDRAWFIXED);
	return TRUE;
}

//////////////////
// Draw the tab: use bg/fg colors.
//
void CColorTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	DRAWITEMSTRUCT& ds = *lpDrawItemStruct;
	
	int iItem = ds.itemID;

	// Get tab item info
	char text[128];
	TCITEM tci;
	tci.mask = TCIF_TEXT;
	tci.pszText = text;
	tci.cchTextMax = sizeof(text);
	GetItem(iItem, &tci);

	// use draw item DC
	CDC dc;
	dc.Attach(ds.hDC);

	// calculate text rectangle and color
	CRect rc = ds.rcItem;
	rc += CPoint(1,4);						 // ?? by trial and error

	dc.FillSolidRect(rc, m_clrBackground);
	dc.SetBkColor(m_clrBackground);
	dc.SetTextColor(m_clrForeground);
	dc.DrawText(text, &rc, DT_CENTER|DT_VCENTER);

	dc.Detach();
}

IMPLEMENT_DYNAMIC(CColorPropertyPage, CPropertyPage)
BEGIN_MESSAGE_MAP(CColorPropertyPage, CPropertyPage)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CColorPropertyPage::CColorPropertyPage(UINT nID, COLORREF bg) : CPropertyPage(nID)
{
	SetBGColor(bg);
}

CColorPropertyPage::~CColorPropertyPage()
{
	
}

void CColorPropertyPage::SetBGColor(COLORREF bg)
{
	m_clrBackground = bg;
}

//////////////////
// Handle WM_ERASEBKGND: fill bg with bg color
//
BOOL CColorPropertyPage::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(rc, m_clrBackground);
	return TRUE;
}

