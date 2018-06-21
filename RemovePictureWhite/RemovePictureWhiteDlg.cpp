
// RemovePictureWhiteDlg.cpp : ʵ���ļ�
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


// CRemovePictureWhiteDlg �Ի���




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


// CRemovePictureWhiteDlg ��Ϣ�������

BOOL CRemovePictureWhiteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRemovePictureWhiteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    CString text;
    m_path.GetWindowText(text);

    ULONG_PTR token = 0;
    GdiplusStartupInput gdiInput;
    GdiplusStartup(&token, &gdiInput, nullptr);
    RemoveBlankBitmap(text.GetBuffer(), L"image/png");

    GdiplusShutdown(token);

}
