/*****************************************************************************

	RetroCode - An IDE for retro development

	CBMProjectWizard.cpp
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
#include "stdafx.h"
#include <RetroCodeEditor.h>
#include "CBM8BitProject.h"
#include "CBMProjectWizard.h"
#include "afxdialogex.h"


// Finestra di dialogo CBMProjectWizard

IMPLEMENT_DYNAMIC(CBMProjectWizard, AWCDialog)

CBMProjectWizard::CBMProjectWizard(CWnd* pParent /*=nullptr*/)
	: AWCDialog(IDD_DIALOG1, pParent)
{

}

CBMProjectWizard::~CBMProjectWizard()
{
}

void CBMProjectWizard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBMProjectWizard, AWCDialog)
END_MESSAGE_MAP()


// Gestori di messaggi di CBMProjectWizard
