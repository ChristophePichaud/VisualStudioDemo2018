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
// AppLookDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "AppLookDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorListProp property

class CColorListProp : public CBCGPProp
{
public:
	CColorListProp(
		const CString& strName,
		UINT nID,
		LPCTSTR lpszDescr = NULL,
		DWORD dwData = 0
		) :
		CBCGPProp(strName, nID, _T(""), lpszDescr, dwData)
	{
	}

protected:
	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat)
	{
		CWnd* pWnd = CBCGPProp::CreateInPlaceEdit (rectEdit, bDefaultFormat);
		if (pWnd != NULL)
		{
			pWnd->ShowWindow (SW_HIDE);
		}

		return pWnd;
	}

	virtual CComboBox* CreateCombo (CWnd* pWndParent, CRect rect)
	{
		rect.bottom = rect.top + 400;

		CBCGPColorComboBox* pWndCombo = new CBCGPColorComboBox;
		pWndCombo->m_bVisualManagerStyle = TRUE;

		if (!pWndCombo->Create (WS_CHILD | CBS_NOINTEGRALHEIGHT | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS,
			rect, pWndParent, BCGPROPLIST_ID_INPLACE_COMBO))
		{
			delete pWndCombo;
			return NULL;
		}

		return pWndCombo;
	}

	virtual void OnDrawValue (CDC* pDC, CRect rect)
	{
		int nIndex = GetSelectedOption();
		CBCGPColorComboBox::DoDrawItem(pDC, rect, m_pWndList->GetFont(), (COLORREF)GetOptionData(nIndex), GetOption(nIndex), !IsEnabled());
	}
};

/////////////////////////////////////////////////////////////////////////////
// CAppLookDlg dialog

CAppLookDlg::CAppLookDlg(BOOL bStartup, CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CAppLookDlg::IDD, pParent),
	m_bStartup (bStartup)
{
	//{{AFX_DATA_INIT(CAppLookDlg)
	m_bShowAtStartup = FALSE;
	//}}AFX_DATA_INIT

	m_nAppLook = theApp.GetInt (_T("AppLook"), 12);
	m_nOffice2007Style = theApp.GetInt (_T("AppStyle"), 0);
	m_nOffice2010Style = theApp.GetInt (_T("AppStyle2010"), 0);
	m_nOffice2013Style = theApp.GetInt (_T("AppStyle2013"), 0);
	m_nOffice2016Style = theApp.GetInt (_T("AppStyle2016"), 0);
	m_nVS2012Style = theApp.GetInt (_T("AppStyleVS2012"), 2);
	m_bVS2012GrayIcons = theApp.GetInt (_T("GrayIcons"), FALSE);
	m_bShowAtStartup = theApp.GetInt (_T("ShowAppLookAtStartup"), TRUE);
	m_bOneNoteTabs = theApp.GetInt (_T("OneNoteTabs"), FALSE);
	m_bMultipleSelTabs = theApp.GetInt (_T("MultipleSelTabs"), TRUE);
	m_bDockTabColors = theApp.GetInt (_T("DockTabColors"), FALSE);
	m_bRoundedTabs = theApp.GetInt (_T("RoundedTabs"), FALSE);
	m_bCustomTooltips = theApp.GetInt (_T("CustomTooltips"), TRUE);
	m_nAccentColor = theApp.GetInt (_T("AccentColor"), 0);
	m_bMaximizeFloatingPanes = theApp.GetInt (_T("MaximizeFloatingPanes"), TRUE);
	m_bDblClickMaximizeFloatingPanes = theApp.GetInt (_T("DblClickMaximizeFloatingPanes"), FALSE);
	m_bShowHiddenPanesOnMouseClick = theApp.GetInt (_T("ShowHiddenPanesOnMouseClick"), FALSE);
	m_bAutoHideAnimation = theApp.GetInt (_T("AutoHideAnimation"), TRUE);
	m_bShowAppState = theApp.GetInt (_T("ShowAppState"), TRUE);

	m_pStyleProp = NULL;

	EnableVisualManagerStyle(TRUE, TRUE);
}


void CAppLookDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppLookDlg)
	DDX_Control(pDX, IDC_PROP_LIST, m_wndPropListPlaceHolder);
	DDX_Check(pDX, IDC_SHOW_AT_STARTUP, m_bShowAtStartup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppLookDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CAppLookDlg)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppLookDlg message handlers

BOOL CAppLookDlg::OnInitDialog() 
{
	LPCTSTR lpAccentColors[] =
	{
		_T("Default"),
		_T("Blue"),
		_T("Brown"),
		_T("Green"),
		_T("Lime"),
		_T("Magenta"),
		_T("Orange"),
		_T("Pink"),
		_T("Purple"),
		_T("Red"),
		_T("Teal"),
		NULL
	};

	CBCGPDialog::OnInitDialog();

	CRect rectPropList;
	m_wndPropListPlaceHolder.GetWindowRect(rectPropList);
	ScreenToClient(rectPropList);

	// Create property list:
	if (!m_wndPropList.Create (WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, rectPropList, this, IDC_PROP_LIST))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.SetPropertyColumnWidth((int)(0.6 * rectPropList.Width()));

	CBCGPProp* pProp = new CBCGPProp (_T("Application Look"), (UINT)AppLook, _T(""),
		_T("Choose a general application look"));

	pProp->AddOption (_T("Visual Studio 6.0"));
	pProp->AddOption (_T("Visual Studio.NET 2003"));
	pProp->AddOption (_T("Office 2003"));
	pProp->AddOption (_T("Visual Studio 2005"));
	pProp->AddOption (_T("Windows native look"));
	pProp->AddOption (_T("Office 2007"));
	pProp->AddOption (_T("Visual Studio 2008"));
	pProp->AddOption (_T("Carbon"));
	pProp->AddOption (_T("Visual Studio 2010"));
	pProp->AddOption (_T("Office 2010"));
	pProp->AddOption (_T("Visual Studio 2012"));
	pProp->AddOption (_T("Office 2013"));
	pProp->AddOption (_T("Visual Studio 2013/2015/2017"));
	pProp->AddOption (_T("Office 2016"));
	pProp->AllowEdit (FALSE);

	pProp->SelectOption(m_nAppLook);

	m_wndPropList.AddProperty(pProp);
	m_wndPropList.SetCurSel(pProp);

	m_pStyleProp = new CBCGPProp (_T("Style"), (UINT)Style, _T(""), _T("Choose a style"));
	m_pStyleProp->AllowEdit (FALSE);

	m_wndPropList.AddProperty(m_pStyleProp);

	pProp = new CColorListProp (_T("Accent Color"), (UINT)AccentColor, _T(""));

	for (int i = 0; lpAccentColors[i] != NULL; i++)
	{
		COLORREF clr = CLR_DEFAULT;

		if (i > 0)
		{
			CBCGPVisualManagerVS2012::AccentColor color = (CBCGPVisualManagerVS2012::AccentColor)(i - 1);
			clr = CBCGPVisualManagerVS2012::AccentColorToRGB(color);
		}

		pProp->AddOption(lpAccentColors[i], TRUE, clr);
	}

	pProp->AllowEdit (FALSE);

	pProp->SelectOption(m_nAccentColor + 1);

	m_wndPropList.AddProperty(pProp);

	m_wndPropList.AddProperty(new CBCGPProp (_T("Gray Icons (VS 2012-2017 only)"), (UINT)VS2012GrayIcons, (_variant_t)(m_bVS2012GrayIcons == TRUE)));
	m_wndPropList.AddProperty(new CBCGPProp (_T("OneNote®-style MDI tabs"), (UINT)OneNoteMDITabs, (_variant_t)(m_bOneNoteTabs == TRUE)));
	m_wndPropList.AddProperty(new CBCGPProp (_T("Multiple-selection MDI tabs"), (UINT)MultipleSelTabs, (_variant_t)(m_bMultipleSelTabs == TRUE)));
	m_wndPropList.AddProperty(new CBCGPProp (_T("Docking Tab Colors"), (UINT)DockingTabColors, (_variant_t)(m_bDockTabColors == TRUE)));
	m_wndPropList.AddProperty(new CBCGPProp (_T("3D Rounded Docking Tabs (VS 2005 theme only)"), (UINT)VS2005RoundedTabs, (_variant_t)(m_bRoundedTabs == TRUE)));
	m_wndPropList.AddProperty(new CBCGPProp (_T("Extended Tooltip"), (UINT)ExtendedToolTips, (_variant_t)(m_bCustomTooltips == TRUE)));

	m_wndPropList.AddProperty(new CBCGPProp (_T("Maximize Floating Panes"), (UINT)MaximizeFloatingPanes, (_variant_t)(m_bMaximizeFloatingPanes == TRUE)));
	m_wndPropList.AddProperty(new CBCGPProp (_T("Double-click Maximizes Floating Panes"), (UINT)DblClickMaximizeFloatingPanes, (_variant_t)(m_bDblClickMaximizeFloatingPanes == TRUE)));
	m_wndPropList.AddProperty(new CBCGPProp (_T("Show Hidden Panes on Mouse Click"), (UINT)ShowHiddenPanesOnMouseClick, (_variant_t)(m_bShowHiddenPanesOnMouseClick == TRUE)));
	m_wndPropList.AddProperty(new CBCGPProp (_T("Auto-hide Panes Animation"), (UINT)AutoHideAnimation, (_variant_t)(m_bAutoHideAnimation == TRUE)));

	m_wndPropList.AddProperty(new CBCGPProp (_T("Application State (Status Bar Special Color)"), (UINT)AppState, (_variant_t)(m_bShowAppState == TRUE)));

	CRect rectPropListClient;
	m_wndPropList.GetClientRect(rectPropListClient);

	if (m_wndPropList.GetRowHeight() * m_wndPropList.GetPropertyCount() < rectPropListClient.Height())
	{
		m_wndPropList.EnableVerticalScrollBar(FALSE);
	}

	OnAppLook ();

	m_wndPropList.SetFocus();

	if (m_bStartup)
	{
		SetLook ();

		if (!m_bShowAtStartup)
		{
			EndDialog (IDCANCEL);
			return TRUE;
		}
	}
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAppLookDlg::SetLook ()
{
	UpdateData();

	CWaitCursor wait;

	CMainFrame* pMainFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());
	if (m_bStartup && pMainFrame != NULL)
	{
		pMainFrame->SetRedraw(FALSE);
	}

	CBCGPVisualManagerVS2005::m_bRoundedAutohideButtons = FALSE;

	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;
	CBCGPTabWnd::TabCloseButtonMode mdiTabsCloseBtnMode = CBCGPTabWnd::TAB_CLOSE_BUTTON_NONE;

	BOOL bMDIActiveTabBoldFont = TRUE;

	theApp.m_bExplorerThemeTrees = FALSE;

	switch (m_nAppLook)
	{
	case 0:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2000);
		break;

	case 1:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_XP);
		break;

	case 2:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2003);
		break;

	case 3:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_VS_2005);

		if (m_bRoundedTabs)
		{
			CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D_ROUNDED;
		}

		CBCGPVisualManagerVS2005::m_bRoundedAutohideButtons = m_bRoundedTabs;
		break;

	case 4:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_DEFAULT);
		CBCGPWinXPVisualManager::m_b3DTabsXPTheme = TRUE;
		mdiTabsCloseBtnMode = CBCGPTabWnd::TAB_CLOSE_BUTTON_ACTIVE;
		break;

	case 5:
		switch (m_nOffice2007Style)
		{
		case 0:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_BLUE);
			break;

		case 1:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_BLACK);
			break;

		case 2:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_AQUA);
			break;

		case 3:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2007_SILVER);
			break;
		}

		mdiTabsCloseBtnMode = m_bOneNoteTabs ? CBCGPTabWnd::TAB_CLOSE_BUTTON_ACTIVE : CBCGPTabWnd::TAB_CLOSE_BUTTON_HIGHLIGHTED_COMPACT;
		break;

	case 6:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_VS_2008);
		break;

	case 7:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_CARBON);
		break;

	case 8:
		theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_VS_2010);
		mdiTabsCloseBtnMode = m_bOneNoteTabs ? CBCGPTabWnd::TAB_CLOSE_BUTTON_ACTIVE : CBCGPTabWnd::TAB_CLOSE_BUTTON_HIGHLIGHTED;
		bMDIActiveTabBoldFont = FALSE;
		theApp.m_bExplorerThemeTrees = TRUE;
		break;

	case 9:
		switch (m_nOffice2010Style)
		{
		case 0:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_BLUE);
			break;

		case 1:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_BLACK);
			break;

		case 2:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2010_SILVER);
			break;
		}

		mdiTabsCloseBtnMode = m_bOneNoteTabs ? CBCGPTabWnd::TAB_CLOSE_BUTTON_ACTIVE : CBCGPTabWnd::TAB_CLOSE_BUTTON_HIGHLIGHTED_COMPACT;
		break;

	case 10:
		CBCGPVisualManagerVS2012::m_bAutoGrayscaleImages = m_bVS2012GrayIcons;
		CBCGPVisualManagerVS2012::SetAccentColor((CBCGPVisualManagerVS2012::AccentColor)m_nAccentColor);

		theApp.SetVisualTheme(
			m_nVS2012Style == 0 ? CBCGPWinApp::BCGP_VISUAL_THEME_VS_2012_LIGHT : 
			m_nVS2012Style == 1 ? CBCGPWinApp::BCGP_VISUAL_THEME_VS_2012_DARK :
			CBCGPWinApp::BCGP_VISUAL_THEME_VS_2012_BLUE);

		mdiTabsCloseBtnMode = m_bOneNoteTabs ? CBCGPTabWnd::TAB_CLOSE_BUTTON_ACTIVE : CBCGPTabWnd::TAB_CLOSE_BUTTON_HIGHLIGHTED;
		bMDIActiveTabBoldFont = FALSE;
		theApp.m_bExplorerThemeTrees = m_nVS2012Style == 0 || m_nVS2012Style == 2;
		break;

	case 11:
		switch (m_nOffice2013Style)
		{
		case 0:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_WHITE);
			break;

		case 1:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_GRAY);
			break;

		case 2:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY);
			break;
		}			

		CBCGPVisualManager2013::SetAccentColor((CBCGPVisualManager2013::AccentColor)m_nAccentColor);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2013));
		
		mdiTabsCloseBtnMode = m_bOneNoteTabs ? CBCGPTabWnd::TAB_CLOSE_BUTTON_ACTIVE : CBCGPTabWnd::TAB_CLOSE_BUTTON_HIGHLIGHTED;
		bMDIActiveTabBoldFont = TRUE;
		theApp.m_bExplorerThemeTrees = TRUE;
		break;

	case 12:
		CBCGPVisualManagerVS2013::m_bAutoGrayscaleImages = m_bVS2012GrayIcons;
		CBCGPVisualManagerVS2013::SetAccentColor((CBCGPVisualManagerVS2012::AccentColor)m_nAccentColor);
		
		theApp.SetVisualTheme(
			m_nVS2012Style == 0 ? CBCGPWinApp::BCGP_VISUAL_THEME_VS_2013_LIGHT : 
			m_nVS2012Style == 1 ? CBCGPWinApp::BCGP_VISUAL_THEME_VS_2013_DARK :
			CBCGPWinApp::BCGP_VISUAL_THEME_VS_2013_BLUE);
		
		mdiTabsCloseBtnMode = m_bOneNoteTabs ? CBCGPTabWnd::TAB_CLOSE_BUTTON_ACTIVE : CBCGPTabWnd::TAB_CLOSE_BUTTON_HIGHLIGHTED;
		bMDIActiveTabBoldFont = FALSE;
		theApp.m_bExplorerThemeTrees = m_nVS2012Style == 0 || m_nVS2012Style == 2;
		break;

	case 13:
		switch (m_nOffice2016Style)
		{
		case 0:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_COLORFUL);
			break;
			
		case 1:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_DARK_GRAY);
			break;
			
		case 2:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_WHITE);
			break;

		case 3:
			theApp.SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2016_BLACK);
			break;
		}			
		
		CBCGPVisualManager2016::SetAccentColor((CBCGPVisualManager2016::AccentColor)m_nAccentColor);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2016));
		
		mdiTabsCloseBtnMode = m_bOneNoteTabs ? CBCGPTabWnd::TAB_CLOSE_BUTTON_ACTIVE : CBCGPTabWnd::TAB_CLOSE_BUTTON_HIGHLIGHTED;
		bMDIActiveTabBoldFont = TRUE;
		theApp.m_bExplorerThemeTrees = TRUE;
		break;
	}

	theApp.WriteInt (_T("AppLook"), m_nAppLook);
	theApp.WriteInt (_T("ShowAppLookAtStartup"), m_bShowAtStartup);
	theApp.WriteInt (_T("OneNoteTabs"), m_bOneNoteTabs);
	theApp.WriteInt (_T("MultipleSelTabs"), m_bMultipleSelTabs);
	theApp.WriteInt (_T("DockTabColors"), m_bDockTabColors);
	theApp.WriteInt (_T("RoundedTabs"), m_bRoundedTabs);
	theApp.WriteInt (_T("CustomTooltips"), m_bCustomTooltips);
	theApp.WriteInt (_T("AppStyle"), m_nOffice2007Style);
	theApp.WriteInt (_T("AppStyle2010"), m_nOffice2010Style);
	theApp.WriteInt (_T("AppStyle2013"), m_nOffice2013Style);
	theApp.WriteInt (_T("AppStyle2016"), m_nOffice2016Style);
	theApp.WriteInt (_T("AppStyleVS2012"), m_nVS2012Style);
	theApp.WriteInt (_T("GrayIcons"), m_bVS2012GrayIcons);
	theApp.WriteInt (_T("AccentColor"), m_nAccentColor);
	theApp.WriteInt (_T("MaximizeFloatingPanes"), m_bMaximizeFloatingPanes);
	theApp.WriteInt (_T("DblClickMaximizeFloatingPanes"), m_bDblClickMaximizeFloatingPanes);
	theApp.WriteInt (_T("ShowHiddenPanesOnMouseClick"), m_bShowHiddenPanesOnMouseClick);
	theApp.WriteInt (_T("AutoHideAnimation"), m_bAutoHideAnimation);
	theApp.WriteInt (_T("MultipleSelTabs"), m_bMultipleSelTabs);
	theApp.WriteInt (_T("ShowAppState"), m_bShowAppState);

	theApp.m_b2012Icons = FALSE;
	theApp.m_bDockingPaneIcons = TRUE;

	switch (m_nAppLook)
	{
	case 10:
	case 12:
		theApp.m_bDockingPaneIcons = FALSE;

		if (m_bVS2012GrayIcons)
		{
			theApp.m_bHiColorIcons = FALSE;
		}
		else
		{
			theApp.m_b2012Icons = TRUE;
		}
		break;

	case 11:// Office 2013
	case 13:// Office 2016
		theApp.m_b2012Icons = TRUE;

	case 2:	// Office 2003
	case 3:	// VS 2005
	case 4:	// Windows Native
	case 5:	// Office 2007
	case 6:	// VS 2008
	case 7:	// Carbon
	case 8:	// VS 2010
	case 9:	// Office 2010
		{
			CWindowDC dc (NULL);
			theApp.m_bHiColorIcons = dc.GetDeviceCaps (BITSPIXEL) >= 16;

			if (globalData.bIsWindows9x && dc.GetDeviceCaps (BITSPIXEL) == 16)
			{
				theApp.m_bHiColorIcons = FALSE;
			}

			CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		}
		break;

	default:
		theApp.m_bHiColorIcons = FALSE;
	}

	CBCGPTabbedControlBar::ResetTabs ();

	if (m_bCustomTooltips)
	{
		CBCGPToolTipParams params;
		params.m_bVislManagerTheme = TRUE;

		theApp.GetTooltipManager ()->SetTooltipParams (
			BCGP_TOOLTIP_TYPE_ALL,
			RUNTIME_CLASS (CBCGPToolTipCtrl),
			&params);
	}
	else
	{
		theApp.GetTooltipManager ()->SetTooltipParams (
			BCGP_TOOLTIP_TYPE_ALL,
			NULL,
			NULL);
	}

	if (pMainFrame != NULL)
	{
		pMainFrame->OnChangeLook (
					m_bOneNoteTabs/* OneNote tabs */,
					m_bOneNoteTabs /* MDI tab colors*/,
					m_nAppLook != 0 /* VS.NET look */,
					m_bDockTabColors /* Dock tab colors*/,
					m_nAppLook == 3 || m_nAppLook == 6	/* VS.NET 2005 MDI tabs */,
					mdiTabsCloseBtnMode,
					m_nAppLook == 3 || m_nAppLook == 6 || m_nAppLook == 7 || m_nAppLook == 8 || m_nAppLook == 10 || m_nAppLook == 11 || m_nAppLook == 12 || m_nAppLook == 13,
					bMDIActiveTabBoldFont, m_bMaximizeFloatingPanes, m_bDblClickMaximizeFloatingPanes,
					m_bShowHiddenPanesOnMouseClick, m_bAutoHideAnimation, m_bMultipleSelTabs, m_bShowAppState);

		if (m_bStartup)
		{
			pMainFrame->SetRedraw();
		}

		pMainFrame->RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW | RDW_ALLCHILDREN);
	}

	OnChangeVisualManager(0, 0);
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW | RDW_ALLCHILDREN);
}

LRESULT CAppLookDlg::OnPropertyChanged (WPARAM,LPARAM lParam)
{
	CBCGPProp* pProp = (CBCGPProp*) lParam;
	ASSERT_VALID(pProp);

	PropID id = (PropID)pProp->GetID();

	switch (id)
	{
	case AppLook:
		m_nAppLook = pProp->GetSelectedOption();
		OnAppLook();
		break;

	case Style:
		switch (m_nAppLook)
		{
		case 5:
			m_nOffice2007Style = pProp->GetSelectedOption();
			break;
		case 9:
			m_nOffice2010Style = pProp->GetSelectedOption();
			break;
		case 10:
		case 12:
			m_nVS2012Style = pProp->GetSelectedOption();
			break;
		case 11:
			m_nOffice2013Style = pProp->GetSelectedOption();
			break;
		case 13:
			m_nOffice2016Style = pProp->GetSelectedOption();
			break;
		}
		break;

	case AccentColor:
		m_nAccentColor = pProp->GetSelectedOption() - 1;
		break;

	case VS2012GrayIcons:
		m_bVS2012GrayIcons = (bool)pProp->GetValue();
		break;

	case OneNoteMDITabs:
		m_bOneNoteTabs = (bool)pProp->GetValue();
		m_wndPropList.EnableProperty(MultipleSelTabs, !m_bOneNoteTabs);
		break;

	case MultipleSelTabs:
		m_bMultipleSelTabs = (bool)pProp->GetValue();
		break;
		
	case DockingTabColors:
		m_bDockTabColors = (bool)pProp->GetValue();
		break;

	case VS2005RoundedTabs:
		m_bRoundedTabs = (bool)pProp->GetValue();
		break;

	case ExtendedToolTips:
		m_bCustomTooltips = (bool)pProp->GetValue();
		break;

	case MaximizeFloatingPanes:
		m_bMaximizeFloatingPanes = (bool)pProp->GetValue();
		m_wndPropList.EnableProperty(DblClickMaximizeFloatingPanes, m_bMaximizeFloatingPanes);
		break;

	case DblClickMaximizeFloatingPanes:
		m_bDblClickMaximizeFloatingPanes = (bool)pProp->GetValue();
		break;

	case ShowHiddenPanesOnMouseClick:
		m_bShowHiddenPanesOnMouseClick = (bool)pProp->GetValue();
		break;

	case AutoHideAnimation:
		m_bAutoHideAnimation = (bool)pProp->GetValue();
		break;

	case AppState:
		m_bShowAppState = (bool)pProp->GetValue();
		break;
	}

	SetLook();
	return 0;
}

void CAppLookDlg::OnAppLook() 
{
	m_wndPropList.EnableProperty(VS2005RoundedTabs, m_nAppLook == 3);
	m_wndPropList.EnableProperty(MultipleSelTabs, !m_bOneNoteTabs);
	m_wndPropList.EnableProperty(VS2012GrayIcons, m_nAppLook == 10 || m_nAppLook == 12);
	m_wndPropList.EnableProperty(AccentColor, m_nAppLook == 10 || m_nAppLook == 11 || m_nAppLook == 12 || m_nAppLook == 13);
	m_wndPropList.EnableProperty(DblClickMaximizeFloatingPanes, m_bMaximizeFloatingPanes);
	m_wndPropList.EnableProperty(AppState, m_nAppLook == 10 || m_nAppLook == 11 || m_nAppLook == 12 || m_nAppLook == 13);

	m_pStyleProp->RemoveAllOptions();
	m_pStyleProp->SelectOption(-1);

	switch (m_nAppLook)
	{
	case 5:	// Office 2007
		m_pStyleProp->AddOption (_T("Office 2007 Blue"));
		m_pStyleProp->AddOption (_T("Office 2007 Black"));
		m_pStyleProp->AddOption (_T("Office 2007 Aqua"));
		m_pStyleProp->AddOption (_T("Office 2007 Silver"));
		m_pStyleProp->Enable();
		m_pStyleProp->SelectOption(m_nOffice2007Style);
		break;

	case 9:	// Office 2010
		m_pStyleProp->AddOption (_T("Office 2010 Blue"));
		m_pStyleProp->AddOption (_T("Office 2010 Black"));
		m_pStyleProp->AddOption (_T("Office 2010 Silver"));
		m_pStyleProp->Enable();
		m_pStyleProp->SelectOption(m_nOffice2010Style);
		break;

	case 10: // VS2012
		m_pStyleProp->AddOption (_T("VS 2012 Light"));
		m_pStyleProp->AddOption (_T("VS 2012 Dark"));
		m_pStyleProp->AddOption (_T("VS 2012 Blue"));
		m_pStyleProp->Enable();
		m_pStyleProp->SelectOption(m_nVS2012Style);
		break;

	case 11: // Office 2013
		m_pStyleProp->AddOption (_T("Office 2013 White"));
		m_pStyleProp->AddOption (_T("Office 2013 Light Gray"));
		m_pStyleProp->AddOption (_T("Office 2013 Dark Gray"));
		m_pStyleProp->Enable();
		m_pStyleProp->SelectOption(m_nOffice2013Style);
		break;
		
	case 12: // VS2013
		m_pStyleProp->AddOption (_T("VS Light"));
		m_pStyleProp->AddOption (_T("VS Dark"));
		m_pStyleProp->AddOption (_T("VS Blue"));
		m_pStyleProp->Enable();
		m_pStyleProp->SelectOption(m_nVS2012Style);
		break;
		
	case 13: // Office 2016
		m_pStyleProp->AddOption (_T("Office 2016 Colorful"));
		m_pStyleProp->AddOption (_T("Office 2016 Dark Gray"));
		m_pStyleProp->AddOption (_T("Office 2016 White"));
		m_pStyleProp->AddOption (_T("Office 2016 Black"));
		m_pStyleProp->Enable();
		m_pStyleProp->SelectOption(m_nOffice2016Style);
		break;
		
	default:
		m_pStyleProp->Enable(FALSE);
		break;
	}
}

void CAppLookDlg::OnCancel() 
{
	UpdateData();
	theApp.WriteInt (_T("ShowAppLookAtStartup"), m_bShowAtStartup);

	CBCGPDialog::OnCancel();
}
