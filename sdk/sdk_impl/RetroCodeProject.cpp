/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCodeProject.cpp
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

using namespace tinyxml2;

int traverseTreeSave(tinyxml2::XMLDocument *lpDoc, tinyxml2::XMLElement *lpParentElem, RetroCodeBaseItem *lpItem);

RetroCodeProject::RetroCodeProject(void) :
	m_lpRootItem(nullptr),
	m_lpPrjDoc(nullptr),
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

void RetroCodeProject::setPluginName(CString strPluginName)
{
	m_strPluginName = strPluginName;
}

RetroCodeBaseItem *RetroCodeProject::AddFileItem(CString strItemName, CString strItemPath, bool bCreateFile, RetroCodeBaseItem *lpParent)
{
	if (m_lpRootItem == nullptr)
		return nullptr;

	RetroCodeBaseItem *lpItem;
	if (lpParent == nullptr)
		lpItem = new RetroCodeProjectFileItem(strItemName, strItemPath, bCreateFile, m_lpRootItem);
	else
		lpItem = new RetroCodeProjectFileItem(strItemName, strItemPath, bCreateFile, lpParent);

	m_bSaveProject = true;
	return lpItem;
}

RetroCodeBaseItem *RetroCodeProject::AddFilterItem(CString strItemName, CString strFilter, RetroCodeBaseItem *lpParent)
{
	if (m_lpRootItem == nullptr)
		return nullptr;

	RetroCodeBaseItem *lpItem;
	if (lpParent == nullptr)
		lpItem = new RetroCodeFilterItem(strItemName, strFilter, m_lpRootItem);
	else
		lpItem = new RetroCodeFilterItem(strItemName, strFilter, lpParent);

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
		if(!m_lpPrjDoc)
		{
			m_lpPrjDoc = new tinyxml2::XMLDocument();

			tinyxml2::XMLElement *lpRoot = m_lpPrjDoc->NewElement("Project");
			lpRoot->SetAttribute("RetroCodeVersion",1);
			lpRoot->SetAttribute("TreeType", "virtual");

			USES_CONVERSION;
			char* pchTmp(T2A(m_strPluginName));

			lpRoot->SetAttribute("Plugin", pchTmp);
			

			traverseTreeSave(m_lpPrjDoc, lpRoot, m_lpRootItem);
			m_lpPrjDoc->InsertFirstChild(lpRoot);
			//USES_CONVERSION;
			char* pchTmp2(T2A(m_strFullPrjFilename));
			m_lpPrjDoc->SaveFile(pchTmp2);
		}

		m_bSaveProject = false;
	}

	return 0;
}

RetroCodeBaseItem *RetroCodeProject::GetRootItem(void)
{
	return m_lpRootItem;
}

int traverseTreeSave( tinyxml2::XMLDocument *lpDoc, tinyxml2::XMLElement *lpParentElem, RetroCodeBaseItem *lpItem )
{
	const int nSize = lpItem->GetChildsCount();
	RetroCodeBaseItem *lpChild;

	for(int i=0; i<nSize; i++)
	{
		lpChild = lpItem->GetChildAt(i);
		
		if(lpChild->GetItemType() == RetroCodeItemType::FILTER_ITEM )
		{
			tinyxml2::XMLElement *lpElem = lpDoc->NewElement("ItemGroup");
			USES_CONVERSION;
			char* pchTmp(T2A(lpChild->GetItemName()));

			lpElem->SetAttribute("name", pchTmp);

			traverseTreeSave(lpDoc,lpElem,lpChild);
			if (lpParentElem)
				lpParentElem->InsertEndChild(lpElem);
			else
				lpDoc->InsertEndChild(lpElem);
		}

		if(lpChild->GetItemType() == RetroCodeItemType::FILE_ITEM)
		{
			RetroCodeProjectFileItem *lpFileItem = (RetroCodeProjectFileItem *)lpChild;
			tinyxml2::XMLElement *lpElem = lpDoc->NewElement("Item");
			USES_CONVERSION;
			char* pchTmp(T2A(lpFileItem->GetItemName()));
			lpElem->SetAttribute("name", pchTmp);

			char* pchTmp2(T2A(lpFileItem->GetPath()));
			lpElem->SetAttribute("path", pchTmp2);
			lpParentElem->InsertEndChild(lpElem);
			//lpDoc->InsertEndChild(lpElem);
		}
	}

	return 0;
}