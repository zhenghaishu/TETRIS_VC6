// TETRISDoc.h : interface of the CTETRISDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRISDOC_H__D8BD6E8C_902D_4A42_9013_9D6DD73D4A06__INCLUDED_)
#define AFX_TETRISDOC_H__D8BD6E8C_902D_4A42_9013_9D6DD73D4A06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTETRISDoc : public CDocument
{
protected: // create from serialization only
	CTETRISDoc();
	DECLARE_DYNCREATE(CTETRISDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTETRISDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTETRISDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTETRISDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRISDOC_H__D8BD6E8C_902D_4A42_9013_9D6DD73D4A06__INCLUDED_)
