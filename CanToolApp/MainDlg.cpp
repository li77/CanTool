
// MainDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "CanToolApp.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include"DbStuctShow.h"
#include"ComDlg.h"
#include"CanTool_LinkList.h"
using std::string;
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
	DDX_Control(pDX, IDC_OUTPUT, mComOutput);
	DDX_Control(pDX, IDC_INPUT, mComInput);
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
ON_WM_TIMER()
ON_BN_CLICKED(IDC_GET_VERSION, &CMainDlg::OnBnClickedGetVersion)
ON_BN_CLICKED(IDC_BUTTON1, &CMainDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &CMainDlg::OnBnClickedButton2)
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
	mList.haveDB = 0;

//时间
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	currentRecordTime= COleDateTime::GetCurrentTime();

	
//	string test3 = CW2A(L"中文字符");//一般可以加一下第二个参数，顺便切换编码??
//	CString test4 = CA2W((char*)test3.data());//一般不用加第二个参数

	
	SetTimer(1, 1000 * 60 * 10, NULL);
	//COleDateTimeSpan timeSpan = time2 - time3;
	//timeSpan.GetTotalSeconds();
//Tree
	//tree加载图片
/*
	mImageList.Create(20, 20, ILC_COLOR24, 4, 1);
	CBitmap  bmImage, bmImage1;
	bmImage.LoadBitmapW(IDB_ACTIVE);
	bmImage1.LoadBitmapW(IDB_POSITIVE);
	mImageList.Add(bmImage1.FromHandle((HBITMAP)(bmImage1)), RGB(0, 0, 0));
	mImageList.Add(bmImage.FromHandle((HBITMAP)(bmImage)), RGB(0, 0, 0));
	bmImage.DeleteObject();
	bmImage1.DeleteObject();
	mMainTree.SetImageList(&mImageList, LVSIL_NORMAL);
*/
	hTreeNodeGlobal = mMainTree.InsertItem(L"数据包", 0, 0);
//MainList
	GetDlgItem(IDC_MESSAGEHEAD)->SetWindowTextW(L"信息名字：XXX，ID：XXX，收到的数据：XXX，收到XX次，节点名字：XXX");
	mMainList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	mMainList.InsertColumn(0, L"信号名字", LVCFMT_CENTER, 160, 0);//80宽   0列
	mMainList.InsertColumn(1, L"信号值", LVCFMT_CENTER, 80, 1);//80宽   0列
	mMainList.InsertColumn(2, L"取值范围", LVCFMT_CENTER, 80, 2);//80宽   0列
	mMainList.InsertColumn(3, L"节点名字", LVCFMT_CENTER, 160, 3);//80宽   0列
	 mMainList.DeleteAllItems();//表头不会被删除
//显示初始化完毕。




	
	// mComOutput.InsertString(mComOutput.GetCount(), L"撒大声地");
	// mComOutput.SetCurSel(mComOutput.GetCount()-1);
	// mComOutput.ResetContent();
	 //*************************测试添加数据库
	 //dbDir[0] = L"C:\\Users\\CDXY\\Desktop\\canmsg-sample.dbc";//调试
	 //mList.DeleteAll();
	 //string mydir = CW2A(dbDir[0]);
	 //dataManage.loadDB(mydir);//链表已建立
	 //mList.haveDB = 1;
	 //mList.mUpdate = mList.mHead->nextMessageNode;

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
	if (dlg.DoModal() == IDOK) {
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
				strShowName += dbDir[i].Right(dbDir[i].GetLength() - index - 1);
				strShowName += "||";
				i++;
			}
		}
		dbDir[i] = "";
		//IDC_OWN_DB
		GetDlgItem(IDC_OWN_DB)->SetWindowTextW(strShowName);
		if (dbDir[0] == L"")
		{
			mList.haveDB = 0;
			return;
		}

		//		dbDir[0] = L"C:\\Users\\CDXY\\Desktop\\canmsg-sample.dbc";//调试
		mList.DeleteAll();

		//至此，把读入的文件路径放入了dbDir数组中！！在下面可以添加一些文件的处理
				//调用魏潇的程序，来InsertList,完成mList的创建
		string mydir = CW2A(dbDir[0]);
		dataManage.loadDB(mydir);//链表已建立
		mList.haveDB = 1;
		mMainList.DeleteAllItems();
		mMainTree.DeleteAllItems();
		hTreeNodeGlobal = mMainTree.InsertItem(L"数据包", 0, 0);
	}
}


void CMainDlg::OnBnClickedClearDb()
{
	// TODO: 在此添加控件通知处理程序代码
	dbDir[0] = "";
	CString str("");
	GetDlgItem(IDC_OWN_DB)->SetWindowTextW(str);
	mList.haveDB = 0;
	mList.DeleteAll();

	mMainList.DeleteAllItems();
	mMainTree.DeleteAllItems();
	hTreeNodeGlobal = mMainTree.InsertItem(L"数据包", 0, 0);
}


void CMainDlg::OnBnClickedShowDbstruc()
{
	// TODO: 在此添加控件通知处理程序代码
	//if (isHaveDB == 0)
	//	return;
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
		/*BOOL bCheck = !mMainTree.GetCheck(oSelectItem);
		mMainTree.SetCheck(oSelectItem,bCheck);
		ConsistentChildCheck(oSelectItem);
		ConsistentParentCheck(oSelectItem);
		mMainTree.SetCheck(oSelectItem,!bCheck);*/

		BOOL bCheck = !mMainTree.GetCheck(oSelectItem);//小面这两句话，点中checkbox不起作用
		mMainTree.SetCheck(oSelectItem,bCheck);

	}
	else//点中text,失能checkbox
	{
		mMainTree.SetCheck(oSelectItem,false);
		ConsistentChildCheck(oSelectItem);
		ConsistentParentCheck(oSelectItem);
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
	//取消check
	*pResult = 0;

	HTREEITEM mySelected = mMainTree.GetSelectedItem();
	mMainTree.SetCheck(mySelected, false);
	UINT id;
	id = getSelectID();
	if (0 == id)//选择了顶级节点
		return;
	else
	{
		mMainTree.SetCheck(mySelected, false);
		ConsistentChildCheck(mySelected);
		ConsistentParentCheck(mySelected);
		mMainList.DeleteAllItems();
		PMessageNode pM = mList.Search(id);

		PSignalNode pS=  pM->pSignalNode;
		int i = 0;
		char buff[1000], buff1[50];
		//更新头部的静态串
		strcpy_s(buff, "信息名：");
		strcat_s(buff, pM->MessageName);
		strcat_s(buff, "  ,ID：");
		sprintf_s(buff1, "%d", pM->id);
		strcat_s(buff, buff1);
		strcat_s(buff, "  ,收到数据：");
		strcat_s(buff, pM->dataShow);
		strcat_s(buff, "  ,收到次数：");
		sprintf_s(buff1, "%d", pM->received);
		strcat_s(buff, buff1);
		strcat_s(buff, "  ,节点名：");
		strcat_s(buff, pM->NodeName);
		GetDlgItem(IDC_MESSAGEHEAD)->SetWindowTextW(CA2W(buff));
		while (pS)//只是更新信号值
		{
			//更新List内容
			mMainList.InsertItem(i,  CA2W(pS->SignalName));//信号名字
			//sprintf_s(buff, "%s %s", pS->value, pS->units);
			if (pS->value - (int)pS->value == 0)
				sprintf_s(buff, "%d", (int)pS->value);
			else
				_gcvt_s(buff, pS->value, 6);
			strcat_s(buff, "  ");
			strcat_s(buff, pS->units);
			mMainList.SetItemText(i, 1, CA2W(buff));//信号值
			strcpy_s(buff, "[ ");
			if (pS->minValue - (int)pS->minValue == 0)
				sprintf_s(buff1, "%d", (int)pS->minValue);
			else
				_gcvt_s(buff1, pS->minValue, 6);
			strcat_s(buff, buff1);
			strcat_s(buff, "  , ");
			if (pS->maxValue - (int)pS->maxValue == 0)
				sprintf_s(buff1, "%d", (int)pS->maxValue);
			else
				_gcvt_s(buff1, pS->maxValue, 6);
			strcat_s(buff, buff1);
			strcat_s(buff, " ]");
			mMainList.SetItemText(i, 2, CA2W(buff));//取值范围

			mMainList.SetItemText(i, 3, CA2W(pS->NodeName));//节点名字
			i++;
			pS = pS->nextSignalNode;
		}
	}
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
	m_strRXData = L"";
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
		
		comRecieveTest(m_strRXData);




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
	mComOutput.InsertString(mComOutput.GetCount(), str);
	mComOutput.SetCurSel(mComOutput.GetCount() - 1);

}



//int CMainDlg::refreshMainListCtl(unsigned int id)//供tree节点改变的时候来调用
//{
//	PMessageNode  pM=mList.Search(id);
//	PSignalNode pS =  pM->pSignalNode;
//	int i = 0;
//	char buff[20], buff1[20];
//	while (pS)//只是更新信号值
//	{
//
//		mMainList.SetItemText(i, 0, CA2W(pS->SignalName));//信号名字
//		//sprintf_s(buff, "%s %s", pS->value, pS->units);
//		_gcvt_s(buff, pS->value, 6);
//		strcat_s(buff, "  ");
//		strcat_s(buff, pS->units);
//		//mMainList.SetItemText(i, 1, CA2W(buff));//信号值
//		mMainList.InsertItem(i, CA2W(buff));
//		strcpy_s(buff, "[ ");
//		_gcvt_s(buff1, pS->minValue, 6);
//		strcat_s(buff, buff1);
//		strcat_s(buff, "  , ");
//		_gcvt_s(buff1, pS->maxValue, 6);
//		strcat_s(buff, buff1);
//		strcat_s(buff, " ]");
//		mMainList.SetItemText(i, 2, CA2W(buff));//取值范围
//
//		mMainList.SetItemText(i, 3, CA2W(pS->NodeName));//节点名字
//		i++;
//		pS = pS->nextSignalNode;
//	}
//	return 0;
//}


void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	if (nIDEvent == 1)
	{
		QueryPerformanceCounter(&t1);//重置
		currentRecordTime = COleDateTime::GetCurrentTime();//修改当前时间
		str = currentRecordTime.Format(VAR_DATEVALUEONLY);//2017/10/16
		str += " ";
		str += currentRecordTime.Format(VAR_TIMEVALUEONLY);//22:54:10
		PMessageNode p = mList.mHead->nextMessageNode;
		while(p!=NULL)
		{
			p->msec = 0;
			string test = CW2A(str);
			memcpy_s(p->date, 20, (char*)test.data(), 20);
			p = p->nextMessageNode;
		}	
	}





	CDialogEx::OnTimer(nIDEvent);
}


__int32 CMainDlg::getMSec()
{
	QueryPerformanceCounter(&t2);
	return (t2.QuadPart - t1.QuadPart) / (tc.QuadPart / 1000);
}


UINT CMainDlg::getSelectID()
{
	HTREEITEM mySelect = mMainTree.GetSelectedItem();
	if (mySelect ==NULL)
	{
		return 0;
	}
	if (mMainTree.GetChildItem(mySelect) == NULL)//孙子节点
	{
		if (mMainTree.GetParentItem(mySelect) == NULL) return 0;
		if(mMainTree.GetItemData(mySelect)==0)
			return mMainTree.GetItemData(mMainTree.GetParentItem(mySelect));
		else	//新的id包
			return mMainTree.GetItemData(mySelect);
	}
	else if (mMainTree.GetParentItem(mySelect) == NULL) //顶级节点
	{
		return 0;
	}
	else 
	{
		return mMainTree.GetItemData(mySelect);
	}


//test



}

void CMainDlg::comRecieveTest(CString mRXData)
{
	//UpdateData(FALSE);//更新编辑框内容（主要是接收编辑框中的）
	mComInput.InsertString(mComInput.GetCount(), mRXData);
	mComInput.SetCurSel(mComInput.GetCount() - 1);
	//数据的解析与前端的处理
	//对收到的数据进行分类处理
	if (mRXData[0] == L'\a' || mRXData == L"\BEL")
	{
		MessageBox(L"CAN设备反馈\\BEL!!");
		return;
	}
	else if (mRXData[0] == L'\r')//成功
	{
		return;
	}
	else if (mRXData[0] == L'T' || mRXData[0] == L't')  //解析串
	{
	}//这里是解析数据的地方
	else  //版本信息
	{
		GetDlgItem(IDC_GET_VERSION)->SetWindowTextW(mRXData);
		return;
	}



	//mRXData 调用魏潇的程序进行解析，更新链表
	string mRData = CW2A(mRXData);
	dataManage.analyze(mRData); //把相应的数据插入mList中
	string sdf;
	if (mRData.length() > 30)
	{
		sdf = mRData.substr(0, 30);
		mRData = sdf;
	}
	char *sp= ( char*)mRData.c_str();
	if (mRData[0] == 't')
	{
		sp += 5;
	}
	else
	{
		sp += 10;
	
	}
	strcpy_s(mList.mUpdate->dataShow, sp);
								//把时间插入  mSec
	mList.mUpdate->msec = getMSec();

//////*******************测试生成
//
//
//	mList.mUpdate = mList.mUpdate->nextMessageNode;
//	if (mList.mUpdate == NULL)
//	{
//		mList.mUpdate = mList.mHead->nextMessageNode;
//	}



	//把最新的节点插入mMainTree中
	HTREEITEM hNodeChild = mMainTree.GetChildItem(hTreeNodeGlobal);
	HTREEITEM hNodeSun;
	HTREEITEM hNewChild;
	CString str;
	wchar_t buff_w[40];
	CString  buffs;
	PSignalNode pS;
	//	PMessageNode pM;
	while (hNodeChild != NULL)//检索在没MainTree中是否存在
	{
		if (mMainTree.GetItemData(hNodeChild) == mList.mUpdate->id)
			break;
		hNodeChild = mMainTree.GetNextItem(hNodeChild, TVGN_NEXT);
	}
	if (hNodeChild == NULL)//树中需要新插入数据，树中不存在
	{
		//要判断其是否在数据库中
		if (mList.mUpdate->pSignalNode == NULL)//新的id包，直接id命名即可
		{
			//data转串TVI_LAST
			_ultow_s(mList.mUpdate->id, buff_w, 10);
			buffs = L"ID: ";
			buffs += buff_w;
			hNodeChild = mMainTree.InsertItem(buffs, 0, 0, hTreeNodeGlobal, TVI_FIRST);
			mMainTree.SetItemData(hNodeChild, mList.mUpdate->id);
		}
		else   //recieve=1的数据包，只需要跟新到数中即可
		{
			hNodeChild = mMainTree.InsertItem(CA2W(mList.mUpdate->MessageName), 0, 0, hTreeNodeGlobal, TVI_FIRST);
			mMainTree.SetItemData(hNodeChild, mList.mUpdate->id);
			pS = mList.mUpdate->pSignalNode;
			while (pS)//添加树的sun节点
			{
				mMainTree.InsertItem(CA2W(pS->SignalName), 0, 0, hNodeChild);
				pS = pS->nextSignalNode;
			}
		}
		mMainTree.SetCheck(hNodeChild, 1);
		ConsistentChildCheck(hNodeChild);
	//	ConsistentParentCheck(hNodeChild);
	}

	else  //树中已有的数据，需要更新树和列表的状态，4中情况,是否选中，是否是未解析的id，未选中啥事没有
	{
		mMainTree.SetCheck(hNodeChild, true);
		ConsistentChildCheck(hNodeChild);
		//ConsistentParentCheck(hNodeChild);
		if (mMainTree.GetSelectedItem() == hNodeChild)//若选中
		{
			if (mList.mUpdate->pSignalNode == NULL)//新的id包，只需更新IDC_MESSAGEHEAD即可
			{
				//更新头部的静态串
				str = L"  ,ID：";
				_ultow_s(mList.mUpdate->id, buff_w, 10);
				str += buff_w;
				str += L"  ,收到数据：";
				str += CA2W(mList.mUpdate->dataShow);
				str += L"  ,收到次数：";
				_ultow_s(mList.mUpdate->received, buff_w, 10);
				str += buff_w;
				GetDlgItem(IDC_MESSAGEHEAD)->SetWindowTextW(str);
			}
			else//更新List,和IDC_MESSAGEHEAD
			{
				//更新mMainList控件，并不是全部插入，根据指针
				pS = mList.mUpdate->pSignalNode;
				int i = 0;
				char buff[40], buff1[40];
				wchar_t buff_w[40];
				while (pS)//只是更新信号值
				{
					if (pS->value - (int)pS->value == 0)
						sprintf_s(buff, "%d", (int)pS->value);
					else
						_gcvt_s(buff, pS->value, 6);
					strcat_s(buff, "  ");
					strcat_s(buff, pS->units);
					mMainList.SetItemText(i, 1, CA2W(buff));//信号值

					i++;
					pS = pS->nextSignalNode;
				}
				//更新头部的静态串
				str = L"信息名：";
				str += CA2W(mList.mUpdate->MessageName);
				str += L"  ,ID：";
				_ultow_s(mList.mUpdate->id, buff_w, 10);
				str += buff_w;
				str += L"  ,收到数据：";
				//					UINT high = (mList.mUpdate->dataShow>> 32) & 0x00000000FFFFFFFF;
				//					UINT low = mList.mUpdate->dataShow & 0x00000000FFFFFFFF;
				//					_ultow_s(high, buff_w, 16);
				//					str += buff;//是复制
				//					_ultow_s(low, buff_w, 16);
				str += CA2W(mList.mUpdate->dataShow);

				str += L"  ,收到次数：";
				_ultow_s(mList.mUpdate->received, buff_w, 10);
				str += buff_w;
				str += L"  ,节点名：";
				str += CA2W(mList.mUpdate->NodeName);
				GetDlgItem(IDC_MESSAGEHEAD)->SetWindowTextW(str);
			



			}//更新List,和IDC_MESSAGEHEAD
		}//选中，if
	
	}
	//至此，主界面更新完毕

	////检查mMainList选中了哪些，并把这些信号发送出去,只支持最大选中32行
	//POSITION pos = mMainList.GetFirstSelectedItemPosition();
	//WPARAM firstPara = 0;
	//LPARAM secondPara = 0;
	//if (pos == NULL)
	//	TRACE0("No items were selected!/n");
	//else
	//{
	//	while (pos)
	//	{
	//		int nItem = mMainList.GetNextSelectedItem(pos);
	//		TRACE1("Item %d was selected!/n", nItem);
	//		//str.Format(_T("选中了第%d行"), nItem);
	//		secondPara |= 1 << nItem;
	//	}
	//	//判断选中的id
	//	firstPara = getSelectID();

	//	HWND hwnd = ::FindWindow(NULL, L"实时曲线显示");
	//	::PostMessage(hwnd, WM_MYSYNCHR, firstPara, secondPara);
	//	hwnd = ::FindWindow(NULL, L"Instrument Panel");
	//	::PostMessage(hwnd, WM_MYSYNCHR, firstPara, secondPara);

	//}
	//至此窗口自定义消息发送完毕
}




void CMainDlg::OnBnClickedGetVersion()
{
	// TODO: 在此添加控件通知处理程序代码
	sendComData(L"V\r");
}


void CMainDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_MONI_RECV)->GetWindowTextW(str);
	str.AppendChar(L'\r');
	comRecieveTest(str);
}


void CMainDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_MONI_SEND)->GetWindowTextW(str);
	str.AppendChar(L'\r');
	sendComData(str);
}
