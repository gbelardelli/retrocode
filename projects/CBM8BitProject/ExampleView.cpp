
// C64DevView.cpp : implementazione della classe ExampleView
//

#include "stdafx.h"
// SHARED_HANDLERS può essere definito in un'anteprima di implementazione del progetto ATL, nei gestori delle anteprime
// e della ricerca e consente di condividere il codice dei documenti con il progetto in questione.

#include "ExampleDoc.h"
#include "resource.h"
#include "ExampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ExampleView

IMPLEMENT_DYNCREATE(ExampleView, CEditView)

BEGIN_MESSAGE_MAP(ExampleView, CEditView)
	ON_WM_DESTROY()
	// Comandi di stampa standard
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &ExampleView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// costruzione/eliminazione di ExampleView

ExampleView::ExampleView()
{
	// TODO: aggiungere qui il codice di costruzione.

}

ExampleView::~ExampleView()
{
}

BOOL ExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: modificare la classe o gli stili Window modificando
	//  la struttura CREATESTRUCT

	return CEditView::PreCreateWindow(cs);
}

void ExampleView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();


	// Impostare i margini di stampa (720 twip = 1/2 pollice).
	//SetMargins(CRect(720, 720, 720, 720));
}


// stampa di ExampleView


void ExampleView::OnFilePrintPreview()
{

}

BOOL ExampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// preparazione predefinita
	return DoPreparePrinting(pInfo);
}


void ExampleView::OnDestroy()
{
	// Disabilitare l'elemento durante la distruzione. È importante
	// quando viene utilizzata una visualizzazione con separatore.

   CEditView::OnDestroy();
}


void ExampleView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void ExampleView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{

}


// diagnostica di ExampleView

#ifdef _DEBUG
void ExampleView::AssertValid() const
{
	CEditView::AssertValid();
}

void ExampleView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

ExampleDoc* ExampleView::GetDocument() const // la versione non debug è inline.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ExampleDoc)));
	return (ExampleDoc*)m_pDocument;
}
#endif //_DEBUG


// gestori di messaggi di ExampleView
