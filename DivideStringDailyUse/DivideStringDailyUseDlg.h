// DivideStringDailyUseDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// CDivideStringDailyUseDlg 对话框
class CDivideStringDailyUseDlg : public CDialog
{
// 构造
public:
	CDivideStringDailyUseDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DIVIDESTRINGDAILYUSE_DIALOG };

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
	CEdit m_editSource;
	CEdit m_editDivideSymbol;
	CEdit m_editResult;
	CButton m_chkToNewTXT;

	CString m_cstrSourceName;
	CString m_cstrDivideSymbol;

	bool m_bIsFile;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedBtnStart();
	void DivideStringBySymbol(const string& strIn, const vector<string>& vecSymbol, vector<string>& vecHasDivide);
};
