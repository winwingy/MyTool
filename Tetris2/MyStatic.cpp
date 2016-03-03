// MyStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "Tetris2.h"
#include "MyStatic.h"


// CMyStatic

IMPLEMENT_DYNAMIC(CMyStatic, CStatic)
CMyStatic::CMyStatic()
:m_colBkgColor(RGB(255, 255, 255))
{
}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyStatic 消息处理程序

void CMyStatic::SetBkgColor(COLORREF col)
{
	m_colBkgColor = col;
}

void CMyStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()	
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(rect);
	dc.FillRect(rect, &CBrush(m_colBkgColor));	
}