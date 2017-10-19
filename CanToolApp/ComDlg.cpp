// ComDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CanToolApp.h"
#include "ComDlg.h"
#include "afxdialogex.h"
#include"Resource.h"
#include"MainDlg.h"
// CComDlg �Ի���

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


// CComDlg ��Ϣ�������


BOOL CComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//GetDlgItem(IDC_COM_SEL)->;
	((CComboBox*)GetDlgItem(IDC_COM_SEL))->SetCurSel(0);//
	((CComboBox*)GetDlgItem(IDC_COM_RATE))->SetCurSel(9);
	((CComboBox*)GetDlgItem(IDC_COM_DATABIT))->SetCurSel(3);
	((CComboBox*)GetDlgItem(IDC_COM_STOPBIT))->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CComDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//((CMainDlg *)GetParent())->mCOMSel = ((CComboBox*)GetDlgItem(IDC_COM_SEL))->GetCurSel();//
	CString str, strbuf;
	GetDlgItem(IDC_COM_RATE)->GetWindowTextW(str);
	GetDlgItem(IDC_COM_DATABIT)->GetWindowTextW(strbuf);
	str = str + ",n," + strbuf;
	GetDlgItem(IDC_COM_STOPBIT)->GetWindowTextW(strbuf);
	str += "strbuf";
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_Index_int = ((CComboBox*)GetDlgItem(IDC_COMBO_CommSelect))->GetCurSel();//��ǰѡ�е�
	/***********
	GetCurSel() ����:���Եõ��û�ѡ�������б�������ݵ�����ֵ.���ص�ֵ����0��ʼ��,���û��ѡ���κ�ѡ��᷵��-1
	************/
	//���ص��Ǵ򿪵Ķ˿ں�
	int m_Index;
	switch (((CMainDlg *)GetParent())->m_ctrlComm.get_PortOpen())//����򿪻�رմ��ڰ���ʱ�����ݵ�ǰ�Ĵ����Ƿ�򿪾�����Ӧ����
	{
	case 0://��ǰ�����ǹرյģ�����д򿪴��ڲ���
		 m_Index = ((CComboBox*)GetDlgItem(IDC_COM_SEL))->GetCurSel();;//��ǰѡ�е���
		((CMainDlg *)GetParent())->m_ctrlComm.put_CommPort(m_Index + 1);//���Ҫ�򿪴�����Ӧ��ѡ���ĸ�����
		((CMainDlg *)GetParent())->m_ctrlComm.put_PortOpen(TRUE);//�򿪴���
		//UpdateData(FALSE);//���°���״̬

		if (((CMainDlg *)GetParent())->m_ctrlComm.get_PortOpen())//����Ѿ��򿪴��ڣ�
		{
			SetDlgItemText(IDOK, _T("�رմ���"));//���İ�����ʾ
			((CMainDlg *)GetParent())->m_ctrlComm.put_Settings(str);//�����ʱ�˿�����Ĭ�ϲ�����9600����У��λ��8λ���ݣ�1λֹͣ
			((CMainDlg *)GetParent())->m_ctrlComm.put_InputMode(1);//1:��ʾ�Զ����Ʒ�ʽ��ȡ���ݣ�
										//0����ʾ���ı���ʽ��ȡ����
			((CMainDlg *)GetParent())->m_ctrlComm.put_RThreshold(1);//����1 ��ʾÿ�����ڽ��ջ��������ж�������һ���ַ�ʱ������һ���������ݵ�OnComm�¼�
										 //����0 ��ʾ���ݴ����¼���������OnComm�¼���������Ӧ��
			((CMainDlg *)GetParent())->m_ctrlComm.put_InputLen(0);//0: ȱʡֵ����ʾʹMSComm�ؼ���ȡ���ջ������е��������ݡ�
			((CMainDlg *)GetParent())->m_ctrlComm.get_Input();//��Ԥ���������������������
			//UpdateData(FALSE);
		}
		else
			AfxMessageBox(_T("���ڴ�ʧ��"));

		break;
	case 1:
		//��ǰ�����Ǵ򿪵�����йش��ڲ���
		//		m_ctrlComm.SetCommPort(m_Index_int + 1);//���Ҫ�򿪴�����Ӧ��ѡ���ĸ�����
		((CMainDlg *)GetParent())->m_ctrlComm.put_PortOpen(FALSE);
		if (!((CMainDlg *)GetParent())->m_ctrlComm.get_PortOpen())//����Ѿ��رմ��ڣ�
		{
			SetDlgItemText(IDOK, _T("�򿪴���"));
			//UpdateData(FALSE);
		}
		else
			AfxMessageBox(_T("���ڹر�ʧ��"));

		break;
	default:
		AfxMessageBox(_T("cannot open Serial Port"));
		break;
	}
								//�����ʱ����ѡ���Ĭ����ʾCOM1  ��ѡ���ŵ������Ǵ�0��ʼ�ġ�
								  //	m_BaudRate_M.SetCurSel(m_BaudRate);//�����ʱ������ѡ���Ĭ����ʾ9600
								  //	m_Data_Select_M.SetCurSel(m_Data_Select);//�����ʱ����λѡ���Ĭ����ʾ8
								  //	m_StopBit_M.SetCurSel(m_StopBit);//�����ʱֹͣλѡ���Ĭ����ʾN  ��ֹͣλ
								  //	m_ParityCheck_M.SetCurSel(m_ParityCheck);// ��żУ��

	CDialogEx::OnOK();
}


void CComDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
