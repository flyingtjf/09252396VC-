#if !defined(AFX_CONFIGPORT_H__A365786A_D151_4A5B_BF20_ED80F952607D__INCLUDED_)
#define AFX_CONFIGPORT_H__A365786A_D151_4A5B_BF20_ED80F952607D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigPort.h : header file
//
#include "RGB.h"
#include "ColorComboBox.h"
#include "MacButtons.h"
#include "Ini.h"
#include "FilePro.h"
/////////////////////////////////////////////////////////////////////////////
// CConfigPort dialog

static const DWORD BAUDRATE[] = 
{CBR_110,CBR_300,CBR_600,CBR_1200,CBR_2400,CBR_4800,
CBR_9600,CBR_14400,CBR_19200,CBR_38400,CBR_56000 ,
CBR_57600,CBR_115200 ,CBR_128000 ,CBR_256000 
};

class CConfigPort : public CDialog
{
// Construction
public:
	CConfigPort(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CConfigPort)
	enum { IDD = IDD_CONFIGPORTDLG };
	CMacButton	m_SavePortConfig;
	CMacButton	m_OKandOpen;
	CMacButton	m_CANCEL;
	CMacButton	m_OK;
	CColorComboBox	m_BaudRate;
	CButton	m_CheckExistPort;
	CColorComboBox	m_DataBits;
	CColorComboBox	m_Parity;
	CColorComboBox	m_Port;
	CColorComboBox	m_StopBits;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigPort)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	CIni m_ini;
protected:
	CBrush m_brHollow;
	CString m_sPort;
	DWORD m_dwBaudRate;
	CString m_sBaudRate;
	BYTE m_byDataBits;
	CString m_sDataBits;
	BYTE m_byParity;
	CString m_sParity;
	BYTE m_byStopBits;
	CString m_sStopBits;
	CString m_sError;
	BOOL m_bCheckExistPort;
	WORD GetAllPortList(CString &sList);
	// Generated message map functions
	//{{AFX_MSG(CConfigPort)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckexistport();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnok();
	afx_msg void OnSaveportconfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bOpen;
	BOOL SetParam(CString sPort,DWORD dwBaudRate,BYTE byDataBits,BYTE byParity,BYTE byStopBits);
	BOOL GetParam(CString &sPort,DWORD &dwBaudRate,BYTE &byDataBits,BYTE &byParity,BYTE &byStopBits);
	BOOL GetParamString(CString &sPort,CString &sBaudRate,
		CString &sDataBits,CString &sParity,CString &sStopBits);
	CString GetError();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGPORT_H__A365786A_D151_4A5B_BF20_ED80F952607D__INCLUDED_)
