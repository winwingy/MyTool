
// DrawDiffFontForKugouDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <string>


// CDrawDiffFontForKugouDlg 对话框
class CDrawDiffFontForKugouDlg : public CDialogEx
{
// 构造
public:
	CDrawDiffFontForKugouDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DRAWDIFFFONTFORKUGOU_DIALOG };

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
    afx_msg void OnBnClickedButtonRun();
    void ClearShow();
    void DrawShowText( const std::wstring& text, const std::wstring& font,
        int size, int factor);
    CEdit m_editText;
    CEdit m_editFont;
    CEdit m_editSize;
    CStatic m_staticSizeValue;
    CStatic m_staticShow;
    CStatic m_staticShowSizeValue;
    CEdit m_editFactor;
    afx_msg void OnBnClickedOk();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};
