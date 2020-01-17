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
