
// MyKO.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MyKO.h"
#include "MyKODlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CMyKOApp

BEGIN_MESSAGE_MAP(CMyKOApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyKOApp construction

CMyKOApp::CMyKOApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

// The one and only CMyKOApp object

CMyKOApp theApp;


// CMyKOApp initialization

BOOL CMyKOApp::InitInstance()
{

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CoInitialize(NULL);
	AfxEnableControlContainer();
	//CWinApp::InitInstance();
	

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();
	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	//CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	//SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	//LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
#if _MSC_VER <= 1200 // MFC 6.0 or earlier 
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif
	

	m_pSkin = new CSCSkin3;
	m_pSkin->CreateDispatch(L"SkinCrafter.SCSkin3");
	m_pSkin->InitLicenKeys(L"SKINCRAFTER", L"SKINCRAFTER.COM", L"support@skincrafter.com", L"DEMOSKINCRAFTERLICENCE");
	m_pSkin->DefineLanguage(0);
	m_pSkin->InitDecoration(0);

	TCHAR Buffer[MAX_PATH];
	//The skin we load by default
	CString defaultSkin = TEXT("PlayerSkin.skf");

	//GetCurrentDirectory(MAX_PATH, Buffer);

	//defaultSkin.Format(TEXT("%s\\%s"), Buffer, TEXT("PlayerSkin.skf"));


	m_pSkin->LoadSkinFromFile(defaultSkin);
	m_pSkin->ApplySkin();

	MyKODlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	//m_pSkin->DeInitDecoration();

	// Delete the shell manager created above.
//	if (pShellManager != NULL)
//	{
//		delete pShellManager;
//	}
#ifndef _AFXDLL
	ControlBarCleanUp();
#endif
	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CMyKOApp::ExitInstance()
{
	m_pSkin->DeInitDecoration();
	delete m_pSkin;

	return CWinApp::ExitInstance();
}

