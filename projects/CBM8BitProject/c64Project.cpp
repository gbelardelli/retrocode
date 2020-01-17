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
		AddFileItem(CString("main.asm"), m_strPrjPath, lpItem );

	lpItem = AddFilterItem(CString("Basic Files"), CString("bas"));
	if (m_cAutoCreateFiles & 2)
		AddFileItem(CString("basic.bas"), m_strPrjPath, lpItem);
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