// MyButton.cpp : 实现文件
//

#include "stdafx.h"
#include "Test2.h"
#include "MyButton.h"
#include ".\mybutton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)
CMyButton::CMyButton()
{
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()



// CMyButton 消息处理程序


void CMyButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MoveWindow(100, 100, 100, 200);

	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyButton::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MoveWindow(0, 0, 100, 200);
	CButton::OnKeyUp(nChar, nRepCnt, nFlags);
}
