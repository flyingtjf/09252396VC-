// MyRichEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MyRichEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRichEdit

CMyRichEdit::CMyRichEdit()
{
}

CMyRichEdit::~CMyRichEdit()
{
}


BEGIN_MESSAGE_MAP(CMyRichEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CMyRichEdit)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRichEdit message handlers

void CMyRichEdit::AddText(CString &strTextIn, COLORREF &crNewColor)
{
	int iTotalTextLength = GetWindowTextLength();
	SetSel(iTotalTextLength, iTotalTextLength);
	ReplaceSel((LPCTSTR)strTextIn);
	int iStartPos = iTotalTextLength;

	CHARFORMAT cf;
	cf.cbSize		= sizeof(CHARFORMAT);
	cf.dwMask		= CFM_COLOR | CFM_UNDERLINE | CFM_BOLD;
	cf.dwEffects	= (unsigned long)~( CFE_AUTOCOLOR | CFE_UNDERLINE | CFE_BOLD);
	cf.crTextColor	= crNewColor;
	SetSelectionCharFormat(cf);

	int iEndPos = GetWindowTextLength();
	SetSel(iStartPos, iEndPos);
	SetSelectionCharFormat(cf);
	HideSelection(TRUE, FALSE);

	static int last = GetLineCount();
	LineScroll(GetLineCount()-last);
	last = GetLineCount();
}
