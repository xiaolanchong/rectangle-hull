// RectangleView.cpp : implementation of the CRectangleView class
//

#include "stdafx.h"
#include "Rectangle.h"

#include "RectangleDoc.h"
#include "RectangleView.h"
#include "PointDlg.h"
#include "NumberDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRectangleView

IMPLEMENT_DYNCREATE(CRectangleView, CScrollView)

BEGIN_MESSAGE_MAP(CRectangleView, CScrollView)
	//{{AFX_MSG_MAP(CRectangleView)
	ON_COMMAND(ID_GENERATE, OnGenerate)
	ON_COMMAND(ID_ERASE, OnErase)
	ON_COMMAND(ID_POLYGON, OnPolygon)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_RECTANGLE, OnRectangle)
	ON_COMMAND(ID_NUMBER, OnNumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRectangleView construction/destruction

CRectangleView::CRectangleView()
{
	// TODO: add construction code here

}

CRectangleView::~CRectangleView()
{
}

BOOL CRectangleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRectangleView drawing

void CRectangleView::OnDraw(CDC* pDC)
{
	CRectangleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	DrawPoint(pDC);
	DrawPolygon(pDC);
	DrawRectangle(pDC);
}

void CRectangleView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CRectangleView diagnostics

#ifdef _DEBUG
void CRectangleView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CRectangleView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CRectangleDoc* CRectangleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRectangleDoc)));
	return (CRectangleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRectangleView message handlers

void CRectangleView::DrawPoint(CDC* pDC)
{
	CRectangleDoc* pDoc = GetDocument();
	CPoint point;
	if(pDoc->m_arPoint.GetSize() != 0)
	{
		CBrush Brush, *pPrevBrush;
		Brush.CreateSolidBrush(RGB(0, 0, 0));
		pPrevBrush = pDC->SelectObject(&Brush);
		for(int i=0; i<pDoc->m_arPoint.GetSize();i++)
		{
			point = pDoc->m_arPoint[i];
			pDC->Ellipse( point.x-2, point.y-2,
						  point.x + 2, point.y + 2);	
		}
		pDC->SelectObject(pPrevBrush);
	}
}

void CRectangleView::DrawPolygon(CDC* pDC)
{
	CRectangleDoc* pDoc = GetDocument();
	if(!pDoc->m_listPolygon.IsEmpty())
	{
		CBrush	*pPrevBrush;
		CPen	Pen,*pPrevPen;
		Pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		pPrevPen = pDC->SelectObject(&Pen);
		pPrevBrush = static_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));
		CPoint* points = new CPoint[pDoc->m_listPolygon.GetCount()];
		POSITION pos = pDoc->m_listPolygon.GetHeadPosition();
		for(int i=0; i<pDoc->m_listPolygon.GetCount();i++)
			points[i] = pDoc->m_listPolygon.GetNext(pos);
		pDC->Polygon(points, pDoc->m_listPolygon.GetCount());
		pDC->SelectObject(pPrevBrush);
		pDC->SelectObject(pPrevPen);
		delete points;
	}
}

void CRectangleView::DrawRectangle(CDC* pDC)
{
	CRectangleDoc* pDoc = GetDocument();
	if(pDoc->m_arRect.GetSize() == 0)
		return;
	CPoint* points = new CPoint[pDoc->m_arRect.GetSize()];
	CBrush	*pPrevBrush;
	CPen	Pen,*pPrevPen;
	Pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pPrevPen = pDC->SelectObject(&Pen);
	pPrevBrush = static_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));
	for(int i=0; i<pDoc->m_arRect.GetSize();i++)
		points[i] = pDoc->m_arRect[i];
	pDC->Polygon(points, pDoc->m_arRect.GetSize());
	pDC->SelectObject(pPrevBrush);
	pDC->SelectObject(pPrevPen);
	delete points;
}
//////////////////////////////////////////////////////////////////

void CRectangleView::OnGenerate() 
{
	// TODO: Add your command handler code here
	GetDocument()->Generate(CRect(50, 50, 450, 350));
	Invalidate();
}

//////////////////////////////////////////////////////////////////

void CRectangleView::OnErase() 
{
	// TODO: Add your command handler code here
	GetDocument()->Erase();
	Invalidate();
}

//////////////////////////////////////////////////////////////////

void CRectangleView::OnPolygon() 
{
	// TODO: Add your command handler code here
	
	GetDocument()->m_listPolygon.RemoveAll();
	DWORD dwTime = GetTickCount();
	GetDocument()->CreatePolygon();
	dwTime = GetTickCount() - dwTime;
	CString str;
	str.Format("%5.2f", dwTime/1000.0f);
//	AfxMessageBox(str);
	Invalidate();
}

void CRectangleView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	GetDocument()->m_arPoint.Add(point);
	InvalidateRect(CRect(point.x-5, point.y-5, point.x+5, point.y+5));
	CScrollView::OnLButtonDown(nFlags, point);
}

void CRectangleView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPointDlg dlg;
	dlg.m_nX = point.x;
	dlg.m_nY = point.y;
	if(dlg.DoModal() == IDOK)
	{
		CPoint point;
		GetDocument()->m_arPoint.Add(CPoint(dlg.m_nX,dlg.m_nY));
		Invalidate();
	}
	CScrollView::OnRButtonDown(nFlags, point);
}

void CRectangleView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	POSITION pos = GetDocument()->m_listPolygon.GetHeadPosition();
	CPoint ptVertex;
	for(int i=0; i<GetDocument()->m_listPolygon.GetCount(); i++)
	{
		ptVertex = GetDocument()->m_listPolygon.GetAt(pos);
		if( (abs(point.x-ptVertex.x)<5) && (abs(point.y - ptVertex.y)<5) )
		{
			CPointDlg dlg;
			dlg.m_nX = ptVertex.x;
			dlg.m_nY = ptVertex.y;
			dlg.DoModal();
			break;
		}
		GetDocument()->m_listPolygon.GetNext(pos);
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CRectangleView::OnRectangle() 
{
	// TODO: Add your command handler code here
//	if(GetDocument()->m_listPolygon.IsEmpty())
	GetDocument()->m_listPolygon.RemoveAll();
	GetDocument()->CreatePolygon();
	GetDocument()->CreateRectangle();
	Invalidate();
}

void CRectangleView::OnNumber() 
{
	// TODO: Add your command handler code here
	CNumberDlg dlg;
	dlg.m_dwGenNum = GetDocument()->m_dwGenNum;
	if(dlg.DoModal() == IDOK)
		GetDocument()->m_dwGenNum = dlg.m_dwGenNum;
}
