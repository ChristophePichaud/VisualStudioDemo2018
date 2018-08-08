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
// BCGPVisualStudioGUIDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VisualStudioDemo.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "VisualStudioDemoDoc.h"
#include "VisualStudioDemoView.h"
#include "NewFileDlg.h"
#include "CAboutDIalog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int  iMaxUserToolbars		= 10;
const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoApp

BEGIN_MESSAGE_MAP(CBCGPVisualStudioGUIDemoApp, CBCGPWinApp)
	//{{AFX_MSG_MAP(CBCGPVisualStudioGUIDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_VIEW_APP_LOOK, OnViewAppLook)
	ON_COMMAND(ID_MDI_TABS_FILE_CLOSE, OnMdiTabsFileClose)
	ON_UPDATE_COMMAND_UI(ID_MDI_TABS_FILE_CLOSE, OnUpdateMdiTabsFileClose)
	ON_COMMAND(ID_WINDOW_CLOSE_ALL, OnWindowCloseAll)
	ON_COMMAND(ID_WINDOW_MANAGER, OnWindowManager)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_OPEN, CBCGPWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CBCGPWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_NEWEMPTY, &CBCGPVisualStudioGUIDemoApp::OnFileNewEmpty)
	ON_COMMAND(ID_FILE_NEW, &CBCGPVisualStudioGUIDemoApp::OnFileNew)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoApp construction

CBCGPVisualStudioGUIDemoApp::CBCGPVisualStudioGUIDemoApp()
{
	CBCGPDockingControlBar::m_bIgnoreRectOnShow = TRUE;

	m_pDocTemplateCpp = NULL;

	m_bHiColorIcons = FALSE;
	m_b2012Icons = FALSE;
	m_bExplorerThemeTrees = FALSE;
	m_bDockingPaneIcons = TRUE;

	CBCGPToolbarOptions toolbarOptions;
	
	toolbarOptions.m_nViewToolbarsMenuEntryID = ID_VIEW_TOOLBARS;
	toolbarOptions.m_nCustomizeCommandID = ID_VIEW_CUSTOMIZE;
	toolbarOptions.m_strCustomizeCommandLabel = _T("Customize...");
	toolbarOptions.m_strToolbarCustomIconsPath = _T(".\\UserImages.bmp");
	toolbarOptions.m_nUserToolbarCommandIDFirst = uiFirstUserToolBarId;
	toolbarOptions.m_nUserToolbarCommandIDLast = uiLastUserToolBarId;
	
	SetToolbarOptions(toolbarOptions);

	SetVisualTheme(BCGP_VISUAL_THEME_VS_2013_BLUE);

	EnableMouseWheelInInactiveWindow();
}

CBCGPVisualStudioGUIDemoApp::~CBCGPVisualStudioGUIDemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPVisualStudioGUIDemoApp object

CBCGPVisualStudioGUIDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoApp initialization

BOOL CBCGPVisualStudioGUIDemoApp::InitInstance()
{
	CBCGPWinApp::InitInstance();

	globalData.m_bUseVisualManagerInBuiltInDialogs = TRUE;

	// The File Manager
	m_pManager = std::make_shared<CFileManager>();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

 	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER < 1400
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("BCGSoft\\BCGControlBarPro\\Examples"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	SetRegistryBase (_T("Settings21"));

	EnableUserTools (ID_TOOLS_ENTRY, ID_USER_TOOL1, ID_USER_TOOL10, 
					RUNTIME_CLASS (CBCGPUserTool), IDR_MENU_ARGS, IDR_MENU_DIRS);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pDocTemplateCpp = new CMultiDocTemplate(
		IDR_BCGDEVTYPE_CPP,
		RUNTIME_CLASS(CBCGPVisualStudioGUIDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CBCGPVisualStudioGUIDemoView));
	AddDocTemplate (m_pDocTemplateCpp);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;

	EnableLoadWindowPlacement (FALSE);

	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
	{
		if (!pMainFrame->LoadMDIState (GetRegSectionPath ()))
		{
			pMainFrame->ShowStartPage (TRUE);
		}
	}
	else
	{
		// Dispatch commands specified on the command line
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
	}

	m_pMainWnd->DragAcceptFiles();

	// The main window has been initialized, so show and update it.
	if (!ReloadWindowPlacement (pMainFrame))
	{
		pMainFrame->ShowWindow(m_nCmdShow);
		pMainFrame->UpdateWindow();
	}

	pMainFrame->SendMessageToDescendants(WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0, TRUE, TRUE);

	return TRUE;
}

// App command to run the dialog
void CBCGPVisualStudioGUIDemoApp::OnAppAbout()
{
	//BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
	CAboutDialog dlg;
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// Customization load/save methods

void CBCGPVisualStudioGUIDemoApp::PreLoadState ()
{
	GetContextMenuManager()->AddMenu (_T("Edit Context menu"), IDR_CONTEXT_MENU);
	GetContextMenuManager()->AddMenu (_T("Edit Left Bar menu"), IDR_POPUP_SELECTIONMARGIN);
	GetContextMenuManager()->AddMenu (_T("Resource"), IDR_POPUP_RESOURCE);
	GetContextMenuManager()->AddMenu (_T("Solution Explorer"), IDR_POPUP_SOLUTION);
}

void CBCGPVisualStudioGUIDemoApp::OnBeforeChangeVisualTheme(CBCGPAppOptions& appOptions, CWnd* pMainWnd)
{
	CBCGPWinApp::OnBeforeChangeVisualTheme(appOptions, pMainWnd);
}

void CBCGPVisualStudioGUIDemoApp::OnAfterChangeVisualTheme(CWnd* pMainWnd)
{
	CBCGPWinApp::OnAfterChangeVisualTheme(pMainWnd);

	CBCGPMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST(CBCGPMDIFrameWnd, pMainWnd);
	if (pMainFrame->GetSafeHwnd() != NULL)
	{
		if (pMainFrame->IsFullScreen())
		{
			// Borders were probably changed - reload full screen mode:
			pMainFrame->ShowFullScreen();
			pMainFrame->ShowFullScreen();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoApp message handlers

void CBCGPVisualStudioGUIDemoApp::OnViewAppLook() 
{
}

BOOL CBCGPVisualStudioGUIDemoApp::SaveAllModified() 
{
	if (!CBCGPWinApp::SaveAllModified ())
	{
		return FALSE;
	}

	CBCGPMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CBCGPMDIFrameWnd, m_pMainWnd);
	if (pMainFrame->GetSafeHwnd() != NULL)
	{
		pMainFrame->SaveMDIState (GetRegSectionPath ());
	}

	return TRUE;
}

void CBCGPVisualStudioGUIDemoApp::OnMdiTabsFileClose()
{
	CBCGPMDIFrameWnd* pMainFrame = CBCGPMDIFrameWnd::GetActiveTearOffFrame() == NULL ?
		DYNAMIC_DOWNCAST (CBCGPMDIFrameWnd, m_pMainWnd) :
		CBCGPMDIFrameWnd::GetActiveTearOffFrame();

	if (pMainFrame->GetSafeHwnd() == NULL)
	{
		return;
	}

	CList<HWND, HWND> lstTabWnds;
	if (pMainFrame->GetSelectedMDIChildren(lstTabWnds) != 0)
	{
		for (POSITION pos = lstTabWnds.GetHeadPosition(); pos != NULL;)
		{
			HWND hwndTab = lstTabWnds.GetNext(pos);
			::SendMessage(hwndTab, WM_CLOSE, 0, 0);
		}
	}
}

void CBCGPVisualStudioGUIDemoApp::OnUpdateMdiTabsFileClose(CCmdUI* pCmdUI)
{
	CBCGPMDIFrameWnd* pMainFrame = CBCGPMDIFrameWnd::GetActiveTearOffFrame() == NULL ?
		DYNAMIC_DOWNCAST (CBCGPMDIFrameWnd, m_pMainWnd) :
		CBCGPMDIFrameWnd::GetActiveTearOffFrame();
	
	if (pMainFrame->GetSafeHwnd() != NULL)
	{
		CList<HWND, HWND> lstTabWnds;
		if (pMainFrame->GetSelectedMDIChildren(lstTabWnds) > 1)
		{
			pCmdUI->SetText(_T("&Close Selected"));
		}
	}
}

void CBCGPVisualStudioGUIDemoApp::OnWindowCloseAll() 
{
	if (BCGPMessageBox(_T("Do you really want to close all tabs?"), MB_YESNO) == IDYES)
	{
		if (m_pDocManager != NULL)
		{
			if (m_pDocManager->SaveAllModified())
			{
				m_pDocManager->CloseAllDocuments(FALSE);
			}
		}
	}
}

void CBCGPVisualStudioGUIDemoApp::OnWindowManager() 
{
	CBCGPMDIFrameWnd* pMainFrame = CBCGPMDIFrameWnd::GetActiveTearOffFrame() == NULL ?
		DYNAMIC_DOWNCAST (CBCGPMDIFrameWnd, m_pMainWnd) :
		CBCGPMDIFrameWnd::GetActiveTearOffFrame();
	
	if (pMainFrame->GetSafeHwnd() != NULL)
	{
		pMainFrame->ShowWindowsDialog();
	}
}


void CBCGPVisualStudioGUIDemoApp::OnFileNewEmpty()
{
	// TODO: Add your command handler code here
	m_pDocTemplateCpp->OpenDocumentFile(NULL);
}


void CBCGPVisualStudioGUIDemoApp::OnFileNew()
{
	// TODO: Add your command handler code here
	CBCGPVisualStudioGUIDemoDoc * pDoc = (CBCGPVisualStudioGUIDemoDoc *)m_pDocTemplateCpp->CreateNewDocument();
	pDoc->OnNewDocumentWithName();
}
