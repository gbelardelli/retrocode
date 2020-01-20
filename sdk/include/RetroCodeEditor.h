/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCodeEditor.h
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
#ifndef _RETROCODEEDITOR_H_
#define _RETROCODEEDITOR_H_

#ifndef _RCDLL
#define RCIMPEXP _declspec(dllimport)
#else
#define RCIMPEXP _declspec(dllexport)
#endif

// Enums
typedef enum _rcPluginTypes
{
	RCINTERNAL_PLUGIN		= 0, 
	RCPROJECT_PLUGIN		= 1
}RCPLUGINTYPES;

typedef enum
{
	ARCH_6502 = 0,
	ARCH_68000 = 1,
	ARCH_Z80 = 2,
	ARCH_END
}ArchitectureType;

#include <vector>
#include <map>

#include <AWCGui.h>

#include <IRetroCodeManager.h>
#include <RetroCodeProjectItem.h>
#include <RetroCodeProject.h>

#include <IPlugin.h>
//#include <IRetroCodeAction.h>
#include <RetroCodeProjectTypePlugin.h>

// Types
typedef struct
{
	CString strPlatformName;
	ArchitectureType atArchType;
	unsigned int uiPlatformID;
}PlatformType, *lpPlatformType;

typedef struct
{
	CString strPrjTypeName;
	CString strPrjTypeDescription;
	unsigned int uiPrjTypeID;
	unsigned int uiPlatformID;
	AWCDialog *lpProjectDlg;
	RetroCodeProjectTypePlugin *lpPlugin;
}ProjectType, *lpProjectType;

// Funzioni
IPlugin *loadPlugin( const wchar_t *lpLibraryPath, void *lpParam );
bool unloadPlugin( const wchar_t *lpLibraryPath );

int RCIMPEXP RegisterPlatform(CString &strPlatformName, ArchitectureType archType);
lpPlatformType RCIMPEXP GetPlatformFromIndex(unsigned int index);
lpPlatformType RCIMPEXP GetPlatformFromName(const wchar_t *lpPlatformName);
unsigned int RCIMPEXP GetPlatformIDFromName(const wchar_t *lpPlatformName);
int RCIMPEXP GetPlatformsCount(void);


int RCIMPEXP RegisterProjectType(CString &strProjectTypeName, CString &strPrjTypeDescription, unsigned int platformID, RetroCodeProjectTypePlugin *lpPlugin = nullptr, AWCDialog *lpProjectDlg = nullptr);
int RCIMPEXP RegisterProjectType(CString &strProjectTypeName, CString &strPrjTypeDescription, lpPlatformType lpPlatform, RetroCodeProjectTypePlugin *lpPlugin = nullptr, AWCDialog *lpProjectDlg = nullptr);

lpProjectType RCIMPEXP GetProjectTypeFromIndex(unsigned int index);
int RCIMPEXP GetProjectTypesCount(void);

#endif
// _RETROCODEEDITOR_H_
