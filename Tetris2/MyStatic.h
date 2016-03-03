#pragma once


// CMyStatic

class CMyStatic : public CStatic
{
	DECLARE_DYNAMIC(CMyStatic)

public:
	CMyStatic();
	virtual ~CMyStatic();
	void SetBkgColor(COLORREF col);
	COLORREF m_colBkgColor;
	afx_msg void OnPaint();

protected:
	DECLARE_MESSAGE_MAP()
};


