#pragma once


// CProgStatusBar

class CProgStatusBar : public CStatusBar
{
	DECLARE_DYNAMIC(CProgStatusBar)

public:
	CProgStatusBar();
	virtual ~CProgStatusBar();
	CProgressCtrl m_wndProgBar;
	CProgressCtrl& GetProgressCtrl() 
	{
		return m_wndProgBar;
	}
	void OnProgress(UINT pct);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


