#if !defined(AFX_NUMBERDLG_H__87AA6511_5B2C_40E0_B451_6A2C51293CE3__INCLUDED_)
#define AFX_NUMBERDLG_H__87AA6511_5B2C_40E0_B451_6A2C51293CE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NumberDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumberDlg dialog

class CNumberDlg : public CDialog
{
// Construction
public:
	CNumberDlg(CWnd* pParent = NULL);   // standard constructor
//	DWORD	m_dwNum;

// Dialog Data
	//{{AFX_DATA(CNumberDlg)
	enum { IDD = IDD_NUMBER };
	DWORD	m_dwGenNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumberDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNumberDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMBERDLG_H__87AA6511_5B2C_40E0_B451_6A2C51293CE3__INCLUDED_)
