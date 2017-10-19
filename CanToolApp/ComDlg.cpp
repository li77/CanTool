// ComDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CanToolApp.h"
#include "ComDlg.h"
#include "afxdialogex.h"
#include"Resource.h"
#include"MainDlg.h"
// CComDlg 对话框

IMPLEMENT_DYNAMIC(CComDlg, CDialogEx)

CComDlg::CComDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COM_DLG, pParent)
{

}

CComDlg::~CComDlg()
{
}

void CComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CComDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CComDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CComDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CComDlg 消息处理程序


BOOL CComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//GetDlgItem(IDC_COM_SEL)->;
	((CComboBox*)GetDlgItem(IDC_COM_SEL))->SetCurSel(0);//
	((CComboBox*)GetDlgItem(IDC_COM_RATE))->SetCurSel(9);
	((CComboBox*)GetDlgItem(IDC_COM_DATABIT))->SetCurSel(3);
	((CComboBox*)GetDlgItem(IDC_COM_STOPBIT))->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CComDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//((CMainDlg *)GetParent())->mCOMSel = ((CComboBox*)GetDlgItem(IDC_COM_SEL))->GetCurSel();//
	CString str, strbuf;
	GetDlgItem(IDC_COM_RATE)->GetWindowTextW(str);
	GetDlgItem(IDC_COM_DATABIT)->GetWindowTextW(strbuf);
	str = str + ",n," + strbuf;
	GetDlgItem(IDC_COM_STOPBIT)->GetWindowTextW(strbuf);
	str += "strbuf";
	// TODO: 在此添加控件通知处理程序代码
	//m_Index_int = ((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->GetCurSel();//当前选中的
	/***********
	GetCurSel() 函数:用以得到用户选中下拉列表框中数据的索引值.返回的值是重0开始的,如果没有选择任何选项将会返回-1
	************/
	//返回的是打开的端口号
	int m_Index;
	switch (((CMainDlg *)GetParent())->m_ctrlComm.get_PortOpen())//点击打开或关闭串口按键时，根据当前的串口是否打开经行相应操作
	{
	case 0://当前串口是关闭的，则进行打开串口操作
		 m_Index = ((CComboBox*)GetDlgItem(IDC_COM_SEL))->GetCurSel();;//当前选中的行
		((CMainDlg *)GetParent())->m_ctrlComm.put_CommPort(m_Index + 1);//如果要打开串口则应先选择哪个串口
		((CMainDlg *)GetParent())->m_ctrlComm.put_PortOpen(TRUE);//打开串口
		//UpdateData(FALSE);//更新按键状态

		if (((CMainDlg *)GetParent())->m_ctrlComm.get_PortOpen())//如过已经打开串口，
		{
			SetDlgItemText(IDOK, _T("关闭串口"));//更改按键提示
			((CMainDlg *)GetParent())->m_ctrlComm.put_Settings(str);//打开软件时端口设置默认波特率9600，无校验位，8位数据，1位停止
			((CMainDlg *)GetParent())->m_ctrlComm.put_InputMode(1);//1:表示以二进制方式捡取数据；
										//0：表示以文本方式捡取数据
			((CMainDlg *)GetParent())->m_ctrlComm.put_RThreshold(1);//参数1 表示每当串口接收缓冲区中有多余或等于一个字符时将引发一个接收数据的OnComm事件
										 //参数0 表示数据传输事件不会引发OnComm事件，即不响应。
			((CMainDlg *)GetParent())->m_ctrlComm.put_InputLen(0);//0: 缺省值。表示使MSComm控件读取接收缓冲区中的所有内容。
			((CMainDlg *)GetParent())->m_ctrlComm.get_Input();//先预读缓冲区以清除残留数据
			//UpdateData(FALSE);
		}
		else
			AfxMessageBox(_T("串口打开失败"));

		break;
	case 1:
		//当前串口是打开的则进行关串口操作
		//		m_ctrlComm.SetCommPort(m_Index_int + 1);//如果要打开串口则应先选择哪个串口
		((CMainDlg *)GetParent())->m_ctrlComm.put_PortOpen(FALSE);
		if (!((CMainDlg *)GetParent())->m_ctrlComm.get_PortOpen())//如果已经关闭串口，
		{
			SetDlgItemText(IDOK, _T("打开串口"));
			//UpdateData(FALSE);
		}
		else
			AfxMessageBox(_T("串口关闭失败"));

		break;
	default:
		AfxMessageBox(_T("cannot open Serial Port"));
		break;
	}
								//打开软件时串口选择框默认显示COM1  子选项编号的排序是从0开始的。
								  //	m_BaudRate_M.SetCurSel(m_BaudRate);//打开软件时波特率选择框默认显示9600
								  //	m_Data_Select_M.SetCurSel(m_Data_Select);//打开软件时数据位选择框默认显示8
								  //	m_StopBit_M.SetCurSel(m_StopBit);//打开软件时停止位选择框默认显示N  无停止位
								  //	m_ParityCheck_M.SetCurSel(m_ParityCheck);// 奇偶校验

	CDialogEx::OnOK();
}


void CComDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
