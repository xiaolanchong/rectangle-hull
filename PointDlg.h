#if !defined(AFX_POINTDLG_H__6BF29E05_A590_45C7_9DE2_FCF3030068A6__INCLUDED_)
#define AFX_POINTDLG_H__6BF29E05_A590_45C7_9DE2_FCF3030068A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPointDlg dialog

class CPointDlg : public CDialog
{
// Construction
public:
	CPointDlg(CWnd* pParent = NULL);   // standard constructor
	

// Dialog Data
	//{{AFX_DATA(CPointDlg)
	enum { IDD = IDD_POINT };
	int		m_nX;
	int		m_nY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPointDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTDLG_H__6BF29E05_A590_45C7_9DE2_FCF3030068A6__INCLUDED_)
