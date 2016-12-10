
// DrawDiffFontForKugouDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawDiffFontForKugou.h"
#include "DrawDiffFontForKugouDlg.h"
#include "afxdialogex.h"
#include <string>
#include <wingdi.h>
#include <WindowsX.h>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CDrawDiffFontForKugouDlg 对话框




CDrawDiffFontForKugouDlg::CDrawDiffFontForKugouDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrawDiffFontForKugouDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawDiffFontForKugouDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_TEXT, m_editText);
    DDX_Control(pDX, IDC_EDIT_FONT, m_editFont);
    DDX_Control(pDX, IDC_EDIT_SIZE, m_editSize);
    DDX_Control(pDX, IDC_STATIC_SIZE_VALUE, m_staticSizeValue);
    DDX_Control(pDX, IDC_STATIC_SHOW, m_staticShow);
    DDX_Control(pDX, IDC_STATIC_SIZE_VALUE3, m_staticShowSizeValue);
    DDX_Control(pDX, IDC_EDIT_FACTOR, m_editFactor);
}

BEGIN_MESSAGE_MAP(CDrawDiffFontForKugouDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_RUN, &CDrawDiffFontForKugouDlg::OnBnClickedButtonRun)
    ON_BN_CLICKED(IDOK, &CDrawDiffFontForKugouDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDrawDiffFontForKugouDlg 消息处理程序

BOOL CDrawDiffFontForKugouDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    m_editText.SetWindowTextW(L"我们要一起， GoGo!@");
    m_editFont.SetWindowTextW(L"黑体");
    m_editSize.SetWindowTextW(L"48");
    m_editFactor.SetWindowTextW(L"3");

    m_staticShow.ShowWindow(SW_HIDE);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDrawDiffFontForKugouDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDrawDiffFontForKugouDlg::OnPaint()
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
        CString text;
        m_editText.GetWindowTextW(text);

        CString font;
        m_editFont.GetWindowTextW(font);

        CString size;
        m_editSize.GetWindowTextW(size);
        int isize = _wtoi(size.GetBuffer());

        CString factor;
        m_editFactor.GetWindowTextW(factor);

        DrawShowText(text.GetBuffer(), font.GetBuffer(), isize,
            _wtoi(factor.GetBuffer()));
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDrawDiffFontForKugouDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





int ConvertWinFontHeightToNeg(int fontSize)
{
    if (fontSize > 0)
    {
        HDC dc = ::GetDC(nullptr);
        int nCaps = ::GetDeviceCaps(dc, LOGPIXELSY);
        if (nCaps == 0)
            nCaps = 72;
        ::ReleaseDC(nullptr, dc);

        return -::MulDiv(fontSize, nCaps, 72);
    }

    return fontSize;
}


bool GetFontSize(const std::wstring& text, const std::wstring& font,
    int size, int factor, int* fontWidth, int* fontHeight)
{
    LOGFONTW logFont = {0};
    wcscpy_s(logFont.lfFaceName, font.c_str());
    logFont.lfCharSet = GB2312_CHARSET;
    logFont.lfHeight = ConvertWinFontHeightToNeg(size) * factor;
    logFont.lfWidth *= 0;
    HFONT newFont = ::CreateFontIndirect(&logFont);
    HDC hdc = GetDC(nullptr);
    HFONT oldFont = (HFONT)::SelectObject(hdc, newFont);
    CSize curSize;
    BOOL ret = ::GetTextExtentPoint32W(
        hdc, text.c_str(), text.length(), &curSize);
    ::SelectObject(hdc, oldFont);

    ReleaseDC(nullptr, hdc);

    if (fontWidth && factor)
    {
        *fontWidth = curSize.cx / factor;
    }
    if (fontHeight && factor)
    {
        *fontHeight = curSize.cy / factor;
    }
    return !!ret;
}


void CDrawDiffFontForKugouDlg::ClearShow()
{
    m_staticShow.SetWindowTextW(L"");
    m_staticSizeValue.SetWindowTextW(L"");
    m_staticShowSizeValue.SetWindowTextW(L"");
}


void CDrawDiffFontForKugouDlg::OnBnClickedButtonRun()
{
    ClearShow();
    {
        CString text;
        m_editText.GetWindowTextW(text);

        CString font;
        m_editFont.GetWindowTextW(font);

        CString size;
        m_editSize.GetWindowTextW(size);
        int isize = _wtoi(size.GetBuffer());

        CString factor;
        m_editFactor.GetWindowTextW(factor);

        int fontWidth = 0;
        int fontHeight = 0; 
        GetFontSize(text.GetBuffer(), font.GetBuffer(), isize,
            _wtoi(factor.GetBuffer()), &fontWidth, &fontHeight);
        std::wstringstream ss;
        ss << L"要显示 的 Size：" << fontWidth << L" , " << fontHeight;
        m_staticShowSizeValue.SetWindowTextW(ss.str().c_str());

    }

    {
        CString font;
        m_editFont.GetWindowTextW(font);

        CString size;
        m_editSize.GetWindowTextW(size);
        int isize = _wtoi(size.GetBuffer());

        CString factor;
        m_editFactor.GetWindowTextW(factor);

        int fontWidth = 0;
        int fontHeight = 0; 
        GetFontSize(L"Wg", font.GetBuffer(), isize,
            _wtoi(factor.GetBuffer()), &fontWidth, &fontHeight);
        std::wstringstream ss;
        ss << L"Wg 的 Size：" << fontWidth << L" , " << fontHeight;
        m_staticSizeValue.SetWindowTextW(ss.str().c_str());
    }

    Invalidate();
}

void CDrawDiffFontForKugouDlg::DrawShowText(
    const std::wstring& text, const std::wstring& font,
    int size, int factor)
{
    CPaintDC hdc(this);
    LOGFONTW logFont = {0};
    wcscpy_s(logFont.lfFaceName, font.c_str());
    logFont.lfCharSet = GB2312_CHARSET;
    logFont.lfHeight = ConvertWinFontHeightToNeg(size);
    logFont.lfWidth = 0;
    HFONT newFont = ::CreateFontIndirect(&logFont);
    HFONT oldFont = (HFONT)::SelectObject(hdc, newFont);
    CSize curSize;
    BOOL ret = ::GetTextExtentPoint32W(
        hdc, text.c_str(), text.length(), &curSize);
    RECT rc = {20, 250, 600,400};
    int drawLen = DrawText(hdc, text.c_str(), text.length(), 
        &rc,  DT_LEFT | DT_NOPREFIX);
    ::SelectObject(hdc, oldFont);
}

void CDrawDiffFontForKugouDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    return;
}


BOOL CDrawDiffFontForKugouDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类

    return CDialogEx::PreTranslateMessage(pMsg);
}
