
// RemovePictureWhiteDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CRemovePictureWhiteDlg 对话框
class CRemovePictureWhiteDlg : public CDialogEx
{
// 构造
public:
	CRemovePictureWhiteDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_REMOVEPICTUREWHITE_DIALOG };

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
    CEdit m_path;
    afx_msg void OnBnClickedButtonRemove();
};
