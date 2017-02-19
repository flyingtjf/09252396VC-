// SwitchStatic.cpp : implementation file
//

#include "stdafx.h" 
#include "Resource.h"
#include "SwitchStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitchStatic

CSwitchStatic::CSwitchStatic()
{
	bSwitchOn = FALSE;
	nSwitchStyle = STYLE_ONE;
	m_SystemMetric = STYLE_ONE;
}

CSwitchStatic::~CSwitchStatic()
{
}


BEGIN_MESSAGE_MAP(CSwitchStatic, CStatic)
	//{{AFX_MSG_MAP(CSwitchStatic)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitchStatic message handlers

void CSwitchStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(&rect); 
	CDC *mdc=new CDC;
	mdc->CreateCompatibleDC(&dc);
	HBITMAP hbitmap; 

	if(!this->bSwitchOn)
		hbitmap=::LoadBitmap(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_NAILOFF));
	else
		hbitmap=::LoadBitmap(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_NAILON));
/////////////
//	CSize size;
//	int rvaluse = ::GetBitmapDimensionEx(hbitmap,&size);
//////////////
	mdc->SelectObject(hbitmap); 
	dc.BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),mdc,0,0,SRCCOPY);
	delete mdc;
	::DeleteObject(hbitmap);
	// Do not call CStatic::OnPaint() for painting messages
}

void CSwitchStatic::SetSwitchState(BOOL bOn)
{
	this->bSwitchOn = bOn;
	this->Invalidate();
}

BOOL CSwitchStatic::GetSwitchState()
{
	return this->bSwitchOn ;
}

BOOL CSwitchStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	::SetCursor(AfxGetApp()->LoadStandardCursor (IDC_ARROW));
	return TRUE;
}

void CSwitchStatic::SetSwitchStyle(tagSYSTEMMETRIC nStyle)
{
	this->m_SystemMetric = nStyle;
}

tagSYSTEMMETRIC CSwitchStatic::GetSwitchStyle()
{
	return this->m_SystemMetric;
}

void CSwitchStatic::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	long style = GetWindowLong(m_hWnd,GWL_STYLE);
	SetWindowLong(m_hWnd,GWL_STYLE,style|SS_NOTIFY);

/*	CRect rect;
	GetWindowRect(&rect);
	rect.right = rect.left + 15;
	rect.bottom = rect.top + 15;
	ScreenToClient(&rect);
	MoveWindow(rect,false);*/
	CStatic::PreSubclassWindow();
}

void CSwitchStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetSwitchState(!GetSwitchState());
	CStatic::OnLButtonDown(nFlags, point);
}

BOOL CSwitchStatic::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	// TODO: Add your specialized code here and/or call the base class
//	::PostMessage(this->GetParent()->m_hWnd,WM_NOTIFY,wParam,lParam);
	return CStatic::OnChildNotify(message, wParam, lParam, pLResult);
}
