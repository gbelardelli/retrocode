/*****************************************************************************

	RetroCodeDoc.cpp
	This file is part of RetroCode an IDE for retro development.
	Copyright(c) 2019 by Gianluca Belardelli.
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
#include "stdafx.h"

// SHARED_HANDLERS può essere definito in un'anteprima di implementazione del progetto ATL, nei gestori di anteprime
// e della ricerca e consente di condividere il codice dei documenti con il progetto in questione.

#include "ExampleDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRetroCodeDoc

IMPLEMENT_DYNCREATE(ExampleDoc, CDocument)

BEGIN_MESSAGE_MAP(ExampleDoc, CDocument)
END_MESSAGE_MAP()


// Costruzione/distruzione di CRetroCodeDoc

ExampleDoc::ExampleDoc() noexcept
{
	// TODO: aggiungere qui il codice di costruzione unico

}

ExampleDoc::~ExampleDoc()
{
}

BOOL ExampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: aggiungere qui il codice di reinizializzazione
	// (nei documenti SDI verrà riutilizzato questo documento).

	return TRUE;
}




// Serializzazione di CRetroCodeDoc

void ExampleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: aggiungere qui il codice di archiviazione.
	}
	else
	{
		// TODO: aggiungere qui il codice di caricamento.
	}
}

// Diagnostica di CRetroCodeDoc

#ifdef _DEBUG
void ExampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void ExampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Comandi di CRetroCodeDoc
