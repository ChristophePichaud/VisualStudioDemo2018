// CAboutDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VisualStudioDemo.h"
#include "CAboutDialog.h"


// CAboutDialog dialog

IMPLEMENT_DYNAMIC(CAboutDialog, CDialogEx)

CAboutDialog::CAboutDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ABOUT, pParent)
{

}

CAboutDialog::~CAboutDialog()
{
}

void CAboutDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDialog, CDialogEx)
END_MESSAGE_MAP()


// CAboutDialog message handlers
