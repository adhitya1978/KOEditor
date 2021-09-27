
// MyKO.h : main header file for the MyKO application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "CSCSkin3.h"

// CMyKOApp:
// See MyKO.cpp for the implementation of this class
//

class CMyKOApp : public CWinApp
{
public:
	CMyKOApp();
	CSCSkin3* m_pSkin;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	DECLARE_MESSAGE_MAP()
};

extern CMyKOApp theApp;
