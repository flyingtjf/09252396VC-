// ProgStatusBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProgStatusBar.h"
#include ".\progstatusbar.h"
#include <afxpriv.h>

// CProgStatusBar

IMPLEMENT_DYNAMIC(CProgStatusBar, CStatusBar)
CProgStatusBar::CProgStatusBar()
{
}

CProgStatusBar::~CProgStatusBar()
{
}


BEGIN_MESSAGE_MAP(CProgStatusBar, CStatusBar)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CProgStatusBar ��Ϣ�������


void CProgStatusBar::OnSize(UINT nType, int cx, int cy)
{
	CStatusBar::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rc;								  // rectangle 
	GetItemRect(0, &rc);					  // item 0 = first pane, "ready" message
	m_wndProgBar.MoveWindow(&rc,FALSE);// move progress bar
}

int CProgStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
//	lpcs->style |= WS_CLIPCHILDREN;
	VERIFY(m_wndProgBar.Create(WS_CHILD, CRect(), this, 1));
	m_wndProgBar.SetRange(0,100);
	return 0;
}

//////////////////
// Set progress bar position. pct is an integer from 0 to 100:
//
//  0 = hide progress bar and display ready message (done);
// >0 = (assemed 0-100) set progress bar position
//
// You should call this from your main frame to update progress.
// (See Mainfrm.cpp)
//
void CProgStatusBar::OnProgress(UINT pct)
{
	CProgressCtrl& pc = m_wndProgBar;
	DWORD dwOldStyle = pc.GetStyle();
	DWORD dwNewStyle = dwOldStyle;
	if (pct>0)
		// positive progress: show prog bar
		dwNewStyle |= WS_VISIBLE;
	else
		// prog <= 0: hide prog bar
		dwNewStyle &= ~WS_VISIBLE;

	if (dwNewStyle != dwOldStyle) {
		// change state of hide/show
		SetWindowText(NULL);								// clear old text
		SetWindowLong(pc.m_hWnd, GWL_STYLE, dwNewStyle);	// change style
	}

	// set progress bar position
	pc.SetPos(pct);
	if (pct==0)
		// display MFC idle (ready) message.
		GetParent()->PostMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
}
