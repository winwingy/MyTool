// Test3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test3.h"
#include "Test3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTest3Dlg 对话框



CTest3Dlg::CTest3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTest3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CTest3Dlg::~CTest3Dlg()
{
	vector<CStatic*>::iterator iter = m_vecPSttShow.begin();
	for ( ; iter != m_vecPSttShow.end(); iter++ )
	{
		if ( *iter != NULL )
		{
			delete *iter;
			*iter = NULL;
		}
	}
}


void CTest3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT1, m_stt1);
}

BEGIN_MESSAGE_MAP(CTest3Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CTest3Dlg 消息处理程序

BOOL CTest3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_stt1.MoveWindow(-10, -20, 50, 50);
	// TODO: 在此添加额外的初始化代码
	m_pSttShow = new CStatic;
	CRect rect(100,100, 150, 150);
	m_iSttID = 2000;
	m_pSttShow->Create("aaaa", WS_CHILD|WS_VISIBLE, rect, this, m_iSttID++);	
	m_vecPSttShow.push_back(m_pSttShow);
	m_pSttShow = new CStatic;
	rect.OffsetRect(0, 50);
	m_pSttShow->Create("BB", WS_CHILD|WS_VISIBLE, rect, this, m_iSttID++);	
	m_vecPSttShow.push_back(m_pSttShow);

	m_pSttShow = new CStatic;
	rect.OffsetRect(0, 50);
	m_pSttShow->Create("BB", WS_CHILD|WS_VISIBLE, rect, this, m_iSttID++);	
	m_vecPSttShow.push_back(m_pSttShow);
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CTest3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTest3Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CTest3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
