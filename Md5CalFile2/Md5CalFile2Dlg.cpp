
// Md5CalFile2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Md5CalFile2.h"
#include "Md5CalFile2Dlg.h"
#include "afxdialogex.h"
#include "md5.h"
#include <Windows.h>
#include <string>
#include <tchar.h>
using std::string;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMd5CalFile2Dlg 对话框




CMd5CalFile2Dlg::CMd5CalFile2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMd5CalFile2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMd5CalFile2Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_editPath);
    DDX_Control(pDX, IDC_EDIT2, m_showMd5Lower);
    DDX_Control(pDX, IDC_EDIT3, m_showMd5Upper);
}

BEGIN_MESSAGE_MAP(CMd5CalFile2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CMd5CalFile2Dlg::OnBnClickedButton1)
    ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMd5CalFile2Dlg 消息处理程序

BOOL CMd5CalFile2Dlg::OnInitDialog()
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

void CMd5CalFile2Dlg::OnPaint()
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
HCURSOR CMd5CalFile2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

class FileMap
{
public:
    FileMap()
        : hFileMapping(INVALID_HANDLE_VALUE)
        , lpBuffer(NULL)
    {
    }

    void* CreateFileMap(const wchar_t* szPath, LARGE_INTEGER* liSize)
    {
        void* retBuf = nullptr;
        HANDLE hFile = INVALID_HANDLE_VALUE;
        do 
        {
            hFile = CreateFile( szPath, GENERIC_READ|GENERIC_WRITE, 
                0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if ( hFile == INVALID_HANDLE_VALUE )
            {
                break;
            }

            GetFileSizeEx( hFile, liSize );
            unsigned __int64 ullSize = liSize->QuadPart;

            hFileMapping = CreateFileMapping(
                hFile, NULL, PAGE_READWRITE, 
                DWORD( liSize->HighPart ), DWORD( liSize->LowPart ), NULL );
            if( !hFileMapping )
            {
                break;
            } 
            char* lpBuffer = (char*)MapViewOfFileEx( 
                hFileMapping, FILE_MAP_WRITE, 0, 0, liSize->LowPart, NULL );

            if( !lpBuffer )
            {
                break;
            }
            retBuf = lpBuffer;
        } while (0);
        if (hFile != INVALID_HANDLE_VALUE)
        {
            CloseHandle(hFile);
        }
        return retBuf;
    }

    ~FileMap()
    {
        if (lpBuffer)
        {
            UnmapViewOfFile(lpBuffer);
            lpBuffer = nullptr;
        }
        if (hFileMapping)
        {
            CloseHandle(hFileMapping);
            hFileMapping = nullptr;
        }
    }

private:

    HANDLE hFileMapping;
    char* lpBuffer;
};

std::wstring Md5Partially( unsigned char* szInput, int iLength, int iPer )//abcde 2
{	
    MD5_CTX mc = {0};
    MD5Init( &mc );	
    for (; iLength >= iPer ; szInput += iPer, iLength -= iPer)
    {
        MD5Update(&mc, szInput, iPer);
    }
    if ( iLength >= 0 )
    {
        MD5Update(&mc, szInput, iLength);
    }	
    MD5Final(&mc);

    wchar_t szRet[3] = {0};

    std::wstring strRet;

    for (int i = 0; i < 16; ++i)
    {
        _stprintf_s(szRet, L"%02X", mc.digest[i]);
        strRet += szRet;
    }
    return strRet;
}

void CMd5CalFile2Dlg::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    m_showMd5Lower.SetWindowTextW(L"");
    m_showMd5Upper.SetWindowTextW(L"");
    LARGE_INTEGER liSize = { 0 };
    CString path;
    m_editPath.GetWindowTextW(path);
    FileMap fileMap;
    char* lpBuffer = (char*)fileMap.CreateFileMap(path.GetBuffer(), &liSize);
    std::wstring strRet = Md5Partially((unsigned char*)lpBuffer, 
        liSize.LowPart, 80*1024);
   
    m_showMd5Upper.SetWindowTextW(strRet.c_str());

    for (unsigned int i = 0; i < strRet.size(); ++i)
    {
        if ( strRet[i] >= L'A' && strRet[i] <= L'Z')
        {
            strRet[i] = strRet[i] - L'A' + L'a';
        }
    }
    m_showMd5Lower.SetWindowTextW(strRet.c_str());
}


void CMd5CalFile2Dlg::OnDropFiles(HDROP hDropInfo)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    WCHAR pszPath[MAX_PATH] = {0};
    UINT nFileNum = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);//DragQueryFile为0xFFFFFFFF的时候返回拖曳文件的个数
    DragQueryFile(hDropInfo, nFileNum - 1, pszPath, MAX_PATH);//获得拖曳的最后一个文件的文件名
    DragFinish(hDropInfo);	//用完记得释放掉hDropInfo

    m_editPath.SetWindowText(pszPath);
    m_editPath.UpdateData(FALSE);
    CDialogEx::OnDropFiles(hDropInfo);
}
