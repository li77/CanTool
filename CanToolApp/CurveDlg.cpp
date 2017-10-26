// CurveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CanToolApp.h"
#include "CurveDlg.h"
#include "afxdialogex.h"


// CCurveDlg 对话框

IMPLEMENT_DYNAMIC(CCurveDlg, CDialogEx)

CCurveDlg::CCurveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CURVE_SHOW, pParent)
{

}

CCurveDlg::~CCurveDlg()
{
}

void CCurveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ISTRIPCHARTX1, mCurveShow);
}


BEGIN_MESSAGE_MAP(CCurveDlg, CDialogEx)
	ON_MESSAGE(WM_MYSYNCHR, OnMysynchr)
END_MESSAGE_MAP()


// CCurveDlg 消息处理程序


BOOL CCurveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	double Chart2TimeCounter = 0;
	COLORREF color = RGB(0, 255, 0);
	CString str("first");
	mCurveShow.AddChannel(str, color, 1, 1);
	for (int i = 0; i < 20; i++) {
		mCurveShow.SetXAxisMinMax(0, 100);
		mCurveShow.AddIndexTime(Chart2TimeCounter);
		mCurveShow.SetChannelData(0, -1, (rand() / (double)RAND_MAX) * 100);
		mCurveShow.SetChannelData(1, -1, (rand() / (double)RAND_MAX) * 100);
		Chart2TimeCounter = Chart2TimeCounter + 10; //100ms or 0.1 sec
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//afx_msg LRESULT CCurveDlg::OnMysynchr(WPARAM wParam, LPARAM lParam)
//{
//
//	return 0;
//}


afx_msg LRESULT CCurveDlg::OnMysynchr(WPARAM wParam, LPARAM lParam)
{
	
	
	SetWindowText(L"消息为：sdfd");
	//MessageBox(L"shoudao1");
	return 0;
}
