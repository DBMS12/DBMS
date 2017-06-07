
// DBMSMFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMSMFC.h"
#include "DBMSMFCDlg.h"
#include "afxdialogex.h"
#include "CreateDBDlg.h"
#include "CreateTBDlg.h"
#include "Tree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT indicators[] = { ID_INDICATOR_NUM, ID_INDICATOR_EXT };//du

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDBMSMFCDlg �Ի���



CDBMSMFCDlg::CDBMSMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDBMSMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDBMSMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_programLangList);
	//DDX_Control(pDX, IDC_TREE1, m_tc);
	DDX_Control(pDX, IDC_TREE1, m_tc);
}

BEGIN_MESSAGE_MAP(CDBMSMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_DATABASE_CREATEDATABASE, &CDBMSMFCDlg::OnDatabaseCreatedatabase)
	ON_COMMAND(ID_TABLE_CREATETABLE, &CDBMSMFCDlg::OnTableCreatetable)
	ON_COMMAND(ID_SYSTEM_EXIT, &CDBMSMFCDlg::OnSystemExit)
	ON_COMMAND(ID_HELP_ABOUTDBMS, &CDBMSMFCDlg::OnHelpAboutdbms)
END_MESSAGE_MAP()


// CDBMSMFCDlg ��Ϣ�������

BOOL CDBMSMFCDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	//���״̬�� *** 
	CRect rect;
	CRect stateRect;
	if (!m_StatusBar.Create(this) || !m_StatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("Can't create status bar\n");
		return false;
	}
	m_StatusBar.GetClientRect(&stateRect);
	m_StatusBar.MoveWindow(0, rect.bottom - stateRect.Height(), rect.right, stateRect.Height());// ����״̬����λ�úʹ�С  
	m_StatusBar.SetPaneInfo(0, m_StatusBar.GetDlgCtrlID(), SBPS_NOBORDERS, 250);//����״̬���Ŀ��  
	m_StatusBar.SetPaneInfo(1, m_StatusBar.GetDlgCtrlID(), SBPS_STRETCH, 20);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);//��ʾ״̬��du


	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_programLangList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_programLangList.SetExtendedStyle(m_programLangList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Ϊ�б���ͼ�ؼ��������   
	m_programLangList.InsertColumn(0, _T("Field1"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_programLangList.InsertColumn(1, _T("Field2"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_programLangList.InsertColumn(2, _T("Field3"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_programLangList.InsertColumn(3, _T("Field4"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_programLangList.InsertColumn(4, _T("Field5"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_programLangList.InsertColumn(5, _T("Field6"), LVCFMT_CENTER, rect.Width() / 6, 5);


	

	//toolbar��ʾ***
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)
		|| !m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("����������ʧ�ܣ�");
		return TRUE;
	}
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	//CString dbname;
	//Tree tr;
	//tr.createT1(dbname);


	//tree control***
	HICON hIcon[3];      // ͼ��������   
	// ��������ͼ�꣬�������ǵľ�����浽����   
	hIcon[0] = theApp.LoadIcon(IDI_DB_ICON);
	hIcon[1] = theApp.LoadIcon(IDI_TABLE_ICON);
	hIcon[2] = theApp.LoadIcon(IDI_DOC_ICON);

	// ����ͼ������CImageList����   
	m_imageList.Create(16, 16, ILC_COLOR32, 3, 3);
	// ������ͼ����ӵ�ͼ������   
	for (int i = 0; i<3; i++)
	{
		m_imageList.Add(hIcon[i]);
	}

	// Ϊ���οؼ�����ͼ������   
	m_tc.SetImageList(&m_imageList, TVSIL_NORMAL);

	//����ָ��ڵ�ľ��
	HTREEITEM hItem;
	HTREEITEM hSubItem;
	HTREEITEM hSubThreeItem;

	//����ڵ�
	//�ڸ��������� Parent1
	hItem = m_tc.InsertItem(L"Parent1", 0, 0, TVI_ROOT);
	m_tc.SetItemData(hItem, 1);

	//�� Parent1 �����һ���ӽ�� Child1_1
	hSubItem = m_tc.InsertItem(L"Child1_1", hItem);
	m_tc.SetItemImage(hSubItem, 1, 1);//��ɱ�ͼ��

	//�� Parent1 �����һ���ӽ��Child1_2������ Child1_1 ����
	hSubItem = m_tc.InsertItem(L"Child1_2", hItem, hSubItem);
	m_tc.SetItemImage(hSubItem, 1, 1);//��ɱ�ͼ��

	hSubThreeItem = m_tc.InsertItem(L"Child11_1", hSubItem);//������--�ֶ�
	m_tc.SetItemImage(hSubThreeItem, 2, 2);//���DOCͼ��






	//*************
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDBMSMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDBMSMFCDlg::OnPaint()
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
HCURSOR CDBMSMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDBMSMFCDlg::OnDatabaseCreatedatabase()
{
	// �������ݿ�Ի�����Ӧ
	CreateDBDlg dlg;
	dlg.DoModal();
}

void CDBMSMFCDlg::OnTableCreatetable()
{
	// ������Ի�����Ӧ
	CreateTBDlg dlg;
	dlg.DoModal();
}


void CDBMSMFCDlg::OnSystemExit()
{
	// �˳�����
	exit(0);
}


void CDBMSMFCDlg::OnHelpAboutdbms()
{
	// help ����DBMS

	MessageBox(L"���ݿ����ϵͳ,database management system.\n���dbms,��һ�ֲ��ݺ͹������ݿ�Ĵ������.\n���ڽ�����ʹ�ú�ά�����ݿ�.\n�û�ͨ��dbms�������ݿ��е�����.\n���ݿ����ԱҲͨ��dbms�������ݿ��ά������.\n����ʹ���Ӧ�ó�����û��ò�ͬ�ķ�����ͬʱ\n��ͬʱ��ȥ�������޸ĺ�ѯ�����ݿ�.", _T("ABOUT DBMS"), MB_OK);
}
