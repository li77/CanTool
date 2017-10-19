// DbStuctShow.cpp : 实现文件
//

#include "stdafx.h"
#include "CanToolApp.h"
#include "DbStuctShow.h"
#include "afxdialogex.h"


// CDbStuctShow 对话框

IMPLEMENT_DYNAMIC(CDbStuctShow, CDialogEx)

CDbStuctShow::CDbStuctShow(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DATA_STRUC, pParent)
{

}

CDbStuctShow::~CDbStuctShow()
{
}

void CDbStuctShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDbStuctShow, CDialogEx)
END_MESSAGE_MAP()


// CDbStuctShow 消息处理程序
