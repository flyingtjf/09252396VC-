// SerialPort.cpp: implementation of the CSerialPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "serialas.h"
#include "SerialPort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSerialPort::CSerialPort()
{
   m_hCom = INVALID_HANDLE_VALUE;
   m_sError.Empty();
   m_dwError = 0;
}

CSerialPort::~CSerialPort()
{

}

HANDLE CSerialPort::OpenPort(LPCTSTR sPort,DWORD dwBaudRate,BYTE byDataBits,
				BYTE byParity,BYTE byStopBits,BOOL bSynchronization)
{
	bool bFlagTry = FALSE; //ָʾ�Ƿ������˳���try��
	TCHAR szPort[10] = {0};
	_tcscpy(szPort,_T("\\\\.\\"));
	_tcscat(szPort,sPort);

	DWORD dwFlag = 0;
	if(bSynchronization)
	{
		dwFlag = 0;
	}
	else
	{
		dwFlag = FILE_FLAG_OVERLAPPED;
	}
	if(m_hCom!=INVALID_HANDLE_VALUE)
	{
		::CloseHandle(m_hCom);
		m_hCom=INVALID_HANDLE_VALUE;
	}
	__try
	{
	m_hCom = CreateFile(szPort,
							GENERIC_READ|GENERIC_WRITE,
							0,						//����ģʽ
							NULL,
							OPEN_EXISTING,
							dwFlag,						
							NULL);

	if(m_hCom==INVALID_HANDLE_VALUE)
	{
		__leave;
	}

	if(SetupComm(m_hCom,2048,1024)==0)
	{
		__leave;
	}

	if(PurgeComm( m_hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR 

		| PURGE_RXCLEAR )==0)
	{
		__leave;
	}
		
	DCB dcb;                         //����dcb����

	if(!GetCommState(m_hCom,&dcb))
	{
		__leave;
	}
	
	COMMTIMEOUTS ct;
	GetCommTimeouts(m_hCom, &ct);
	ct.ReadIntervalTimeout = 500;
	ct.ReadTotalTimeoutConstant = 1000;
	ct.ReadTotalTimeoutMultiplier = 1000;
	ct.WriteTotalTimeoutConstant = 0;
	ct.WriteTotalTimeoutMultiplier = 0;

	if(!SetCommTimeouts(m_hCom, &ct))
	{
		__leave;
	}

	dcb.Parity = byParity;				//���У�鷽ʽ
	if(byParity!=NOPARITY)
	{
		dcb.fBinary = TRUE;				//����У��
	}
	dcb.BaudRate = dwBaudRate;			//���ͨ������
	dcb.ByteSize = byDataBits;			//����λ��
	dcb.StopBits = byStopBits;			//ֹͣλ

	dcb.fOutxCtsFlow = FALSE;			//��������
	dcb.fOutxDsrFlow = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;

	// ���趨�Ĳ���ֵ���ڸô���
	if(!SetCommState(m_hCom,&dcb))
	{
		__leave;
	}
	bFlagTry = TRUE;
	}//end try
	__finally
	{
//		if(AbnormalTermination())
		if(!bFlagTry)
		{
			m_dwError = GetLastError();
			if(m_hCom!=INVALID_HANDLE_VALUE)
			{
				::CloseHandle(m_hCom);
				m_hCom=INVALID_HANDLE_VALUE;
			}
		}
	}
	return m_hCom;
}


BOOL  CSerialPort::ClosePort()
{
	if(CloseHandle(m_hCom))
	{
		m_hCom = INVALID_HANDLE_VALUE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CString CSerialPort::GetError()
{
	return GetErrorDesc(m_dwError);
}

DWORD CSerialPort::GetErrorCode() const
{
	return m_dwError;
}

CString CSerialPort::GetErrorDesc(DWORD dwError)
{
	CString strResult;
	HLOCAL hlocal = NULL; //malloc a result buffer
	BOOL fOk = FormatMessage
	(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 
	NULL, dwError, MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), 
	(PTSTR) &hlocal, 0, NULL);
	if (!fOk) 
	{
		//check if it is netError
		//remember do not load the dll or module the dll loaded
		HMODULE hDll = LoadLibraryEx(TEXT("netmsg.dll"), NULL, DONT_RESOLVE_DLL_REFERENCES);
		if (hDll != NULL) 
		{
			fOk =FormatMessage(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_FROM_SYSTEM,
			hDll, dwError, 
			MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), 
			(PTSTR) &hlocal, 0, NULL);
			FreeLibrary(hDll);
		}
	}
//	if(!fOk)
//	return GetSocketErrorDesc(dwError);
	strResult.Format(_T("������� : %ld\n������Ϣ: %s"),dwError,hlocal);
	LocalFree(hlocal);
	return strResult;
}
