#include "StdAfx.h"
#include "DesktopItem.h"
#include <assert.h>
#include <CommCtrl.h>
#include <memory>
#include <functional>


DesktopItem::DesktopItem(void)
{
}


DesktopItem::~DesktopItem(void)
{

}

HWND DesktopItem::GetDesktopProgmanHwnd()
{
    HWND progman = FindWindow(L"Progman", L"Program Manager");
    if (!progman)
    {
        assert(progman);
        return nullptr;
    }
    return progman;
}

HWND DesktopItem::GetDesktopTreeHwnd()
{
    HWND progman = FindWindow(L"Progman", L"Program Manager");
    if (!progman)
    {
        assert(progman);
        return nullptr;
    }

    HWND defView = FindWindowEx(progman, 0, L"SHELLDLL_DefView", nullptr);
    if (!defView)
    {
        assert(defView);
        return nullptr;
    }

    HWND view32 = FindWindowEx(defView, 0, L"SysListView32", nullptr);
    if (!view32)
    {
        assert(view32);
        return nullptr;
    }
    return view32;
}


typedef struct tagLVITEMWKG
{
    UINT mask;
    int iItem;
    int iSubItem;
    UINT state;
    UINT stateMask;
    BYTE hoder1[4];
    LPWSTR pszText;
    BYTE hoder2[4];
    int cchTextMax;
    int iImage;
    LPARAM lParam;
    BYTE hoder3[4];
#if (_WIN32_IE >= 0x0300)
    int iIndent;
#endif
#if (_WIN32_WINNT >= 0x0501)
    int iGroupId;
    UINT cColumns; // tile view columns
    BYTE hoder4[4];
    PUINT puColumns;
    BYTE hoder5[4];
#endif
#if _WIN32_WINNT >= 0x0600
    int* piColFmt;
    BYTE hoder6[4];
    int iGroup; // readonly. only valid for owner data.
    BYTE hoder7[4];
#endif
} LVITEMWKG, *LPLVITEMWKG;


bool GetDesktopIcon64(IN HANDLE processHandle, HWND listViewWnd,
    const std::wstring& targetText, OUT RECT* iconPos)
{
    WCHAR* anoMemTextBuf = nullptr;
    const int Len = MAX_PATH;
    anoMemTextBuf = reinterpret_cast<WCHAR*>(VirtualAllocEx(
        processHandle, nullptr, Len * sizeof(WCHAR),
        MEM_COMMIT, PAGE_READWRITE));
    assert(anoMemTextBuf);
    //SendMessage(processHandle, LVM_GETITEMTEXT)
    LVITEMWKG item = {0};
    item.mask = LVIF_TEXT;
    item.pszText = anoMemTextBuf;
    item.cchTextMax = Len;
    LVITEMWKG* anoMemItem = reinterpret_cast<LVITEMWKG*>(
        VirtualAllocEx(processHandle, nullptr, sizeof(item), 
        MEM_COMMIT, PAGE_READWRITE));
    assert(anoMemItem);

    DWORD writtted = 0;
    BOOL ret = WriteProcessMemory(processHandle, anoMemItem,
        &item, sizeof(LVITEMWKG), &writtted);
    assert(ret);

    int count = (int)SendMessage(listViewWnd, LVM_GETITEMCOUNT, 0, 0);
    std::unique_ptr<WCHAR[]> localBut(new WCHAR[Len]);
    BOOL rectRet = FALSE;

    RECT* anoMemRcTemp = reinterpret_cast<RECT*>(
        VirtualAllocEx(processHandle, nullptr, sizeof(RECT), 
        MEM_COMMIT, PAGE_READWRITE));
    auto anoMemRcDelFun =  [processHandle](void* p)
    {VirtualFreeEx(processHandle, p, 0, MEM_RELEASE);};
    std::unique_ptr<RECT, std::function<void(void* p)>> 
        anoMemRc(anoMemRcTemp, anoMemRcDelFun);
    assert(anoMemRc);

    for (int i = 0; i < count; ++i)
    {
        int getLen = (int)SendMessage(listViewWnd, LVM_GETITEMTEXT,
            i, reinterpret_cast<LPARAM>(anoMemItem));
        if (getLen > 0)
        {
            DWORD readed = 0;
            ReadProcessMemory(processHandle, anoMemTextBuf,
                localBut.get(), getLen*sizeof(WCHAR), &readed);
            if (readed > 0)
            {
                std::wstring readText(localBut.get(),
                                      localBut.get() + readed/2);
                if (readText == targetText)
                {
                    rectRet = (BOOL)SendMessage(
                        listViewWnd, LVM_GETITEMRECT, i, (LPARAM)anoMemRc.get());
                    if (rectRet)
                    {
                        SIZE_T rcMemRead = 0;
                        ReadProcessMemory(processHandle, anoMemRc.get(),
                            iconPos, sizeof(RECT), &rcMemRead);
                    }
                    break;
                }
            }
        }
    }

    VirtualFreeEx(processHandle, anoMemTextBuf, 0, MEM_RELEASE);
    VirtualFreeEx(processHandle, anoMemItem, 0, MEM_RELEASE);
    return !!rectRet;
}



bool GetDesktopIcon32(IN HANDLE processHandle, HWND listViewWnd,
    const std::wstring& targetText, OUT RECT* iconPos)
{
    WCHAR* ProcesstextBuf = nullptr;
    const int Len = MAX_PATH;
    ProcesstextBuf = reinterpret_cast<WCHAR*>(VirtualAllocEx(
        processHandle, nullptr, Len * sizeof(WCHAR),
        MEM_COMMIT, PAGE_READWRITE));
    assert(ProcesstextBuf);
    //SendMessage(processHandle, LVM_GETITEMTEXT)
    LVITEM item = {0};
    item.mask = LVIF_TEXT;
    item.pszText = ProcesstextBuf;
    item.cchTextMax = Len;
    LVITEM* processItem = reinterpret_cast<LVITEM*>(
        VirtualAllocEx(processHandle, nullptr, sizeof(item), 
        MEM_COMMIT, PAGE_READWRITE));
    assert(processItem);

    DWORD writtted = 0;
    BOOL ret = WriteProcessMemory(processHandle, processItem,
        &item, sizeof(LVITEM), &writtted);
    assert(ret);

    int count = (int)SendMessage(listViewWnd, LVM_GETITEMCOUNT, 0, 0);
    std::unique_ptr<WCHAR[]> localBut(new WCHAR[Len]);
    BOOL rectRet = FALSE;
    for (int i = 0; i < count; ++i)
    {
        int getLen = (int)SendMessage(listViewWnd, LVM_GETITEMTEXT,
            i, reinterpret_cast<LPARAM>(processItem));
        if (getLen > 0)
        {
            DWORD readed = 0;
            ReadProcessMemory(processHandle, ProcesstextBuf,
                localBut.get(), Len*sizeof(WCHAR), &readed);
            if (readed > 0)
            {
                std::wstring readText(localBut.get(), localBut.get() + readed); //£¿£¿

                if (readText == targetText)
                {
                    rectRet = (BOOL)SendMessage(
                        listViewWnd, LVM_GETITEMRECT, i, (LPARAM)iconPos);
                    break;
                }
            }
        }
    }

    VirtualFreeEx(processHandle, ProcesstextBuf, 0, MEM_RELEASE);
    VirtualFreeEx(processHandle, processItem, 0, MEM_RELEASE);
    return !!rectRet;
}

BOOL IsWow64ProcessEx( __in HANDLE hProcess, __out PBOOL Wow64Process )
{
    typedef BOOL (WINAPI*IsWow64ProcessPFN)(HANDLE, PBOOL );

    IsWow64ProcessPFN IsWow64ProcessPfn = 
        (IsWow64ProcessPFN)GetProcAddress(GetModuleHandle(L"kernel32"),
        "IsWow64Process");
    if (IsWow64ProcessPfn)
    {
        IsWow64ProcessPfn(hProcess, Wow64Process);
        return TRUE;
    }
    return FALSE;
}

bool DesktopItem::GetDesktopIcon(
    IN const std::wstring& iconName, OUT RECT* iconPos )
{
    HWND view32 = GetDesktopTreeHwnd();
    if (!view32)
    {
        return false;
    }

    DWORD processId = 0;
    GetWindowThreadProcessId(view32, &processId);
    if (!processId)
    {
        assert(processId);
        return false;
    }

    HANDLE processHandle = OpenProcess(
        PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE,
        FALSE, processId);
    if (!processHandle)
    {
        assert(processHandle);
        return false;
    }

    BOOL Wow64Process = FALSE;
    HANDLE curProcess = GetCurrentProcess();
    bool ret = false;
    ret = !!IsWow64ProcessEx(GetCurrentProcess(), &Wow64Process);
    if (!ret)
    {
        assert(ret);
        return false;
    }
   
    if (Wow64Process)
    {
        ret = GetDesktopIcon64(processHandle, view32, iconName, iconPos);
    }
    else
    {
        ret = GetDesktopIcon32(processHandle, view32, iconName, iconPos);
    }
    CloseHandle(processHandle);
    return ret;
}
