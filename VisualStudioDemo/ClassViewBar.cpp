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
// ClassViewBar.cpp: implementation of the CClassViewBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "MainFrm.h"
#include "ClassViewBar.h"

class CClassViewMenuButton : public CBCGPToolbarMenuButton
{
	friend class CClassViewBar;

	DECLARE_SERIAL(CClassViewMenuButton)

public:
	CClassViewMenuButton(HMENU hMenu = NULL) :
		CBCGPToolbarMenuButton ((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE,
						BOOL bDrawBorder = TRUE,
						BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CBCGPToolBar::GetImages ();

		CBCGPDrawState ds(CBCGPVisualManager::GetInstance()->IsAutoGrayscaleImages());
		pImages->PrepareDrawImage (ds);

		CBCGPToolbarMenuButton::OnDraw (pDC, rect, 
			pImages, bHorz, 
			bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage (ds);
	}
};

IMPLEMENT_SERIAL(CClassViewMenuButton, CBCGPToolbarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CClassViewBar, CBCGPDockingControlBar)

CClassViewBar::CClassViewBar()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CClassViewBar::~CClassViewBar()
{
}

BEGIN_MESSAGE_MAP(CClassViewBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CClassViewBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMEBER_FUNCTION, OnClassAddMemeberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMEBER_VARIABLE, OnClassAddMemeberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnClassDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassViewBar message handlers

int CClassViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndSplitter.CreateStatic(this, 2, 1);
	m_wndSplitter.SetBorderSize(0);

	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create views:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;
	
	m_wndClassView.m_bVisualManagerStyle = TRUE;

	if (!m_wndClassView.Create (dwViewStyle, rectDummy, &m_wndSplitter, m_wndSplitter.IdFromRowCol (0, 0)))
	{
		TRACE0("Failed to create Class View\n");
		return -1;      // fail to create
	}

	m_wndClassView.SetOwner(this);

	const DWORD dwListStyle = WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE;

	m_wndMembers.m_bVisualManagerStyle = TRUE;

	if (!m_wndMembers.Create (dwListStyle, rectDummy, &m_wndSplitter, m_wndSplitter.IdFromRowCol (1, 0)))
	{
		TRACE0("Failed to create Preview\n");
		return -1;      // fail to create
	}

	// Load images:
	m_wndToolBar.Create (this, dwDefaultToolbarStyle, IDR_SORT);
	m_wndToolBar.LoadToolBar (IDR_SORT, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle ();

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
		
	m_wndToolBar.SetBarStyle (
		m_wndToolBar.GetBarStyle () & 
			~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner (this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame (FALSE);

	CBCGPToolBarImages* pImages = CBCGPToolBar::GetImages ();
	ASSERT_VALID (pImages);

	CMenu menuSort;
	menuSort.LoadMenu (IDR_POPUP_SORT);

	m_wndToolBar.ReplaceButton (ID_SORT_MENU, 
		CClassViewMenuButton (menuSort.GetSubMenu (0)->GetSafeHmenu ()));

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST (CClassViewMenuButton,
		m_wndToolBar.GetButton (0));

	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage (CImageHash::GetImageOfCommand (m_nCurrSort));
		pButton->SetMessageWnd (this);
	}

	// Fill view context (dummy code, don't seek here something magic :-)):
	FillClassView();

	return 0;
}

void CClassViewBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	
	if (CanAdjustLayout())
	{
		AdjustLayout();
	}
}

void CClassViewBar::FillClassView ()
{
	HTREEITEM hRoot = m_wndClassView.InsertItem (_T("MyApp classes"), 0, 0);
	m_wndClassView.SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hClass = m_wndClassView.InsertItem (_T("CAboutDlg"), 1, 1, hRoot);
	m_wndClassView.SetItemData(hClass, 1);
	m_wndClassView.InsertItem (_T("Base Types"), 2, 2, hClass);
	m_wndClassView.Expand (hRoot, TVE_EXPAND);

	hClass = m_wndClassView.InsertItem (_T("CMyAppApp"), 1, 1, hRoot);
	m_wndClassView.SetItemData(hClass, 2);
	m_wndClassView.InsertItem (_T("Base Types"), 2, 2, hClass);

	hClass = m_wndClassView.InsertItem (_T("CMyAppDoc"), 1, 1, hRoot);
	m_wndClassView.SetItemData(hClass, 3);
	m_wndClassView.InsertItem (_T("Base Types"), 2, 2, hClass);
	m_wndClassView.Select(hClass, TVGN_CARET);

	hClass = m_wndClassView.InsertItem (_T("CMyAppView"), 1, 1, hRoot);
	m_wndClassView.SetItemData(hClass, 4);
	m_wndClassView.InsertItem (_T("Base Types"), 2, 2, hClass);
	m_wndClassView.Expand (hClass, TVE_EXPAND);

	hClass = m_wndClassView.InsertItem (_T("CMainFrame"), 1, 1, hRoot);
	m_wndClassView.SetItemData(hClass, 5);
	m_wndClassView.InsertItem (_T("Base Types"), 2, 2, hClass);

	hClass = m_wndClassView.InsertItem (_T("Globals"), 2, 2, hRoot);
	m_wndClassView.SetItemData(hClass, 6);
}

void CClassViewBar::FillClassMembers(HTREEITEM hItem)
{
	m_wndMembers.DeleteAllItems();

	int nClass = hItem == NULL ? 0 : (int)m_wndClassView.GetItemData(hItem);

	switch (nClass)
	{
	case 1:
		m_wndMembers.InsertItem (_T("CAboutDlg()"), 3, 3);
		m_wndMembers.InsertItem (_T("DoDataExchange(CDataExchange* pDX)"), 4, 4);
		break;

	case 2:
		m_wndMembers.InsertItem (_T("CMyAppApp()"), 3, 3);
		m_wndMembers.InsertItem (_T("InitInstance()"), 3, 3);
		m_wndMembers.InsertItem (_T("OnAppAbout()"), 3, 3);
		break;

	case 3:
		m_wndMembers.InsertItem (_T("AssertValid()"), 3, 3);
		m_wndMembers.InsertItem (_T("CMyAppDoc()"), 4, 4);
		m_wndMembers.InsertItem (_T("~CMyAppDoc()"), 3, 3);
		m_wndMembers.InsertItem (_T("Dump(CDumpContext& dc)"), 3, 3);
		m_wndMembers.InsertItem (_T("OnNewDocument()"), 3, 3);
		m_wndMembers.InsertItem (_T("Serialize()"), 3, 3);
		break;

	case 4:
		m_wndMembers.InsertItem (_T("AssertValid()"), 3, 3);
		m_wndMembers.InsertItem (_T("CMyAppView()"), 4, 4);
		m_wndMembers.InsertItem (_T("~CMyAppView()"), 3, 3);
		m_wndMembers.InsertItem (_T("Dump(CDumpContext& dc)"), 3, 3);
		m_wndMembers.InsertItem (_T("GetDocument()"), 3, 3);
		m_wndMembers.InsertItem (_T("OnDraw(CDC* pDC)"), 3, 3);
		break;

	case 5:
		m_wndMembers.InsertItem (_T("AssertValid()"), 3, 3);
		m_wndMembers.InsertItem (_T("CMainFrame()"), 3, 3);
		m_wndMembers.InsertItem (_T("~CMainFrame()"), 3, 3);
		m_wndMembers.InsertItem (_T("Dump(CDumpContext& dc)"), 3, 3);
		m_wndMembers.InsertItem (_T("OnCreate(LPCREATESTRUCT lpCreateStruct)"), 4, 4);
		m_wndMembers.InsertItem (_T("PreCreateWindow(CREATESTRUCT& cs)"), 3, 3);
		m_wndMembers.InsertItem (_T("m_wndMenuBar"), 6, 6);
		m_wndMembers.InsertItem (_T("m_wndToolBar"), 6, 6);
		m_wndMembers.InsertItem (_T("m_wndStatusBar"), 6, 6);
		break;

	case 6:
		m_wndMembers.InsertItem (_T("theApp"), 5, 5);
		break;
	}
}

void CClassViewBar::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (CBCGPPopupMenu::GetSafeActivePopupMenu() != NULL)
	{
		return;
	}
	
	CBCGPTreeCtrl* pWndTree = (CBCGPTreeCtrl*)&m_wndClassView;
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
	CMenu menu;
	menu.LoadMenu (IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CBCGPMDIFrameWnd)))
	{
	   CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	   
	   if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
		   return;
	   
	   ((CBCGPMDIFrameWnd*)AfxGetMainWnd())->OnShowPopupMenu (pPopupMenu);
	   UpdateDialogControls(this, FALSE);
	}
}

void CClassViewBar::AdjustLayout ()
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect (rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout (FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos (NULL, rectClient.left, rectClient.top, 
								rectClient.Width (), cyTlb,
								SWP_NOACTIVATE | SWP_NOZORDER);

	CRect rectPrev;
	m_wndSplitter.GetClientRect (rectPrev);

	m_wndSplitter.SetWindowPos (NULL, rectClient.left, rectClient.top + cyTlb, 
								rectClient.Width (), rectClient.Height () - cyTlb,
								SWP_NOACTIVATE | SWP_NOZORDER);

	if (rectPrev.Height () != rectClient.Height () - cyTlb)
	{
		m_wndSplitter.SetRowInfo (0, rectClient.Height () * 2 / 3, 0);
	}
}

BOOL CClassViewBar::PreTranslateMessage(MSG* pMsg) 
{
	return CBCGPDockingControlBar::PreTranslateMessage(pMsg);
}

void CClassViewBar::OnSort (UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST (CClassViewMenuButton,
		m_wndToolBar.GetButton (0));

	if (pButton != NULL)
	{
		pButton->SetImage (CImageHash::GetImageOfCommand (id));
		m_wndToolBar.Invalidate ();
		m_wndToolBar.UpdateWindow ();
	}
}

void CClassViewBar::OnUpdateSort (CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (pCmdUI->m_nID == m_nCurrSort);
}

void CClassViewBar::OnClassAddMemeberFunction() 
{
	BCGPMessageBox (_T("Add member function..."));
}

void CClassViewBar::OnClassAddMemeberVariable() 
{
	// TODO: Add your command handler code here
	
}

void CClassViewBar::OnClassDefinition() 
{
	// TODO: Add your command handler code here
	
}

void CClassViewBar::OnClassProperties() 
{
	// TODO: Add your command handler code here
	
}

void CClassViewBar::OnNewFolder() 
{
	BCGPMessageBox (_T("New Folder..."));
}

void CClassViewBar::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
	m_wndClassView.SetFocus ();
}

void CClassViewBar::OnChangeVisualStyle ()
{
	m_ClassViewImages.DeleteImageList ();

	UINT uiBmpId = theApp.m_b2012Icons ? IDB_CLASS_VIEW_2012 : theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_HC : IDB_CLASS_VIEW;

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

	m_ClassViewImages.Create (16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ClassViewImages.Add (&bmp, RGB (255, 0, 0));
	
	m_wndClassView.SetImageList (&m_ClassViewImages, TVSIL_NORMAL);
	m_wndMembers.SetImageList (&m_ClassViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages ();
	m_wndToolBar.LoadBitmap (theApp.m_b2012Icons ? IDB_SORT_2012 : theApp.m_bHiColorIcons ? 
		IDB_SORT_HC : IDR_SORT, 0, 0, TRUE /* Locked */);

	globalData.SetWindowTheme(&m_wndClassView, theApp.m_bExplorerThemeTrees ? L"explorer" : NULL, NULL);
	m_wndClassView.SendMessage (BCGM_CHANGEVISUALMANAGER, 0, 0);
	TreeView_SetLineColor(m_wndClassView.GetSafeHwnd(), globalData.clrBarDkShadow);

	m_wndMembers.SendMessage (BCGM_CHANGEVISUALMANAGER, 0, 0);
	m_wndSplitter.SetBorderSize(theApp.m_b2012Icons ? 0 : 2);
}
