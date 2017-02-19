// FilePro.h: interface for the CFilePro class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEPRO_H__F87ED525_DAC9_4CC5_851E_D0DBCB6C9A33__INCLUDED_)
#define AFX_FILEPRO_H__F87ED525_DAC9_4CC5_851E_D0DBCB6C9A33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shlwapi.h"

class CFilePro : public CObject  
{
public:
	CFilePro();
	virtual ~CFilePro();
    //////////////////////////////
private:
	BOOL CreateLink(LPCTSTR szPath,//快捷方式的目标应用程序
	LPCTSTR szLink);//快捷方式的数据文件名（*、lnk）

public:
	///浏览文件夹
	static BOOL BrowseForFolder(
	HWND hwnd,
    LPITEMIDLIST pidlRoot,//浏览开始处的PIDL
	LPITEMIDLIST *ppidlDestination,//浏览结束时所选择的PIDL	
    LPCTSTR lpszTitle);//浏览对话框中的提示文字

	static BOOL BrowseForFolder(
	HWND hwnd,
    LPITEMIDLIST pidlRoot,//浏览开始处的PIDL
	LPTSTR  szPath,
    LPCTSTR lpszTitle = NULL);//浏览对话框中的提示文字
	// 创建快捷方式
	bool CreateShortCut(LPCTSTR shortCutPath,LPCTSTR fileName=NULL);
	bool CreateShortCutStartMenu(LPCTSTR fileName=NULL);
	bool CreateShortCutDesktop(LPCTSTR fileName=NULL);

	static bool ReleasePIDL(LPITEMIDLIST *ppidl);

	static bool CreateFolder(LPCTSTR sPath,LPCTSTR sFoldName);
	static bool CreateFolder(LPCTSTR sPath);
};

#endif // !defined(AFX_FILEPRO_H__F87ED525_DAC9_4CC5_851E_D0DBCB6C9A33__INCLUDED_)
