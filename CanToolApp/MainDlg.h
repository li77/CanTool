
// MainDlg.h : ͷ�ļ�
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
// CMainDlg �Ի���
/*
{





}
*/
class CMainDlg : public CDialogEx
{
// ����
public:
	CMainDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DLG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CInstrumentShow *mInstrumentDlg;
	CCurveDlg *mCurveDlg;
	CImageList mImageList;
	CString mCOMstr;
	int mCOMSel;
// ʵ��
protected:
	HICON m_hIcon;
	CCom_led m_comLed;
	CString dbDir[10];
	

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg LRESULT OnMyMsgHandler(WPARAM w, LPARAM l);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedComMana();
	afx_msg void OnBnClickedLoadDb();
	afx_msg void OnBnClickedClearDb();
	afx_msg void OnBnClickedShowDbstruc();
	afx_msg void OnBnClickedInstrumentPan();
	afx_msg void OnBnClickedShowCurves();
	afx_msg void OnBnClickedSetValue();
	CTreeCtrl mMainTree;
	CListCtrl mMainList;
	CString m_strRXData;//�յ����ַ���
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
};
