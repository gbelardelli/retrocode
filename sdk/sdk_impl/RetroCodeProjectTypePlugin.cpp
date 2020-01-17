#include "stdafx.h"
#include <RetroCodeEditor.h>

int RetroCodeProjectTypePlugin::CreateProject(RetroCodeProject **newProject, CString strPrjName, CString strPrjPath, int nPrjID )
{
	// Normalize path
	CString normalPath = strPrjPath;
	if (normalPath.GetAt(normalPath.GetLength() - 1) != '\\')
		normalPath += "\\";

	CString fullPath = normalPath;
	fullPath += strPrjName;
	fullPath += ".rcproj";

	DWORD dwAttr = GetFileAttributes(normalPath);
	// Check path exists and is a dir.
	if (dwAttr == INVALID_FILE_ATTRIBUTES || !(dwAttr & FILE_ATTRIBUTE_DIRECTORY))
		return 1;

	// Check if file already exists
	if (GetFileAttributes(fullPath) != INVALID_FILE_ATTRIBUTES)
		return 2;

	HINSTANCE hOld = AfxGetResourceHandle();
	AfxSetResourceHandle(this->GetPluginHinstance());
	int nRes = onCreateProject(newProject, nPrjID);
	AfxSetResourceHandle(hOld);

	if (nRes != 0)
		return nRes;

	RetroCodeProject *lpPrj = *newProject;
	if(*newProject)
	{
		(*newProject)->setProjectName(strPrjName);
		(*newProject)->setProjectPath(normalPath);
		(*newProject)->setFullFilename(fullPath);
		(*newProject)->setProjectID(nPrjID);
		(*newProject)->setProjectArch(GetProjectTypeArch());
		(*newProject)->createRootItem();
		
		(*newProject)->onNewProject();
	}

	return 0;
}