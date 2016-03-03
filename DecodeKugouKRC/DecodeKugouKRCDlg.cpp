
// DecodeKugouKRCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DecodeKugouKRC.h"
#include "DecodeKugouKRCDlg.h"
#include "afxdialogex.h"
#include <assert.h>
#include "Base64.h"
#include "StrAssist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDecodeKugouKRCDlg 对话框




CDecodeKugouKRCDlg::CDecodeKugouKRCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDecodeKugouKRCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDecodeKugouKRCDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDecodeKugouKRCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_DROPFILES()
    ON_BN_CLICKED(IDC_BTN_DECODE, &CDecodeKugouKRCDlg::OnBnClickedBtnDecode) 
END_MESSAGE_MAP()


// CDecodeKugouKRCDlg 消息处理程序

BOOL CDecodeKugouKRCDlg::OnInitDialog()
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

void CDecodeKugouKRCDlg::OnPaint()
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
HCURSOR CDecodeKugouKRCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDecodeKugouKRCDlg::OnDropFiles(HDROP hDropInfo)
{
    int count = DragQueryFile(hDropInfo, -1, NULL, 0);
    for (int i = 0; i < count; ++i)
    {
        TCHAR filePath[MAX_PATH];
        if(DragQueryFile(hDropInfo, i, filePath, MAX_PATH) != 0)
        {
            CWnd* editPath = GetDlgItem(IDC_EDIT_PATH);
            editPath->SetWindowText(filePath);
        }
        else
        {
            assert(0 && L"DragQueryFile" == NULL);
        }
    }
    CDialog::OnDropFiles(hDropInfo);
}

struct AutoCloseHandle
{
    AutoCloseHandle(FILE* fp)
        : fp_(fp)
    {
    }
    ~AutoCloseHandle()
    {
        if (fp_)
        {
            fclose(fp_);
        }
    }
    void ReSet()
    {
        fclose(fp_);
        fp_ = nullptr;
    }
   FILE* fp_;
};

bool CDecodeKugouKRCDlg::DealBase64(std::wstring& target)
{
    FILE* fp = nullptr;    
    _wfopen_s(&fp, target.c_str(), L"r+");
    if (fp == nullptr)
    {
        CString path(target.c_str());
        path += L" 文件打不开";
        MessageBox(path, L"错误！", MB_OK);
        return false;
    }
    AutoCloseHandle closeHandle(fp);

    char szBuf[1024*10];
    std::string lyric;

    while (1)
    {
        int readed = fread(szBuf, 1, 1024*10-1, fp);
        if (readed == 0)
        {
            break;
        }
        szBuf[readed] = 0;
        lyric += szBuf;
    }

    if (lyric.find("[split:")  != std::string::npos)
    {
        return false;
    }

    std::string::size_type posBegin = lyric.find("[language:");
    if (posBegin == std::string::npos)
    {
        return false;
    }
    posBegin += strlen("[language:");
    std::string::size_type posEnd = lyric.find("]", posBegin);
    if (posEnd == std::string::npos)
    {
        return false;
    }

    std::string language(lyric, posBegin, posEnd - posBegin);
    if (language.empty())
    {
        return false;
    }
    char* pStrBase64 = nullptr;
    CBase64::Base64EnCodeAlloc(language.c_str(), &pStrBase64);
    pStrBase64 = CBase64::Base64DeCode(language.c_str(), pStrBase64);

    std::string languageReal = CStrAssist::UnicodeIntStrToAnsi(pStrBase64, true);

    lyric.replace(posBegin, posEnd - posBegin, languageReal.c_str());
    CBase64::Base64EnCodeFree(pStrBase64);
    pStrBase64 = nullptr;
    closeHandle.ReSet();
    fp = nullptr;
    _wfopen_s(&fp, target.c_str(), L"w");
    if (fp == nullptr)
    {
        CString path(target.c_str());
        path += L" 文件打不开";
        MessageBox(path, L"错误！", MB_OK);
        return false;
    }
    AutoCloseHandle closeHandleW(fp);

    int write = fwrite(lyric.c_str(), 1, lyric.size(), fp);
    
    if (write > 0)
    {
        return true;
    }
    return false;
}


void CDecodeKugouKRCDlg::OnBnClickedBtnDecode()
{
    TCHAR decoder[MAX_PATH] = L"E:\\0工作资料\\工具\\lyric_decoder\\lyric_decoder.exe";//L"C:\\Program Files (x86)\\IDM Computer Solutions\\UltraEdit\\Uedit32.exe";
    FILE* fp = NULL;
    _tfopen_s(&fp, decoder, L"r");
    if (fp == NULL)
    {
        CString path(decoder);
        MessageBox(path + L"路径不存在");
        return;
    }
    fclose(fp);

    CWnd* editPath = GetDlgItem(IDC_EDIT_PATH);
    CString editPathText;
    editPath->GetWindowText(editPathText);
    if (editPathText.IsEmpty())
    {        
        MessageBox(L"歌词文件路径不存在");
        return;
    }
    std::wstring target = editPathText.GetBuffer();
    std::wstring::size_type pos = target.rfind(L'.');
    if (pos == std::wstring::npos)
    {
        pos = target.size();
    }
    target.replace(pos, target.size()-pos, L".txt");

    DeleteFile(target.c_str());

    CString cmdline = L"\"" + editPathText + L"\""+ CString(L" ") + L"\"" + CString(target.c_str()) + L"\"";
    
    SHELLEXECUTEINFOW execInfo = {0};
    execInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    execInfo.lpVerb = L"open";
    execInfo.cbSize = sizeof(execInfo);
    execInfo.lpFile = decoder;
    execInfo.lpParameters = cmdline.GetBuffer();
    execInfo.nShow = SW_SHOW;
    BOOL ret = ShellExecuteExW(&execInfo);

    if (ret == FALSE || execInfo.hProcess == NULL)
    {
        MessageBox(L"程序运行失败！！！", L"错误！", MB_OK);
    }
    else
    {
        WaitForSingleObject(execInfo.hProcess, INFINITE);

        if (DealBase64(target))
        {
            GetDlgItem(IDC_BTN_DECODE)->SetWindowTextW(L"成功, 解密文件在同一路径下");
        }
        else
        {
            GetDlgItem(IDC_BTN_DECODE)->SetWindowTextW(L"失败");
            DeleteFile(target.c_str());
        }

        DWORD code = 0;;
        GetExitCodeProcess(execInfo.hProcess, &code);
        CString tips = L"退出码是: ";
        tips.Format(L"%s %d", tips, code);
    }
}


