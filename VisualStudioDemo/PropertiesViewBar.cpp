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
// PropertiesViewBar.cpp: implementation of the CPropertiesViewBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "MainFrm.h"
#include "PropertiesViewBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesViewBar::CPropertiesViewBar()
{
	m_BorderColor = CBCGPColor::Orange;
	m_FillBrush.SetColors(CBCGPColor::LightSteelBlue, CBCGPColor::White, CBCGPBrush::BCGP_GRADIENT_RADIAL_TOP_LEFT, 0.75);
	m_TextBrush.SetColor(CBCGPColor::SteelBlue);
}

CPropertiesViewBar::~CPropertiesViewBar()
{
}

BEGIN_MESSAGE_MAP(CPropertiesViewBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CPropertiesViewBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_SORTINGPROP, OnSortingprop)
	ON_UPDATE_COMMAND_UI(ID_SORTINGPROP, OnUpdateSortingprop)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_COMMAND(ID_EXPAND, OnExpand)
	ON_UPDATE_COMMAND_UI(ID_EXPAND, OnUpdateExpand)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_COMMAND_CLICKED, OnCommandClicked)
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_MENU_ITEM_SELECTED, OnMenuItemSelected)
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_GET_MENU_ITEM_STATE, OnGetMenuItemState)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

void CPropertiesViewBar::AdjustLayout ()
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	m_wndPropList.SetWindowPos(NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	if (!m_wndPropList.Create (WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	InitPropList ();
	AdjustLayout ();

	return 0;
}

void CPropertiesViewBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (CanAdjustLayout())
	{
		AdjustLayout();
	}
}

void CPropertiesViewBar::OnSortingprop() 
{
	m_wndPropList.SetAlphabeticMode ();
}

void CPropertiesViewBar::OnUpdateSortingprop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndPropList.IsAlphabeticMode ());
}

void CPropertiesViewBar::OnExpand() 
{
	m_wndPropList.SetAlphabeticMode (FALSE);
}

void CPropertiesViewBar::OnUpdateExpand(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (!m_wndPropList.IsAlphabeticMode ());
}

void CPropertiesViewBar::OnProperties1() 
{
	// TODO: Add your command handler code here
	
}

void CPropertiesViewBar::OnUpdateProperties1(CCmdUI* /*pCmdUI*/) 
{
	// TODO: Add your command update UI handler code here
	
}

void CPropertiesViewBar::OnProperties2() 
{
	// TODO: Add your command handler code here
	
}

void CPropertiesViewBar::OnUpdateProperties2(CCmdUI* /*pCmdUI*/) 
{
	// TODO: Add your command update UI handler code here
	
}

void CPropertiesViewBar::InitPropList ()
{
	SetPropListFont ();

	// Add commands:
	CStringList lstCommands;
	lstCommands.AddTail (_T("Add New"));
	lstCommands.AddTail (_T("Remove All"));

	m_wndPropList.SetCommands (lstCommands);

	// Add custom menu items:
	CStringList lstCustomMenuItem;
	lstCustomMenuItem.AddTail (_T("Apply Data Binding..."));
	lstCustomMenuItem.AddTail (_T("Apply Resource..."));
	lstCustomMenuItem.AddTail (_T("Extract Value to Resource..."));
	lstCustomMenuItem.AddTail (_T("Go to Value Definition..."));

	m_wndPropList.SetCustomMenuItems(lstCustomMenuItem);

	// Setup general look:
	m_wndPropList.EnableToolBar();
	m_wndPropList.EnableSearchBox();
	m_wndPropList.EnableHeaderCtrl (FALSE);
	m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.MarkModifiedProperties ();
	m_wndPropList.EnableContextMenu();

	// Add properties:
	CBCGPProp* pGroup1 = new CBCGPProp (_T("Appearance"));

	pGroup1->AddSubItem (new CBCGPProp (_T("3D Look"), (_variant_t) true,
		_T("Specifies the dialog's font will be non-bold and controls will have a 3D border")));

	CBCGPProp* pProp = new CBCGPProp (_T("Border"), _T("Dialog Frame"),
		_T("One of: None, Thin, Resizable, or Dialog Frame"));
	pProp->AddOption (_T("None"));
	pProp->AddOption (_T("Thin"));
	pProp->AddOption (_T("Resizable"));
	pProp->AddOption (_T("Dialog Frame"));
	pProp->AllowEdit (FALSE);

	pGroup1->AddSubItem (pProp);
	pGroup1->AddSubItem (new CBCGPProp (_T("Caption"), (_variant_t) _T("About BCGProTest"),
		_T("Specifies the text that will be displayed in the dialog's title bar")));

	m_wndPropList.AddProperty (pGroup1);

	CBCGPProp* pSize = new CBCGPProp (_T("Window Size"), 0, TRUE);

	pProp = new CBCGPProp (_T("Height"), (_variant_t) 250l,
							_T("Specifies the dialog's height"));
	pProp->EnableSpinControl (TRUE, 0, 1000);
	pSize->AddSubItem (pProp);

	pProp = new CBCGPProp (	_T("Width"), (_variant_t) 150l,
							_T("Specifies the dialog's width"));
	pProp->EnableSpinControl (TRUE, 0, 1000);
	pSize->AddSubItem (pProp);

	m_wndPropList.AddProperty (pSize);

	CBCGPProp* pGroup2 = new CBCGPProp (_T("Font"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle ((HFONT) GetStockObject (DEFAULT_GUI_FONT));
	font->GetLogFont (&lf);

	lstrcpy (lf.lfFaceName, _T("Arial"));

	pGroup2->AddSubItem (new CBCGPFontProp (_T("Font"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("Specifies the default font for the dialog")));
	pGroup2->AddSubItem (new CBCGPProp (_T("Use System Font"), (_variant_t) false, _T("Specifies that the dialog uses MS Shell Dlg font")));

	m_wndPropList.AddProperty (pGroup2);

	CBCGPProp* pGroup3 = new CBCGPProp (_T("Brushes"));

	CBCGPColorProp* pColorProp = new CBCGPColorProp (_T("Border Color"), m_BorderColor, NULL, _T("Specifies the default dialog border color"));
	pColorProp->EnableOtherButton (_T("Other..."));
	pColorProp->EnableAutomaticButton (_T("Default"), globalData.clrBarShadow);
	pGroup3->AddSubItem (pColorProp);

	pGroup3->AddSubItem (new CBCGPBrushProp (_T("Background"), m_FillBrush, NULL,
		_T("Specifies the default background")));

	pGroup3->AddSubItem (new CBCGPBrushProp (_T("Foreground"), m_TextBrush, NULL,
		_T("Specifies the default foreground")));

	m_wndPropList.AddProperty (pGroup3);

	CBCGPProp* pGroup4 = new CBCGPProp (_T("Misc"));
	pProp = new CBCGPProp (_T("(Name)"), _T("IDD_ABOUT_BOX (dialog)"));
	pProp->Enable (FALSE);
	pGroup4->AddSubItem (pProp);

	static TCHAR BASED_CODE szFilter[] = _T("Icon Files (*.ico)|*.ico|All Files (*.*)|*.*||");
	pGroup4->AddSubItem (new CBCGPFileProp (_T("Icon"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("Specifies the dialog icon")));

	pGroup4->AddSubItem (new CBCGPFileProp (_T("Folder"), _T("c:\\")));

	COleDateTime date = COleDateTime::GetCurrentTime ();
	pGroup4->AddSubItem (new CBCGPDateTimeProp (_T("Date"), date,
		_T("Set a date"), 0, CBCGPDateTimeCtrl::DTM_DATE));

	pGroup4->AddSubItem (new CBCGPDateTimeProp (_T("Time"), date,
		_T("Set a time"), 0, CBCGPDateTimeCtrl::DTM_TIME));

	m_wndPropList.AddProperty (pGroup4);

	CBCGPProp* pGroup5 = new CBCGPProp (_T("Hierarchy"));

	CBCGPProp* pGroup51 = new CBCGPProp (_T("First sub-level"));
	pGroup5->AddSubItem (pGroup51);

	CBCGPProp* pGroup511 = new CBCGPProp (_T("Second sub-level"));
	pGroup51->AddSubItem (pGroup511);

	pGroup511->AddSubItem (new CBCGPProp (_T("Item 1"), (_variant_t) _T("Value 1"),
		_T("This is a description")));
	pGroup511->AddSubItem (new CBCGPProp (_T("Item 2"), (_variant_t) _T("Value 2"),
		_T("This is a description")));
	pGroup511->AddSubItem (new CBCGPProp (_T("Item 3"), (_variant_t) _T("Value 3"),
		_T("This is a description")));

	pGroup5->Expand (FALSE);
	m_wndPropList.AddProperty (pGroup5);
}

void CPropertiesViewBar::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus ();
}

void CPropertiesViewBar::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	CBCGPDockingControlBar::OnSettingChange(uFlags, lpszSection);
	SetPropListFont ();
}

void CPropertiesViewBar::SetPropListFont ()
{
	::DeleteObject (m_fntPropList.Detach ());

	LOGFONT lf;
	globalData.fontRegular.GetLogFont (&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	globalData.GetNonClientMetrics (info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect (&lf);
	m_wndPropList.SetFont (&m_fntPropList);
}

LRESULT CPropertiesViewBar::OnCommandClicked(WPARAM, LPARAM lp)
{
	CString str;

	switch (lp)
	{
	case 0:
		str = _T("Add new control dialog");
		break;

	case 1:
		str = _T("Remove all controls dialog");
		break;
	}

	BCGPMessageBox (str);
	SetFocus();
	return 0;
}

LRESULT CPropertiesViewBar::OnGetMenuItemState(WPARAM wp, LPARAM lp)
{
	int nMenuIndex = (int)wp;

	CBCGPProp* pProp = (CBCGPProp*)lp;
	ASSERT_VALID(pProp);

	UINT nState = 0;

	switch (nMenuIndex)
	{
	case 2:	// Extract value to resource
		nState |= (MF_GRAYED | MF_CHECKED);
		break;

	case 3:	// Go to Value Definition
		nState |= MF_GRAYED;
		break;
	}

	return nState;
}

LRESULT CPropertiesViewBar::OnMenuItemSelected(WPARAM wp, LPARAM lp)
{
	int nMenuIndex = (int)wp;

	CBCGPProp* pProp = (CBCGPProp*)lp;
	ASSERT_VALID(pProp);

	CString str = _T("Unknown");

	switch (nMenuIndex)
	{
	case 0:
		str.Format (_T("Apply Data Binding.\nProperty: %s"), pProp->GetName());
		break;

	case 1:
		str.Format (_T("Apply Resource.\nProperty: %s"), pProp->GetName());
		break;
	}

	BCGPMessageBox (str);
	SetFocus();
	return 0;
}
