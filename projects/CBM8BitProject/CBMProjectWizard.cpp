// CBMProjectWizard.cpp: file di implementazione
//

#include "stdafx.h"
#include <RetroCodeEditor.h>
#include "CBM8BitProject.h"
#include "CBMProjectWizard.h"
#include "afxdialogex.h"


// Finestra di dialogo CBMProjectWizard

IMPLEMENT_DYNAMIC(CBMProjectWizard, AWCDialog)

CBMProjectWizard::CBMProjectWizard(CWnd* pParent /*=nullptr*/)
	: AWCDialog(IDD_DIALOG1, pParent)
{

}

CBMProjectWizard::~CBMProjectWizard()
{
}

void CBMProjectWizard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBMProjectWizard, AWCDialog)
END_MESSAGE_MAP()


// Gestori di messaggi di CBMProjectWizard
