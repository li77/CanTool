#pragma once


// CDbStuctShow �Ի���

class CDbStuctShow : public CDialogEx
{
	DECLARE_DYNAMIC(CDbStuctShow)

public:
	CDbStuctShow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDbStuctShow();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATA_STRUC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
