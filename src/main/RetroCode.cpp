/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCode.cpp
	Author:		Gianluca Belardelli
	Date:		08/01/2020

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
#include <stdafx.h>
#include <afxwinappex.h>
#include <afxdialogex.h>

#include <RetroCodeEditor.h>
#include "RetroCode.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "RetroCodeDoc.h"

#include <views\RetroCodeView.h>
#include <managers\PluginManager.h>
#include <dialogs\NewProjectDlg.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRetroCodeApp

BEGIN_MESSAGE_MAP(CRetroCodeApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CRetroCodeApp::OnAppAbout)
	// Comandi di documenti basati su file standard
	//ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Comando di stampa standard
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_NEW, &CRetroCodeApp::OnFileNew)
	ON_COMMAND(ID_FILE_NUOVOFILE32803, &CRetroCodeApp::OnNewFile)
END_MESSAGE_MAP()


// Costruzione di CRetroCodeApp

extern "C"
{
	int tassMain(int argc, wchar_t *argv2);
}

CRetroCodeApp::CRetroCodeApp() noexcept
{
	m_bHiColorIcons = TRUE;

	// supporto Gestione riavvio
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Se l'applicazione è compilata mediante il supporto CLR (/clr):
	//     1) Questa ipostazione è necessaria per il corretto funzionamento del supporto di Gestione riavvio.
	//     2) Nel progetto è necessario aggiungere un riferimento a System.Windows.Forms per eseguire la compilazione.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: sostituire la stringa dell'ID applicazione seguente con una stringa di ID univoca; il formato consigliato
	// per la stringa è NomeSocietà.NomeProdotto.Sottoprodotto.Versione
	SetAppID(_T("retroCode.AppID.NoVersion"));

	// TODO: aggiungere qui il codice di costruzione.
	// Inserire l'inizializzazione significativa in InitInstance.
	m_hSciDLL = nullptr;

	//int res = tassMain(1, _T("test.prg"));
	//printf("res : %d\n", res);
	
}

// Unico oggetto CRetroCodeApp

CRetroCodeApp theApp;


// Inizializzazione di CRetroCodeApp

BOOL CRetroCodeApp::InitInstance()
{
	// InitCommonControlsEx() è necessario in Windows XP se nel manifesto
	// di un'applicazione è specificato l'utilizzo di ComCtl32.dll versione 6 o successiva per abilitare
	// gli stili visuali.  In caso contrario, non sarà possibile creare finestre.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Effettuare questa impostazione in modo da includere tutte le classi di controlli comuni da utilizzare
	// nell'applicazione.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Inizializzare le librerie OLE.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	m_hSciDLL = LoadLibraryFromApplicationDirectory(SCILEX_LIBRARY_NAME);
	if (m_hSciDLL == nullptr)
	{
		AfxMessageBox(_T("Scintilla DLL is not installed, Please download the SciTE editor and copy the SciLexer.dll into this application's directory"));
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// Per usare il controllo RichEdit, è richiesto AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// Inizializzazione standard
	// Se non si utilizzano queste funzionalità e si desidera ridurre la dimensione
	// dell'eseguibile finale, è necessario rimuovere dal seguente codice
	// le specifiche routine di inizializzazione che non sono necessarie.
	// Modificare la chiave del Registro di sistema in cui sono memorizzate le impostazioni
	// TODO: è necessario modificare questa stringa in modo appropriato,
	// inserendo ad esempio il nome della società o dell'organizzazione.
	SetRegistryKey(_T("Applicazioni locali generate tramite la Creazione guidata applicazioni"));
	LoadStdProfileSettings(6);  // Caricare le opzioni del file INI standard (inclusa MRU).


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Registrare i modelli di documenti dell'applicazione.  I modelli di documenti
	//  funzionano da connessione tra documenti, finestre cornice e viste.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CRetroCodeDoc),
		RUNTIME_CLASS(CChildFrame), // frame MDI figlio personalizzato
		RUNTIME_CLASS(CRetroCodeView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// creare finestra cornice MDI principale.
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	PluginManager::LoadPlugins(_T("plugins"), this);

	// richiamare DragAcceptFiles solo se è presente un suffisso.
	//  In un'applicazione MDI questo deve verificarsi immediatamente dopo l'impostazione di m_pMainWnd.
	// Abilitare il trascinamento della selezione.
	m_pMainWnd->DragAcceptFiles();

	// Analizzare la riga di comando per i comandi shell standard, DDE, apri file
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Abilitare apertura esecuzione DDE.
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Invia i comandi specificati nella riga di comando.  Restituisce FALSE se
	// l'applicazione è stata avviata con l'opzione /RegServer, /Register, /Unregserver o /Unregister.
	
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// La finestra principale è stata inizializzata, quindi è possibile visualizzarla e aggiornarla.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CRetroCodeApp::ExitInstance()
{
	//TODO: gestire le altre risorse eventualmente aggiunte.
	AfxOleTerm(FALSE);
	if (m_hSciDLL)
	{
		FreeLibrary(m_hSciDLL);
		m_hSciDLL = nullptr;
	}
	return CWinAppEx::ExitInstance();
}

HMODULE CRetroCodeApp::LoadLibraryFromApplicationDirectory(LPCTSTR lpFileName)
{
	//Get the Application diretory
	CString sFullPath;
	const int nGMFN = GetModuleFileName(nullptr, sFullPath.GetBuffer(_MAX_PATH), _MAX_PATH);
	sFullPath.ReleaseBuffer();
	if (nGMFN == 0)
		//#pragma warning(suppress: 26487)
		return nullptr;

	//Form the new path
	CString sDrive;
	CString sDir;
	_tsplitpath_s(sFullPath, sDrive.GetBuffer(_MAX_DRIVE), _MAX_DRIVE, sDir.GetBuffer(_MAX_DIR), _MAX_DIR, nullptr, 0, nullptr, 0);
	sDir.ReleaseBuffer();
	sDrive.ReleaseBuffer();
	CString sFname;
	CString sExt;
	_tsplitpath_s(lpFileName, nullptr, 0, nullptr, 0, sFname.GetBuffer(_MAX_FNAME), _MAX_FNAME, sExt.GetBuffer(_MAX_EXT), _MAX_EXT);
	sExt.ReleaseBuffer();
	sFname.ReleaseBuffer();
	_tmakepath_s(sFullPath.GetBuffer(_MAX_PATH), _MAX_PATH, sDrive, sDir, sFname, sExt);
	sFullPath.ReleaseBuffer();

	//Delegate to LoadLibrary
//#pragma warning(suppress: 26487)
	return LoadLibrary(sFullPath);
}
// Gestori di messaggi di CRetroCodeApp


// finestra di dialogo CAboutDlg utilizzata per visualizzare le informazioni sull'applicazione.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dati della finestra di dialogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // supporto DDX/DDV

// Implementazione
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// comando dell'applicazione per eseguire la finestra di dialogo
void CRetroCodeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Metodi di caricamento/salvataggio personalizzazione di CRetroCodeApp

void CRetroCodeApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CRetroCodeApp::LoadCustomState()
{
}

void CRetroCodeApp::SaveCustomState()
{
}

// Gestori di messaggi di CRetroCodeApp





void CRetroCodeApp::OnFileNew()
{
	POSITION pos = GetFirstDocTemplatePosition();
	CDocTemplate *lpDocTemplate = GetNextDocTemplate(pos);
	
	NewProjectDlg dlg(true);
	int nModalResult = dlg.DoModal();
	if( nModalResult == IDOK)
	{
		//CWinAppEx::OnFileNew();
		//pos = lpDocTemplate->GetFirstDocPosition();
		//int ndoc = GetOpenDocumentCount();
		//CDocument *lpDoc = lpDocTemplate->CreateNewDocument();
		//ndoc = GetOpenDocumentCount();
		//lpDoc->OnNewDocument();
		//CDocument *lpDoc = lpDocTemplate->GetNextDoc(pos);

	}
}


void CRetroCodeApp::OnNewFile()
{
	NewProjectDlg dlg(true);
	dlg.DoModal();
}


CDocument* CRetroCodeApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	// TODO: aggiungere qui il codice specifico e/o chiamare la classe di base

	return CWinAppEx::OpenDocumentFile(lpszFileName);
}
