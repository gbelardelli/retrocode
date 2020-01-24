/*****************************************************************************

	RetroCode - An IDE for retro development

	FileView.cpp
	Author:		Gianluca Belardelli
	Date:		08/01/2020

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
#include <main\MainFrm.h>
#include "ProjectView.h"
#include "Resource.h"
#include <main\RetroCode.h>

#include <managers\RetroCodeWorkspace.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView() noexcept
{
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Gestori di messaggi CWorkspaceBar

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Creare visualizzazione:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("Non è stato possibile creare la visualizzazione file.\n");
		return -1;      // impossibile creare
	}

	// Caricare immagini visualizzazione:
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* È bloccato */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// Tutti i comandi verranno indirizzati tramite questo controllo anziché tramite il frame principale:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// Inserire i dati statici della visualizzazione albero (codice fittizio, niente di particolare)
	FillFileView();
	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

int CFileView::traverseAndBuildProjectTree( HTREEITEM lpParent, RetroCodeBaseItem *lpItem)
{
	const int nSize = lpItem->GetChildsCount();
	RetroCodeBaseItem *lpChild;

	for (int i = 0; i < nSize; i++)
	{
		lpChild = lpItem->GetChildAt(i);

		if (lpChild->GetItemType() == RetroCodeItemType::FILTER_ITEM)
		{
			HTREEITEM hSrc = m_wndFileView.InsertItem(lpChild->GetItemName(), 0, 0, lpParent);
			m_wndFileView.SetItemData(hSrc, (DWORD_PTR)lpChild);
			traverseAndBuildProjectTree( hSrc, lpChild);
		}

		if (lpChild->GetItemType() == RetroCodeItemType::FILE_ITEM)
		{
			HTREEITEM hSrc = m_wndFileView.InsertItem(lpChild->GetItemName(), 1, 1, lpParent);
			m_wndFileView.SetItemData(hSrc, (DWORD_PTR)lpChild);
			traverseAndBuildProjectTree(lpParent, lpChild);
		}
	}

	return 0;
}

void CFileView::FillFileView()
{
	RetroCodeProject *lpPrj = RetroCodeWorkspace::GetHinstance()->GetActiveProject();
	if( lpPrj != nullptr )
	{
		RetroCodeBaseItem *lpRootItem = lpPrj->GetRootItem();
		HTREEITEM hRoot = m_wndFileView.InsertItem(lpRootItem->GetItemName(), 0, 0);
		m_wndFileView.SetItemData(hRoot, (DWORD_PTR)lpRootItem);
		traverseAndBuildProjectTree(hRoot, lpRootItem);
		m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
		m_wndFileView.Expand(hRoot, TVE_EXPAND);
		/*HTREEITEM hRoot = m_wndFileView.InsertItem(_T("File FakeApp"), 0, 0);
		

		HTREEITEM hSrc = m_wndFileView.InsertItem(_T("File di origine FakeApp"), 0, 0, hRoot);

		m_wndFileView.InsertItem(_T("FakeApp.cpp"), 1, 1, hSrc);
		m_wndFileView.InsertItem(_T("FakeApp.rc"), 1, 1, hSrc);
		m_wndFileView.InsertItem(_T("FakeAppDoc.cpp"), 1, 1, hSrc);
		m_wndFileView.InsertItem(_T("FakeAppView.cpp"), 1, 1, hSrc);
		m_wndFileView.InsertItem(_T("MainFrm.cpp"), 1, 1, hSrc);
		m_wndFileView.InsertItem(_T("StdAfx.cpp"), 1, 1, hSrc);

		HTREEITEM hInc = m_wndFileView.InsertItem(_T("File di intestazione FakeApp"), 0, 0, hRoot);

		m_wndFileView.InsertItem(_T("FakeApp.h"), 2, 2, hInc);
		m_wndFileView.InsertItem(_T("FakeAppDoc.h"), 2, 2, hInc);
		m_wndFileView.InsertItem(_T("FakeAppView.h"), 2, 2, hInc);
		m_wndFileView.InsertItem(_T("Resource.h"), 2, 2, hInc);
		m_wndFileView.InsertItem(_T("MainFrm.h"), 2, 2, hInc);
		m_wndFileView.InsertItem(_T("StdAfx.h"), 2, 2, hInc);

		HTREEITEM hRes = m_wndFileView.InsertItem(_T("File di risorse FakeApp"), 0, 0, hRoot);

		m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hRes);
		m_wndFileView.InsertItem(_T("FakeApp.rc2"), 2, 2, hRes);
		m_wndFileView.InsertItem(_T("FakeAppDoc.ico"), 2, 2, hRes);
		m_wndFileView.InsertItem(_T("FakeToolbar.bmp"), 2, 2, hRes);

		m_wndFileView.Expand(hRoot, TVE_EXPAND);
		m_wndFileView.Expand(hSrc, TVE_EXPAND);
		m_wndFileView.Expand(hInc, TVE_EXPAND);
		*/
	}
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Scegliere la voce selezionata:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != nullptr)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(nullptr, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnProperties()
{
	FillFileView();

}

void CFileView::OnFileOpen()
{
	// TODO: aggiungere qui il codice del gestore di comandi
}

void CFileView::OnFileOpenWith()
{
	// TODO: aggiungere qui il codice del gestore di comandi
}

void CFileView::OnDummyCompile()
{
	// TODO: aggiungere qui il codice del gestore di comandi
}

void CFileView::OnEditCut()
{
	// TODO: aggiungere qui il codice del gestore di comandi
}

void CFileView::OnEditCopy()
{
	// TODO: aggiungere qui il codice del gestore di comandi
}

void CFileView::OnEditClear()
{
	// TODO: aggiungere qui il codice del gestore di comandi
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // contesto di dispositivo per il disegno

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Bloccato */);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Impossibile caricare bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}
