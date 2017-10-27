// MySelect.cpp : 实现文件
//

#include "stdafx.h"
#include "MySqlTest.h"
#include "MySelectDlg.h"
#include "afxdialogex.h"


// CMySelectDlg 对话框

IMPLEMENT_DYNAMIC(CMySelectDlg, CDialogEx)

CMySelectDlg::CMySelectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SELECT, pParent)
{

}

CMySelectDlg::~CMySelectDlg()
{
}

void CMySelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mListBox);
	DDX_Control(pDX, IDC_TREE1, mListTree);
}


BEGIN_MESSAGE_MAP(CMySelectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMySelectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMySelectDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK2, &CMySelectDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CMySelectDlg 消息处理程序


void CMySelectDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMySelectDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMySelectDlg::OnBnClickedOk2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::EndDialog(NoMySel);
}
