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
// BCGPVisualStudioGUIDemo.h : main header file for the BCGPVisualStudioGUIDemo application
//

#if !defined(AFX_BCGCBDOTNETEXAMPLE_H__AEAC1B76_E65E_4075_9A38_537CC10CEC1F__INCLUDED_)
#define AFX_BCGCBDOTNETEXAMPLE_H__AEAC1B76_E65E_4075_9A38_537CC10CEC1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "FileManager.h"
/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoApp:
// See BCGPVisualStudioGUIDemo.cpp for the implementation of this class
//

class CBCGPVisualStudioGUIDemoApp : public CBCGPWinApp
{
public:
	CBCGPVisualStudioGUIDemoApp();
	virtual ~CBCGPVisualStudioGUIDemoApp();

	BOOL	m_bHiColorIcons;
	BOOL	m_b2012Icons;
	BOOL	m_bExplorerThemeTrees;
	BOOL	m_bDockingPaneIcons;
	
	CMultiDocTemplate*		m_pDocTemplateCpp;

// Overrides
	virtual void PreLoadState();
	virtual void OnBeforeChangeVisualTheme(CBCGPAppOptions& appOptions, CWnd* pMainWnd);
	virtual void OnAfterChangeVisualTheme(CWnd* pMainWnd);

public:
	std::shared_ptr<CFileManager> m_pManager;
	std::shared_ptr<CFileManager> GetManager()
	{
		return m_pManager;
	}

public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPVisualStudioGUIDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL SaveAllModified();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPVisualStudioGUIDemoApp)
	afx_msg void OnAppAbout();
	afx_msg void OnViewAppLook();
	afx_msg void OnMdiTabsFileClose();
	afx_msg void OnUpdateMdiTabsFileClose(CCmdUI* pCmdUI);
	afx_msg void OnWindowCloseAll();
	afx_msg void OnWindowManager();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileNewEmpty();
	afx_msg void OnFileNew();
};


extern CBCGPVisualStudioGUIDemoApp theApp;


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGCBDOTNETEXAMPLE_H__AEAC1B76_E65E_4075_9A38_537CC10CEC1F__INCLUDED_)
