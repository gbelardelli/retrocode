#include <stdafx.h>
#include <RetroCodeEditor.h>

#include "RetroCodeManager.h"

#include "RetroCodeWorkspace.h"
#include "views\ProjectView.h"

RetroCodeProject *RetroCodeManager::GetActiveProject(void)
{
	return RetroCodeWorkspace::GetHinstance()->GetActiveProject();
}

CMDIFrameWndEx *RetroCodeManager::GetMainEditorFrame(void)
{
	return m_lpMainFrame;
}

void RetroCodeManager::SetMainEditorFrame(CMDIFrameWndEx *lpFrame)
{
	m_lpMainFrame = lpFrame;
}

CDockablePane *RetroCodeManager::GetProjectView(void)
{
	return nullptr;
}
