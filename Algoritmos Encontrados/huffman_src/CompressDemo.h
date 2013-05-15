// CompressDemo.h : main header file for the CompressDemo application
//

#if !defined(AFX_CompressDemo_H__CA7F3565_939A_11D7_B8FA_00C0DF05DA5F__INCLUDED_)
#define AFX_CompressDemo_H__CA7F3565_939A_11D7_B8FA_00C0DF05DA5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCompressDemoApp:
// See CompressDemo.cpp for the implementation of this class
//

class CCompressDemoApp : public CWinApp
{
public:
	CCompressDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompressDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCompressDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CompressDemo_H__CA7F3565_939A_11D7_B8FA_00C0DF05DA5F__INCLUDED_)
