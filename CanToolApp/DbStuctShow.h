#pragma once
#include "afxcmn.h"
#include"CanTool_LinkList.h"
#include "ColorListCtrl.h"
#include "iledmatrixx1.h"
#include"resource.h"
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
public:
	char bitStart=16;
	char bitNum=12;
	BOOL isSmallEndian=0;
	CTreeCtrl mDBTree;
	HTREEITEM hNodeGlobal;
	virtual BOOL OnInitDialog();
//	afx_msg void OnLvnItemchangedStrucList(NMHDR *pNMHDR, LRESULT *pResult);
//	CColorListCtrl mColorListCtl;
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CIledmatrixx1 mLEDMatrix;
	HANDLE mLEDthread;
	afx_msg void OnDestroy();
	afx_msg void OnTvnSelchangedDbTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeBitstart();
	afx_msg void OnEnKillfocusBitstart();
	afx_msg void OnEnChangeBitnum();
	afx_msg void OnEnChangeCoding();
};
extern void ThreadFunc(CDbStuctShow *pstructShow);