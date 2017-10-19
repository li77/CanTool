
// MainDlg.cpp : ʵ���ļ�
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
	isHaveDB = 0;
//Tree
	//tree����ͼƬ
	mImageList.Create(20, 20, ILC_COLOR24, 4, 1);
	CBitmap  bmImage, bmImage1;
	bmImage.LoadBitmapW(IDB_ACTIVE);
	bmImage1.LoadBitmapW(IDB_POSITIVE);
	mImageList.Add(bmImage1.FromHandle((HBITMAP)(bmImage1)), RGB(0, 0, 0));
	mImageList.Add(bmImage.FromHandle((HBITMAP)(bmImage)), RGB(0, 0, 0));
	bmImage.DeleteObject();
	bmImage1.DeleteObject();
	mMainTree.SetImageList(&mImageList, LVSIL_NORMAL);
	hTreeNodeGlobal = mMainTree.InsertItem(L"���ݰ�", 0, 0);
	
	//�ı�ѡ��ʱ�Ĵ���
	//������յ�ǰ��ͼ��

	//�ı�ѡ���Ĵ���






	 mMainList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT
		 | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	 mMainList.InsertColumn(0,L"ID",LVCFMT_LEFT,80,0);//80��   0��
	 mMainList.InsertColumn(1, L"������",LVCFMT_LEFT, 80,1);
	 mMainList.InsertItem(0, _T("�Ϻ���ͨ��ѧ"));
	 mMainList.SetItemText(0, 1, _T("�Ϻ�"));
	 mMainList.InsertItem(1, _T("������ͨ��ѧ"));
	 mMainList.SetItemText(1, 1, _T("����"));
	 mMainList.InsertItem(2, _T("���Ͻ�ͨ��ѧ"));
	 mMainList.SetItemText(2, 1, _T("�ɶ�"));
	 mMainList.InsertItem(3, _T("������ͨ��ѧ"));
	 mMainList.SetItemText(3, 1, _T("����"));
	 mMainList.InsertItem(4, _T("����ͨ��ѧ"));
	 mMainList.SetItemText(4, 1, _T("̨��"));




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
	if (dlg.DoModal() == IDOK){
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
	
//���ˣ��Ѷ�����ļ�·��������dbDir�����У���������������һЩ�ļ��Ĵ���
		//����κ��ĳ�����InsertList,���mList�Ĵ���



		isHaveDB = 1;
	}
}


void CMainDlg::OnBnClickedClearDb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	dbDir[0] = "";
	CString str("");
	GetDlgItem(IDC_OWN_DB)->SetWindowTextW(str);
	isHaveDB = 0;
	mList.DeleteAll();
}


void CMainDlg::OnBnClickedShowDbstruc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (isHaveDB == 0)
		return;
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
	HTREEITEM my = mMainTree.GetSelectedItem();
	int i=mMainTree.GetItemData(my);

	*pResult = 0;
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
		//UpdateData(FALSE);//���±༭�����ݣ���Ҫ�ǽ��ձ༭���еģ�
		//������д���

		//m_strRXData ����κ��ĳ�����н�������������








		updateMainDlg();

	
		//	PostMessage(WM_MYSYNCHR, c, 0);
		HWND hwnd = ::FindWindow(NULL, L"ʵʱ������ʾ");
		::PostMessage(hwnd, WM_MYSYNCHR,mList.mUpdate->id,0);
		hwnd = ::FindWindow(NULL, L"Instrument Panel");
		::PostMessage(hwnd, WM_MYSYNCHR, mList.mUpdate->id, 0);






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

}


void CMainDlg::updateMainDlg()
{
	//����
	int updateFlage = 0;
	HTREEITEM hPreChildItem;
	HTREEITEM hChildItem = mMainTree.GetChildItem(hTreeNodeGlobal);
	hPreChildItem = hChildItem;
	while (hChildItem != NULL) 
	{
		if (mMainTree.GetItemData(hChildItem)== mList.mUpdate->id)
		{
		//����
			updateFlage = 1;
			break;
		}
		hChildItem = mMainTree.GetNextItem(hChildItem, TVGN_NEXT);
	}
	if (updateFlage == 0) //�²���ڵ�
	{
		if (hPreChildItem == hChildItem)//ͷ��//Ϊ��
		{
			

		}
		else//ĩβ����ڵ�
		{
			//hPreChildItem
		}
	}

}
