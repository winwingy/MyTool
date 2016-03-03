// Test3Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <vector>
#include <string>
using namespace std;


// CTest3Dlg 对话框
class CTest3Dlg : public CDialog
{
// 构造
public:
	CTest3Dlg(CWnd* pParent = NULL);	// 标准构造函数
	~CTest3Dlg();

// 对话框数据
	enum { IDD = IDD_TEST3_DIALOG };

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
	CStatic* m_pSttShow;
	vector< CStatic* > m_vecPSttShow;
	int m_iSttID;
public:
	CStatic m_stt1;
	
};
