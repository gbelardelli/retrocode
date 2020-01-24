/*****************************************************************************

	RetroCode - An IDE for retro development

	ViewTree.h
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
#pragma once

/////////////////////////////////////////////////////////////////////////////
// Finestra CViewTree

class CViewTree : public CTreeCtrl
{
private:
	bool m_bIsContext;
	CView *m_lpFocusView;
// Costruzione
public:
	CViewTree() noexcept;

// Sostituzioni
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// Implementazione
public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()

	void manageMouseClick(NMHDR *pNMHDR, LRESULT *pResult, bool bSetFocus = false);

public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);

	void SelectItemForContextMenu(HTREEITEM hItem);
	afx_msg void OnTvnSelchanging(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
