
// MainDlg.h : 头文件
//

#pragma once

#include "com_led.h"
#include "InstrumentShow.h"
#include "CurveDlg.h"
#include "SetValueDlg.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "mscomm1.h"
#include"CanTool_LinkList.h"
#include <string>
#include"CANToolMessage.h"
// CMainDlg 对话框
/*
{





}
*/
class CMainDlg : public CDialogEx
{
// 构造
public:
	CMainDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DLG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CInstrumentShow *mInstrumentDlg;
	CCurveDlg *mCurveDlg;
	CImageList mImageList;
	CString mCOMstr;
	int mCOMSel;
	COleDateTime currentRecordTime ;
	LARGE_INTEGER   t1, t2, tc;
// 实现
protected:
	HICON m_hIcon;
	CCom_led m_comLed;
	CString dbDir[10];
	

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg LRESULT OnMyMsgHandler(WPARAM w, LPARAM l);
	afx_msg void OnBnClickedComMana();
	afx_msg void OnBnClickedLoadDb();
	afx_msg void OnBnClickedClearDb();
	afx_msg void OnBnClickedShowDbstruc();
	afx_msg void OnBnClickedInstrumentPan();
	afx_msg void OnBnClickedShowCurves();
	afx_msg void OnBnClickedSetValue();
	CTreeCtrl mMainTree;
	CListCtrl mMainList;
	CString m_strRXData;//收到的字符串
	HTREEITEM hTreeNodeGlobal;
	void sendComData(CString str);
	afx_msg void OnClickMainTree(NMHDR *pNMHDR, LRESULT *pResult);
private:
	void ConsistentParentCheck(HTREEITEM hTreeItem);
	void ConsistentChildCheck(HTREEITEM hTreeItem);
public:
	afx_msg void OnSelchangedMainTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawMainTree(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic mCMessageHead;
	afx_msg void OnLvnItemchangedMainList(NMHDR *pNMHDR, LRESULT *pResult);
	CMscomm1 m_ctrlComm;
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	void OnOncommMscomm1();
	
	void updateMainDlg();
	int refreshMainListCtl(unsigned int id);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	__int32 getMSec();
	UINT getSelectID();
	CListBox mComOutput;
	CListBox mComInput;
	void comRecieveTest(CString mRXData);
	afx_msg void OnBnClickedGetVersion();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
