// rcSDK.cpp: definisce le routine di inizializzazione per la DLL.
//

#include "stdafx.h"
#include "rcSDK.h"

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

// CrcSDKApp

BEGIN_MESSAGE_MAP(CrcSDKApp, CWinApp)
END_MESSAGE_MAP()


// Costruzione di CrcSDKApp

CrcSDKApp::CrcSDKApp()
{
	// TODO: aggiungere qui il codice di costruzione.
	// Inserire l'inizializzazione significativa in InitInstance.
}


// Unico oggetto CrcSDKApp

CrcSDKApp theApp;


// Inizializzazione di CrcSDKApp

BOOL CrcSDKApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
