// ShapeI.cpp : 实现文件
//

#include "stdafx.h"
#include "ShapeI.h"
#include ".\shapei.h"


// CShapeI

IMPLEMENT_DYNAMIC(CShapeI, CWnd)
CShapeI::CShapeI()

{
	m_shape = SHAPE_I;
	m_dmdOne.Create( _T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE, CRect(100, 100, 120, 120), this, 1234);
	m_dmdTwo.Create( _T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE, CRect(100, 100, 120, 120), this, 1235);
	m_dmdThree.Create( _T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE, CRect(100, 100, 120, 120), this, 1236);
	m_dmdFour.Create( _T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE, CRect(100, 100, 120, 120), this, 1237);
}

CShapeI::~CShapeI()
{
}


BEGIN_MESSAGE_MAP(CShapeI, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CShapeI 消息处理程序


void CShapeI::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDiamonds::OnPaint()
// 	CRect rect;
// 	m_dmdOne.MoveWindowBySize(  );	
// 	m_dmdOne.GetWindowRect( &rect );
// 	rect.OffsetRect(0, m_dmdOne.GetWidth());
// 	m_dmdTwo.MoveWindow(rect);
// 	rect.OffsetRect(0, m_dmdOne.GetWidth());
// 	m_dmdThree.MoveWindow(rect);
// 	rect.OffsetRect(0, m_dmdOne.GetWidth());
// 	m_dmdFour.MoveWindow(rect);
}
