#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMySelectDlg �Ի���

class CMySelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMySelectDlg)

public:
	CMySelectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMySelectDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk2();
	CListBox mListBox;
	CTreeCtrl mListTree;
};
