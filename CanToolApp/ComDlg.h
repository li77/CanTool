#pragma once


// CComDlg �Ի���

class CComDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CComDlg)

public:
	CComDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CComDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COM_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
