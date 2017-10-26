// SetValueDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CanToolApp.h"
#include "SetValueDlg.h"
#include "afxdialogex.h"
#include"MainDlg.h"
#include"CanTool_LinkList.h"
#include <string>
#include"CANToolMessage.h"
using std::string;
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
	DDX_Control(pDX, IDC_SET_EDIT, mSetText);
	DDX_Control(pDX, IDC_SET_TREE, mSetTree);
}


BEGIN_MESSAGE_MAP(CSetValueDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetValueDlg::OnBnClickedOk)
	ON_NOTIFY(TVN_SELCHANGED, IDC_SET_TREE, &CSetValueDlg::OnTvnSelchangedSetTree)
END_MESSAGE_MAP()


// CSetValueDlg 消息处理程序


void CSetValueDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	CString strResult;
	GetDlgItem(IDC_SET_EDIT)->GetWindowTextW(str);
	if (str == L"")
	{
		MessageBox(L"您未选中数据！！");
		return;
	}
//	dataManage.setMessage(str)  CW2A(str);
	//memcpy_s(buff,1,CW2A(L""),1);
	string sstr = CW2A(str);
	string sstrff=dataManage.synthesis(sstr);
	strResult =CA2W(sstrff.c_str());
	str = strResult;
	str.Delete(str.GetLength() - 5, 4);
	((CMainDlg *)GetParent())->GetDlgItem(IDC_MONI_RECV)->SetWindowText(str);
	((CMainDlg *)GetParent())->sendComData(strResult);
	CDialogEx::OnOK();
}


BOOL CSetValueDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str;
	hNodeGlobal = mSetTree.InsertItem(L"顶级1", 0, 0);
	PMessageNode pM = mList.mHead->nextMessageNode;
	PSignalNode pS;
	HTREEITEM hNodeChild;
	int i = 0;
	while (pM != NULL)
	{
		pS = pM->pSignalNode;
		if (pS == NULL)
			break;
		str = CA2W(pM->MessageName);
		hNodeChild = mSetTree.InsertItem(str, 0, 0, hNodeGlobal);
		mSetTree.SetItemData(hNodeChild, pM->id);
		i = 0;
		while (pS != NULL)
		{
			str = CA2W(pS->SignalName);
			HTREEITEM hNodeSun = mSetTree.InsertItem(str, 0, 0, hNodeChild);
			mSetTree.SetItemData(hNodeSun, i);
			i++;
			pS = pS->nextSignalNode;
		}
		pM = pM->nextMessageNode;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSetValueDlg::OnTvnSelchangedSetTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM mySelected = mSetTree.GetSelectedItem();
	int seletedData = mSetTree.GetItemData(mySelected);
	PSignalNode pS;
	PMessageNode pM;
	CString  str(L""),str1;
	int i = 0;
	if (mSetTree.GetParentItem(mySelected) == NULL)
		return;
	else if (mSetTree.GetChildItem(mySelected) == NULL)
	{
		pM = mList.Search(mSetTree.GetItemData(mSetTree.GetParentItem(mySelected)));
	}
	else
	{
		pM = mList.Search(mSetTree.GetItemData(mySelected));
	}
	pS = pM->pSignalNode;
	char buff[2000]="",buff1[20];
	string strbuff;
	str1.Format(L"ID : %d\r\nDLC : %d\r\ntime_interval : 0  ms [0 ,65535]\r\n", pM->id, pM->DLC-48);
	//str += str1;
	while (pS)
	{
		/*if (pS->minValue - (int)pS->minValue == 0)
			sprintf_s(buff, "%d", (int)pS->minValue);
		else
			_gcvt_s(buff, pS->minValue, 6);
		if (pS->maxValue - (int)pS->maxValue == 0)
			sprintf_s(buff1, "%d", (int)pS->maxValue);
		else
			_gcvt_s(buff1, pS->maxValue, 6);
		str1.Format( L"%s : 0 %s 取值范围 [%s,%s]\r\n", pS->SignalName, pS->units, buff1, buff1);
		str += str1;*/
		strcat_s(buff, pS->SignalName);
		strcat_s(buff, "        : 0 ");
		strcat_s(buff, pS->units);
		strcat_s(buff, "取值范围 [ ");
		if (pS->minValue - (int)pS->minValue == 0)
			sprintf_s(buff1, "%d", (int)pS->minValue);
		else
			_gcvt_s(buff1, pS->minValue, 6);
		strcat_s(buff, buff1);
		strcat_s(buff, ", ");
		if (pS->maxValue - (int)pS->maxValue == 0)
			sprintf_s(buff1, "%d", (int)pS->maxValue);
		else
			_gcvt_s(buff1, pS->maxValue, 6);
		strcat_s(buff, buff1);
		strcat_s(buff, " ]\r\n");
		pS = pS->nextSignalNode;
	}
	GetDlgItem(IDC_SET_EDIT)->SetWindowTextW(str1+CA2W(buff));
	//GetDlgItem(IDC_SET_EDIT)->SetWindowTextW(str);



	*pResult = 0;
}
