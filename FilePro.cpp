// FilePro.cpp: implementation of the CFilePro class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FilePro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFilePro::CFilePro()
{

}

CFilePro::~CFilePro()
{

}
/////follow is functon
bool CFilePro::CreateShortCut(LPCTSTR shortCutPath,LPCTSTR fileName )
{
	TCHAR szPath[MAX_PATH];
	TCHAR szFileName[MAX_PATH];
	ZeroMemory(szPath,MAX_PATH);
	ZeroMemory(szFileName,MAX_PATH);
	if(shortCutPath==NULL) return false;
	if(fileName ==NULL )
	{
		::GetModuleFileName(NULL,szFileName,MAX_PATH);
	}
	else
	{
#ifndef UNICODE 
		memcpy(szFileName,fileName,strlen(fileName));
#else
		memcpy(szFileName,fileName,wcslen(fileName)*sizeof(TCHAR));
#endif
	}
	
#ifndef UNICODE 
		memcpy(szPath,shortCutPath,strlen(shortCutPath));
#else
		memcpy(szPath,shortCutPath,wcslen(shortCutPath)*sizeof(TCHAR));
#endif
	TCHAR *p = szFileName;
	for(int i = lstrlen(szFileName);i>0;i--)
	{
		if(*(p+i)==_T('\\'))
			break;
	}
	p = szFileName+i;
	//形成完整的快捷方式数据文件名	
	wsprintf(szPath+lstrlen(szPath),_T("\\%s.lnk"),p);
	
	CreateLink(szFileName,szPath);
	return true;
}

///浏览文件夹
BOOL CFilePro::BrowseForFolder(HWND hwnd,
    LPITEMIDLIST pidlRoot,//浏览开始处的PIDL
	LPITEMIDLIST *ppidlDestination,//浏览结束时所选择的PIDL	
    LPCTSTR lpszTitle)//浏览对话框中的提示文字
{    
	BROWSEINFO BrInfo ;
    ZeroMemory( &BrInfo, sizeof(BrInfo)) ;
    BrInfo.hwndOwner = hwnd ;
	BrInfo.pidlRoot = pidlRoot ;
    BrInfo.lpszTitle = lpszTitle ;
	BrInfo.ulFlags=BIF_RETURNONLYFSDIRS|BIF_EDITBOX|BIF_DONTGOBELOWDOMAIN ;
	BrInfo.lpfn=0;
	BrInfo.lParam=0;
	BrInfo.iImage=0;
    //浏览文件夹
	*ppidlDestination= SHBrowseForFolder(&BrInfo);
    if(*ppidlDestination==NULL)
	{
		return false;
	}
	return TRUE;
}

BOOL CFilePro::BrowseForFolder(
	HWND hwnd,
    LPITEMIDLIST pidlRoot,//浏览开始处的PIDL
	LPTSTR szPath,
    LPCTSTR lpszTitle)//浏览对话框中的提示文字
{
	LPITEMIDLIST pidlDestination;
	BROWSEINFO BrInfo ;
    ZeroMemory( &BrInfo, sizeof(BrInfo)) ;
    BrInfo.hwndOwner = hwnd ;
	BrInfo.pidlRoot = pidlRoot ;
    BrInfo.lpszTitle = lpszTitle ;
	BrInfo.ulFlags=BIF_RETURNONLYFSDIRS|BIF_EDITBOX|BIF_DONTGOBELOWDOMAIN ;
	BrInfo.lpfn=0;
	BrInfo.lParam=0;
	BrInfo.iImage=0;
    //浏览文件夹
	pidlDestination= SHBrowseForFolder(&BrInfo);
    if(pidlDestination==NULL)
	{
		return false;
	}
	// 把PIDL转换为路径名
	if(!SHGetPathFromIDList(pidlDestination, szPath))
	{
		ReleasePIDL(&pidlDestination);
		return false;
	}

	ReleasePIDL(&pidlDestination);
	return TRUE;
}

// 创建快捷方式
BOOL CFilePro::CreateLink(	LPCTSTR szPath,//快捷方式的目标应用程序
	LPCTSTR szLink)//快捷方式的数据文件名（*、lnk）
{
	HRESULT hres;	
	IShellLink *psl;	
	IPersistFile *ppf;
	//创建一个ISellLink实例	
	hres=CoCreateInstance(CLSID_ShellLink,NULL,CLSCTX_INPROC_SERVER,		
								IID_IShellLink,(void**)&psl);
	if(FAILED(hres))	return FALSE;	
	//设置快捷键（此处设为Shift+Ctrl+R)	
	psl->SetHotkey(MAKEWORD('R',HOTKEYF_SHIFT|HOTKEYF_CONTROL));
	//从IShellLink获取其IPersistFile接口
	hres=psl->QueryInterface(IID_IPersistFile,(void**)&ppf);

	if(FAILED(hres))return FALSE;
	//调用IPersistFile::Save
	psl->SetPath(szPath);
	//保存快捷方式的数据文件(*.lnk)	
#ifndef UNICODE	
	WCHAR wsz[MAX_PATH];
	MultiByteToWideChar(CP_ACP,0,szLink,-1,wsz,	MAX_PATH);
	hres=ppf->Save(wsz,STGM_READWRITE);	
#else
	hres=ppf->Save(szLink,STGM_READWRITE);	
#endif
	//释放IPersistFile和IShellLink接口
	ppf->Release();	
	psl->Release();	
	return TRUE;
}

bool CFilePro::CreateShortCutStartMenu(LPCTSTR fileName)
{
	TCHAR szFileName[MAX_PATH];
	TCHAR szPath[MAX_PATH];
	ZeroMemory(szPath,MAX_PATH);
	ZeroMemory(szFileName,MAX_PATH);
	if(fileName==NULL) 
	{
		::GetModuleFileName(NULL,szFileName,MAX_PATH);
	}
	else
	{
#ifndef UNICODE 
		memcpy(szFileName,fileName,strlen(fileName));
#else
		memcpy(szFileName,fileName,wcslen(fileName)*sizeof(TCHAR));
#endif
	}
	LPITEMIDLIST  pidlBeginAt ;
    // 取得开始菜单或桌面的PIDL
    if(NOERROR !=SHGetSpecialFolderLocation( HWND_DESKTOP, 
            CSIDL_COMMON_DESKTOPDIRECTORY , &pidlBeginAt) )
	{
		ReleasePIDL(&pidlBeginAt);
		return false;
	}
	
	if(!SHGetPathFromIDList(pidlBeginAt, szPath))
	{
		ReleasePIDL(&pidlBeginAt);
		return false;
	}
	if(!CreateShortCut(szPath,szFileName )) return false;
	return true;
}
	

bool CFilePro::CreateShortCutDesktop(LPCTSTR fileName)
{
	TCHAR szFileName[MAX_PATH];
	TCHAR szPath[MAX_PATH];
	ZeroMemory(szPath,MAX_PATH);
	ZeroMemory(szFileName,MAX_PATH);
	if(fileName==NULL) 
	{
		::GetModuleFileName(NULL,szFileName,MAX_PATH);
	}
	else
	{
#ifndef UNICODE 
		memcpy(szFileName,fileName,strlen(fileName));
#else
		memcpy(szFileName,fileName,wcslen(fileName)*sizeof(TCHAR));
#endif
	}
	LPITEMIDLIST  pidlBeginAt ;
    // 取得开始菜单或桌面的PIDL
    if(NOERROR !=SHGetSpecialFolderLocation( HWND_DESKTOP, 
            CSIDL_COMMON_DESKTOPDIRECTORY , &pidlBeginAt) )
	{
		ReleasePIDL(&pidlBeginAt);
		return false;
	}
	
	if(!SHGetPathFromIDList(pidlBeginAt, szPath))
	{
		ReleasePIDL(&pidlBeginAt);
		return false;
	}

	ReleasePIDL(&pidlBeginAt);
	if(!CreateShortCut(szPath,szFileName )) return false;
	return true;
}


bool CFilePro::ReleasePIDL(LPITEMIDLIST *ppidl)
{
	LPMALLOC pMalloc;
	//Retrieve a pointer to the shell's IMalloc interface
	if (SUCCEEDED(SHGetMalloc(&pMalloc)))
	{
		pMalloc->Free(*ppidl);
		(void)pMalloc->Release();
		return true;
	}
	return false;
}


bool CFilePro::CreateFolder(LPCTSTR sPath,LPCTSTR sFoldName)
{
	
	return false;
}

bool CFilePro::CreateFolder(LPCTSTR sPath)
{
/*	if(!PathIsDirectory(sPath))
	{
		MessageBox(NULL,_T("无效的路径名"),_T("error"),MB_OK);
		return false;
	}*/
	if(CreateDirectory(sPath,NULL))
		return true;
	return false;
}