#pragma once
#include <string>


class WRect : public RECT
{
public:
    WRect(int x, int y, int cx, int cy)
    {
        left = x;
        top = y;
        right = x + cx;
        bottom = y + cy;
    }

    WRect()
    {
        left = 0;
        top = 0;
        right = 0;
        bottom = 0;
    }

    int Width() const
    {
        return right - left;
    }

    int Height() const
    {

        return bottom - top;
    }

    operator LPRECT()
    {
        return this;
    }

    bool PtInRect(const POINT& pt)
    {
        return !!::PtInRect(this, pt);
    }

private:



};

class LayerWindow
{
public:
    HWND Create(HWND hwnd, int x, int y, int cx, int cy);
    HWND GetHWND(){return hWnd_;}
    void Show(const std::wstring& leftPng,
        const std::wstring& mainPng, const std::wstring& closeButton);
    LayerWindow(void);
    ~LayerWindow(void);

private:
    static LRESULT CALLBACK WndProcStatic(HWND hWnd, UINT message,
        WPARAM wParam, LPARAM lParam);
    LRESULT WndProc(HWND hWnd, UINT message,
        WPARAM wParam, LPARAM lParam);
    void UpdateLayer(HWND hWnd, const std::wstring& leftPng,
        const std::wstring& mainPng, const std::wstring& closeButton);
    HWND hWnd_;
    WRect pos_;
    WRect leftPos_;
    WRect mainPos_;
    WRect closePos_;
};

