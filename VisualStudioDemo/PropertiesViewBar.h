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
// PropertiesViewBar.h: interface for the CPropertiesViewBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTIESVIEWBAR_H__91E4A4A8_1AD0_450E_841C_409767044A55__INCLUDED_)
#define AFX_PROPERTIESVIEWBAR_H__91E4A4A8_1AD0_450E_841C_409767044A55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPropertiesViewBar : public CBCGPDockingControlBar  
{
// Construction
public:
	CPropertiesViewBar();

	void AdjustLayout ();

// Attributes
public:
	void SetVSDotNetLook (BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook (bSet);
		m_wndPropList.SetGroupNameFullWidth (bSet);
	}
	
	void SetBooleanPropertiesStyle(CBCGPPropList::BooleanPropertiesStyle style)
	{
		m_wndPropList.SetBooleanPropertiesStyle(style);
	}

protected:
	CBCGPPropList		m_wndPropList;
	CFont				m_fntPropList;
	CBCGPColor			m_BorderColor;
	CBCGPBrush			m_FillBrush;
	CBCGPBrush			m_TextBrush;

// Attributes
protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesViewBar)
	//}}AFX_VIRTUAL

	virtual void GetPaneInfo(CString& strName, CString& strInfo, HICON& hIcon, BOOL& bAutoDestroyIcon)
	{
		CBCGPDockingControlBar::GetPaneInfo(strName, strInfo, hIcon, bAutoDestroyIcon);
		strInfo = _T("Displays the property pages for the item currently selected.");
		
		if (hIcon == NULL)
		{
			// Current Visual theme doesn't have docking pane icons:
			int nImage = BCGPGetCmdMgr()->GetCmdImage(ID_VIEW_PROPERTIES, FALSE);
			if (nImage >= 0)
			{
				hIcon = CBCGPToolBar::GetImages()->ExtractIcon(nImage);
				bAutoDestroyIcon = TRUE;
			}
		}
	}

// Implementation
public:
	virtual ~CPropertiesViewBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropertiesViewBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSortingprop();
	afx_msg void OnUpdateSortingprop(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnExpand();
	afx_msg void OnUpdateExpand(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//}}AFX_MSG
	afx_msg LRESULT OnCommandClicked(WPARAM, LPARAM);
	afx_msg LRESULT OnMenuItemSelected(WPARAM, LPARAM);
	afx_msg LRESULT OnGetMenuItemState(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

	void InitPropList ();
	void SetPropListFont ();
};

#endif // !defined(AFX_PROPERTIESVIEWBAR_H__91E4A4A8_1AD0_450E_841C_409767044A55__INCLUDED_)
