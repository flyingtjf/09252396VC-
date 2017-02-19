#if !defined(AFX_MYRICHEDITCTRL_H__C4DB9CEB_6D3E_473A_8855_BC7A3E99FB2C__INCLUDED_)
#define AFX_MYRICHEDITCTRL_H__C4DB9CEB_6D3E_473A_8855_BC7A3E99FB2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyRichEditCtrl.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CMyRichEditCtrl window
#include "MyRichEdit.h"
class CMyRichEditCtrl : public CMyRichEdit 
{
// Construction
public:
	CMyRichEditCtrl();
    void SelFont()
	{
		OnSelectfont();
	}
// Attributes
public:

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyRichEditCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyRichEditCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyRichEditCtrl)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCopy() { Copy(); }
	afx_msg void OnCut() { Cut(); }
	afx_msg void OnPaste() { Paste(); }
	afx_msg void OnSelectall() { SetSel(0, -1); }
	afx_msg void OnUndo() { Undo(); }
	afx_msg void OnClear() { Clear(); }
	afx_msg void OnSelectfont();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYRICHEDITCTRL_H__C4DB9CEB_6D3E_473A_8855_BC7A3E99FB2C__INCLUDED_)
