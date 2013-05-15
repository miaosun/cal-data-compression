// CompressDlg.h : header file
//

#if !defined(AFX_CompressDLG_H__CA7F3567_939A_11D7_B8FA_00C0DF05DA5F__INCLUDED_)
#define AFX_CompressDLG_H__CA7F3567_939A_11D7_B8FA_00C0DF05DA5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCompressDlg dialog

class CCompressDlg : public CDialog
{
// Construction
public:
	CCompressDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCompressDlg)
	enum { IDD = IDD_Compress_DIALOG };
	int		m_nComboAlgorithm;
	CString	m_strPTFile;
	CString	m_strCTFile;
	CString	m_strDPTFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCompressDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDecompress();
	afx_msg void OnPTFBrowse();
	afx_msg void OnCTFBrowse();
	afx_msg void OnDPTFBrowse();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CompressDLG_H__CA7F3567_939A_11D7_B8FA_00C0DF05DA5F__INCLUDED_)
