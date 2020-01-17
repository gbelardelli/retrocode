#include "stdafx.h"
#include <RetroCodeEditor.h>

RetroCodeProject::RetroCodeProject(void) :
	m_lpRootItem(nullptr),
	m_lpPrjFile(nullptr),
	m_bSaveProject(false)
{
}

RetroCodeProject::~RetroCodeProject(void)
{
}

void RetroCodeProject::createRootItem(void)
{
	m_lpRootItem = new RetroCodeProjectItem(m_strPrjName, m_strPrjPath);
	m_bSaveProject = true;
}

void RetroCodeProject::setProjectName(CString strPrjName)
{
	m_strPrjName = strPrjName;
}

void RetroCodeProject::setProjectDesc(CString strPrjDesc)
{
	m_strPrjDesc = strPrjDesc;
}

void RetroCodeProject::setProjectArch(ArchitectureType atType)
{
	m_atArch = atType;
}

void RetroCodeProject::setProjectPath(CString strPrjPath)
{
	m_strPrjPath = strPrjPath;
}

void RetroCodeProject::setProjectID(unsigned int uiPrjID)
{
	m_uiPrjID = uiPrjID;
}

void RetroCodeProject::setFullFilename(CString strFilename)
{
	m_strFullPrjFilename = strFilename;
}


RetroCodeBaseItem *RetroCodeProject::AddFileItem(CString strItemName, CString strItemPath, RetroCodeBaseItem *lpParent)
{
	if (m_lpRootItem == nullptr)
		return nullptr;

	RetroCodeBaseItem *lpItem;
	if (lpParent == nullptr)
		lpItem = new RetroCodeProjectFileItem(strItemName, strItemPath, m_lpRootItem);
	else
		lpItem = new RetroCodeProjectFileItem(strItemName, strItemPath, lpParent);

	m_bSaveProject = true;
	return lpItem;
}

RetroCodeBaseItem *RetroCodeProject::AddFilterItem(CString strItemName, CString strFilter, RetroCodeBaseItem *lpParent)
{
	if (m_lpRootItem == nullptr)
		return nullptr;

	RetroCodeBaseItem *lpItem;
	if (lpParent == nullptr)
		lpItem = new RetroCodeProjectFileItem(strItemName, strFilter, m_lpRootItem);
	else
		lpItem = new RetroCodeProjectFileItem(strItemName, strFilter, lpParent);

	m_bSaveProject = true;
	return lpItem;
}

RetroCodeBaseItem *RetroCodeProject::AddFolderItem(CString strItemName, CString strItemPath, RetroCodeBaseItem *lpParent)
{
	return nullptr;
}

int RetroCodeProject::SaveProject(void)
{
	if(m_bSaveProject)
	{
		if(!m_lpPrjFile)
		{
			m_lpPrjFile = new CFile();
			if(!m_lpPrjFile->Open(m_strFullPrjFilename, CFile::modeCreate | CFile::modeReadWrite))
			{
				delete m_lpPrjFile;
				m_lpPrjFile = nullptr;
				return -1;
			}
		}

		m_bSaveProject = false;
	}

	return 0;
}