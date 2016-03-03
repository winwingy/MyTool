// ShortCutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShortCut.h"
#include "ShortCutDlg.h"
#include ".\shortcutdlg.h"

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


// CShortCutDlg 对话框



CShortCutDlg::CShortCutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShortCutDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShortCutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SHOW, m_editShow);
}

BEGIN_MESSAGE_MAP(CShortCutDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnBnClickedButtonChange)
	ON_EN_CHANGE(IDC_EDIT_SHOW, OnEnChangeEditShow)
	ON_BN_CLICKED(IDC_BTN_Divide, OnBnClickedBtnDivide)
END_MESSAGE_MAP()


// CShortCutDlg 消息处理程序

BOOL CShortCutDlg::OnInitDialog()
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
	ZeroMemory(m_pszPath, MAX_PATH);
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CShortCutDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShortCutDlg::OnPaint() 
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
HCURSOR CShortCutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CShortCutDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	UINT nFileNum = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);//DragQueryFile为0xFFFFFFFF的时候返回拖曳文件的个数
	DragQueryFile(hDropInfo, nFileNum - 1, m_pszPath, MAX_PATH);//获得拖曳的最后一个文件的文件名
	DragFinish(hDropInfo);	//用完记得释放掉hDropInfo
	TRACEONE("%s\n",m_pszPath);
	m_editShow.SetWindowText(m_pszPath);
	m_editShow.UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}

void CShortCutDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pszPath[0] == 0 )
	{
		CString cstrText;
		m_editShow.GetWindowText(cstrText);
		if (cstrText[0] == 0)
		{
			m_editShow.SetWindowText("没有文件");
			m_editShow.UpdateData(FALSE);
			return;
		}
		sprintf(m_pszPath, "%s", cstrText);
		//strcpy(m_pszPath, cstrText);	
		TRACE("IN   %s\n",m_pszPath );

	}

	TRACE("%s\n", m_pszPath);
	FILE* fp;
	fp = fopen(m_pszPath, "r");
	if (fp == NULL)
	{
		CString cstrText = "打不开";
		cstrText += m_pszPath;
		m_editShow.SetWindowText(cstrText);
		m_editShow.UpdateData(FALSE);
		return;
	}
	FILE* fpOut;
	CString cstrNewPath = RemoveSuffix(m_pszPath);
	cstrNewPath += "_cut";
	cstrNewPath += GetSuffix(m_pszPath);
	TRACEONE("%s\n", cstrNewPath);


	fpOut = fopen(cstrNewPath, "w");
	if (fpOut == NULL)
	{
		CString cstrText = "建新文件失败";
		
		m_editShow.SetWindowText(cstrText);
		m_editShow.UpdateData(FALSE);
		return;
	}
	CHAR cstrRead[LINE_NUM];
	CHAR szAdd;
	int iRes = 0;

	CString cstrShowOut;
	CString cstrTemp;

	while( (iRes = fread(cstrRead, 1, LINE_NUM, fp)) > 0 )
	{
		cstrShowOut = "";
		TRACEONE("%d    %c\n", iRes, cstrRead[iRes -1]);
		
		fwrite(cstrRead, 1, iRes, fpOut);
		for (int j = 0; j < iRes; j++)
		{
			cstrTemp.Format("%c", cstrRead[j]);
			cstrShowOut += cstrTemp;
		}

		int i = 0;
		while(i < iRes)
		{
			if (IsDBCSLeadByte(cstrRead[i]))// 只能用于判断第一个字节的    abc你
			{
				i = i+2;
			}
			else
			{
				i++;
			}
		}

		if ( i > iRes )
		{			
			fread(cstrRead, 1, 1, fp);
			fwrite(cstrRead, 1, 1, fpOut);
			cstrTemp.Format("%c", cstrRead[0]);
			cstrShowOut += cstrTemp;		
		}

		if (iRes == LINE_NUM)
		{
			cstrRead[0] = '\r';
			cstrRead[1] = '\n';
			fwrite(cstrRead, 1,2 , fpOut);
			for (int j = 0; j < 2; j++)
			{
				cstrTemp.Format("%c", cstrRead[j]);
				cstrShowOut += cstrTemp;
			}
		}
		cstrShowOut += "\r\n";
		TRACE("%s", cstrShowOut);
		
	}	

	fclose(fp);
	fclose(fpOut);
	MessageBox("Wait");
	MessageBox("Finish");
}
CString CShortCutDlg::RemoveSuffix(CString cstrRhs)
{
	int i = 0;
	int iLen = cstrRhs.GetLength();
	int pos = 0;
	for (; i < iLen; i++ )
	{
		if ( cstrRhs.GetAt(i) == '.')
		{
			pos = i;
		}
	}
	ASSERT(pos > 0);
	CString cstrRes = cstrRhs.Left(pos);
	return cstrRes;
}
CString CShortCutDlg::GetSuffix(CString cstrRhs)
{
	int i = 0;
	int iLen = cstrRhs.GetLength();
	int pos = 0;
	for (; i < iLen; i++ )
	{
		if ( cstrRhs.GetAt(i) == '.')
		{
			pos = i;
		}
	}
	ASSERT(pos > 0);
	CString cstrRes = cstrRhs.Right(iLen - pos  ); //a.txt
	return cstrRes;
}
void CShortCutDlg::OnEnChangeEditShow()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	
	// TODO:  在此添加控件通知处理程序代码
	
}

void CShortCutDlg::OnBnClickedBtnDivide()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pszPath[0] == 0 )
	{
		CString cstrText;
		m_editShow.GetWindowText(cstrText);
		if (cstrText[0] == 0)
		{
			m_editShow.SetWindowText("没有文件");
			m_editShow.UpdateData(FALSE);
			return;
		}
		sprintf(m_pszPath, "%s", cstrText);
		//strcpy(m_pszPath, cstrText);	
		TRACE("IN   %s\n",m_pszPath );

	}

	TRACE("%s\n", m_pszPath);
	FILE* fp;
	fp = fopen(m_pszPath, "r");
	if (fp == NULL)
	{
		CString cstrText = "打不开";
		cstrText += m_pszPath;
		m_editShow.SetWindowText(cstrText);
		m_editShow.UpdateData(FALSE);
		return;
	}
	FILE* fpOut;
	CString cstrNewPath;
	CString cstrFileName = RemoveSuffix(m_pszPath);
	cstrNewPath += cstrFileName;
	cstrNewPath += "_001";
	CString cstrSuffix = GetSuffix(m_pszPath);
	cstrNewPath += cstrSuffix;
	TRACEONE("%s\n", cstrNewPath);


	fpOut = fopen(cstrNewPath, "w");
	if (fpOut == NULL)
	{
		CString cstrText = "建新文件失败";

		m_editShow.SetWindowText(cstrText);
		m_editShow.UpdateData(FALSE);
		return;
	}
	CHAR cstrRead[BOOK_FULL_COUNT];
	CHAR szAdd;
	int iRes = 0;
	int ibook = 1;

	CString cstrShowOut;
	CString cstrTemp;

	while( (iRes = fread(cstrRead, 1, BOOK_FULL_COUNT, fp)) > 0 )
	{
		cstrShowOut = "";
		//TRACEONE("%d    %c\n", iRes, cstrRead[iRes -1]);
		fwrite(cstrRead, 1, iRes, fpOut);
		ibook++;
		fclose(fpOut);	

		cstrTemp.Format("_%03d", ibook);
		cstrNewPath = "";		
		cstrNewPath += cstrFileName;
		cstrNewPath += cstrTemp;	
		cstrNewPath += cstrSuffix;

		fpOut = fopen(cstrNewPath, "w");
		if (fpOut == NULL)
		{
			CString cstrText = "建新文件失败";

			m_editShow.SetWindowText(cstrText);
			m_editShow.UpdateData(FALSE);
			return;
		}

	}	

	fclose(fp);
	
}
