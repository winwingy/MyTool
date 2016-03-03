#pragma once
#include "Define.h"

// CDiamonds

class CDiamonds : public CWnd
{
	DECLARE_DYNAMIC(CDiamonds)

public:
	CDiamonds();
	virtual ~CDiamonds();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int GetWidth();
	void MoveWindowBySize();
protected:
	COLORREF m_colDiamonds;
	COLORREF m_colBorder;	
	SIZE	m_sizePos;
	SIZE	m_sizeWidth;

public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


