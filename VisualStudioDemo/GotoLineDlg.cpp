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
// GotoLineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualStudioDemo.h"
#include "GotoLineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGotoLineDlg dialog


CGotoLineDlg::CGotoLineDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CGotoLineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGotoLineDlg)
	m_nLineNumber = 1;
	//}}AFX_DATA_INIT

	EnableVisualManagerStyle(TRUE, TRUE);
}


void CGotoLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGotoLineDlg)
	DDX_Text(pDX, IDC_LINE, m_nLineNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGotoLineDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CGotoLineDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGotoLineDlg message handlers
