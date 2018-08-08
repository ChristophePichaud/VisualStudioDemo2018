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
// WatchBar.cpp : implementation file
//

#include "stdafx.h"
#include "VisualStudioDemo.h"
#include "WatchBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_LIST_1	1

/////////////////////////////////////////////////////////////////////////////
// CWatchBar

CWatchBar::CWatchBar()
{
}

CWatchBar::~CWatchBar()
{
}


BEGIN_MESSAGE_MAP(CWatchBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CWatchBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWatchBar message handlers

int CWatchBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_Font.CreateStockObject(DEFAULT_GUI_FONT);

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create output pane:
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT;

	m_wndWatch.m_bVisualManagerStyle = TRUE;

	m_wndWatch.Create (dwStyle, rectDummy, this, ID_LIST_1);
	m_wndWatch.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_wndWatch.InsertColumn (0, _T("Variable"), LVCFMT_LEFT, 100);
	m_wndWatch.InsertColumn (1, _T("Value"), LVCFMT_LEFT, 100);

	m_wndWatch.InsertItem (0, _T("m_nCount"));
	m_wndWatch.SetItemText (0, 1, _T("100"));

	m_wndWatch.InsertItem (1, _T("strName"));
	m_wndWatch.SetItemText (1, 1, _T("\"John\""));

	m_wndWatch.SetFont (&m_Font);
	return 0;
}

void CWatchBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (CanAdjustLayout ())
	{
		m_wndWatch.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);
	}
}

void CWatchBar::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
	m_wndWatch.SetFocus ();
}
