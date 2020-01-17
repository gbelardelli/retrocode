
// retroCode.h: file di intestazione principale per l'applicazione retroCode
//
#pragma once

#ifndef __AFXWIN_H__
	#error "includere 'stdafx.h' prima di includere questo file per PCH"
#endif

#include "resource.h"       // simboli principali


// CRetroCodeApp:
// Per l'implementazione di questa classe, vedere retroCode.cpp
//

class CRetroCodeApp : public CWinAppEx
{
protected:
	HINSTANCE m_hSciDLL;
	HMODULE LoadLibraryFromApplicationDirectory(LPCTSTR lpFileName);

public:
	CRetroCodeApp() noexcept;


// Override
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementazione
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileNew();
	afx_msg void OnNewFile();
};

extern CRetroCodeApp theApp;
