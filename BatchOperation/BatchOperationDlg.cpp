
// BatchOperationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatchOperation.h"
#include "BatchOperationDlg.h"
#include "afxdialogex.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBatchOperationDlg 对话框




CBatchOperationDlg::CBatchOperationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBatchOperationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBatchOperationDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_PATH, m_editPath);
    DDX_Control(pDX, IDC_EDIT_CONDITION, m_editCondition);
    DDX_Control(pDX, IDC_EDIT_ADD_BEG, m_editAddBeg);
    DDX_Control(pDX, IDC_EDIT_ADD_END, m_editAddEnd);
}

BEGIN_MESSAGE_MAP(CBatchOperationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CBatchOperationDlg::OnBnClickedOk)
    ON_WM_DROPFILES()
    ON_BN_CLICKED(IDC_BUTTON_CHANG_FILE_STRING, &CBatchOperationDlg::OnBnClickedButtonChangFileString)
END_MESSAGE_MAP()


// CBatchOperationDlg 消息处理程序

BOOL CBatchOperationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    DragAcceptFiles(TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBatchOperationDlg::OnPaint()
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
HCURSOR CBatchOperationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void FindAndRename(wstring pszPath, wstring codition, wstring addBegin,
    map<wstring,wstring>* namePair)
{    
    wstring dir = pszPath;
    WIN32_FIND_DATA findData = {0};
    pszPath += _T("\\*.*");    
    HANDLE hFind = FindFirstFile(pszPath.c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        return;
    }
    do 
    {
        wstring fileName(findData.cFileName);
        wstring::size_type pos = fileName.find(codition);
        if (pos != wstring::npos)
        {
            wstring newName(fileName);
            newName.insert(0, addBegin);
            namePair->insert(
                make_pair(dir + L"\\" + fileName, dir + L"\\" + newName));
        }
    } while (FindNextFile(hFind, &findData));
    FindClose(hFind);
}

void RenameMap(const map<wstring,wstring>& namePair)
{
    int ret = -1;
    for (auto per = namePair.begin(); per != namePair.end(); ++per)
    {
        ret = _trename(per->first.c_str(), per->second.c_str());
    }

}


void CBatchOperationDlg::OnBnClickedOk()
{
    CString pathText;
    m_editPath.GetWindowText(pathText);  
    CString codition;
    m_editCondition.GetWindowText(codition);
    CString editAddBeg;
    m_editAddBeg.GetWindowText(editAddBeg);
    CString editAddEnd;
    m_editAddEnd.GetWindowText(editAddEnd);
    map<wstring,wstring> namePair;
    FindAndRename(pathText.GetBuffer(), codition.GetBuffer(),
    editAddBeg.GetBuffer(), &namePair);
    RenameMap(namePair);    
}


void CBatchOperationDlg::OnDropFiles(HDROP hDropInfo)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    UINT uFileNum=::DragQueryFile(hDropInfo,0xffffffff,NULL,0); 
    WCHAR strFileName[MAX_PATH]; 
    for (UINT i=0;i<uFileNum;i++) 
    { 
        ::DragQueryFileW(hDropInfo,i,strFileName,MAX_PATH);
        CString str(strFileName);
    } 

    POINT pt = {0};
    GetCursorPos(&pt);
    {
        CRect rectPath;
        m_editPath.GetWindowRect(rectPath);
        if (rectPath.PtInRect(pt))
        {
            m_editPath.SetWindowText(strFileName);
        }
    }

    {
        CRect rectCondition;
        m_editCondition.GetWindowRect(rectCondition);
        if (rectCondition.PtInRect(pt))
        {
            m_editCondition.SetWindowText(strFileName);
        }
    }

    {
        CRect rectAddBeg;
        m_editAddBeg.GetWindowRect(rectAddBeg);
        if (rectAddBeg.PtInRect(pt))
        {
            m_editAddBeg.SetWindowText(strFileName);
        }
    }

    {
        CRect rectAddEnd;
        m_editAddEnd.GetWindowRect(rectAddEnd);
        if (rectAddEnd.PtInRect(pt))
        {
            m_editAddEnd.SetWindowText(strFileName);
        }
    }

    ::DragFinish(hDropInfo); 
    CDialogEx::OnDropFiles(hDropInfo);
}

#include <queue>

void CBatchOperationDlg::OnBnClickedButtonChangFileString()
{
    queue<int> que;
    que
    string path = "E:\\GitCode\\Fazheng\\bin\\kugou_d\\MakeRingForm.xml";
    FILE* fp = fopen(path.c_str(), "r+");
    assert(fp);
    if (fp == nullptr)
    {
        return;
    }
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp) + 1;
    char* szBuf = new char[size + 1];
    fseek(fp, 0, SEEK_SET);
    int readed = fread(szBuf, 1, size, fp);
    szBuf[readed] = 0;
    string text(szBuf);
    delete szBuf;
    string::size_type posBeg = 0;
    string::size_type posEnd = 0;
    string findwhat(".png\"");

    while(1)
    {   
        posEnd = text.find(findwhat, posBeg);
        int writed = -1;
        if (posEnd != string::npos)
        {
            posBeg = text.rfind("\"", posEnd);
            if (posBeg != string::npos &&posBeg < posEnd)
            {
                string addText("make_ring_");
                text.insert(++posBeg, addText);
                posBeg = posEnd + findwhat.length() + addText.length() + 1;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    fseek(fp, 0, SEEK_SET);
    int wri = fwrite(text.c_str(), 1, text.length(), fp);
    fclose(fp);
}
