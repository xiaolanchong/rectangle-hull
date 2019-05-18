// RectangleView.h : interface of the CRectangleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLEVIEW_H__64310F07_8AD5_4FE2_B573_17D9B96F17B1__INCLUDED_)
#define AFX_RECTANGLEVIEW_H__64310F07_8AD5_4FE2_B573_17D9B96F17B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRectangleView : public CScrollView
{
protected: // create from serialization only
	CRectangleView();
	DECLARE_DYNCREATE(CRectangleView)

// Attributes
public:
	CRectangleDoc*	GetDocument();
	void			DrawPoint(CDC* pDC);
	void			DrawPolygon(CDC* pDC);
	void			DrawRectangle(CDC* pDC);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRectangleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRectangleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRectangleView)
	afx_msg void OnGenerate();
	afx_msg void OnErase();
	afx_msg void OnPolygon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRectangle();
	afx_msg void OnNumber();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RectangleView.cpp
inline CRectangleDoc* CRectangleView::GetDocument()
   { return (CRectangleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECTANGLEVIEW_H__64310F07_8AD5_4FE2_B573_17D9B96F17B1__INCLUDED_)
