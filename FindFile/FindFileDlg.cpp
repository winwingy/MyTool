// FindFileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FindFile.h"
#include "FindFileDlg.h"
#include ".\findfiledlg.h"
#include "process.h"
#include <vector>
#include <string>
using std::vector;
using std::string;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int FIND_BY_NAME = 1;
const int FIND_BY_SIZE = 2;




void GetHardDisks(vector<string>& vecHardDisks)
{
	
	TCHAR pszPerDriver[10];
	TCHAR szBuf[100];
	memset(szBuf, 0, sizeof(szBuf));
	DWORD dwLenth = GetLogicalDriveStrings(sizeof(szBuf)/sizeof(TCHAR), szBuf);
	for (TCHAR* pTemp = szBuf; *pTemp; pTemp += _tcslen(pTemp) + 1)//"C:\<>D:\<><>"
	{
		sprintf(szBuf, "%s",pTemp);
		UINT uType = GetDriveType(szBuf);
		if (uType == DRIVE_FIXED)
		{
			vecHardDisks.push_back(szBuf);			
		}
	}	
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

unsigned __stdcall FindThread(void* pArguments)
{
	CFindFileDlg* pThisDlg = (CFindFileDlg*)(pArguments);
	pThisDlg->m_bIsFinding = true;
		
	vector<string> vecHardDisks;

	GetHardDisks(vecHardDisks);	

	
	for (vector<string>::iterator itHardDisks = vecHardDisks.begin(); 
		itHardDisks != vecHardDisks.end(); 
		itHardDisks++)
	{
		//itHardDisks[itHardDisks->size() - 1] = 0;
		pThisDlg->FindPerDriver(itHardDisks->c_str(), pThisDlg->m_iFindByWhat);
	}
	if ( pThisDlg->m_iFindByWhat == FIND_BY_NAME )
	{
		pThisDlg->m_btnFindWay1.SetWindowText("查找完咯");
	}
	else
	{
		pThisDlg->m_btnFindWay2.SetWindowText("查找完咯");
	}
	

	pThisDlg->m_bIsFinding = false;
	return 0;
}

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


// CFindFileDlg 对话框



CFindFileDlg::CFindFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindFileDlg::IDD, pParent),m_dwHighSize(0),m_iLineNum(0),m_iFindByWhat(FIND_BY_NAME),
	m_bIsFinding(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFindFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_SHOW, m_editShowPath);
	DDX_Control(pDX, IDC_BUTTON_FINDWAY1, m_btnFindWay1);
	DDX_Control(pDX, IDC_BUTTON_FINDWAY2, m_btnFindWay2);
	DDX_Control(pDX, IDC_EDIT_SIZE, m_editSize);
}

BEGIN_MESSAGE_MAP(CFindFileDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_FINDWAY1, OnBnClickedButtonFindway1)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_EDIT_NAME, OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_SIZE, OnEnChangeEditSize)
	ON_BN_CLICKED(IDC_BUTTON_FINDWAY2, OnBnClickedButtonFindway2)
END_MESSAGE_MAP()


// CFindFileDlg 消息处理程序

BOOL CFindFileDlg::OnInitDialog()
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

	CRect rect;
	GetDlgItem(IDC_EDIT_SHOW)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	
	m_iShowPathLeft = rect.left;
	m_iShowPathTop = rect.top;

	m_editShowPath.SetLimitText(0xFFFFFFFF);//设置edit字数限制
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CFindFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFindFileDlg::OnPaint() 
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
HCURSOR CFindFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFindFileDlg::OnBnClickedButtonFindway1()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_bIsFinding == true )
	{
		MessageBox("正在查找中");
		return;
	}

	m_editShowPath.SetWindowText("");
	m_iLineNum = 0;

	 m_editName.GetWindowText(m_cstrFindName);

	if (m_cstrFindName == "")
	{
		MessageBox("名字为空");
		return;
	}

	m_btnFindWay1.SetWindowText("正在查找中........");

	this->m_iFindByWhat = FIND_BY_NAME;

	CloseHandle( (HANDLE)_beginthreadex(NULL, 0, FindThread, this, 0 , NULL) );

}


void CFindFileDlg::FindPerDriver(const CHAR* pszDriver, int iType)
{
	LPSTR pszFindName = m_cstrFindName.GetBuffer();

	CHAR pszPath[1024] = {0};
	sprintf(pszPath, "%s//*.*", pszDriver);
	WIN32_FIND_DATA findData = {0};
	HANDLE hFind = FindFirstFile(pszPath, &findData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	try
	{
		do 
		{
			if (findData.cFileName[0] == '.')
			{
				continue;
			}
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{

				TCHAR szFile[1024];
				sprintf(szFile, "%s\\%s", pszDriver, findData.cFileName);
				//TRACE("%s\n", szFile);

				int iFind = 0;
				if (iType == FIND_BY_NAME)
				{
					if (strstr(findData.cFileName, pszFindName) != NULL)
					{
						iFind = 1;
					}
					else
					{
						iFind = 0;
					}
				}
				if (iFind > 0)
				{
					//m_cstrShowPath.Format("%d", m_iLineNum++);
					m_cstrShowPath = szFile;
					m_cstrShowPath += "\r\n";
					int iLen = ::GetWindowTextLength(m_editShowPath.m_hWnd);
					m_editShowPath.SetSel(iLen, iLen);
					m_editShowPath.ReplaceSel(m_cstrShowPath);
					m_editShowPath.LineScroll(m_editShowPath.GetLineCount());
				
				}		
								
				FindPerDriver(szFile, iType);
			}
			else
			{
				TCHAR szFile[1024];
				sprintf(szFile, "%s\\%s", pszDriver, findData.cFileName);
				//TRACE("%s\n", szFile);
				int iFind = 0;
				if (iType == FIND_BY_NAME)
				{
					if (strstr(findData.cFileName, pszFindName) != NULL)
					{
						iFind = 1;
					}
					else
					{
						iFind = 0;
					}
				}
				else
				{
					if ( findData.nFileSizeHigh > m_dwHighSize || (findData.nFileSizeLow > m_dwLowSize && m_dwHighSize == 0) )
					{
						iFind = 1;
					}
					else
					{
						iFind = 0;
					}
				}
				if (iFind > 0)
				{
					//m_cstrShowPath.Format("%d", m_iLineNum++);
					m_cstrShowPath = szFile;
					m_cstrShowPath += "\r\n";
					int iLen = ::GetWindowTextLength(m_editShowPath.m_hWnd);
					m_editShowPath.SetSel(iLen, iLen);
					m_editShowPath.ReplaceSel(m_cstrShowPath);
					m_editShowPath.LineScroll(m_editShowPath.GetLineCount());
				}	
			}
		} while (FindNextFile(hFind, &findData));
	}
	catch (CMemoryException* e)
	{
		TRACE("CMemoryException\n");
	}
	catch (CFileException* e)
	{
		TRACE("CFileException\n");
	}
	catch (CException* e)
	{
		TRACE("CException\n");
	}
	
}


void CFindFileDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	HDWP hDwp = BeginDeferWindowPos(1);
	DeferWindowPos(hDwp, ::GetDlgItem(m_hWnd, IDC_EDIT_SHOW), NULL, m_iShowPathLeft, m_iShowPathTop, cx - m_iShowPathLeft*2, cy - m_iShowPathTop - 10, SWP_NOACTIVATE|SWP_NOZORDER);
	//m_editShowPath.SetWindowPos(&wndTop, m_iShowPathLeft, m_iShowPathTop, cx - m_iShowPathLeft*2, cy - m_iShowPathTop - 10, SWP_SHOWWINDOW);
	EndDeferWindowPos(hDwp);
}

void CFindFileDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类


	//CDialog::OnOK();
}

void CFindFileDlg::OnEnChangeEditName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	m_iEnterFocus = 1;
	// TODO:  在此添加控件通知处理程序代码
}

void CFindFileDlg::OnEnChangeEditSize()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	m_iEnterFocus = 2;
	// TO	DO:  在此添加控件通知处理程序代码
}

BOOL CFindFileDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			if (m_iEnterFocus == 1)
			{
				OnBnClickedButtonFindway1();
			}
			if (m_iEnterFocus == 2)
			{
				OnBnClickedButtonFindway2();
			}
		}
		
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CFindFileDlg::OnBnClickedButtonFindway2()
{
	if ( m_bIsFinding == true )
	{
		MessageBox("正在查找中");
		return;
	}
	

	m_editShowPath.SetWindowText("");
	m_iLineNum = 0;

	CString cstrSize;
	m_editSize.GetWindowText(cstrSize);//以MB为单位的
	if (cstrSize == "")
	{
		MessageBox("大小不能为空或为负为0");
		return;
	}
	double dSize = double(atof(cstrSize) * 1024 * 1024);
	if (dSize < 0)
	{
		MessageBox("大小不能为空或为负为0");
		return;
	}
	DWORD dwBigist = 0xFFFFFFFF;
	double dDwordBigist = double(dwBigist);
	if (dSize > dDwordBigist )
	{
		m_dwHighSize = 1;
	}
	else
	{
		m_dwHighSize = 0;
		m_dwLowSize = (DWORD)dSize;
	}

	if (m_dwLowSize == 0)
	{
		MessageBox("大小不能为空或为负为0");
		return;
	}

	m_btnFindWay2.SetWindowText("正在查找中........");

	m_iFindByWhat = FIND_BY_SIZE;

	CloseHandle( (HANDLE)_beginthreadex(NULL, 0, FindThread, this, 0, NULL) );
}
