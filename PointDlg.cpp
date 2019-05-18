// PointDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Rectangle.h"
#include "PointDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointDlg dialog


CPointDlg::CPointDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPointDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPointDlg)
	m_nX = 0;
	m_nY = 0;
	//}}AFX_DATA_INIT
}


void CPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointDlg)
	DDX_Text(pDX, IDC_EDITX, m_nX);
	DDX_Text(pDX, IDC_EDITY, m_nY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointDlg, CDialog)
	//{{AFX_MSG_MAP(CPointDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointDlg message handlers
