
// DBMSMFCDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDBMSMFCDlg 对话框



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


// CDBMSMFCDlg 消息处理程序

BOOL CDBMSMFCDlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码

	//添加状态栏 *** 
	CRect rect;
	CRect stateRect;
	if (!m_StatusBar.Create(this) || !m_StatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("Can't create status bar\n");
		return false;
	}
	m_StatusBar.GetClientRect(&stateRect);
	m_StatusBar.MoveWindow(0, rect.bottom - stateRect.Height(), rect.right, stateRect.Height());// 调整状态栏的位置和大小  
	m_StatusBar.SetPaneInfo(0, m_StatusBar.GetDlgCtrlID(), SBPS_NOBORDERS, 250);//设置状态栏的宽度  
	m_StatusBar.SetPaneInfo(1, m_StatusBar.GetDlgCtrlID(), SBPS_STRETCH, 20);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);//显示状态栏du


	// 获取编程语言列表视图控件的位置和大小   
	m_programLangList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_programLangList.SetExtendedStyle(m_programLangList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加三列   
	m_programLangList.InsertColumn(0, _T("Field1"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_programLangList.InsertColumn(1, _T("Field2"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_programLangList.InsertColumn(2, _T("Field3"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_programLangList.InsertColumn(3, _T("Field4"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_programLangList.InsertColumn(4, _T("Field5"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_programLangList.InsertColumn(5, _T("Field6"), LVCFMT_CENTER, rect.Width() / 6, 5);


	

	//toolbar显示***
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)
		|| !m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("工具条创建失败！");
		return TRUE;
	}
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	//CString dbname;
	//Tree tr;
	//tr.createT1(dbname);


	//tree control***
	HICON hIcon[3];      // 图标句柄数组   
	// 加载三个图标，并将它们的句柄保存到数组   
	hIcon[0] = theApp.LoadIcon(IDI_DB_ICON);
	hIcon[1] = theApp.LoadIcon(IDI_TABLE_ICON);
	hIcon[2] = theApp.LoadIcon(IDI_DOC_ICON);

	// 创建图像序列CImageList对象   
	m_imageList.Create(16, 16, ILC_COLOR32, 3, 3);
	// 将三个图标添加到图像序列   
	for (int i = 0; i<3; i++)
	{
		m_imageList.Add(hIcon[i]);
	}

	// 为树形控件设置图像序列   
	m_tc.SetImageList(&m_imageList, TVSIL_NORMAL);

	//声明指向节点的句柄
	HTREEITEM hItem;
	HTREEITEM hSubItem;
	HTREEITEM hSubThreeItem;

	//插入节点
	//在根结点上添加 Parent1
	hItem = m_tc.InsertItem(L"Parent1", 0, 0, TVI_ROOT);
	m_tc.SetItemData(hItem, 1);

	//在 Parent1 上添加一个子结点 Child1_1
	hSubItem = m_tc.InsertItem(L"Child1_1", hItem);
	m_tc.SetItemImage(hSubItem, 1, 1);//变成表图标

	//在 Parent1 上添加一个子结点Child1_2，排在 Child1_1 后面
	hSubItem = m_tc.InsertItem(L"Child1_2", hItem, hSubItem);
	m_tc.SetItemImage(hSubItem, 1, 1);//变成表图标

	hSubThreeItem = m_tc.InsertItem(L"Child11_1", hSubItem);//第三级--字段
	m_tc.SetItemImage(hSubThreeItem, 2, 2);//变成DOC图标






	//*************
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDBMSMFCDlg::OnPaint()
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
HCURSOR CDBMSMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDBMSMFCDlg::OnDatabaseCreatedatabase()
{
	// 创建数据库对话框响应
	CreateDBDlg dlg;
	dlg.DoModal();
}

void CDBMSMFCDlg::OnTableCreatetable()
{
	// 创建表对话框响应
	CreateTBDlg dlg;
	dlg.DoModal();
}


void CDBMSMFCDlg::OnSystemExit()
{
	// 退出程序
	exit(0);
}


void CDBMSMFCDlg::OnHelpAboutdbms()
{
	// help 关于DBMS

	MessageBox(L"数据库管理系统,database management system.\n简称dbms,是一种操纵和管理数据库的大型软件.\n用于建立、使用和维护数据库.\n用户通过dbms访问数据库中的数据.\n数据库管理员也通过dbms进行数据库的维护工作.\n它可使多个应用程序和用户用不同的方法在同时\n或不同时刻去建立，修改和询问数据库.", _T("ABOUT DBMS"), MB_OK);
}
