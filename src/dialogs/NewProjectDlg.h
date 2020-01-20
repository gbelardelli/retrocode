/*****************************************************************************

	RetroCode - An IDE for retro development

	NewProjectDlg.h
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
#pragma once

#include <AWCDialog.h>
#include <AWCButton.h>

// Finestra di dialogo NewProjectDlg
#include <RetroCodeEditor.h>

class NewProjectDlg : public AWCDialog
{
	DECLARE_DYNAMIC(NewProjectDlg)

public:
	NewProjectDlg( bool bProject, CWnd* pParent = nullptr );   // costruttore standard
	virtual ~NewProjectDlg();

// Dati della finestra di dialogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWPROJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Supporto DDX/DDV
	void loadProjectsTypes();
	DECLARE_MESSAGE_MAP()

	void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
public:
	AWCButton m_btnOK;
	AWCButton m_btnCancel;
	CTreeCtrl m_prjTree;
	virtual BOOL OnInitDialog();

private:
	bool	m_bIsProject;
	lpProjectType	m_lpSelectedPrj;
public:
	CListCtrl m_prjList;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_prjDesc;
	CEdit m_prjName;
	CEdit m_prjPath;
	afx_msg void OnBnClickedOk();
};
