/*****************************************************************************

	RetroCode - An IDE for retro development

	IRetroCodeManager.h
	Author:		Gianluca Belardelli
	Date:		08/01/2020

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
#ifndef _IRETROCODEMANAGER_H_
#define _IRETROCODEMANAGER_H_

class IRetroCodeProject;
//class AWCMainFrame;
class CWnd;

//#include "..\events\AWCPluginEvent.h"
//#include <AWCCallback.h>

class RCIMPEXP IRetroCodeManager
{
public:
	virtual bool InitDefaultPlugins( const wchar_t *lpwcPluginPath ) = 0;
	/*virtual AWCMainFrame *GetMainEditorFrame( void ) = 0;
	virtual void SetMainEditorFrame( AWCMainFrame *lpFrame ) = 0;
	virtual bool CreateEditorPanel( CWnd *lpView ) = 0;
	virtual bool ShowEditorPanel( CWnd *lpView ) = 0;*/
	virtual IRetroCodeProject *GetActiveProject( void ) = 0;
	virtual void SetActiveProject(IRetroCodeProject *lpProject ) = 0;
	/*virtual bool AddToolsMenuItem( wchar_t *lpwcText, HICON hIcon = NULL, wchar_t *lpwcMsg = NULL ) = 0;
	virtual bool AddToolsMenuItem( LPAWCMENU *lpMenu ) = 0;

	virtual void AddMenuHandler( unsigned long ulID, Functor0 &lpFunctor ) = 0;
	virtual bool ProcessEvent( AWCPluginEvent *lpEvent ) = 0;
	virtual void RegisterEvent( awcEventType etEventType, Functor1<AWCPluginEvent *> *lpFunctor ) = 0;*/


};

#endif
// _IRETROCODEMANAGER_H_
