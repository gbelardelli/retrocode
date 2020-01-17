/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCodeWorkspace.h
	Author:		Gianluca Belardelli
	Date:		13/01/2020

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
#ifndef _RETROCODEWORKSPACE_H_
#define _RETROCODEWORKSPACE_H_

#include <RetroCodeEditor.h>

class RetroCodeWorkspace
{
private:
	static RetroCodeWorkspace *m_lpUniqueWSInstance;

	std::vector<RetroCodeProject *>m_vcWorkspaceProjects;
	RetroCodeProject *m_lpActiveProject;

private:
	RetroCodeWorkspace(void);
	//int _createProjectFile(IRetroCodeProjectTypePlugin *lpPlugin, IRetroCodeProject *lpNewPrj);
public:
	~RetroCodeWorkspace(void);
	static RetroCodeWorkspace *GetHinstance(void);
	
	int CreateAndLoadProject(RetroCodeProjectTypePlugin *lpPlugin, CString strPrjName, CString strPrjPath, int uiPrjId = -1);
	int LoadProject(CString strFilename);
	int SaveProject(void);
	int SaveAsProject(CString strNewPrjName);
	int SaveAllProjects(void);
	int CloseProject(void);

	int BuildProject(void);
	int BuildAndRunProject(void);
	int BuildAll(void);

	void SetActiveProject(RetroCodeProject *lpPrj);
	RetroCodeProject *GetActiveProject(void);

	int GetNumProjects(void);
	void AddProject(RetroCodeProject *lpPrj, bool bSetActive = false);
};

#endif
// _RETROCODEWORKSPACE_H_
