// CntCodeLineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CntCodeLine.h"
#include "CntCodeLineDlg.h"
#include ".\cntcodelinedlg.h"

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


// CCntCodeLineDlg 对话框



CCntCodeLineDlg::CCntCodeLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCntCodeLineDlg::IDD, pParent),m_dCntLines()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCntCodeLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE, m_editFile);
}

BEGIN_MESSAGE_MAP(CCntCodeLineDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BTN_CNT, OnBnClickedBtnCnt)
END_MESSAGE_MAP()


// CCntCodeLineDlg 消息处理程序

BOOL CCntCodeLineDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	
	SetDefID(IDC_BTN_CNT);
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CCntCodeLineDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCntCodeLineDlg::OnPaint() 
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
HCURSOR CCntCodeLineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCntCodeLineDlg::OnDropFiles(HDROP hDropInfo)
{
	CHAR pszPath[MAX_PATH] = {0};
	UINT nFileNum = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);//DragQueryFile为0xFFFFFFFF的时候返回拖曳文件的个数
	DragQueryFile(hDropInfo, nFileNum - 1, pszPath, MAX_PATH);//获得拖曳的最后一个文件的文件名
	DragFinish(hDropInfo);	//用完记得释放掉hDropInfo
	
	m_editFile.SetWindowText(pszPath);
	m_editFile.UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}

void CCntCodeLineDlg::OnBnClickedBtnCnt()
{
	// TODO: 在此添加控件通知处理程序代码
	m_dCntLines = 0;
	CString cstrPath;
	m_editFile.GetWindowText(cstrPath);
	if (cstrPath == "")
	{
		m_editFile.SetWindowText("没文件");
		return;
	}
	DWORD ulAttri = 0;
	if ( (ulAttri = GetFileAttributes(cstrPath) ) == 0xFFFFFFFF)
	{
		MessageBox("文件不存在");
		return;
	}
	if (ulAttri == FILE_ATTRIBUTE_DIRECTORY)
	{
		Findfile(cstrPath);
	}
	else
	{
		m_dCntLines += cntLines( cstrPath );
	}

	cstrPath.Format("一共有%.0lf行", m_dCntLines);//控制输出格式
	m_editFile.SetWindowText(cstrPath);

	
}

//返回文件后缀名,分割文件名
CString CCntCodeLineDlg::GetSuffix(const CString& cstrPath)
{
	char driver[MAX_PATH];
	char dir[MAX_PATH];
	char fname[MAX_PATH];
	char ext[MAX_PATH];
	_splitpath(cstrPath, driver, dir, fname, ext);
	return ext;
}
void CCntCodeLineDlg::Findfile(const CString& cstrFolderFile)
{
	TCHAR szFileName[MAX_PATH] = {0};
	TCHAR szFullPathFileName[MAX_PATH] = {0};
	WIN32_FIND_DATA findData = {0};
	if ( cstrFolderFile.Right(1) != '\\' )
	{
		_stprintf( szFullPathFileName, "%s\\*.*", cstrFolderFile );
	}
	else
	{
		_stprintf( szFullPathFileName, "%s*.*", cstrFolderFile );
	}
	
	HANDLE hFind = FindFirstFile( szFullPathFileName, &findData );
	if ( INVALID_HANDLE_VALUE == hFind )
	{
		m_editFile.SetWindowText("文件不对");
		return;
	}
	bool bFinished = false;
	while ( !bFinished )
	{
		_stprintf( szFileName, "%s\\%s", cstrFolderFile, findData.cFileName );
		if ( FILE_ATTRIBUTE_DIRECTORY & findData.dwFileAttributes )
		{
			if ( _tcscmp( findData.cFileName, "." ) && _tcscmp( findData.cFileName, ".." ) )
			{
				Findfile( szFileName );

			}			
		}
		else
		{
			if ( (GetSuffix(szFileName) == ".cpp") || (GetSuffix(szFileName) == ".c") 
				|| (GetSuffix(szFileName) == ".h")
				/*|| (GetSuffix(szFileName) == ".txt")*/)
			{
				m_dCntLines += cntLines( szFileName );
			}		
		}
		if ( !FindNextFile ( hFind, &findData) )
		{
			if (ERROR_NO_MORE_FILES == GetLastError())
			{
				bFinished = true;
			}
		}
	}
}

double CCntCodeLineDlg::cntLines( const CString& cstrFileName)
{
	FILE* fp = fopen(cstrFileName, "r");
	if (fp == NULL)
	{
		MessageBox("文件打不开");
		return -1;
	}
	CHAR pstrTemp[READ_ONCE];
	double dResLines = 0.0;

//	MessageBox(cstrFileName);

	int iRes;
	while ((iRes = fread(pstrTemp, 1, READ_ONCE, fp)) > 0)
	{
		for (int i = 0; i < iRes; i++)//abcd\nabe\ana
		{
			//TRACE( "%c", pstrTemp[i] );
			if (pstrTemp[i] == '\n')
			{				
				dResLines++;				
			}
		}
	}
	if (dResLines > 0)
	{
		dResLines++;
	}

	fclose(fp);

	return dResLines;
}
