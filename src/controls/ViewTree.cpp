/*****************************************************************************

	RetroCode - An IDE for retro development

	ViewTree.cpp
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
#include "ViewTree.h"
#include <main\MainFrm.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree() noexcept
{
	m_lpFocusView = nullptr;
	m_bIsContext = false;
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CViewTree::OnNMDblclk)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CViewTree::OnTvnSelchanged)
	ON_NOTIFY_REFLECT(TVN_SELCHANGING, &CViewTree::OnTvnSelchanging)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CViewTree::OnNMRClick)
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewTree::OnNMClick)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Gestori di messaggi CViewTree

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != nullptr);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != nullptr)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	if (pNMHDR && pNMHDR->code == TVN_SELCHANGING)
	{
		OutputDebugString(_T("CViewTree::OnNotify"));
	}
	return bRes;
}

void CViewTree::manageMouseClick(NMHDR *pNMHDR, LRESULT *pResult, bool bSetFocus)
{
	*pResult = 0;
	
	HTREEITEM hSelected = GetSelectedItem();
	if (hSelected)
	{
		RetroCodeBaseItem *lpItem = (RetroCodeBaseItem *)GetItemData(hSelected);
		if (!lpItem)
			return;

		if (lpItem->GetItemType() == RetroCodeItemType::FILE_ITEM)
		{
			RetroCodeProjectFileItem *lpFile = (RetroCodeProjectFileItem *)lpItem;
			CWinAppEx *lpApp = dynamic_cast<CWinAppEx*>(AfxGetApp());
			int nDocs = lpApp->GetOpenDocumentCount();

			POSITION pos = lpApp->GetFirstDocTemplatePosition();
			CDocTemplate *lpDocTemplate = lpApp->GetNextDocTemplate(pos);

			pos = lpDocTemplate->GetFirstDocPosition();
			CDocument *lpDoc;
			while (pos != nullptr)
			{
				lpDoc = lpDocTemplate->GetNextDoc(pos);
				if (lpDoc->GetTitle().Compare(lpFile->GetItemName()) == 0)
				{
					// Se il file è già aperto dovrebbe attivare la
					// view corrispondente
					CWnd* lpWndMain = AfxGetMainWnd();
					CFrameWnd* pFrame = ((CMDIFrameWnd*)lpWndMain)->MDIGetActive();
					POSITION posView = lpDoc->GetFirstViewPosition();
					while (posView != nullptr)
					{
						CView *lpView = lpDoc->GetNextView(posView);

						if (lpView->GetDocument() == lpDoc)
						{
							((CMainFrame*)lpWndMain)->ActivateTab(lpFile->GetItemName());
							m_lpFocusView = lpView;

							return;
						}
					}
					return;
				}
			}

			lpDoc = lpDocTemplate->OpenDocumentFile(lpFile->GetFullFilename());
			OutputDebugString(_T("cioa\n"));
		}
	}
}

void CViewTree::SelectItemForContextMenu(HTREEITEM hItem)
{
	m_bIsContext = true;
	SelectItem(hItem);
}

void CViewTree::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	OutputDebugString(_T("****** CViewTree::OnNMDblclk\n"));
	if (m_lpFocusView)
	{
		GetParent()->SetForegroundWindow();
		//m_lpFocusView->GetParentFrame()->SetFocus();
		m_lpFocusView->SetFocus();
		m_lpFocusView = nullptr;
		
		*pResult = 1;
	}
}

BOOL CViewTree::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	CTreeCtrl::Create(dwStyle, rect, pParentWnd, nID);

	SetBkColor(AWCStyleManager::GetInstance()->GetCtrlBackgroundColor());
	SetTextColor(AWCStyleManager::GetInstance()->GetWindowTextColor());
	SetLineColor(AWCStyleManager::GetInstance()->GetWindowTextColor());

	return TRUE;
}

void CViewTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	OutputDebugString(_T("****** CViewTree::OnTvnSelchanged\n"));
	if (!m_bIsContext)
		manageMouseClick(pNMHDR, pResult);
	else
		m_bIsContext = false;
}


void CViewTree::OnTvnSelchanging(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	OutputDebugString(_T("****CViewTree::OnTvnSelchanging\n"));
	*pResult = 0;
}


void CViewTree::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: aggiungere qui il codice del gestore di notifiche del controllo
	OutputDebugString(_T("****CViewTree::OnNMRClick\n"));
	m_bIsContext = true;
	*pResult = 0;
}


void CViewTree::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: aggiungere qui il codice del gestore di messaggi e/o chiamare il codice predefinito
	OutputDebugString(_T("****CViewTree::OnRButtonDown\n"));
	CTreeCtrl::OnRButtonDown(nFlags, point);
}


void CViewTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: aggiungere qui il codice del gestore di notifiche del controllo
	OutputDebugString(_T("****CViewTree::OnNMClick\n"));
	*pResult = 0;
}


void CViewTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: aggiungere qui il codice del gestore di messaggi e/o chiamare il codice predefinito
	OutputDebugString(_T("****CViewTree::OnLButtonDblClk\n"));
	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}


void CViewTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: aggiungere qui il codice del gestore di messaggi e/o chiamare il codice predefinito
	OutputDebugString(_T("****CViewTree::OnLButtonDown\n"));
	CTreeCtrl::OnLButtonDown(nFlags, point);
}


void CViewTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: aggiungere qui il codice del gestore di messaggi e/o chiamare il codice predefinito
	OutputDebugString(_T("****CViewTree::OnLButtonUp\n"));
	CTreeCtrl::OnLButtonUp(nFlags, point);
}
