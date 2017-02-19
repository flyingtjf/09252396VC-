// SerialAsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SerialAs.h"
#include "SerialAsDlg.h"
#include <afx.h>
#include "FilePro.h"
#include <limits.h>
#include "Shlwapi.h"
#include "shlobj.h"
#include "StatLink.h"
#include "CreditStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#define	ID_PORTSTATUS 0
#define	ID_COMSTATUS  1
#define	ID_TIME       2
static const UINT BASED_CODE indicators[] =
{
	ID_PORTSTATUS,
	ID_COMSTATUS,
	ID_TIME
};

static const TIME_ID_TIME = 1;
static const TIME_ID_SEND = 2;
static const TIME_ID_REV = 3;

typedef struct _SEND
{
	BOOL bFlag;
	DOUBLE value;
}SEND;



class CAboutDlg : public CDialog
{
public:
	BOOL m_bAbout;
	CAboutDlg();
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CMacButton	m_btSwitch;
	CStaticLink	m_staticMail;
	CRichEditCtrl	m_reditHelpText;
	CMacButton	m_btOK;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
protected:
	CBrush m_bkBrush;
	//{{AFX_MSG(CAboutDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonswitch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CToolTipCtrl m_ToolTipMail ;
	CCreditStatic m_DyCredits;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	m_bAbout = TRUE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_BUTTONSWITCH, m_btSwitch);
	DDX_Control(pDX, IDC_STATIC_MAIL, m_staticMail);
	DDX_Control(pDX, IDC_RICHEDITHELP, m_reditHelpText);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDC_DYCREDITS, m_DyCredits);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTONSWITCH, OnButtonswitch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialAsDlg dialog

CSerialAsDlg::CSerialAsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialAsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSerialAsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hCom = INVALID_HANDLE_VALUE;
	m_bRun = FALSE;
	m_dwRevCount = 0;
	m_dwSendCount = 0;
	m_sRev = _T("");
	m_bRevUpdate = FALSE;
	m_bHexDisplay = FALSE;
	m_bAutoSend = FALSE;
	m_bAutoClear = FALSE;
	m_bHEXSend = FALSE;
	m_dwSendFileLen = 0;
	m_bSendFlag = FALSE;
	m_SendError = FALSE;
	m_hEventSendFile = CreateEvent( 
		NULL,         // no security attributes
		TRUE,         // manual-reset event
		FALSE,        // initial state is nosignaled
		NULL		  // object name
		);
	m_bCancelSend = TRUE;
	m_bkBrush.CreateSolidBrush(DLGBK_COLOR);
}

void CSerialAsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSerialAsDlg)
	DDX_Control(pDX, IDC_MYHELP, m_btHelp);
	DDX_Control(pDX, IDC_STATIC_NAIL, m_staticNail);
	DDX_Control(pDX, IDC_STATIC_STR_PERIOD, m_staticStrPeriod);
	DDX_Control(pDX, IDC_STATIC_STR_MS, m_staticStrMS);
	DDX_Control(pDX, IDC_SAVEFILENAME, m_editSavefileName);
	DDX_Control(pDX, IDC_CLEARREVDATA, m_btClearRevData);
	DDX_Control(pDX, IDC_CHECKHEXSEND, m_checkHEXSend);
	DDX_Control(pDX, IDC_CHECKAUTOSEND, m_checkAutoSend);
	DDX_Control(pDX, IDC_BTNSAVEFILE, m_btSaveFile);
	DDX_Control(pDX, IDC_BTNPORTCONFIG, m_btConfigPort);
	DDX_Control(pDX, IDC_BTNOPENPORT, m_btOpenPort);
	DDX_Control(pDX, IDC_BTNCLOSEPORT, m_btClosePort);
	DDX_Control(pDX, IDC_BTNCHANGESAVEFILEPATH, m_btChangeSaveFilePath);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_EDITSENDCOUNT, m_editSendCount);
	DDX_Control(pDX, IDC_BTNCLEARREVCOUNT, m_btClearRevCount);
	DDX_Control(pDX, IDC_BTNCLEARSENDCOUNT, m_btClearSendCount);
	DDX_Control(pDX, IDC_CLEARSENDDATA, m_btClearSendData);
	DDX_Control(pDX, IDC_EDITSENDFILEPATH, m_editSendFilePath);
	DDX_Control(pDX, IDC_STARTSENDFILE, m_btStartSendFile);
	DDX_Control(pDX, IDC_SELECTSENDFILE, m_btSelectSendFile);
	DDX_Control(pDX, IDC_EDITSENDPERIOD, m_editSendPeriod);
	DDX_Control(pDX, IDC_MANUALSEND, m_btManualSend);
	DDX_Control(pDX, IDC_RICHEDITSENDDATA, m_Send);
	DDX_Control(pDX, IDC_RICHEDITREVDATA, m_Rev);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSerialAsDlg, CDialog)
	//{{AFX_MSG_MAP(CSerialAsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNPORTCONFIG, OnBtnportconfig)
	ON_BN_CLICKED(IDC_BTNOPENPORT, OnBtnopenport)
	ON_BN_CLICKED(IDC_BTNCLOSEPORT, OnBtncloseport)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SELECTSENDFILE, OnSelectsendfile)
	ON_BN_CLICKED(IDC_BTNCLEARREVCOUNT, OnBtnclearrevcount)
	ON_BN_CLICKED(IDC_BTNCLEARSENDCOUNT, OnBtnclearsendcount)
	ON_BN_CLICKED(IDC_CLEARREVDATA, OnClearrevdata)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHECKHEXDISPLAY, OnCheckhexdisplay)
	ON_BN_CLICKED(IDC_STARTSENDFILE, OnStartsendfile)
	ON_BN_CLICKED(IDC_CHECKAUTOSEND, OnCheckautosend)
	ON_BN_CLICKED(IDC_MANUALSEND, OnManualsend)
	ON_BN_CLICKED(IDC_CHECKAUTOCLEAR, OnCheckautoclear)
	ON_BN_CLICKED(IDC_CLEARSENDDATA, OnClearsenddata)
	ON_BN_CLICKED(IDC_CHECKHEXSEND, OnCheckhexsend)
	ON_BN_CLICKED(IDC_BTNSAVEFILE, OnBtnsavefile)
	ON_BN_CLICKED(IDC_BTNCHANGESAVEFILEPATH, OnBtnchangesavefilepath)
	ON_EN_CHANGE(IDC_SAVEFILENAME, OnChangeSavefilename)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_STATIC_NAIL, OnStaticNail)
	ON_BN_CLICKED(IDC_MYHELP, OnMyhelp)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECEIVE,OnReceive)
	ON_MESSAGE(WM_SEND,OnSend)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialAsDlg message handlers

BOOL CSerialAsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//创建状态条

	DWORD style = WS_CHILD|WS_VISIBLE|CBRS_BOTTOM;
	style &= ~WS_THICKFRAME;
	m_StatusBar.CreateEx(this,SBT_TOOLTIPS,style, AFX_IDW_STATUS_BAR);
	m_StatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT));
	CRect rect,rect1;
	GetClientRect(&rect);
    m_staticNail.GetWindowRect(&rect1);

	m_StatusBar.SetPaneInfo(0,ID_PORTSTATUS,SBPS_NORMAL,rect.Width()*2/5-5);
	m_StatusBar.SetPaneInfo(1,ID_COMSTATUS,SBPS_STRETCH,rect.Width()*2/5-rect1.Width());
	m_StatusBar.SetPaneInfo(2,ID_TIME,SBPS_NORMAL ,rect.Width()*1/5);
	m_StatusBar.MoveWindow(rect.left+20,rect.bottom-rect1.Height(),
						   rect.Width()-rect1.Width()-5,rect1.Height(),TRUE);
	m_StatusBar.GetStatusBarCtrl().SetBkColor(DLGBK_COLOR);
	m_hIconClosed = AfxGetApp()->LoadIcon(IDI_ICONCLOSED);
	m_hIconOpened = AfxGetApp()->LoadIcon(IDI_ICONOPENED);
	m_StatusBar.GetStatusBarCtrl().SetIcon(0,m_hIconClosed);

	EnableCtrl(TRUE);
	UpdateStatusBar();

	SetTimer(TIME_ID_TIME,1000,NULL);
	GetDlgItem(IDC_EDITREVCOUNT)->SetWindowText(_T("RX:0"));
	GetDlgItem(IDC_EDITSENDCOUNT)->SetWindowText(_T("TX:0"));

	GetDlgItem(IDC_EDITSENDPERIOD)->SetWindowText(_T("1000"));
	SetDlgItemText(IDC_RICHEDITSENDDATA,_T("lxg215@hotmail.com"));

	m_hSendEvent = CreateEvent( 
		NULL,         // no security attributes
		TRUE,         // manual-reset event
		FALSE,        // initial state is nosignaled
		NULL		  // object name
		); 
	if(m_hSendEvent==NULL)
		return false;

	SetDlgItemText(IDC_SAVEFILENAME,_T("Rev.dat"));
	CString str;
	str = STR_ROOT_DIR ;
	str += _T("\\Rev.dat");
	SetDlgItemText(IDC_STATICSAVEFILEPATH,str);
	m_sSaveDir = STR_ROOT_DIR;
	m_OldSaveFileName = _T("Rev.dat") ;

	GetClientRect(&m_OldRect);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSerialAsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSerialAsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSerialAsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSerialAsDlg::OnBtnportconfig() 
{
	// TODO: Add your control notification handler code here
	if(m_ConfigPort.DoModal()==IDOK)
	{
		if(m_ConfigPort.m_bOpen)
		{
			OnBtnopenport();
		}
		UpdateStatusBar();
	}
}

UINT CSerialAsDlg::RevThreadProc(LPVOID pParam)
{
	HANDLE			h_gEvent;
	DWORD			dwBytesRead;
	OVERLAPPED		Overlapped;
	
	CSerialAsDlg *pDlg = (CSerialAsDlg*) pParam;

	BOOL bReadStatus = FALSE;
	dwBytesRead  = 0;
	memset(&Overlapped,0,sizeof(OVERLAPPED));
	h_gEvent = NULL;
	h_gEvent = CreateEvent( 
		NULL,				
		TRUE,				//手工设置事件有无信号
		FALSE,				//初始化事件为无信号状态
		NULL				
		); 

	if(h_gEvent == NULL) return 0;
	
	Overlapped.hEvent = h_gEvent;
#define BUFSIZE 1024	
	BYTE data[BUFSIZE];
	ZeroMemory(data,BUFSIZE);
	DWORD dwEvtMask=0;
	GetCommMask(pDlg->m_hCom,&dwEvtMask);
	dwEvtMask |= EV_RXCHAR;
	SetCommMask(pDlg->m_hCom,dwEvtMask);
	while(pDlg->m_bRun)
	{
		WaitCommEvent(pDlg->m_hCom,&dwEvtMask,NULL);
		if(pDlg->m_hCom==INVALID_HANDLE_VALUE)
			return 0;
		if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR){ 

		COMSTAT ComStat ; 
		DWORD dwLength,dwErrorFlags; 

		ClearCommError(pDlg->m_hCom, &dwErrorFlags, &ComStat ) ; 
		dwLength = ComStat.cbInQue ; //输入缓冲区有多少数据？ 

	if (dwLength > 0){

		bReadStatus = ReadFile( pDlg->m_hCom, data,dwLength, &dwBytesRead, 

					&Overlapped); //读数据
		if(!bReadStatus)
		{
			if(GetLastError()==ERROR_IO_PENDING)
			{

			while(!GetOverlappedResult(pDlg->m_hCom, 

				&Overlapped, &dwBytesRead, TRUE ))
			{ 

				if(GetLastError() == ERROR_IO_INCOMPLETE) 
					continue;
			}
				pDlg->m_bRevCS.Lock();
				for(int i = 0;i<dwBytesRead;i++)
				{
					pDlg->m_dequeRevData.push_back(data[i]);
				}
				pDlg->m_bRevCS.Unlock();
				pDlg->PostMessage(WM_RECEIVE,0,0);
			}
		}
		else
		{
			pDlg->m_bRevCS.Lock();
			for(int i = 0;i<dwLength;i++)
			{
				pDlg->m_dequeRevData.push_back(data[i]);
			}
			pDlg->m_bRevCS.Unlock();
			pDlg->PostMessage(WM_RECEIVE,0,0);	
		}
	}
	}
	}
//////////////////////////////////////////////////////////////////
	return 0;
}

void CSerialAsDlg::OnBtnopenport() 
{
	// TODO: Add your control notification handler code here
	CString sPort;
	DWORD dwBaudRate;
	BYTE byDataBits;
	BYTE byParity;
	BYTE byStopBits;

	m_ConfigPort.GetParam(sPort,dwBaudRate,byDataBits,byParity,byStopBits);
	m_hCom = m_Port.OpenPort(sPort,dwBaudRate,byDataBits,byParity,byStopBits);
	if(m_hCom!=INVALID_HANDLE_VALUE)
	{
		EnableCtrl(FALSE);
		UpdateStatusBar();
		m_bRun = TRUE;
		SetTimer(TIME_ID_REV,50,NULL);
		AfxBeginThread(RevThreadProc,this,THREAD_PRIORITY_NORMAL,0,0,NULL);
		AfxBeginThread(SendThreadProc,this,THREAD_PRIORITY_NORMAL,0,0,NULL);
	////////////////////////////////////
		CString str;
		GetDlgItem(IDC_EDITSENDFILEPATH)->GetWindowText(str);
		if(str.IsEmpty())
			return;
		CFile file;
		CFileException fe;

		if(!file.Open(str,CFile::modeRead,&fe))
		{
			fe.ReportError();
			str = _T("文件信息获得失败!");
			this->UpdateStatusBarInfo(m_StatusBar,1,str);
			return;
		}
		try
		{
			m_dwSendFileLen = file.GetLength();
			CString str;
			if(m_dwSendFileLen<1024)
				str.Format(_T("文件大小:%d字节，发送时间:%d秒"),m_dwSendFileLen,	int(m_dwSendFileLen/GetByteRate()+1));
			else if(m_dwSendFileLen>1024&&m_dwSendFileLen<1024*1024)
				str.Format(_T("文件大小:%.1fK，发送时间:%d秒"),m_dwSendFileLen/1024.0,	int(m_dwSendFileLen/GetByteRate()));
			else
				str.Format(_T("文件大小:%.2fM，发送时间:%d秒"),m_dwSendFileLen/1024.0/1024.0,	int(m_dwSendFileLen/GetByteRate()));

			this->UpdateStatusBarInfo(m_StatusBar,1,str);
			file.Close();
		}
		catch(CFileException e)
		{
			file.Abort(); // will not throw an exception
			e.ReportError();
			CString str;
			str = _T("文件信息获得失败!");
			this->UpdateStatusBarInfo(m_StatusBar,1,str);
		}
	}
	else
	{
		CString str = m_Port.GetError();
		MessageBox(str,_T("串口打开失败！"),MB_ICONERROR);
	}
}

void CSerialAsDlg::EnableCtrl(BOOL bFlag)
{
	GetDlgItem(IDC_BTNOPENPORT)->EnableWindow(bFlag);
	GetDlgItem(IDC_BTNCLOSEPORT)->EnableWindow(!bFlag);
	GetDlgItem(IDC_BTNPORTCONFIG)->EnableWindow(bFlag);
	GetDlgItem(IDC_CHECKAUTOSEND)->EnableWindow(!bFlag);
	GetDlgItem(IDC_STARTSENDFILE)->EnableWindow(!bFlag);
	GetDlgItem(IDC_MANUALSEND)->EnableWindow(!bFlag);
}

void CSerialAsDlg::OnBtncloseport() 
{
	// TODO: Add your control notification handler code here
	m_bRun = FALSE;
	if(m_Port.ClosePort())
	{
		m_hCom = INVALID_HANDLE_VALUE;
		EnableCtrl(TRUE);
		UpdateStatusBar();
		KillTimer(TIME_ID_REV);
		::SetEvent(m_hSendEvent);
	}
	else
	{
		AfxMessageBox(_T(" Fatal Error!"));
	}
}

void CSerialAsDlg::UpdateStatusBar()
{
	CString sPort;
	CString sBaudRate;
	CString sDataBits;
	CString sParity;
	CString sStopBits;

	m_ConfigPort.GetParamString(sPort,sBaudRate,
								sDataBits,sParity,sStopBits);

	CString sStatus;
	if(m_hCom!=INVALID_HANDLE_VALUE)
	{
		sStatus = _T("Opened");
	}
	else
	{
		sStatus = _T("Closed");
	}
	CString str;
	str = sPort+_T(",")+sStatus+_T(",") +CString(sBaudRate)+_T(",")
		+sDataBits+_T(",")+sParity+_T(",")+sStopBits;
	UpdateStatusBarInfo(m_StatusBar,0,str);
	if(m_hCom!=INVALID_HANDLE_VALUE)
	{
		m_StatusBar.GetStatusBarCtrl().SetIcon(0,NULL);		
		m_StatusBar.GetStatusBarCtrl().SetIcon(0,m_hIconOpened);
	}
	else
	{
		m_StatusBar.GetStatusBarCtrl().SetIcon(0,NULL);		
		m_StatusBar.GetStatusBarCtrl().SetIcon(0,m_hIconClosed);
	}

}

//更新状态栏的信息
void CSerialAsDlg::UpdateStatusBarInfo(CStatusBar &statusBar,int nIndex,LPCTSTR lpszNewText)
{
	TCHAR text[256];
	_stprintf(text,_T("%s"),lpszNewText);
	m_StatusBar.SetPaneText(nIndex,text);
/*	CFont font,*pOldFont;
	font.CreateFont(-15,0,0,0,500,FALSE,FALSE,0,ANSI_CHARSET,
	OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,PROOF_QUALITY,
		DEFAULT_PITCH|FF_SWISS,"宋体");
	CDC *pDC = m_StatusBar.GetDC();
	COLORREF color = RGB_BTNFACE;
	CBrush brush,pOldBrush;
	brush.CreateSolidBrush(color);
	CRect rect;
	rect = m_StatusBar.GetBorders();
//	pOldBrush = pDC->SelectObject(&brush);
	pDC->FillRect(&rect,&brush);
	pOldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(255,0,0));
	pDC->SetBkMode(1);
	pDC->TextOut(0,4,lpszNewText);
	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);*/
}

void CSerialAsDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==TIME_ID_TIME)
	{
		CString str;
		SYSTEMTIME st;
		GetLocalTime(&st); 
		str.Format(_T("%02d:%02d:%02d"),st.wHour,st.wMinute,st.wSecond);
		UpdateStatusBarInfo(m_StatusBar,2,str);
	}
	else if(nIDEvent==TIME_ID_REV)
	{
		if(m_bRevUpdate)
		{
			m_bRevUpdate = FALSE;
		}
	}
	else if(nIDEvent==TIME_ID_SEND)
	{
		if(m_bAutoSend)
		{
			::SetEvent(m_hSendEvent);
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CSerialAsDlg::OnSelectsendfile() 
{
	// TODO: Add your control notification handler code here
	static TCHAR  szSplitFilter[] = _T("(*.*)|*.*||");

	CFileDialog dlg(TRUE,
					NULL,
					NULL,
					OFN_HIDEREADONLY	| 
					OFN_OVERWRITEPROMPT ,
					szSplitFilter
					);

	if(dlg.DoModal()==IDOK)
	{
		GetDlgItem(IDC_EDITSENDFILEPATH)->SetWindowText(dlg.GetPathName());
		CFile file;
		CFileException fe;

		if(!file.Open(dlg.GetPathName(),CFile::modeRead,&fe))
		{
			fe.ReportError();
			CString str;
			str = _T("文件信息获得失败!");
			this->UpdateStatusBarInfo(m_StatusBar,1,str);
			return;
		}

		try
		{
			m_dwSendFileLen = file.GetLength();
			CString str;
			if(m_dwSendFileLen<1024)
				str.Format(_T("文件大小:%d字节，发送时间:%d秒"),m_dwSendFileLen,	int(m_dwSendFileLen/GetByteRate()+1));
			else if(m_dwSendFileLen>1024&&m_dwSendFileLen<1024*1024)
				str.Format(_T("文件大小:%.1fK，发送时间:%d秒"),m_dwSendFileLen/1024.0,	int(m_dwSendFileLen/GetByteRate()));
			else
				str.Format(_T("文件大小:%.2fM，发送时间:%d秒"),m_dwSendFileLen/1024.0/1024.0,	int(m_dwSendFileLen/GetByteRate()));

			this->UpdateStatusBarInfo(m_StatusBar,1,str);
			file.Close();
		}
		catch(CFileException e)
		{
			file.Abort(); // will not throw an exception
			e.ReportError();
			CString str;
			str = _T("文件信息获得失败!");
			this->UpdateStatusBarInfo(m_StatusBar,1,str);
		}

	}
}

void CSerialAsDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	BOOL bFlag = FALSE;
	CString str;
	str.Empty();
	if(m_hCom!=INVALID_HANDLE_VALUE)
		str = _T("处于连接状态，确实要退出吗？");
	if(m_bSendFlag)
		str = _T("正在发送文件，确实要退出吗？");

	if(str.IsEmpty()) 
	{
		CDialog::OnCancel();
	}
	else
	{
		if(MessageBox(str,_T("退出确认"),MB_OKCANCEL)==IDOK)
			bFlag = TRUE;
	}
		
	if(bFlag)
	{
		if(m_hCom!=INVALID_HANDLE_VALUE)
		{
			OnBtncloseport(); 
		}	
		CDialog::OnCancel();
	}
}

LRESULT CSerialAsDlg::OnSend(WPARAM wParam,LPARAM lParam)
{
	SEND *pSend = (SEND*)(lParam);
	m_dwSendCount += DWORD(wParam);
	CString str;
	str.Format(_T("TX:%d"),m_dwSendCount);
	GetDlgItem(IDC_EDITSENDCOUNT)->SetWindowText(str);
	if(pSend->bFlag)
	{
		str.Format(_T("正在发送：%.1f%%,剩余时间%d秒"),pSend->value,UINT(m_dwSendFileLen*(100-pSend->value)/100/GetByteRate()));
		UpdateStatusBarInfo(m_StatusBar,1,str);
		m_StatusBar.GetStatusBarCtrl().SetIcon(0,NULL);	
	}
	if(pSend->bFlag==TRUE&&pSend->value < 0.000001)	 
	{
		UpdateStatusBar();
		str.Format(_T("已发送完毕！"));
		if(m_bCancelSend)
		{
			str.Format(_T("已取消发送！"));
		}
		if(m_SendError)
		{
			str.Format(_T("发送有错误，未能完成本次发送!"));
		}
		GetDlgItem(IDC_STARTSENDFILE)->SetWindowText(_T("发送文件"));
		UpdateStatusBarInfo(m_StatusBar,1,str);
		GetDlgItem(IDC_BTNCLOSEPORT)->EnableWindow(TRUE);
		m_StatusBar.OnProgress(0);
	}
	if(pSend->value>0.0001&&pSend->value<1.1)
		pSend->value = 1.00001;
	if(pSend->bFlag) m_StatusBar.OnProgress(UINT(pSend->value));
	return 0;
}

LRESULT CSerialAsDlg::OnReceive(WPARAM wParam,LPARAM lParam)
{
	CString str,strTemp;
	str.Empty();
	m_bRevCS.Lock();
	int size = m_dequeRevData.size();
	for(int i=0;i<size;i++)
	{
		if(!m_bHexDisplay)
		{
			strTemp.Format(_T("%c"),m_dequeRevData[0]);
		}
		else
		{
			strTemp.Format(_T(" %02x"),m_dequeRevData[0]);
		}
		m_dequeRevData.pop_front();
		str += strTemp;
	}
	m_dwRevCount += size; 
	m_bRevCS.Unlock();
	COLORREF color = RGB_RED;;
	m_Rev.AddText(str,color);
	str.Format(_T("RX:%d"),m_dwRevCount);
	GetDlgItem(IDC_EDITREVCOUNT)->SetWindowText(str);
	if(m_bAutoClear)
	{
		if(m_Rev.GetLineCount()>35) OnClearrevdata();
	}
	return 0;
}

void CSerialAsDlg::OnBtnclearrevcount() 
{
	// TODO: Add your control notification handler code here
	m_dwRevCount = 0;
	CString str;
	str.Format(_T("RX:%d"),m_dwRevCount);
	GetDlgItem(IDC_EDITREVCOUNT)->SetWindowText(str);
}

void CSerialAsDlg::OnBtnclearsendcount() 
{
	// TODO: Add your control notification handler code here
	m_dwSendCount = 0;
	CString str;
	str.Format(_T("TX:%d"),m_dwSendCount);
	GetDlgItem(IDC_EDITSENDCOUNT)->SetWindowText(str);
}

void CSerialAsDlg::OnClearrevdata() 
{
	// TODO: Add your control notification handler code here
	m_sRev = _T("");
	m_Rev.SetWindowText(m_sRev);
}

void CSerialAsDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CDialog::OnLButtonDown(nFlags, point);
}

void CSerialAsDlg::OnCheckhexdisplay() 
{
	// TODO: Add your control notification handler code here
	m_bHexDisplay = !m_bHexDisplay;
}

UINT CSerialAsDlg::SendThreadProc(LPVOID pParam)
{
	CSerialAsDlg *pDlg = (CSerialAsDlg *)pParam;
	HANDLE hEvent = 0;
	OVERLAPPED overlapped;
	memset(&overlapped,0,sizeof(OVERLAPPED));
	DWORD dwWrite = 0;
	static _SEND send;

	hEvent = CreateEvent( 
		NULL,         // no security attributes
		TRUE,         // manual-reset event
		FALSE,        // initial state is nosignaled
		NULL		  // object name
		); 
	overlapped.hEvent = hEvent;
	while(pDlg->m_bRun)
	{
		::WaitForSingleObject(pDlg->m_hSendEvent,0xFFFFFFFF);
		::ResetEvent(pDlg->m_hSendEvent);
		if(pDlg->m_hCom==INVALID_HANDLE_VALUE)
			return 0;
		CString str;
		pDlg->m_Send.GetWindowText(str);
		DWORD len = str.GetLength();
		DWORD dwBytesWrite = 0;
		BOOL bStatus;

		if(pDlg->m_bHEXSend)
		{
			BYTE *p = new BYTE[(len+1)*sizeof(TCHAR)];
			len = pDlg->StrToHex(str,p,len);
			bStatus = WriteFile(pDlg->m_hCom,p,len,&dwWrite,&overlapped);
		}
		else
		{
			bStatus = WriteFile(pDlg->m_hCom,str.GetBuffer(len),len,
								&dwWrite,&overlapped);
			str.ReleaseBuffer();
		}
		if(!bStatus)
		{
			if(GetLastError()==ERROR_IO_PENDING)
			{
				while(!GetOverlappedResult(pDlg->m_hCom, 
					&overlapped, &dwBytesWrite, TRUE ))
				{ 
					if(GetLastError() == ERROR_IO_INCOMPLETE) 
						continue;
				}
				send.bFlag = false;
				send.value = 0;
				pDlg->PostMessage(WM_SEND,dwBytesWrite,(LPARAM)&send);
			}
		}
		else
		{
			send.bFlag = false;
			send.value = 0;
			pDlg->PostMessage(WM_SEND,len,(LPARAM)&send);
		}
	}
	return 0;
}

UINT CSerialAsDlg::SendFileThreadProc(LPVOID pParam)
{
	CSerialAsDlg *pDlg = (CSerialAsDlg *)pParam;
	HANDLE hEvent = 0;
	OVERLAPPED overlapped;
	DWORD dwWrite = 0;
	memset(&overlapped,0,sizeof(OVERLAPPED));
	static SEND send;
	
	hEvent = CreateEvent( 
		NULL,         // no security attributes
		TRUE,         // manual-reset event
		FALSE,        // initial state is nosignaled
		NULL		  // object name
		); 
	overlapped.hEvent = hEvent;
	
	CString sFilePathName;
	pDlg->GetDlgItem(IDC_EDITSENDFILEPATH)->GetWindowText(sFilePathName);
	
	DWORD dwAttr;
	dwAttr=GetFileAttributes(sFilePathName);
	if(dwAttr==0xFFFFFFFF)
	{
		::MessageBox(NULL,_T("文件路径不对"),_T("提示"),MB_OK|MB_ICONERROR);

		pDlg->GetDlgItem(IDC_BTNCLOSEPORT)->EnableWindow(TRUE);
		pDlg->GetDlgItem(IDC_STARTSENDFILE)->SetWindowText(_T("发送文件"));
		pDlg->GetDlgItem(IDC_STARTSENDFILE)->EnableWindow(TRUE);
		pDlg->m_bSendFlag = FALSE;
		return 0;
	}
	
	CFile file;
	CFileException fe;

	if(!file.Open(sFilePathName,CFile::modeRead,&fe))
	{
		fe.ReportError();
		file.Abort();
		send.bFlag = true;
		send.value = 0.0;
		pDlg->PostMessage(WM_SEND,0,(LPARAM)&send);
		pDlg->m_bSendFlag = FALSE;
		SetEvent(pDlg->m_hEventSendFile);
		return 0;
	}
	TRY
	{
		file.Seek(0,CFile::begin);///从文件头开始往下移动0字节
	
#define LENGTH (1024)
	BYTE *pFile = new BYTE[LENGTH];
	DWORD dwLength = (long)file.GetLength();
	BOOL bFlag = TRUE;
	DWORD dwLeaveLen = dwLength;
	BOOL bStatus;
	DWORD dwBytesWrite = 0;
	pDlg->GetDlgItem(IDC_STARTSENDFILE)->EnableWindow(TRUE);
	while(bFlag&&pDlg->m_bSendFlag)
	{
		DWORD len = 0;
		if(dwLeaveLen<LENGTH)
		{
			len = dwLeaveLen;
			bFlag = FALSE;
		}
		else
		{
			dwLeaveLen -= LENGTH;
			len = LENGTH;
		}
		file.Read(pFile,len);
		bStatus = WriteFile(pDlg->m_hCom,pFile, 
			len,&dwWrite, &overlapped);
		if(!bStatus)
		{
			if(GetLastError()==ERROR_IO_PENDING)
			{
				
				while(!GetOverlappedResult(pDlg->m_hCom, 
					
					&overlapped, &dwBytesWrite, TRUE ))
				{ 
					if(GetLastError() == ERROR_IO_INCOMPLETE) 
						continue;
					
				}
				send.bFlag = true;
				send.value = (dwLength-dwLeaveLen)*100.0/dwLength;
				pDlg->PostMessage(WM_SEND,dwBytesWrite,(LPARAM)(&send.bFlag));
			}
		}
		else
		{
			send.bFlag = true;
			send.value = 0.0;
			pDlg->PostMessage(WM_SEND,len,(LPARAM)&send);
		}
		
	}
	delete []pFile;
	file.Close();
	}
	CATCH(CFileException ,e)
	{
		file.Abort(); // will not throw an exception
		e->ReportError();
		pDlg->m_SendError = TRUE;
	}
	END_CATCH

	send.bFlag = true;
	send.value = 0.0;
	pDlg->PostMessage(WM_SEND,0,(LPARAM)&send);
	pDlg->m_bSendFlag = FALSE;
	SetEvent(pDlg->m_hEventSendFile);
	return 0;
}

void CSerialAsDlg::OnStartsendfile() 
{
	// TODO: Add your control notification handler code here
	static CWinThread* thread;
	if(!m_bSendFlag)
	{
		m_bSendFlag = TRUE;
		m_SendError = FALSE;
		m_bCancelSend = FALSE;
		GetDlgItem(IDC_BTNCLOSEPORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_STARTSENDFILE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STARTSENDFILE)->SetWindowText(_T("取消发送"));
		ResetEvent(m_hEventSendFile);
		thread = AfxBeginThread(SendFileThreadProc,this,THREAD_PRIORITY_NORMAL,0,0,NULL);
	}
	else
	{
		m_bSendFlag = FALSE;
		m_bCancelSend = TRUE;
		DWORD st = WaitForSingleObject(m_hEventSendFile,2000);
		if(st==WAIT_TIMEOUT)
		{
			TerminateThread(thread,0);
		}
		GetDlgItem(IDC_BTNCLOSEPORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_STARTSENDFILE)->SetWindowText(_T("发送文件"));
	}
}

void CSerialAsDlg::OnCheckautosend() 
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_EDITSENDPERIOD)->GetWindowText(str);
	int iPeriod = _ttoi(str);
	if(!m_bAutoSend)
	{
		if(iPeriod==0)
		{
			MessageBox(_T("请选择一个合适的周期！"),_T("提示！"),MB_ICONERROR);
			m_checkAutoSend.SetCheck(0);
			return ;
		}
	}

	m_bAutoSend = !m_bAutoSend;
	if(m_bAutoSend)
	{

		SetTimer(TIME_ID_SEND,iPeriod,NULL);
	}
	else
	{
		KillTimer(TIME_ID_SEND);
	}
}

void CSerialAsDlg::OnManualsend() 
{
	// TODO: Add your control notification handler code here
	SetEvent(m_hSendEvent);
}

void CSerialAsDlg::OnCheckautoclear() 
{
	// TODO: Add your control notification handler code here
	m_bAutoClear = !m_bAutoClear;
}

void CSerialAsDlg::OnClearsenddata() 
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_RICHEDITSENDDATA,_T(""));
}

void CSerialAsDlg::OnCheckhexsend() 
{
	// TODO: Add your control notification handler code here
	m_bHEXSend = !m_bHEXSend;
}

DWORD CSerialAsDlg::StrToHex(CString str,BYTE *p,DWORD len)
{
	BYTE *pTemp = new BYTE[len];
	str.MakeLower();
	str.TrimLeft();
	str.TrimRight();
	str.Replace(_T('\n'),_T(' '));
	str.Replace(_T('\r'),_T(' '));
	len = str.GetLength();
	memcpy(pTemp,p,len*sizeof(BYTE));
	pTemp = (BYTE *)str.GetBuffer(len);
	DWORD dwStart = 0;
	BYTE value = 0;
	DWORD i=0;
	DWORD count = 0;
	for(i=0;i<len;i++)
	{
		if(('0'<=pTemp[i]&&pTemp[i]<='9')||('a'<=pTemp[i]&&pTemp[i]<='f')||pTemp[i]==' ')
		{
			continue;
		}
		else
		{
			str.ReleaseBuffer();
			return 0;
		}
	}
	BOOL bFlag= false;
    for(i=0;i<len;i++)
	{
		if(pTemp[i]!=' ')
		{
			if(!bFlag)
			{
				dwStart = i;
				bFlag = TRUE;  //新的一个数开始了
			}
		}
		else if(bFlag)
		{
			if(i-dwStart>2)
				{
					str.ReleaseBuffer();
					return 0;
				}
				else
				{
					if(i-dwStart==2)
					{
						p[count] = HEXToDec(pTemp[dwStart])*16;
						p[count++] += HEXToDec(pTemp[dwStart+1]);
					}
					else
					{
						p[count++] = HEXToDec(pTemp[dwStart]);
					}
				}
				bFlag = false;
				continue;
		}
		if(i==len-1)
		{
			i++;
			if(i-dwStart>2)
				{
					str.ReleaseBuffer();
					return 0;
				}
				else
				{
					if(i-dwStart==2)
					{
						p[count] = HEXToDec(pTemp[dwStart])*16;
						p[count++] += HEXToDec(pTemp[dwStart+1]);
					}
					else
					{
						p[count++] = HEXToDec(pTemp[dwStart]);
					}
				}
		}
	}
	str.ReleaseBuffer();
	return count;
}

//把一个字母或数字转换为十进制
BYTE CSerialAsDlg::HEXToDec(BYTE value)
{
	if('0'<=value&&value<='9')
	{
		return value-'0';
	}
	else if('a'<=value&&value<='f')
	{
		return value-'a'+10;
	}
	return 0;
}

void CSerialAsDlg::OnBtnsavefile() 
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_RICHEDITREVDATA,str);
	DWORD len = str.GetLength();
	if(len ==0) 
	{
		MessageBox(_T("接受区无数据!"),_T("提示"),MB_ICONERROR);
		return; 
	}

	GetDlgItemText(IDC_STATICSAVEFILEPATH,str);
	if(!PathFileExists(m_sSaveDir))
	{
		if(MessageBox(_T("没有此目录，要创建吗？"),_T("提示"),MB_OKCANCEL)==IDOK)
		{
			if(!CFilePro::CreateFolder(m_sSaveDir))
				return;
		}
		else
		{
			return;
		}
	}
	WriteMyFile(str);
}

void CSerialAsDlg::OnBtnchangesavefilepath() 
{
	// TODO: Add your control notification handler code here
	LPITEMIDLIST  pidlBeginAt ;
    // 取得开始菜单或桌面的PIDL
    if(NOERROR !=SHGetSpecialFolderLocation( HWND_DESKTOP, 
            CSIDL_DESKTOP, 
			&pidlBeginAt) )
	{
		CFilePro::ReleasePIDL(&pidlBeginAt);
		return;
	}
	TCHAR szPath[ MAX_PATH] ;
	if(CFilePro::BrowseForFolder(m_hWnd,pidlBeginAt, szPath,_T("请选择要存放文件的目录：")))
	{
		CString str ;
		m_sSaveDir	= CString(szPath);
		m_sSaveDir.TrimRight(_T("\\"));
		GetDlgItemText(IDC_SAVEFILENAME,str);
		str = m_sSaveDir +_T("\\") + str;
		SetDlgItemText(IDC_STATICSAVEFILEPATH,str);
	}
}

//把数据写入文件
void CSerialAsDlg::WriteMyFile(CString filename)
{
//	filename.MakeLower();
	CString str;
	GetDlgItemText(IDC_RICHEDITREVDATA,str);

/*  CString strFileName,sPath;
	strFileName = filename;

	CString sFileName;
	GetDlgItemText(IDC_SAVEFILENAME,sFileName);
	sFileName.MakeLower();
	strFileName.TrimRight(sFileName);
	strFileName.TrimRight(_T("\\"));

	int index = strFileName.Find(_T('\\'),0);

	if(index == 0xffffffff)
	{
		strFileName = strFileName + _T("\\")+ sFileName;
	}
	else
	{
		CString sTemp = strFileName;
		CString sSubTemp;
		while(1)
		{
			CFileFind finder;
			int length = sTemp.GetLength();
			BOOL bFlag = finder.FindFile(sTemp);
			if(!bFlag)
			{
				CFilePro::CreateFolder(strFileName);
				break;
			}
			index = 0;
			int tempIndex = 0;
			index = str.Find(_T("\\"),0);
			if(index = 0xffffffff)
				break;
			while(index!=0xffffffff)
			{
				tempIndex = index;
				index = sTemp.Find(_T("\\"));
			}
			sSubTemp = sTemp.Right(length - tempIndex);
			sTemp.TrimRight(sSubTemp);
			sTemp.TrimRight(_T("\\"));

			index = str.Find(_T("\\"),0);
			if(index = 0xffffffff)
				break;
			index = str.Find(_T("\\"),index);
			if(index = 0xffffffff)
				break;
		}
	}*/
//	WIN32_FIND_DATA wfd;
//	HANDLE handle = ::FindFirstFile(strFileName,&wfd);
//	if(INVALID_HANDLE_VALUE==handle||wfd.dwFileAttributes&&FILE_ATTRIBUTE_DIRECTORY!=FILE_ATTRIBUTE_DIRECTORY)
//		AfxMessageBox("aaa");
	if(PathFileExists(filename))
	{
		if(!(MessageBox(_T("已经存在一个同名的文件，要覆盖吗？"),_T("提示"),MB_OKCANCEL)==IDOK))
		{
			return;
		}
	}

	DWORD len = str.GetLength();
	if(len ==0) return; 
	CFile file;
	CFileException fe;
	if(!file.Open(filename,CFile::modeCreate|CFile::modeWrite,&fe))
	{
		fe.ReportError();
		return ;
	}
	TRY
	{
	//	BYTE *pTemp = new BYTE[len];
//	pTemp = (BYTE *)str.GetBuffer(len);
	file.Write(str,len);
//	str.ReleaseBuffer();
	file.Close();
	}
	CATCH(CFileException ,e)
	{
		file.Abort(); // will not throw an exception
		e->ReportError();
		return;
	}
	END_CATCH

	MessageBox(_T("文件保存成功!"),_T("提示"),MB_OK);

}

void CSerialAsDlg::OnOK()
{

}

BOOL CSerialAsDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->hwnd==GetDlgItem(IDC_EDITSENDPERIOD)->m_hWnd)
	{
		if(pMsg->wParam==VK_RETURN)
		{
			CString str;
			GetDlgItem(IDC_EDITSENDPERIOD)->GetWindowText(str);
			int iPeriod = _ttoi(str);
			if(iPeriod==0)
			{
				MessageBox(_T("请选择一个合适的周期！"),_T("提示！"),MB_ICONERROR);
				return TRUE;
			}
			if(m_bAutoSend)
			{
				KillTimer(TIME_ID_SEND);
				SetTimer(TIME_ID_SEND,iPeriod,NULL);
			}
				return TRUE;		//若为FALSE,此段代码要运行两次!!!
		}

	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CSerialAsDlg::OnChangeSavefilename() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_SAVEFILENAME,str);
	if(1)
	{
		m_OldSaveFileName = str;
	}
	else
	{
		SetDlgItemText(IDC_SAVEFILENAME,m_OldSaveFileName);
		return;
	}
	str = m_sSaveDir +_T("\\") + str;
	SetDlgItemText(IDC_STATICSAVEFILEPATH,str);
}

DWORD CSerialAsDlg::GetByteRate()
{
	CString sPort;
	DWORD dwBaudRate;
	BYTE byDataBits;
	BYTE byParity;
	BYTE byStopBits;
	m_ConfigPort.GetParam(sPort,dwBaudRate,byDataBits,byParity,byStopBits);
	
	float fStopBit = 0;
	switch(byStopBits)
	{
		case 0:
			fStopBit = 1;
			break;
		case 1:
			fStopBit = 1.5;
			break;
		case 2:
			fStopBit = 2;;
			break;
		default:
			fStopBit = 1;
			break;
	}
	
	if(byParity!=0)
	{
		byParity = 1;
	}
	return (dwBaudRate/(byDataBits+fStopBit+byParity+1));
}


BOOL CSerialAsDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
/*	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	dc.FillRect(rect,&m_bkBrush);
	return true;*/
	return CDialog::OnEraseBkgnd(pDC);
}

HBRUSH CSerialAsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_STATIC||CTLCOLOR_SCROLLBAR  ==nCtlColor||nCtlColor==CTLCOLOR_DLG)
	{
	// TODO: Return a different brush if the default is not desired
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)(m_bkBrush.m_hObject);
	}
	return hbr;
}

void CSerialAsDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if(cx==0||cy==0)
		return;
	CRect rect;
	if(m_btManualSend.m_hWnd)
	{
		m_btManualSend.GetWindowRect(&rect);
		rect.top += (cy-m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		ScreenToClient(&rect);
		m_btManualSend.MoveWindow(&rect);
	}
	if(m_staticNail.m_hWnd)
	{
		m_staticNail.GetWindowRect(&rect);
		rect.top += (cy-m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		ScreenToClient(&rect);
		m_staticNail.MoveWindow(&rect);
	}

	if(m_editSendPeriod.m_hWnd)
	{
		m_editSendPeriod.GetWindowRect(&rect);
		rect.top += (cy-m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		ScreenToClient(&rect);
		m_editSendPeriod.MoveWindow(&rect);
	}
	if(m_btStartSendFile.m_hWnd)
	{
		m_btStartSendFile.GetWindowRect(&rect);
		rect.top += (cy-m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		rect.right += (cx - m_OldRect.Width());
		rect.left += (cx - m_OldRect.Width());
		ScreenToClient(&rect);
		m_btStartSendFile.MoveWindow(&rect);
	}
	if(m_btSelectSendFile.m_hWnd)
	{
		m_btSelectSendFile.GetWindowRect(&rect);
		rect.top += (cy-m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		rect.right += (cx - m_OldRect.Width());
		rect.left += (cx - m_OldRect.Width());
		ScreenToClient(&rect);
		m_btSelectSendFile.MoveWindow(&rect);
	}
	if(m_editSendFilePath.m_hWnd)
	{
		m_editSendFilePath.GetWindowRect(&rect);
		rect.top += (cy-m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		rect.right += (cx - m_OldRect.Width());
		rect.left += (cx - m_OldRect.Width());
		ScreenToClient(&rect);
		m_editSendFilePath.MoveWindow(&rect);
	}
	if(m_Send.m_hWnd)
	{
		m_Send.GetWindowRect(&rect);
		rect.bottom += (cy - m_OldRect.Height());
		rect.top += (cy - m_OldRect.Height());
		rect.right += (cx - m_OldRect.Width());
		ScreenToClient(&rect);
		m_Send.MoveWindow(&rect);
	}
	if(m_Rev.m_hWnd)
	{
		m_Rev.GetWindowRect(&rect);
		rect.bottom += (cy - m_OldRect.Height());
		rect.right += (cx - m_OldRect.Width());
		ScreenToClient(&rect);
		m_Rev.MoveWindow(&rect);
	}
	if(m_btClearSendData.m_hWnd)
	{
		m_btClearSendData.GetWindowRect(&rect);
		rect.top += (cy - m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		ScreenToClient(&rect);
		m_btClearSendData.MoveWindow(&rect);
	}	
	if(m_btClearSendCount.m_hWnd)
	{
		m_btClearSendCount.GetWindowRect(&rect);
		rect.top += (cy - m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		rect.right += (cx - m_OldRect.Width());
		rect.left += (cx - m_OldRect.Width());
		ScreenToClient(&rect);
		m_btClearSendCount.MoveWindow(&rect);
	}

	if(m_editSendCount.m_hWnd)
	{
		m_editSendCount.GetWindowRect(&rect);
		rect.top += (cy - m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		rect.right += (cx - m_OldRect.Width());
		rect.left += (cx - m_OldRect.Width());
		ScreenToClient(&rect);
		m_editSendCount.MoveWindow(&rect);
	}	
	if(m_btHelp.m_hWnd)
	{
		m_btHelp.GetWindowRect(&rect);
		rect.top += (cy - m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		rect.right += (cx - m_OldRect.Width());
		rect.left += (cx - m_OldRect.Width());
		ScreenToClient(&rect);
		m_btHelp.MoveWindow(&rect);
	}
	if(m_btCancel.m_hWnd)
	{
		m_btCancel.GetWindowRect(&rect);
		rect.top += (cy - m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		rect.right += (cx - m_OldRect.Width());
		rect.left += (cx - m_OldRect.Width());
		ScreenToClient(&rect);
		m_btCancel.MoveWindow(&rect);
	}	
	if(m_checkAutoSend.m_hWnd)
	{
		m_checkAutoSend.GetWindowRect(&rect);
		rect.top += (cy - m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		ScreenToClient(&rect);
		m_checkAutoSend.MoveWindow(&rect);
	}	
	if(m_staticStrMS.m_hWnd)
	{
		m_staticStrMS.GetWindowRect(&rect);
		rect.top += (cy - m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		ScreenToClient(&rect);
		m_staticStrMS.MoveWindow(&rect);
	}	
	if(m_staticStrPeriod.m_hWnd)
	{
		m_staticStrPeriod.GetWindowRect(&rect);
		rect.top += (cy - m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		ScreenToClient(&rect);
		m_staticStrPeriod.MoveWindow(&rect);
	}	
	if(m_checkHEXSend.m_hWnd)
	{
		m_checkHEXSend.GetWindowRect(&rect);
		rect.top += (cy - m_OldRect.Height());
		rect.bottom += (cy - m_OldRect.Height());
		ScreenToClient(&rect);
		m_checkHEXSend.MoveWindow(&rect);
	}


	GetClientRect(&m_OldRect);
	
	CRect rect1;
	GetClientRect(&rect);

	if(m_StatusBar.m_hWnd)
	{
	    m_staticNail.GetWindowRect(&rect1);
		m_StatusBar.SetPaneInfo(0,ID_PORTSTATUS,SBPS_NORMAL,rect.Width()*2/5-5);
		m_StatusBar.SetPaneInfo(1,ID_COMSTATUS,SBPS_STRETCH,rect.Width()*2/5-rect1.Width());
		m_StatusBar.SetPaneInfo(2,ID_TIME,SBPS_NORMAL ,rect.Width()*1/5);		
		m_StatusBar.MoveWindow(rect.left+20,rect.bottom-rect1.Height(),rect.Width()-rect1.Width()-5,rect1.Height(),TRUE);
	}
	Invalidate();
}


void CSerialAsDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
//	lpMMI->ptMinTrackSize.x = 750;
//	lpMMI->ptMinTrackSize.y = 500;
	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CSerialAsDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{

	CDialog::OnSizing(fwSide, pRect);
	CRect rect1,rect2;
	m_btSelectSendFile.GetWindowRect(&rect1);
	m_btCancel.GetWindowRect(&rect2);
	if((pRect->right-pRect->left)<(rect2.right-rect1.left+50))
	{
		pRect->right = pRect->left+rect2.right-rect1.left+50;
	}
	CRect rect3,rect4;
	m_btConfigPort.GetWindowRect(&rect1);
	m_editSavefileName.GetWindowRect(&rect2);
	m_checkHEXSend.GetWindowRect(&rect3);
	m_StatusBar.GetWindowRect(&rect4);

	if((pRect->bottom-pRect->top)<((rect2.bottom-rect1.top)+(rect4.bottom-rect3.top)+40))
	// TODO: Add your message handler code here
	{
		pRect->bottom = pRect->top+((rect2.bottom-rect1.top)+(rect4.bottom-rect3.top)+40);
	}
}

void CSerialAsDlg::OnStaticNail() 
{
	// TODO: Add your control notification handler code here
	static BOOL bFlag = FALSE;
	if(bFlag)
	{
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE| WS_EX_TOPMOST);
		bFlag = FALSE;
	}
	else
	{
		SetWindowPos(&wndTopMost, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE);
		bFlag = TRUE;
	}
}

void CSerialAsDlg::OnMyhelp() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlgAbout;
	dlgAbout.m_bAbout = FALSE;
	dlgAbout.DoModal();
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_STATIC||nCtlColor==CTLCOLOR_DLG)
	{
	// TODO: Return a different brush if the default is not desired
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)(m_bkBrush.m_hObject);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd *pCwnd = GetDlgItem(IDC_STATIC_MAIL);
	m_ToolTipMail.Create(this);
	m_ToolTipMail.Activate(TRUE);
	m_ToolTipMail.AddTool(pCwnd, _T("Email给我lxg215@hotmail.com"));
	m_ToolTipMail.SetDelayTime(200);


	m_staticMail.m_link = _T("mailto:lxg215@hotmail.com");


	CString str = _T("\t\t\t\t写在前面的话");
	 str += _T("\r\n\t接触串口已经一年多了，虽然串口比较简单，可是我还不能说是很熟悉\
更不敢说精通了，为了给新接触串口的朋友一个例子，我一个直想做个关于串口的东西，所以\
就仿照了龚建伟的串口助手2.2作了一个（源代码没有仿照，其实他的源码我没看过:)）,希望能对\
大家有所帮助,花了我三天呢!");
	str += _T("\r\n\t此软件修正了龚建伟的串口助手2.2的几个bug，当然也可能引进了新的bug，呵呵");

	str += _T("原来的bug和不如意的地方如下:");

	str += _T("\r\n\r\n1. 当发送端数据发送很快的时候，接收发生丢数据的情况。");
	
	str += _T("\r\n\r\n2.发送时间间隔短的时候，实际发送的数据个数和记录的不符。");
	
	str += _T("\r\n\r\n3.数据量较大的时候占用系统资源太多。");

	str += _T("\r\n\r\n4......");

	m_reditHelpText.SetWindowText(str);

	static CHARFORMAT cf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	m_reditHelpText.GetDefaultCharFormat(cf);
	cf.dwMask		= CFM_COLOR;
	cf.dwEffects	= (unsigned long)~( CFE_AUTOCOLOR);
	cf.crTextColor	= RGB(0,128,0);
	m_reditHelpText.SetSel(0,-1);
	m_reditHelpText.SetSelectionCharFormat(cf);	
	m_reditHelpText.SetWordCharFormat(cf);
	m_bkBrush.CreateSolidBrush(DLGBK_COLOR);

	str.LoadString(IDS_TITLE);
	str += _T("\r|");
    str += _T("1.00版\t||");
	str += _T("最后更新\r|2005年8月\t|||||");
	TCHAR  *pArrCredit = new TCHAR[str.GetLength()];
	memcpy( pArrCredit,str.GetBuffer(str.GetLength()),str.GetLength()*sizeof(TCHAR));
	str.ReleaseBuffer();

	m_DyCredits.SubclassDlgItem(IDD_ABOUTBOX,this);
	m_DyCredits.SetCredits(pArrCredit,_T('|'));
	m_DyCredits.SetSpeed(1);							//滚动速度(0-慢速，1-中速，2-快速)
	m_DyCredits.SetColor(BACKGROUND_COLOR, RGB(0,255,200));
	m_DyCredits.SetTransparent();
	m_DyCredits.SetGradient(GRADIENT_RIGHT_DARK);
	delete pArrCredit;
	OnButtonswitch();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CAboutDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTipMail.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void CAboutDlg::OnButtonswitch() 
{
	// TODO: Add your control notification handler code here
	if(m_bAbout)
	{
		m_btSwitch.SetWindowText(_T("串口助手帮助"));
		m_reditHelpText.ShowWindow(SW_HIDE);		
		m_DyCredits.ShowWindow(SW_SHOW);
		m_DyCredits.StartScrolling();
		SetWindowText(_T("关于串口助手1.0"));
	}
	else
	{
		m_btSwitch.SetWindowText(_T("关于串口助手1.0"));
		m_DyCredits.EndScrolling();
		m_DyCredits.ShowWindow(SW_HIDE);
		m_reditHelpText.ShowWindow(SW_SHOW);
		SetWindowText(_T("串口助手帮助"));
	}
	m_bAbout = !m_bAbout;
}


BOOL CSerialAsDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	OnMyhelp() ;
	return TRUE;
//	return CDialog::OnHelpInfo(pHelpInfo);
}
