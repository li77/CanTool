// SetValueDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CanToolApp.h"
#include "SetValueDlg.h"
#include "afxdialogex.h"
#include"MainDlg.h"

// CSetValueDlg �Ի���

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


// CSetValueDlg ��Ϣ�������


void CSetValueDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;





	((CMainDlg *)GetParent())->sendComData(str);
	CDialogEx::OnOK();
}
