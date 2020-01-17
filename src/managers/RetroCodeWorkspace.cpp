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
#include <stdafx.h>
#include "RetroCodeWorkspace.h"
#include <tinyxml2.h>

RetroCodeWorkspace *RetroCodeWorkspace::m_lpUniqueWSInstance = nullptr;

RetroCodeWorkspace::RetroCodeWorkspace(void) : m_lpActiveProject(nullptr)
{
}

RetroCodeWorkspace::~RetroCodeWorkspace(void)
{
}

RetroCodeWorkspace *RetroCodeWorkspace::GetHinstance(void)
{
	if (m_lpUniqueWSInstance == nullptr)
		m_lpUniqueWSInstance = new RetroCodeWorkspace();

	return m_lpUniqueWSInstance;
}

int RetroCodeWorkspace::CreateAndLoadProject(RetroCodeProjectTypePlugin *lpPlugin, CString strPrjName, CString strPrjPath, int uiPrjId)
{
	RetroCodeProject *lpNewPrj;
	int nRes = lpPlugin->CreateProject(&lpNewPrj, strPrjName, strPrjPath, uiPrjId);
	if(!nRes)
	{
		// Set active project only if is first project in workspace
		if (m_vcWorkspaceProjects.size() == 0)
			m_lpActiveProject = lpNewPrj;

		m_vcWorkspaceProjects.push_back(lpNewPrj);
	}

	return -1;
}

int RetroCodeWorkspace::LoadProject(CString strFilename)
{
	return 0;
}

int RetroCodeWorkspace::SaveProject(void)
{
	return 0;
}

int RetroCodeWorkspace::SaveAsProject(CString strNewPrjName)
{
	return 0;
}

int RetroCodeWorkspace::SaveAllProjects(void)
{
	return 0;
}

int RetroCodeWorkspace::CloseProject(void)
{
	return 0;
}

int RetroCodeWorkspace::BuildProject(void)
{
	return 0;
}

int RetroCodeWorkspace::BuildAndRunProject(void)
{
	return 0;
}

int RetroCodeWorkspace::BuildAll(void)
{
	return 0;
}

void RetroCodeWorkspace::SetActiveProject(RetroCodeProject *lpPrj)
{
	m_lpActiveProject = lpPrj;
}

RetroCodeProject *RetroCodeWorkspace::GetActiveProject(void)
{
	return m_lpActiveProject;
}

int RetroCodeWorkspace::GetNumProjects(void)
{
	return m_vcWorkspaceProjects.size();
}

void RetroCodeWorkspace::AddProject(RetroCodeProject *lpPrj, bool bSetActive)
{
}
/*
int RetroCodeWorkspace::_createProjectFile(IRetroCodeProjectTypePlugin *lpPlugin, IRetroCodeProject *lpNewPrj)
{
	CString xml("<Project RetroCodeVersion=\"1\">\n");
	xml += "</Project>\n";
	xml += "<ProjectOptions plugin=\"";
	xml += lpPlugin->GetName();
	xml += "\">\n";
	//lpPlugin->
	xml += "</ProjectOptions>\n";

	DWORD dwAttr = GetFileAttributes(lpNewPrj->GetProjectPath());
	// Check path exists and is a dir.
	if (dwAttr== INVALID_FILE_ATTRIBUTES || !(dwAttr & FILE_ATTRIBUTE_DIRECTORY))
		return 1;

	CString fullFileName = lpNewPrj->GetProjectPath();
	if (fullFileName.GetAt(fullFileName.GetLength() - 1) != '\\')
		fullFileName += "\\";

	fullFileName += lpNewPrj->GetProjectName();
	fullFileName += ".rcproj";

	// Check if file already exists
	if (GetFileAttributes(fullFileName) != INVALID_FILE_ATTRIBUTES)
		return 2;

	CFile prjFile;
	if (!prjFile.Open(fullFileName, CFile::modeCreate | CFile::modeReadWrite))
		return 3;

	return 0;
}
*/