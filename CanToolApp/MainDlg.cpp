
// MainDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "CanToolApp.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include"DbStuctShow.h"
#include"ComDlg.h"
#include"CanTool_LinkList.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg 对话框



CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_DLG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_LED, m_comLed);
	DDX_Control(pDX, IDC_MAIN_TREE, mMainTree);
	DDX_Control(pDX, IDC_MAIN_LIST, mMainList);
	DDX_Control(pDX, IDC_MESSAGEHEAD, mCMessageHead);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COM_MANA, &CMainDlg::OnBnClickedComMana)
	ON_BN_CLICKED(IDC_LOAD_DB, &CMainDlg::OnBnClickedLoadDb)
	ON_BN_CLICKED(IDC_CLEAR_DB, &CMainDlg::OnBnClickedClearDb)
	ON_BN_CLICKED(IDC_SHOW_DBSTRUC, &CMainDlg::OnBnClickedShowDbstruc)
	ON_BN_CLICKED(IDC_INSTRUMENT_PAN, &CMainDlg::OnBnClickedInstrumentPan)
	ON_BN_CLICKED(IDC_SHOW_CURVES, &CMainDlg::OnBnClickedShowCurves)
	ON_BN_CLICKED(IDC_SET_VALUE, &CMainDlg::OnBnClickedSetValue)
//	ON_MESSAGE(WM_MYSYNCHR, OnMyMsgHandler)
ON_NOTIFY(NM_CLICK, IDC_MAIN_TREE, &CMainDlg::OnClickMainTree)
ON_NOTIFY(TVN_SELCHANGED, IDC_MAIN_TREE, &CMainDlg::OnSelchangedMainTree)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_MAIN_TREE, &CMainDlg::OnCustomdrawMainTree)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_MAIN_LIST, &CMainDlg::OnLvnItemchangedMainList)
ON_WM_DESTROY()
END_MESSAGE_MAP()
//LRESULT CMainDlg::OnMyMsgHandler(WPARAM w, LPARAM l)
//{
//	MessageBox (L"Hello,World!");
//	return 0;
//}

// CMainDlg 消息处理程序

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	m_comLed.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	m_comLed.SetActiveNoEvent(false);
	isHaveDB = 0;
//Tree
	//tree加载图片
	mImageList.Create(20, 20, ILC_COLOR24, 4, 1);
	CBitmap  bmImage, bmImage1;
	bmImage.LoadBitmapW(IDB_ACTIVE);
	bmImage1.LoadBitmapW(IDB_POSITIVE);
	mImageList.Add(bmImage1.FromHandle((HBITMAP)(bmImage1)), RGB(0, 0, 0));
	mImageList.Add(bmImage.FromHandle((HBITMAP)(bmImage)), RGB(0, 0, 0));
	bmImage.DeleteObject();
	bmImage1.DeleteObject();
	mMainTree.SetImageList(&mImageList, LVSIL_NORMAL);
	hTreeNodeGlobal = mMainTree.InsertItem(L"数据包", 0, 0);
	
	//改变选择时的代码
	//可能清空当前的图标

	//改变选择后的代码






	 mMainList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT
		 | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	 mMainList.InsertColumn(0,L"ID",LVCFMT_LEFT,80,0);//80宽   0列
	 mMainList.InsertColumn(1, L"所属国",LVCFMT_LEFT, 80,1);
	 mMainList.InsertItem(0, _T("上海交通大学"));
	 mMainList.SetItemText(0, 1, _T("上海"));
	 mMainList.InsertItem(1, _T("西安交通大学"));
	 mMainList.SetItemText(1, 1, _T("西安"));
	 mMainList.InsertItem(2, _T("西南交通大学"));
	 mMainList.SetItemText(2, 1, _T("成都"));
	 mMainList.InsertItem(3, _T("北京交通大学"));
	 mMainList.SetItemText(3, 1, _T("北京"));
	 mMainList.InsertItem(4, _T("新竹交通大学"));
	 mMainList.SetItemText(4, 1, _T("台湾"));




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMainDlg::OnBnClickedComMana()
{
	// TODO: 在此添加控件通知处理程序代码
	CComDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}
	if (m_ctrlComm.get_PortOpen())//如过已经打开串口，
		m_comLed.SetActiveNoEvent(true);
	else
		m_comLed.SetActiveNoEvent(false);	
}


void CMainDlg::OnBnClickedLoadDb()
{
	// TODO: 在此添加控件通知处理程序代码
	dbDir[0] = "";
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT| OFN_ALLOWMULTISELECT,
		L"数据库文件 (*.dbc)|*.dbc|All Files (*.*)|*.*||");
	CString strPath, strFolder, strShowName;
	if (dlg.DoModal() == IDOK){
		strPath = dlg.GetPathName();//选中一个文件的时候，存储的是完整路径，选中多个文件的时候，不含文件名的路径
		strFolder = dlg.GetFolderPath();
		int i = 0; strShowName = "";
		if (strPath != strFolder)//只选择一个文件
		{
			dbDir[0] = strPath;
			//strShowName= dlg.GetFileName();
			int index = dbDir[i].ReverseFind('\\');
			strShowName += strPath.Right(strPath.GetLength() - index - 1);
			i++;
		}
		else {
			POSITION pos = dlg.GetStartPosition();
			while (pos != NULL) 
				{
					dbDir[i] = dlg.GetNextPathName(pos);
					int index = dbDir[i].ReverseFind('\\');
					strShowName += dbDir[i].Right(dbDir[i].GetLength()-index-1);
					strShowName += "||";
					i++;
				}
			}
		dbDir[i] = "";
		//IDC_OWN_DB
		GetDlgItem(IDC_OWN_DB)->SetWindowTextW(strShowName);
		if (dbDir[0] == L"")
		{
			isHaveDB = 0;
			return;
		}
		mList.DeleteAll();
	
//至此，把读入的文件路径放入了dbDir数组中！！在下面可以添加一些文件的处理
		//调用魏潇的程序，来InsertList,完成mList的创建



		isHaveDB = 1;
	}
}


void CMainDlg::OnBnClickedClearDb()
{
	// TODO: 在此添加控件通知处理程序代码
	dbDir[0] = "";
	CString str("");
	GetDlgItem(IDC_OWN_DB)->SetWindowTextW(str);
	isHaveDB = 0;
	mList.DeleteAll();
}


void CMainDlg::OnBnClickedShowDbstruc()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isHaveDB == 0)
		return;
	CDbStuctShow mDlgStuctShow;
	INT_PTR nResponse = mDlgStuctShow.DoModal();
 if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}
}


void CMainDlg::OnBnClickedInstrumentPan()
{
	// TODO: 在此添加控件通知处理程序代码
	//?如果指针变量m_pTipDlg的值为NULL，则对话框还未创建，需要动态创建???
	if  (NULL == mInstrumentDlg)
	{
		//?创建非模态对话框实例???
		mInstrumentDlg = new  CInstrumentShow();
		mInstrumentDlg->Create(IDD_INSTRUMENT, this);
	}
	//?显示非模态对话框???
	mInstrumentDlg->ShowWindow(SW_SHOW);

	//?将各控件中的数据保存到相应的变量???
	UpdateData(TRUE);


	//?根据各变量的值更新相应的控件。和的编辑框会显示m_editSum的值???
	UpdateData(FALSE);



}


void CMainDlg::OnBnClickedShowCurves()
{

	if (NULL == mCurveDlg)
	{
		mCurveDlg = new  CCurveDlg();
		mCurveDlg->Create(IDD_CURVE_SHOW, this);
	}
	mCurveDlg->ShowWindow(SW_SHOW);
}


void CMainDlg::OnBnClickedSetValue()
{
	// TODO: 在此添加控件通知处理程序代码
	CSetValueDlg dlg;
	dlg.DoModal();
}


void CMainDlg::OnClickMainTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CPoint oPoint;
	UINT nFlag;
	GetCursorPos(&oPoint);
	mMainTree.ScreenToClient(&oPoint);
	HTREEITEM oSelectItem = mMainTree.HitTest(oPoint,&nFlag);
	if (oSelectItem == NULL)
	{
		return;
	}
	mMainTree.SelectItem(oSelectItem);
	if (nFlag&TVHT_ONITEMSTATEICON)
	{
		BOOL bCheck = !mMainTree.GetCheck(oSelectItem);
		mMainTree.SetCheck(oSelectItem,bCheck);
		ConsistentChildCheck(oSelectItem);
		ConsistentParentCheck(oSelectItem);

		mMainTree.SetCheck(oSelectItem,!bCheck);
	}


	*pResult = 0;
}


void CMainDlg::ConsistentParentCheck(HTREEITEM hTreeItem)
{
	HTREEITEM hParentItem = mMainTree.GetParentItem(hTreeItem);
	//父节点为空则返回，否则处理父节点
	if (NULL != hParentItem)
	{
		//依次判断选中项的父节点的各子节点的状态
		HTREEITEM hChildItem = mMainTree.GetChildItem(hParentItem);
		while (NULL != hParentItem)
		{
			//如果父节点有一个未选中，则父节点未选中，并递归处理父节点
			if (mMainTree.GetCheck(hChildItem)==FALSE)
			{
				mMainTree.SetCheck(hParentItem, false);
				return ConsistentParentCheck(hParentItem);
			}
			//获取父节点的下一个子节点
			hChildItem = mMainTree.GetNextItem(hChildItem,TVGN_NEXT);
		}
		//所有节点已选中，则父节点未选中状态
		mMainTree.SetCheck(hParentItem,TRUE);
		return ConsistentParentCheck(hParentItem);
	}
}
void CMainDlg::ConsistentChildCheck(HTREEITEM hTreeItem)
{
	BOOL bCheck = mMainTree.GetCheck(hTreeItem);
	//如果存在子节点，则一致化子节点状态
	if (mMainTree.ItemHasChildren(hTreeItem))
	{
		//依次一致化子节点
		HTREEITEM hChildItem = mMainTree.GetChildItem(hTreeItem);
		while (hChildItem != NULL)
		{
			mMainTree.SetCheck(hChildItem,bCheck);
			ConsistentChildCheck(hChildItem);

			hChildItem= mMainTree.GetNextItem(hChildItem, TVGN_NEXT);
		}
	}
}


void CMainDlg::OnSelchangedMainTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM my = mMainTree.GetSelectedItem();
	int i=mMainTree.GetItemData(my);

	*pResult = 0;
}


void CMainDlg::OnCustomdrawMainTree(NMHDR *pNMHDR, LRESULT *pResult)
{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	LPNMTVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMTVCUSTOMDRAW>(pNMHDR);
	//switch (pNMCD->nmcd.dwDrawStage)
	//{
	//case CDDS_PREPAINT:
	//	*pResult = CDRF_NOTIFYITEMDRAW;
	//	return;
	//case CDDS_ITEMPREPAINT:
	//	// 这里做判断
	//	pNMCD->clrText = RGB(0, 255, 255); // 这样设置文字颜色
	//	pNMCD->clrTextBk = RGB(255, 255, 255); // 这样设置背景颜色
	//	break;
	//}


	//switch (pNMCD->iLevel)
	//{
	//	// painting all 0-level items blue,
	//	// and all 1-level items red (GGH)
	//case 0:
	//	if (pNMCD->nmcd.uItemState == (CDIS_FOCUS | CDIS_SELECTED)) // selected
	//		pNMCD->clrText = RGB(255, 0, 0);
	//	else
	//		pNMCD->clrText = RGB(0, 0, 0);
	//	break;
	//case 1:
	//	if (pNMCD->nmcd.uItemState == (CDIS_FOCUS | CDIS_SELECTED)) // selected
	//		pNMCD->clrText = RGB(255, 255, 255);
	//	else
	//		pNMCD->clrText = RGB(255, 0, 0);
	//	break;
	//}

//	*pResult = CDRF_SKIPDEFAULT;

	*pResult = 0;
}





void CMainDlg::OnLvnItemchangedMainList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMainDlg::OnDestroy()
{
	if (m_ctrlComm.get_PortOpen())//如过已经打开串口，
		m_ctrlComm.put_PortOpen(FALSE);//关闭串口
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
BEGIN_EVENTSINK_MAP(CMainDlg, CDialogEx)
	ON_EVENT(CMainDlg, IDC_MSCOMM1, 1, CMainDlg::OnOncommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CMainDlg::OnOncommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码
	VARIANT variant_inp;
	COleSafeArray safearry_inp;
	LONG len, k;
	BYTE rxdata[2048];
	CString strtemp;
	if (m_ctrlComm.get_CommEvent() == 2)//事件值为2表示接收缓冲区内有数据
	{
		//以下根据自己的通讯协议添加处理代码
		variant_inp = m_ctrlComm.get_Input();//读缓冲区
		safearry_inp = variant_inp;//VARIANT转化为COleSafeArray
		len = safearry_inp.GetOneDimSize();//字符长度
		for (k = 0; k<len; k++)
		{
			safearry_inp.GetElement(&k, rxdata + k);//转化为BYTE型数组
		}
		for (k = 0; k<len; k++)//将数组转化成Cstring型变量
		{
			BYTE bt = *(char*)(rxdata + k);
			//if(m_ctrlHexSend.GetCheck())
			//	strtemp.Format("%02x",bt);
			//else
			strtemp.Format(_T("%c"), bt);//将字符送入临时变量strtemp中存放  
			m_strRXData += strtemp;//加入接收编辑框对应字符串
								   /*******************
								   以上的语句可以进行对sbuf的读取。
								   ***********************/
			//order = _ttoi(strtemp);//order是字符转化后的int值

		}
		//UpdateData(FALSE);//更新编辑框内容（主要是接收编辑框中的）
		//在这进行处理

		//m_strRXData 调用魏潇的程序进行解析，更新链表








		updateMainDlg();

	
		//	PostMessage(WM_MYSYNCHR, c, 0);
		HWND hwnd = ::FindWindow(NULL, L"实时曲线显示");
		::PostMessage(hwnd, WM_MYSYNCHR,mList.mUpdate->id,0);
		hwnd = ::FindWindow(NULL, L"Instrument Panel");
		::PostMessage(hwnd, WM_MYSYNCHR, mList.mUpdate->id, 0);






	}

}


void CMainDlg::sendComData(CString str)
{
	long len;
	CByteArray array;
	len = str.GetLength();//发送数据的长度

	array.RemoveAll();
	array.SetSize(len);
	for (int i = 0; i<len; i++)
		array.SetAt(i, str[i]);
	m_ctrlComm.put_Output(COleVariant(array)); // 发送数据

}


void CMainDlg::updateMainDlg()
{
	//遍历
	int updateFlage = 0;
	HTREEITEM hPreChildItem;
	HTREEITEM hChildItem = mMainTree.GetChildItem(hTreeNodeGlobal);
	hPreChildItem = hChildItem;
	while (hChildItem != NULL) 
	{
		if (mMainTree.GetItemData(hChildItem)== mList.mUpdate->id)
		{
		//更新
			updateFlage = 1;
			break;
		}
		hChildItem = mMainTree.GetNextItem(hChildItem, TVGN_NEXT);
	}
	if (updateFlage == 0) //新插入节点
	{
		if (hPreChildItem == hChildItem)//头插//为空
		{
			

		}
		else//末尾插入节点
		{
			//hPreChildItem
		}
	}

}
