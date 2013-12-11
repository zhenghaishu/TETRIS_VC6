#if !defined(AFX_GAMESETTING_H__57F5C5D7_46E8_4B25_82A6_2B89D817B4D2__INCLUDED_)
#define AFX_GAMESETTING_H__57F5C5D7_46E8_4B25_82A6_2B89D817B4D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGameSetting dialog

class CGameSetting : public CDialog
{
// Construction
public:
	CGameSetting(int m_iGameLevel, BOOL m_bPlayMusic, BOOL m_bDrawGrid, CWnd* pParent = NULL);   // standard constructor
	int  m_iLevel;
// Dialog Data
	//{{AFX_DATA(CGameSetting)
	enum { IDD = IDD_GAME_SETTING };
	BOOL	m_bDrawGrid;
	BOOL	m_bPlayMusic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	int  m_lastLevel;
	BOOL m_lastMusic;
	BOOL m_lastGrid;

	// Generated message map functions
	//{{AFX_MSG(CGameSetting)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMESETTING_H__57F5C5D7_46E8_4B25_82A6_2B89D817B4D2__INCLUDED_)
