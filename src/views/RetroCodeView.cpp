/*****************************************************************************

	RetroCode - An IDE for retro development

	RetroCodeView.cpp
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
#include <stdafx.h>
#include <main\RetroCode.h>
#include "RetroCodeView.h"
#include "ScintillaView.h"
#include <resource.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const TCHAR* g_cppKeyWords = 
  _T("and and_eq asm auto bitand bitor bool break ")
  _T("case catch char class compl const const_cast continue ")
  _T("default delete do double dynamic_cast else enum explicit export extern false float for ")
  _T("friend goto if inline int long mutable namespace new not not_eq ")
  _T("operator or or_eq private protected public ")
  _T("register reinterpret_cast return short signed sizeof static static_cast struct switch ")
  _T("template this throw true try typedef typeid typename union unsigned using ")
  _T("virtual void volatile wchar_t while xor xor_eq ");


IMPLEMENT_DYNCREATE(CRetroCodeView, CScintillaView)

BEGIN_MESSAGE_MAP(CRetroCodeView, CScintillaView)
/*  ON_COMMAND(ID_OPTIONS_ADDMARKER, &CRetroCodeView::OnOptionsAddmarker)
  ON_COMMAND(ID_OPTIONS_DELETEMARKER, &CRetroCodeView::OnOptionsDeletemarker)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_DELETEMARKER, &CRetroCodeView::OnUpdateOptionsDeletemarker)
  ON_COMMAND(ID_OPTIONS_FIND_NEXTMARKER, &CRetroCodeView::OnOptionsFindNextmarker)
  ON_COMMAND(ID_OPTIONS_FIND_PREVMARKER, &CRetroCodeView::OnOptionsFindPrevmarker)
  ON_COMMAND(ID_OPTIONS_FOLD_MARGIN, &CRetroCodeView::OnOptionsFoldMargin)
  ON_COMMAND(ID_OPTIONS_SELECTION_MARGIN, &CRetroCodeView::OnOptionsSelectionMargin)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_SELECTION_MARGIN, &CRetroCodeView::OnUpdateOptionsSelectionMargin)
  ON_COMMAND(ID_OPTIONS_VIEW_LINENUMBERS, &CRetroCodeView::OnOptionsViewLinenumbers)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIEW_LINENUMBERS, &CRetroCodeView::OnUpdateOptionsViewLinenumbers)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_ADDMARKER, &CRetroCodeView::OnUpdateOptionsAddmarker)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_FOLD_MARGIN, &CRetroCodeView::OnUpdateOptionsFoldMargin)
  ON_UPDATE_COMMAND_UI(ID_INDICATOR_LINE, &CRetroCodeView::OnUpdateLine) 
  ON_UPDATE_COMMAND_UI(ID_INDICATOR_STYLE, &CRetroCodeView::OnUpdateStyle) 
  ON_UPDATE_COMMAND_UI(ID_INDICATOR_FOLD, &CRetroCodeView::OnUpdateFold) 
  ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, &CRetroCodeView::OnUpdateInsert)
  */
  ON_WM_ACTIVATE()
END_MESSAGE_MAP()

CRetroCodeView::CRetroCodeView()
{
  LoadMarginSettings();
}

void CRetroCodeView::OnDraw(CDC* /*pDC*/)
{
  const CRetroCodeDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  UNREFERENCED_PARAMETER(pDoc);
}

CRetroCodeDoc* CRetroCodeView::GetDocument()
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRetroCodeDoc)));
  return static_cast<CRetroCodeDoc*>(m_pDocument);
}

void CRetroCodeView::SetAStyle(int style, COLORREF fore, COLORREF back, int size, const char* face) 
{
  CScintillaCtrl& rCtrl = GetCtrl();

  rCtrl.StyleSetFore(style, fore);
  rCtrl.StyleSetBack(style, back);
  if (size >= 1)
    rCtrl.StyleSetSize(style, size);
  if (face) 
    rCtrl.StyleSetFont(style, face);
}

void CRetroCodeView::DefineMarker(int marker, int markerType, COLORREF fore, COLORREF back) 
{
  CScintillaCtrl& rCtrl = GetCtrl();

  rCtrl.MarkerDefine(marker, markerType);
  rCtrl.MarkerSetFore(marker, fore);
  rCtrl.MarkerSetBack(marker, back);
}

void CRetroCodeView::OnInitialUpdate() 
{
  //Let the base class do its thing
  __super::OnInitialUpdate();

  CScintillaCtrl& rCtrl = GetCtrl();

  //Setup the Lexer
  rCtrl.SetLexer(SCLEX_TASS64);
  rCtrl.SetKeyWords(0, g_cppKeyWords);

  //Setup styles
  SetAStyle(STYLE_BRACEBAD, RGB(0, 0, 0), RGB(0xff, 0xff, 0xff), 11, "Verdana");
  rCtrl.StyleClearAll();
  SetAStyle(SCE_C_DEFAULT, RGB(0, 0, 0));
  SetAStyle(SCE_C_COMMENT, RGB(0, 0x80, 0));
  SetAStyle(SCE_C_COMMENTLINE, RGB(0, 0x80, 0));
  SetAStyle(SCE_C_COMMENTDOC, RGB(0, 0x80, 0));
  SetAStyle(SCE_C_COMMENTLINEDOC, RGB(0, 0x80, 0));
  SetAStyle(SCE_C_COMMENTDOCKEYWORD, RGB(0, 0x80, 0));
  SetAStyle(SCE_C_COMMENTDOCKEYWORDERROR, RGB(0, 0x80, 0));
  SetAStyle(SCE_C_NUMBER, RGB(0, 0x80, 0x80));
  SetAStyle(SCE_C_WORD, RGB(0, 0, 0x80));
  rCtrl.StyleSetBold(SCE_C_WORD, 1);
  SetAStyle(SCE_C_STRING, RGB(0x80, 0, 0x80));
  SetAStyle(SCE_C_IDENTIFIER, RGB(0, 0, 0));
  SetAStyle(SCE_C_PREPROCESSOR, RGB(0x80, 0, 0));
  SetAStyle(SCE_C_OPERATOR, RGB(0x80, 0x80, 0));

  //Setup folding
  rCtrl.SetMarginWidthN(2, 16);
  rCtrl.SetMarginSensitiveN(2, TRUE);
  rCtrl.SetMarginTypeN(2, SC_MARGIN_SYMBOL);
  rCtrl.SetMarginMaskN(2, SC_MASK_FOLDERS);
  rCtrl.SetScintillaProperty(_T("fold"), _T("1"));

  //Setup markers
  DefineMarker(SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0xFF));
  DefineMarker(SC_MARKNUM_FOLDER, SC_MARK_PLUS, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
  DefineMarker(SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
  DefineMarker(SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
  DefineMarker(SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
  DefineMarker(SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
  DefineMarker(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));

  //Setup auto completion
  rCtrl.AutoCSetSeparator(10); //Use a separator of line feed

  //Setup call tips
  rCtrl.SetMouseDwellTime(1000);

  //Enable Multiple selection
  rCtrl.SetMultipleSelection(TRUE);

#ifdef _DEBUG
  AfxDump(this);
#endif
}

void CRetroCodeView::OnOptionsAddmarker()
{
  CScintillaCtrl& rCtrl = GetCtrl();
  const Sci_Position nPos = rCtrl.GetCurrentPos();
  const int nLine = rCtrl.LineFromPosition(nPos);
  rCtrl.MarkerAdd(nLine, 0);
}

#pragma warning(suppress: 26429)
void CRetroCodeView::OnUpdateOptionsAddmarker(CCmdUI* pCmdUI)
{
  CScintillaCtrl& rCtrl = GetCtrl();
  const Sci_Position nPos = rCtrl.GetCurrentPos();
  const int nLine = rCtrl.LineFromPosition(nPos);
  const int nBits = rCtrl.MarkerGet(nLine);
#pragma warning(suppress: 26486)
  pCmdUI->Enable((nBits & 0x1) == 0);
}

void CRetroCodeView::OnOptionsDeletemarker()
{
  CScintillaCtrl& rCtrl = GetCtrl();
  const Sci_Position nPos = rCtrl.GetCurrentPos();
  const int nLine = rCtrl.LineFromPosition(nPos);
  rCtrl.MarkerDelete(nLine, 0);
}

#pragma warning(suppress: 26429)
void CRetroCodeView::OnUpdateOptionsDeletemarker(CCmdUI* pCmdUI)
{
  CScintillaCtrl& rCtrl = GetCtrl();
  const Sci_Position nPos = rCtrl.GetCurrentPos();
  const int nLine = rCtrl.LineFromPosition(nPos);
  const int nBits = rCtrl.MarkerGet(nLine);
#pragma warning(suppress: 26486)
  pCmdUI->Enable(nBits & 0x1);
}

void CRetroCodeView::OnOptionsFindNextmarker()
{
  CScintillaCtrl& rCtrl = GetCtrl();
  const Sci_Position nPos = rCtrl.GetCurrentPos();
  const int nLine = rCtrl.LineFromPosition(nPos);
  const int nFoundLine = rCtrl.MarkerNext(nLine + 1, 0x1);
  if (nFoundLine >= 0)
    rCtrl.GotoLine(nFoundLine);
  else
    MessageBeep(MB_ICONHAND);
}

void CRetroCodeView::OnOptionsFindPrevmarker()
{
  CScintillaCtrl& rCtrl = GetCtrl();
  const Sci_Position nPos = rCtrl.GetCurrentPos();
  const int nLine = rCtrl.LineFromPosition(nPos);
  const int nFoundLine = rCtrl.MarkerPrevious(nLine - 1, 0x1);
  if (nFoundLine >= 0)
    rCtrl.GotoLine(nFoundLine);
  else
    MessageBeep(MB_ICONHAND);
}

void CRetroCodeView::OnOptionsFoldMargin()
{
  CScintillaCtrl& rCtrl = GetCtrl();
  const int nMarginWidth = rCtrl.GetMarginWidthN(2);
  if (nMarginWidth)
    rCtrl.SetMarginWidthN(2, 0);
  else
    rCtrl.SetMarginWidthN(2, 16);
}

#pragma warning(suppress: 26429)
void CRetroCodeView::OnUpdateOptionsFoldMargin(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
  pCmdUI->SetCheck(GetCtrl().GetMarginWidthN(2) != 0);
}

void CRetroCodeView::OnOptionsSelectionMargin()
{
  CScintillaCtrl& rCtrl = GetCtrl();
  const int nMarginWidth = rCtrl.GetMarginWidthN(1);
  if (nMarginWidth)
    rCtrl.SetMarginWidthN(1, 0);
  else
    rCtrl.SetMarginWidthN(1, 16);
}

#pragma warning(suppress: 26429)
void CRetroCodeView::OnUpdateOptionsSelectionMargin(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
  pCmdUI->SetCheck(GetCtrl().GetMarginWidthN(1) != 0);
}

void CRetroCodeView::OnOptionsViewLinenumbers()
{
  CScintillaCtrl& rCtrl = GetCtrl();
  const int nMarginWidth = rCtrl.GetMarginWidthN(0);
  if (nMarginWidth)
    rCtrl.SetMarginWidthN(0, 0);
  else
    rCtrl.SetMarginWidthN(0, 32);
}

#pragma warning(suppress: 26429)
void CRetroCodeView::OnUpdateOptionsViewLinenumbers(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
  pCmdUI->SetCheck(GetCtrl().GetMarginWidthN(0) != 0);
}

#pragma warning(suppress: 26429)
void CRetroCodeView::OnUpdateInsert(CCmdUI* pCmdUI)
{
  CString sText;
  if (GetCtrl().GetOvertype())
    VERIFY(sText.LoadString(ID_INDICATOR_OVR));
#pragma warning(suppress: 26486)
  pCmdUI->SetText(sText);
}

#pragma warning(suppress: 26429)
void CRetroCodeView::OnUpdateStyle(CCmdUI* pCmdUI)
{
   CScintillaCtrl& rCtrl = GetCtrl();
   const Sci_Position nPos = rCtrl.GetCurrentPos();
   const int nStyle = rCtrl.GetStyleAt(nPos);
   CString sLine;
   //TODO:
   //sLine.Format(IDS_STYLE_INDICATOR, nStyle);

   pCmdUI->SetText(sLine);
}

#pragma warning(suppress: 26429)
void CRetroCodeView::OnUpdateFold(CCmdUI* pCmdUI)
{
  CScintillaCtrl& rCtrl = GetCtrl();
  const Sci_Position nPos = rCtrl.GetCurrentPos();
  const int nLine = rCtrl.LineFromPosition(nPos);
  int nLevel = rCtrl.GetFoldLevel(nLine) & SC_FOLDLEVELNUMBERMASK;
  nLevel -= 1024;
  CString sLine;
  //TODO:
  //sLine.Format(IDS_FOLD_INDICATOR, nLevel);

  pCmdUI->SetText(sLine);
}

#pragma warning(suppress: 26429)
void CRetroCodeView::OnUpdateLine(CCmdUI* pCmdUI)
{
  CScintillaCtrl& rCtrl = GetCtrl();
  const Sci_Position nPos = rCtrl.GetCurrentPos();
  const int nLine = rCtrl.LineFromPosition(nPos);
  const Sci_Position nColumn = rCtrl.GetColumn(nPos);

  CString sLine;
  //TODO:
  //sLine.Format(IDS_LINE_INDICATOR, nLine, nColumn, nPos);

  pCmdUI->SetText(sLine);
}

//Some simple examples of implementing auto completion
void CRetroCodeView::OnCharAdded(_Inout_ SCNotification* /*pSCNotification*/)
{
  CScintillaCtrl& rCtrl = GetCtrl();

  //Get the previous 13 characters and if it is "scintilla is " case insensitive
  //then display a list which allows "very cool", "easy" or the "way cool!!"
  const Sci_Position nStartSel = rCtrl.GetSelectionStart();
  const Sci_Position nEndSel = rCtrl.GetSelectionEnd();
  if ((nStartSel == nEndSel) && (nStartSel >= 13))
  {
    Sci_TextRange tr;
#pragma warning(suppress: 26472)
    tr.chrg.cpMin = static_cast<Sci_PositionCR>(nStartSel - 13);
#pragma warning(suppress: 26472)
    tr.chrg.cpMax = static_cast<Sci_PositionCR>(nEndSel);
    CStringA sText;
    tr.lpstrText = sText.GetBuffer(13);
    rCtrl.GetTextRange(&tr);
    sText.ReleaseBuffer();

    //Display the auto completion list
    if (sText.CompareNoCase("scintilla is ") == 0)
    {
      //Display the auto completion list
      //rCtrl.AutoCSetOrder(SC_ORDER_PERFORMSORT);
      //int nOrder = rCtrl.AutoCGetOrder();
      rCtrl.AutoCShow(0, _T("very cool\neasy to use\nway cool!!"));
    }
  }

#ifdef _DEBUG
  //Test out some of the methods
  /*
  int nTabMinimumWidth = rCtrl.GetTabMinimumWidth();
  rCtrl.SetTabMinimumWidth(0);
  nTabMinimumWidth = rCtrl.GetTabMinimumWidth();
  BOOL bCommandEvents = rCtrl.GetCommandEvents();
  rCtrl.SetCommandEvents(FALSE);
  bCommandEvents = rCtrl.GetCommandEvents();
  Sci_Position nPos = rCtrl.GetCurrentPos();
  int nStyle = rCtrl.GetStyleAt(nPos);
  int nSubStyleStart = rCtrl.GetSubStylesStart(nStyle);
  int nSubStyleLength = rCtrl.GetSubStylesLength(nStyle);
  rCtrl.AllocateSubStyles(nStyle, 2);
  nSubStyleStart = rCtrl.GetSubStylesStart(nStyle);
  nSubStyleLength = rCtrl.GetSubStylesLength(nStyle);
  const int nDistanceToSecondaryStyles = rCtrl.DistanceToSecondaryStyles();
  UNREFERENCED_PARAMETER(nDistanceToSecondaryStyles);
  rCtrl.FreeSubStyles();
  int nLineTypesAllowed = rCtrl.GetLineEndTypesAllowed();
  const int nLineTypesSupported = rCtrl.GetLineEndTypesSupported();
  UNREFERENCED_PARAMETER(nLineTypesSupported);
  const int nLineTypesActive = rCtrl.GetLineEndTypesActive();
  UNREFERENCED_PARAMETER(nLineTypesActive);
  rCtrl.SetLineEndTypesAllowed(SC_LINE_END_TYPE_UNICODE);
  nLineTypesAllowed = rCtrl.GetLineEndTypesAllowed();
  rCtrl.AllocateExtendedStyles(3);
  rCtrl.ReleaseAllExtendedStyles();
  int nAutomaticFold = rCtrl.GetAutomaticFold();
  rCtrl.SetAutomaticFold(SC_AUTOMATICFOLD_SHOW | SC_AUTOMATICFOLD_CHANGE);
  nAutomaticFold = rCtrl.GetAutomaticFold();
  nPos = rCtrl.GetCurrentPos();
  int nLine = rCtrl.LineFromPosition(nPos);
  UNREFERENCED_PARAMETER(nLine);
  rCtrl.FoldAll(SC_FOLDACTION_TOGGLE);
  rCtrl.ScrollRange(40, 100);
  CString sLine1 = rCtrl.GetCurLine();
  CString sLine2 = rCtrl.GetLine(0);
  CString sProperty = rCtrl.GetScintillaProperty(_T("fold"));
  CString sProperty2 = rCtrl.GetPropertyExpanded(_T("fold"));
  CString sTempText = rCtrl.GetText(10);
  CString sFont = rCtrl.StyleGetFont(1);
  const int nProperty = rCtrl.GetPropertyInt(_T("fold"), 0);
  nProperty;
  rCtrl.AppendText(2, _T("XY"));
  rCtrl.SetTargetStart(0);
  rCtrl.SetTargetEnd(10);
  rCtrl.ReplaceTarget(2, _T("XY"));
  CString sAutoCCurrentText = rCtrl.AutoCGetCurrentText();
  CString sLexerLanguage = rCtrl.GetLexerLanguage();
  CString sPropertyNames = rCtrl.PropertyNames();
  const int nPropertyType = rCtrl.PropertyType(_T("fold.at.else"));
  nPropertyType;
  CString sPropertyDescription = rCtrl.DescribeProperty(_T("fold.at.else"));
  CString sDescribeKeyWordSets = rCtrl.DescribeKeyWordSets();
  rCtrl.SetWhitespaceSize(3);
  const int nWhitespaceSize = rCtrl.GetWhitespaceSize();
  nWhitespaceSize;
  rCtrl.SetFontQuality(2);
  const int nFontQuality = rCtrl.GetFontQuality();
  nFontQuality;
  rCtrl.SetFirstVisibleLine(3);
  rCtrl.SetMultiPaste(2);
  const int nMultiPaste = rCtrl.GetMultiPaste();
  nMultiPaste;
  rCtrl.SetCaretSticky(1);
  const int nCaretSticky = rCtrl.GetCaretSticky();
  nCaretSticky;
  CString sTag = rCtrl.GetTag(0);
  const char* pszPointer = rCtrl.GetCharacterPointer();
  pszPointer;
  rCtrl.SetSelectionNStart(0, 2);
  const Sci_Position nSelectionNStart = rCtrl.GetSelectionNStart(0);
  nSelectionNStart;
  const Sci_Position nSelectionNEnd = rCtrl.GetSelectionNEnd(0);
  nSelectionNEnd;
  rCtrl.SetAdditionalCaretsVisible(FALSE);
  const BOOL bAdditionCaretVisible = rCtrl.GetAdditionalCaretsVisible();
  bAdditionCaretVisible;
  const int nContractedFoldNext = rCtrl.ContractedFoldNext(0);
  nContractedFoldNext;
  rCtrl.VerticalCentreCaret();
  rCtrl.ChangeLexerState(0, -1);
  const int nCharacters = rCtrl.CountCharacters(0, 100);
  UNREFERENCED_PARAMETER(nCharacters);
  const BOOL bTest = rCtrl.GetSelectionEmpty();
  UNREFERENCED_PARAMETER(bTest);
  const int nPhasesDraw = rCtrl.GetPhasesDraw();
  rCtrl.SetPhasesDraw(nPhasesDraw);
  rCtrl.AddTabStop(0, 40);
  rCtrl.AddTabStop(0, 60);
  const int nNextTabStop = rCtrl.GetNextTabStop(0, 40);
  UNREFERENCED_PARAMETER(nNextTabStop);
  rCtrl.ClearTabStops(0);
  const int nIME = rCtrl.GetIMEInteraction();
  rCtrl.SetIMEInteraction(nIME);
  rCtrl.CallTipSetPosStart(100);
  const Sci_Position nPosition = rCtrl.PositionRelative(0, 3);
  UNREFERENCED_PARAMETER(nPosition);
  const int nMulti = rCtrl.AutoCGetMulti();
  rCtrl.AutoCSetMulti(nMulti);
  const BOOL bMouseSelection = rCtrl.GetMouseSelectionRectangularSwitch();
  rCtrl.SetMouseSelectionRectangularSwitch(bMouseSelection);
  rCtrl.DropSelectionN(0);
  rCtrl.SetRepresentation("\xe2\x84\xa6", "U+2126 \xe2\x84\xa6");
  char szRepresenation[32];
  szRepresenation[0] = '\0';
#pragma warning(suppress: 26485)
  rCtrl.GetRepresentation("\xe2\x84\xa6", szRepresenation);
  rCtrl.ClearRepresentation("\xe2\x84\xa6");
  nStyle = rCtrl.GetStyleFromSubStyle(2);
  const int nPrimaryStyle = rCtrl.GetPrimaryStyleFromStyle(nStyle);
  UNREFERENCED_PARAMETER(nPrimaryStyle);
  rCtrl.SetEdgeMode(EDGE_BACKGROUND);
  rCtrl.SetEdgeColour(RGB(200, 0, 0));
  rCtrl.MultiEdgeAddLine(3, RGB(0, 200, 0));
  rCtrl.MultiEdgeClearAll();
  rCtrl.SetMouseWheelCaptures(TRUE);
  const BOOL bCaptures = rCtrl.GetMouseWheelCaptures();
  UNREFERENCED_PARAMETER(bCaptures);
  rCtrl.ToggleFoldShowText(28, _T("PJ"));
  rCtrl.FoldDisplayTextSetStyle(SC_FOLDDISPLAYTEXT_BOXED);
  int nMode = rCtrl.GetTabDrawMode();
  rCtrl.SetTabDrawMode(SCTD_STRIKEOUT);
  nMode = rCtrl.GetTabDrawMode();
  rCtrl.UsePopUp(SC_POPUP_TEXT);
  const int nFrame = rCtrl.GetCaretLineFrame();
  rCtrl.SetCaretLineFrame(nFrame);
  const int nChars = rCtrl.CountCodeUnits(0, 3);
  UNREFERENCED_PARAMETER(nChars);
  nPos = rCtrl.PositionRelativeCodeUnits(0, 3);
  int nIndex = rCtrl.GetLineCharacterIndex();
  rCtrl.AllocateLineCharacterIndex(SC_LINECHARACTERINDEX_UTF16);
  nIndex = rCtrl.GetLineCharacterIndex();
  rCtrl.ReleaseLineCharacterIndex(SC_LINECHARACTERINDEX_UTF16);
  nLine = rCtrl.LineFromIndexPosition(0, 3);
  nPos = rCtrl.IndexPositionFromLine(nLine, 3);
  rCtrl.SetCharacterCategoryOptimization(0x1000);
  int nTemp = rCtrl.GetCharacterCategoryOptimization();
  nTemp = rCtrl.FoldDisplayTextGetStyle();
  rCtrl.FoldDisplayTextSetStyle(SC_FOLDDISPLAYTEXT_BOXED);
  nTemp = rCtrl.FoldDisplayTextGetStyle();
  rCtrl.SetDefaultFoldDisplayText(_T("X"));
  CString sTemp(rCtrl.GetDefaultFoldDisplayText());
  */
#endif

  //As another example, get the previous 2 characters and if it is "res" case sensitive
  //then display a list which allows "resize", "restart" and "restore"
  if ((nStartSel == nEndSel) && (nStartSel >= 3))
  {
    Sci_TextRange tr;
#pragma warning(suppress: 26472)
    tr.chrg.cpMin = static_cast<Sci_PositionCR>(nStartSel - 3);
#pragma warning(suppress: 26472)
    tr.chrg.cpMax = static_cast<Sci_PositionCR>(nEndSel);
    CStringA sText;
    tr.lpstrText = sText.GetBuffer(3);
    rCtrl.GetTextRange(&tr);
    sText.ReleaseBuffer();

    //Display the auto completion list
    if (sText == "res")
    {
      //Display the auto completion list
      rCtrl.AutoCShow(3, _T("resize\nrestart\nrestore"));
    }
  }

  //As another example, get the previous 16 characters and if it is "SAMPLE_INDICATOR" case insensitive
  //then display that text with a squiggly underline
  if ((nStartSel == nEndSel) && (nStartSel >= 16))
  {
    Sci_TextRange tr;
#pragma warning(suppress: 26472)
    tr.chrg.cpMin = static_cast<Sci_PositionCR>(nStartSel - 16);
#pragma warning(suppress: 26472)
    tr.chrg.cpMax = static_cast<Sci_PositionCR>(nEndSel);
    CStringA sText;
    tr.lpstrText = sText.GetBuffer(16);
    rCtrl.GetTextRange(&tr);
    sText.ReleaseBuffer();

    //Display the Sample indicator
    if (sText.CompareNoCase("sample_indicator") == 0)
    {
      //For demonstration purposes lets make the "C" Comment style into hotspots which turn red
      rCtrl.SetIndicatorCurrent(0);
      rCtrl.StyleSetHotSpot(SCE_C_COMMENT, TRUE);
      rCtrl.SetHotspotActiveFore(TRUE, RGB(255, 0, 0));

      //Show the indicator
#pragma warning(suppress: 26472)
      rCtrl.IndicatorFillRange(tr.chrg.cpMin, static_cast<int>(nStartSel));
    }
  }
}

//A simple example of call tips
void CRetroCodeView::OnDwellStart(_Inout_ SCNotification* pSCNotification)
{
  CScintillaCtrl& rCtrl = GetCtrl();

  //Only display the call tip if the scintilla window has focus
  const CWnd* pFocusWnd = GetFocus();
  if (pFocusWnd != nullptr)
  {
    if (pFocusWnd->GetSafeHwnd() == rCtrl.GetSafeHwnd())
    {
      //Get the previous 7 characters and next 7 characters around
      //the current dwell position and if it is "author " case insensitive
      //then display "PJ Naughter" as a call tip
      Sci_TextRange tr{};
#pragma warning(suppress: 26472)
      tr.chrg.cpMin = static_cast<Sci_PositionCR>(max(0, pSCNotification->position - 7));
#pragma warning(suppress: 26472)
      tr.chrg.cpMax = static_cast<Sci_PositionCR>(min(pSCNotification->position + 7, rCtrl.GetLength()));
      CStringA sText;
      tr.lpstrText = sText.GetBuffer(14);
      rCtrl.GetTextRange(&tr);
      sText.ReleaseBuffer();

      //Display the call tip
      sText.MakeUpper();
      if (sText.Find("AUTHOR ") != -1)
        rCtrl.CallTipShow(pSCNotification->position, _T("PJ Naughter"));
    }
  }
}

void CRetroCodeView::OnDwellEnd(_Inout_ SCNotification* /*pSCNotification*/)
{
  CScintillaCtrl& rCtrl = GetCtrl();

  //Cancel any outstanding call tip
  if (rCtrl.CallTipActive())
    rCtrl.CallTipCancel();
}

#pragma warning(suppress: 26434)
void CRetroCodeView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
  //Let the base class do its thing
  __super::OnActivate(nState, pWndOther, bMinimized);

  CScintillaCtrl& rCtrl = GetCtrl();

  //Cancel any outstanding call tip
  if (nState == WA_INACTIVE && rCtrl.CallTipActive())
    rCtrl.CallTipCancel();
}

void CRetroCodeView::OnModifyAttemptRO(_Inout_ SCNotification* /*pSCNotification*/)
{
	//TODO:
/*  if (AfxMessageBox(IDP_ALLOW_MODIFY_READONLY_FILE, MB_YESNO) == IDYES)
    GetCtrl().SetReadOnly(FALSE);*/
}

#pragma warning(suppress: 26440)
void CRetroCodeView::OnModified(_Inout_ SCNotification* pSCNotification)
{
  if (pSCNotification->modificationType & SC_MOD_INSERTCHECK)
  {
  #ifdef _DEBUG
    //Just some demo code to test out SCI_CHANGEINSERTION
    CScintillaCtrl& rCtrl = GetCtrl();
#pragma warning(suppress: 26486)
    if (strcmp(pSCNotification->text, "Dublin") == 0)
      rCtrl.ChangeInsertion(18, _T("Capital of Ireland"));
  #endif
  }
}

std::unique_ptr<CScintillaCtrl> CRetroCodeView::CreateScintillaControl()
{
  return std::make_unique<CScintillaCtrl>();
}
