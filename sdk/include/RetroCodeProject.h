/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCodeProject.h
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
#ifndef _RETROCODEPROJECT_H_
#define _RETROCODEPROJECT_H_

#include <RetroCodeEditor.h>

class RCIMPEXP RetroCodeProject
{
	friend class RetroCodeProjectTypePlugin;
private:
	ArchitectureType m_atArch;
	unsigned int m_uiPrjID;

	bool m_bHasFilters;
	bool m_bSaveProject;
protected:
	CString m_strPrjName;
	CString m_strPrjDesc;
	CString m_strPrjPath;
	CString m_strFullPrjFilename;
	CString m_strPluginName;
	RetroCodeBaseItem	*m_lpRootItem;
	//CFile				*m_lpPrjFile;
	tinyxml2::XMLDocument	*m_lpPrjDoc;

	std::vector<RetroCodeBaseItem *>m_vcChilds;

// Methods
protected:
	virtual int _loadProject( void ) = 0;

	void setProjectName(CString strPrjName);
	void setProjectDesc(CString strPrjDesc);
	void setProjectArch(ArchitectureType atType);
	void setProjectPath(CString strPrjPath);
	void setProjectID(unsigned int uiPrjID);
	void setFullFilename(CString strFilename);
	void setPluginName(CString strPluginName);
	void createRootItem(void);

	virtual void onNewProject(void) = 0;
	virtual void onSaveProject(void) = 0;

public:
	RetroCodeProject(void);
	virtual ~RetroCodeProject(void);

	CString &GetProjectName( void ) { return m_strPrjName; }
	CString &GetProjectDesc(void) {	return m_strPrjDesc; }
	ArchitectureType GetProjectArch(void) { return m_atArch; }
	CString &GetProjectPath(void) { return m_strPrjPath; }
	
	int SaveProject( void );
	virtual void onSaveAsProject( CString &strFilename ) = 0;
	virtual void onBuildProject( void ) = 0;
	virtual void onCleanProject( void ) = 0;

	RetroCodeBaseItem *AddFileItem(CString strItemName, CString strItemPath, bool bCreateFile, RetroCodeBaseItem *lpParent = nullptr);
	RetroCodeBaseItem *AddFilterItem(CString strItemName, CString strFilter, RetroCodeBaseItem *lpParent = nullptr);
	RetroCodeBaseItem *AddFolderItem(CString strItemName, CString strItemPath, RetroCodeBaseItem *lpParent = nullptr);

	//int GetItemsCount(void);
	RetroCodeBaseItem *GetRootItem(void);

	//RetroCodeBaseItem *GetChildAt(int nIdx);
	//CString GetChildNameAt(int nIdx);
	//unsigned int GetChildTypeAt(int nIdx);

	bool RemoveChild(RetroCodeBaseItem *lpChild);
	void RemoveAllChilds(void);
};

#endif
// _RETROCODEPROJECT_H_
