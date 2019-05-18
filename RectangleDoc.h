// RectangleDoc.h : interface of the CRectangleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLEDOC_H__0FE0B956_0109_4AF6_987D_562F5DF2EE2A__INCLUDED_)
#define AFX_RECTANGLEDOC_H__0FE0B956_0109_4AF6_987D_562F5DF2EE2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include <math.h>

class CRectangleDoc : public CDocument
{
protected: // create from serialization only
	CRectangleDoc();
	DECLARE_DYNCREATE(CRectangleDoc)

// Attributes
public:

	void	Generate(const CRect& rcArea);	//randomly generate point
	void	Erase();						// erase all points
	void	CreatePolygon();				// convex polygon
	void	CreateRectangle();				// final rectangle
	BOOL	IsSwap(	const CPoint& ptFirst,	// swap 2 points?
							const CPoint& ptSecond,
							const CPoint& ptLeft);
	void	SortPoint(const CPoint& point);			// sort point for polygon
	void	QuickSort(int nLeft, int nRight,		// hoar's sorting
						const CPoint& ptLeft);
	void	FindVertex();							// find 5 points
	CPoint	FindPoint(	double fA1, double fB1, double fC1,		// cross point of 2 lines
						double fA2, double fB2, double fC2 );

	CArray<CPoint, CPoint>	m_arPoint;				// all points
	CList<CPoint, CPoint>	m_listPolygon;			// polygon's points
	CArray<CPoint, CPoint>	m_arRect;				// rectangle's points
	DWORD					m_dwGenNum;				// number of points

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRectangleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRectangleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRectangleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECTANGLEDOC_H__0FE0B956_0109_4AF6_987D_562F5DF2EE2A__INCLUDED_)
