#pragma once


// CSetValueDlg �Ի���

class CSetValueDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetValueDlg)

public:
	CSetValueDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetValueDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};