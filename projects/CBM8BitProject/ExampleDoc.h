
// RetroCodeDoc.h: interfaccia della classe CRetroCodeDoc
//


#pragma once


class ExampleDoc : public CDocument
{
protected: // creare solo da serializzazione.
	ExampleDoc() noexcept;
	DECLARE_DYNCREATE(ExampleDoc)

// Attributi
public:

// Operazioni
public:

// Sostituzioni
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementazione
public:
	virtual ~ExampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funzioni generate per la mappa dei messaggi
protected:
	DECLARE_MESSAGE_MAP()

};
