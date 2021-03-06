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
// OutputView.cpp: implementation of the CResourceViewBar class.
//

#include "stdafx.h"
#include "VisualStudioDemo.h"
#include "MainFrm.h"
#include "OutputView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputViewBar::COutputViewBar()
{
}

COutputViewBar::~COutputViewBar()
{
}

BEGIN_MESSAGE_MAP(COutputViewBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(COutputViewBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int COutputViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectClient (0, 0, lpCreateStruct->cx, lpCreateStruct->cy);

	// Create output pane:
	const DWORD dwStyle = WS_CLIPSIBLINGS | LBS_NOINTEGRALHEIGHT | LBS_NOSEL | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS;

	m_wndOutput.m_bVisualManagerStyle = TRUE;

	if (!m_wndOutput.Create (dwStyle, rectClient, this, 1))
	{
		TRACE0("Failed to create output window\n");
		return -1;      // fail to create
	}

	UpdateFonts();

	// Fill view context (dummy code, don't seek here something magic :-)):
	FillDebugWindow ();
	return 0;
}

void COutputViewBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (CanAdjustLayout())
	{
		m_wndOutput.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);
	}

	AdjusrHorzScroll (m_wndOutput);
}

void COutputViewBar::AdjusrHorzScroll (CListBox& wndListBox)
{
	CClientDC dc (this);
	CFont* pOldFont = dc.SelectObject (&globalData.fontRegular);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount (); i ++)
	{
		CString strItem;
		wndListBox.GetText (i, strItem);

		cxExtentMax = max (cxExtentMax, dc.GetTextExtent (strItem).cx);
	}
	
	wndListBox.SetHorizontalExtent (cxExtentMax);
	dc.SelectObject (pOldFont);
}

void COutputViewBar::FillDebugWindow ()
{
	m_wndOutput.AddString (_T("The program has started successfully."));
	m_wndOutput.AddString (_T("Enjoy using it!"));
}

/////////////////////////////////////////////////////////////////////////////
// COutputList1

COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}


BEGIN_MESSAGE_MAP(COutputList, CBCGPListBox)
	//{{AFX_MSG_MAP(COutputList)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_OUTPUT_GOTO_ERROR, OnOutputGotoError)
	ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList message handlers

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point) 
{
	if (CBCGPPopupMenu::GetSafeActivePopupMenu() != NULL)
	{
		return;
	}
	
   CMenu menu;
   menu.LoadMenu(IDR_POPUP_OUTPUT);

   CMenu* pSumMenu = menu.GetSubMenu(0);

   if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CBCGPMDIFrameWnd)))
   {
	   CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;

	   if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
         return;

      ((CBCGPMDIFrameWnd*)AfxGetMainWnd())->OnShowPopupMenu (pPopupMenu);
      UpdateDialogControls(this, FALSE);
   }

   SetFocus ();
}

void COutputList::OnEditCopy() 
{
	BCGPMessageBox (_T("Copy output"));
}

void COutputList::OnEditClear() 
{
	BCGPMessageBox (_T("Clear output"));
}

void COutputList::OnOutputGotoError() 
{
	// TODO: Add your command handler code here
	
}

void COutputList::OnViewOutput() 
{
	CBCGPDockingControlBar* pParentBar = DYNAMIC_DOWNCAST (CBCGPDockingControlBar, GetOwner ());
	CBCGPMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CBCGPMDIFrameWnd, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus ();
		pMainFrame->ShowControlBar (pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout ();

	}
}

void COutputViewBar::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
	m_wndOutput.SetFocus ();
}

void COutputViewBar::UpdateFonts()
{
	m_wndOutput.SetFont (&globalData.fontRegular);
}

void COutputViewBar::AddString(CString strMessage)
{
	m_wndOutput.AddString(strMessage);
}

void COutputViewBar::ClearBuildWindow()
{
	m_wndOutput.ResetContent();
}
