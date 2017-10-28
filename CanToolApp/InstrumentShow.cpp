// InstrumentShow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CanToolApp.h"
#include "InstrumentShow.h"
#include "afxdialogex.h"


// CInstrumentShow �Ի���

IMPLEMENT_DYNAMIC(CInstrumentShow, CDialogEx)

CInstrumentShow::CInstrumentShow(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INSTRUMENT, pParent)
{

}

CInstrumentShow::~CInstrumentShow()
{

}

void CInstrumentShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ILEDROUNDX1, mInstrumentLED);
	DDX_Control(pDX, IDC_IANGULARGAUGEX1, mInstrumentPanel);
	DDX_Control(pDX, IDC_ISEVENSEGMENTINTEGERX1, mInstrumentSegment);
}


BEGIN_MESSAGE_MAP(CInstrumentShow, CDialogEx)
	ON_MESSAGE(WM_MYSYNCHR,OnMysynchr)
END_MESSAGE_MAP()


// CInstrumentShow ��Ϣ�������


BOOL CInstrumentShow::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	mInstrumentPanel.SetPositionNoEvent(100);
	int num= mInstrumentPanel.get_Position();


	mInstrumentLED.SetActiveNoEvent(false);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


//afx_msg LRESULT CInstrumentShow::OnMysynchr(WPARAM wParam, LPARAM lParam)
//{
//	return 0;
//}


afx_msg LRESULT CInstrumentShow::OnMysynchr(WPARAM wParam, LPARAM lParam)
{
	PMessageNode pM;
	pM=mList.Search(wParam);
	PSignalNode pS;
	pS = pM->pSignalNode;
	int i = 0;
	while (pS)
	{
		if (lParam&(1 >> i) != 0) break;
		pS = pS->nextSignalNode;
	}
//	pS->value
//	mInstrumentLED.SetActiveNoEvent();
	//	MessageBox(L"shoudao2");

	return 0;
}
