// SetValueDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CanToolApp.h"
#include "SetValueDlg.h"
#include "afxdialogex.h"
#include"MainDlg.h"

// CSetValueDlg 对话框

IMPLEMENT_DYNAMIC(CSetValueDlg, CDialogEx)

CSetValueDlg::CSetValueDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SET_DLG, pParent)
{

}

CSetValueDlg::~CSetValueDlg()
{
}

void CSetValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetValueDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetValueDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetValueDlg 消息处理程序


void CSetValueDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;





	((CMainDlg *)GetParent())->sendComData(str);
	CDialogEx::OnOK();
}
