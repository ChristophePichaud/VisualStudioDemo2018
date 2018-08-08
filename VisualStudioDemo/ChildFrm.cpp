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
// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "VisualStudioDemo.h"
#include "VisualStudioDemoDoc.h"
#include "MainFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CBCGPMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CBCGPMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	ON_WM_MDIACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~WS_SYSMENU;

	if( !CBCGPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

HICON hViewIcon = NULL;

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CBCGPMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	hViewIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), MAKEINTRESOURCE (IDI_CLASS_VIEW_HC), IMAGE_ICON, 
		::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	return 0;
}

void CChildFrame::ActivateFrame(int nCmdShow) 
{
	nCmdShow = SW_MAXIMIZE;
	CBCGPMDIChildWnd::ActivateFrame(nCmdShow);
}

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CBCGPMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	
	if (bActivate)
	{
		SetAppState();
	}
	else if (DYNAMIC_DOWNCAST(CChildFrame, pActivateWnd) == NULL)
	{
		CBCGPVisualManagerVS2012::SetStateColorRGB((COLORREF)-1);
	}
}

void CChildFrame::SetAppState()
{
	CMainFrame* pMainFrame = DYNAMIC_DOWNCAST(CMainFrame, GetTopLevelFrame());
	if (pMainFrame != NULL)
	{
		ASSERT_VALID(pMainFrame);

		COLORREF clrState = (COLORREF)-1;

		if (pMainFrame->IsShowApplicationState())
		{
			CBCGPVisualStudioGUIDemoDoc* pDoc = DYNAMIC_DOWNCAST(CBCGPVisualStudioGUIDemoDoc, GetActiveDocument());
			if (pDoc != NULL)
			{
				clrState = pDoc->GetStateColor();
			}
			else	// Assume Start Page
			{
				clrState = RGB(104, 33, 122);
			}
		}

		CBCGPVisualManagerVS2012::SetStateColorRGB(clrState);
	}
}

