#pragma once


// Finestra di dialogo CBMProjectWizard

class CBMProjectWizard : public AWCDialog
{
	DECLARE_DYNAMIC(CBMProjectWizard)

public:
	CBMProjectWizard(CWnd* pParent = nullptr);   // costruttore standard
	virtual ~CBMProjectWizard();

// Dati della finestra di dialogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Supporto DDX/DDV

	DECLARE_MESSAGE_MAP()
};
