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
// DockableStartPage.cpp: implementation of the CDockableStartPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VisualStudioDemo.h"
#include "DockableStartPage.h"
#include "StartView.h"
#include "ChildFrm.h"

BEGIN_MESSAGE_MAP(CDockableStartPage, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CDockableStartPage)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDockableStartPage::CDockableStartPage()
{
    m_pContext = NULL;

    CRuntimeClass* pFactory = RUNTIME_CLASS(CStartView);
    m_pStartView = (CStartView *)(pFactory->CreateObject());
}

CDockableStartPage::~CDockableStartPage()
{

}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CDockableStartPage::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (m_pStartView != NULL)
	{
		m_pStartView->CreateView(this, m_pContext);
	}

	return 0;
}

void CDockableStartPage::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	
	if (m_pStartView->GetSafeHwnd ())
	{
		m_pStartView->SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

CBCGPMDIChildWnd* CDockableStartPage::OnNewMDITabbedChildWnd(CBCGPMDIFrameWnd* /*pMainFrame*/) const
{
	return new CChildFrame;
}

