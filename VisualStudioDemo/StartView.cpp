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
// StartView.cpp : implementation file
//

#include "stdafx.h"
#include "VisualStudioDemo.h"
#include "StartView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartView

#define IDC_START_IMAGE	1

IMPLEMENT_DYNCREATE(CStartView, CView)

CStartView::CStartView() :
	m_wndHotSpot(TRUE /* DPI auto-scale */)
{
}

CStartView::~CStartView()
{
}

BEGIN_MESSAGE_MAP(CStartView, CView)
	//{{AFX_MSG_MAP(CStartView)
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnDisableUpdate)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnDisableUpdate)
	ON_WM_SYSCOLORCHANGE()
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDS_CARET_POS, OnCaretPos)
	ON_BN_CLICKED(IDC_START_IMAGE, OnClickHotSpot)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartView diagnostics

#ifdef _DEBUG
void CStartView::AssertValid() const
{
	CView::AssertValid();
}

void CStartView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStartView operations

BOOL CStartView::CreateView(CWnd* pParent, CCreateContext* pContext)
{
	CRect rect (0, 0, 300,300);

    if (!Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
        rect, pParent, AFX_IDW_PANE_FIRST, pContext))
    {
        TRACE0("Warning: couldn't create CStartView!\n");
        return FALSE;
    }

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStartView message handlers

void CStartView::OnInitialUpdate() 
{
	CRect rectClient;
	GetClientRect (rectClient);

	m_wndHotSpot.Create (rectClient, this, IDC_START_IMAGE);
	SetBitmap ();
}

void CStartView::OnDraw(CDC* /*pDC*/)
{
}

void CStartView::OnCaretPos(CCmdUI* pCmdUI)
{
	pCmdUI->SetText (_T(""));
	pCmdUI->Enable(FALSE);
}

BOOL CStartView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

void CStartView::OnDisableUpdate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

void CStartView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_wndHotSpot.GetSafeHwnd () != NULL)
	{
		m_wndHotSpot.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

void CStartView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	if (m_wndHotSpot.GetSafeHwnd () != NULL)
	{
		m_wndHotSpot.SetFocus ();
	}	
}

void CStartView::OnClickHotSpot()
{
	UINT uiCmd = m_wndHotSpot.GetHotSpot ();
	if (uiCmd == 1)
	{
		uiCmd = ID_HELP_WEB;
	}

	AfxGetMainWnd ()->SendMessage (WM_COMMAND, uiCmd);
}

void CStartView::OnSysColorChange() 
{
	CView::OnSysColorChange();
	SetBitmap ();	
}

void CStartView::OnChangeVisualStyle()
{
	SetBitmap ();
}

void CStartView::SetBitmap ()
{
	if (m_wndHotSpot.GetSafeHwnd () == NULL)
	{
		return;
	}

	BOOL bTileHotSpots = FALSE;

	if (theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_VS_2012_DARK ||
		theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_VS_2013_DARK ||
		theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_BLACK)
	{
		m_wndHotSpot.SetImage (IDB_START_HC_2012_DARK);
		m_wndHotSpot.SetBackgroundColor(RGB (45, 45, 48));
		
		bTileHotSpots = TRUE;
	}
	else if (theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_VS_2012_LIGHT ||
		theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_VS_2012_BLUE ||
		theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_WHITE ||
		theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_GRAY ||
		theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY ||
		theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_COLORFUL ||
		theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_DARK_GRAY ||
		theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_WHITE ||
		theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_VS_2013_LIGHT ||
		theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_VS_2013_BLUE)
	{
		m_wndHotSpot.SetImage (IDB_START_HC_2012);
		m_wndHotSpot.SetBackgroundColor(RGB (239, 239, 242));

		bTileHotSpots = TRUE;
	}
	else if (theApp.GetVisualTheme() == CBCGPWinApp::BCGP_VISUAL_THEME_VS_2010)
	{
		m_wndHotSpot.SetImage (IDB_START_HC_2010);
		m_wndHotSpot.SetBackgroundColor (RGB (79, 105, 148));
	}
	else
	{
		m_wndHotSpot.SetImage (IDB_START_HC);
		m_wndHotSpot.SetBackgroundColor (RGB (227, 232, 242));
	}

	m_wndHotSpot.SetHighlightHotArea (82, 45);

	m_wndHotSpot.AddHotSpot (1, CRect (CPoint (33, 302), CSize (125, 50)));

	if (bTileHotSpots)
	{
		m_wndHotSpot.AddHotSpot (ID_VIEW_CUSTOMIZE, CRect (CPoint (40, 92), CSize (116, 92)), _T("Customize"), _T("Click this tile to customize toolbars, menus and keyboard shortcuts."));
		m_wndHotSpot.AddHotSpot (ID_VIEW_APP_LOOK, CRect (CPoint (162, 92), CSize (116, 92)), _T("Application Look"), _T("Click this tile to change application visual theme and other parameters"));
		m_wndHotSpot.AddHotSpot (ID_FILE_NEW, CRect (CPoint (40, 192), CSize (116, 92)), _T("New File"), _T("Click this tile to create a new document: C++, HTML, C# and others"));
		m_wndHotSpot.AddHotSpot (ID_HELP_WEB, CRect (CPoint (162, 192), CSize (116, 92)), _T("www.bcgsoft.com"), _T("Click this tile to visit our site"));
	}
	else
	{
		m_wndHotSpot.AddHotSpot (ID_VIEW_CUSTOMIZE, CRect (CPoint (360, 139), CSize (186, 29)));
		m_wndHotSpot.AddHotSpot (ID_VIEW_APP_LOOK, CRect (CPoint (360, 175), CSize (186, 18)));
		m_wndHotSpot.AddHotSpot (ID_FILE_NEW, CRect (CPoint (360, 193), CSize (186, 29)));
		m_wndHotSpot.AddHotSpot (ID_HELP_WEB, CRect (CPoint (360, 229), CSize (186, 29)));
	}
}

int CStartView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
