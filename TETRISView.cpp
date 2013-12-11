// TETRISView.cpp : implementation of the CTETRISView class
//

#include "stdafx.h"
#include "TETRIS.h"
#include "GameSetting.h"

#include "TETRISDoc.h"
#include "TETRISView.h"

#include "mmsystem.h"
#pragma comment(lib,  "Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTETRISView

IMPLEMENT_DYNCREATE(CTETRISView, CView)

BEGIN_MESSAGE_MAP(CTETRISView, CView)
	//{{AFX_MSG_MAP(CTETRISView)
	ON_WM_CREATE()
	ON_COMMAND(ID_GAME_START, OnGameStart)
	ON_UPDATE_COMMAND_UI(ID_GAME_START, OnUpdateGameStart)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_GAME_PAUSE, OnGamePause)
	ON_UPDATE_COMMAND_UI(ID_GAME_PAUSE, OnUpdateGamePause)
	ON_COMMAND(ID_GAME_END, OnGameEnd)
	ON_UPDATE_COMMAND_UI(ID_GAME_END, OnUpdateGameEnd)
	ON_COMMAND(ID_GAME_SETTING, OnGameSetting)
	ON_UPDATE_COMMAND_UI(ID_GAME_SETTING, OnUpdateGameSetting)
	ON_COMMAND(ID_GAME_LEVEL1, OnGameLevel1)
	ON_UPDATE_COMMAND_UI(ID_GAME_LEVEL1, OnUpdateGameLevel1)
	ON_COMMAND(ID_GAME_LEVEL2, OnGameLevel2)
	ON_UPDATE_COMMAND_UI(ID_GAME_LEVEL2, OnUpdateGameLevel2)
	ON_COMMAND(ID_GAME_LEVEL3, OnGameLevel3)
	ON_UPDATE_COMMAND_UI(ID_GAME_LEVEL3, OnUpdateGameLevel3)
	ON_COMMAND(ID_GAME_LEVEL4, OnGameLevel4)
	ON_UPDATE_COMMAND_UI(ID_GAME_LEVEL4, OnUpdateGameLevel4)
	ON_COMMAND(ID_GAME_LEVEL5, OnGameLevel5)
	ON_UPDATE_COMMAND_UI(ID_GAME_LEVEL5, OnUpdateGameLevel5)
	ON_COMMAND(ID_SHOW_GRID, OnShowGrid)
	ON_UPDATE_COMMAND_UI(ID_SHOW_GRID, OnUpdateShowGrid)
	ON_COMMAND(ID_PLAY_MUSIC, OnPlayMusic)
	ON_UPDATE_COMMAND_UI(ID_PLAY_MUSIC, OnUpdatePlayMusic)
	ON_COMMAND(ID_ABOUT_GAMERULE, OnAboutGamerule)
	ON_UPDATE_COMMAND_UI(ID_ABOUT_GAMERULE, OnUpdateAboutGamerule)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTETRISView construction/destruction

CTETRISView::CTETRISView()
{
	// TODO: add construction code here
	m_bGamePause = FALSE;
	m_bGameEnd = TRUE;

	m_iRow = 20;
	m_iCol = 10;
	m_iSize = 30;

	m_bDrawGrid = 1;
	m_bPlayMusic = FALSE;

	int i,j;

	// Initialize: hide blocks
	for(i=0; i<m_iRow; i++)
		for(j=0; j<m_iCol; j++)
			showBlock[i][j] = 0;

	// Initialize bottomInterface data
	// i stands for block's shape, which is changed clockwise. 
	//    e.g.,1 for erect I-style block and 11 for horizontal I-style block
	// j stands for the bottomInterface number, orderly from small to large
	// for details please refer to Program Design Report

	for(i=1; i<=74; i++)
		for(j=0; j<4; j++)
			bottomInterface[i][j] = -1;

	// I-style block
	bottomInterface[1][0] = 3;	
	bottomInterface[11][0] = 0; bottomInterface[11][1] = 1;	bottomInterface[11][2] = 2; bottomInterface[11][3] = 3;

	// O-style block
	bottomInterface[2][0] = 1; bottomInterface[2][1] = 3;

	// T-style block
	bottomInterface[3][0] = 0; bottomInterface[3][1] = 2; bottomInterface[3][2] = 3;	
	bottomInterface[31][0] = 2; bottomInterface[31][1] = 3;	
	bottomInterface[32][0] = 0; bottomInterface[32][1] = 2; bottomInterface[32][2] = 3;	
	bottomInterface[33][0] = 0; bottomInterface[33][1] = 3;

	// S-style block
	bottomInterface[4][0] = 1; bottomInterface[4][1] = 3;	
	bottomInterface[41][0] = 0; bottomInterface[41][1] = 2; bottomInterface[41][2] = 3;

	// Z-style block
	bottomInterface[5][0] = 1; bottomInterface[5][1] = 3;
	bottomInterface[51][0] = 0; bottomInterface[51][1] = 2; bottomInterface[51][2] = 3;

	// L-style block
	bottomInterface[6][0] = 0; bottomInterface[6][1] = 3;	
	bottomInterface[61][0] = 0; bottomInterface[61][1] = 1; bottomInterface[61][2] = 3;
	bottomInterface[62][0] = 2; bottomInterface[62][1] = 3;
	bottomInterface[63][0] = 1; bottomInterface[63][1] = 2; bottomInterface[63][2] = 3;

	// J-style block
	bottomInterface[7][0] = 2; bottomInterface[7][1] = 3;	
	bottomInterface[71][0] = 0; bottomInterface[71][1] = 1; bottomInterface[71][2] = 3;
	bottomInterface[72][0] = 0; bottomInterface[72][1] = 3;
	bottomInterface[73][0] = 1; bottomInterface[73][1] = 2; bottomInterface[73][2] = 3;
}

CTETRISView::~CTETRISView()
{
}

BOOL CTETRISView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTETRISView drawing

/****************************************************************************
* Function: Initialize the game's basic information
*
* Last modify date: 2009-12-2
****************************************************************************/
int CTETRISView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	screenBrush = new CBrush(BLACK);
	gameAreaBrush = new CBrush(RGB(128,128,128));

	blockBrush = new CBrush(RGB(255,255,255));

	
	gridLinePen = new CPen(PS_SOLID,1,RGB(0,0,0));
	whitePen = new CPen(PS_SOLID,1,RGB(255,255,255));

	m_iNextBlockType = Random(7);
	m_iLevel = 3;

	return 0;
}

/****************************************************************************
* Function: show game area, block area, totle score,
*	game level and so on
*
* Last modify date: 2009-11-2
****************************************************************************/
void CTETRISView::OnDraw(CDC* pDC)
{
	CTETRISDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	pDC->SelectObject(screenBrush);
	CRect rect;
	GetClientRect(&rect);
	pDC->Rectangle(rect);

	pDC->SelectObject(gameAreaBrush);
	pDC->Rectangle(10, 10, 10+10*m_iSize, 10+20*m_iSize);

	pDC->SelectObject(gridLinePen);
	int i,j;
	if(m_bDrawGrid)
	{
		//draw horizontal grid line
		for(i=0; i<m_iRow; i++)
		{
			pDC->MoveTo(10, 10+i*m_iSize);
			pDC->LineTo(10+10*m_iSize, 10+i*m_iSize);
		}

		//draw vertical grid line
		for(i=0; i<m_iCol; i++)
		{
			pDC->MoveTo(10+i*m_iSize, 10);
			pDC->LineTo(10+i*m_iSize, 10+20*m_iSize);
		}
	}

	// Draw block of different colors
	switch(blockColor)
	{
	case 1:
		blockBrush = new CBrush(RGB(255,255,255));
		break;
	case 2:
		blockBrush = new CBrush(RGB(255,0,0));
		break;
	case 3:
		blockBrush = new CBrush(RGB(0,255,0));
		break;
	case 4:
		blockBrush = new CBrush(RGB(0,0,255));
		break;
	case 5:
		blockBrush = new CBrush(RGB(255,255,0));
		break;
	case 6:
		blockBrush = new CBrush(RGB(255,0,255));
		break;
	case 7:
		blockBrush = new CBrush(RGB(0,255,255));
		break;
	default:
		break;
	}
	pDC->SelectObject(blockBrush);
	pDC->SelectObject(whitePen);
	for(i=0; i<m_iRow; i++)
	{
		for(j=0; j<m_iCol; j++)
		{
			if(showBlock[i][j] == 1)
			{
				// Draw block's top boarder and right boarder
				pDC->MoveTo(10+j*m_iSize+1, 10+i*m_iSize+1);
				pDC->LineTo(10+(j+1)*m_iSize-1, 10+i*m_iSize+1);
				pDC->MoveTo(10+(j+1)*m_iSize-1, 10+i*m_iSize+1);
				pDC->LineTo(10+(j+1)*m_iSize-1, 10+(i+1)*m_iSize-1);

				// Draw block's left boarder and bottom board
				pDC->MoveTo(10+j*m_iSize+1, 10+i*m_iSize+1);
				pDC->LineTo(10+j*m_iSize+1, 10+(i+1)*m_iSize-1);
				pDC->MoveTo(10+j*m_iSize+1, 10+(i+1)*m_iSize-1);
				pDC->LineTo(10+(j+1)*m_iSize-1, 10+(i+1)*m_iSize-1);

				// Draw block' color
			
				pDC->Rectangle(10+j*m_iSize+2, 10+i*m_iSize+2, 10+(j+1)*m_iSize-2, 10+(i+1)*m_iSize-2);

			}			
		}
	}

	if(!m_bGameEnd)
	{
		// Show next block
		pDC->SetBkColor(BLACK);
		pDC->SetTextColor(WHITE);
		pDC->TextOut(10+320, 10, "Next Block:");
		for(int k=0; k<4; k++)
		{
			i = nextBlockRow[k];
			j = nextBlockCol[k];

			// draw next block's top boarder and right board
			pDC->MoveTo(10+j*m_iSize+1+320, 10+i*m_iSize+1+30);
			pDC->LineTo(10+(j+1)*m_iSize-1+320, 10+i*m_iSize+1+30);
			pDC->MoveTo(10+(j+1)*m_iSize-1+320, 10+i*m_iSize+1+30);
			pDC->LineTo(10+(j+1)*m_iSize-1+320, 10+(i+1)*m_iSize-1+30);
			
			// draw next block's left boarder and bottom board
			pDC->MoveTo(10+j*m_iSize+1+320, 10+i*m_iSize+1+30);
			pDC->LineTo(10+j*m_iSize+1+320, 10+(i+1)*m_iSize-1+30);
			pDC->MoveTo(10+j*m_iSize+1+320, 10+(i+1)*m_iSize-1+30);
			pDC->LineTo(10+(j+1)*m_iSize-1+320, 10+(i+1)*m_iSize-1+30);

			pDC->Rectangle(10+j*m_iSize+2+320, 10+i*m_iSize+2+30,
				10+(j+1)*m_iSize+-2+320, 10+(i+1)*m_iSize-2+30);

		}

		// Show total score
		pDC->TextOut(10+320, 10+180, "Total score:");
		CString str;
		str.Format("%d", m_iScore);
		pDC->TextOut(10+320, 10+200, str);

		// Show game level
		pDC->TextOut(10+320, 10+280, "Game level:");
		CString str2;
		str2.Format("%d", m_iLevel);
		pDC->TextOut(10+320, 10+300, str2);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTETRISView printing

BOOL CTETRISView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTETRISView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTETRISView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTETRISView diagnostics

#ifdef _DEBUG
void CTETRISView::AssertValid() const
{
	CView::AssertValid();
}

void CTETRISView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTETRISDoc* CTETRISView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTETRISDoc)));
	return (CTETRISDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTETRISView message handlers

/****************************************************************************
* Function: Do all of the drive task
* 
* Last Modify Date: 2009-12-2
****************************************************************************/
void CTETRISView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	// If game is beginning or the pre-block falled to bottom, new block falls
	if(m_bFallToBottom)
	{
		m_iCurBlockType = m_iNextBlockType;
		m_iNextBlockType = Random(7);
		CurrentBlockStatus(m_iCurBlockType);
		SetBlockStatus();
		m_bFallToBottom = FALSE;
		FallToBottom();
		InvalidateBlockArea();

		NextBlockStatus(m_iNextBlockType);
		CRect rect(10+320, 10, 10+440, 10+160);
		InvalidateRect(&rect);

		int i,j,k;
		if(m_bFallToBottom)
		{
			for(i=0; i<m_iCol; i++)
			{
				if(showBlock[0][i])
				{
					KillTimer(1);
					AfxMessageBox("Game Over!");
					for(j=0; j<m_iRow; j++)
					{
						for(k=0; k<m_iCol; k++)
						{
							showBlock[j][k]=0;
						}
					}
					Invalidate();
					m_bGameEnd = TRUE;
					break;
				}
			}//for
		}//if
	}//if

	else
	{
		BlockMoveDown();
	}
	CView::OnTimer(nIDEvent);
}


/****************************************************************************
* Function: Result in a random value stand for block's type
*	1 for I-style, 2 for O-style, 3 for T-style, 4 for S-style
*	5 for Z-style, 6 for L-style, 7 for J-style
*
* Last modify date: 2009-12-2
****************************************************************************/
int CTETRISView::Random(int MaxNumber)
{
	int number;	
	srand(time(NULL));
	number= rand()%MaxNumber+1;	
	return number;
}


/****************************************************************************
* Function: Show/Hide the status of block, 1 for show and 0 for hide
*
* Last modify date: 2009-12-2
****************************************************************************/
void CTETRISView::SetBlockStatus()
{
	int row0,row1,row2,row3,col0,col1,col2,col3;
	row0 = curBlockRow[0];
	row1 = curBlockRow[1];
	row2 = curBlockRow[2];
	row3 = curBlockRow[3];
	col0 = curBlockCol[0];
	col1 = curBlockCol[1];
	col2 = curBlockCol[2];
	col3 = curBlockCol[3];

	showBlock[row0][col0] = 1;
	showBlock[row1][col1] = 1;
	showBlock[row2][col2] = 1;
	showBlock[row3][col3] = 1;
}

/****************************************************************************
* Function: Show rows and columns of current block
*
* Last modify date: 2009-12-2
*****************************************************************************/
void CTETRISView::CurrentBlockStatus(int m_iType)
{
	switch(m_iType)
	{
	case 1: 
		curBlockRow[0] = 0;	curBlockCol[0] = 5;	curBlockRow[1] = 1;	curBlockCol[1] = 5;
		curBlockRow[2] = 2;	curBlockCol[2] = 5;	curBlockRow[3] = 3;	curBlockCol[3] = 5;
		blockColor = 1;
		break;
	case 2: 
		curBlockRow[0] = 0;	curBlockCol[0] = 5;	curBlockRow[1] = 1;	curBlockCol[1] = 5;
		curBlockRow[2] = 0;	curBlockCol[2] = 6;	curBlockRow[3] = 1;	curBlockCol[3] = 6;
		blockColor = 2;
		break;
	case 3:
		curBlockRow[0] = 1;	curBlockCol[0] = 4;	curBlockRow[1] = 0;	curBlockCol[1] = 5;
		curBlockRow[2] = 1;	curBlockCol[2] = 5;	curBlockRow[3] = 1;	curBlockCol[3] = 6;
		blockColor = 3;
		break;
	case 4:
		curBlockRow[0] = 0;	curBlockCol[0] = 5;	curBlockRow[1] = 1;	curBlockCol[1] = 5;
		curBlockRow[2] = 1;	curBlockCol[2] = 6;	curBlockRow[3] = 2;	curBlockCol[3] = 6;
		blockColor = 4;
		break;
	case 5:
		curBlockRow[0] = 1;	curBlockCol[0] = 5;	curBlockRow[1] = 2;	curBlockCol[1] = 5;
		curBlockRow[2] = 0;	curBlockCol[2] = 6;	curBlockRow[3] = 1;	curBlockCol[3] = 6;
		blockColor = 5;
		break;
	case 6:
		curBlockRow[0] = 0;	curBlockCol[0] = 5;	curBlockRow[1] = 0;	curBlockCol[1] = 6;
		curBlockRow[2] = 1;	curBlockCol[2] = 6;	curBlockRow[3] = 2;	curBlockCol[3] = 6;
		blockColor = 6;
		break;
	case 7:
		curBlockRow[0] = 0;	curBlockCol[0] = 5;	curBlockRow[1] = 1;	curBlockCol[1] = 5;
		curBlockRow[2] = 2;	curBlockCol[2] = 5;	curBlockRow[3] = 0;	curBlockCol[3] = 6;
		blockColor = 7;
		break;
	default:
		break;
	}
}

/****************************************************************************
* Function: Show rows and columns of next block
*
* Last modify mode: 2009-12-2
****************************************************************************/
void CTETRISView::NextBlockStatus(int m_iType)
{
	switch(m_iType)
	{
	case 1:
		nextBlockRow[0] = 0;	nextBlockCol[0] = 1;	nextBlockRow[1] = 1;	nextBlockCol[1] = 1;
		nextBlockRow[2] = 2;	nextBlockCol[2] = 1;	nextBlockRow[3] = 3;	nextBlockCol[3] = 1;
		break;
	case 2:
		nextBlockRow[0] = 0;	nextBlockCol[0] = 1;	nextBlockRow[1] = 1;	nextBlockCol[1] = 1;
		nextBlockRow[2] = 0;	nextBlockCol[2] = 2;	nextBlockRow[3] = 1;	nextBlockCol[3] = 2;
		break;
	case 3:
		nextBlockRow[0] = 1;	nextBlockCol[0] = 0;	nextBlockRow[1] = 0;	nextBlockCol[1] = 1;
		nextBlockRow[2] = 1;	nextBlockCol[2] = 1;	nextBlockRow[3] = 1;	nextBlockCol[3] = 2;
		break;
	case 4:
		nextBlockRow[0] = 0;	nextBlockCol[0] = 1;	nextBlockRow[1] = 1;	nextBlockCol[1] = 1;
		nextBlockRow[2] = 1;	nextBlockCol[2] = 2;	nextBlockRow[3] = 2;	nextBlockCol[3] = 2;
		break;
	case 5:
		nextBlockRow[0] = 1;	nextBlockCol[0] = 1;	nextBlockRow[1] = 2;	nextBlockCol[1] = 1;
		nextBlockRow[2] = 0;	nextBlockCol[2] = 2;	nextBlockRow[3] = 1;	nextBlockCol[3] = 2;
		break;
	case 6:
		nextBlockRow[0] = 0;	nextBlockCol[0] = 1;	nextBlockRow[1] = 0;	nextBlockCol[1] = 2;
		nextBlockRow[2] = 1;	nextBlockCol[2] = 2;	nextBlockRow[3] = 2;	nextBlockCol[3] = 2;
		break;
	case 7:
		nextBlockRow[0] = 0;	nextBlockCol[0] = 1;	nextBlockRow[1] = 1;	nextBlockCol[1] = 1;
		nextBlockRow[2] = 2;	nextBlockCol[2] = 1;	nextBlockRow[3] = 0;	nextBlockCol[3] = 2;
		break;
	default:
		break;
	}
}

/**********************************************************
* Function: Move down the block
*
* Last Modify Date: 2009-12-2
**********************************************************/
void CTETRISView::BlockMoveDown()
{
	FallToBottom();
	if(!m_bFallToBottom)
	{
		int row0,row1,row2,row3,col0,col1,col2,col3;
		row0 = curBlockRow[0];
		row1 = curBlockRow[1];
		row2 = curBlockRow[2];
		row3 = curBlockRow[3];
		col0 = curBlockCol[0];
		col1 = curBlockCol[1];
		col2 = curBlockCol[2];
		col3 = curBlockCol[3];

		showBlock[row0][col0] = 0;
		showBlock[row1][col1] = 0;
		showBlock[row2][col2] = 0;
		showBlock[row3][col3] = 0;

		InvalidateBlockArea();

		curBlockRow[0] += 1;
		curBlockRow[1] += 1;
		curBlockRow[2] += 1;
		curBlockRow[3] += 1;

		showBlock[row0+1][col0] = 1;
		showBlock[row1+1][col1] = 1;
		showBlock[row2+1][col2] = 1;
		showBlock[row3+1][col3] = 1;

		InvalidateBlockArea();
	}
}

/**********************************************************
* Function: Move the block, three Direction: 
*		Left, Right or Accelerate down
*
* Last Modify Date: 2009-12-2
**********************************************************/
void CTETRISView::BlockMove(int m_iDirection)
{
	int row0,row1,row2,row3,col0,col1,col2,col3;
	row0 = curBlockRow[0];
	row1 = curBlockRow[1];
	row2 = curBlockRow[2];
	row3 = curBlockRow[3];
	col0 = curBlockCol[0];
	col1 = curBlockCol[1];
	col2 = curBlockCol[2];
	col3 = curBlockCol[3];
	
	switch(m_iDirection)
	{
	case LEFT:
		if( (curBlockCol[0]>0)&&(!LeftIsLimit())&&(!m_bFallToBottom) )
		{
			showBlock[row0][col0] = 0;
			showBlock[row1][col1] = 0;
			showBlock[row2][col2] = 0;
			showBlock[row3][col3] = 0;
			
			InvalidateBlockArea();
			
			curBlockCol[0] -= 1;
			curBlockCol[1] -= 1;
			curBlockCol[2] -= 1;
			curBlockCol[3] -= 1;
			showBlock[row0][col0-1] = 1;
			showBlock[row1][col1-1] = 1;
			showBlock[row2][col2-1] = 1;
			showBlock[row3][col3-1] = 1;
			
			InvalidateBlockArea();
		}
		break;

	case RIGHT:
		if( (curBlockCol[3]<m_iCol-1)&&(!RightIsLimit())&&(!m_bFallToBottom) )
		{
			showBlock[row0][col0] = 0;
			showBlock[row1][col1] = 0;
			showBlock[row2][col2] = 0;
			showBlock[row3][col3] = 0;
			
			InvalidateBlockArea();

			curBlockCol[0] += 1;
			curBlockCol[1] += 1;
			curBlockCol[2] += 1;
			curBlockCol[3] += 1;
			showBlock[row0][col0+1] = 1;
			showBlock[row1][col1+1] = 1;
			showBlock[row2][col2+1] = 1;
			showBlock[row3][col3+1] = 1;
			
			InvalidateBlockArea();
		}
		break;

	case DOWN:
		BlockMoveDown();
		break;

	default:
		break;
	}
}

/**********************************************************
* Function: Judging whether fall to the bottom or not
*
* Last Modify Date: 2009-12-2
**********************************************************/
void CTETRISView::FallToBottom()
{
	int row0,row1,row2,row3;
	int i;
	int index,nextRow,Col;
	row0 = curBlockRow[0];
	row1 = curBlockRow[1];
	row2 = curBlockRow[2];
	row3 = curBlockRow[3];

	// Fall to the bottom
	if(row0>=m_iRow-1||row1>=m_iRow-1||row2>=m_iRow-1||row3>=m_iRow-1)
		m_bFallToBottom = TRUE;
	else
	{
		for(i=0; i<4; i++)
		{
			// Fall on other block
			if(bottomInterface[m_iCurBlockType][i]>-1)
			{
				index = bottomInterface[m_iCurBlockType][i];
				nextRow = curBlockRow[index]+1;
				Col = curBlockCol[index];
				if(showBlock[nextRow][Col] == 1)
					m_bFallToBottom = TRUE;
			}
		}
	}

	BOOL m_bColFull;
	int j,k;
	int m_iDeleteLine = 0;
	
	if(m_bFallToBottom)
	{
		for(i=0; i<m_iRow; i++)
		{
			m_bColFull = TRUE;
			for(j=0; j<m_iCol; j++)
			{
				if(showBlock[i][j] == 0)
					m_bColFull = FALSE;
			}

			// Delete the line which is full of block 
			if(m_bColFull)
			{
				for(k=i; k>0; k--)
				{
					for(j=0; j<m_iCol; j++)
					{
						showBlock[k][j] = showBlock[k-1][j];
					}
				}
				for(j=0; j<m_iCol; j++)
				{
					showBlock[0][j] = 0;
				}
				m_iDeleteLine += 1;
			}
		}

		if(m_iDeleteLine>0)
		{
			if(m_iDeleteLine == 1)
				m_iScore += 100;
			else if(m_iDeleteLine == 2)
				m_iScore += 300;
			else if(m_iDeleteLine == 3)
				m_iScore += 600;
			else if(m_iDeleteLine == 4)
				m_iScore += 1000;

			// Refresh game area
			CRect rect1(10, 10, 10+10*m_iSize, 10+20*m_iSize);
			InvalidateRect(&rect1);

			// Refresh score area
			CRect rect2(10+320, 10+180, 10+400, 10+220);
			InvalidateRect(&rect2);
		}
	}
}

/****************************************************************************
* Function: Reaction when key down certain key on keyboards
*
* Last modify date: 2009-12-2
****************************************************************************/
void CTETRISView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case 'a':
	case 'A':
	case VK_LEFT:
		BlockMove(LEFT);
		break;
	case 'd':
	case 'D':
	case VK_RIGHT:
		BlockMove(RIGHT);
		break;
	case 'w':
	case 'W':
	case VK_UP:
		BlockChange();
		break;
	case 's':
	case 'S':
	case VK_DOWN:
		BlockMove(DOWN);
		break;
	default:
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

/****************************************************************************
* Function: Judge whether left move is limited, limited return TRUE, 
*	not limited return FALSE
*
* Last Modify Date: 2009-12-2
****************************************************************************/
BOOL CTETRISView::LeftIsLimit()
{
	int row0,row1,row2,row3,col0,col1,col2,col3;
	row0 = curBlockRow[0];
	row1 = curBlockRow[1];
	row2 = curBlockRow[2];
	row3 = curBlockRow[3];
	col0 = curBlockCol[0];
	col1 = curBlockCol[1];
	col2 = curBlockCol[2];
	col3 = curBlockCol[3];

	switch(m_iCurBlockType)
	{
	case 1:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1] ||
			showBlock[row2][col2-1] || showBlock[row3][col3-1])
			return TRUE;
		break;
	case 11:
		if(showBlock[row0][col0-1])
			return TRUE;
		break;

	case 2:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1])
			return TRUE;
		break;

	case 3:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1])
			return TRUE;
		break;
	case 31:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1] ||
			showBlock[row2][col2-1])
			return TRUE;
		break;
	case 32:
		if(showBlock[row0][col0-1] || showBlock[row2][col2-1] )
			return TRUE;
		break;
	case 33:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1] ||
			 showBlock[row3][col3-1])
			 return TRUE;
		break;

	case 4:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1] ||
			 showBlock[row3][col3-1])
			 return TRUE;
		break;
	case 41:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1])
			return TRUE;
		break;

	case 5:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1] ||
			 showBlock[row2][col2-1])
			 return TRUE;
		break;
	case 51:
		if(showBlock[row0][col0-1] || showBlock[row2][col2-1])
			return TRUE;
		break;

	case 6:
		if(showBlock[row0][col0-1] || showBlock[row2][col2-1] ||
			showBlock[row3][col3-1])
			return TRUE;
		break;
	case 61:
		if(showBlock[row0][col0-1] || showBlock[row2][col2-1])
			return TRUE;
		break;
	case 62:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1] ||
			 showBlock[row2][col2-1])
			 return TRUE;
		break;
	case 63:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1])
			return TRUE;
		break;

	case 7:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1] ||
			 showBlock[row2][col2-1])
			 return TRUE;
		break;
	case 71:
		if(showBlock[row0][col0-1] || showBlock[row3][col3-1])
			return TRUE;
		break;
	case 72:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1] ||
			 showBlock[row2][col2-1])
			 return TRUE;
		break;
	case 73:
		if(showBlock[row0][col0-1] || showBlock[row1][col1-1])
			 return TRUE;
		break;
		
	default:
		break;
	}

	return FALSE;
}

/****************************************************************************
* Function: Judge whether right move is limited, limited return TRUE, 
*	not limited return FALSE
*
* Last Modify Date: 2009-12-2
****************************************************************************/
BOOL CTETRISView::RightIsLimit()
{
	int row0,row1,row2,row3,col0,col1,col2,col3;
	row0 = curBlockRow[0];
	row1 = curBlockRow[1];
	row2 = curBlockRow[2];
	row3 = curBlockRow[3];
	col0 = curBlockCol[0];
	col1 = curBlockCol[1];
	col2 = curBlockCol[2];
	col3 = curBlockCol[3];

	switch(m_iCurBlockType)
	{
	case 1:
		if(showBlock[row0][col0+1] || showBlock[row1][col1+1] ||
			showBlock[row2][col2+1] || showBlock[row3][col3+1])
			return TRUE;
		break;
	case 11:
		if(showBlock[row3][col3 + 1])
			return TRUE;
		break;

	case 2:
		if(showBlock[row2][col2+1] || showBlock[row3][col3+1])
			return TRUE;
		break;

	case 3:
		if(showBlock[row1][col1+1] || showBlock[row3][col3+1])
			return TRUE;
		break;
	case 31:
		if(showBlock[row0][col0+1] || showBlock[row2][col2+1] ||
			showBlock[row3][col3+1])
			return TRUE;
		break;
	case 32:
		if(showBlock[row2][col2+1] || showBlock[row3][col3+1] )
			return TRUE;
		break;
	case 33:
		if(showBlock[row1][col1+1] || showBlock[row2][col2+1] ||
			 showBlock[row3][col3+1])
			 return TRUE;
		break;

	case 4:
		if(showBlock[row0][col0+1] || showBlock[row2][col2+1] ||
			 showBlock[row3][col3+1])
			 return TRUE;
		break;
	case 41:
		if(showBlock[row2][col2+1] || showBlock[row3][col3+1])
			return TRUE;
		break;

	case 5:
		if(showBlock[row1][col1+1] || showBlock[row2][col2+1] ||
			 showBlock[row3][col3+1])
			 return TRUE;
		break;
	case 51:
		if(showBlock[row1][col1+1] || showBlock[row3][col3+1])
			return TRUE;
		break;

	case 6:
		if(showBlock[row1][col1+1] || showBlock[row2][col2+1] ||
			showBlock[row3][col3+1])
			return TRUE;
		break;
	case 61:
		if(showBlock[row2][col2+1] || showBlock[row3][col3+1])
			return TRUE;
		break;
	case 62:
		if(showBlock[row0][col0+1] || showBlock[row1][col1+1] ||
			 showBlock[row3][col3+1])
			 return TRUE;
		break;
	case 63:
		if(showBlock[row1][col1+1] || showBlock[row3][col3+1])
			return TRUE;
		break;

	case 7:
		if(showBlock[row1][col1+1] || showBlock[row2][col2+1] ||
			 showBlock[row3][col3+1])
			 return TRUE;
		break;
	case 71:
		if(showBlock[row2][col2+1] || showBlock[row3][col3+1])
			return TRUE;
		break;
	case 72:
		if(showBlock[row1][col1+1] || showBlock[row2][col2+1] ||
			 showBlock[row3][col3+1])
			 return TRUE;
		break;
	case 73:
		if(showBlock[row0][col0+1] || showBlock[row3][col3+1])
			 return TRUE;
		break;
		
	default:
		break;
	}

	return FALSE;
}

/****************************************************************************
* Function: Clockwise change the block's shape  
*
* Last Modify Date: 2009-12-2
****************************************************************************/
void CTETRISView::BlockChange()
{
	int row0,row1,row2,row3,col0,col1,col2,col3;
	row0 = curBlockRow[0];
	row1 = curBlockRow[1];
	row2 = curBlockRow[2];
	row3 = curBlockRow[3];
	col0 = curBlockCol[0];
	col1 = curBlockCol[1];
	col2 = curBlockCol[2];
	col3 = curBlockCol[3];

	int newRow0,newRow1,newRow2,newRow3,newCol0,newCol1,newCol2,newCol3;
	newRow0 = row0;
	newRow1 = row1;
	newRow2 = row2;
	newRow3 = row3;
	newCol0 = col0;
	newCol1 = col1;
	newCol2 = col2;
	newCol3 = col3;

	int newBlock;
	switch(m_iCurBlockType)
	{
	case 1:
		newRow0 = row0 + 1; newCol0 = col0 - 1;
		newRow2 = row2 - 1; newCol2 = col2 + 1;
		newRow3 = row3 - 2; newCol3 = col3 + 2;
		newBlock = 11;
		break;
	case 11:
		newRow0 = row0 - 1; newCol0 = col0 + 1;
		newRow2 = row2 + 1; newCol2 = col2 - 1;
		newRow3 = row3 + 2; newCol3 = col3 - 2;
		newBlock = 1;
		break;

	case 2:
		newBlock = 2;
		break;

	case 3:
		newRow0 = row0 - 1; newCol0 = col0 + 1;
		newRow1 = row1 + 1;
		newRow2 = row2 + 1;
		newBlock = 31;
		break;
	case 31:
		newRow0 = row0 + 1; newCol0 = col0 - 1;
		newBlock = 32;
		break;
	case 32:
		newRow1 = row1 - 1; 
		newRow2 = row2 - 1;
		newRow3 = row3 + 1; newCol3 = col3 - 1;
		newBlock = 33;
		break;
	case 33:
		newRow3 = row3 - 1; newCol3 = col3 + 1;
		newBlock = 3;
		break;

	case 4:
		newRow0 = row0 + 2; newCol0 = col0 - 1;
		newRow2 = row2 + 1; newCol2 = col2 - 1;
		newRow3 = row3 - 1;
		newBlock = 41;
		break;
	case 41:
		newRow0 = row0 - 2; newCol0 = col0 + 1;
		newRow2 = row2 - 1; newCol2 = col2 + 1;
		newRow3 = row3 + 1;
		newBlock = 4;
		break;

	case 5:
		newCol0 = col0 - 1;
		newRow1 = row1 - 1;
		newRow2 = row2 + 2; newCol2 = col2 - 1;
		newRow3 = row3 + 1;
		newBlock = 51;
		break;
	case 51:
		                    newCol0 = col0 + 1;
		newRow1 = row1 + 1; 
		newRow2 = row2 - 2; newCol2 = col2 + 1;
		newRow3 = row3 - 1;
		newBlock = 5;
		break;

	case 6:
		newRow0 = row0 + 2; newCol0 = col0 - 1;
		newRow1 = row1 + 2; newCol1 = col1 - 1;
		newBlock = 61;
		break;
	case 61:
		newRow0 = row0 - 2; 
		newRow1 = row1 - 1; newCol1 = col1 - 1;
		newRow2 = row2 + 1; newCol2 = col2 - 2;
		                    newCol3 = col3 - 1;
		newBlock = 62;
		break;
	case 62:
		newRow2 = row2 - 2; newCol2 = col2 + 1;
		newRow3 = row3 - 2; newCol3 = col3 + 1;
		newBlock = 63;
		break;
	case 63:
		                    newCol0 = col0 + 1;
		newRow1 = row1 - 1; newCol1 = col1 + 2;
		newRow2 = row2 + 1; newCol2 = col2 + 1;
		newRow3 = row3 + 2;
		newBlock = 6;
		break;

	case 7:
		newRow1 = row1 - 1; newCol1 = col1 + 1;
		newRow2 = row2 - 2; newCol2 = col2 + 2;
		newRow3 = row3 + 1; newCol3 = col3 + 1;
		newBlock = 71;
		break;
	case 71:
		newRow0 = row0 + 2; newCol0 = col0 + 1;
						    newCol1 = col1 + 1;
		newRow2 = row2 + 1; 
	    newRow3 = row3 + 1;
		newBlock = 72;
		break;
	case 72:
		newRow0 = row0 - 1; newCol0 = col0 - 1;
		newRow1 = row1 + 2; newCol1 = col1 - 2;
		newRow2 = row2 + 1; newCol2 = col2 - 1;
		newBlock = 73;
		break;
	case 73:
		newRow0 = row0 - 1;
		newRow1 = row1 - 1; 
		                    newCol2 = col2 - 1;
		newRow3 = row3 - 2; newCol3 = col3 - 1;
		newBlock = 7;
		break;

	default:
		break;
	}

	showBlock[row0][col0] = 0;
	showBlock[row1][col1] = 0;
	showBlock[row2][col2] = 0;
	showBlock[row3][col3] = 0;
	if (showBlock[newRow0][newCol0]==0 && 
		showBlock[newRow1][newCol1]==0 && 
		showBlock[newRow2][newCol2]==0 && 
		showBlock[newRow3][newCol3]==0 && 
		newCol0>=0 && newCol3<=m_iCol-1 && 
		!(newRow0<0 || newRow1<0 || newRow2<0 || newRow3<0) && 
		!(newRow0>m_iRow-1 || newRow1>m_iRow-1 || newRow2>m_iRow-1 || newRow3>m_iRow-1) )
	{
		InvalidateBlockArea();

		curBlockRow[0]=newRow0;
		curBlockRow[1]=newRow1;
		curBlockRow[2]=newRow2;
		curBlockRow[3]=newRow3;
		curBlockCol[0]=newCol0;
		curBlockCol[1]=newCol1;
		curBlockCol[2]=newCol2;
		curBlockCol[3]=newCol3;

		showBlock[newRow0][newCol0] = 1;
		showBlock[newRow1][newCol1] = 1;
		showBlock[newRow2][newCol2] = 1;
		showBlock[newRow3][newCol3] = 1;

		InvalidateBlockArea();

		// Change current block's shape
		m_iCurBlockType = newBlock;
	}
	else
	{
		showBlock[row0][col0] = 1;
		showBlock[row1][col1] = 1;
		showBlock[row2][col2] = 1;
		showBlock[row3][col3] = 1;
	}

	// Judge whether fall to bottom or not 
	FallToBottom();
}

/****************************************************************************
* Funciton: Refresh block shape
*
* Last Modify Date: 2009-11-2
****************************************************************************/
void CTETRISView::InvalidateBlockArea()
{
	int i;
	for(i=0; i<4; i++)
	{
		CRect rect(10+curBlockCol[i]*m_iSize, 10+curBlockRow[i]*m_iSize,
			10+(curBlockCol[i]+1)*m_iSize, 10+(curBlockRow[i]+1)*m_iSize);
		InvalidateRect(&rect);
	}
}

void CTETRISView::PlayMid()
{
	HWND hWnd;
	hWnd = GetSafeHwnd();

	char inBuf[300], outBuf[300], fileName[255];
	MCIERROR mciError;

	strcpy(fileName, "Beethoven.mid");
	wsprintf(inBuf, "Open %s type sequencer alias myseq", fileName);
	mciError = mciSendString(inBuf, outBuf, sizeof(outBuf), NULL);
	if(mciError == 0)
	{
		mciError = mciSendString("play myseq notify", NULL, 0, hWnd);
		if(mciError != 0)
			mciSendString("close myseq", NULL, 0, NULL);
	}
}

void CTETRISView::StopMid()
{
	mciSendString("Close myseq", NULL, 0, NULL);
}

/****************************************************************************
* Function: Start the Game
*
* Last Modify Date: 2009-12-2
****************************************************************************/
void CTETRISView::OnGameStart() 
{
	// TODO: Add your command handler code here

	if(!m_bGamePause)
	{
		m_bGameEnd = FALSE;
		m_iScore = 0;

		CRect rect(10, 10, 10+440, 10+370);
		InvalidateRect(&rect);
	}
	m_bGamePause = FALSE;
	m_bGameEnd = FALSE;

	// Set the block's falling speed, corresponding to Ontimer Function
	SetTimer(1000, 1500-m_iLevel*250, NULL);
}

void CTETRISView::OnUpdateGameStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bGameEnd || m_bGamePause)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

/**********************************************************
* Function: Pause the game
*
* Date: 2010-1-18
**********************************************************/
void CTETRISView::OnGamePause() 
{
	// TODO: Add your command handler code here
	m_bGamePause = TRUE;
	KillTimer(1);
}

void CTETRISView::OnUpdateGamePause(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(!m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTETRISView::OnGameEnd() 
{
	// TODO: Add your command handler code here
	m_bGameEnd = TRUE;

	int i,j;
	for(i=0; i<m_iRow; i++)
	{
		for(j=0; j<m_iCol; j++)
		{
			showBlock[i][j] = 0;
		}
	}

	CRect rect(10, 10, 10+10*m_iSize, 10+20*m_iSize);
	InvalidateRect(&rect);

	m_bGamePause = FALSE;

	KillTimer(1);
}

void CTETRISView::OnUpdateGameEnd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(!m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTETRISView::OnGameSetting() 
{
	// TODO: Add your command handler code here
	CGameSetting dlg(m_iLevel, m_bPlayMusic, m_bDrawGrid);
	dlg.DoModal();
	m_iLevel = dlg.m_iLevel;
	m_bDrawGrid = dlg.m_bDrawGrid;
	m_bPlayMusic = dlg.m_bPlayMusic;
	if(m_bPlayMusic)
		PlayMid();
	else
		StopMid();

	Invalidate();
}

void CTETRISView::OnUpdateGameSetting(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CTETRISView::OnGameLevel1() 
{
	// TODO: Add your command handler code here
	m_iLevel = 1;
}

void CTETRISView::OnUpdateGameLevel1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);

	if(m_iLevel == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CTETRISView::OnGameLevel2() 
{
	// TODO: Add your command handler code here
	m_iLevel = 2;	
}

void CTETRISView::OnUpdateGameLevel2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);

	if(m_iLevel == 2)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CTETRISView::OnGameLevel3() 
{
	// TODO: Add your command handler code here
	m_iLevel = 3;	
}

void CTETRISView::OnUpdateGameLevel3(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);

	if(m_iLevel == 3)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CTETRISView::OnGameLevel4() 
{
	// TODO: Add your command handler code here
	m_iLevel = 4;	
}

void CTETRISView::OnUpdateGameLevel4(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);

	if(m_iLevel == 4)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CTETRISView::OnGameLevel5() 
{
	// TODO: Add your command handler code here
	m_iLevel = 5;	
}

void CTETRISView::OnUpdateGameLevel5(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);

	if(m_iLevel == 5)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

void CTETRISView::OnShowGrid() 
{
	// TODO: Add your command handler code here
	if (m_bDrawGrid)
		m_bDrawGrid = FALSE;
	else
		m_bDrawGrid = TRUE;

	Invalidate();
}

void CTETRISView::OnUpdateShowGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bGameEnd)
		pCmdUI -> Enable(TRUE);
	else
		pCmdUI -> Enable(FALSE);

	if (m_bDrawGrid)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);	
}

void CTETRISView::OnPlayMusic() 
{
	// TODO: Add your command handler code here
	if (m_bPlayMusic)
	{
		m_bPlayMusic = FALSE;
		StopMid();
	}
	else
	{
		m_bPlayMusic = TRUE;
		PlayMid();
	}
}

void CTETRISView::OnUpdatePlayMusic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bGameEnd)
		pCmdUI -> Enable(TRUE);
	else
		pCmdUI -> Enable(FALSE);

	if (m_bPlayMusic)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);	
}

void CTETRISView::OnAboutGamerule() 
{
	// TODO: Add your command handler code here
	WinExec("notepad.exe GameRule", SW_SHOW);	
}

void CTETRISView::OnUpdateAboutGamerule(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bGameEnd)
		pCmdUI -> Enable(TRUE);
	else
		pCmdUI -> Enable(FALSE);
}
