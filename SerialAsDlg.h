// SerialAsDlg.h : header file
//

#if !defined(AFX_SERIALASDLG_H__2CBAB726_8D2A_4221_ABB0_AFD6E7925D33__INCLUDED_)
#define AFX_SERIALASDLG_H__2CBAB726_8D2A_4221_ABB0_AFD6E7925D33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSerialAsDlg dialog
#include "MyRichEditCtrl.h"

#include "ConfigPort.h"
#include "SerialPort.h"
#include "ProgStatusBar.h"
#include <afxmt.h>
#include <deque>
#include "FilePro.h"
#include "SwitchStatic.h"

#define WM_RECEIVE WM_USER+101
#define WM_SEND WM_USER+102
using namespace std;
class CSerialAsDlg : public CDialog
{
// Construction
public:
	CSerialAsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSerialAsDlg)
	enum { IDD = IDD_SERIALAS_DIALOG };
	CMacButton	m_btHelp;
	CSwitchStatic	m_staticNail;
	CStatic	m_staticStrPeriod;
	CStatic	m_staticStrMS;
	CEdit	m_editSavefileName;
	CMacButton	m_btClearRevData;
	CButton	m_checkHEXSend;
	CButton	m_checkAutoSend;
	CMacButton	m_btSaveFile;
	CMacButton	m_btConfigPort;
	CMacButton	m_btOpenPort;
	CMacButton	m_btClosePort;
	CMacButton	m_btChangeSaveFilePath;
	CMacButton	m_btCancel;
	CEdit	m_editSendCount;
	CMacButton	m_btClearRevCount;
	CMacButton	m_btClearSendCount;
	CMacButton	m_btClearSendData;
	CEdit	m_editSendFilePath;
	CMacButton	m_btStartSendFile;
	CMacButton	m_btSelectSendFile;
	CEdit	m_editSendPeriod;
	CMacButton	m_btManualSend;
	CMyRichEditCtrl	m_Send;
	CMyRichEdit	m_Rev;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialAsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CProgStatusBar m_StatusBar;
	// Generated message map functions
	//{{AFX_MSG(CSerialAsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnportconfig();
	afx_msg void OnBtnopenport();
	afx_msg void OnBtncloseport();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelectsendfile();
	virtual void OnCancel();
	afx_msg void OnBtnclearrevcount();
	afx_msg void OnBtnclearsendcount();
	afx_msg void OnClearrevdata();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCheckhexdisplay();
	afx_msg void OnStartsendfile();
	afx_msg void OnCheckautosend();
	afx_msg void OnManualsend();
	afx_msg void OnCheckautoclear();
	afx_msg void OnClearsenddata();
	afx_msg void OnCheckhexsend();
	afx_msg void OnBtnsavefile();
	afx_msg void OnBtnchangesavefilepath();
	afx_msg void OnChangeSavefilename();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnStaticNail();
	afx_msg void OnMyhelp();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnReceive(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSend(WPARAM wParam,LPARAM lParam);
private:
	CConfigPort m_ConfigPort;
	CSerialPort m_Port;
	void EnableCtrl(BOOL bFlag);
	void UpdateStatusBar();
	void UpdateStatusBarInfo(CStatusBar &statusBar,
	int nIndex,LPCTSTR lpszNewText);
	static	UINT RevThreadProc(LPVOID pParam);
	static UINT SendFileThreadProc(LPVOID pParam);
	static UINT SendThreadProc(LPVOID pParam);	
	DWORD m_dwRevCount;
	DWORD m_dwSendCount;
	CString m_sRev;
	BOOL m_bRevUpdate;
	BOOL m_bHexDisplay;
	BOOL m_bAutoSend;
	BOOL m_bAutoClear;
	CString  m_sSaveDir;
	CString m_OldSaveFileName;
	DWORD m_dwSendFileLen;
	static BYTE HEXToDec(BYTE value);
	void WriteMyFile(CString filename);
	virtual void OnOK();
	DWORD GetByteRate();
	BOOL m_bSendFlag;
	HANDLE m_hEventSendFile;
	BOOL m_bCancelSend;
	CBrush m_bkBrush;
	//保存原始窗口信息
	CRect m_OldRect;
	HICON m_hIconClosed;
	HICON m_hIconOpened;
	BOOL m_bHEXSend;
	BOOL m_SendError;
	static DWORD StrToHex(CString str,BYTE *p,DWORD len);
	CCriticalSection m_bRevCS;
	HANDLE m_hCom;
	BOOL m_bRun;
	deque<BYTE>m_dequeRevData;
	HANDLE m_hSendEvent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALASDLG_H__2CBAB726_8D2A_4221_ABB0_AFD6E7925D33__INCLUDED_)
