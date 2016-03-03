
// BatchOperationDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CBatchOperationDlg 对话框
class CBatchOperationDlg : public CDialogEx
{
// 构造
public:
	CBatchOperationDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BATCHOPERATION_DIALOG };

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
    afx_msg void OnBnClickedOk();
    CEdit m_editPath;
    CEdit m_editCondition;
    CEdit m_editAddBeg;
    CEdit m_editAddEnd;
    afx_msg void OnDropFiles(HDROP hDropInfo);
    afx_msg void OnBnClickedButtonChangFileString();
};
