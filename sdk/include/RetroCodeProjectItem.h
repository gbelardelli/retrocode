/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCodeBaseItem.h
	Author:		Gianluca Belardelli
	Date:		10/01/2020

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
#ifndef _RETROCODEPROJECTITEM_H_
#define _RETROCODEPROJECTITEM_H_

typedef enum
{
	UNKNOWN_ITEM = 0,
	PROJECT_ITEM = 1,
	FILE_ITEM = 2,
	FILTER_ITEM = 3,
	FOLDER_ITEM = 4
}RetroCodeItemType;

class RCIMPEXP RetroCodeBaseItem
{
private:
	RetroCodeBaseItem	*m_lpParentItem;
	std::vector<RetroCodeBaseItem *>m_vcChilds;

protected:
	CString	m_strItemName;
	unsigned int m_uiItemType;
	void *m_lpItemData;

// Methods
private:
	void AddChild(RetroCodeBaseItem *lpChild);

	RetroCodeBaseItem *GetChildAt(int nIdx);
	CString GetChildNameAt(int nIdx);

	bool RemoveChild(RetroCodeBaseItem *lpChild);
	bool RemoveChildAt(int nIdx);
	void RemoveAllChilds(void);
protected:
	RetroCodeBaseItem(CString strItemName, RetroCodeBaseItem *lpParent = nullptr);
	RetroCodeBaseItem(RetroCodeBaseItem &copy);

public:
	~RetroCodeBaseItem(void);
	
	CString &GetItemName(void);
	unsigned int GetItemType(void);

	void SetItemData(void *lpData);
	void *GetItemData(void);

	int GetChildsCount(void);
	
	unsigned int GetChildTypeAt(int nIdx);



};

class RCIMPEXP RetroCodeProjectItem : public RetroCodeBaseItem
{
protected:
	CString m_strFilePath;
	CString m_strFullFilename;

public:
	RetroCodeProjectItem(CString strItemName, CString strItemPath, RetroCodeBaseItem *lpParent = nullptr);
	virtual ~RetroCodeProjectItem(void);

};

class RCIMPEXP RetroCodeFilterItem : public RetroCodeBaseItem
{
public:
	RetroCodeFilterItem(CString strItemName, CString strFilter, RetroCodeBaseItem *lpParent = nullptr);
	virtual ~RetroCodeFilterItem(void);
};

class RCIMPEXP RetroCodeProjectFileItem : public RetroCodeBaseItem
{
protected:
	CString m_strFilePath;
	CString m_strFullFilename;

	unsigned int m_uiFileType;

protected:
	void setFileType(void);

public:
	RetroCodeProjectFileItem(CString strItemName, CString strItemPath, RetroCodeBaseItem *lpParent = nullptr );
	virtual ~RetroCodeProjectFileItem(void);

	unsigned int GetFileType(void);
};
#endif
// _RETROCODEPROJECTITEM_H_