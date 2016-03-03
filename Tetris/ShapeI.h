#pragma once


#include "Shape.h"
// CShapeI

class CShapeI : public CShape
{
	DECLARE_DYNAMIC(CShapeI)

public:
	CShapeI();
	virtual ~CShapeI();

protected:
	DECLARE_MESSAGE_MAP()
protected:


public:
	afx_msg void OnPaint();
};


