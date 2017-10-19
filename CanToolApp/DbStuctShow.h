#pragma once


// CDbStuctShow 对话框

class CDbStuctShow : public CDialogEx
{
	DECLARE_DYNAMIC(CDbStuctShow)

public:
	CDbStuctShow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDbStuctShow();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATA_STRUC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
