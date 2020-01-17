/*****************************************************************************

	RetroCode - An IDE for retro development

	CBM8BitProjectType.h
	Author:		Gianluca Belardelli
	Date:		10/01/2020

	Copyright(c) 2019-2020 by Gianluca Belardelli.
	All Rights Reserved

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/
#ifndef _CBM8BITPROJECTTYPE_
#define _CBM8BITPROJECTTYPE_

#include "resource.h"		// simboli principali

class C64Project;

class CBM8BitProjectType : public RetroCodeProjectTypePlugin
{
private:
	int m_c64PrjID;
	int m_c128PrjID;
	int m_vic20PrjID;

	CString m_strName;
	AWCDialog *m_lpWizardDlg;

	C64Project	*m_lpC64Prj;

protected:
	virtual int onCreateProject(RetroCodeProject **newProject, int nPrjID);

public:
	CBM8BitProjectType();
	virtual ~CBM8BitProjectType();

	// Override IPlugin
	virtual wchar_t    		*GetDescription(void);
	virtual wchar_t			*GetName(void);
	virtual unsigned long	GetVersion(void);
	virtual RCPLUGINTYPES	GetPluginType(void);
	virtual bool			InitPlugin(void *lpParam);
	virtual bool			ShutdownPlugin(void *lpParam);

	// Override IRetroCodeProjectTypePlugin
	virtual CString &GetProjectTypeDescription(void);
	virtual CString	&GetProjectTypeName(void);
	virtual ArchitectureType GetProjectTypeArch(void);
	virtual AWCDialog *GetProjectTypeDialog(void);

	//virtual RetroCodeProject *CreateProject(CString strPrjName, CString strPrjPath, int nPrjID = -1);

	virtual int RegisterTools(void);
	virtual int RegisterItemTypes(void);
	virtual int RegisterEditors(void);
	virtual int RegisterSideWindows(void);
	virtual int RegisterOutputWindows(void);

	virtual int RegisterBuildChain(void);
	virtual int RegisterEmulator(void);

};

#endif
// _CBM8BITPROJECTTYPE_