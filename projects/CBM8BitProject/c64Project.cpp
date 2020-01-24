/*****************************************************************************

	RetroCode - An IDE for retro development

	C64Project.cpp
	Author:		Gianluca Belardelli
	Date:		13/01/2020

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
#include "c64Project.h"


C64Project::C64Project(unsigned int uiStartAddress) :
	m_uiStartAddress(uiStartAddress),
	m_cAutoCreateFiles(3)
{
}

C64Project::~C64Project(void)
{
}

void C64Project::onNewProject(void)
{
	RetroCodeBaseItem *lpItem = AddFilterItem(CString("Assembler Files"), CString("asm"));

	if(m_cAutoCreateFiles & 1)
	{
		AddFileItem(CString("main.asm"), m_strPrjPath, true, lpItem );
		AddFileItem(CString("main2.asm"), m_strPrjPath, true, lpItem);
		AddFileItem(CString("main3.asm"), m_strPrjPath, true, lpItem);
	}
	lpItem = AddFilterItem(CString("Basic Files"), CString("bas"));
	if (m_cAutoCreateFiles & 2)
	{
		AddFileItem(CString("basic.bas"), m_strPrjPath, true, lpItem);
		AddFileItem(CString("basic2.bas"), m_strPrjPath, true, lpItem);
		RetroCodeBaseItem *lpItem2 = AddFilterItem(CString("Test inner filter"), CString("asm"), lpItem);
		AddFileItem(CString("inner.spr"), m_strPrjPath, true, lpItem2);
	}
	
	lpItem = AddFilterItem(CString("Spote Files"), CString("bas"));
	if (m_cAutoCreateFiles & 2)
	{
		AddFileItem(CString("file.txt"), m_strPrjPath, true, lpItem);
		AddFileItem(CString("file1.txt"), m_strPrjPath, true, lpItem);
		AddFileItem(CString("file2.spr"), m_strPrjPath, true, lpItem);
	}
}

void C64Project::onSaveProject(void)
{
	CString xml("<startAddress></startAddress>");
}

void C64Project::onSaveAsProject(CString &strFilename)
{
}

void C64Project::onBuildProject(void)
{
}

void C64Project::onCleanProject(void)
{
}

int C64Project::_loadProject(void)
{
	return 1;
}