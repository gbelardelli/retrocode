/*****************************************************************************

	RetroCode - An IDE for retro development

	IRetroCodeAction.h
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
#ifndef _IRETROCODEACTION_H_
#define _IRETROCODEACTION_H_

class IRetroCodeAction
{
// Methods
public:
	virtual ~IRetroCodeAction( void ) {};

	virtual wchar_t *GetActionShortDescription( void ) = 0;
	
	virtual bool DoAction( void ) = 0;

	virtual bool DoUndoAction( void ) = 0;
	virtual bool DoRedoAction( void ) = 0;
};

#endif
// _IRETROCODEACTION_H_
