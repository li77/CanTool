#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSetValueDlg 对话框

class CSetValueDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetValueDlg)

public:
	CSetValueDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetValueDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit mSetText;
	CTreeCtrl mSetTree;
	HTREEITEM hNodeGlobal;
	afx_msg void OnTvnSelchangedSetTree(NMHDR *pNMHDR, LRESULT *pResult);
};
