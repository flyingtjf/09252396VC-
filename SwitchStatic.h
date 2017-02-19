#if !defined(AFX_SWITCHSTATIC_H__9B4DB668_A212_469E_B31F_175E4FC70E59__INCLUDED_)
#define AFX_SWITCHSTATIC_H__9B4DB668_A212_469E_B31F_175E4FC70E59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SwitchStatic.h : header file
//
typedef enum tagSYSTEMMETRIC{STYLE_ONE,STYLE_TWO,STYLE_THREE,STYLE_FOUR,STYLE_FIVE,STYLE_SIX};

/////////////////////////////////////////////////////////////////////////////
// CSwitchStatic window

class CSwitchStatic : public CStatic
{
// Construction
public:
	CSwitchStatic();
	BOOL  bSwitchOn;
	tagSYSTEMMETRIC m_SystemMetric;

protected:
	UINT nSwitchStyle;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchStatic)
	public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	tagSYSTEMMETRIC GetSwitchStyle();
	void SetSwitchStyle(tagSYSTEMMETRIC nStyle);
	BOOL GetSwitchState();
	void SetSwitchState(BOOL bOn);
	virtual ~CSwitchStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSwitchStatic)
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHSTATIC_H__9B4DB668_A212_469E_B31F_175E4FC70E59__INCLUDED_)
