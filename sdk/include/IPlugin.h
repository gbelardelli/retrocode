/*****************************************************************************

	RetroCode - An IDE for retro development

	IPlugin.h
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
#ifndef _IPLUGIN_H_
#define _IPLUGIN_H_

///IPlugin è la classe base da cui derivano le
///implementazioni dei singoli oggetti caricati come plug-ins
class RCIMPEXP IPlugin
{
public:
	virtual wchar_t    		*GetDescription( void ) = 0;
	virtual wchar_t			*GetName( void ) = 0;
	virtual unsigned long	GetVersion( void ) = 0;
	virtual RCPLUGINTYPES	GetPluginType(void) = 0;

	virtual bool			InitPlugin( void *lpParam ) = 0;
	virtual bool			ShutdownPlugin( void *lpParam ) = 0;
	HMODULE                 GetPluginHinstance(void);

	/** 
		Questo metodo viene richiamato direttamente dall'editor ed è
		utilizzato dal plugin per aggiungere le voci di menu, di
		cui ha bisogno, al menù principale dell'applicazione.
        @param lpMenuBar Puntatore a IAWCMenu che rappresenta il menù
		principale dell'applicazione.
		@return true se il plugin crea un nuovo menù altrimenti false.
		L'implementazione di default ritorna false. In tutte le
		classi derivate da IAWCPlugin che impementano questo metodo
		è necessario ritornare true per visualizzare il menù.
    */
    //virtual bool BuildMenu( IAWCMenu *lpMenuBar ) { return false; }

    /** This method is called by Code::Blocks core modules (EditorManager,
        * ProjectManager etc) and is used by the plugin to add any menu
        * items it needs in the module's popup menu. For example, when
        * the user right-clicks on a project file in the project tree,
        * ProjectManager prepares a popup menu to display with context
        * sensitive options for that file. Before it displays this popup
        * menu, it asks all attached plugins (by asking PluginManager to call
        * this method), if they need to add any entries
        * in that menu. This method is called.\n
        * If the plugin does not need to add items in the menu,
        * just do nothing ;)
        * @param type the module that's preparing a popup menu
        * @param menu pointer to the popup menu
        * @param data pointer to FileTreeData object (to access/modify the file tree)
        */
    //virtual void BuildModuleMenu(cb_optional const ModuleType type, cb_optional wxMenu* menu, cb_optional const FileTreeData* data = 0) { }

    /** This method is called by Code::Blocks and is used by the plugin
        * to add any toolbar items it needs on Code::Blocks's toolbar.\n
        * It is a pure virtual method that needs to be implemented by all
        * plugins. If the plugin does not need to add items on the toolbar,
        * just do nothing ;)
        * @param toolBar the wxToolBar to create items on
        * @return The plugin should return true if it needed the toolbar, false if not
        */
    //virtual bool BuildToolBar(cb_optional wxToolBar* toolBar ) { return false; }
	
	///Tipo funzione di apertura del plugin.
	typedef IPlugin *( *PLUGINENTRYFUNC )( void *lpParam );
	typedef void ( *PLUGINEXITFUNC )(void);
};

#endif // _IPLUGIN_H_

