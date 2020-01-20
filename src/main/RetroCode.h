/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCode.h
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
