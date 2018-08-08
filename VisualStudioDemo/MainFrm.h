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
// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1E4CD94D_CB6E_4FAD_9DDE_3E2B96D11CE2__INCLUDED_)
#define AFX_MAINFRM_H__1E4CD94D_CB6E_4FAD_9DDE_3E2B96D11CE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WatchBar.h"
#include "FileViewBar.h"
#include "OutputView.h"
#include "DockableStartPage.h"
#include "FileManager.h"

class CMainFrame : public CBCGPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)

public:
	CMainFrame();

// Attributes
public:
	BOOL IsShowApplicationState() const
	{
		return m_bShowAppState;
	}

// Operations
public:
	void OnChangeLook (BOOL bOneNoteTabs, BOOL bMDITabColors, BOOL bIsVSDotNetLook, 
		BOOL bDockTabColors, BOOL bMDITabsVS2005Look,
		CBCGPTabWnd::TabCloseButtonMode mdiTabCloseButtonMode, BOOL bDocumentMenu, BOOL bMDIActiveTabBoldFont,
		BOOL bMaximizeFloatingPanes, BOOL bDblClickMaximizeFloatingPanes, BOOL bShowHiddenPanesOnMouseClick,
		BOOL bAutoHideAnimation, BOOL bMultipleSelTabs, BOOL bShowAppState);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

	virtual CBCGPMDIChildWnd* CreateDocumentWindow (LPCTSTR lpcszDocName, CObject* pObj);
	virtual BOOL OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop);

// Implementation
public:
	static CBCGPToolbarComboBoxButton* GetFindCombo();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void ShowStartPage (BOOL bConvertToTabbed = FALSE);

public:
	std::shared_ptr<CFileManager> m_pManager;
	std::shared_ptr<CFileManager> GetManager() const
	{
		return m_pManager;
	}
	void SetManager(std::shared_ptr<CFileManager> pManager);
	void UpdateSolution(std::shared_ptr<CCodeFile> cf);
	void UpdateSolution(std::shared_ptr<CAssemblyFile> cf);
	void CloseAllDocuments();

public:
	CFileViewBar			m_wndFileView;
	COutputViewBar			m_wndOutputView;

protected:  // control bar embedded members
	CBCGPMenuBar			m_wndMenuBar;
	CBCGPStatusBar			m_wndStatusBar;
	CBCGPToolBar			m_wndToolBar;
	CBCGPToolBar			m_wndToolbarBuild;
	CBCGPToolBar			m_wndToolbarEdit;

	CDockableStartPage		m_wndStartPage;

	CWatchBar				m_wndWatchBar;

	CBCGPToolBarImages		m_UserImages;

	BOOL					m_bShowAppState;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHelpKeyboardmap();
	afx_msg void OnFileNewProject();
	afx_msg void OnFileNewBlankSolution();
	afx_msg void OnFileOpenSolution();
	afx_msg void OnFileCloseSolution();
	afx_msg void OnFileSaveAll();
	afx_msg void OnViewRefresh();
	afx_msg void OnToolsConnectToDatabase();
	afx_msg void OnToolsDebugProcesses();
	afx_msg void OnViewFullScreen();
	afx_msg void OnToolsOptions();
	afx_msg void OnHelpWeb();
	afx_msg void OnMdiMoveToNextGroup();
	afx_msg void OnMdiMoveToPrevGroup();
	afx_msg void OnMdiNewHorzTabGroup();
	afx_msg void OnMdiNewVertGroup();
	afx_msg void OnMdiCancel();
	afx_msg void OnClose();
	afx_msg void OnViewClass();
	afx_msg void OnUpdateViewClass(CCmdUI* pCmdUI);
	afx_msg void OnViewFile();
	afx_msg void OnUpdateViewFile(CCmdUI* pCmdUI);
	afx_msg void OnViewResource();
	afx_msg void OnUpdateViewResource(CCmdUI* pCmdUI);
	afx_msg void OnViewProperties();
	afx_msg void OnUpdateViewProperties(CCmdUI* pCmdUI);
	afx_msg void OnViewOutput();
	afx_msg void OnUpdateViewOutput(CCmdUI* pCmdUI);
	afx_msg void OnViewWatch();
	afx_msg void OnUpdateViewWatch(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbox();
	afx_msg void OnUpdateViewToolbox(CCmdUI* pCmdUI);
	afx_msg void OnMdiTabbedDocument();
	afx_msg void OnUpdateMdiTabbedDocument(CCmdUI* pCmdUI);
	afx_msg void OnHelpShowStart();
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnReseWindowsLayout();
	//}}AFX_MSG
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg LRESULT OnGetTabToolTip(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnHelpCustomizeToolbars(WPARAM wp, LPARAM lp);
	afx_msg void OnToolBox();
	afx_msg void OnUpdateCaretPos(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingBars ();
	void SetDockingBarsIcons (BOOL bHiColorIcons);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1E4CD94D_CB6E_4FAD_9DDE_3E2B96D11CE2__INCLUDED_)
