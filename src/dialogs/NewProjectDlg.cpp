/*****************************************************************************

	RetroCode - An IDE for retro development

	NewProjectDlg.cpp
	Author:		Gianluca Belardelli
	Date:		10/01/2020

	Copyright(c) 2018-2020 by Gianluca Belardelli.
	All Rights Reserved

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, version 3.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/
#include "stdafx.h"
#include "NewProjectDlg.h"
#include "afxdialogex.h"
#include <resource.h>
#include <AWCStyleManager.h>
#include <RetroCodeEditor.h>
#include <managers/PluginManager.h>
#include <managers/RetroCodeWorkspace.h>
// Finestra di dialogo NewProjectDlg

IMPLEMENT_DYNAMIC(NewProjectDlg, AWCDialog)

extern void fillFakeProjects();

NewProjectDlg::NewProjectDlg( bool bProject, CWnd* pParent )
	: AWCDialog(IDD_NEWPROJECT, pParent),
	m_bIsProject(bProject),
	m_lpSelectedPrj(nullptr)
{
	fillFakeProjects();
}

NewProjectDlg::~NewProjectDlg()
{
}

void NewProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_TREE1, m_prjTree);
	DDX_Control(pDX, IDC_LIST1, m_prjList);
	DDX_Control(pDX, IDC_STATICPRJDESC, m_prjDesc);
	DDX_Control(pDX, IDC_PRJNAMEEDIT, m_prjName);
	DDX_Control(pDX, IDC_PRJPATHEDIT, m_prjPath);
}


BEGIN_MESSAGE_MAP(NewProjectDlg, AWCDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnTvnSelchangedTree)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &NewProjectDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDOK, &NewProjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Gestori di messaggi di NewProjectDlg


BOOL NewProjectDlg::OnInitDialog()
{
	AWCDialog::OnInitDialog();

	// TODO:  Aggiungere qui ulteriori informazioni per l'inizializzazione
	m_prjTree.SetBkColor(AWCStyleManager::GetInstance()->GetCtrlBackgroundColor());
	m_prjTree.SetTextColor(AWCStyleManager::GetInstance()->GetWindowTextColor());
	m_prjTree.SetLineColor(AWCStyleManager::GetInstance()->GetWindowTextColor());

	m_prjList.SetBkColor(AWCStyleManager::GetInstance()->GetCtrlBackgroundColor());
	m_prjList.SetTextBkColor(AWCStyleManager::GetInstance()->GetCtrlBackgroundColor());
	m_prjList.SetTextColor(AWCStyleManager::GetInstance()->GetWindowTextColor());
	loadProjectsTypes();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ECCEZIONE: le pagine delle proprietÓ OCX devono restituire FALSE
}

void NewProjectDlg::loadProjectsTypes()
{
	const int nPlatformCount = GetPlatformsCount();

	HTREEITEM hRoot, hChild;

	hRoot = m_prjTree.InsertItem(_T("Installati"));

	for( int i=0; i<nPlatformCount; i++ )
	{
		lpPlatformType lpPlatform = GetPlatformFromIndex(i);
		hChild = m_prjTree.InsertItem( lpPlatform->strPlatformName, hRoot );
		m_prjTree.SetItemData(hChild, (DWORD_PTR)lpPlatform);
		if (i == 0)
			m_prjTree.SelectItem(hChild);
	}
}

void NewProjectDlg::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	HTREEITEM hSelectedItem = m_prjTree.GetSelectedItem();
	lpPlatformType lpPlatform = (lpPlatformType)m_prjTree.GetItemData(hSelectedItem);

	if( lpPlatform )
	{
		const int nProjectsCount = GetProjectTypesCount();
		m_prjList.DeleteAllItems();
		int nIdx = 0;

		for( int i=0; i<nProjectsCount; i++ )
		{
			lpProjectType lpPrj = GetProjectTypeFromIndex(i);
			
			if( lpPrj->uiPlatformID == lpPlatform->uiPlatformID )
			{
				nIdx = m_prjList.InsertItem(nIdx, lpPrj->strPrjTypeName);
				m_prjList.SetItemData(nIdx, (DWORD_PTR)lpPrj);
			}
		}

		if (m_prjList.GetItemCount() > 0)
			m_prjList.SetSelectionMark(0);
	}
	*pResult = 0;
}

void NewProjectDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: aggiungere qui il codice del gestore di notifiche del controllo
	lpProjectType lpPrj = (lpProjectType)pNMLV->lParam;
	if (lpPrj)
	{
		//m_prjDesc.SetWindowTextW(_T(""));
		m_prjDesc.SetWindowTextW(lpPrj->strPrjTypeDescription);
		m_lpSelectedPrj = lpPrj;
	}

	*pResult = 0;
}

void NewProjectDlg::OnBnClickedOk()
{
	// TODO: aggiungere qui il codice del gestore di notifiche del controllo
	if(m_lpSelectedPrj)
	{
		int nModalRes = IDOK;
		RetroCodeProject *lpPrj = nullptr;
		this->SetWindowPos(nullptr, 0, 0, 0, 0, SWP_HIDEWINDOW);
		if (m_lpSelectedPrj->lpPlugin)
		{
			nModalRes = RetroCodeWorkspace::GetHinstance()->CreateAndLoadProject(m_lpSelectedPrj->lpPlugin, CString("Test"), CString("C:\\MyProjects\\testpath"), m_lpSelectedPrj->uiPrjTypeID);
		}
		if( nModalRes == IDOK )
		{
			// Save & create project
		}

		EndDialog(nModalRes);
	}
}
