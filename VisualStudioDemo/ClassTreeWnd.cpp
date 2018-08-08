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
// ClassTreeWnd.cpp : implementation file
//

#include "stdafx.h"
#include "VisualStudioDemo.h"
#include "ClassTreeWnd.h"
#include "ClassViewBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassTreeWnd

CClassTreeWnd::CClassTreeWnd()
{
}

CClassTreeWnd::~CClassTreeWnd()
{
}

BEGIN_MESSAGE_MAP(CClassTreeWnd, CBCGPTreeCtrl)
	//{{AFX_MSG_MAP(CClassTreeWnd)
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassTreeWnd message handlers

BOOL CClassTreeWnd::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	BOOL bRes = CBCGPTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT (pNMHDR != NULL);

	if (pNMHDR->code == TTN_SHOW && GetToolTips () != NULL)
	{
		GetToolTips ()->SetWindowPos (&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CClassTreeWnd::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);

	/*
	CClassViewBar* pParentPane = DYNAMIC_DOWNCAST(CClassViewBar, GetOwner());
	if (pParentPane->GetSafeHwnd() != NULL)
	{
		pParentPane->FillClassMembers(GetSelectedItem());
	}
	*/

	*pResult = 0;	
}

