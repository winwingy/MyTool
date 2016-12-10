#pragma once
#include <string>
#define IN
#define OUT
#define INOUT
class DesktopItem
{
public:
    static HWND GetDesktopTreeHwnd();
    static HWND DesktopItem::GetDesktopProgmanHwnd();
    static bool GetDesktopIcon(IN const std::wstring& iconName,
        OUT RECT* iconPos);
    DesktopItem(void);
    ~DesktopItem(void);
};

