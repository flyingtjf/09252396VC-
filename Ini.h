// Ini.h: interface for the CIni class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INI_H__2F085719_1376_4BD1_809D_D1693D9119F8__INCLUDED_)
#define AFX_INI_H__2F085719_1376_4BD1_809D_D1693D9119F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIni : public CObject  
{
public:
	CIni();
	virtual ~CIni();
	void SetFilePath(CString sPath);
	CString GetFilePath() const;
	BOOL WriteString( 
		  LPCTSTR lpAppName,  // pointer to section name
		  LPCTSTR lpKeyName,  // pointer to key name
		  LPCTSTR lpString,   // pointer to string to add
		  LPCTSTR lpFileName  );
	BOOL WriteString( 
		  LPCTSTR lpAppName,  // pointer to section name
		  LPCTSTR lpKeyName,  // pointer to key name
		  LPCTSTR lpString );
	
	DWORD GetString( 
			  LPCTSTR lpAppName,        // points to section name
			  LPCTSTR lpKeyName,        // points to key name
			  LPCTSTR lpDefault,        // points to default string
			  LPTSTR lpReturnedString,  // points to destination buffer
			  DWORD nSize,              // size of destination buffer
			  LPCTSTR lpFileName  );
	DWORD  GetString( 
			  LPCTSTR lpAppName,        // points to section name
			  LPCTSTR lpKeyName,        // points to key name
			  LPCTSTR lpDefault,        // points to default string
			  LPTSTR lpReturnedString,  // points to destination buffer
			  DWORD nSize         );
	UINT   GetInt(
				  LPCTSTR lpAppName,  // address of section name
				  LPCTSTR lpKeyName,  // address of key name
				  INT nDefault,       // return value if key name is not found
				  LPCTSTR lpFileName  // address of initialization filename
				);
	UINT   GetInt(
				  LPCTSTR lpAppName,  // address of section name
				  LPCTSTR lpKeyName,  // address of key name
				  INT nDefault);
private:

	CString m_sFilePath;
};

#endif // !defined(AFX_INI_H__2F085719_1376_4BD1_809D_D1693D9119F8__INCLUDED_)
