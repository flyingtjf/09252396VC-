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
	BOOL CreateLink(LPCTSTR szPath,//��ݷ�ʽ��Ŀ��Ӧ�ó���
	LPCTSTR szLink);//��ݷ�ʽ�������ļ�����*��lnk��

public:
	///����ļ���
	static BOOL BrowseForFolder(
	HWND hwnd,
    LPITEMIDLIST pidlRoot,//�����ʼ����PIDL
	LPITEMIDLIST *ppidlDestination,//�������ʱ��ѡ���PIDL	
    LPCTSTR lpszTitle);//����Ի����е���ʾ����

	static BOOL BrowseForFolder(
	HWND hwnd,
    LPITEMIDLIST pidlRoot,//�����ʼ����PIDL
	LPTSTR  szPath,
    LPCTSTR lpszTitle = NULL);//����Ի����е���ʾ����
	// ������ݷ�ʽ
	bool CreateShortCut(LPCTSTR shortCutPath,LPCTSTR fileName=NULL);
	bool CreateShortCutStartMenu(LPCTSTR fileName=NULL);
	bool CreateShortCutDesktop(LPCTSTR fileName=NULL);

	static bool ReleasePIDL(LPITEMIDLIST *ppidl);

	static bool CreateFolder(LPCTSTR sPath,LPCTSTR sFoldName);
	static bool CreateFolder(LPCTSTR sPath);
};

#endif // !defined(AFX_FILEPRO_H__F87ED525_DAC9_4CC5_851E_D0DBCB6C9A33__INCLUDED_)
