
// RemovePictureWhiteDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CRemovePictureWhiteDlg �Ի���
class CRemovePictureWhiteDlg : public CDialogEx
{
// ����
public:
	CRemovePictureWhiteDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_REMOVEPICTUREWHITE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CEdit m_path;
    afx_msg void OnBnClickedButtonRemove();
};