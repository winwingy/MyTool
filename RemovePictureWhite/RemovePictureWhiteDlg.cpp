
// RemovePictureWhiteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemovePictureWhite.h"
#include "RemovePictureWhiteDlg.h"
#include "afxdialogex.h"
#include <GdiPlus.h>
#include <string>

using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRemovePictureWhiteDlg 对话框




CRemovePictureWhiteDlg::CRemovePictureWhiteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRemovePictureWhiteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CRemovePictureWhiteDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_PATH, m_path);
}

BEGIN_MESSAGE_MAP(CRemovePictureWhiteDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CRemovePictureWhiteDlg::OnBnClickedButtonRemove)
END_MESSAGE_MAP()


// CRemovePictureWhiteDlg 消息处理程序

BOOL CRemovePictureWhiteDlg::OnInitDialog()
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

void CRemovePictureWhiteDlg::OnPaint()
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
HCURSOR CRemovePictureWhiteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT num, size;
    Gdiplus::GetImageEncodersSize(&num, &size);
    Gdiplus::ImageCodecInfo* pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
    Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);
    Gdiplus::ImageCodecInfo* temp = pImageCodecInfo;
    bool found = false;
    for (UINT ix = 0; !found && ix < num; ++ix)
    {
        if (_wcsicmp(pImageCodecInfo[ix].MimeType, format) == 0) 
        {
            *pClsid = pImageCodecInfo[ix].Clsid;
            found = true;
        }
        ++temp;
    }
    free(pImageCodecInfo);
    return found;
}

//  imageType = L"image/jpeg"
bool RemoveBlankBitmap(const std::wstring picturePath, 
    const std::wstring imageType)
{
    Status sta = Ok;

    Bitmap bitmap(picturePath.c_str());
    int width = bitmap.GetWidth();
    int height = bitmap.GetHeight();
    Rect rect(0, 0, width, height);
    BitmapData* data = new BitmapData;
    sta = bitmap.LockBits(&rect, ImageLockModeRead|ImageLockModeWrite, 
        PixelFormat32bppARGB, data);
    if (sta != Ok)
    {
        return false;
    }
    BYTE* lockData = reinterpret_cast<BYTE*>(data->Scan0);
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
//             DWORD* val = reinterpret_cast<DWORD*>(
//                 lockData + (w + h*width)*4);
			DWORD* val = reinterpret_cast<DWORD*>(
				lockData + w * 4 + h * width * 4);
            if (*val == 0xffffffff)
            {
                *val = 0;
            }
        }
    }
    bitmap.UnlockBits(data);
    delete data;

    CLSID clsid;
    GetEncoderClsid(imageType.c_str(), &clsid);
    std::wstring tempPath =picturePath;
    size_t pos = tempPath.rfind(L".");
    if (pos == std::wstring::npos)
    {
        return false;
    }
    tempPath.insert(pos, L"_alpha");
    sta = bitmap.Save(tempPath.c_str(), &clsid);
    return true;
}



void CRemovePictureWhiteDlg::OnBnClickedButtonRemove()
{
    // TODO: 在此添加控件通知处理程序代码
    CString text;
    m_path.GetWindowText(text);

    ULONG_PTR token = 0;
    GdiplusStartupInput gdiInput;
    GdiplusStartup(&token, &gdiInput, nullptr);
    RemoveBlankBitmap(text.GetBuffer(), L"image/png");

    GdiplusShutdown(token);

}
