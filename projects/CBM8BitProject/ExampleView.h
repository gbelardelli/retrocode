
// C64DevView.h : interfaccia della classe ExampleView
//

#pragma once

class ExampleView : public CEditView
{
protected: // creare solo da serializzazione.
	ExampleView();
	DECLARE_DYNCREATE(ExampleView)

// Attributi
public:
	ExampleDoc* GetDocument() const;

// Operazioni
public:

// Sostituzioni
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // richiamato la prima volta dopo la costruzione
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

// Implementazione
public:
	virtual ~ExampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funzioni generate per la mappa dei messaggi
protected:
	afx_msg void OnDestroy();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // versione di debug in C64DevView.cpp
inline ExampleDoc* ExampleView::GetDocument() const
   { return reinterpret_cast<ExampleDoc*>(m_pDocument); }
#endif

