
// MFCApplication2-cj.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCApplication2cjApp: 
// �йش����ʵ�֣������ MFCApplication2-cj.cpp
//

class CMFCApplication2cjApp : public CWinApp
{
public:
	CMFCApplication2cjApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication2cjApp theApp;