
// HttpRequestUseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpRequestUse.h"
#include "HttpRequestUseDlg.h"
#include "afxdialogex.h"
#include "../HttpRequest/http_request.h"

#ifdef _DEBUG
#pragma comment(lib, "../Debug/HttpRequest.lib")
#else
#pragma comment(lib, "../Release/HttpRequest.lib")
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHttpRequestUseDlg 对话框




CHttpRequestUseDlg::CHttpRequestUseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHttpRequestUseDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttpRequestUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHttpRequestUseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_SYNC_GET, &CHttpRequestUseDlg::OnBnClickedButtonSyncGet)
    ON_BN_CLICKED(IDC_BUTTON_SYNC_POST, &CHttpRequestUseDlg::OnBnClickedButtonSyncPost)
    ON_BN_CLICKED(IDC_BUTTON_ASYNC_GET, &CHttpRequestUseDlg::OnBnClickedButtonAsyncGet)
    ON_BN_CLICKED(IDC_BUTTON_ASYNC_POST, &CHttpRequestUseDlg::OnBnClickedButtonAsyncPost)
END_MESSAGE_MAP()


// CHttpRequestUseDlg 消息处理程序

BOOL CHttpRequestUseDlg::OnInitDialog()
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

void CHttpRequestUseDlg::OnPaint()
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
HCURSOR CHttpRequestUseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHttpRequestUseDlg::OnBnClickedButtonSyncGet()
{
    // TODO: 在此添加控件通知处理程序代码
    http_request::HttpRequest* httpRequest = 
        http_request::HttpRequest::GetInstance();
    http_request::SyncHttpRequestParam syncparam;
    syncparam.URL = "http://www.baidu.com";
    syncparam.method = "GET";
    
    http_request::HttpRequestRet httpRequestRet;
    httpRequest->SyncHttpRequest(syncparam, httpRequestRet);

}


void CHttpRequestUseDlg::OnBnClickedButtonSyncPost()
{
    
}

void AsyncGetWebCallback(const http_request::AsyncHttpRequestRet& requestRet, 
    const std::string& url)
{


}


void CHttpRequestUseDlg::OnBnClickedButtonAsyncGet()
{
    http_request::HttpRequest* httpRequest = 
        http_request::HttpRequest::GetInstance();
    http_request::AsncHttpRequestParam requestParam;
    requestParam.URL = "http://www.baidu.com";
    requestParam.method = "GET";
    requestParam.callbackFun = std::bind(AsyncGetWebCallback, 
        std::placeholders::_1, requestParam.URL);
    
    httpRequest->AsncHttpRequest(requestParam);

}

void AsyncPOSTCallback(const http_request::AsyncHttpRequestRet& requestRet, 
    const std::string& url)
{

}


void CHttpRequestUseDlg::OnBnClickedButtonAsyncPost()
{
    http_request::HttpRequest* httpRequest = 
        http_request::HttpRequest::GetInstance();
    http_request::AsncHttpRequestParam requestParam;
    requestParam.URL = "http://client.show.qq.com/cgi-bin/qqshow_user_props_info";
    requestParam.header = 
"Accept: */*\r\n\
Accept-Language: zh-CN\r\n\
x-flash-version: 11,5,502,110\r\n\
Content-Type: application/x-www-form-urlencoded\r\n\
Accept-Encoding: gzip, deflate\r\n\
User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR\3.0.30729; .NET4.0C; .NET4.0E)\r\n\
Connection: Keep-Alive\r\n\
Pragma: no-cache\r\n\
Cookie: ac=1,030,017; pt2gguin=o0237858502; RK=/UkXmgsESe; ptcz=790f8134cad4ef6aae106c15123b058e54c80069c7ca5976d490dddc8b998f63; pgv_pvid=5879667293; pgv_pvi=7525848064; uin_cookie=237858502; euin_cookie=C00ABA6DFC77188C27C69CAFAE5239B901738FB9D3319F3C\r\n";
    requestParam.method = "POST";
    requestParam.body = "uin=237858502&ckey=D03CDE9D8077B3B2188FECB09CB426C781C8E3481571AC18BB493B87371A6319&senduin=13340509";
    requestParam.callbackFun = std::bind(AsyncPOSTCallback, 
        std::placeholders::_1, requestParam.URL);

    httpRequest->AsncHttpRequest(requestParam);
}
