#pragma once
#include "istripchartx1.h"


// CCurveDlg �Ի���

class CCurveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCurveDlg)

public:
	CCurveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCurveDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CURVE_SHOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CIstripchartx1 mCurveShow;
	virtual BOOL OnInitDialog();
protected:
//	afx_msg LRESULT OnMysynchr(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMysynchr(WPARAM wParam, LPARAM lParam);
};
