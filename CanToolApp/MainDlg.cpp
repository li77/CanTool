
// MainDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMainDlg �Ի���



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

// CMainDlg ��Ϣ�������

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_comLed.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	m_comLed.SetActiveNoEvent(false);
	mList.haveDB = 0;

//ʱ��
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	currentRecordTime= COleDateTime::GetCurrentTime();

	
//	string test3 = CW2A(L"�����ַ�");//һ����Լ�һ�µڶ���������˳���л�����??
//	CString test4 = CA2W((char*)test3.data());//һ�㲻�üӵڶ�������

	
	SetTimer(1, 1000 * 60 * 10, NULL);
	//COleDateTimeSpan timeSpan = time2 - time3;
	//timeSpan.GetTotalSeconds();
//Tree
	//tree����ͼƬ
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
	hTreeNodeGlobal = mMainTree.InsertItem(L"���ݰ�", 0, 0);
//MainList
	GetDlgItem(IDC_MESSAGEHEAD)->SetWindowTextW(L"��Ϣ���֣�XXX��ID��XXX���յ������ݣ�XXX���յ�XX�Σ��ڵ����֣�XXX");
	mMainList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	mMainList.InsertColumn(0, L"�ź�����", LVCFMT_CENTER, 160, 0);//80��   0��
	mMainList.InsertColumn(1, L"�ź�ֵ", LVCFMT_CENTER, 80, 1);//80��   0��
	mMainList.InsertColumn(2, L"ȡֵ��Χ", LVCFMT_CENTER, 80, 2);//80��   0��
	mMainList.InsertColumn(3, L"�ڵ�����", LVCFMT_CENTER, 160, 3);//80��   0��
	 mMainList.DeleteAllItems();//��ͷ���ᱻɾ��
//��ʾ��ʼ����ϡ�




	
	// mComOutput.InsertString(mComOutput.GetCount(), L"��������");
	// mComOutput.SetCurSel(mComOutput.GetCount()-1);
	// mComOutput.ResetContent();
	 //*************************����������ݿ�
	 //dbDir[0] = L"C:\\Users\\CDXY\\Desktop\\canmsg-sample.dbc";//����
	 //mList.DeleteAll();
	 //string mydir = CW2A(dbDir[0]);
	 //dataManage.loadDB(mydir);//�����ѽ���
	 //mList.haveDB = 1;
	 //mList.mUpdate = mList.mHead->nextMessageNode;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMainDlg::OnBnClickedComMana()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CComDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}
	if (m_ctrlComm.get_PortOpen())//����Ѿ��򿪴��ڣ�
		m_comLed.SetActiveNoEvent(true);
	else
		m_comLed.SetActiveNoEvent(false);	
}


void CMainDlg::OnBnClickedLoadDb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	dbDir[0] = "";
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT| OFN_ALLOWMULTISELECT,
		L"���ݿ��ļ� (*.dbc)|*.dbc|All Files (*.*)|*.*||");
	CString strPath, strFolder, strShowName;
	if (dlg.DoModal() == IDOK) {
		strPath = dlg.GetPathName();//ѡ��һ���ļ���ʱ�򣬴洢��������·����ѡ�ж���ļ���ʱ�򣬲����ļ�����·��
		strFolder = dlg.GetFolderPath();
		int i = 0; strShowName = "";
		if (strPath != strFolder)//ֻѡ��һ���ļ�
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

		//		dbDir[0] = L"C:\\Users\\CDXY\\Desktop\\canmsg-sample.dbc";//����
		mList.DeleteAll();

		//���ˣ��Ѷ�����ļ�·��������dbDir�����У���������������һЩ�ļ��Ĵ���
				//����κ��ĳ�����InsertList,���mList�Ĵ���
		string mydir = CW2A(dbDir[0]);
		dataManage.loadDB(mydir);//�����ѽ���
		mList.haveDB = 1;
		mMainList.DeleteAllItems();
		mMainTree.DeleteAllItems();
		hTreeNodeGlobal = mMainTree.InsertItem(L"���ݰ�", 0, 0);
	}
}


void CMainDlg::OnBnClickedClearDb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	dbDir[0] = "";
	CString str("");
	GetDlgItem(IDC_OWN_DB)->SetWindowTextW(str);
	mList.haveDB = 0;
	mList.DeleteAll();

	mMainList.DeleteAllItems();
	mMainTree.DeleteAllItems();
	hTreeNodeGlobal = mMainTree.InsertItem(L"���ݰ�", 0, 0);
}


void CMainDlg::OnBnClickedShowDbstruc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//if (isHaveDB == 0)
	//	return;
	CDbStuctShow mDlgStuctShow;
	INT_PTR nResponse = mDlgStuctShow.DoModal();
 if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}
}


void CMainDlg::OnBnClickedInstrumentPan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//?���ָ�����m_pTipDlg��ֵΪNULL����Ի���δ��������Ҫ��̬����???
	if  (NULL == mInstrumentDlg)
	{
		//?������ģ̬�Ի���ʵ��???
		mInstrumentDlg = new  CInstrumentShow();
		mInstrumentDlg->Create(IDD_INSTRUMENT, this);
	}
	//?��ʾ��ģ̬�Ի���???
	mInstrumentDlg->ShowWindow(SW_SHOW);

	//?�����ؼ��е����ݱ��浽��Ӧ�ı���???
	UpdateData(TRUE);


	//?���ݸ�������ֵ������Ӧ�Ŀؼ����͵ı༭�����ʾm_editSum��ֵ???
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSetValueDlg dlg;
	dlg.DoModal();
}


void CMainDlg::OnClickMainTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

		BOOL bCheck = !mMainTree.GetCheck(oSelectItem);//С�������仰������checkbox��������
		mMainTree.SetCheck(oSelectItem,bCheck);

	}
	else//����text,ʧ��checkbox
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
	//���ڵ�Ϊ���򷵻أ��������ڵ�
	if (NULL != hParentItem)
	{
		//�����ж�ѡ����ĸ��ڵ�ĸ��ӽڵ��״̬
		HTREEITEM hChildItem = mMainTree.GetChildItem(hParentItem);
		while (NULL != hParentItem)
		{
			//������ڵ���һ��δѡ�У��򸸽ڵ�δѡ�У����ݹ鴦���ڵ�
			if (mMainTree.GetCheck(hChildItem)==FALSE)
			{
				mMainTree.SetCheck(hParentItem, false);
				return ConsistentParentCheck(hParentItem);
			}
			//��ȡ���ڵ����һ���ӽڵ�
			hChildItem = mMainTree.GetNextItem(hChildItem,TVGN_NEXT);
		}
		//���нڵ���ѡ�У��򸸽ڵ�δѡ��״̬
		mMainTree.SetCheck(hParentItem,TRUE);
		return ConsistentParentCheck(hParentItem);
	}
}
void CMainDlg::ConsistentChildCheck(HTREEITEM hTreeItem)
{
	BOOL bCheck = mMainTree.GetCheck(hTreeItem);
	//��������ӽڵ㣬��һ�»��ӽڵ�״̬
	if (mMainTree.ItemHasChildren(hTreeItem))
	{
		//����һ�»��ӽڵ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ȡ��check
	*pResult = 0;

	HTREEITEM mySelected = mMainTree.GetSelectedItem();
	mMainTree.SetCheck(mySelected, false);
	UINT id;
	id = getSelectID();
	if (0 == id)//ѡ���˶����ڵ�
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
		//����ͷ���ľ�̬��
		strcpy_s(buff, "��Ϣ����");
		strcat_s(buff, pM->MessageName);
		strcat_s(buff, "  ,ID��");
		sprintf_s(buff1, "%d", pM->id);
		strcat_s(buff, buff1);
		strcat_s(buff, "  ,�յ����ݣ�");
		strcat_s(buff, pM->dataShow);
		strcat_s(buff, "  ,�յ�������");
		sprintf_s(buff1, "%d", pM->received);
		strcat_s(buff, buff1);
		strcat_s(buff, "  ,�ڵ�����");
		strcat_s(buff, pM->NodeName);
		GetDlgItem(IDC_MESSAGEHEAD)->SetWindowTextW(CA2W(buff));
		while (pS)//ֻ�Ǹ����ź�ֵ
		{
			//����List����
			mMainList.InsertItem(i,  CA2W(pS->SignalName));//�ź�����
			//sprintf_s(buff, "%s %s", pS->value, pS->units);
			if (pS->value - (int)pS->value == 0)
				sprintf_s(buff, "%d", (int)pS->value);
			else
				_gcvt_s(buff, pS->value, 6);
			strcat_s(buff, "  ");
			strcat_s(buff, pS->units);
			mMainList.SetItemText(i, 1, CA2W(buff));//�ź�ֵ
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
			mMainList.SetItemText(i, 2, CA2W(buff));//ȡֵ��Χ

			mMainList.SetItemText(i, 3, CA2W(pS->NodeName));//�ڵ�����
			i++;
			pS = pS->nextSignalNode;
		}
	}
}


void CMainDlg::OnCustomdrawMainTree(NMHDR *pNMHDR, LRESULT *pResult)
{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LPNMTVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMTVCUSTOMDRAW>(pNMHDR);
	//switch (pNMCD->nmcd.dwDrawStage)
	//{
	//case CDDS_PREPAINT:
	//	*pResult = CDRF_NOTIFYITEMDRAW;
	//	return;
	//case CDDS_ITEMPREPAINT:
	//	// �������ж�
	//	pNMCD->clrText = RGB(0, 255, 255); // ��������������ɫ
	//	pNMCD->clrTextBk = RGB(255, 255, 255); // �������ñ�����ɫ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CMainDlg::OnDestroy()
{
	if (m_ctrlComm.get_PortOpen())//����Ѿ��򿪴��ڣ�
		m_ctrlComm.put_PortOpen(FALSE);//�رմ���
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}
BEGIN_EVENTSINK_MAP(CMainDlg, CDialogEx)
	ON_EVENT(CMainDlg, IDC_MSCOMM1, 1, CMainDlg::OnOncommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CMainDlg::OnOncommMscomm1()
{
	// TODO: �ڴ˴������Ϣ����������
	VARIANT variant_inp;
	COleSafeArray safearry_inp;
	LONG len, k;
	BYTE rxdata[2048];
	CString strtemp;
	m_strRXData = L"";
	if (m_ctrlComm.get_CommEvent() == 2)//�¼�ֵΪ2��ʾ���ջ�������������
	{
		//���¸����Լ���ͨѶЭ����Ӵ������
		variant_inp = m_ctrlComm.get_Input();//��������
		safearry_inp = variant_inp;//VARIANTת��ΪCOleSafeArray
		len = safearry_inp.GetOneDimSize();//�ַ�����
		for (k = 0; k<len; k++)
		{
			safearry_inp.GetElement(&k, rxdata + k);//ת��ΪBYTE������
		}
		for (k = 0; k<len; k++)//������ת����Cstring�ͱ���
		{
			BYTE bt = *(char*)(rxdata + k);
			//if(m_ctrlHexSend.GetCheck())
			//	strtemp.Format("%02x",bt);
			//else
			strtemp.Format(_T("%c"), bt);//���ַ�������ʱ����strtemp�д��  
			m_strRXData += strtemp;//������ձ༭���Ӧ�ַ���
								   /*******************
								   ���ϵ������Խ��ж�sbuf�Ķ�ȡ��
								   ***********************/
			//order = _ttoi(strtemp);//order���ַ�ת�����intֵ

		}
		
		comRecieveTest(m_strRXData);




	}

}


void CMainDlg::sendComData(CString str)
{	
	long len;
	CByteArray array;
	len = str.GetLength();//�������ݵĳ���

	array.RemoveAll();
	array.SetSize(len);
	for (int i = 0; i<len; i++)
		array.SetAt(i, str[i]);
	m_ctrlComm.put_Output(COleVariant(array)); // ��������
	mComOutput.InsertString(mComOutput.GetCount(), str);
	mComOutput.SetCurSel(mComOutput.GetCount() - 1);

}



//int CMainDlg::refreshMainListCtl(unsigned int id)//��tree�ڵ�ı��ʱ��������
//{
//	PMessageNode  pM=mList.Search(id);
//	PSignalNode pS =  pM->pSignalNode;
//	int i = 0;
//	char buff[20], buff1[20];
//	while (pS)//ֻ�Ǹ����ź�ֵ
//	{
//
//		mMainList.SetItemText(i, 0, CA2W(pS->SignalName));//�ź�����
//		//sprintf_s(buff, "%s %s", pS->value, pS->units);
//		_gcvt_s(buff, pS->value, 6);
//		strcat_s(buff, "  ");
//		strcat_s(buff, pS->units);
//		//mMainList.SetItemText(i, 1, CA2W(buff));//�ź�ֵ
//		mMainList.InsertItem(i, CA2W(buff));
//		strcpy_s(buff, "[ ");
//		_gcvt_s(buff1, pS->minValue, 6);
//		strcat_s(buff, buff1);
//		strcat_s(buff, "  , ");
//		_gcvt_s(buff1, pS->maxValue, 6);
//		strcat_s(buff, buff1);
//		strcat_s(buff, " ]");
//		mMainList.SetItemText(i, 2, CA2W(buff));//ȡֵ��Χ
//
//		mMainList.SetItemText(i, 3, CA2W(pS->NodeName));//�ڵ�����
//		i++;
//		pS = pS->nextSignalNode;
//	}
//	return 0;
//}


void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	if (nIDEvent == 1)
	{
		QueryPerformanceCounter(&t1);//����
		currentRecordTime = COleDateTime::GetCurrentTime();//�޸ĵ�ǰʱ��
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
	if (mMainTree.GetChildItem(mySelect) == NULL)//���ӽڵ�
	{
		if (mMainTree.GetParentItem(mySelect) == NULL) return 0;
		if(mMainTree.GetItemData(mySelect)==0)
			return mMainTree.GetItemData(mMainTree.GetParentItem(mySelect));
		else	//�µ�id��
			return mMainTree.GetItemData(mySelect);
	}
	else if (mMainTree.GetParentItem(mySelect) == NULL) //�����ڵ�
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
	//UpdateData(FALSE);//���±༭�����ݣ���Ҫ�ǽ��ձ༭���еģ�
	mComInput.InsertString(mComInput.GetCount(), mRXData);
	mComInput.SetCurSel(mComInput.GetCount() - 1);
	//���ݵĽ�����ǰ�˵Ĵ���
	//���յ������ݽ��з��ദ��
	if (mRXData[0] == L'\a' || mRXData == L"\BEL")
	{
		MessageBox(L"CAN�豸����\\BEL!!");
		return;
	}
	else if (mRXData[0] == L'\r')//�ɹ�
	{
		return;
	}
	else if (mRXData[0] == L'T' || mRXData[0] == L't')  //������
	{
	}//�����ǽ������ݵĵط�
	else  //�汾��Ϣ
	{
		GetDlgItem(IDC_GET_VERSION)->SetWindowTextW(mRXData);
		return;
	}



	//mRXData ����κ��ĳ�����н�������������
	string mRData = CW2A(mRXData);
	dataManage.analyze(mRData); //����Ӧ�����ݲ���mList��
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
								//��ʱ�����  mSec
	mList.mUpdate->msec = getMSec();

//////*******************��������
//
//
//	mList.mUpdate = mList.mUpdate->nextMessageNode;
//	if (mList.mUpdate == NULL)
//	{
//		mList.mUpdate = mList.mHead->nextMessageNode;
//	}



	//�����µĽڵ����mMainTree��
	HTREEITEM hNodeChild = mMainTree.GetChildItem(hTreeNodeGlobal);
	HTREEITEM hNodeSun;
	HTREEITEM hNewChild;
	CString str;
	wchar_t buff_w[40];
	CString  buffs;
	PSignalNode pS;
	//	PMessageNode pM;
	while (hNodeChild != NULL)//������ûMainTree���Ƿ����
	{
		if (mMainTree.GetItemData(hNodeChild) == mList.mUpdate->id)
			break;
		hNodeChild = mMainTree.GetNextItem(hNodeChild, TVGN_NEXT);
	}
	if (hNodeChild == NULL)//������Ҫ�²������ݣ����в�����
	{
		//Ҫ�ж����Ƿ������ݿ���
		if (mList.mUpdate->pSignalNode == NULL)//�µ�id����ֱ��id��������
		{
			//dataת��TVI_LAST
			_ultow_s(mList.mUpdate->id, buff_w, 10);
			buffs = L"ID: ";
			buffs += buff_w;
			hNodeChild = mMainTree.InsertItem(buffs, 0, 0, hTreeNodeGlobal, TVI_FIRST);
			mMainTree.SetItemData(hNodeChild, mList.mUpdate->id);
		}
		else   //recieve=1�����ݰ���ֻ��Ҫ���µ����м���
		{
			hNodeChild = mMainTree.InsertItem(CA2W(mList.mUpdate->MessageName), 0, 0, hTreeNodeGlobal, TVI_FIRST);
			mMainTree.SetItemData(hNodeChild, mList.mUpdate->id);
			pS = mList.mUpdate->pSignalNode;
			while (pS)//�������sun�ڵ�
			{
				mMainTree.InsertItem(CA2W(pS->SignalName), 0, 0, hNodeChild);
				pS = pS->nextSignalNode;
			}
		}
		mMainTree.SetCheck(hNodeChild, 1);
		ConsistentChildCheck(hNodeChild);
	//	ConsistentParentCheck(hNodeChild);
	}

	else  //�������е����ݣ���Ҫ���������б��״̬��4�����,�Ƿ�ѡ�У��Ƿ���δ������id��δѡ��ɶ��û��
	{
		mMainTree.SetCheck(hNodeChild, true);
		ConsistentChildCheck(hNodeChild);
		//ConsistentParentCheck(hNodeChild);
		if (mMainTree.GetSelectedItem() == hNodeChild)//��ѡ��
		{
			if (mList.mUpdate->pSignalNode == NULL)//�µ�id����ֻ�����IDC_MESSAGEHEAD����
			{
				//����ͷ���ľ�̬��
				str = L"  ,ID��";
				_ultow_s(mList.mUpdate->id, buff_w, 10);
				str += buff_w;
				str += L"  ,�յ����ݣ�";
				str += CA2W(mList.mUpdate->dataShow);
				str += L"  ,�յ�������";
				_ultow_s(mList.mUpdate->received, buff_w, 10);
				str += buff_w;
				GetDlgItem(IDC_MESSAGEHEAD)->SetWindowTextW(str);
			}
			else//����List,��IDC_MESSAGEHEAD
			{
				//����mMainList�ؼ���������ȫ�����룬����ָ��
				pS = mList.mUpdate->pSignalNode;
				int i = 0;
				char buff[40], buff1[40];
				wchar_t buff_w[40];
				while (pS)//ֻ�Ǹ����ź�ֵ
				{
					if (pS->value - (int)pS->value == 0)
						sprintf_s(buff, "%d", (int)pS->value);
					else
						_gcvt_s(buff, pS->value, 6);
					strcat_s(buff, "  ");
					strcat_s(buff, pS->units);
					mMainList.SetItemText(i, 1, CA2W(buff));//�ź�ֵ

					i++;
					pS = pS->nextSignalNode;
				}
				//����ͷ���ľ�̬��
				str = L"��Ϣ����";
				str += CA2W(mList.mUpdate->MessageName);
				str += L"  ,ID��";
				_ultow_s(mList.mUpdate->id, buff_w, 10);
				str += buff_w;
				str += L"  ,�յ����ݣ�";
				//					UINT high = (mList.mUpdate->dataShow>> 32) & 0x00000000FFFFFFFF;
				//					UINT low = mList.mUpdate->dataShow & 0x00000000FFFFFFFF;
				//					_ultow_s(high, buff_w, 16);
				//					str += buff;//�Ǹ���
				//					_ultow_s(low, buff_w, 16);
				str += CA2W(mList.mUpdate->dataShow);

				str += L"  ,�յ�������";
				_ultow_s(mList.mUpdate->received, buff_w, 10);
				str += buff_w;
				str += L"  ,�ڵ�����";
				str += CA2W(mList.mUpdate->NodeName);
				GetDlgItem(IDC_MESSAGEHEAD)->SetWindowTextW(str);
			



			}//����List,��IDC_MESSAGEHEAD
		}//ѡ�У�if
	
	}
	//���ˣ�������������

	////���mMainListѡ������Щ��������Щ�źŷ��ͳ�ȥ,ֻ֧�����ѡ��32��
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
	//		//str.Format(_T("ѡ���˵�%d��"), nItem);
	//		secondPara |= 1 << nItem;
	//	}
	//	//�ж�ѡ�е�id
	//	firstPara = getSelectID();

	//	HWND hwnd = ::FindWindow(NULL, L"ʵʱ������ʾ");
	//	::PostMessage(hwnd, WM_MYSYNCHR, firstPara, secondPara);
	//	hwnd = ::FindWindow(NULL, L"Instrument Panel");
	//	::PostMessage(hwnd, WM_MYSYNCHR, firstPara, secondPara);

	//}
	//���˴����Զ�����Ϣ�������
}




void CMainDlg::OnBnClickedGetVersion()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sendComData(L"V\r");
}


void CMainDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_MONI_RECV)->GetWindowTextW(str);
	str.AppendChar(L'\r');
	comRecieveTest(str);
}


void CMainDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_MONI_SEND)->GetWindowTextW(str);
	str.AppendChar(L'\r');
	sendComData(str);
}
