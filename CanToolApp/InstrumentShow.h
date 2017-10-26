#pragma once
#include "com_led.h"
#include "iangulargaugex1.h"
#include "isevensegmentintegerx1.h"
#include"CanTool_LinkList.h"
#include"CANToolMessage.h"

// CInstrumentShow �Ի���

class CInstrumentShow : public CDialogEx
{
	DECLARE_DYNAMIC(CInstrumentShow)

public:
	CInstrumentShow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInstrumentShow();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSTRUMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CCom_led mInstrumentLED;
	CIangulargaugex1 mInstrumentPanel;
	CIsevensegmentintegerx1 mInstrumentSegment;
	virtual BOOL OnInitDialog();
protected:
//	afx_msg LRESULT OnMysynchr(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMysynchr(WPARAM wParam, LPARAM lParam);
};
