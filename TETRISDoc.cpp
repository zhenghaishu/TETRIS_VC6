// TETRISDoc.cpp : implementation of the CTETRISDoc class
//

#include "stdafx.h"
#include "TETRIS.h"

#include "TETRISDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTETRISDoc

IMPLEMENT_DYNCREATE(CTETRISDoc, CDocument)

BEGIN_MESSAGE_MAP(CTETRISDoc, CDocument)
	//{{AFX_MSG_MAP(CTETRISDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTETRISDoc construction/destruction

CTETRISDoc::CTETRISDoc()
{
	// TODO: add one-time construction code here

}

CTETRISDoc::~CTETRISDoc()
{
}

BOOL CTETRISDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTETRISDoc serialization

void CTETRISDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTETRISDoc diagnostics

#ifdef _DEBUG
void CTETRISDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTETRISDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTETRISDoc commands
