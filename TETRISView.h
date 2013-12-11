// TETRISView.h : interface of the CTETRISView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRISVIEW_H__6103B782_3999_4712_AAE2_A0890280581C__INCLUDED_)
#define AFX_TETRISVIEW_H__6103B782_3999_4712_AAE2_A0890280581C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//Macro define
#define WHITE RGB(255,255,255)
#define BLACK RGB(0,0,0)
#define BLUE RGB(0,0,255)

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

class CTETRISView : public CView
{
protected: // create from serialization only
	CTETRISView();
	DECLARE_DYNCREATE(CTETRISView)

// Attributes
public:
	CTETRISDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTETRISView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTETRISView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CBrush	*screenBrush;
	CBrush	*gameAreaBrush;
	CBrush	*blockBrush;
	CPen	*gridLinePen;
	CPen	*whitePen;

	int m_iRow;			// Total rows of grid
	int m_iCol;			// Total columns of grid
	int m_iSize;		// Length or width of each square in grid
	int m_iLevel;
	int bottomInterface[74][4];
	int m_iScore; // Totle score from game
	int curBlockRow[4];
	int curBlockCol[4];
	int nextBlockRow[4];
	int nextBlockCol[4];
	int m_iNextBlockType;
	int m_iCurBlockType;
	int blockColor;

	BOOL m_bDrawGrid;	// Whether draw grid or not: 1-draw, 0-not draw
	BOOL m_bPlayMusic;	// Whether play music or not;
	BOOL m_bGameStart;
	BOOL m_bGamePause;
	BOOL m_bGameEnd;
	BOOL showBlock[20][10]; // 1-show block, 0-hide block
	BOOL m_bFallToBottom;

	void SetBlockStatus();
	void CurrentBlockStatus(int m_iType);
	void NextBlockStatus(int m_iType);

	void BlockMove(int m_iDirection);
	void BlockMoveDown();
	void BlockChange();

	int  Random(int MaxNumber);
	void InvalidateBlockArea();

	void FallToBottom();
	BOOL LeftIsLimit();
	BOOL RightIsLimit();

	void PlayMid();
	void StopMid();

// Generated message map functions
protected:
	//{{AFX_MSG(CTETRISView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGameStart();
	afx_msg void OnUpdateGameStart(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGamePause();
	afx_msg void OnUpdateGamePause(CCmdUI* pCmdUI);
	afx_msg void OnGameEnd();
	afx_msg void OnUpdateGameEnd(CCmdUI* pCmdUI);
	afx_msg void OnGameSetting();
	afx_msg void OnUpdateGameSetting(CCmdUI* pCmdUI);
	afx_msg void OnGameLevel1();
	afx_msg void OnUpdateGameLevel1(CCmdUI* pCmdUI);
	afx_msg void OnGameLevel2();
	afx_msg void OnUpdateGameLevel2(CCmdUI* pCmdUI);
	afx_msg void OnGameLevel3();
	afx_msg void OnUpdateGameLevel3(CCmdUI* pCmdUI);
	afx_msg void OnGameLevel4();
	afx_msg void OnUpdateGameLevel4(CCmdUI* pCmdUI);
	afx_msg void OnGameLevel5();
	afx_msg void OnUpdateGameLevel5(CCmdUI* pCmdUI);
	afx_msg void OnShowGrid();
	afx_msg void OnUpdateShowGrid(CCmdUI* pCmdUI);
	afx_msg void OnPlayMusic();
	afx_msg void OnUpdatePlayMusic(CCmdUI* pCmdUI);
	afx_msg void OnAboutGamerule();
	afx_msg void OnUpdateAboutGamerule(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TETRISView.cpp
inline CTETRISDoc* CTETRISView::GetDocument()
   { return (CTETRISDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRISVIEW_H__6103B782_3999_4712_AAE2_A0890280581C__INCLUDED_)
