
// EasyEncodeAndDecodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EasyEncodeAndDecode.h"
#include "EasyEncodeAndDecodeDlg.h"
#include "afxdialogex.h"
#include <string>

using std::string;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEasyEncodeAndDecodeDlg 对话框




CEasyEncodeAndDecodeDlg::CEasyEncodeAndDecodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEasyEncodeAndDecodeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEasyEncodeAndDecodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ENCODEING_TEXT, m_editEncodingText);
	DDX_Control(pDX, IDC_EDIT_FINISH_ENCODE_PATH, m_editFinishEncodePath);
	DDX_Control(pDX, IDC_EDIT_DECODINGPATH, m_editDecodingPath);
}

BEGIN_MESSAGE_MAP(CEasyEncodeAndDecodeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ENCODE, &CEasyEncodeAndDecodeDlg::OnBnClickedButtonEncode)
	ON_BN_CLICKED(IDC_BUTTON_DECODE, &CEasyEncodeAndDecodeDlg::OnBnClickedButtonDecode)
END_MESSAGE_MAP()


// CEasyEncodeAndDecodeDlg 消息处理程序

BOOL CEasyEncodeAndDecodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEasyEncodeAndDecodeDlg::OnPaint()
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
HCURSOR CEasyEncodeAndDecodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int EnCode(char* szText, int iSize)
{
	for ( int i = 0; i<iSize; ++i )
	{
		szText[i] = ~(szText[i])+10;
	}
	return 0;
}


void CEasyEncodeAndDecodeDlg::OnBnClickedButtonEncode()
{
	CString cstreditEncodingText;
	m_editEncodingText.GetWindowText(cstreditEncodingText);
	string streditEncodingText((char*)cstreditEncodingText.GetBuffer(), cstreditEncodingText.GetLength()*2);
	EnCode((char*)streditEncodingText.c_str(), streditEncodingText.length());
	CString cstreditFinishEncodePath;
	m_editFinishEncodePath.GetWindowText(cstreditFinishEncodePath);
	if ( cstreditFinishEncodePath.IsEmpty() )
	{
		cstreditFinishEncodePath = L"D:\\EncodeFile.zb";
	}

	FILE* fp = nullptr;
	_wfopen_s(&fp, cstreditFinishEncodePath.GetBuffer(), L"wb");
	fwrite( streditEncodingText.c_str(), 1, streditEncodingText.length(), fp );
	fclose(fp);

}

void Decode(char* pDecode, int iSize)
{
	for ( int i = 0; i<iSize; ++i )
	{
		pDecode[i] = ~(pDecode[i] -10);
	}
}


void CEasyEncodeAndDecodeDlg::OnBnClickedButtonDecode()
{
	CString cstrDecodingPath;
	m_editDecodingPath.GetWindowText(cstrDecodingPath);
	if ( cstrDecodingPath.IsEmpty() )
	{
		cstrDecodingPath = L"D:\\EncodeFile.zb";
	}

	FILE* fp = nullptr;
	_wfopen_s(&fp, cstrDecodingPath.GetBuffer(), L"rb");
	fseek( fp, 0, SEEK_END );
	long filesize = ftell(fp); 
	char* pBuf = new char[filesize+2];
	pBuf[filesize] = 0;
	pBuf[filesize+1] = 0;
	fseek(fp, 0, SEEK_SET);
	fread(pBuf, 1, filesize, fp);
	fclose(fp);
	Decode(pBuf, filesize);
	CString cstBuf((WCHAR*)pBuf, filesize/2);
	m_editEncodingText.SetWindowText( cstBuf );	
}
