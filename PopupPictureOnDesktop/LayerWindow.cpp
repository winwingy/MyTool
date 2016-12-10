#include "StdAfx.h"
#include "LayerWindow.h"
#include <assert.h>
#include <GdiPlus.h>
#include <WindowsX.h>
#include "DesktopItem.h"
using namespace Gdiplus;
#pragma comment(lib, "Msimg32.lib")

namespace
{
enum TIMER_ID
{
    TIMER_SHOW

};
}

LayerWindow::LayerWindow(void)
    : hWnd_(nullptr)

{
}


LayerWindow::~LayerWindow(void)
{
}

HWND LayerWindow::Create( HWND hwnd, int x, int y, int cx, int cy)
{
    WNDCLASSEX wcs = {0};
    wcs.cbSize = sizeof(wcs);
    wcs.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW +1);
    wcs.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcs.hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr));
    wcs.lpfnWndProc = LayerWindow::WndProcStatic;
    wcs.lpszClassName = L"LayerWindow";
    wcs.style = CS_VREDRAW|CS_HREDRAW;
    RegisterClassEx(&wcs);

    HWND hwndCreate = CreateWindowEx(0, wcs.lpszClassName,
        L"LayerWindowWnd", WS_OVERLAPPED, x, y, cx, cy,
        hwnd, nullptr, wcs.hInstance, this);
    assert(hwndCreate);
    hWnd_ = hwndCreate;
    return hwndCreate;
}

void RemoveBorderEx(HWND hWnd)
{
    static bool init = false;
    if (false == init)
    {
        LONG oldStyle = GetWindowLong(hWnd, GWL_STYLE);
        DWORD removeStyle = ~(WS_OVERLAPPED|WS_SYSMENU|WS_MAXIMIZEBOX|
            WS_BORDER|WS_MAXIMIZEBOX|WS_CAPTION|WS_SIZEBOX);
        SetWindowLong(hWnd, GWL_STYLE, oldStyle & removeStyle);
        LONG oldExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
        DWORD removeStyleEx = ~(WS_EX_LEFT|WS_EX_LTRREADING|
            WS_EX_RIGHTSCROLLBAR);
        SetWindowLong(hWnd, GWL_EXSTYLE, oldExStyle & removeStyleEx);
        SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0,
            SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER|
            SWP_FRAMECHANGED);
        SetMenu(hWnd, NULL);
        init = true;
    }
}


HBITMAP  CreateDIBCompatibleBitmap(HDC hdc, int nWidth, int nHeight )
{   
    BYTE* pBits;
    BITMAPINFOHEADER          bmih;    
    ZeroMemory( &bmih, sizeof( BITMAPINFOHEADER ) );   

    bmih.biSize                 = sizeof( BITMAPINFOHEADER );    
    bmih.biWidth                = nWidth;
    bmih.biHeight               = nHeight;
    bmih.biPlanes               = 1 ;    
    bmih.biBitCount             = 32;//这里一定要是32    
    bmih.biCompression          = BI_RGB ;    
    bmih.biSizeImage            = 0 ;    
    bmih.biXPelsPerMeter        = 0 ;    
    bmih.biYPelsPerMeter        = 0 ;    
    bmih.biClrUsed              = 0 ;    
    bmih.biClrImportant         = 0 ;   
    HBITMAP hBitMap = CreateDIBSection( hdc, ( BITMAPINFO * )&bmih,  DIB_RGB_COLORS, ( VOID** )&pBits, NULL, 0 );   
    return hBitMap;   
}

enum Draw_Anchors
{
    Draw_Left_VCenter,
    Draw_Center_VCenter,
    Draw_Right_Top,

};

bool GetDrawPos(const WRect& clientRect, const WRect& pngRect,
                Draw_Anchors anchor, __out WRect* drawPos)
{
    if (Draw_Left_VCenter == anchor)
    {
        drawPos->left = clientRect.left;
        drawPos->top = clientRect.top +
            (clientRect.Height() - pngRect.Height())/2;
        drawPos->right = drawPos->left + pngRect.Width();
        drawPos->bottom = drawPos->top + pngRect.Height();
    }
    else if (Draw_Center_VCenter == anchor)
    {
        drawPos->left = clientRect.left + 
            (clientRect.Width() - pngRect.Width())/2;
        drawPos->top = clientRect.top +
            (clientRect.Height() - pngRect.Height())/2;
        drawPos->right = drawPos->left + pngRect.Width();
        drawPos->bottom = drawPos->top + pngRect.Height();
    }
    else if (Draw_Right_Top == anchor)
    {
        drawPos->left = clientRect.right - pngRect.Width();
        drawPos->top = clientRect.top;
        drawPos->right = drawPos->left + pngRect.Width();
        drawPos->bottom = drawPos->top + pngRect.Height();
    }
    return true;
}

void DrawPng(HWND hWnd, HDC comDC, const std::wstring& png,
    Draw_Anchors anchor, __out WRect* drawPosRet)
{
    HDC backDC = CreateCompatibleDC(comDC);

    WRect rect;
    GetClientRect(hWnd, rect);
    
    HBITMAP bitmapMem =CreateDIBCompatibleBitmap(
        backDC, rect.Width(), rect.Height());
    SelectObject(backDC, bitmapMem);
    
    Graphics grap(backDC);
    Image imagePng(png.c_str());
    WRect drawPos;
    WRect pngRect(0, 0, imagePng.GetWidth(), imagePng.GetHeight());
    GetDrawPos(rect, pngRect, anchor, &drawPos);
    *drawPosRet = drawPos;
    grap.DrawImage(&imagePng, drawPos.left, drawPos.top, imagePng.GetWidth(),
        imagePng.GetHeight());

    BLENDFUNCTION bfc = {0};
    bfc.AlphaFormat = AC_SRC_ALPHA;
    bfc.SourceConstantAlpha = 255;
    BOOL ret = ::AlphaBlend(comDC, drawPos.left, drawPos.top,imagePng.GetWidth(),
        imagePng.GetHeight(), 
        backDC, drawPos.left, drawPos.top, imagePng.GetWidth(),
        imagePng.GetHeight(), bfc);

    DeleteBitmap(bitmapMem);
    DeleteDC(backDC);
}

void LayerWindow::UpdateLayer(HWND hWnd, const std::wstring& leftPng, 
    const std::wstring& mainPng, const std::wstring& closeButton)
{
    HDC hdc = GetDC(hWnd);
    HDC comDC = CreateCompatibleDC(hdc);
    WRect srcRect;
    GetWindowRect(hWnd, &srcRect);

    HBITMAP bitmapMem =CreateDIBCompatibleBitmap(
        hdc, srcRect.Width(), srcRect.Height());
    SelectObject(comDC, bitmapMem);

    DrawPng(hWnd, comDC, leftPng, Draw_Left_VCenter, &leftPos_);
    DrawPng(hWnd,comDC, mainPng, Draw_Center_VCenter, &mainPos_);
    DrawPng(hWnd,comDC, closeButton,Draw_Right_Top, &closePos_);

    POINT dstPt = {srcRect.left, srcRect.top};
    SIZE dstSize = {srcRect.Width(), srcRect.Height()};
    POINT srcPt = {0, 0};
    BLENDFUNCTION bfc = {0};
    bfc.AlphaFormat = AC_SRC_ALPHA;
    bfc.SourceConstantAlpha = 255;
    BOOL ret = ::UpdateLayeredWindow(hWnd, hdc, &dstPt, &dstSize, comDC,
        &srcPt, 0, &bfc, ULW_ALPHA);
    DWORD err = GetLastError();

    DeleteBitmap(bitmapMem);
    DeleteDC(comDC);
    ReleaseDC(hWnd, hdc);
    GetWindowRect(hWnd, pos_);
}



void LayerWindow::Show( const std::wstring& leftPng, 
    const std::wstring& mainPng, const std::wstring& closeButton )
{  
    RemoveBorderEx(hWnd_);

    LONG style = GetWindowLong(hWnd_, GWL_EXSTYLE);
    if (0 == (WS_EX_LAYERED & style))
    {
        SetWindowLong(hWnd_, GWL_EXSTYLE, style | WS_EX_LAYERED);
    }

    UpdateLayer(hWnd_, leftPng, mainPng, closeButton);

}

LRESULT CALLBACK LayerWindow::WndProcStatic(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    LayerWindow* pThis = NULL;
    switch(message)
    {
    case WM_NCCREATE:
        {
            LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
            pThis = reinterpret_cast<LayerWindow*>(lpcs->lpCreateParams);
            pThis->hWnd_ = hWnd;
            ::SetWindowLongPtr(hWnd, GWLP_USERDATA, 
                reinterpret_cast<LPARAM>(pThis));
            return TRUE;
        }
    }

    pThis =  reinterpret_cast<LayerWindow*>(
        ::GetWindowLongPtr(hWnd, GWLP_USERDATA));

    if (pThis)
    {
        return pThis->WndProc(hWnd, message, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

LRESULT LayerWindow::WndProc( HWND hWnd,
    UINT message, WPARAM wParam, LPARAM lParam )
{
    switch(message)
    {
        case WM_SYSCOMMAND:
        {
            switch(wParam)
            {
            case SC_MINIMIZE:
                {
                    return 0;
                }
            }
            break;
        }
        
    	case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc;
                hdc = BeginPaint(hWnd, &ps);
                // TODO: 在此添加任意绘图代码...
                EndPaint(hWnd, &ps);
                break;
            }
        case WM_NCHITTEST:
            {
                return HTCAPTION;
            }
        case WM_NCLBUTTONDOWN:
            {
                int xPos = GET_X_LPARAM(lParam);
                int yPos = GET_Y_LPARAM(lParam);
                POINT pt = {xPos, yPos};
                ScreenToClient(hWnd_, &pt);
                if (closePos_.PtInRect(pt))
                {
                    PostMessage(hWnd, WM_CLOSE, 0, 0);
                }
                break;
            }
        case WM_CREATE:
            {
                SetTimer(hWnd_, TIMER_SHOW, 100, NULL);
                break;
            }
        case WM_TIMER:
            {
                SetWindowPos( DesktopItem::GetDesktopProgmanHwnd(),
                    GetHWND(), 
                    0, 0, 0, 0,
                    SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
                break;
            }
//         case WM_WINDOWPOSCHANGED:
//             {
//                 SetWindowPos(hWnd_, 0,
//                     pos_.left, pos_.top, pos_.Width(), pos_.Height(),
//                     SWP_NOACTIVATE);
//                  SetWindowPos(DesktopItem::GetDesktopProgmanHwnd(), hWnd_,  
//                      pos_.left, pos_.top, pos_.Width(), pos_.Height(),
//                      SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);
//                 break;
//             }
//         case WM_MOUSEACTIVATE:
//             {
//                 return MA_NOACTIVATE;
//             }
        default:
             return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

