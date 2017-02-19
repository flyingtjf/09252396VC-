#if !defined(AFX_HELPSHEET_H__37EEDC79_E68B_40B3_B30A_393A8E0D9AD2__INCLUDED_)
#define AFX_HELPSHEET_H__37EEDC79_E68B_40B3_B30A_393A8E0D9AD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HELPSHEET.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHELPSHEET dialog

class CHELPSHEET : public CDialog
{
// Construction
public:
	CHELPSHEET(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHELPSHEET)
	enum { IDD = IDD_DLGHELP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHELPSHEET)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHELPSHEET)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPSHEET_H__37EEDC79_E68B_40B3_B30A_393A8E0D9AD2__INCLUDED_)
