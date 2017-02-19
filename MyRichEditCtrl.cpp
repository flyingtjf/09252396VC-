// MyRichEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyRichEditCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRichEditCtrl
#define ID_RICH_UNDO                    2001
#define ID_RICH_CUT                     2002
#define ID_RICH_COPY                    2003
#define ID_RICH_PASTE                   2004
#define ID_RICH_CLEAR                   2005
#define ID_RICH_SELECTALL               2006
#define ID_RICH_SETFONT                 2007

CMyRichEditCtrl::CMyRichEditCtrl()
{
}

CMyRichEditCtrl::~CMyRichEditCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyRichEditCtrl, CMyRichEdit)
	//{{AFX_MSG_MAP(CMyRichEditCtrl)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_RICH_COPY, OnCopy)
	ON_COMMAND(ID_RICH_CUT, OnCut)
	ON_COMMAND(ID_RICH_PASTE, OnPaste)
	ON_COMMAND(ID_RICH_SELECTALL, OnSelectall)
	ON_COMMAND(ID_RICH_UNDO, OnUndo)
	ON_COMMAND(ID_RICH_CLEAR, OnClear)
	ON_COMMAND(ID_RICH_SETFONT, OnSelectfont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRichEditCtrl message handlers

void CMyRichEditCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//设置为焦点
	SetFocus();
	//创建一个弹出式菜单
	CMenu popmenu;
	popmenu.CreatePopupMenu();
	//添加菜单项目
	popmenu.AppendMenu(0, ID_RICH_UNDO, _T("&Undo"));
	popmenu.AppendMenu(0, MF_SEPARATOR);
	popmenu.AppendMenu(0, ID_RICH_CUT, _T("&Cut"));
	popmenu.AppendMenu(0, ID_RICH_COPY, _T("C&opy"));
	popmenu.AppendMenu(0, ID_RICH_PASTE, _T("&Paste"));
	popmenu.AppendMenu(0, ID_RICH_CLEAR, _T("C&lear"));
	popmenu.AppendMenu(0, MF_SEPARATOR);
	popmenu.AppendMenu(0, ID_RICH_SELECTALL, _T("Select &All"));
	popmenu.AppendMenu(0, MF_SEPARATOR);
	popmenu.AppendMenu(0, ID_RICH_SETFONT, _T("Select &Font"));

	//初始化菜单项
	UINT nUndo=(CanUndo() ? 0 : MF_GRAYED );
	popmenu.EnableMenuItem(ID_RICH_UNDO, MF_BYCOMMAND|nUndo);

	UINT nSel=((GetSelectionType()!=SEL_EMPTY) ? 0 : MF_GRAYED) ;
	popmenu.EnableMenuItem(ID_RICH_CUT, MF_BYCOMMAND|nSel);
	popmenu.EnableMenuItem(ID_RICH_COPY, MF_BYCOMMAND|nSel);
	popmenu.EnableMenuItem(ID_RICH_CLEAR, MF_BYCOMMAND|nSel);
	
	UINT nPaste=(CanPaste() ? 0 : MF_GRAYED) ;
	popmenu.EnableMenuItem(ID_RICH_PASTE, MF_BYCOMMAND|nPaste);

	//显示菜单
	CPoint pt;
	GetCursorPos(&pt);
	popmenu.TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
	popmenu.DestroyMenu();
	CMyRichEdit::OnRButtonDown(nFlags, point);
}

void CMyRichEditCtrl::OnSelectfont() 
{
	// TODO: Add your command handler code here
	static BOOL bFlag = TRUE;
	static CHARFORMAT cf;
	static LOGFONT lf;
	if(bFlag)
	{
		memset(&lf, 0, sizeof(LOGFONT));
		memset(&cf, 0, sizeof(CHARFORMAT));
		GetDefaultCharFormat(cf);
		bFlag = FALSE;
	}
	//得到相关字体属性
	BOOL bIsBold = cf.dwEffects & CFE_BOLD;
	BOOL bIsItalic = cf.dwEffects & CFE_ITALIC;
	BOOL bIsUnderline = cf.dwEffects & CFE_UNDERLINE;
	BOOL bIsStrickout = cf.dwEffects & CFE_STRIKEOUT;
	//设置属性
	lf.lfCharSet = cf.bCharSet;
	lf.lfHeight = cf.yHeight/15;
	lf.lfPitchAndFamily = cf.bPitchAndFamily;
	lf.lfItalic = bIsItalic;
	lf.lfWeight = (bIsBold ? FW_BOLD : FW_NORMAL);
	lf.lfUnderline = bIsUnderline;
	lf.lfStrikeOut = bIsStrickout;
	_stprintf(lf.lfFaceName, _T("%s"),cf.szFaceName);
	
	CFontDialog dlg(&lf);
	dlg.m_cf.rgbColors = cf.crTextColor;
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCharFormat(cf);//获得所选字体的属性
		SetSel(0,-1);
		SetSelectionCharFormat(cf);	//为选定的内容设定所选字体
		SetWordCharFormat(cf);	//为将要输入的内容设定字体
	}
}


