// AnimateStatic.cpp : implementation file
//

#include "stdafx.h"
#include "Animation.h"
#include "AnimateStatic.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimateStatic

CAnimateStatic::CAnimateStatic()
: m_nAnimationType(xtWindowsDefault)
, m_nAnimationDelay(500)
, m_nAnimationSteps(10)
{
	m_bAnimationFinished = FALSE;
}

CAnimateStatic::~CAnimateStatic()
{
}

BEGIN_MESSAGE_MAP(CAnimateStatic, CStatic)
	//{{AFX_MSG_MAP(CAnimateStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimateStatic message handlers

void CAnimateStatic::OnDraw(CDC* pDC)
{
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);

	CXTPBitmapDC bitmap(&dcCompatible, &m_bmpGear);

	BITMAP info;
	m_bmpGear.GetObject(sizeof(info), &info);

	pDC->BitBlt(0, 0, info.bmWidth, info.bmHeight, &dcCompatible, 0,0, SRCCOPY);
	pDC->Draw3dRect(0, 0, info.bmWidth, info.bmHeight, 0,0);
}

void CAnimateStatic::OnPaint() 
{
	CPaintDC dc(this);
	CXTPClientRect rClient(this);
	
	CXTMemDC memDC(&dc, rClient, GetXtremeColor(COLOR_WINDOW));
	OnDraw(&memDC);
	
	if (!m_bAnimationFinished)
	{
		// create animation device context.
		CXTAnimationMemDC animationDC(&dc, rClient, GetXtremeColor(COLOR_WINDOW));
		OnDraw(&animationDC);
		
		// set animation attributes.
		animationDC.Animate(m_nAnimationType, m_nAnimationSteps, m_nAnimationDelay);
		m_bAnimationFinished = TRUE;
	}
}

void CAnimateStatic::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();
	
	// add our custom animation handler.
	CXTAnimationMemDC::SetCustomAnimation(CustomAnimation);

	m_bmpGear.LoadBitmap(IDB_CODEJOCKGEAR);
}

void AFX_CDECL CAnimateStatic::CustomAnimation(CRect rc, CDC* pDestDC, CDC* pSrcDC, int nType, int nSteps, int nAnimationTime)
{
	switch(nType) 
	{
	case animateNoise: 
		{
			int nCount = (nAnimationTime / 100) * rc.Width() * rc.Height() / 2;
			for (int j = 0; j < nCount; j++)
			{
				CPoint pt(rand() % rc.Width(), rand() % rc.Height());
				pDestDC->SetPixel(pt, pSrcDC->GetPixel(pt));
			}
		}
		break;
	case animateStretch: 
		{
			for (int i = 0; i < rc.Height(); 
			i += (1 + (rc.Height() / nSteps)))
			{
				pDestDC->StretchBlt(rc.left, rc.top, rc.Width(), i, pSrcDC, 
					0, 0, rc.Width(), rc.Height(), SRCCOPY);
				Sleep(nAnimationTime / nSteps);
			}
		}
		break;
	case animateCircles: 
		{
			CXTMemDC backDC(pDestDC, rc, (COLORREF)-1L);
			backDC.FromDC();  // copy image from screen
			
			const int nDiameter =  16;
			
			for (int i = 0; i < nSteps; i++)
			{
				double dRadius = (double)nDiameter / 1.5 * double(i+1)/ nSteps;
				for(int y = 0; y < rc.Height(); y++ )
				{
					int yDist = abs( y % nDiameter - nDiameter/2 );
					
					for(int x = 0; x < rc.Width(); x++ )
					{
						int xDist = abs(x % nDiameter - nDiameter/2 );
						
						if( sqrt((double)(yDist*yDist) + (xDist*xDist)) < dRadius )
						{
							backDC.SetPixel(x, y, pSrcDC->GetPixel(x, y));
						}
					}
				} 
				
				pDestDC->BitBlt(rc.left, rc.top, 
					rc.Width(), rc.Height(), &backDC, 
					0, 0, SRCCOPY);
				
				Sleep(nAnimationTime / nSteps);
			}
		}
		break;
		
	default:
		CXTAnimationMemDC::DefaultAnimation(rc, pDestDC, pSrcDC, nType, nSteps, nAnimationTime);
	}
}

void CAnimateStatic::Animate()
{
	m_bAnimationFinished = FALSE;
	ShowWindow(SW_HIDE);
	ShowWindow(SW_SHOW);
}
