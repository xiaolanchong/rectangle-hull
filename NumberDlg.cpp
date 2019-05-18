// NumberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Rectangle.h"
#include "NumberDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNumberDlg dialog


CNumberDlg::CNumberDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNumberDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNumberDlg)
	m_dwGenNum = 0;
	//}}AFX_DATA_INIT
}


void CNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNumberDlg)
	DDX_Text(pDX, IDC_NUMBER, m_dwGenNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNumberDlg, CDialog)
	//{{AFX_MSG_MAP(CNumberDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumberDlg message handlers

