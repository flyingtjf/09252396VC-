// HELPSHEET.cpp : implementation file
//

#include "stdafx.h"
#include "serialas.h"
#include "HELPSHEET.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHELPSHEET dialog


CHELPSHEET::CHELPSHEET(CWnd* pParent /*=NULL*/)
	: CDialog(CHELPSHEET::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHELPSHEET)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHELPSHEET::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHELPSHEET)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHELPSHEET, CDialog)
	//{{AFX_MSG_MAP(CHELPSHEET)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHELPSHEET message handlers
