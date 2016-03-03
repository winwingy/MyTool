#pragma once

#include "Diamonds.h"
// CShape

class CShape : public CWnd
{
	DECLARE_DYNAMIC(CShape)

public:
	CShape();
	CShape(int x, int y);
	virtual ~CShape();

	bool SetPos(int x, int y);

protected:
	DECLARE_MESSAGE_MAP()
protected:
	EN_SHAPE m_shape;
	CDiamonds m_dmdOne;
	CDiamonds m_dmdTwo;
	CDiamonds m_dmdThree;
	CDiamonds m_dmdFour;
	SIZE m_sizePos;
public:
	afx_msg void OnPaint();
};


