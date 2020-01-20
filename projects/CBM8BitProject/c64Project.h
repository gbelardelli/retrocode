/*****************************************************************************

	RetroCode - An IDE for retro development

	C64Project.h
	Author:		Gianluca Belardelli
	Date:		13/01/2020

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
#ifndef _C64PROJECT_H_
#define _C64PROJECT_H_

class C64Project : public RetroCodeProject
{
// Members
protected:
	unsigned int	m_uiStartAddress;
	unsigned char	m_cAutoCreateFiles;

protected:
	virtual int _loadProject(void);
	virtual void onNewProject(void);
public:
	C64Project(unsigned int uiStartAddress);
	virtual ~C64Project(void);
	
	virtual void onSaveProject(void);
	virtual void onSaveAsProject(CString &strFilename);
	virtual void onBuildProject(void);
	virtual void onCleanProject(void);
};

#endif
// _C64PROJECT_H_
