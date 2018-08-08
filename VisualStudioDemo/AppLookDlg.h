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
#if !defined(AFX_APPLOOKDLG_H__5B2B5394_3611_49AE_B2B6_F84D14BC5189__INCLUDED_)
#define AFX_APPLOOKDLG_H__5B2B5394_3611_49AE_B2B6_F84D14BC5189__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppLookDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppLookDlg dialog

class CAppLookDlg : public CBCGPDialog
{
// Construction
public:
	CAppLookDlg(BOOL bStartup, CWnd* pParent = NULL);   // standard constructor

	CBCGPPropList m_wndPropList;

// Dialog Data
	//{{AFX_DATA(CAppLookDlg)
	enum { IDD = IDD_APP_LOOK };
	CStatic	m_wndPropListPlaceHolder;
	BOOL	m_bShowAtStartup;
	//}}AFX_DATA

	enum PropID
	{
		AppLook,
		Style,
		AccentColor,
		VS2012GrayIcons,
		OneNoteMDITabs,
		DockingTabColors,
		VS2005RoundedTabs,
		ExtendedToolTips,
		MaximizeFloatingPanes,
		DblClickMaximizeFloatingPanes,
		ShowHiddenPanesOnMouseClick,
		AutoHideAnimation,
		MultipleSelTabs,
		AppState,
	};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppLookDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAppLookDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	afx_msg LRESULT OnPropertyChanged (WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()

	int m_nAppLook;
	int m_nOffice2007Style;
	int	m_nOffice2010Style;
	int m_nOffice2013Style;
	int m_nOffice2016Style;
	int	m_nVS2012Style;
	int m_nAccentColor;
	BOOL m_bVS2012GrayIcons;
	BOOL m_bDockTabColors;
	BOOL m_bOneNoteTabs;
	BOOL m_bMultipleSelTabs;
	BOOL m_bRoundedTabs;
	BOOL m_bCustomTooltips;
	BOOL m_bMaximizeFloatingPanes;
	BOOL m_bDblClickMaximizeFloatingPanes;
	BOOL m_bShowHiddenPanesOnMouseClick;
	BOOL m_bAutoHideAnimation;
	BOOL m_bShowAppState;

	const BOOL	m_bStartup;
	CBCGPProp*	m_pStyleProp;

	void OnAppLook();
	void SetLook ();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLOOKDLG_H__5B2B5394_3611_49AE_B2B6_F84D14BC5189__INCLUDED_)
