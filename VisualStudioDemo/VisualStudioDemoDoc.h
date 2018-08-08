//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2018 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BCGPVisualStudioGUIDemoDoc.h : interface of the CBCGPVisualStudioGUIDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGCBDOTNETEXAMPLEDOC_H__1260A711_4153_43F3_ADAF_952FAD30AC46__INCLUDED_)
#define AFX_BCGCBDOTNETEXAMPLEDOC_H__1260A711_4153_43F3_ADAF_952FAD30AC46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileManager.h"

class CBCGPVisualStudioGUIDemoDoc : public CDocument
{
protected: // create from serialization only
	CBCGPVisualStudioGUIDemoDoc();
	DECLARE_DYNCREATE(CBCGPVisualStudioGUIDemoDoc)

// Attributes
public:
	UINT	m_uiExampleID;
	UINT	m_uiExampleXMLSettingsID;

	std::shared_ptr<CFileManager> GetManager() const
	{
		CBCGPVisualStudioGUIDemoApp * pApp = (CBCGPVisualStudioGUIDemoApp *)AfxGetApp();
		return pApp->GetManager();
	}

	// Operations
public:
	COLORREF GetStateColor() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPVisualStudioGUIDemoDoc)
	virtual void Serialize(CArchive& ar);
	virtual void SetTitle(LPCTSTR lpszTitle);
	BOOL OnNewDocumentWithName();
	void OnNewEmptyDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL
	
// Implementation
public:
	void CheckTitle();

	virtual ~CBCGPVisualStudioGUIDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL	m_bTitleMark;

	void CommonInit ();

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPVisualStudioGUIDemoDoc)
	afx_msg void OnDummyBuild();
	afx_msg void OnDummyCompile();
	afx_msg void OnDummyExecute();
	afx_msg void OnDummyGo();
	afx_msg void OnDummySelectActiveConfiguration();
	afx_msg void OnDummyClean();
	afx_msg void OnDummyRebuildAll();
	afx_msg void OnToolsMacro();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGCBDOTNETEXAMPLEDOC_H__1260A711_4153_43F3_ADAF_952FAD30AC46__INCLUDED_)
