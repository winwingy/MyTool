// Shape.cpp : 实现文件
//

#include "stdafx.h"
#include "Shape.h"
#include ".\shape.h"


// CShape

IMPLEMENT_DYNAMIC(CShape, CWnd)
CShape::CShape()
{
	m_shape = SHAPE_I;
	m_dmdOne.Create( _T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE, CRect(100, 100, 120, 120), this, 1234);

	CHAR* lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL );

	m_dmdTwo.Create( _T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE, CRect(100, 100, 120, 120), this, 1235);
	m_dmdThree.Create( _T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE, CRect(100, 100, 120, 120), this, 1236);
	m_dmdFour.Create( _T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE, CRect(100, 100, 120, 120), this, 1237);
}
CShape::CShape(int x, int y)
{
	m_sizePos.cx = x;
	m_sizePos.cy = y;
}
CShape::~CShape()
{
}
bool CShape::SetPos(int x, int y)
{
	m_sizePos.cx = x;
	m_sizePos.cy = y;
	return true;
}

BEGIN_MESSAGE_MAP(CShape, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CShape 消息处理程序


void CShape::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CRect rect;
	m_dmdOne.MoveWindowBySize(  );	
	m_dmdOne.GetWindowRect( &rect );
	rect.OffsetRect(0, m_dmdOne.GetWidth());
	m_dmdTwo.MoveWindow(rect);
	rect.OffsetRect(0, m_dmdOne.GetWidth());
	m_dmdThree.MoveWindow(rect);
	rect.OffsetRect(0, m_dmdOne.GetWidth());
	m_dmdFour.MoveWindow(rect);
}
