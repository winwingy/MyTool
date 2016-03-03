// CntCodeLineDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

const int READ_ONCE = 1024;
// CCntCodeLineDlg 对话框
class CCntCodeLineDlg : public CDialog
{
// 构造
public:
	CCntCodeLineDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CNTCODELINE_DIALOG };

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
	CEdit m_editFile;
	afx_msg void OnBnClickedBtnCnt();
	double m_dCntLines;
	double cntLines(const CString& cstrFileName);
	void Findfile( const CString& cstrFolderFile);

	//返回文件后缀名,分割文件名
	CString GetSuffix(const CString& cstrPath);
};
