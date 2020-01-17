#include <stdafx.h>
#include <RetroCodeEditor.h>

RetroCodeBaseItem::RetroCodeBaseItem(CString strItemName, RetroCodeBaseItem *lpParent)
	: m_strItemName(strItemName), m_lpItemData(nullptr), 
	m_uiItemType(UNKNOWN_ITEM)
{
	if (lpParent)
		lpParent->AddChild(this);
	else
		m_lpParentItem = nullptr;
}

RetroCodeBaseItem::RetroCodeBaseItem(RetroCodeBaseItem &copy)
{
	m_strItemName = copy.m_strItemName;
	m_uiItemType = copy.m_uiItemType;
	m_lpItemData = copy.m_lpItemData;

	m_vcChilds = copy.m_vcChilds;
}

RetroCodeBaseItem::~RetroCodeBaseItem(void)
{
	m_lpItemData = nullptr;
}

CString &RetroCodeBaseItem::GetItemName(void)
{
	return m_strItemName;
}

unsigned int RetroCodeBaseItem::GetItemType(void)
{
	return m_uiItemType;
}

void RetroCodeBaseItem::SetItemData(void *lpData)
{
	m_lpItemData = lpData;
}

void *RetroCodeBaseItem::GetItemData(void)
{
	return m_lpItemData;
}

void RetroCodeBaseItem::AddChild(RetroCodeBaseItem *lpChild)
{
	lpChild->m_lpParentItem = this;
	m_vcChilds.push_back(lpChild);
}

int RetroCodeBaseItem::GetChildsCount(void)
{
	return m_vcChilds.size();
}

RetroCodeBaseItem *RetroCodeBaseItem::GetChildAt(int nIdx)
{
	const size_t nItems = m_vcChilds.size();
	if (nItems > 0 && nIdx < nItems)
		return m_vcChilds[nIdx];

	return nullptr;
}

CString RetroCodeBaseItem::GetChildNameAt(int nIdx)
{
	const size_t nItems = m_vcChilds.size();
	if (nItems > 0 && nIdx < nItems)
		return m_vcChilds[nIdx]->GetItemName();

	return CString("");
}

unsigned int RetroCodeBaseItem::GetChildTypeAt(int nIdx)
{
	const size_t nItems = m_vcChilds.size();
	if (nItems > 0 && nIdx < nItems)
		return m_vcChilds[nIdx]->GetItemType();

	return -1;
}

bool RetroCodeBaseItem::RemoveChild(RetroCodeBaseItem *lpChild)
{
	const size_t nItems = m_vcChilds.size();
	for(int i=0; i<nItems; i++)
	{
		if( m_vcChilds[i] == lpChild )
		{
			m_vcChilds.erase(m_vcChilds.begin() + i);
			return true;
		}
	}

	return false;
}

bool RetroCodeBaseItem::RemoveChildAt(int nIdx)
{
	const size_t nItems = m_vcChilds.size();
	if (nItems > 0 && nIdx < nItems)
	{
		m_vcChilds.erase(m_vcChilds.begin() + nIdx);
		return true;
	}

	return false;
}

void RetroCodeBaseItem::RemoveAllChilds(void)
{
	const size_t nItems = m_vcChilds.size();
	for (int i = 0; i < nItems; i++)
	{
		m_vcChilds.erase(m_vcChilds.begin());
	}
}



RetroCodeProjectItem::RetroCodeProjectItem(
	CString strItemName, CString strItemPath, RetroCodeBaseItem *lpParent) :
	RetroCodeBaseItem(strItemName, lpParent),
	m_strFilePath(strItemPath)
{
	m_uiItemType = RetroCodeItemType::PROJECT_ITEM;
}

RetroCodeProjectItem::~RetroCodeProjectItem(void)
{
}



RetroCodeFilterItem::RetroCodeFilterItem(
	CString strItemName, CString strFilter, RetroCodeBaseItem *lpParent) :
	RetroCodeBaseItem(strItemName, lpParent)
{
	m_uiItemType = RetroCodeItemType::FILTER_ITEM;
}

RetroCodeFilterItem::~RetroCodeFilterItem(void)
{
}


RetroCodeProjectFileItem::RetroCodeProjectFileItem(
	CString strItemName, CString strItemPath, RetroCodeBaseItem *lpParent) :
		RetroCodeBaseItem( strItemName, lpParent ),
		m_strFilePath(strItemPath)
{
	m_uiItemType = RetroCodeItemType::FILE_ITEM;
}

RetroCodeProjectFileItem::~RetroCodeProjectFileItem(void)
{
}

unsigned int RetroCodeProjectFileItem::GetFileType(void)
{
	return m_uiFileType;
}

void RetroCodeProjectFileItem::setFileType(void)
{
	int nIdx = m_strItemName.ReverseFind('.');
	if( nIdx > 0 )
	{
		CString strExt = m_strItemName.Left(nIdx-1);

		// TODO:
		// Check map
		m_uiFileType = 1;
	}
	else
	{
		// I file senza estensione sono trattati come .txt
		m_uiFileType = 2;
	}
}

