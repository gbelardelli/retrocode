/*****************************************************************************

	RetroCode - An IDE for retro development

	PluginManager.h
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
#ifndef _PLUGINMANAGER_H_
#define _PLUGINMANAGER_H_

#include <IPlugin.h>
#include <vector>

typedef struct _tagPluginInfo_
{
    wchar_t *lpwcName;
    wchar_t *lpwcDescription;
    wchar_t *lpwcAuthor;
    wchar_t *lpwcAuthorEmail;
    wchar_t *lpwcAuthorWebsite;
    wchar_t *lpwcLicense;
	unsigned int uiVersion;
}PluginInfo, *lpPluginInfo;

typedef struct _tagPluginMap_
{
	IPlugin			*lpPlugin;
	PluginInfo		*lpInfo;
	HMODULE			hPluginModule;
	unsigned int	uiPluginStatus;
}PluginMap, *lpPluginMap;

typedef enum
{
	PLUGIN_NOTLOADED,
	PLUGIN_LOADED	= 1,
};

class PluginManager
{
private:
	static IPlugin *LoadPlugin( const wchar_t *lpwcFilename, void *lpParam, HMODULE *hLibModule );
	static std::vector< lpPluginMap >m_vcPluginList;

	static unsigned int GetStartID( void );
public:
	static bool LoadPlugins( const wchar_t *lpDirPath = NULL, void *lpParam = NULL );
	static DWORD GetTotalPlugins( void ) { return m_vcPluginList.size(); }
	static lpPluginInfo GetPluginInfo( int nIdx );
	static HMODULE GetPluginModule(IPlugin *lpPlugin);
	static HMODULE SetPluginResourceHandle(IPlugin *lpPlugin);
	static lpPluginMap GetPlugin(int nIdx);
	static lpPluginMap GetPluginFromID( unsigned int dwID );
};

#endif // _PLUGINMANAGER_H_
