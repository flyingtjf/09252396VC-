#include "stdafx.h"
#include "ColorEdit.h"
#include "RGB.h"
#include ".\coloredit.h"

CColorEdit::CColorEdit()
{
	m_bReadOnly = false;
}

CColorEdit::~CColorEdit()
{
}

BEGIN_MESSAGE_MAP(CColorEdit, CEdit)
	//{{AFX_MSG_MAP(CColorEdit)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

BOOL CColorEdit::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
        if (message != WM_CTLCOLOREDIT )
        {
                 return CEdit::OnChildNotify(message,wParam,lParam,pLResult);
        }
        HDC hdcChild = (HDC)wParam;
        if( m_bOverControl )
        {
                SetTextColor(hdcChild, m_crHotFg);
                SetBkColor(hdcChild, m_crHotBg);
                *pLResult = (LRESULT)(m_pHotBrush->GetSafeHandle());
        }
        else
        {
                SetTextColor(hdcChild, m_crFg);
                SetBkColor(hdcChild, m_crBg);
                *pLResult = (LRESULT)(m_pBrush->GetSafeHandle());
        }
        return TRUE;
} 	

void CColorEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
        if (!m_bOverControl)
        {
                m_bOverControl = TRUE;
                Invalidate();
                SetTimer(m_nTimerID, m_iRolloverDelay, NULL);
        }
	CEdit::OnMouseMove(nFlags, point);
}

void CColorEdit::OnTimer(UINT nIDEvent) 
{
        CPoint p(GetMessagePos());
        ScreenToClient(&p);
        CRect rect;
        GetClientRect(rect);
        if (!rect.PtInRect(p))
        {
                m_bOverControl = FALSE;
                KillTimer(m_nTimerID);
                Invalidate();
        }	
	CEdit::OnTimer(nIDEvent);
}

HBRUSH CColorEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr;
	if( !IsWindowEnabled() )
		return *m_pBrush;
	if( m_bOverControl )
        {
                pDC->SetTextColor(m_crHotFg);
                pDC->SetBkColor(m_crHotBg);
		hbr = CEdit::OnCtlColor(pDC, pWnd, nCtlColor);
                hbr = *m_pHotBrush;
        }
        else
        {
                pDC->SetTextColor(m_crFg);
                pDC->SetBkColor(m_crBg);
		hbr = CEdit::OnCtlColor(pDC, pWnd, nCtlColor);
                hbr = *m_pBrush;
        }


	return hbr;
}

void CColorEdit::OnPaint() 
{
	if( !IsWindowEnabled() )
	{
		CPaintDC dc(this);
		CString m_Text;
		GetWindowText(m_Text);
		m_pBrush->DeleteObject();
		m_pBrush->CreateSolidBrush(m_crDisabledBg);
		CDC* pDC = GetDC();
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_crDisabledBg);
		pDC->SelectObject(m_pBrush);
		pDC->SelectObject(GetFont());
		CRect rc;
		GetClientRect(&rc);
		ScreenToClient(&rc);
		pDC->Rectangle(0, 0, rc.Width(), rc.Height());
		pDC->SetTextColor(m_crDisabledFg);
		pDC->TextOut(2, 2, m_Text);
	}
	else
		CEdit::OnPaint();
}



BOOL CColorEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN)
	{
		if(m_bReadOnly)
			return TRUE;//������������β�����
	}
	return CEdit::PreTranslateMessage(pMsg);
}

void CColorEdit::SetReadOnly(const bool bFlag)
{
	m_bReadOnly = bFlag;
}

void CColorEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bReadOnly)
	{
		return;
	}
	else
		CEdit::OnRButtonDown(nFlags, point);
	
}
