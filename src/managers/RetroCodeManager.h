/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCodeWorkspace.h
	Author:		Gianluca Belardelli
	Date:		23/01/2020

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
#ifndef _RETROCODEMANAGER_H_
#define _RETROCODEMANAGER_H_

class RetroCodeManager : public IRetroCodeManager
{
private:
	CMDIFrameWndEx	*m_lpMainFrame;
	//CProjectView	*m_lpPrjView;

public:
	virtual RetroCodeProject *GetActiveProject(void);
	virtual CMDIFrameWndEx *GetMainEditorFrame(void);
	virtual void SetMainEditorFrame(CMDIFrameWndEx *lpFrame);
	virtual CDockablePane *GetProjectView(void);

};

#endif
// _RETROCODEMANAGER_H_


