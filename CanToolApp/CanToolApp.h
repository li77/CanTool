
// CanToolApp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCanToolApp: 
// �йش����ʵ�֣������ CanToolApp.cpp
//

class CCanToolApp : public CWinApp
{
public:
	CCanToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCanToolApp theApp;