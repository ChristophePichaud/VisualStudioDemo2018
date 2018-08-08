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
// ToolBox.cpp: implementation of the CResourceViewBar class.
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "ToolBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBoxBar

CToolBoxBar::CToolBoxBar()
{
}

CToolBoxBar::~CToolBoxBar()
{
}

BEGIN_MESSAGE_MAP(CToolBoxBar, CBCGPToolBoxEx)
	//{{AFX_MSG_MAP(CToolBoxBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CToolBoxBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPToolBoxEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	AddToolsPage (_T("Windows Forms"), IDB_TOOLS_PAGE1_HC, 16, 
		_T("Pointer\nLabel\nButton\nText Box\nMain Menu\nCheck Box\nRadio Button\nGroup Box\nPicture Box\nPanel\nData Grid\nList Box\nChecked List Box\nCombo Box\nList View\nTree View\nTab Control\nDate Time Picker\nMonth Calendar\nHorizontal Scroll Bar\nVertical Scroll Bar\nTimer\nSplitter\nDomain UpDown\nNumeric UpDown\nTrack Bar\nProgress Bar\nRich Text Box"));
	AddToolsPage (_T("Components"),	IDB_TOOLS_PAGE2_HC, 16, _T("Pointer\nData Set\nOleDb Data Adapter\nOleDb Connection"));
	AddToolsPage (_T("Data"),	IDB_TOOLS_PAGE3_HC, 16, _T("Pointer\nFile System Watch\nEvent Log\nDirectory Entry"));

	return 0;
}

void CToolBoxBar::ReloadIcons()
{
	GetPage(0)->UpdateImageList(theApp.m_b2012Icons ? IDB_TOOLS_PAGE1_2012 : theApp.m_bHiColorIcons ? IDB_TOOLS_PAGE1_HC : IDB_TOOLS_PAGE1);
	GetPage(1)->UpdateImageList(theApp.m_b2012Icons ? IDB_TOOLS_PAGE2_2012 : theApp.m_bHiColorIcons ? IDB_TOOLS_PAGE2_HC : IDB_TOOLS_PAGE2);
	GetPage(2)->UpdateImageList(theApp.m_b2012Icons ? IDB_TOOLS_PAGE3_2012 : theApp.m_bHiColorIcons ? IDB_TOOLS_PAGE3_HC : IDB_TOOLS_PAGE3);
}
