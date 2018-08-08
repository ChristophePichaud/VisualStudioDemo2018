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
// DockableStartPage.h: interface for the CDockableStartPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCKABLESTARTPAGE_H__01E78BD5_3362_48F3_8F95_5A8F692B1DA4__INCLUDED_)
#define AFX_DOCKABLESTARTPAGE_H__01E78BD5_3362_48F3_8F95_5A8F692B1DA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStartView;

class CDockableStartPage  : public CBCGPDockingControlBar
{
	friend class CMainFrame;

public:
	CDockableStartPage();
	virtual ~CDockableStartPage();

// Attributes
protected:
	CStartView*		m_pStartView;
	CCreateContext* m_pContext;

// Operations
public:
	void SetContext (CCreateContext* pContext)
	{
		m_pContext = pContext;
	}
	
// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual void GetPaneInfo(CString& strName, CString& strInfo, HICON& hIcon, BOOL& bAutoDestroyIcon)
	{
		CBCGPDockingControlBar::GetPaneInfo(strName, strInfo, hIcon, bAutoDestroyIcon);
		strInfo = _T("Create new file, change visual theme and more.");
		
		if (hIcon == NULL)
		{
			// Current Visual theme doesn't have docking pane icons:
		}
	}

	virtual CBCGPMDIChildWnd* OnNewMDITabbedChildWnd(CBCGPMDIFrameWnd* pMainFrame) const;
};

#endif // !defined(AFX_DOCKABLESTARTPAGE_H__01E78BD5_3362_48F3_8F95_5A8F692B1DA4__INCLUDED_)
