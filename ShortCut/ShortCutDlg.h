// ShortCutDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

const int LINE_NUM = 100;
const int BOOK_FULL_COUNT = 1024;
#define  TRACEONE 
// CShortCutDlg 对话框
class CShortCutDlg : public CDialog
{
// 构造
public:
	CShortCutDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SHORTCUT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CHAR m_pszPath[MAX_PATH];
	afx_msg void OnBnClickedButtonChange();
	CEdit m_editShow;
	CString RemoveSuffix(CString cstrRhs);
	CString GetSuffix(CString cstrRhs);
	afx_msg void OnEnChangeEditShow();
	afx_msg void OnBnClickedBtnDivide();
};
