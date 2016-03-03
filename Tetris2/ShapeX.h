#pragma once

#include "Define.h"
// CShapeX

class CShapeX : public CStatic
{
	DECLARE_DYNAMIC(CShapeX)

public:
	CShapeX();
	virtual ~CShapeX();

protected:
	DECLARE_MESSAGE_MAP()
	EN_SHAPE m_shape;


	virtual void PreSubclassWindow();
public:
	afx_msg void OnPaint();

	CStatic m_stt1;
	CStatic m_stt2;
	CStatic m_stt3;
	CStatic m_stt4;

	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


