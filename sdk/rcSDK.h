// rcSDK.h: file di intestazione principale per la DLL di rcSDK
//

#pragma once

#ifndef __AFXWIN_H__
	#error "inclusione di 'stdafx.h' del file corrente per PCH"
#endif

#include "resource.h"		// simboli principali


// CrcSDKApp
// Per l'implementazione di questa classe, vedere rcSDK.cpp
//

class CrcSDKApp : public CWinApp
{
public:
	CrcSDKApp();

// Override
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
