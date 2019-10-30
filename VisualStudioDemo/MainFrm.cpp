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
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "VisualStudioDemo.h"
#include "FindComboBox.h"
#include "MainFrm.h"
#include "BCGPTabbedControlBar.h"
#include "BCGPMiniFrameWnd.h"
#include "ChildFrm.h"
#include "StartView.h"
#include "UndoBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SEARCH_PROMPT			_T("Search Toolbox")
#define OUT_OF_FILTER_MESSAGE	_T("No results found")

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CBCGPMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_HELP_KEYBOARDMAP, OnHelpKeyboardmap)
	ON_COMMAND(ID_FILE_NEW_PROJECT, OnFileNewProject)
	ON_COMMAND(ID_FILE_NEW_BLANK_SOLUTION, OnFileNewBlankSolution)
	ON_COMMAND(ID_FILE_OPEN_SOLUTION, OnFileOpenSolution)
	ON_COMMAND(ID_FILE_CLOSE_SOLUTION, OnFileCloseSolution)
	ON_COMMAND(ID_FILE_SAVE_ALL, OnFileSaveAll)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_TOOLS_CONNECT_TO_DATABASE, OnToolsConnectToDatabase)
	ON_COMMAND(ID_TOOLS_DEBUG_PROCESSES, OnToolsDebugProcesses)
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullScreen)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_COMMAND(ID_HELP_WEB, OnHelpWeb)
	ON_COMMAND(ID_MDI_MOVE_TO_NEXT_GROUP, OnMdiMoveToNextGroup)
	ON_COMMAND(ID_MDI_MOVE_TO_PREV_GROUP, OnMdiMoveToPrevGroup)
	ON_COMMAND(ID_MDI_NEW_HORZ_TAB_GROUP, OnMdiNewHorzTabGroup)
	ON_COMMAND(ID_MDI_NEW_VERT_GROUP, OnMdiNewVertGroup)
	ON_COMMAND(ID_MDI_CANCEL, OnMdiCancel)
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_CLASS, OnViewClass)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CLASS, OnUpdateViewClass)
	ON_COMMAND(ID_VIEW_FILE, OnViewFile)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FILE, OnUpdateViewFile)
	ON_COMMAND(ID_VIEW_RESOURCE, OnViewResource)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESOURCE, OnUpdateViewResource)
	ON_COMMAND(ID_VIEW_PROPERTIES, OnViewProperties)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTIES, OnUpdateViewProperties)
	ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT, OnUpdateViewOutput)
	ON_COMMAND(ID_VIEW_WATCH, OnViewWatch)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WATCH, OnUpdateViewWatch)
	ON_COMMAND(ID_VIEW_TOOLBOX, OnViewToolbox)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBOX, OnUpdateViewToolbox)
	ON_COMMAND(ID_MDI_TABBED_DOCUMENT, OnMdiTabbedDocument)
	ON_UPDATE_COMMAND_UI(ID_MDI_TABBED_DOCUMENT, OnUpdateMdiTabbedDocument)
	ON_COMMAND(ID_HELP_SHOW_START, OnHelpShowStart)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_WINDOW_RESET_LAYOUT, OnReseWindowsLayout)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_REGISTERED_MESSAGE(BCGM_ON_GET_TAB_TOOLTIP, OnGetTabToolTip)
	ON_REGISTERED_MESSAGE(BCGM_CUSTOMIZEHELP, OnHelpCustomizeToolbars)
	ON_COMMAND(ID_TOOLBOX, OnToolBox)
	ON_UPDATE_COMMAND_UI(IDS_CARET_POS, OnUpdateCaretPos)
	ON_COMMAND(ID_FILE_OPEN_FOLDER, &CMainFrame::OnFileOpenFolder)
	ON_COMMAND(ID_FILE_CLOSE_FOLDER, &CMainFrame::OnFileCloseFolder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	IDS_CARET_POS,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL, 
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	CBCGPPopupMenu::SetForceShadow (TRUE);

	m_bCanCovertControlBarToMDIChild = TRUE;
	m_bShowAppState = FALSE;

	// Set Manager pointer
	CBCGPVisualStudioGUIDemoApp * pApp = (CBCGPVisualStudioGUIDemoApp *)AfxGetApp();
	SetManager(pApp->GetManager());

	//m_bOpenFolder = false;

	EnableWindowsNavigator();
	EnableTearOffMDIChildren();
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CBCGPToolbarComboBoxButton::SetFlatMode ();
	CBCGPToolBar::EnableQuickCustomization ();

	//-----------------
	// Create menu bar:
	//-----------------
	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	//--------------------------------------------
	// Menu will not take the focus on activation:
	//--------------------------------------------
	CBCGPPopupMenu::SetForceMenuFocus (FALSE);

	//---------------------
	// Create main toolbar:
	//---------------------
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strMainToolbarTitle;
	strMainToolbarTitle.LoadString (IDS_MAIN_TOOLBAR);
	m_wndToolBar.SetWindowText (strMainToolbarTitle);

	//----------------------
	// Create Build toolbar:
	//----------------------
	if (!m_wndToolbarBuild.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D,
		ID_VIEW_BUILD_TOOLBAR) ||
		!m_wndToolbarBuild.LoadToolBar (IDR_BUILD))
	{
		TRACE0("Failed to create build toolbar\n");
		return FALSE;      // fail to create
	}

	CString strBuildToolbarTitle;
	strBuildToolbarTitle.LoadString (IDS_BUILD_TOOLBAR);
	m_wndToolbarBuild.SetWindowText (strBuildToolbarTitle);

	//---------------------
	// Create Edit toolbar:
	//---------------------
	if (!m_wndToolbarEdit.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D,
		ID_VIEW_EDIT_TOOLBAR) ||
		!m_wndToolbarEdit.LoadToolBar (IDR_EDIT))
	{
		TRACE0("Failed to create edit toolbar\n");
		return FALSE;      // fail to create
	}

	CString strEditToolbarTitle;
	strEditToolbarTitle.LoadString (IDS_EDIT_TOOLBAR);
	m_wndToolbarEdit.SetWindowText (strEditToolbarTitle);

	//--------------------------------------------------------------
	// Load menu items images (not placed on the standard toolbars):
	//--------------------------------------------------------------
	CBCGPToolBar::AddToolBarForImageCollection (IDR_MENU_IMAGES);

	//-------------------
	// Create status bar:
	//-------------------
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.SetPaneStyle (0, SBPS_STRETCH);

	//------------------------------
	// Update status bar indicators:
	//------------------------------
	m_wndStatusBar.SendMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);

	//--------------------------------
	// Create docking control windows:
	//--------------------------------
	if (!CreateDockingBars ())
	{
		return -1;
	}

	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolbarBuild.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolbarEdit.EnableDocking(CBRS_ALIGN_ANY);
	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutputView.EnableDocking(CBRS_ALIGN_ANY);

	m_wndWatchBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);

	EnableAutoHideBars(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);

	DockControlBar(&m_wndToolbarBuild);
	DockControlBarLeftOf (&m_wndToolbarEdit, &m_wndToolbarBuild);

	//CBCGPDockingControlBar* pTabbedBar = NULL; 
	//m_wndFileView.AttachToTabWnd (pTabbedBar, BCGP_DM_SHOW, TRUE, &pTabbedBar);
	DockControlBar(&m_wndFileView);

	DockControlBar(&m_wndOutputView);

	m_wndWatchBar.DockToWindow (&m_wndOutputView, CBRS_ALIGN_LEFT);

	// "Output" and "Watch" panes are initially in auto-hide mode:
	m_wndOutputView.ToggleAutoHide();
	m_wndWatchBar.ToggleAutoHide();

	//------------------------
	// Enable windows manager:
	//------------------------
	EnableWindowsDialog (ID_WINDOW_MANAGER, _T("Windows..."), TRUE /* Show always */, FALSE /* No help button */, TRUE /* Resizable */);
	EnableFullScreenMode (ID_VIEW_FULLSCREEN);

	DockControlBar(&m_wndStartPage);

	SaveDockingLayout();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */,
		BCGCUSTOMIZE_MENU_SHADOWS | BCGCUSTOMIZE_TEXT_LABELS | BCGCUSTOMIZE_MENU_ANIMATIONS);

	pDlgCust->EnableUserDefinedToolbars ();

	//-----------------
	// Setup combboxes:
	//-----------------
	CFindComboButton comboBoxFind;
	comboBoxFind.SetPrompt(_T("Search"));

	pDlgCust->ReplaceButton (ID_EDIT_FIND, comboBoxFind);

	CBCGPToolbarComboBoxButton comboButtonConfig (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, 
			CImageHash::GetImageOfCommand (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, FALSE),
			CBS_DROPDOWNLIST);
	comboButtonConfig.AddItem (_T("Win32 Debug"));
	comboButtonConfig.AddItem (_T("Win32 Release"));
	comboButtonConfig.SelectItem (0);

	pDlgCust->ReplaceButton (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, comboButtonConfig);

	//-------------------------
	// Setup undo/redo buttons:
	//-------------------------
	pDlgCust->ReplaceButton (ID_EDIT_UNDO, CUndoButton (ID_EDIT_UNDO, _T("&Undo")));
	pDlgCust->ReplaceButton (ID_EDIT_REDO, CUndoButton (ID_EDIT_REDO, _T("&Redo")));

	pDlgCust->Create ();
}

LRESULT CMainFrame::OnToolbarReset(WPARAM wp,LPARAM)
{
	UINT uiToolBarId = (UINT) wp;

	switch (uiToolBarId)
	{
	case IDR_MAINFRAME:
		{
			//--------------------------------------
			// Replace "Find..." button by combobox:
			//--------------------------------------
			CFindComboButton comboBoxFind;
			comboBoxFind.SetPrompt(_T("Search"));

			m_wndToolBar.ReplaceButton (ID_EDIT_FIND, comboBoxFind);

			//-------------------------------------
			// Replace "Undo" button by menubutton:
			//-------------------------------------
			m_wndToolBar.ReplaceButton (ID_EDIT_UNDO, CUndoButton (ID_EDIT_UNDO, _T("&Undo")));
			m_wndToolBar.ReplaceButton (ID_EDIT_REDO, CUndoButton (ID_EDIT_REDO, _T("&Redo")));
		}
		break;

	case IDR_BUILD:
		{
			//-----------------------------------------------
			// Replace "Configuration..." button by combobox:
			//-----------------------------------------------
			CBCGPToolbarComboBoxButton comboButton (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, 
				CImageHash::GetImageOfCommand (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, FALSE),
				CBS_DROPDOWNLIST);
			comboButton.AddItem (_T("Win32 Debug"));
			comboButton.AddItem (_T("Win32 Release"));
			comboButton.SelectItem (0);

			m_wndToolbarBuild.ReplaceButton (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION,
											comboButton);
		}
		break;
	}

	return 0;
}

LRESULT CMainFrame::OnHelpCustomizeToolbars(WPARAM /*wp*/, LPARAM lp)
{
//	int iPageNum = (int) wp;

	CBCGPToolbarCustomize* pDlg = (CBCGPToolbarCustomize*) lp;
	ASSERT_VALID (pDlg);

	// TODO: show help about page number iPageNum


	return 0;
}

BOOL CMainFrame::OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop)
{
	CMenu menu;
	VERIFY(menu.LoadMenu (bDrop ? IDR_POPUP_DROP_MDITABS : IDR_POPUP_MDITABS));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	if ((dwAllowedItems & BCGP_MDI_CREATE_HORZ_GROUP) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_NEW_HORZ_TAB_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CREATE_VERT_GROUP) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_NEW_VERT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_NEXT) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_MOVE_TO_NEXT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_PREV) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_MOVE_TO_PREV_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_BE_DOCKED) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_TABBED_DOCUMENT, MF_BYCOMMAND);
	}

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->SetAutoDestroy (FALSE);

	CWnd* pMenuOwner = GetActiveTearOffFrame() == NULL ? this : GetActiveTearOffFrame();
	pPopupMenu->Create(pMenuOwner, point.x, point.y, pPopup->GetSafeHmenu ());

	return TRUE;
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	if (!CBCGPMDIFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	// Add some tools for example....
	CBCGPUserToolsManager* pUserToolsManager = theApp.GetUserToolsManager ();
	if (pUserToolsManager != NULL &&
		pUserToolsManager->GetUserTools ().IsEmpty ())
	{
		CBCGPUserTool* pTool1 = pUserToolsManager->CreateNewTool ();
		pTool1->m_strLabel = _T("Notepad");
		pTool1->SetCommand (_T("notepad.exe"));

		CBCGPUserTool* pTool2 = pUserToolsManager->CreateNewTool ();
		pTool2->m_strLabel = _T("Paint Brush");
		pTool2->SetCommand (_T("mspaint.exe"));

		CBCGPUserTool* pTool3 = pUserToolsManager->CreateNewTool ();
		pTool3->m_strLabel = _T("Windows Explorer");
		pTool3->SetCommand (_T("explorer.exe"));

		CBCGPUserTool* pTool4 = pUserToolsManager->CreateNewTool ();
		pTool4->m_strLabel = _T("BCGSoft On-Line");
		pTool4->SetCommand (_T("http://www.bcgsoft.com"));
	}

	CBCGPMDITabParams mdiTabParams;
	mdiTabParams.m_bTabCustomTooltips = TRUE;

	EnableMDITabbedGroups (TRUE, mdiTabParams);
	return TRUE;
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	//----------------------------------------------------
	// If control located on toolbar has focus, we should 
	// redirect clipboard commands to this control:
	//----------------------------------------------------
	if (CFindComboButton::HasFocus () && HIWORD (wParam) == 1)	// Command from accelerator
	{
		UINT uiCmd = LOWORD (wParam);
		switch (uiCmd)
		{
		case ID_EDIT_PASTE:
			::SendMessage (::GetFocus (), WM_PASTE, 0, 0);
			return TRUE;

		case ID_EDIT_COPY:
			::SendMessage (::GetFocus (), WM_COPY, 0, 0);
			return TRUE;

		case ID_EDIT_CUT:
			::SendMessage (::GetFocus (), WM_CUT, 0, 0);
			return TRUE;
		}
	}
	
	return CBCGPMDIFrameWnd::OnCommand(wParam, lParam);
}

void CMainFrame::OnHelpKeyboardmap() 
{
	CBCGPKeyMapDlg dlg (this, TRUE /* Enable Print */);
	dlg.DoModal ();
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!CBCGPMDIFrameWnd::OnCreateClient(lpcs, pContext))
	{
		return FALSE;
	}

	m_wndStartPage.SetContext (pContext);

	if (!m_wndStartPage.Create (_T("Start Page"), this, CRect (0, 0, 300, 300),
		TRUE, ID_HELP_SHOW_START,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar\n");
		return FALSE;      // fail to create
	}

	m_wndStartPage.EnableDocking (CBRS_ALIGN_ANY);

	return TRUE;
}

BOOL CMainFrame::CreateDockingBars ()
{
	//------------------
	// Create file view:
	//------------------
	if (!m_wndFileView.Create (_T("Solution Explorer"), this, CRect (0, 0, 200, 200),
		TRUE, 
		ID_VIEW_FILE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Solution Explorer bar\n");
		return FALSE;      // fail to create
	}


	//////////////////////////////////New Output////////////////////////////////////////
	if (!m_wndOutputView.Create (_T("Output"), this, CRect (0, 0, 200, 100),
		TRUE, 
		ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create output bar\n");
		return FALSE;      // fail to create
	}

	//------------------
	// Create watch bar:
	//------------------
	if (!m_wndWatchBar.Create (_T("Watch"), this, CRect (0, 0, 300, 100),
		TRUE, 
		ID_VIEW_WATCH,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create watch bar\n");
		return FALSE;      // fail to create
	}

	SetDockingBarsIcons (FALSE);
	return TRUE;
}

void CMainFrame::SetDockingBarsIcons (BOOL bHiColorIcons)
{
	HICON hFileViewIcon = !theApp.m_bDockingPaneIcons ? NULL : (HICON) ::LoadImage (::AfxGetResourceHandle (), 
				MAKEINTRESOURCE (theApp.m_b2012Icons ? IDI_FILE_VIEW_2012 : bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW),
				IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_wndFileView.SetIcon (hFileViewIcon, FALSE);


	HICON hOutputBarIcon = !theApp.m_bDockingPaneIcons ? NULL : (HICON) ::LoadImage (::AfxGetResourceHandle (), 
				MAKEINTRESOURCE (theApp.m_b2012Icons ? IDI_OUTPUT_BAR_2012 : bHiColorIcons ? IDI_OUTPUT_BAR_HC : IDI_OUTPUT_BAR),
				IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_wndOutputView.SetIcon (hOutputBarIcon, FALSE);


	HICON hWatchBarIcon = !theApp.m_bDockingPaneIcons ? NULL : (HICON) ::LoadImage (::AfxGetResourceHandle (), 
				MAKEINTRESOURCE (theApp.m_b2012Icons ? IDI_WATCH_BAR_2012 : bHiColorIcons ? IDI_WATCH_BAR_HC : IDI_WATCH_BAR),
				IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_wndWatchBar.SetIcon (hWatchBarIcon, FALSE);

	
	UpdateMDITabbedBarsIcons ();
}

void CMainFrame::OnFileNewProject() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileNewBlankSolution() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileOpenSolution() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileCloseSolution() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileSaveAll() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewRefresh() 
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnToolsConnectToDatabase() 
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnToolsDebugProcesses() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewFullScreen()
{
	ShowFullScreen ();
}

void CMainFrame::OnToolBox() 
{
}

CBCGPToolbarComboBoxButton* CMainFrame::GetFindCombo()
{
	CBCGPToolbarComboBoxButton* pFindCombo = NULL;

	CObList listButtons;
	if (CBCGPToolBar::GetCommandButtons (ID_EDIT_FIND_COMBO, listButtons) > 0)
	{
		for (POSITION posCombo = listButtons.GetHeadPosition (); 
			 pFindCombo == NULL && posCombo != NULL;)
		{
			CBCGPToolbarComboBoxButton* pCombo = 
				DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton, listButtons.GetNext (posCombo));

			if (pCombo != NULL &&
				pCombo->GetEditCtrl ()->GetSafeHwnd () == ::GetFocus ())
			{
				pFindCombo = pCombo;
			}
		}
	}

	return pFindCombo;
}

void CMainFrame::OnToolsOptions() 
{
}

void CMainFrame::OnChangeLook (BOOL bOneNoteTabs, BOOL bMDITabColors, BOOL bIsVSDotNetLook,
							   BOOL bDockTabColors, BOOL bMDITabsVS2005Look,
							   CBCGPTabWnd::TabCloseButtonMode mdiTabCloseButtonMode, BOOL bDocumentMenu, 
							   BOOL bMDIActiveTabBoldFont, BOOL bMaximizeFloatingPanes, 
							   BOOL bDblClickMaximizeFloatingPanes, BOOL bShowHiddenPanesOnMouseClick,
							   BOOL bAutoHideAnimation, BOOL bMultipleSelTabs, BOOL bShowAppState)
{
	CBCGPMDITabParams mdiTabParams;
	mdiTabParams.m_bTabCustomTooltips = TRUE;
	mdiTabParams.m_bDocumentMenu = bDocumentMenu;

	if (bMDITabsVS2005Look)
	{
		mdiTabParams.m_style = CBCGPTabWnd::STYLE_3D_VS2005;
	}
	else if (bOneNoteTabs)
	{
		mdiTabParams.m_style = CBCGPTabWnd::STYLE_3D_ONENOTE;
		mdiTabParams.m_bAutoColor = bMDITabColors;
	}

	mdiTabParams.m_closeButtonMode = mdiTabCloseButtonMode;
	mdiTabParams.m_bActiveTabBoldFont = bMDIActiveTabBoldFont;
	mdiTabParams.m_bTabMultipleSelection = bMultipleSelTabs;

	EnableMDITabbedGroups (TRUE, mdiTabParams);

	m_wndFileView.OnChangeVisualStyle ();

	if (m_wndStartPage.m_pStartView != NULL)
	{
		m_wndStartPage.m_pStartView->OnChangeVisualStyle();
	}

	CBCGPTabbedControlBar::EnableTabAutoColor (bDockTabColors);

	//-----------------------
	// Reload toolbar images:
	//-----------------------
	CBCGPToolBar::ResetAllImages ();

	CBCGPToolBar::SetGrayDisabledImages(theApp.m_b2012Icons);

	m_wndToolBar.LoadBitmap (theApp.m_b2012Icons ? IDB_MAINFRAME_2012 : theApp.m_bHiColorIcons ? IDB_MAINFRAME_HC : IDR_MAINFRAME);
	m_wndToolbarBuild.LoadBitmap (theApp.m_b2012Icons ? IDB_BUILD_2012 : theApp.m_bHiColorIcons ? IDB_BUILD_HC : IDR_BUILD);
	m_wndToolbarEdit.LoadBitmap (theApp.m_b2012Icons ? IDB_EDIT_2012 : theApp.m_bHiColorIcons ? IDB_EDIT_HC : IDR_EDIT);

	CBCGPToolBar::AddToolBarForImageCollection (IDR_MENU_IMAGES, 
		theApp.m_b2012Icons ? IDB_MENU_IMAGES_2012 : theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_HC : 0);

	//------------------
	// Inform all views:
	//------------------
	for (CWnd* pWndChild = m_wndClientArea.GetWindow (GW_CHILD); 
		pWndChild != NULL; pWndChild = pWndChild->GetNextWindow ())
	{
		CBCGPMDIChildWnd* pMDIChild = DYNAMIC_DOWNCAST(CBCGPMDIChildWnd, pWndChild);
		if (pMDIChild != NULL)
		{
			CBCGPVisualStudioGUIDemoView* pView = DYNAMIC_DOWNCAST (
				CBCGPVisualStudioGUIDemoView, pMDIChild->GetActiveView ());
			if (pView != NULL)
			{
				pView->OnChangeVisualStyle ();
			}

			CStartView* pStartView = DYNAMIC_DOWNCAST(CStartView, pMDIChild->GetActiveView ());
			if (pStartView != NULL)
			{
				pStartView->OnChangeVisualStyle ();
			}
		}
	}

	SetDockingBarsIcons (theApp.m_bHiColorIcons);

	EnableAutoHideBars(CBRS_ALIGN_ANY, bShowHiddenPanesOnMouseClick);
	CBCGPDockingControlBar::m_bDisableAnimation = !bAutoHideAnimation;

	EnableMaximizeFloatingBars(bMaximizeFloatingPanes, bDblClickMaximizeFloatingPanes);

	CBCGPDockManager* pDockManager = GetDockManager ();
	ASSERT_VALID (pDockManager);

	pDockManager->AdjustBarFrames ();

	if (m_bShowAppState != bShowAppState)
	{
		m_bShowAppState = bShowAppState;

		CChildFrame* pFrame = DYNAMIC_DOWNCAST(CChildFrame, GetActiveFrame());
		if (pFrame != NULL)
		{
			ASSERT_VALID(pFrame);
			pFrame->SetAppState();
		}
	}

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}

void CMainFrame::OnHelpWeb() 
{
	::ShellExecute (NULL, NULL, _T("http://www.bcgsoft.com"), NULL, NULL, NULL);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	return CBCGPMDIFrameWnd::PreCreateWindow(cs);
}

void CMainFrame::OnMdiMoveToNextGroup() 
{
	MDITabMoveToNextGroup ();
}

void CMainFrame::OnMdiMoveToPrevGroup() 
{
	MDITabMoveToNextGroup (FALSE);
}

void CMainFrame::OnMdiNewHorzTabGroup() 
{
	MDITabNewGroup (FALSE);
}

void CMainFrame::OnMdiNewVertGroup() 
{
	MDITabNewGroup ();
}

void CMainFrame::OnMdiCancel() 
{
	// TODO: Add your command handler code here
	
}

CBCGPMDIChildWnd* CMainFrame::CreateDocumentWindow (LPCTSTR lpcszDocName, CObject* /*pObj*/)
{
	if (lpcszDocName != NULL && lpcszDocName [0] != '\0')
	{
		CDocument* pDoc = AfxGetApp()->OpenDocumentFile (lpcszDocName);

		if (pDoc != NULL)
		{
			POSITION pos = pDoc->GetFirstViewPosition();

			if (pos != NULL)
			{
				CView* pView = pDoc->GetNextView (pos);
				return DYNAMIC_DOWNCAST (CBCGPMDIChildWnd, pView->GetParent ());
			}   
		}

	}

	return NULL;
}

void CMainFrame::OnClose() 
{
	SaveMDIState (theApp.GetRegSectionPath ());
	CBCGPMDIFrameWnd::OnClose();
}

LRESULT CMainFrame::OnGetTabToolTip(WPARAM /*wp*/, LPARAM lp)
{
	CBCGPTabToolTipInfo* pInfo = (CBCGPTabToolTipInfo*) lp;
	ASSERT (pInfo != NULL);
	ASSERT_VALID (pInfo->m_pTabWnd);

	if (!pInfo->m_pTabWnd->IsMDITab ())
	{
		return 0;
	}

	CFrameWnd* pFrame = DYNAMIC_DOWNCAST (CFrameWnd,
		pInfo->m_pTabWnd->GetTabWnd (pInfo->m_nTabIndex));
	if (pFrame == NULL)
	{
		return 0;
	}

	CDocument* pDoc = pFrame->GetActiveDocument ();
	if (pDoc == NULL)
	{
		return 0;
	}

	pInfo->m_strText = pDoc->GetPathName ();
	return 0;
}

void CMainFrame::OnViewClass() 
{
}

void CMainFrame::OnUpdateViewClass(CCmdUI* pCmdUI) 
{
}

void CMainFrame::OnViewFile() 
{
	m_wndFileView.ShowControlBar (!m_wndFileView.IsVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewFile(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndFileView.IsVisible ());	
}

void CMainFrame::OnViewResource() 
{
}

void CMainFrame::OnUpdateViewResource(CCmdUI* pCmdUI) 
{
}

void CMainFrame::OnViewProperties() 
{
}

void CMainFrame::OnUpdateViewProperties(CCmdUI* pCmdUI) 
{
}

void CMainFrame::OnViewOutput() 
{
	m_wndOutputView.ShowControlBar (!m_wndOutputView.IsVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewOutput(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndOutputView.IsVisible ());
}

void CMainFrame::OnViewWatch() 
{
	m_wndWatchBar.ShowControlBar (!m_wndWatchBar.IsVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewWatch(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndWatchBar.IsVisible ());
}

void CMainFrame::OnViewToolbox() 
{
}

void CMainFrame::OnUpdateViewToolbox(CCmdUI* pCmdUI) 
{
}

void CMainFrame::OnHelpShowStart() 
{
	if (!m_wndStartPage.IsVisible ())
	{
		m_wndStartPage.ShowControlBar (TRUE, FALSE, TRUE);	
		return;
	}

	if (m_wndStartPage.IsMDITabbed())
	{
		MDIActivate(m_wndStartPage.GetParentFrame());
	}
	else
	{
		m_wndStartPage.ShowControlBar(TRUE, FALSE, TRUE);
	}
}

void CMainFrame::ShowStartPage (BOOL bConvert)
{
	OnHelpShowStart(); 
	if (bConvert)
	{
		ControlBarToTabbedDocument (&m_wndStartPage);
	}
} 

void CMainFrame::OnMdiTabbedDocument() 
{
	CBCGPMDIChildWnd* pMDIChild = DYNAMIC_DOWNCAST(CBCGPMDIChildWnd, MDIGetActive ());
	if (pMDIChild == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	TabbedDocumentToControlBar (pMDIChild);
}

void CMainFrame::OnUpdateMdiTabbedDocument(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck ();
}

void CMainFrame::OnUpdateCaretPos(CCmdUI* pCmdUI)
{
	pCmdUI->SetText (_T(""));
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	CBCGPMDIFrameWnd::OnSettingChange(uFlags, lpszSection);
	
	m_wndOutputView.UpdateFonts();
}

void CMainFrame::OnReseWindowsLayout() 
{
	if (BCGPMessageBox(_T("Are you sure you want to restore the default window layout for the environment?"), 
		MB_YESNO | MB_ICONQUESTION, 0, NULL, _T("Reset Window Layout")) == IDYES)
	{
		LoadDockingLayout();
	}
}

void CMainFrame::SetManager(std::shared_ptr<CFileManager> pManager)
{
	m_pManager = pManager;
}

void CMainFrame::UpdateSolution(std::shared_ptr<CCodeFile> cf)
{
	m_wndFileView.UpdateSolution(cf);
}

void CMainFrame::UpdateSolution(std::shared_ptr<CAssemblyFile> af)
{
	m_wndFileView.UpdateSolution(af);
}

void CMainFrame::CloseAllDocuments()
{
	CBCGPVisualStudioGUIDemoApp * pApp = (CBCGPVisualStudioGUIDemoApp *)AfxGetApp();
	POSITION pos = pApp->m_pDocTemplateCpp->GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument * pDoc = pApp->m_pDocTemplateCpp->GetNextDoc(pos);

		POSITION pos2 = pDoc->GetFirstViewPosition();
		while (pos2 != NULL)
		{
			CView* pView = pDoc->GetNextView(pos2);
			pView->GetParentFrame()->DestroyWindow();
		}
	}
}


void CMainFrame::OnFileOpenFolder()
{
	// TODO: Add your command handler code here
	CFolderPickerDialog dlg;
	if (dlg.DoModal() == IDCANCEL)
		return;

	GetManager()->ClearSolution();

	CString strPath = dlg.GetFolderPath();

	CFileManager::SearchDrive(_T("*.*"), strPath, true, false, m_wndFileView._hSrc);
	m_wndFileView.m_wndFileView.Expand(m_wndFileView._hSrc, TVE_EXPAND);

	//m_bOpenFolder = true;
}


void CMainFrame::OnFileCloseFolder()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	this->OnFileCloseSolution();
	this->CloseAllDocuments();

	//m_bOpenFolder = false;
}

