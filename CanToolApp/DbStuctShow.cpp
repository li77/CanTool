// DbStuctShow.cpp : 实现文件
//

#include "stdafx.h"
#include "CanToolApp.h"
#include "DbStuctShow.h"
#include "afxdialogex.h"
using std::string;

// CDbStuctShow 对话框

IMPLEMENT_DYNAMIC(CDbStuctShow, CDialogEx)

CDbStuctShow::CDbStuctShow(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DATA_STRUC, pParent)
{

}

CDbStuctShow::~CDbStuctShow()
{
}

void CDbStuctShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DB_TREE, mDBTree);
	//  DDX_Control(pDX, IDC_STRUC_LIST, mColorListCtl);
	DDX_Control(pDX, IDC_ILEDMATRIXX1, mLEDMatrix);
}


BEGIN_MESSAGE_MAP(CDbStuctShow, CDialogEx)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_STRUC_LIST, &CDbStuctShow::OnLvnItemchangedStrucList)
ON_BN_CLICKED(IDC_BUTTON1, &CDbStuctShow::OnBnClickedButton1)
ON_WM_MOUSEMOVE()
ON_WM_DESTROY()
ON_NOTIFY(TVN_SELCHANGED, IDC_DB_TREE, &CDbStuctShow::OnTvnSelchangedDbTree)
ON_EN_CHANGE(IDC_BITSTART, &CDbStuctShow::OnEnChangeBitstart)
ON_EN_KILLFOCUS(IDC_BITSTART, &CDbStuctShow::OnEnKillfocusBitstart)
ON_EN_CHANGE(IDC_BITNUM, &CDbStuctShow::OnEnChangeBitnum)
ON_EN_CHANGE(IDC_CODING, &CDbStuctShow::OnEnChangeCoding)
END_MESSAGE_MAP()


// CDbStuctShow 消息处理程序


BOOL CDbStuctShow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//把数据库载入到mDBTree
	CString str;
	 hNodeGlobal = mDBTree.InsertItem(L"顶级1", 0, 0);
	 PMessageNode pM = mList.mHead->nextMessageNode;
	 PSignalNode pS;
	 HTREEITEM hNodeChild;
	 int i = 0;
	 while (pM != NULL)
	 {
		 pS = pM->pSignalNode;
		 if (pS == NULL)
			 break;
		  str = CA2W(pM->MessageName);
		  hNodeChild = mDBTree.InsertItem(str, 0, 0, hNodeGlobal);
		  mDBTree.SetItemData(hNodeChild, pM->id);
		  i = 0;
		  while (pS!=NULL)
		  {
			  str = CA2W(pS->SignalName);
			  HTREEITEM hNodeSun =mDBTree.InsertItem(str, 0, 0, hNodeChild);
			  mDBTree.SetItemData(hNodeSun, i);
			  i++;
			  pS=pS->nextSignalNode;
		  }
		pM= pM->nextMessageNode;
	 }

	//mLEDMatrix.SetIndicatorActive(7, 7, 1);
	 DWORD  threadId;
	  mLEDthread = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)ThreadFunc,this,0, &threadId);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDbStuctShow::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
//	mColorListCtl.SetColor(0, 4, RGB(125, 125, 125));
  // Invalidate(TRUE);
	//CRect rec= mColorListCtl.GetItemRect(, );
	//CRect rec;
	//mColorListCtl.GetItemRect(0,&rec, LVIR_LABEL);
	//CBrush brush;
	//CDC *m_pDC = GetDC();
	//brush.CreateSolidBrush(RGB(255,0,0));
	//CBrush* oldBr = m_pDC->SelectObject(&brush);
	//m_pDC->Rectangle(210+40,60+20,290, 100);
	//m_pDC->SelectObject(oldBr);
	//ReleaseDC(m_pDC);
	//mColorListCtl.
}


//void CDbStuctShow::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	//char fd[30];
//	//sprintf_s(fd, "x=%d, y=%d", point.x, point.y);
//
//	//SetWindowText(CA2W(fd));
//	CDialogEx::OnMouseMove(nFlags, point);
//}


void ThreadFunc(CDbStuctShow *pstructShow)
{
	char i;//记录流动到哪一位了
	char row, col;
	BOOL isSmallEndian;
	char bitStart, bitNum;
	while (1)//灯自高位向低位流动
	{
		isSmallEndian = pstructShow->isSmallEndian;
		bitStart = pstructShow->bitStart;
		bitNum = pstructShow->bitNum;
		if (pstructShow->isSmallEndian == 1)//小端     左下-》右上
		{
			row = (bitStart + bitNum-1) / 8 ;
			col = 7 - (bitStart + bitNum-1) % 8;
			for (i = 0; i < bitNum; i++)
			{
				//得到开始显示的位置
				pstructShow->mLEDMatrix.SetIndicatorActive(row, col, 1);
				col++;
				row -= col > 7 ? 1 : 0;
				col = col % 8;
				Sleep(100);
			}
			Sleep(200);
			row = (bitStart + bitNum-1) / 8 ;
			col = 7 - (bitStart + bitNum-1) % 8;
			for (i = 0; i < bitNum; i++)
			{
				//得到开始显示的位置
				pstructShow->mLEDMatrix.SetIndicatorActive(row, col, 0);
				col++;
				row -= col > 7 ? 1 : 0;
				col = col % 8;
			}
		}
		else//左上-》右下
		{
			row = bitStart  / 8;
			col = 7 - bitStart % 8;
			for (i = 0; i < bitNum; i++)
			{
				//得到开始显示的位置
				pstructShow->mLEDMatrix.SetIndicatorActive(row, col, 1);
				col++;
				row += col > 7 ? 1 : 0;
				col = col % 8;
				Sleep(100);
			}
			Sleep(200);
			row = bitStart / 8;
			col = 7 - bitStart  % 8;
			for (i = 0; i < bitNum; i++)
			{
				//得到开始显示的位置
				pstructShow->mLEDMatrix.SetIndicatorActive(row, col, 0);
				col++;
				row += col > 7 ? 1 : 0;
				col = col % 8;
			}


		}
	
	}
}


void CDbStuctShow::OnDestroy()
{
	TerminateThread(mLEDthread, 0);
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


void CDbStuctShow::OnTvnSelchangedDbTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM mySelected = mDBTree.GetSelectedItem();
	int seletedData = mDBTree.GetItemData(mySelected);
	PSignalNode pS;
	CString  buff;
	wchar_t  buff1[20];
	int i=0;
	if (mDBTree.GetChildItem(mySelected) == NULL)
	{
	//	
		if (mDBTree.GetParentItem(mySelected) == NULL)  return;
		pS = mList.Search(mDBTree.GetItemData(mDBTree.GetParentItem(mySelected)))->pSignalNode;
		while (seletedData != i  && pS!=NULL)
		{
			pS = pS->nextSignalNode;
			i++;
		}
		bitNum = pS->bitNum;
		bitStart = pS->startBit;
		isSmallEndian = pS->Endian[0]-0x30;
		//填充字符串
		buff = L"信号名字：";
		buff += CA2W(pS->SignalName);
		buff += L"  ,起始位：";
		_itow_s(pS->startBit, buff1, 10);
		buff += buff1;
		buff += L"   ,位数目：";
		_itow_s(pS->bitNum, buff1, 10);
		buff += buff1;
		buff += L"   ,格式：";
		_itow_s(pS->Endian[0]-0x30, buff1, 10);
		buff = buff+buff1+L'+';
		GetDlgItem(IDC_STATIC_SHOW)->SetWindowTextW(buff);
	}
	*pResult = 0;
}


void CDbStuctShow::OnEnChangeBitstart()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	BOOL flag;
	bitStart = GetDlgItemInt(IDC_BITSTART, &flag, true);
	bitNum = GetDlgItemInt(IDC_BITNUM, &flag, true);
	isSmallEndian = GetDlgItemInt(IDC_CODING, &flag, true);
	
	// TODO:  在此添加控件通知处理程序代码
}


void CDbStuctShow::OnEnKillfocusBitstart()
{
	

	
}


void CDbStuctShow::OnEnChangeBitnum()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	BOOL flag;
	bitStart = GetDlgItemInt(IDC_BITSTART, &flag, true);
	bitNum = GetDlgItemInt(IDC_BITNUM, &flag, true);
	isSmallEndian = GetDlgItemInt(IDC_CODING, &flag, true);
	// TODO:  在此添加控件通知处理程序代码
}


void CDbStuctShow::OnEnChangeCoding()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	BOOL flag;
	bitStart = GetDlgItemInt(IDC_BITSTART, &flag, true);
	bitNum = GetDlgItemInt(IDC_BITNUM, &flag, true);
	isSmallEndian = GetDlgItemInt(IDC_CODING, &flag, true);
	// TODO:  在此添加控件通知处理程序代码
}
