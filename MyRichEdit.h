#if !defined(AFX_MYRICHEDIT_H__062A5E70_CF0E_40B4_A0F1_DAEF6B0B9543__INCLUDED_)
#define AFX_MYRICHEDIT_H__062A5E70_CF0E_40B4_A0F1_DAEF6B0B9543__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyRichEdit.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CMyRichEdit window

class CMyRichEdit : public CRichEditCtrl
{
// Construction
public:
	CMyRichEdit();

// Attributes
public:

// Operations
public:
	void AddText(CString &strTextIn, COLORREF &crNewColor);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyRichEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyRichEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyRichEdit)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYRICHEDIT_H__062A5E70_CF0E_40B4_A0F1_DAEF6B0B9543__INCLUDED_)
