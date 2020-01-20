/*****************************************************************************

	RetroCode - An IDE for retro development

	CBMProjectWizard.h
	Author:		Gianluca Belardelli
	Date:		10/01/2020

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
#ifndef _CBMPROJECTWIZARD_H_
#define _CBMPROJECTWIZARD_H_

class CBMProjectWizard : public AWCDialog
{
	DECLARE_DYNAMIC(CBMProjectWizard)

public:
	CBMProjectWizard(CWnd* pParent = nullptr);   // costruttore standard
	virtual ~CBMProjectWizard();

// Dati della finestra di dialogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Supporto DDX/DDV

	DECLARE_MESSAGE_MAP()
};

#endif
// _CBMPROJECTWIZARD_H_
