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
#include <stdafx.h>

// SHARED_HANDLERS può essere definito in un'anteprima di implementazione del progetto ATL, nei gestori di anteprime
// e della ricerca e consente di condividere il codice dei documenti con il progetto in questione.

#ifndef SHARED_HANDLERS
#include "retroCode.h"
#endif

#include "RetroCodeDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRetroCodeDoc

IMPLEMENT_DYNCREATE(CRetroCodeDoc, CDocument)

BEGIN_MESSAGE_MAP(CRetroCodeDoc, CDocument)
END_MESSAGE_MAP()


// Costruzione/distruzione di CRetroCodeDoc

CRetroCodeDoc::CRetroCodeDoc() noexcept
{
	// TODO: aggiungere qui il codice di costruzione unico

}

CRetroCodeDoc::~CRetroCodeDoc()
{
}

BOOL CRetroCodeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: aggiungere qui il codice di reinizializzazione
	// (nei documenti SDI verrà riutilizzato questo documento).

	return TRUE;
}




// Serializzazione di CRetroCodeDoc

void CRetroCodeDoc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Supporto per anteprime
void CRetroCodeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modificare il codice per creare i dati del documento
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
    fontDraw.CreateFontIndirect(&lf);


	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Supporto per gestori di ricerca
void CRetroCodeDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Consente di impostare i contenuti di ricerca dai dati del documento.
	// Le parti di contenuto devono essere separata da ";"

	// Ad esempio:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CRetroCodeDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Diagnostica di CRetroCodeDoc

#ifdef _DEBUG
void CRetroCodeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRetroCodeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Comandi di CRetroCodeDoc
