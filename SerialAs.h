// SerialAs.h : main header file for the SERIALAS application
//

#if !defined(AFX_SERIALAS_H__97CA55C1_70D3_437F_A184_DA39CE281BEC__INCLUDED_)
#define AFX_SERIALAS_H__97CA55C1_70D3_437F_A184_DA39CE281BEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSerialAsApp:
// See SerialAs.cpp for the implementation of this class
//

class CSerialAsApp : public CWinApp
{
public:
	CSerialAsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialAsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSerialAsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALAS_H__97CA55C1_70D3_437F_A184_DA39CE281BEC__INCLUDED_)
