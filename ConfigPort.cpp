// ConfigPort.cpp : implementation file
//

#include "stdafx.h"
#include "SerialAs.h"
#include "ConfigPort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigPort dialog


CConfigPort::CConfigPort(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigPort::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigPort)
	//}}AFX_DATA_INIT

	CString sFilePath;
	sFilePath = STR_ROOT_DIR;
	if(!PathFileExists(STR_ROOT_DIR))
	{
		CFilePro::CreateFolder(STR_ROOT_DIR);
	}
	sFilePath += _T("\\");
	sFilePath += STR_PORT_INI;
	m_ini.GetString(_T("PortConfig"),_T("PortName"),_T("COM1"),
					m_sPort.GetBuffer(MAX_PATH),MAX_PATH,sFilePath);
	m_sPort.ReleaseBuffer();
	m_ini.GetString(_T("PortConfig"),_T("BaudRate"),_T("9600"),
					m_sBaudRate.GetBuffer(MAX_PATH),MAX_PATH,sFilePath);
	m_sBaudRate.ReleaseBuffer();
	m_ini.GetString(_T("PortConfig"),_T("DataBits"),_T("8"),
					m_sDataBits.GetBuffer(MAX_PATH),MAX_PATH,sFilePath);
	m_sDataBits.ReleaseBuffer();
	m_ini.GetString(_T("PortConfig"),_T("StopBits"),_T("1"),
					m_sStopBits.GetBuffer(MAX_PATH),MAX_PATH,sFilePath);
	m_sStopBits.ReleaseBuffer();	
	m_ini.GetString(_T("PortConfig"),_T("Parity"),_T("无校验"),
					m_sParity.GetBuffer(MAX_PATH),MAX_PATH,sFilePath);
	m_sParity.ReleaseBuffer();	
	m_byParity = m_ini.GetInt(_T("PortConfig"),_T("byParity"),NOPARITY,sFilePath);
	m_byStopBits = m_ini.GetInt(_T("PortConfig"),_T("byStopBits"),0,sFilePath);
	
	//	m_sPort = _T("COM1");

	m_dwBaudRate = _ttoi(m_sBaudRate);
	m_byDataBits = _ttoi(m_sDataBits);
//	m_byParity = NOPARITY;
//	m_byStopBits = (atof(m_sStopBits)+0.6);
//	m_sBaudRate  =_T("9600");
//	m_sDataBits = _T("8");
//	m_sParity = _T("无校验");
//	m_sStopBits = _T("1");

	m_brHollow.CreateSolidBrush(DLGBK_COLOR);
	m_sError.Empty();
	m_bCheckExistPort = TRUE;
}


void CConfigPort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigPort)
	DDX_Control(pDX, IDC_SAVEPORTCONFIG, m_SavePortConfig);
	DDX_Control(pDX, IDC_BTNOK, m_OKandOpen);
	DDX_Control(pDX, IDCANCEL, m_CANCEL);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_COMBOBAUDRATE, m_BaudRate);
	DDX_Control(pDX, IDC_CHECKEXISTPORT, m_CheckExistPort);
	DDX_Control(pDX, IDC_COMBDATABITS, m_DataBits);
	DDX_Control(pDX, IDC_COMBOPARITY, m_Parity);
	DDX_Control(pDX, IDC_COMBOPORT, m_Port);
	DDX_Control(pDX, IDC_COMBOSTOPBITS, m_StopBits);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigPort, CDialog)
	//{{AFX_MSG_MAP(CConfigPort)
	ON_BN_CLICKED(IDC_CHECKEXISTPORT, OnCheckexistport)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTNOK, OnBtnok)
	ON_BN_CLICKED(IDC_SAVEPORTCONFIG, OnSaveportconfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigPort message handlers

void CConfigPort::OnOK() 
{
	// TODO: Add extra validation here
	CString str;
	m_Port.GetLBText(m_Port.GetCurSel(),m_sPort);
	m_BaudRate.GetLBText(m_BaudRate.GetCurSel(),m_sBaudRate);
	m_dwBaudRate = _ttoi(m_sBaudRate);
	m_StopBits.GetLBText(m_StopBits.GetCurSel(),m_sStopBits);
	m_byStopBits = m_StopBits.GetCurSel();

	m_DataBits.GetLBText(m_DataBits.GetCurSel(),m_sDataBits);
	m_byDataBits = _ttoi(m_sDataBits);
    m_Parity.GetLBText(m_Parity.GetCurSel(),m_sParity);
	m_byParity = m_Parity.GetCurSel();
	CDialog::OnOK();
}

BOOL CConfigPort::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_CheckExistPort.SetCheck(m_bCheckExistPort);
	OnCheckexistport();

	CString str;
	m_DataBits.ResetContent();
	m_DataBits.AddString(_T("6"));
	m_DataBits.AddString(_T("7"));
	m_DataBits.AddString(_T("8"));
	str.Format(_T("%d"),m_byDataBits);
	m_DataBits.SelectString(-1,str);

	m_StopBits.ResetContent();
	m_StopBits.AddString(_T("1"));
	m_StopBits.AddString(_T("1.5"));
	m_StopBits.AddString(_T("2"));
	switch(m_byStopBits)
	{
		case 0:
			str = _T("1");
			break;
		case 1:
			str = _T("1.5");
			break;
		case 2:
			str = _T("2");
			break;
		default:
			str = _T("1");
			break;
	}
	m_StopBits.SelectString(-1,str);

	m_Parity.ResetContent();
	m_Parity.AddString(_T("无校验"));
	m_Parity.AddString(_T("奇校验"));
	m_Parity.AddString(_T("偶校验"));
	m_Parity.AddString(_T("标记"));
	m_Parity.AddString(_T("空格"));
	switch(m_byParity)
	{
		case 0:
			str = _T("无校验");
			break;
		case 1:
			str = _T("奇校验");
			break;
		case 2:
			str = _T("偶校验");
			break;
		case 3:
			str = _T("标记");
			break;
		case 4:
			str = _T("空格");
			break;
		default:
			str = _T("无校验");
			break;
	}
	m_Parity.SelectString(-1,str);

	m_BaudRate.ResetContent();
	int i = 0;
	for(i = 0;i<sizeof(BAUDRATE)/sizeof(DWORD);i++)
	{
		str.Format(_T("%d"),BAUDRATE[i]);
		m_BaudRate.AddString(str);
	}
	str.Format(_T("%d"),m_dwBaudRate);
	m_BaudRate.SelectString(-1,str);

	m_bOpen = false;

	m_Port.SetColors(RGB_RED, RGB_SYSWINDOWBK, RGB_RED, RGB_SYSWINDOWBK);
    m_DataBits.SetColors(RGB_RED, RGB_SYSWINDOWBK, RGB_RED, RGB_SYSWINDOWBK);
	m_StopBits.SetColors(RGB_RED, RGB_SYSWINDOWBK, RGB_RED, RGB_SYSWINDOWBK);
	m_Parity.SetColors(RGB_RED, RGB_SYSWINDOWBK, RGB_RED, RGB_SYSWINDOWBK);
	m_BaudRate.SetColors(RGB_RED, RGB_SYSWINDOWBK, RGB_RED, RGB_SYSWINDOWBK);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CConfigPort::	SetParam(CString sPort,DWORD dwBaudRate,BYTE byDataBits,BYTE byParity,BYTE byStopBits)
{
	return false;
}

BOOL CConfigPort::	GetParam(CString &sPort,DWORD &dwBaudRate,
				    BYTE &byDataBits,BYTE &byParity,BYTE &byStopBits)
{
	sPort = m_sPort;
	dwBaudRate = m_dwBaudRate;
	byDataBits = m_byDataBits;
	byParity = m_byParity;
	byStopBits = m_byStopBits;
	return true;
}

void CConfigPort::OnCheckexistport() 
{
	// TODO: Add your control notification handler code here
	CString strPort;
	CString sList;
	if(m_CheckExistPort.GetCheck()==0)
	{
		m_Port.ResetContent();
		for(int i = 0;i<256;i++)
		{
			strPort.Format(_T("COM%d"),i+1);
			m_Port.AddString(strPort);
		}
		if(CB_ERR==m_Port.SelectString(-1,m_sPort))
		{
			m_Port.SelectString(-1,_T("COM1"));
		}
	}
	else
	{
		m_Port.ResetContent();
		GetAllPortList(sList);
		if(CB_ERR==m_Port.SelectString(-1,m_sPort))
		{
			m_Port.SetCurSel(0);
		}
	}
	m_bCheckExistPort = m_CheckExistPort.GetCheck();
}

WORD CConfigPort::GetAllPortList(CString &sList)
{
	CString str;
	HKEY hKey;
	str=_T("HARDWARE\\DEVICEMAP\\SERIALCOMM");
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, str,0,KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) 
	{
		RegCloseKey( hKey );
		return 0;
	}

    TCHAR    achClass[MAX_PATH] = _T("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys;                 // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 

    TCHAR  achValue[MAX_PATH]; 
    DWORD cchValue = MAX_PATH; 
    BYTE  achBuff[80]; 
	DWORD chValue = 60; 
	DWORD type = REG_SZ;
    // Get the class name and the value count. 
    if(RegQueryInfoKey(hKey,        // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime)!=ERROR_SUCCESS)      // last write time 
 	{
		RegCloseKey( hKey );
		return 0;
	}
    if (cValues) 
    {
        for (DWORD j = 0, retValue = ERROR_SUCCESS; 
                j < cValues; j++) 
        { 
            chValue = 60;
			cchValue = 60;
			retValue = RegEnumValue(hKey, j, achValue, 
                &cchValue, 
                NULL, 
                &type,    // &dwType, 
                achBuff, // &bData, 
                &chValue);   // &bcData 
			if(retValue == ERROR_SUCCESS)
			{
				sList += (LPTSTR)(achBuff);
				m_Port.AddString(LPTSTR(achBuff));
			}
		}
	}
	RegCloseKey( hKey );
	return 0;
}

HBRUSH CConfigPort::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
//		pDC->SetBkMode(TRANSPARENT);  //设置背景模式透明
//		pDC->SetTextColor(RGB(255,0,0));//设置文字颜色；
	if(nCtlColor==CTLCOLOR_STATIC||CTLCOLOR_SCROLLBAR  ==nCtlColor||nCtlColor==CTLCOLOR_DLG)
	{
	// TODO: Return a different brush if the default is not desired
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)(m_brHollow.m_hObject);
	}
	return hbr;
}

void CConfigPort::OnBtnok() 
{
	// TODO: Add your control notification handler code here
	m_bOpen = TRUE;
	OnOK();
}

BOOL CConfigPort::GetParamString(CString &sPort,CString &sBaudRate,
		CString &sDataBits,CString &sParity,CString &sStopBits)
{
	sPort = m_sPort;
	sBaudRate = m_sBaudRate;
	sDataBits = m_sDataBits;
	sParity = m_sParity;
	sStopBits = m_sStopBits;
	return true;
}

CString CConfigPort::GetError()
{
	return m_sError;
}

void CConfigPort::OnSaveportconfig() 
{
	// TODO: Add your control notification handler code here
	CString sFilePath;
	sFilePath = STR_ROOT_DIR;
	sFilePath += _T("\\");
	sFilePath += STR_PORT_INI;

	CString sPort,sBaudRate,sStopBits,sDataBits,sParity;
	BYTE byStopBits,byDataBits,byParity;
	DWORD dwBaudRate;
	CString str;
	sPort.Empty();
	m_Port.GetLBText(m_Port.GetCurSel(),sPort);
	m_BaudRate.GetLBText(m_BaudRate.GetCurSel(),sBaudRate);
	dwBaudRate = _ttoi(sBaudRate);
	m_StopBits.GetLBText(m_StopBits.GetCurSel(),sStopBits);
	byStopBits = m_StopBits.GetCurSel();

	m_DataBits.GetLBText(m_DataBits.GetCurSel(),sDataBits);
	byDataBits = _ttoi(sDataBits);
    m_Parity.GetLBText(m_Parity.GetCurSel(),sParity);
	byParity = m_Parity.GetCurSel();

	if(!sPort.IsEmpty())
	{
		m_ini.WriteString(_T("PortConfig"),_T("PortName"),
						sPort,sFilePath);
	}

	m_ini.WriteString(_T("PortConfig"),_T("BaudRate"),
					sBaudRate,sFilePath);

	m_ini.WriteString(_T("PortConfig"),_T("DataBits"),
					sDataBits,sFilePath);

	m_ini.WriteString(_T("PortConfig"),_T("StopBits"),
					sStopBits,sFilePath);
	
	m_ini.WriteString(_T("PortConfig"),_T("Parity"),
					sParity,sFilePath);
	
	str.Format(_T("%d"),byParity);
	m_ini.WriteString(_T("PortConfig"),_T("byParity"),str,sFilePath);
	str.Format(_T("%d"),byStopBits);
	m_ini.WriteString(_T("PortConfig"),_T("byStopBits"),str,sFilePath);
}
