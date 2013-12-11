// GameSetting.cpp : implementation file
//

#include "stdafx.h"
#include "TETRIS.h"
#include "GameSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameSetting dialog


CGameSetting::CGameSetting(int m_iGameLevel, BOOL m_bPlayMusic, BOOL m_bDrawGrid, CWnd* pParent /*=NULL*/)
	: CDialog(CGameSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGameSetting)
	m_bDrawGrid = FALSE;
	m_bPlayMusic = FALSE;
	//}}AFX_DATA_INIT
	m_lastLevel = m_iGameLevel;
	m_lastMusic = m_bPlayMusic;
	m_lastGrid = m_bDrawGrid;

}


void CGameSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameSetting)
	DDX_Check(pDX, IDC_CHECK_GRID, m_bDrawGrid);
	DDX_Check(pDX, IDC_CHECK_MUSIC, m_bPlayMusic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGameSetting, CDialog)
	//{{AFX_MSG_MAP(CGameSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameSetting message handlers

BOOL CGameSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CComboBox *m_comboLevel;
	CButton   *m_btnDrawGrid;
	CButton   *m_btnMusic;

	m_comboLevel = (CComboBox *)GetDlgItem(IDC_COMBO_GAMELEVEL);
	m_comboLevel -> SetCurSel(m_lastLevel);

	m_btnDrawGrid = (CButton *)GetDlgItem(IDC_CHECK_GRID);
	m_btnDrawGrid -> SetCheck(m_lastGrid);

	m_btnMusic = (CButton *)GetDlgItem(IDC_CHECK_MUSIC);
	m_btnMusic -> SetCheck(m_lastMusic);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGameSetting::OnOK() 
{
	// TODO: Add extra validation here
	CComboBox *m_comboLevel;
	m_comboLevel = (CComboBox *)GetDlgItem(IDC_COMBO_GAMELEVEL);

	m_iLevel = m_comboLevel->GetCurSel();
	if(m_iLevel<1 || m_iLevel>5)
		m_iLevel = 3;

	CDialog::OnOK();
}
