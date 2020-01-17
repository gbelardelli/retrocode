// c64project.cpp: definisce le routine di inizializzazione per la DLL.
//

#include "stdafx.h"
#include <RetroCodeEditor.h>
#include "cbm8bitProject.h"

#include "ExampleDoc.h"
#include "ExampleView.h"

#include "c64Project.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: se questa DLL è collegata in modo dinamico alle DLL
//		MFC, le funzioni esportate da questa DLL che
//		vengono chiamate in MFC devono avere la macro AFX_MANAGE_STATE
//		all'inizio della funzione.
//
//		Ad esempio:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// corpo della funzione normale
//		}
//
//		È molto importante che tale macro sia presente in ciascuna
//		funzione davanti a qualsiasi chiamata MFC.  Tale macro dovrà
//		quindi essere specificato come prima istruzione all'interno della
//		funzione, precedendo anche le dichiarazioni di variabili oggetto,
//		poiché i relativi costruttori possono generare chiamate alla DLL
//		MFC.
//
//		Vedere le note tecniche 33 e 58 di MFC per ulteriori
//		informazioni.
//

// Cc64projectApp
/*
BEGIN_MESSAGE_MAP(Cc64projectApp, CWinApp)
END_MESSAGE_MAP()*/

#include "CBMProjectWizard.h"

CBM8BitProjectType::CBM8BitProjectType() :
	m_c64PrjID(-1), m_c128PrjID(-1), m_vic20PrjID(-1),
	m_strName(PRJ_NAME), m_lpWizardDlg(nullptr),
	m_lpC64Prj(nullptr)
{

}

CBM8BitProjectType::~CBM8BitProjectType()
{
	if(m_lpWizardDlg != nullptr)
		delete m_lpWizardDlg;

	if (m_lpC64Prj != nullptr)
		delete m_lpC64Prj;
}

wchar_t *CBM8BitProjectType::GetDescription(void)
{
	return L"Ciao ciao";
}

wchar_t *CBM8BitProjectType::GetName(void)
{
	LPCWSTR ret = m_strName;
	return (wchar_t *)ret;
}

RCPLUGINTYPES CBM8BitProjectType::GetPluginType(void)
{
	return RCPLUGINTYPES::RCPROJECT_PLUGIN;
}

unsigned long CBM8BitProjectType::GetVersion(void)
{
	return 1;
}

bool CBM8BitProjectType::InitPlugin(void *lpParam)
{
	/*CWinApp *app = (CWinApp *)lpParam;
	POSITION pos = app->GetFirstDocTemplatePosition();
	CDocTemplate *doc = app->GetNextDocTemplate(pos);
	pos = doc->GetFirstDocPosition();
	CDocument *docu = doc->GetNextDoc(pos);
	pos = docu->GetFirstViewPosition();
	CView *view = docu->GetNextView(pos);
	view->GetParentFrame()->GetRuntimeClass();
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(0,
		RUNTIME_CLASS(ExampleDoc),
		view->GetParentFrame()->GetRuntimeClass(), // frame MDI figlio personalizzato
		RUNTIME_CLASS(ExampleView));

	app->AddDocTemplate(pDocTemplate);*/



	int idx = RegisterPlatform(CString("Commodore 64"), ARCH_6502);
	m_c64PrjID = RegisterProjectType(CString("Default C64 Project"), CString("A normal C64 project in basic and/or assembler"), idx, this);

	idx = RegisterPlatform(CString("Commodore 128"), ARCH_6502);
	m_c128PrjID = RegisterProjectType(CString("Default C128 Project"), CString("A normal C128 project"), idx, this);

	idx = RegisterPlatform(CString("Commodore VIC-20"), ARCH_6502);
	m_vic20PrjID = RegisterProjectType(CString("Default VIC-20 Project"), CString("A normal VIC-20 project"), idx, this);

	

	return true;
}

bool CBM8BitProjectType::ShutdownPlugin(void *lpParam)
{
	return true;
}

CString &CBM8BitProjectType::GetProjectTypeDescription(void)
{
	return CString("");
}

CString	&CBM8BitProjectType::GetProjectTypeName(void)
{
	return CString("");
}

ArchitectureType CBM8BitProjectType::GetProjectTypeArch(void)
{
	return ArchitectureType::ARCH_6502;
}

AWCDialog *CBM8BitProjectType::GetProjectTypeDialog(void)
{
	return m_lpWizardDlg;
}
int CBM8BitProjectType::onCreateProject(RetroCodeProject **newProject, int nPrjID)
{
	m_lpWizardDlg = new CBMProjectWizard();
	int nModalRes = IDCANCEL;

	if (nPrjID == m_c64PrjID)
	{
		nModalRes = m_lpWizardDlg->DoModal();
		if (nModalRes == IDOK)
		{
			m_lpC64Prj = new C64Project(0);
			*newProject = m_lpC64Prj;
			return 0;
		}

		return -1;
	}
	else if (nPrjID == m_c128PrjID)
	{
	}
	else if (nPrjID == m_vic20PrjID)
	{
	}
	
	return -1;
}
/*
RetroCodeProject *CBM8BitProjectType::CreateProject(CString strPrjName, CString strPrjPath, int nPrjID)
{
	m_lpWizardDlg = new CBMProjectWizard();
	RetroCodeProject *lpPrj = nullptr;

	int nModalRes;
	if( nPrjID == m_c64PrjID )
	{
		nModalRes = m_lpWizardDlg->DoModal();
		if( nModalRes == IDOK )
		{
			lpPrj = new C64Project(5);
			lpPrj->onNewProject(strPrjName, strPrjPath);
		}
	}
	else if (nPrjID == m_c128PrjID)
	{
		nModalRes = m_lpWizardDlg->DoModal();
	}
	else if(nPrjID == m_vic20PrjID)
	{
		nModalRes = m_lpWizardDlg->DoModal();
	}

	return lpPrj;


}
*/
int CBM8BitProjectType::RegisterTools(void)
{
	return 0;
}

int CBM8BitProjectType::RegisterItemTypes(void)
{
	return 0;
}

int CBM8BitProjectType::RegisterEditors(void)
{
	return 0;
}

int CBM8BitProjectType::RegisterSideWindows(void)
{
	return 0;
}

int CBM8BitProjectType::RegisterOutputWindows(void)
{
	return 0;
}

int CBM8BitProjectType::RegisterBuildChain(void)
{
	return 0;
}

int CBM8BitProjectType::RegisterEmulator(void)
{
	return 0;
}



CBM8BitProjectType theApp;

IPlugin* PluginEntry(void *lpParam)
{
	theApp.InitPlugin(lpParam);
	return &theApp;
}