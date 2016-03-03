// FindFileDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

// CFindFileDlg 对话框
class CFindFileDlg : public CDialog
{
// 构造
public:
	CFindFileDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FINDFILE_DIALOG };

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
	afx_msg void OnBnClickedButtonFindway1();
	CEdit m_editName;
	CString m_cstrShowPath;	
	void FindPerDriver(const CHAR* pszDriver, int iType);
	int m_iShowPathLeft;
	int m_iShowPathTop;
	int m_iEnterFocus;
	
	CString m_cstrFindName;
	CEdit m_editShowPath;
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual void OnOK();
public:
	afx_msg void OnEnChangeEditName();
	afx_msg void OnEnChangeEditSize();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_btnFindWay1;
	CButton m_btnFindWay2;
	afx_msg void OnBnClickedButtonFindway2();
	CEdit m_editSize;
	DWORD m_dwLowSize;
	DWORD m_dwHighSize;
	int m_iFindByWhat;			//通过什么方式查找
	int m_iLineNum;
	bool m_bIsFinding;			//是否正在查找,同一时间只能进行一个查找
	
};
