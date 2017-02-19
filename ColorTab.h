////////////////////////////////////////////////////////////////
// MSDN Magazine -- December 2004
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual Studio .NET 2003 on Windows XP. Tab size=3.
//
#ifndef _COLORTABCTRL
#define _COLORTABCTRL
class CColorTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CColorTabCtrl)
public:
	CColorTabCtrl();
	virtual ~CColorTabCtrl();

	BOOL SubclassDlgItem(UINT nID, CWnd* pParent);	// non-virtual override
	void SetColors(COLORREF bg, COLORREF fg);

protected:
	// bg/fg colors
	COLORREF m_clrBackground;
	COLORREF m_clrForeground;

	// MFC overrides
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	DECLARE_MESSAGE_MAP()
};

class CColorPropertyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CColorPropertyPage)
public:
	CColorPropertyPage(UINT nID, COLORREF bg = GetSysColor(COLOR_3DFACE));
	virtual ~CColorPropertyPage();

	void SetBGColor(COLORREF bg);

protected:
	// bg colors
	COLORREF m_clrBackground;

	// MFC overrides
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()
};

#endif