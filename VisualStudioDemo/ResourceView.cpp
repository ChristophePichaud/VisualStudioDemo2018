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
// ResourceView.cpp: implementation of the CResourceViewBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "MainFrm.h"
#include "ResourceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CResourceViewBar::CResourceViewBar()
{
}

CResourceViewBar::~CResourceViewBar()
{
}


BEGIN_MESSAGE_MAP(CResourceViewBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CResourceViewBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

int CResourceViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create view:
	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;
	
	m_wndResourceView.m_bVisualManagerStyle = TRUE;

	if (!m_wndResourceView.Create (dwViewStyle, rectDummy, this, 3))
	{
		TRACE0("Failed to create workspace view\n");
		return -1;      // fail to create
	}

	// Load view images:
	m_ResourceViewImages.Create (IDB_RESOURCE_VIEW, 16, 0, RGB (255, 0, 255));
	m_wndResourceView.SetImageList (&m_ResourceViewImages, TVSIL_NORMAL);

	// Fill view context (dummy code, don't seek here something magic :-)):
	FillResourceView ();

	OnChangeVisualStyle ();
	return 0;
}

void CResourceViewBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (CanAdjustLayout())
	{
		m_wndResourceView.SetWindowPos (NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);
	}
}

void CResourceViewBar::FillResourceView ()
{
	HTREEITEM hRoot = m_wndResourceView.InsertItem (_T("MyApp resources"), 0, 0);
	m_wndResourceView.SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hFolder = m_wndResourceView.InsertItem (_T("Accelerator"), 0, 0, hRoot);
	m_wndResourceView.InsertItem (_T("IDR_MAINFRAME"), 1, 1, hFolder);

	m_wndResourceView.Expand (hRoot, TVE_EXPAND);

	hFolder = m_wndResourceView.InsertItem (_T("Dialog"), 0, 0, hRoot);
	m_wndResourceView.InsertItem (_T("IDD_ABOUTBOX"), 3, 3, hFolder);

	hFolder = m_wndResourceView.InsertItem (_T("Icon"), 0, 0, hRoot);
	m_wndResourceView.InsertItem (_T("IDR_HELLO"), 4, 4, hFolder);
	m_wndResourceView.InsertItem (_T("IDR_MAINFRAME"), 4, 4, hFolder);

	m_wndResourceView.Expand (hFolder, TVE_EXPAND);

	hFolder = m_wndResourceView.InsertItem (_T("Menu"), 0, 0, hRoot);
	m_wndResourceView.InsertItem (_T("IDR_CONTEXT_MENU"), 5, 5, hFolder);
	m_wndResourceView.InsertItem (_T("IDR_POPUP_SELECTIONMARGIN"), 5, 5, hFolder);
	m_wndResourceView.InsertItem (_T("IDR_HELLO"), 5, 5, hFolder);
	m_wndResourceView.InsertItem (_T("IDR_MAINFRAME"), 5, 5, hFolder);
	m_wndResourceView.InsertItem (_T("IDR_POPUP_TOOLBAR"), 5, 5, hFolder);

	m_wndResourceView.Expand (hFolder, TVE_EXPAND);

	hFolder = m_wndResourceView.InsertItem (_T("String Table"), 0, 0, hRoot);
	m_wndResourceView.InsertItem (_T("String Table"), 6, 6, hFolder);

	hFolder = m_wndResourceView.InsertItem (_T("Toolbar"), 0, 0, hRoot);
	m_wndResourceView.InsertItem (_T("IDR_MAINFRAME"), 7, 7, hFolder);

	hFolder = m_wndResourceView.InsertItem (_T("Version"), 0, 0, hRoot);
	m_wndResourceView.InsertItem (_T("VS_VERSION_INFO"), 8, 8, hFolder);
}

void CResourceViewBar::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (CBCGPPopupMenu::GetSafeActivePopupMenu() != NULL)
	{
		return;
	}
	
	CBCGPTreeCtrl* pWndTree = (CBCGPTreeCtrl*) &m_wndResourceView;
	ASSERT_VALID (pWndTree);

	if (pWnd != pWndTree)
	{
		CBCGPDockingControlBar::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint (-1, -1))
	{
		//---------------------
		// Select clicked item:
		//---------------------
		CPoint ptTree = point;
		pWndTree->ScreenToClient (&ptTree);

		HTREEITEM hTreeItem = pWndTree->HitTest (ptTree);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem (hTreeItem);
		}
	}

	pWndTree->SetFocus ();
	theApp.GetContextMenuManager ()->ShowPopupMenu (IDR_POPUP_RESOURCE,
		point.x, point.y, this, TRUE);
}

void CResourceViewBar::OnEditCut() 
{
	// TODO: Add your command handler code here
	
}

void CResourceViewBar::OnEditCopy() 
{
	// TODO: Add your command handler code here
	
}

void CResourceViewBar::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}

void CResourceViewBar::OnEditClear() 
{
	// TODO: Add your command handler code here
	
}

void CResourceViewBar::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
	m_wndResourceView.SetFocus ();
}

void CResourceViewBar::OnChangeVisualStyle ()
{
	m_ResourceViewImages.DeleteImageList ();

	UINT uiBmpId = theApp.m_b2012Icons ? IDB_RESOURCE_VIEW_2012 : theApp.m_bHiColorIcons ? 
		IDB_RESOURCE_VIEW_HC : IDB_RESOURCE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap (uiBmpId))
	{
		TRACE(_T ("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT (FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap (&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons || theApp.m_b2012Icons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ResourceViewImages.Create (16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ResourceViewImages.Add (&bmp, RGB (255, 0, 255));

	m_wndResourceView.SetImageList (&m_ResourceViewImages, TVSIL_NORMAL);

	globalData.SetWindowTheme(&m_wndResourceView, theApp.m_bExplorerThemeTrees ? L"explorer" : NULL, NULL);
	m_wndResourceView.SendMessage (BCGM_CHANGEVISUALMANAGER, 0, 0);
	TreeView_SetLineColor(m_wndResourceView.GetSafeHwnd(), globalData.clrBarDkShadow);
}
