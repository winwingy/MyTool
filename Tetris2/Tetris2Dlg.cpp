// Tetris2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tetris2.h"
#include "Tetris2Dlg.h"
#include "Define.h"
#include ".\tetris2dlg.h"
#include "ToolHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define TRACE_W TRACE


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTetris2Dlg 对话框



CTetris2Dlg::CTetris2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTetris2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CTetris2Dlg::~CTetris2Dlg()
{
	ClearStt();
}

void CTetris2Dlg::ClearStt()
{
	vector< CMyStatic*>::iterator iter = m_vecSttStop.begin();
	for ( ; iter != m_vecSttStop.end(); iter++ )
	{
		delete *iter;
		*iter = NULL;
	}
	m_vecSttStop.clear();
	if ( m_pStt1 != NULL )
	{
		delete( m_pStt1 );
		m_pStt1 = NULL;
	}
	if ( m_pStt2 != NULL )
	{
		delete( m_pStt2 );
		m_pStt2 = NULL;
	}
	if ( m_pStt3 != NULL )
	{
		delete( m_pStt3 );
		m_pStt3 = NULL;
	}
	if ( m_pStt4 != NULL )
	{
		delete( m_pStt4 );
		m_pStt4 = NULL;
	}
}

void CTetris2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTetris2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE( MENU_START, MENU_EXIT, OnMenuGame )
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTetris2Dlg 消息处理程序

BOOL CTetris2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	MoveWindow(100, 50, MAIN_WIDTH, MAIN_HEIGHT);

	MoveWindow(10, 180, MAIN_WIDTH, MAIN_HEIGHT);//test

	CMenu menuMain;
	menuMain.CreateMenu(); //创建空的顶层菜单
	CMenu menuPopup;

	//Game
	menuPopup.CreatePopupMenu();//
	menuPopup.AppendMenu(MF_STRING,MENU_START,"Start");
	menuPopup.AppendMenu(MF_STRING,MENU_PAUSE,"Pause");	
	menuPopup.AppendMenu(MF_STRING,MENU_EXIT,"Exit");	
	menuMain.AppendMenu(MF_POPUP,(UINT)menuPopup.Detach(),"Game");//

	//Level
	menuPopup.CreatePopupMenu();//
	menuPopup.AppendMenu(MF_STRING,MENU_LEVEL1,"Level1");
	menuPopup.AppendMenu(MF_STRING,MENU_LEVEL2,"Level2");
	menuPopup.AppendMenu(MF_STRING,MENU_LEVEL3,"Level3");		
	menuMain.AppendMenu(MF_POPUP,(UINT)menuPopup.Detach(),"Level");//创建File弹出菜单

	//Speed
// 	menuPopup.CreatePopupMenu();//
// 	menuPopup.AppendMenu(MF_STRING,MENU_LEVEL,"Speed");
// 	menuPopup.AppendMenu(MF_STRING,MENU_LEVEL,"Speed");
// 	menuPopup.AppendMenu(MF_STRING,MENU_LEVEL,"Speed");		
// 	menuPopup.AppendMenu(MF_STRING,MENU_SPEED,"Speed");

	SetMenu(&menuMain);//设置菜单

// 	menuPopup.CreatePopupMenu();
// 	menuPopup.AppendMenu(MF_STRING,ID_EDIT_COPY,"Copy");
// 	menuPopup.AppendMenu(MF_STRING,ID_EDIT_CUT,"Cut");
// 	menuMain.AppendMenu(MF_POPUP,(UINT)menuPopup.Detach(),"Edit");//创建Edit弹出菜单
	
	m_iTurnDirect = TURN_DIRECTION_RIGHT;
	m_iTurnCnt = 0;

	OnMenuStart();

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CTetris2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTetris2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		Draw(dc);
		CDialog::OnPaint();
	}
}
void CTetris2Dlg::Draw(CPaintDC& dc)
{	
	dc.Rectangle(GAME_ZONE_LEFT, GAME_ZONE_TOP, GAME_ZONE_RIGHT, GAME_ZONE_BOTTM);
}	

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CTetris2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTetris2Dlg::GenerateDiamond()
{
	srand( time(0) );
	int iShape = m_iShape = rand()%(SHAPE_END - SHAPE_BEGIN - 1);
	int iColor1(0);
	int iColor2(0);
	int iColor3(0);
	int iColor4(0);	
	int arrColor[4];
	do 
	{
		arrColor[0] = iColor1 = rand()%( sizeof(g_aDiamondColor)/sizeof(COLORREF) );
		arrColor[1] = iColor2 = rand()%( sizeof(g_aDiamondColor)/sizeof(COLORREF) );
		arrColor[2] = iColor3 = rand()%( sizeof(g_aDiamondColor)/sizeof(COLORREF) );
		arrColor[3] = iColor4 = rand()%( sizeof(g_aDiamondColor)/sizeof(COLORREF) );		
	} while ( CToolHelp<int>::IsHaveSame( sizeof(arrColor)/sizeof(arrColor[0]), arrColor ) );	


	CRect rectPerDiamond(GAME_ZONE_LEFT + GAME_ZONE_WIDTH/2 - PER_DIAMOND_LENTH, GAME_ZONE_TOP,
		GAME_ZONE_LEFT + GAME_ZONE_WIDTH/2, GAME_ZONE_TOP + PER_DIAMOND_LENTH);
	m_pStt1 = new CMyStatic();
	m_pStt1->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_1);
	m_pStt1->SetBkgColor(g_aDiamondColor[iColor1]);

	SetTimer( TIMER_ID, 1000, NULL );

	switch(iShape)
	{
	case SHAPE_I:
		{
			rectPerDiamond.OffsetRect(0,PER_DIAMOND_LENTH);
			m_pStt2 = new CMyStatic();
			m_pStt2->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_2);
			m_pStt2->SetBkgColor(g_aDiamondColor[iColor2]);
			rectPerDiamond.OffsetRect(0,PER_DIAMOND_LENTH);
			m_pStt3 = new CMyStatic();
			m_pStt3->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_3);
			m_pStt3->SetBkgColor(g_aDiamondColor[iColor3]);
			rectPerDiamond.OffsetRect(0,PER_DIAMOND_LENTH);
			m_pStt4 = new CMyStatic();
			m_pStt4->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_4);
			m_pStt4->SetBkgColor(g_aDiamondColor[iColor4]);

			break;
		}
	case SHAPE_L:
		{
			rectPerDiamond.OffsetRect(0,PER_DIAMOND_LENTH);
			m_pStt2 = new CMyStatic();
			m_pStt2->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_2);
			m_pStt2->SetBkgColor(g_aDiamondColor[iColor2]);
			rectPerDiamond.OffsetRect(0,PER_DIAMOND_LENTH);
			m_pStt3 = new CMyStatic();
			m_pStt3->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_3);
			m_pStt3->SetBkgColor(g_aDiamondColor[iColor3]);
			rectPerDiamond.OffsetRect(PER_DIAMOND_LENTH, 0);
			m_pStt4 = new CMyStatic();
			m_pStt4->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_4);
			m_pStt4->SetBkgColor(g_aDiamondColor[iColor4]);
			
			break;
		}
	case SHAPE_O:
		{
			rectPerDiamond.OffsetRect(PER_DIAMOND_LENTH, 0);
			m_pStt2 = new CMyStatic();
			m_pStt2->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_2);
			m_pStt2->SetBkgColor(g_aDiamondColor[iColor2]);
			rectPerDiamond.OffsetRect(0,PER_DIAMOND_LENTH);
			m_pStt3 = new CMyStatic();
			m_pStt3->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_3);
			m_pStt3->SetBkgColor(g_aDiamondColor[iColor3]);
			rectPerDiamond.OffsetRect(-PER_DIAMOND_LENTH, 0);
			m_pStt4 = new CMyStatic();
			m_pStt4->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_4);
			m_pStt4->SetBkgColor(g_aDiamondColor[iColor4]);

			break;
		}
	case SHAPE_K://|-
		{
			rectPerDiamond.OffsetRect(0,PER_DIAMOND_LENTH);
			m_pStt2 = new CMyStatic();
			m_pStt2->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_2);
			m_pStt2->SetBkgColor(g_aDiamondColor[iColor2]);
			rectPerDiamond.OffsetRect(0,PER_DIAMOND_LENTH);
			m_pStt3 = new CMyStatic();
			m_pStt3->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_3);
			m_pStt3->SetBkgColor(g_aDiamondColor[iColor3]);
			rectPerDiamond.OffsetRect( PER_DIAMOND_LENTH,-PER_DIAMOND_LENTH );
			m_pStt4 = new CMyStatic();
			m_pStt4->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_4);
			m_pStt4->SetBkgColor(g_aDiamondColor[iColor4]);

			break;
		}
	case SHAPE_Z: //  |_
		//    |
		{
			rectPerDiamond.OffsetRect(PER_DIAMOND_LENTH, 0);
			m_pStt2 = new CMyStatic();
			m_pStt2->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_2);
			m_pStt2->SetBkgColor(g_aDiamondColor[iColor2]);
			rectPerDiamond.OffsetRect(0, PER_DIAMOND_LENTH);
			m_pStt3 = new CMyStatic();
			m_pStt3->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_3);
			m_pStt3->SetBkgColor(g_aDiamondColor[iColor3]);
			rectPerDiamond.OffsetRect(PER_DIAMOND_LENTH, 0);
			m_pStt4 = new CMyStatic();
			m_pStt4->Create(NULL, WS_CHILD|WS_VISIBLE, rectPerDiamond, this, DIAMOND_ID_4);
			m_pStt4->SetBkgColor(g_aDiamondColor[iColor4]);

			break;
		}	
	}//End of switch(iShape)

	m_iTurnCnt = rand() % 4;
	if ( m_iTurnCnt == 1 || m_iTurnCnt == 3 )
	{
		//Turn();
	}
	m_iTurnCnt = 0;//test
}
void CTetris2Dlg::OnMenuStart()
{
	GenerateDiamond();
}

void CTetris2Dlg::OnMenuGame(UINT nID)
{
	switch(nID)
	{
	case MENU_START:
		{
			OnMenuStart();
			break;
		}
	}
}

void CTetris2Dlg::OnTimer(UINT nIDEvent)
{

	Move4SttOffSet(0, PER_DIAMOND_LENTH);

	CDialog::OnTimer(nIDEvent);
}

bool CTetris2Dlg::Is4SttCanMove(int iXOffSet, int iYOffSet)
{
	if ( !IsWindowCanMove(m_pStt1,iXOffSet, iYOffSet) )
	{
		return false;
	}
	if ( !IsWindowCanMove(m_pStt2,iXOffSet, iYOffSet) )
	{
		return false;
	}
	if ( !IsWindowCanMove(m_pStt3,iXOffSet, iYOffSet) )
	{
		return false;
	}
	if ( !IsWindowCanMove(m_pStt4,iXOffSet, iYOffSet) )
	{
		return false;
	}
	return true;
}
bool CTetris2Dlg::TouchDiamond(const CRect& rectDiamond, const vector< CMyStatic* >& vecSttStop)
{
	vector< CMyStatic* >::const_iterator iter = vecSttStop.begin();
	CRect rect;
	for ( ; iter != vecSttStop.end(); iter++ )
	{
		(*iter)->GetWindowRect(rect);
		ScreenToClient(rect);

		if ( rectDiamond.EqualRect( rect ) )
		{
			return true;
		}
	}
	return false;
}

void CTetris2Dlg::DestoyDiamond(vector< CMyStatic* >& vecPerLine, vector< CMyStatic* >& vecSttStop)
{
	vector< CMyStatic* >::iterator iterWhole = vecSttStop.begin();
	vector< CMyStatic* >::iterator iterPer = vecPerLine.begin();

	for ( ; iterPer != vecPerLine.end(); ++iterPer )
	{
		for (; iterWhole != m_vecSttStop.end(); ++iterWhole )
		{
			if ( *iterPer == *iterWhole )
			{
				vecSttStop.erase(iterWhole);
			}
		}
		(*iterPer)->DestroyWindow();
		delete(*iterPer);		
	}
	vecPerLine.clear();
}

void CTetris2Dlg::AfterEatDown(int iYPos,const vector< CMyStatic* >& vecSttStop)
{
	vector< CMyStatic* >::const_iterator iterWhole = vecSttStop.begin();
	for ( ; iterWhole != vecSttStop.end(); ++iterWhole )
	{
		CRect rect;
		(*iterWhole)->GetWindowRect(rect);
		ScreenToClient(rect);
		if ( rect.top < iYPos )
		{
			rect.OffsetRect(0, PER_DIAMOND_LENTH);
			(*iterWhole)->MoveWindow(rect);
		}
	}
	for ( iterWhole = vecSttStop.begin(); iterWhole != vecSttStop.end(); ++iterWhole )
	{
		(*iterWhole)->Invalidate(true);
	}
}

void CTetris2Dlg::EatPerLine()
{
	int iLeft(GAME_ZONE_LEFT);
	int iTop(GAME_ZONE_BOTTM - PER_DIAMOND_LENTH);
	CRect rectLine(iLeft, iTop, iLeft+PER_DIAMOND_LENTH, iTop+PER_DIAMOND_LENTH);
	vector< CMyStatic* >::iterator iter = m_vecSttStop.begin();
	CRect rectPer;
	vector< CMyStatic* > vecPerLine;	 
	while (1) 
	{	
		TRACE_W("m_vecSttStop.size %d\n", m_vecSttStop.size());
		TRACE_W("vecPerLine.size %d\n", vecPerLine.size());
		for ( ; iter != m_vecSttStop.end(); ++iter )
		{
			(*iter)->GetWindowRect(rectPer);
			ScreenToClient(rectPer);
			if ( rectPer == rectLine )
			{
				vecPerLine.push_back(*iter);				
				break;				
			}
		}

		rectLine.OffsetRect(PER_DIAMOND_LENTH, 0);
		if ( rectLine.left >= GAME_ZONE_RIGHT - PER_DIAMOND_LENTH )
		{
			if ( vecPerLine.size() == GAME_ZONE_WIDTH/PER_DIAMOND_LENTH )
			{
				DestoyDiamond(vecPerLine, m_vecSttStop);
				AfterEatDown(rectLine.top, m_vecSttStop);
				rectLine.OffsetRect(0, PER_DIAMOND_LENTH);
			}
			vecPerLine.clear();
			rectLine = CRect( GAME_ZONE_LEFT, rectLine.top - PER_DIAMOND_LENTH, GAME_ZONE_LEFT + PER_DIAMOND_LENTH, rectLine.top );
			if ( rectLine.top < GAME_ZONE_TOP )
			{
				break;
			}
		}
	} 



	for ( ; iter != m_vecSttStop.end(); ++iter )
	{
		(*iter)->GetWindowRect(rectPer);
		ScreenToClient(rectPer);
		if ( rectPer == rectLine )
		{
			rectLine.OffsetRect(PER_DIAMOND_LENTH, 0);
		}
		else
		{
			vecPerLine.clear();
		}

		if ( rectLine.right >= GAME_ZONE_RIGHT - PER_DIAMOND_LENTH )
		{
			vecPerLine.clear();
			iLeft = GAME_ZONE_LEFT;
			iTop -= PER_DIAMOND_LENTH;
			if ( iTop <= GAME_ZONE_TOP )
			{
				break;
			}
		}
		else
		{
			vecPerLine.push_back(*iter);
		}
	}
}



bool CTetris2Dlg::IsWindowCanMove(CWnd* pWnd, int iXOffSet, int iYOffSet)
{
	CRect rectDiamond;
	pWnd->GetWindowRect(&rectDiamond);
	rectDiamond.OffsetRect(iXOffSet, iYOffSet);
	ScreenToClient(rectDiamond);
	bool bTouch = TouchDiamond(rectDiamond, m_vecSttStop);
	bool bStop = bTouch && iXOffSet == 0 && iYOffSet == PER_DIAMOND_LENTH;
	if (rectDiamond.bottom > GAME_ZONE_BOTTM ||  bStop )
	{
		m_bIsStop = true;
		SttStop();

		GenerateDiamond();
		return false;
	}
	
	if ( rectDiamond.left < GAME_ZONE_LEFT
		|| rectDiamond.right > GAME_ZONE_RIGHT || bTouch )
	{
		return false;
	}
	return true;
}

void CTetris2Dlg::SttStop()
{
	m_vecSttStop.push_back(m_pStt1);
	m_vecSttStop.push_back(m_pStt2);
	m_vecSttStop.push_back(m_pStt3);
	m_vecSttStop.push_back(m_pStt4);
	m_pStt1 = NULL;
	m_pStt2 = NULL;
	m_pStt3 = NULL;
	m_pStt4 = NULL;
	EatPerLine();	
}

void CTetris2Dlg::Move4SttOffSet(int iXOffSet, int iYOffSet)
{
	if( !Is4SttCanMove(iXOffSet, iYOffSet) )
	{
		return;
	}
	MoveWindowOffSet(m_pStt1, iXOffSet, iYOffSet);
	MoveWindowOffSet(m_pStt2, iXOffSet, iYOffSet);
	MoveWindowOffSet(m_pStt3, iXOffSet, iYOffSet);
	MoveWindowOffSet(m_pStt4, iXOffSet, iYOffSet);
	m_pStt1->Invalidate(TRUE);
	m_pStt2->Invalidate(TRUE);
	m_pStt3->Invalidate(TRUE);
	m_pStt4->Invalidate(TRUE);
}

void CTetris2Dlg::MoveWindowOffSet(CWnd* pWnd, int iXOffSet, int iYOffSet)
{
	CRect rectDiamond;
	pWnd->GetWindowRect(&rectDiamond);
	rectDiamond.OffsetRect(iXOffSet, iYOffSet);
	ScreenToClient(rectDiamond);
	pWnd->MoveWindow(rectDiamond);
}

int CTetris2Dlg::TurnPoint(CRect rect1, CRect rect2, CRect rect3, CRect rect4)
{
	int iRect1 = CToolHelp<int>::RectTotalRange(rect1, 3, rect2, rect3, rect4);
	int iRect2 = CToolHelp<int>::RectTotalRange(rect2, 3, rect1, rect3, rect4);
	int iRect3 = CToolHelp<int>::RectTotalRange(rect3, 3, rect2, rect1, rect4);
	int iRect4 = CToolHelp<int>::RectTotalRange(rect4, 3, rect2, rect3, rect1);

	int array[4] = { iRect1, iRect2, iRect3, iRect4 };

	vector<int> vecMin = CToolHelp<int>::MinValue(4, iRect1);

	if ( vecMin.size() == 1 )
	{
		return vecMin[0];
	}

	vector<int>::iterator iter = vecMin.begin();
	CRect arrCRect[4] = {rect1, rect2, rect3, rect4};
	vector<CRect> vecCRect;
	for ( ; iter != vecMin.end(); iter++)
	{
		vecCRect.push_back( arrCRect[*iter] );
	}



	if ( TURN_DIRECTION_RIGHT == m_iTurnDirect )
	{
		
	}

}
// 
// void CTetris2Dlg::OrderDiamondPoint()
// {
// 
// }

void CTetris2Dlg::ShapeITurn()
{
	if ( m_iTurnCnt == 0 || m_iTurnCnt == 2 )//是竖着时
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{	
			CRect rect3;
			m_pStt3->GetWindowRect(rect3);
			ScreenToClient(rect3);			
			if ( !IsWindowCanMove(m_pStt3, -PER_DIAMOND_LENTH, 0) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt3, PER_DIAMOND_LENTH, 0) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt3, 2*PER_DIAMOND_LENTH, 0) )
			{
				return;
			}
			CRect rect1(rect3);
			CRect rect2(rect3);
			CRect rect4(rect3);		
			rect1.OffsetRect(2*PER_DIAMOND_LENTH, 0);
			rect2.OffsetRect(PER_DIAMOND_LENTH, 0);
			rect4.OffsetRect(-PER_DIAMOND_LENTH, 0);

			m_pStt1->MoveWindow(rect1);
			m_pStt2->MoveWindow(rect2);
			m_pStt3->MoveWindow(rect3);
			m_pStt4->MoveWindow(rect4);

			//4 3 2 1
			//将指针变下使其顺序为1 2 3 4
			CMyStatic* pTemp = m_pStt1;
			m_pStt1 = m_pStt4;
			m_pStt4 = pTemp;
			pTemp = m_pStt2;
			m_pStt2 = m_pStt3;
			m_pStt3 = pTemp;

			m_iTurnCnt = 1;
		}
	}
	else//是横着时
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{
			CRect rect2;
			m_pStt2->GetWindowRect(rect2);
			ScreenToClient(rect2);
			if ( !IsWindowCanMove(m_pStt2, 0, -PER_DIAMOND_LENTH) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, 0, PER_DIAMOND_LENTH ) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, 0, 2*PER_DIAMOND_LENTH ) )
			{
				return;
			}
			CRect rect1(rect2);
			CRect rect3(rect2);
			CRect rect4(rect2);	
			rect1.OffsetRect(0, -PER_DIAMOND_LENTH);
			rect3.OffsetRect(0, PER_DIAMOND_LENTH);
			rect4.OffsetRect(0, 2*PER_DIAMOND_LENTH);

			m_pStt1->MoveWindow(rect1);
			m_pStt2->MoveWindow(rect2);
			m_pStt3->MoveWindow(rect3);
			m_pStt4->MoveWindow(rect4);
			m_iTurnCnt = 0;
		}
	}// end of  else//是横着时

	m_pStt1->Invalidate(TRUE);
	m_pStt2->Invalidate(TRUE);
	m_pStt3->Invalidate(TRUE);
	m_pStt4->Invalidate(TRUE);
}

void CTetris2Dlg::ShapeLTurn()
{
	CRect rect3;
	m_pStt3->GetWindowRect(rect3);
	ScreenToClient(rect3);

	CRect rect1(rect3);
	CRect rect2(rect3);
	CRect rect4(rect3);	

	if ( m_iTurnCnt == 0 )//是L时
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{					
			if ( !IsWindowCanMove(m_pStt3, 2*PER_DIAMOND_LENTH, 0) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt3, PER_DIAMOND_LENTH, 0) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt3, 0, PER_DIAMOND_LENTH) )
			{
				return;
			}	
			rect1.OffsetRect(2*PER_DIAMOND_LENTH, 0);
			rect2.OffsetRect(PER_DIAMOND_LENTH, 0);
			rect4.OffsetRect(0, PER_DIAMOND_LENTH);
		}
	}
	else if(1 == m_iTurnCnt )
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{		
			if ( !IsWindowCanMove(m_pStt3, 0, 2*PER_DIAMOND_LENTH) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt3, 0, PER_DIAMOND_LENTH) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt3, -PER_DIAMOND_LENTH, 0) )
			{
				return;
			}	
			rect1.OffsetRect(0, 2*PER_DIAMOND_LENTH);
			rect2.OffsetRect(0, PER_DIAMOND_LENTH);
			rect4.OffsetRect(-PER_DIAMOND_LENTH, 0);		
		}
	}// end of if(1 == m_iTurnCnt )
	else if ( 2 == m_iTurnCnt )
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{		
			if ( !IsWindowCanMove(m_pStt3, -2*PER_DIAMOND_LENTH, 0) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt3, -PER_DIAMOND_LENTH, 0) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt3, 0, -PER_DIAMOND_LENTH) )
			{
				return;
			}	
			rect1.OffsetRect(-2*PER_DIAMOND_LENTH, 0);
			rect2.OffsetRect(-PER_DIAMOND_LENTH, 0);
			rect4.OffsetRect(0, -PER_DIAMOND_LENTH);		
		}
	}// end of  if ( 2 == m_iTurnCnt )
	else if ( 3 == m_iTurnCnt )
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{		
			if ( !IsWindowCanMove(m_pStt3, 0, -2*PER_DIAMOND_LENTH) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt3, 0, -PER_DIAMOND_LENTH) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt3, PER_DIAMOND_LENTH, 0) )
			{
				return;
			}	
			rect1.OffsetRect(0, -2*PER_DIAMOND_LENTH);
			rect2.OffsetRect(0, -PER_DIAMOND_LENTH);
			rect4.OffsetRect(PER_DIAMOND_LENTH, 0);		
		}
	}
	m_pStt1->MoveWindow(rect1);
	m_pStt2->MoveWindow(rect2);
	m_pStt3->MoveWindow(rect3);
	m_pStt4->MoveWindow(rect4);
	m_iTurnCnt++;
	m_iTurnCnt %= 4;
	m_pStt1->Invalidate(TRUE);
	m_pStt2->Invalidate(TRUE);
	m_pStt3->Invalidate(TRUE);
	m_pStt4->Invalidate(TRUE);
}

void CTetris2Dlg::ShapeOTurn()
{
	CRect rect1;
	m_pStt1->GetWindowRect(rect1);
	ScreenToClient(rect1);

	CRect rect2(rect1);
	CRect rect3(rect1);
	CRect rect4(rect1);	


	if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
	{					
		if ( !IsWindowCanMove(m_pStt1, PER_DIAMOND_LENTH, 0) )
		{
			return;
		}				
		if ( !IsWindowCanMove(m_pStt1, PER_DIAMOND_LENTH, PER_DIAMOND_LENTH) )
		{
			return;
		}				
		if ( !IsWindowCanMove(m_pStt1, 0, PER_DIAMOND_LENTH) )
		{
			return;
		}	
		rect2.OffsetRect(PER_DIAMOND_LENTH, 0);
		rect3.OffsetRect(PER_DIAMOND_LENTH, PER_DIAMOND_LENTH);
		rect4.OffsetRect(0, PER_DIAMOND_LENTH);
	}	
	m_pStt1->MoveWindow(rect2);
	m_pStt2->MoveWindow(rect3);
	m_pStt3->MoveWindow(rect4);
	m_pStt4->MoveWindow(rect1);

	CMyStatic* pTemp = m_pStt1;
	m_pStt1 = m_pStt4;
	m_pStt4 = m_pStt3;
	m_pStt3 = m_pStt2;
	m_pStt2 = pTemp;

	m_pStt1->Invalidate(TRUE);
	m_pStt2->Invalidate(TRUE);
	m_pStt3->Invalidate(TRUE);
	m_pStt4->Invalidate(TRUE);
}


void CTetris2Dlg::ShapeKTurn()//|-
{
	CRect rect2;
	m_pStt2->GetWindowRect(rect2);
	ScreenToClient(rect2);

	CRect rect1(rect2);
	CRect rect3(rect2);
	CRect rect4(rect2);	

	if ( m_iTurnCnt == 0 )//|-
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{					
			if ( !IsWindowCanMove(m_pStt2, PER_DIAMOND_LENTH, 0) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, 0, PER_DIAMOND_LENTH) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, -PER_DIAMOND_LENTH, 0) )
			{
				return;
			}	
			rect1.OffsetRect(PER_DIAMOND_LENTH, 0);
			rect3.OffsetRect(0, PER_DIAMOND_LENTH);
			rect4.OffsetRect(-PER_DIAMOND_LENTH, 0);
		}
	}
	else if(1 == m_iTurnCnt )//T时
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{		
			if ( !IsWindowCanMove(m_pStt2, 0, PER_DIAMOND_LENTH) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, -PER_DIAMOND_LENTH, 0) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, 0, -PER_DIAMOND_LENTH) )
			{
				return;
			}	
			rect1.OffsetRect(0, PER_DIAMOND_LENTH);
			rect3.OffsetRect(-PER_DIAMOND_LENTH, 0);
			rect4.OffsetRect(0, -PER_DIAMOND_LENTH);		
		}
	}// end of if(1 == m_iTurnCnt )
	else if ( 2 == m_iTurnCnt )// -| 时
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{		
			if ( !IsWindowCanMove(m_pStt2, -PER_DIAMOND_LENTH, 0) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, 0, -PER_DIAMOND_LENTH) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, PER_DIAMOND_LENTH, 0) )
			{
				return;
			}	
			rect1.OffsetRect(-PER_DIAMOND_LENTH, 0);
			rect3.OffsetRect(0, -PER_DIAMOND_LENTH);
			rect4.OffsetRect(PER_DIAMOND_LENTH, 0);		
		}
	}// end of  if ( 2 == m_iTurnCnt )
	else if ( 3 == m_iTurnCnt )//
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{		
			if ( !IsWindowCanMove(m_pStt2, 0, -PER_DIAMOND_LENTH) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, PER_DIAMOND_LENTH, 0) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, 0, PER_DIAMOND_LENTH) )
			{
				return;
			}	
			rect1.OffsetRect(0, -PER_DIAMOND_LENTH);
			rect3.OffsetRect(PER_DIAMOND_LENTH, 0);
			rect4.OffsetRect(0, PER_DIAMOND_LENTH);		
		}
	}
	m_pStt1->MoveWindow(rect1);
	m_pStt2->MoveWindow(rect2);
	m_pStt3->MoveWindow(rect3);
	m_pStt4->MoveWindow(rect4);
	m_iTurnCnt++;
	m_iTurnCnt %= 4;
	m_pStt1->Invalidate(TRUE);
	m_pStt2->Invalidate(TRUE);
	m_pStt3->Invalidate(TRUE);
	m_pStt4->Invalidate(TRUE);
}


void CTetris2Dlg::ShapeZTurn()//Z
{
	CRect rect2;// 以2 为轴吧
	m_pStt2->GetWindowRect(rect2);
	ScreenToClient(rect2);

	CRect rect1(rect2);
	CRect rect3(rect2);
	CRect rect4(rect2);	

	if ( 0 == m_iTurnCnt )//Z (0)
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{
			if ( !IsWindowCanMove(m_pStt2, PER_DIAMOND_LENTH, 0) )
			{
				return;
			}
			if ( !IsWindowCanMove(m_pStt2, PER_DIAMOND_LENTH, PER_DIAMOND_LENTH) )
			{
				return;
			}				 
			if ( !IsWindowCanMove(m_pStt2, 0, PER_DIAMOND_LENTH) )
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, 0, 2*PER_DIAMOND_LENTH) )
			{
				return;
			}	
			rect1.OffsetRect(PER_DIAMOND_LENTH, 0);
			rect2.OffsetRect(PER_DIAMOND_LENTH, PER_DIAMOND_LENTH);
			rect3.OffsetRect(0, PER_DIAMOND_LENTH);
			rect4.OffsetRect(0, 2*PER_DIAMOND_LENTH);
		}
	}
	else if(1 == m_iTurnCnt )// 与 (1) 时
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{		
			if ( !IsWindowCanMove(m_pStt2, PER_DIAMOND_LENTH, 0) )//1
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, 0, -PER_DIAMOND_LENTH) )//3
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, -PER_DIAMOND_LENTH, -PER_DIAMOND_LENTH) )
			{
				return;
			}	
			rect1.OffsetRect( PER_DIAMOND_LENTH, 0);
			rect3.OffsetRect(0, -PER_DIAMOND_LENTH);
			rect4.OffsetRect(-PER_DIAMOND_LENTH, -PER_DIAMOND_LENTH);		
		}
	}// end of if(1 == m_iTurnCnt )
	else if ( 2 == m_iTurnCnt )// Z (2) 时
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{		
			if ( !IsWindowCanMove(m_pStt2, 0, PER_DIAMOND_LENTH) )//1
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, PER_DIAMOND_LENTH, 0) )//3
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, PER_DIAMOND_LENTH, -PER_DIAMOND_LENTH) )
			{
				return;
			}	
			rect1.OffsetRect(0, PER_DIAMOND_LENTH);
			rect3.OffsetRect(PER_DIAMOND_LENTH, 0);
			rect4.OffsetRect(PER_DIAMOND_LENTH, -PER_DIAMOND_LENTH);		
		}
	}// end of  if ( 2 == m_iTurnCnt )
	else if ( 3 == m_iTurnCnt )// 与(3)时
	{
		if ( m_iTurnDirect == TURN_DIRECTION_RIGHT )
		{		
			if ( !IsWindowCanMove(m_pStt2, 0, -PER_DIAMOND_LENTH) )//1
			{
				return;
			}	
			if ( !IsWindowCanMove(m_pStt2, PER_DIAMOND_LENTH, -PER_DIAMOND_LENTH) )//2
			{
				return;
			}
			if ( !IsWindowCanMove(m_pStt2, PER_DIAMOND_LENTH, 0) )//3
			{
				return;
			}				
			if ( !IsWindowCanMove(m_pStt2, 2*PER_DIAMOND_LENTH, 0) )//4
			{
				return;
			}	
			rect1.OffsetRect(0, -PER_DIAMOND_LENTH);
			rect2.OffsetRect(PER_DIAMOND_LENTH, -PER_DIAMOND_LENTH);
			rect3.OffsetRect(PER_DIAMOND_LENTH, 0);
			rect4.OffsetRect(2*PER_DIAMOND_LENTH, 0);		
		}
	}
	m_pStt1->MoveWindow(rect1);
	m_pStt2->MoveWindow(rect2);
	m_pStt3->MoveWindow(rect3);
	m_pStt4->MoveWindow(rect4);
	m_iTurnCnt++;
	m_iTurnCnt %= 4;
	m_pStt1->Invalidate(TRUE);
	m_pStt2->Invalidate(TRUE);
	m_pStt3->Invalidate(TRUE);
	m_pStt4->Invalidate(TRUE);
}


void CTetris2Dlg::Turn()
{
	
	switch( m_iShape )
	{
	case SHAPE_I:
		{
			ShapeITurn();			
			break;
		}
	case SHAPE_L:
		{
			ShapeLTurn();	
			break;
		}
	case SHAPE_O:
		{
			ShapeOTurn();	
			break;
		}
	case SHAPE_K://|-
		{
			ShapeKTurn();	
			break;
		}
	case SHAPE_Z: //  |_
		//    |
		{
			ShapeZTurn();	

			break;
		}
	}
}

BOOL CTetris2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN)
	{
		switch( pMsg->wParam)
		{
		case VK_LEFT:
			{
				Move4SttOffSet(-PER_DIAMOND_LENTH, 0);
				break;
			}
		case VK_UP:
			{
				//Move4SttOffSet(-PER_DIAMOND_LENTH, 0);
				int iRet = CToolHelp<int>::SameCnt(5, 4, 0, -5, 3, 0);
				Turn();

				break;
			}
		case VK_RIGHT:
			{
				Move4SttOffSet(PER_DIAMOND_LENTH, 0);
				break;
			}
		case VK_DOWN:
			{
				Move4SttOffSet(0, PER_DIAMOND_LENTH);
				break;
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
