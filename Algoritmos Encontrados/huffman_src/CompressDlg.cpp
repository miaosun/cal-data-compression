// CompressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CompressDemo.h"
#include "CompressDlg.h"
#include "huffman.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompressDlg dialog

CCompressDlg::CCompressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompressDlg)
	m_nComboAlgorithm = AfxGetApp()->GetProfileInt("Options", "Algorithm", 0);
	m_strPTFile = AfxGetApp()->GetProfileString("Options", "Source file");
	m_strCTFile = AfxGetApp()->GetProfileString("Options", "Compressed file");
	m_strDPTFile = AfxGetApp()->GetProfileString("Options", "Decompressed file");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCompressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompressDlg)
	DDX_CBIndex(pDX, IDC_COMBO1, m_nComboAlgorithm);
	DDX_Text(pDX, IDC_EDIT1, m_strPTFile);
	DDX_Text(pDX, IDC_EDIT2, m_strCTFile);
	DDX_Text(pDX, IDC_EDIT3, m_strDPTFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCompressDlg, CDialog)
	//{{AFX_MSG_MAP(CCompressDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DECompress, OnDecompress)
	ON_BN_CLICKED(IDC_PTF_BROWSE, OnPTFBrowse)
	ON_BN_CLICKED(IDC_CTF_BROWSE, OnCTFBrowse)
	ON_BN_CLICKED(IDC_DPTF_BROWSE, OnDPTFBrowse)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompressDlg message handlers

BOOL CCompressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCompressDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCompressDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void Compress(LPCSTR lpcsSrcFile, LPCSTR lpcsDesFile, bool bCompress)
{
	int nFile = _open(lpcsSrcFile, _O_RDONLY|_O_BINARY, 0);
	int nFileLength = _filelength(nFile);
	BYTE *pFileBuffer = new BYTE[nFileLength];
	_read(nFile, pFileBuffer, nFileLength);
	_close(nFile);

	// compress or decompress file buffer
	BYTE *pDes;
	int nDesLen;
	DWORD dw = ::GetTickCount();
	if(bCompress)
		CompressHuffman(pFileBuffer, nFileLength, pDes, nDesLen);
	else
		DecompressHuffman(pFileBuffer, nFileLength, pDes, nDesLen);
	dw = ::GetTickCount() - dw;
	delete pFileBuffer;

	// open destination buffer
	nFile = _open(lpcsDesFile, _O_CREAT|_O_BINARY|_O_WRONLY, _S_IREAD|_S_IWRITE);
	// write file buffer
	_write(nFile, pDes, nDesLen);
	_close(nFile);

	free(pDes);

	CString str;
	str.Format("Elapsed time: %d ms", dw);
	AfxMessageBox(str);
}

void CCompressDlg::OnOK() 
{
	UpdateData(TRUE);

	Compress(m_strPTFile, m_strCTFile, true);
}

void CCompressDlg::OnDecompress() 
{
	UpdateData(TRUE);

	Compress(m_strCTFile, m_strDPTFile, false);
}

void CCompressDlg::OnPTFBrowse() 
{
	UpdateData(TRUE);

	CFileDialog dlg(TRUE, "", m_strPTFile, OFN_OVERWRITEPROMPT, "All Files (*.*) | *.*; ||", this);
	dlg.m_ofn.lpstrTitle = "Choose file to be enCompressed";
	if(dlg.DoModal() != IDOK)
		return;
	m_strPTFile = dlg.GetPathName();
	AfxGetApp()->WriteProfileString("Options", "Source file", m_strPTFile);

	UpdateData(FALSE);
}

void CCompressDlg::OnCTFBrowse() 
{
	UpdateData(TRUE);

	CFileDialog dlg(FALSE, "", m_strCTFile, OFN_OVERWRITEPROMPT, "All Files (*.*) | *.*; ||", this);
	dlg.m_ofn.lpstrTitle = "Choose file to be decompressed";
	if(dlg.DoModal() != IDOK)
		return;
	m_strCTFile = dlg.GetPathName();
	AfxGetApp()->WriteProfileString("Options", "Compressed file", m_strCTFile);

	UpdateData(FALSE);
}

void CCompressDlg::OnDPTFBrowse() 
{
	UpdateData(TRUE);

	CFileDialog dlg(FALSE, "", m_strDPTFile, OFN_OVERWRITEPROMPT, "All Files (*.*) | *.*; ||", this);
	dlg.m_ofn.lpstrTitle = "Choose decompressed file";
	if(dlg.DoModal() != IDOK)
		return;
	m_strDPTFile = dlg.GetPathName();
	AfxGetApp()->WriteProfileString("Options", "Decompressed file", m_strDPTFile);

	UpdateData(FALSE);
}

void CCompressDlg::OnDestroy() 
{
	UpdateData(TRUE);

	AfxGetApp()->WriteProfileInt("Options", "Algorithm", m_nComboAlgorithm);

	CDialog::OnDestroy();	
}

