/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCodeEditor.cpp
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
#include <RetroCodeEditor.h>

#define _FAKEPROJECTS_

std::vector<lpPlatformType> g_vcPlatforms;
std::vector<lpProjectType> g_vcProjects;

int RegisterPlatform(CString &strPlatformName, ArchitectureType archType)
{
	lpPlatformType addPlatform = GetPlatformFromName(strPlatformName);
	if (addPlatform)
		return addPlatform->uiPlatformID;

	addPlatform = new PlatformType;
	addPlatform->atArchType = archType;
	addPlatform->strPlatformName = strPlatformName;
	addPlatform->uiPlatformID = g_vcPlatforms.size();

	g_vcPlatforms.push_back(addPlatform);
	return addPlatform->uiPlatformID;
}

lpPlatformType GetPlatformFromIndex(unsigned int index)
{
	if (index > g_vcPlatforms.size())
		return nullptr;

	return g_vcPlatforms[index];
}

lpPlatformType GetPlatformFromName(const wchar_t *lpPlatformName)
{
	const size_t nLen = g_vcPlatforms.size();
	for(int i=0; i<nLen; i++)
	{
		if (g_vcPlatforms[i]->strPlatformName.Compare(lpPlatformName) == 0)
			return g_vcPlatforms[i];
	}

	return nullptr;
}

unsigned int GetPlatformIDFromName(const wchar_t *lpPlatformName)
{
	lpPlatformType lpPlatform = GetPlatformFromName(lpPlatformName);
	if (lpPlatform)
		return lpPlatform->uiPlatformID;

	return -1;
}

int GetPlatformsCount(void)
{
	return g_vcPlatforms.size();
}

int RegisterProjectType(CString &strProjectTypeName, CString &strPrjTypeDescription, unsigned int platformID, RetroCodeProjectTypePlugin *lpPlugin, AWCDialog *lpProjectDlg)
{
	if (GetPlatformFromIndex(platformID) == nullptr)
		return -1;

	lpProjectType addPrj = new ProjectType;
	addPrj->uiPlatformID = platformID;
	addPrj->strPrjTypeName = strProjectTypeName;
	addPrj->strPrjTypeDescription = strPrjTypeDescription;
	addPrj->lpPlugin = lpPlugin;
	addPrj->lpProjectDlg = lpProjectDlg;
	addPrj->uiPrjTypeID = g_vcProjects.size();

	g_vcProjects.push_back(addPrj);
	return addPrj->uiPrjTypeID;
}

int RegisterProjectType(CString &strProjectTypeName, CString &strPrjTypeDescription, lpPlatformType lpPlatform, RetroCodeProjectTypePlugin *lpPlugin, AWCDialog *lpProjectDlg)
{
	lpProjectType addPrj = new ProjectType;
	addPrj->uiPlatformID = lpPlatform->uiPlatformID;
	addPrj->strPrjTypeName = strProjectTypeName;
	addPrj->strPrjTypeDescription = strPrjTypeDescription;
	addPrj->lpPlugin = lpPlugin;
	addPrj->lpProjectDlg = lpProjectDlg;
	addPrj->uiPrjTypeID = g_vcProjects.size();

	g_vcProjects.push_back(addPrj);
	return addPrj->uiPrjTypeID;
}

lpProjectType GetProjectTypeFromIndex(unsigned int index)
{
	if (index > g_vcProjects.size())
		return nullptr;

	return g_vcProjects[index];
}

int GetProjectTypesCount(void)
{
	return g_vcProjects.size();
}

#if defined _FAKEPROJECTS_
void RCIMPEXP fillFakeProjects()
{
	int idx = RegisterPlatform( CString("Commodore 64"), ARCH_6502 );
	RegisterProjectType( CString("C64 S.E.U.C.K. Project"), CString("A S.E.U.C.K C64 project"), idx );

	idx = RegisterPlatform(CString("Commodore 128"), ARCH_6502);
	RegisterProjectType(CString("C128 CP/M Project"), CString("A C128 project that use CP/M"), idx);
}
#else
void RCIMPEXP fillFakeProjects() {}
#endif
