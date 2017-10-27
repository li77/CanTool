#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMySelectDlg 对话框

class CMySelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMySelectDlg)

public:
	CMySelectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMySelectDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk2();
	CListBox mListBox;
	CTreeCtrl mListTree;
};
