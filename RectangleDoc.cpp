// RectangleDoc.cpp : implementation of the CRectangleDoc class
//

#include "stdafx.h"
#include "Rectangle.h"
#include "RectangleDoc.h"
#include <stdlib.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRectangleDoc

IMPLEMENT_DYNCREATE(CRectangleDoc, CDocument)

BEGIN_MESSAGE_MAP(CRectangleDoc, CDocument)
	//{{AFX_MSG_MAP(CRectangleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRectangleDoc construction/destruction

CRectangleDoc::CRectangleDoc():m_dwGenNum(50)
{
	// TODO: add one-time construction code here
	srand(static_cast<unsigned int>(time(NULL)));
}

CRectangleDoc::~CRectangleDoc()
{
}

BOOL CRectangleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRectangleDoc serialization

void CRectangleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRectangleDoc diagnostics

#ifdef _DEBUG
void CRectangleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRectangleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRectangleDoc commands

///////////////////////////////////////////////////////////////////

void CRectangleDoc::Generate(const CRect& rcArea)
{
	int cx, cy;
	Erase();
	m_arPoint.SetSize(m_dwGenNum);
	for(DWORD i=0; i<m_dwGenNum; i++)
	{
		cx = rcArea.left + rand()%rcArea.Width();
		cy = rcArea.top + rand()%rcArea.Height();
		m_arPoint.SetAt(i, CPoint(cx, cy));
	}
}

void CRectangleDoc::Erase()
{
	m_arPoint.RemoveAll();
	m_listPolygon.RemoveAll();
	m_arRect.RemoveAll();
}

//////////////////////////////////////////////////////////////////

void CRectangleDoc::CreatePolygon()
{
	int i;
	POSITION pos;
	BOOL	bLine = TRUE;
	if(m_arPoint.GetSize() ==0 )			// empty->exit
		return;
	CPoint ptLeft = m_arPoint[0];
	for(i=1; i<m_arPoint.GetSize(); i++)	//find left point of polygon
		if(m_arPoint[i].x < ptLeft.x)
			ptLeft = m_arPoint[i];

	for(i=0; i< m_arPoint.GetSize();i++)	// vertical line?
		if(m_arPoint[i].x != ptLeft.x)
		{
			bLine = FALSE;
			break;
		}
	if(bLine)								// yes -> find min&max y
	{
		int nMinY	= ptLeft.y;
		int nMaxY	= ptLeft.y;
		for(i=0; i<m_arPoint.GetSize();i++)				
		{
			if(m_arPoint[i].y > nMaxY)
				nMaxY = m_arPoint[i].y;
			if(m_arPoint[i].y < nMinY)
				nMinY = m_arPoint[i].y;
		}
		m_listPolygon.AddTail(CPoint(ptLeft.x, nMinY));	// add head&tail
		m_listPolygon.AddTail(CPoint(ptLeft.x, nMaxY));
		return;
	}
	bLine = TRUE;
	for(i=0; i< m_arPoint.GetSize();i++)	// horizontal line?
		if(m_arPoint[i].y != ptLeft.y)
		{
			bLine = FALSE;
			break;
		}
	if(bLine)								// yes -> find min&max y
	{
		int nMinX	= ptLeft.x;
		int nMaxX	= ptLeft.x;
		for(i=0; i<m_arPoint.GetSize();i++)				
		{
			if(m_arPoint[i].x > nMaxX)
				nMaxX = m_arPoint[i].x;
			if(m_arPoint[i].y < nMinX)
				nMinX = m_arPoint[i].x;
		}
		m_listPolygon.AddTail(CPoint(nMinX, ptLeft.y));	// add head&tail
		m_listPolygon.AddTail(CPoint(nMaxX, ptLeft.y));
		return;
	}
	//////////////////////////////////////////////
	SortPoint(ptLeft);								// so we have normal polygon or inclined line
	m_arPoint.Add(ptLeft);							// sort points 
	m_listPolygon.AddTail(/*m_arPoint[0]*/ptLeft);	// left point - first point of polygon  
	for(i=1; i<m_arPoint.GetSize(); i++)			// find first non left point
	{
		if(m_arPoint[i] != m_arPoint[i-1])
		{
			m_listPolygon.AddTail(m_arPoint[i]);
			i++;
			break;
		}
	}
	CPoint ptTail, ptPreTail,pt;
	for(; i<m_arPoint.GetSize(); i++)				// create convex polygon from sorted array
	{
		pos = m_listPolygon.GetTailPosition();		// see 3 point ptPreTail->ptTail->m_arPoint[i]
		ptTail		= m_listPolygon.GetPrev(pos);
		ptPreTail	= m_listPolygon.GetPrev(pos);
		pt = m_arPoint[i];
		if(m_arPoint[i] == ptTail || m_arPoint[i] == ptPreTail)
			continue;
		if(m_arPoint[i].x == ptPreTail.x &&			// sorting of vertical line 
			ptTail.x == ptPreTail.x)
		{
		//	if(ptPreTail.y < ptLeft.y && )
			m_listPolygon.RemoveTail();
			m_listPolygon.AddTail(m_arPoint[i]);
			continue;
		}
		if(m_arPoint[i].y == ptPreTail.y &&			// sorting of horizontal line
			ptTail.y == ptPreTail.y)
		{
			if(ptPreTail.x < m_arPoint[i].x && 
				m_arPoint[i].x < ptTail.x)
			{
				continue;
			}
			else
			{
				m_listPolygon.RemoveTail();
				m_listPolygon.AddTail(m_arPoint[i]);
			}
			continue;
		}
		if( ( m_arPoint[i].x - ptPreTail.x )*		//go left or right?
			( -ptTail.y + ptPreTail.y) >=
			( m_arPoint[i].y - ptPreTail.y )*
			( -ptTail.x + ptPreTail.x ) )
		{
			m_listPolygon.AddTail(m_arPoint[i]);	// right -> clockwise
		}
		else
		{
			m_listPolygon.RemoveTail();				// left -> non convex -> go back
			i--;
		}
	}
	m_arPoint.RemoveAt(m_arPoint.GetUpperBound());	//remove last point
	if(m_listPolygon.GetTail() == ptLeft)
		m_listPolygon.RemoveTail();
}

//////////////////////////////////////////////////////////////////

void CRectangleDoc::SortPoint(const CPoint& point)
{
/*	int i, j;							//buble sorting(will be censored)
	CPoint ptTemp1, ptTemp2;
	int nCount = m_arPoint.GetSize();
	for(i=1; i<nCount; i++)		
		for(j=nCount-1; j>=i; j--)
		{
			ptTemp1 = m_arPoint.GetAt(j-1);
			ptTemp2 = m_arPoint.GetAt(j);
			if(IsSwap(ptTemp1, ptTemp2,point))
			{
				m_arPoint.SetAt(j-1, ptTemp2);
				m_arPoint.SetAt(j, ptTemp1);
			}
		}*/
	QuickSort(0, m_arPoint.GetUpperBound(), point); //Hoar sorting
}

void CRectangleDoc::QuickSort(int nLeft, int nRight, const CPoint& ptLeft)
{
	int i = nLeft, j = nRight;
	CPoint pt1, pt2;
	pt1 = m_arPoint[(nLeft+nRight)/2];
	do
	{
		while( IsSwap(pt1, m_arPoint[i], ptLeft) && i<nRight ) i++;
		while( IsSwap(m_arPoint[j], pt1, ptLeft) && j>nLeft ) j--;
		if(i <= j)
		{
			pt2 = m_arPoint[i];		// swap
		//	pt3 = m_arPoint[j];
			m_arPoint.SetAt(i, m_arPoint[j]);
			m_arPoint.SetAt(j, pt2);
			i++;
			j--;
		}
	}
	while( i <= j );
	if(nLeft<j) QuickSort(nLeft, j, ptLeft);	//recursing
	if(i<nRight) QuickSort(i, nRight, ptLeft);
}
//////////////////////////////////////////////////////////////////

void CRectangleDoc::CreateRectangle()
{
	if(m_listPolygon.IsEmpty())	
		return;
	m_arRect.SetSize(5);
	FindVertex();			// find far vertices - left, right, up and a polygon's edge
	int nx = m_arRect[1].x - m_arRect[0].x;		// normal line
	int ny = m_arRect[1].y - m_arRect[0].y;
	int c1 = -ny*m_arRect[1].x + nx*m_arRect[1].y;		// ax + by + c = 0 - line
	int c2 = -nx*m_arRect[2].x - ny*m_arRect[2].y;
	int c3 = -ny*m_arRect[3].x + nx*m_arRect[3].y;
	int c4 = -nx*m_arRect[4].x - ny*m_arRect[4].y;
	m_arRect.SetAt( 0, FindPoint(ny, -nx, c1, nx, ny, c4) );	// find 4 rectangle's corners
	m_arRect.SetAt( 1, FindPoint(ny, -nx, c1, nx, ny, c2) );	// find cross points of lines
	m_arRect.SetAt( 2, FindPoint(ny, -nx, c3, nx, ny, c2) );
	m_arRect.SetAt( 3, FindPoint(ny, -nx, c3, nx, ny, c4) );
	m_arRect.RemoveAt(4);		//for rectangle we need 4 points - vertices
}


void CRectangleDoc::FindVertex()
{
	int i, nLeft, nRight, nPos;
	POSITION posHead;
	CPoint	ptX, ptY, pt1, pt2, pt3, ptUp, ptLeft, ptRight;
	double	fDist1, fDist2, fDist3, fLength;
	double	fSquare = 10e+100, fMaxUp, fMaxLeft, fMinRight;
	m_listPolygon.AddTail(m_listPolygon.GetHead()); // add for this 0->1->2->3->4->0
	for(i=0; i<m_listPolygon.GetCount()-1; i++)		// for each side find 5 points
	{
		nRight	= m_listPolygon.GetCount()-1;
		nLeft	= 1;
		posHead	= m_listPolygon.GetHeadPosition();
		ptX		= m_listPolygon.GetNext(posHead);
		ptY		= m_listPolygon.GetAt(posHead);
		fLength	= sqrt(	static_cast<double>((ptY.x - ptX.x)*(ptY.x - ptX.x) +
											(ptY.y - ptX.y)*(ptY.y - ptX.y) ));
		fMaxUp = 0;
		///find upper point of polygon
		while(nLeft != nRight)
		{
			nPos	= (nLeft+nRight)/2;
			pt1	= m_listPolygon.GetAt(m_listPolygon.FindIndex(nPos-1));
			pt2	= m_listPolygon.GetAt(m_listPolygon.FindIndex(nPos));
			pt3	= m_listPolygon.GetAt(m_listPolygon.FindIndex(nPos+1));
			fDist1 = abs((ptY.y - ptX.y)*(pt1.x - ptX.x) -
						(ptY.x - ptX.x)*(pt1.y - ptX.y)  )/fLength;
			fDist2 = abs((ptY.y - ptX.y)*(pt2.x - ptX.x) -
						(ptY.x - ptX.x)*(pt2.y - ptX.y)  )/fLength;
			fDist3 = abs((ptY.y - ptX.y)*(pt3.x - ptX.x) -
						(ptY.x - ptX.x)*(pt3.y - ptX.y)  )/fLength;
			if(fDist2 >= fDist1 && fDist2 >= fDist3)		// maximum
			{
				break;
			}
			if(fDist2 >= fDist1 && fDist3 > fDist2)		// go up
				nLeft = nPos;
			else
				nRight = nPos;			// go down
		}
		fMaxUp = fDist2;
		ptUp = pt2;
		///find left point
		nRight	= m_listPolygon.GetCount()-1;
		nLeft	= 0;
		fMaxLeft = 0; 
		while(nLeft != nRight)
		{
			nPos	= (nLeft+nRight)/2;
			pt1	= m_listPolygon.GetAt(m_listPolygon.FindIndex(nPos-1));
			pt2	= m_listPolygon.GetAt(m_listPolygon.FindIndex(nPos));
			pt3	= m_listPolygon.GetAt(m_listPolygon.FindIndex(nPos+1));
			fDist1 = ( (ptY.x - ptX.x)*(pt1.x - ptX.x)+
					   (ptY.y - ptX.y)*(pt1.y - ptX.y) )/fLength;
			fDist2 = ( (ptY.x - ptX.x)*(pt2.x - ptX.x)+
					   (ptY.y - ptX.y)*(pt2.y - ptX.y) )/fLength;
			fDist3 = ( (ptY.x - ptX.x)*(pt3.x - ptX.x)+
					   (ptY.y - ptX.y)*(pt3.y - ptX.y) )/fLength;			
			if(fDist2 < 0)					//maximum have to be positive
			{
				nRight = nPos;
				continue;
			}
			if(fDist2 >= fDist1 && fDist2 >= fDist3)// maximum
			{
				break;
			}
			if(fDist2 >= fDist1 && fDist3 > fDist2)	// go up
				nLeft = nPos;
			else
				nRight = nPos;			// go down

		}
		m_listPolygon.RemoveHead();
		m_listPolygon.AddTail(m_listPolygon.GetHead());
		//find right point
		fMaxLeft = fDist2;
		ptLeft = pt2;
		fMinRight = 0;
		nRight	= m_listPolygon.GetCount()-1;
		nLeft	= 0;
		while(nLeft != nRight)
		{
			nPos	= (nLeft+nRight)/2;
			pt1	= m_listPolygon.GetAt(m_listPolygon.FindIndex(nPos-1));
			pt2	= m_listPolygon.GetAt(m_listPolygon.FindIndex(nPos));
			pt3	= m_listPolygon.GetAt(m_listPolygon.FindIndex(nPos+1));
			fDist1 = ( (ptY.x - ptX.x)*(pt1.x - ptY.x)+
					   (ptY.y - ptX.y)*(pt1.y - ptY.y) )/fLength;
			fDist2 = ( (ptY.x - ptX.x)*(pt2.x - ptY.x)+
					   (ptY.y - ptX.y)*(pt2.y - ptY.y) )/fLength;
			fDist3 = ( (ptY.x - ptX.x)*(pt3.x - ptY.x)+
					   (ptY.y - ptX.y)*(pt3.y - ptY.y) )/fLength;			
			if(fDist2 > 0)					//minimum is negative
			{
				nLeft = nPos;
				continue;
			}
			if(fDist2 <= fDist1 && fDist2 <= fDist3)// minimum
			{
				break;
			}
			if(fDist2 >= fDist1 && fDist3 > fDist2)	// go up
				nRight = nPos;
			else
				nLeft = nPos;			// go down

		}
		fMinRight = fDist2;
		ptRight = pt2;
		if(fMaxUp * (fabs(fMinRight) + fMaxLeft-fLength) < fSquare) //minimum ?
		{
			fSquare = fMaxUp * (fabs(fMinRight) + fMaxLeft-fLength);
			m_arRect.SetAt(0, ptX);
			m_arRect.SetAt(1, ptY);
			m_arRect.SetAt(2, ptLeft);
			m_arRect.SetAt(3, ptUp);
			m_arRect.SetAt(4, ptRight);
			CString str;
			str.Format("%f", fSquare);
//			AfxMessageBox(str);
		}
	}	
	m_listPolygon.RemoveTail();	//we add one vertex, now remove it
}
//////////////////////////////////////////////////////////////////

CPoint	CRectangleDoc::FindPoint(	double fA1, double fB1, double fC1,
									double fA2, double fB2, double fC2 )
{
	CPoint ptCross;	
	ptCross.x = long((-fC1*fB2 + fB1*fC2)/(fA1*fB2 - fB1*fA2));	// Kramer's method
	ptCross.y = long((-fC2*fA1 + fA2*fC1)/(fA1*fB2 - fB1*fA2)); 
	return ptCross;
}

//////////////////////////////////////////////////////////////////

BOOL CRectangleDoc::IsSwap(	const CPoint& ptFirst, 
							const CPoint& ptSecond,
							const CPoint& ptLeft)
{
	#define PI 3.14159265358
	double fArctan1, fArctan2;
	if(ptFirst == ptLeft)
		return FALSE;
	if(ptFirst.x == ptLeft.x)
	{
		if(ptFirst.y <= ptLeft.y)
			fArctan1 = PI/2;
		else
			fArctan1 = -PI/2;
	}
	else
		fArctan1 = atan( double	(-ptFirst.y + ptLeft.y)/ \
								(ptFirst.x - ptLeft.x) );
	////////////
	if(ptSecond.x == ptLeft.x)
	{
		if(ptSecond.y <= ptLeft.y)
			fArctan2 = PI/2;
		else
			fArctan2 = -PI/2;
	}
	else
		fArctan2 = atan( double	(-ptSecond.y + ptLeft.y)/ \
								(ptSecond.x - ptLeft.x) );
	//////////////////////
	if(fArctan1 == fArctan2)
	{
		if(fArctan1 == PI/2 || fArctan1 == -PI/2)
		{
			if(ptSecond.y > ptFirst.y)
				return TRUE;
			else 
				return FALSE;
		}
		if(ptSecond.x > ptFirst.x)
			return TRUE;
		else
			return FALSE;
	//	}
	}
	/////////////////////////
	if(fArctan1 < fArctan2)
		return TRUE;
	return FALSE;
}