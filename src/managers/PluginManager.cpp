/*****************************************************************************

	RetroCode - An IDE for retro development

	PluginManager.cpp
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

#include "PluginManager.h"
//#include "AWCEditorManager.h"

/*#include <AWCMenu.h>
#include <AWCMainFrm.h>*/

#include <io.h>
#include <direct.h>



constexpr auto START_PLUGIN_ID = 0x0001;
std::vector< lpPluginMap >PluginManager::m_vcPluginList;

IPlugin *loadPlugin( const wchar_t *lpLibraryPath, void *lpParam )
{
	HMODULE hLibrary;

	hLibrary = LoadLibrary(lpLibraryPath);
	if (!hLibrary)
	{
		DWORD dwErr = GetLastError();
		return nullptr;
	}

	IPlugin::PLUGINENTRYFUNC EntryFunc = (IPlugin::PLUGINENTRYFUNC)GetProcAddress(hLibrary, "PluginEntry");
	if (!EntryFunc)
	{
		FreeLibrary(hLibrary);
		return nullptr;
	}

	IPlugin *lpPlugin = EntryFunc(lpParam);

	return lpPlugin;
}

IPlugin *PluginManager::LoadPlugin( const wchar_t *lpFilename, void *lpParam, HMODULE *hLibModule)
{
	HMODULE hLibrary;
	*hLibModule = nullptr;

	hLibrary = LoadLibrary(lpFilename);
	if (!hLibrary)
	{
		DWORD dwErr = GetLastError();
		return nullptr;
	}

	IPlugin::PLUGINENTRYFUNC EntryFunc = (IPlugin::PLUGINENTRYFUNC)GetProcAddress(hLibrary, "PluginEntry");
	if (!EntryFunc)
	{
		FreeLibrary(hLibrary);
		return nullptr;
	}

	IPlugin *lpPlugin = EntryFunc(lpParam);
	if (lpPlugin)
		*hLibModule = hLibrary;

	return lpPlugin;
}

unsigned int PluginManager::GetStartID( void )
{
	return 0;
}

lpPluginInfo PluginManager::GetPluginInfo( int nIdx )
{
	if (nIdx > m_vcPluginList.size())
		return nullptr;

	return m_vcPluginList[ nIdx ]->lpInfo;
}

HMODULE PluginManager::GetPluginModule(IPlugin *lpPlugin)
{
	const size_t nSize = m_vcPluginList.size();
	for(int i=0; i<nSize; i++)
	{
		if (m_vcPluginList[i]->lpPlugin == lpPlugin)
			return m_vcPluginList[i]->hPluginModule;
	}

	return nullptr;
}

HMODULE PluginManager::SetPluginResourceHandle(IPlugin *lpPlugin)
{
	const size_t nSize = m_vcPluginList.size();
	for (int i = 0; i < nSize; i++)
	{
		if (m_vcPluginList[i]->lpPlugin == lpPlugin)
		{
			HINSTANCE hOld = AfxGetResourceHandle();
			AfxSetResourceHandle(m_vcPluginList[i]->hPluginModule);
			return hOld;
		}
	}

	return nullptr;
}

bool PluginManager::LoadPlugins( const wchar_t *lpDirPath, void *lpParam )
{
	DWORD dwCurrGUIButtonID = 0;
	HMODULE hMod;
	struct _wfinddata64_t c_file;
	intptr_t hFile = 0;
	int nLen = 0;

	nLen = GetCurrentDirectory(0,nullptr);

	wchar_t *lpCurrDir = new wchar_t[nLen]; 
	GetCurrentDirectory( nLen, lpCurrDir );

	if (lpDirPath != nullptr)
		_wchdir(lpDirPath);

	hFile = _wfindfirst64(_T("*.dll"), &c_file);
	if (hFile == -1L)
		return false;

	IPlugin *lpPlugin;
	lpPlugin = PluginManager::LoadPlugin(c_file.name, lpParam, &hMod );
	if( lpPlugin != nullptr)
	{
		lpPluginMap lpPMap = new PluginMap;
		lpPMap->lpPlugin = lpPlugin;
		lpPMap->uiPluginStatus = PLUGIN_LOADED;
		lpPluginInfo lpInfo = new PluginInfo;
		lpInfo->lpwcName = lpPlugin->GetName();
		lpPMap->lpInfo = lpInfo;
		lpPMap->hPluginModule = hMod;
		dwCurrGUIButtonID++;

		m_vcPluginList.push_back( lpPMap );
	}

	while( _wfindnext64( hFile, &c_file ) == 0 )
	{
		lpPlugin = PluginManager::LoadPlugin(c_file.name, lpParam, &hMod);

		if( lpPlugin != nullptr )
		{
			lpPluginMap lpPMap = new PluginMap;
			lpPMap->lpPlugin = lpPlugin;
			lpPMap->uiPluginStatus = 1;
			lpPluginInfo lpInfo = new PluginInfo;
			lpInfo->lpwcName = lpPlugin->GetName();
			lpPMap->lpInfo = lpInfo;
			lpPMap->hPluginModule = hMod;
			dwCurrGUIButtonID++;

			m_vcPluginList.push_back( lpPMap );
		}
	}

	_findclose( hFile );

	_wchdir( lpCurrDir );
	delete []lpCurrDir;
	return true;
}

lpPluginMap PluginManager::GetPluginFromID( unsigned int dwID )
{
	for( int i=0; i<m_vcPluginList.size(); i++ )
	{
		lpPluginMap lpPMap = m_vcPluginList[i];
		if( lpPMap->uiPluginStatus == dwID )
			return lpPMap;
	}

	return nullptr;
}

lpPluginMap PluginManager::GetPlugin(int nIdx)
{
	if (nIdx < 0 || nIdx > m_vcPluginList.size())
		return nullptr;

	return m_vcPluginList[nIdx];
}
