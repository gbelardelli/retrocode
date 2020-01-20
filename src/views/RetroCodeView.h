/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCodeView.h
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
#ifndef _RETROCODEVIEW_H_
#define _RETROCODEVIEW_H_

#include <views\ScintillaView.h>
#include <main\RetroCodeDoc.h>

class CRetroCodeView : public CScintillaView
{
protected: //create from serialization only
  CRetroCodeView();
  DECLARE_DYNCREATE(CRetroCodeView)

public:
	CRetroCodeDoc* GetDocument();

  void OnDraw(CDC* pDC) override;
  void OnInitialUpdate() override;

protected:
  afx_msg void OnOptionsAddmarker();
  afx_msg void OnOptionsDeletemarker();
  afx_msg void OnUpdateOptionsDeletemarker(CCmdUI* pCmdUI);
  afx_msg void OnOptionsFindNextmarker();
  afx_msg void OnOptionsFindPrevmarker();
  afx_msg void OnOptionsFoldMargin();
  afx_msg void OnOptionsSelectionMargin();
  afx_msg void OnUpdateOptionsSelectionMargin(CCmdUI* pCmdUI);
  afx_msg void OnOptionsViewLinenumbers();
  afx_msg void OnUpdateOptionsViewLinenumbers(CCmdUI* pCmdUI);
  afx_msg void OnUpdateOptionsAddmarker(CCmdUI* pCmdUI);
  afx_msg void OnUpdateOptionsFoldMargin(CCmdUI* pCmdUI);
  afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
  afx_msg void OnUpdateStyle(CCmdUI* pCmdUI);
  afx_msg void OnUpdateFold(CCmdUI* pCmdUI);
  afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
  afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

  DECLARE_MESSAGE_MAP()
  void OnCharAdded(_Inout_ SCNotification* pSCNotification) override;
  void OnDwellStart(_Inout_ SCNotification* pSCNotification) override;
  void OnDwellEnd(_Inout_ SCNotification* pSCNotification) override;
  void OnModifyAttemptRO(_Inout_ SCNotification* pSCNotification) override;
  void OnModified(_Inout_ SCNotification* pSCNotification) override;
  std::unique_ptr<CScintillaCtrl> CreateScintillaControl() override;

  void SetAStyle(int style, COLORREF fore, COLORREF back=RGB(0xff, 0xff, 0xff), int size=-1, const char *face=0);
  void DefineMarker(int marker, int markerType, COLORREF fore, COLORREF back);
};

#endif
// _RETROCODEVIEW_H_
