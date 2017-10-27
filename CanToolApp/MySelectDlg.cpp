// MySelect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MySqlTest.h"
#include "MySelectDlg.h"
#include "afxdialogex.h"


// CMySelectDlg �Ի���

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


// CMySelectDlg ��Ϣ�������


void CMySelectDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CMySelectDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CMySelectDlg::OnBnClickedOk2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::EndDialog(NoMySel);
}
