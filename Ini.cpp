// Ini.cpp: implementation of the CIni class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "serialas.h"
#include "Ini.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIni::CIni()
{

}

CIni::~CIni()
{

}

void CIni::SetFilePath(CString sPath)
{
	m_sFilePath = sPath;
}

CString CIni::GetFilePath() const
{
	return m_sFilePath;
}

BOOL CIni::WriteString( 
		  LPCTSTR lpAppName,  // pointer to section name
		  LPCTSTR lpKeyName,  // pointer to key name
		  LPCTSTR lpString,   // pointer to string to add
		  LPCTSTR lpFileName  // pointer to initialization filename
)
{
	return WritePrivateProfileString(lpAppName,lpKeyName,lpString,lpFileName);
}

BOOL CIni::WriteString( 
		  LPCTSTR lpAppName,  // pointer to section name
		  LPCTSTR lpKeyName,  // pointer to key name
		  LPCTSTR lpString)
{
	return WritePrivateProfileString(lpAppName,lpKeyName,lpString,m_sFilePath);
}

DWORD  CIni::GetString( 
			  LPCTSTR lpAppName,        // points to section name
			  LPCTSTR lpKeyName,        // points to key name
			  LPCTSTR lpDefault,        // points to default string
			  LPTSTR lpReturnedString,  // points to destination buffer
			  DWORD nSize,              // size of destination buffer
			  LPCTSTR lpFileName  
)
{
	return GetPrivateProfileString(lpAppName,lpKeyName,lpDefault,lpReturnedString,nSize,lpFileName);
}

DWORD  CIni::GetString( 
			  LPCTSTR lpAppName,        // points to section name
			  LPCTSTR lpKeyName,        // points to key name
			  LPCTSTR lpDefault,        // points to default string
			  LPTSTR lpReturnedString,  // points to destination buffer
			  DWORD nSize        )
{
	return GetPrivateProfileString(lpAppName,lpKeyName,lpDefault,lpReturnedString,nSize,m_sFilePath);
}

UINT CIni::GetInt(
  LPCTSTR lpAppName,  // address of section name
  LPCTSTR lpKeyName,  // address of key name
  INT nDefault,       // return value if key name is not found
  LPCTSTR lpFileName  // address of initialization filename
)
{
	return GetPrivateProfileInt(lpAppName,lpKeyName,nDefault,lpFileName);
}

UINT CIni::GetInt(
  LPCTSTR lpAppName,  // address of section name
  LPCTSTR lpKeyName,  // address of key name
  INT nDefault     )
{
	return GetPrivateProfileInt(lpAppName,lpKeyName,nDefault,m_sFilePath);
}