// DivideStringDailyUseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DivideStringDailyUse.h"
#include "DivideStringDailyUseDlg.h"
#include ".\dividestringdailyusedlg.h"


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


// CDivideStringDailyUseDlg 对话框



CDivideStringDailyUseDlg::CDivideStringDailyUseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDivideStringDailyUseDlg::IDD, pParent)
	, m_bIsFile(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDivideStringDailyUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SOURCE, m_editSource);
	DDX_Control(pDX, IDC_EDIT_DIVIDE_SYMBOL, m_editDivideSymbol);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
	DDX_Control(pDX, IDC_CHECK_TO_NEW_TXT, m_chkToNewTXT);
}

BEGIN_MESSAGE_MAP(CDivideStringDailyUseDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BTN_START, OnBnClickedBtnStart)
END_MESSAGE_MAP()


// CDivideStringDailyUseDlg 消息处理程序

BOOL CDivideStringDailyUseDlg::OnInitDialog()
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

	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CDivideStringDailyUseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDivideStringDailyUseDlg::OnPaint() 
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
HCURSOR CDivideStringDailyUseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDivideStringDailyUseDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int iCnt = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);//返回拖曳的个数
	if ( iCnt >= 1 )
	{	
		char szName[MAX_PATH] = {0};
		DragQueryFile( hDropInfo, iCnt -1, szName, sizeof(szName) );
		m_editSource.SetWindowText(szName);
		m_cstrSourceName = szName;
		m_bIsFile = true;
		m_chkToNewTXT.SetCheck(BST_CHECKED);
	}


	CDialog::OnDropFiles(hDropInfo);
}

void CDivideStringDailyUseDlg::DivideStringBySymbol(const string& strIn, const vector<string>& vecSymbol,
													vector<string>& vecHasDivide)
{	
	vector<int> vecDivideIndex;			//分割符的下标
	vector<int>::iterator itrDivideIndex;

	vector<string>::const_iterator itrSymbol;	
	int iTempIndex;	
	
	//;,asfdsafsasd;,adfasdf;ree
	for ( itrSymbol = vecSymbol.begin(); itrSymbol != vecSymbol.end(); itrSymbol++ )//先找第一个符号的下标
	{
		int iFindIndex(0);
		do 
		{
			iTempIndex = strIn.find(*itrSymbol, iFindIndex);
			if ( iTempIndex != string::npos )
			{				
				vecDivideIndex.push_back(iTempIndex);
				iFindIndex = iTempIndex + itrSymbol->size();									
			}
			else
			{
				break;
			}
		} while (1);
	}

	if ( vecDivideIndex.size() > 0 )
	{
		vecDivideIndex.push_back(strIn.size());
		//排序并除重
		sort(vecDivideIndex.begin(), vecDivideIndex.end());
		vector<int>::iterator itNewEnd = unique(vecDivideIndex.begin(), vecDivideIndex.end());//unique只是将不重的放到前面，后面的不管
		vecDivideIndex.erase( itNewEnd, vecDivideIndex.end() );//所以必须删除后面的
		int iIndexDivide(0);
		for ( int i(0); i <= vecDivideIndex.size(); i++ )
		{
			string strHasDivide( strIn, iIndexDivide, vecDivideIndex[i] - iIndexDivide );
			if ( strHasDivide.size() > 0 && strHasDivide != "" && strHasDivide != " " && strHasDivide != "  ")
			{
				bool bIsSameSymbol(false);
				for ( itrSymbol = vecSymbol.begin(); itrSymbol != vecSymbol.end(); itrSymbol++ )
				{
					if ( strHasDivide == *itrSymbol )
					{
						bIsSameSymbol = true;
						break;
					}

				}
				if ( bIsSameSymbol == false  )
				{
					vecHasDivide.push_back(strHasDivide);
				}
			}
			//看分隔符的下标长度

			for ( itrSymbol = vecSymbol.begin(); itrSymbol != vecSymbol.end(); itrSymbol++ )
			{
				int iSymbolIndex = strIn.find(*itrSymbol,  vecDivideIndex[i]);
				if ( iSymbolIndex == vecDivideIndex[i] )
				{
					iIndexDivide = vecDivideIndex[i] + itrSymbol->size();
				}
			}

			if ( iIndexDivide >= strIn.size() )
			{
				break;
			}
		}		
	}
	if ( vecHasDivide.size() == 0 )
	{
		vecHasDivide.push_back(strIn);
	}
}

void CDivideStringDailyUseDlg::OnBnClickedBtnStart()
{
	vector<string>::iterator iter;
	m_editDivideSymbol.GetWindowText(m_cstrDivideSymbol);
	vector<string> vecDivide;
	vector<string> vecSymbol;
	vecSymbol.push_back("$");
	DivideStringBySymbol(m_cstrDivideSymbol.GetBuffer(), vecSymbol, vecDivide);
	for ( iter = vecDivide.begin(); iter!= vecDivide.end(); iter++ )
	{
		TRACE("%s\t\t", iter->c_str());
	}

	string strSource;
	
	if ( m_bIsFile )
	{
		FILE* fpRead= fopen( m_cstrSourceName.GetBuffer(), "r" );
		if ( fpRead == NULL )
		{
			TRACE("fpRead!\n");
			return;
		}
		char szRead[1024];		
		int iRead;

		while ( ( iRead = fread( szRead, sizeof(szRead[0]), sizeof(szRead), fpRead ) ) > 0 )
		{
			if ( iRead < sizeof(szRead) )
			{
				szRead[iRead] = 0;
			}
			strSource += szRead;
		}
		fclose(fpRead);

	}
	else
	{
		m_editSource.GetWindowText(m_cstrSourceName);
		strSource = m_cstrSourceName.GetBuffer();
	}
	vector<string> vecOut;
	DivideStringBySymbol(strSource, vecDivide , vecOut);
	string strResult;
	string strResultTXT;

	for ( iter = vecOut.begin(); iter!= vecOut.end(); iter++ )
	{
		TRACE("%s\t", iter->c_str());
		strResult += *iter;	
		string strTemp = *iter;		
		if ( strTemp[0] == '\n' )
		{
			strTemp.erase(0, 1);
		}
		if ( strTemp[strTemp.size() -1] == '\n' )
		{
			strTemp.erase(strTemp.size() -1, 1);
		}
		strResultTXT += strTemp;
		strResult += "\r\n";	
		strResultTXT += "\r\n";
	}

	m_editResult.SetWindowText(strResult.c_str());
	m_editResult.UpdateData(FALSE);

	//是否写入文本	
	if ( m_chkToNewTXT.GetCheck() || m_bIsFile )
	{
		if ( m_bIsFile == false )
		{
			m_cstrSourceName = "D:\\Temp.txt";
		}
		char szDrive[MAX_PATH];
		char szDir[MAX_PATH];
		char szFile[MAX_PATH];
		char szExt[MAX_PATH]; 
		_splitpath(m_cstrSourceName.GetBuffer(), szDrive, szDir, szFile, szExt );
		string strFile("New  ");
		strFile += szFile;
		char szFullPath[1024];
		_makepath(szFullPath, szDrive, szDir, strFile.c_str(), szExt);

		FILE* fpWrite =fopen(szFullPath, "w");
		if ( fpWrite == NULL  )
		{		
			TRACE("fpWrite!\n");
			return;
		}
		
		int len = fwrite( strResultTXT.c_str(), sizeof(char), strResultTXT.size(), fpWrite );
		fclose(fpWrite);
	}

	m_bIsFile = false;
}
