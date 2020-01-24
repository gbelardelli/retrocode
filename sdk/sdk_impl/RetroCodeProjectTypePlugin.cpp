/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCodeProjectTypePlugin.cpp
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
#include "stdafx.h"
#include <RetroCodeEditor.h>

int RetroCodeProjectTypePlugin::CreateProject(RetroCodeProject **newProject, CString strPrjName, CString strPrjPath, int nPrjID )
{
	// Normalize path
	CString normalPath = strPrjPath;
	if (normalPath.GetAt(normalPath.GetLength() - 1) != '\\')
		normalPath += "\\";

	CString fullPath = normalPath;
	fullPath += strPrjName;
	fullPath += ".rcproj";

	DWORD dwAttr = GetFileAttributes(normalPath);
	// Check path exists and is a dir.
	if (dwAttr == INVALID_FILE_ATTRIBUTES || !(dwAttr & FILE_ATTRIBUTE_DIRECTORY))
		return 1;

	// Check if file already exists
	if (GetFileAttributes(fullPath) != INVALID_FILE_ATTRIBUTES)
		return 2;

	HINSTANCE hOld = AfxGetResourceHandle();
	AfxSetResourceHandle(this->GetPluginHinstance());
	int nRes = onCreateProject(newProject, nPrjID);
	AfxSetResourceHandle(hOld);

	if (nRes != 0)
		return nRes;

	RetroCodeProject *lpPrj = *newProject;
	if(*newProject)
	{
		(*newProject)->setProjectName(strPrjName);
		(*newProject)->setProjectPath(normalPath);
		(*newProject)->setFullFilename(fullPath);
		(*newProject)->setProjectID(nPrjID);
		(*newProject)->setProjectArch(GetProjectTypeArch());
		(*newProject)->createRootItem();
		(*newProject)->setPluginName(GetName());
		(*newProject)->onNewProject();
		(*newProject)->SaveProject();
	}

	return 0;
}