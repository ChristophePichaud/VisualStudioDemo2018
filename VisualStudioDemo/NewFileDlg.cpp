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
// NewFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "NewFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewFileDlg dialog

CNewFileDlg::CNewFileDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CNewFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	EnableVisualManagerStyle(TRUE, TRUE);
	EnableLayout();
	EnableLoadWindowPlacement();
}


void CNewFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewFileDlg)
	DDX_Control(pDX, IDC_TEMPLATE_LIST, m_wndTemplateList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNewFileDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CNewFileDlg)
	ON_LBN_DBLCLK(IDC_TEMPLATE_LIST, OnDblclkTemplateList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewFileDlg message handlers

BOOL CNewFileDlg::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	ASSERT_VALID(pLayout);
	
	pLayout->AddAnchor(IDC_TEMPLATE_LIST, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
	pLayout->AddAnchor(IDOK, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone);
	pLayout->AddAnchor(IDCANCEL, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone);

	m_wndTemplateList.FillList();
	GetDlgItem(IDOK)->EnableWindow(m_wndTemplateList.GetSelectedTemplate() != NULL);

	if (m_wndTemplateList.GetCount() == 1)
	{
		EndDialog(IDOK);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewFileDlg::OnDblclkTemplateList() 
{
	if (m_wndTemplateList.GetSelectedTemplate() != NULL)
	{
		OnOK();
	}
}

void CNewFileDlg::OnOK() 
{
	CDocTemplate* pTemplate = m_wndTemplateList.GetSelectedTemplate();
	ASSERT_VALID(pTemplate);
	
	pTemplate->OpenDocumentFile(NULL);
	
	CBCGPDialog::OnOK();
}
