/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCodeProjectTypePlugin.h
	Author:		Gianluca Belardelli
	Date:		10/01/2020

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
#ifndef _RETROCODEPROJECTTYPEPLUGIN_H_
#define _RETROCODEPROJECTTYPEPLUGIN_H_

class RCIMPEXP RetroCodeProjectTypePlugin : public IPlugin
{
protected:
	virtual int onCreateProject(RetroCodeProject **newProject, int nPrjID) = 0;

public:
	virtual CString &GetProjectTypeDescription(void) = 0;
	virtual CString	&GetProjectTypeName(void) = 0;
	virtual ArchitectureType GetProjectTypeArch(void) = 0;
	virtual AWCDialog *GetProjectTypeDialog(void) = 0;

	int CreateProject(RetroCodeProject **newProject, CString strPrjName, CString strPrjPath, int nPrjID = -1 );

	virtual int RegisterTools(void) = 0;
	virtual int RegisterItemTypes(void) = 0;
	virtual int RegisterEditors(void) = 0;
	virtual int RegisterSideWindows(void) = 0;
	virtual int RegisterOutputWindows(void) = 0;

	virtual int RegisterBuildChain(void) = 0;
	virtual int RegisterEmulator(void) = 0;
};

#endif
// _RETROCODEPROJECTTYPEPLUGIN_H_

