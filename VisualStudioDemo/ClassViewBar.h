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
// ClassViewBar1.h: interface for the CClassViewBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSVIEWBAR1_H__FFAF44CB_B481_4420_8FDF_AF44ABE73D6C__INCLUDED_)
#define AFX_CLASSVIEWBAR1_H__FFAF44CB_B481_4420_8FDF_AF44ABE73D6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClassTreeWnd.h"

class CClassToolBar : public CBCGPToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)	
	{		
		CBCGPToolBar::OnUpdateCmdUI ((CFrameWnd*) GetOwner (), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList () const		{	return FALSE;	}
};

class CClassViewBar : public CBCGPDockingControlBar  
{
	DECLARE_DYNAMIC(CClassViewBar)

public:
	CClassViewBar();
	virtual ~CClassViewBar();

	void AdjustLayout ();
	void OnChangeVisualStyle ();
	void FillClassMembers(HTREEITEM hItem);

protected:
	CBCGPSplitterWnd	m_wndSplitter;
	CClassToolBar		m_wndToolBar;
	CClassTreeWnd		m_wndClassView;
	CClassTreeWnd		m_wndMembers;
	CImageList			m_ClassViewImages;

	UINT				m_nCurrSort;

	void FillClassView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClassViewBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	//}}AFX_VIRTUAL

	virtual void GetPaneInfo(CString& strName, CString& strInfo, HICON& hIcon, BOOL& bAutoDestroyIcon)
	{
		CBCGPDockingControlBar::GetPaneInfo(strName, strInfo, hIcon, bAutoDestroyIcon);
		strInfo = _T("Contains list of solution classes.");
		
		if (hIcon == NULL)
		{
			// Current Visual theme doesn't have docking pane icons:
			int nImage = BCGPGetCmdMgr()->GetCmdImage(ID_VIEW_CLASS, FALSE);
			if (nImage >= 0)
			{
				hIcon = CBCGPToolBar::GetImages()->ExtractIcon(nImage);
				bAutoDestroyIcon = TRUE;
			}
		}
	}

	// Generated message map functions
protected:
	//{{AFX_MSG(CClassViewBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClassAddMemeberFunction();
	afx_msg void OnClassAddMemeberVariable();
	afx_msg void OnClassDefinition();
	afx_msg void OnClassProperties();
	afx_msg void OnNewFolder();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	afx_msg LRESULT OnChangeActiveTab (WPARAM, LPARAM);
	afx_msg void OnSort (UINT id);
	afx_msg void OnUpdateSort (CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_CLASSVIEWBAR1_H__FFAF44CB_B481_4420_8FDF_AF44ABE73D6C__INCLUDED_)
