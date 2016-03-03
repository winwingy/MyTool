
// HttpRequestUseDlg.h : 头文件
//

#pragma once


// CHttpRequestUseDlg 对话框
class CHttpRequestUseDlg : public CDialogEx
{
// 构造
public:
	CHttpRequestUseDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HTTPREQUESTUSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonSyncGet();
    afx_msg void OnBnClickedButtonSyncPost();
    afx_msg void OnBnClickedButtonAsyncGet();
    afx_msg void OnBnClickedButtonAsyncPost();
};
