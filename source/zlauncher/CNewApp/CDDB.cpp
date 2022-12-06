/*
 CDDBDialog 클래스(CDDB.cpp)

  desc : DDB를 생성하고 처리하는 클래스.
  date : 2004년 5월 30일
  comp : 고려대학교 제어계측연구회(KUCIRA) - 임동환
         http://www.kucira.com
  text : MFC를 공부하는 사람 누구나 자유 배포 및 수정이 가능합니다. 단, 특정 개인이나
         단체의 이익을 위한 목적으로 사용되는 것은 금합니다.

  오류가 생겼을 경우엔 프로젝트에 msimg32.lib을 추가해줘야 합니다.
*/


#include "stdafx.h"
#include "CDDB.h"



/*************************************************************
 CDDB

  desc : 생성자
**************************************************************/
CDDB::CDDB()
{
	m_pParentDC			= NULL;						// Set parent window DC

	m_nWidth			= 0;						// Set width
	m_nHeight			= 0;						// Set height
	m_nColor			= RGB( 255, 255, 255);		// Set color
	m_nTransColor		= RGB( 255, 0,   255);		// Set transparent color
	m_CoordinateMode	= CM_RELATIVE;				// Set coordinate mode
}


/*************************************************************
 ~CDDB

  desc : 소멸자
**************************************************************/
CDDB::~CDDB()
{
	m_DC.DeleteDC();								// Delete memory DC
	m_pParentDC			= NULL;						// Reset parent window DC pointer

	m_nWidth			= 0;						// Reset width
	m_nHeight			= 0;						// Reset height
	m_nColor			= RGB( 255, 255, 255);		// Reset color
	m_nTransColor		= RGB( 255, 0,   255);		// Reset transparent color
	m_CoordinateMode	= CM_RELATIVE;				// Set coordinate mode
}


/*************************************************************
 CreateDDB

  desc : 지정한 크기의 DDB를 생성한다.
  arg  : pDC = 윈도우의 DC 포인터 입력
         width, height = 생성할 DDB의 크기
		 color = DDB를 채울 생상값(RGB) 입력
  ret  : true(=성공) or false(=실패)
  ex   : CreateDDB( GetDC(), 200, 100, RGB(255,255,255));
**************************************************************/
bool CDDB::CreateDDB( CDC* pDC, int width, int height, COLORREF color)
{
	if ( !m_DC.CreateCompatibleDC( pDC))			// Create memory DC
		return false;								// Fail


	m_pParentDC = pDC;								// Set parent window DC pointer

	// Create bitmap
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap( pDC, width, height);
	m_DC.SelectObject( &bitmap);

	// Initialize
	m_nWidth  = width;								// Set width
	m_nHeight = height;								// Set height
	m_DC.SetBkMode( TRANSPARENT);					// Set text background color

	// Fill color
	m_DC.FillSolidRect( 0, 0, width, height, color);
	m_nColor = color;


	return true;									// Success
}


/*************************************************************
 CreateDDB

  desc : 지정한 비트맵 리소스를 가진 DDB를 생성한다.
  arg  : pDC = 윈도우의 DC 포인터 입력
		 nIDResource = 이미지 리소스 ID
  ret  : true(=성공) or false(=실패)
  ex   : CreateDDB( GetDC(), IDB_BITMAP);
**************************************************************/
bool CDDB::CreateDDB( CDC* pDC, UINT nIDResource)
{
	if ( !m_DC.CreateCompatibleDC( pDC))			// Create memory DC
		return false;								// Fail


	m_pParentDC = pDC;								// Set parent window DC pointer

	// Create bitmap
	CBitmap bitmap;
	if ( !bitmap.LoadBitmap( nIDResource))
		return false;								// Load bitmap fail


	m_DC.SelectObject( &bitmap);					// Create bitmap

	// Initialize
	BITMAP bmpInfo;
	bitmap.GetBitmap( &bmpInfo);					// Get bitmap infomation
	m_nWidth  = bmpInfo.bmWidth;					// Get bitmap width size
	m_nHeight = bmpInfo.bmHeight;					// Get bitmap height size
	m_DC.SetBkMode( TRANSPARENT);					// Set text background color


	return true;									// Success
}


/*************************************************************
 CreateDDB

  desc : 지정한 파일로부터 비트맵을 가져와서 DDB를 생성한다.
  arg  : pDC = 윈도우의 DC 포인터 입력
		 szBmpFileName = 비트맵 파일 이름
  ret  : true(=성공) or false(=실패)
  ex   : CreateDDB( GetDC(), "..\bitmap.bmp");
**************************************************************/
bool CDDB::CreateDDB( CDC* pDC, LPCTSTR szBmpFileName)
{
	// 아직 구현 안했음

	return false;
}


/*************************************************************
 DeleteDDB

  desc : DDB를 삭제한다.
  arg  : none
  ret  : true(=성공) or false(=실패)
  exp  : DeleteDDB();
**************************************************************/
bool CDDB::DeleteDDB()
{
	// Delete DC
	if ( m_DC.DeleteDC() == TRUE)
	{
		m_DC.DeleteDC();							// Delete memory DC
		m_pParentDC			= NULL;					// Reset parent window DC pointer

		m_nWidth			= 0;					// Reset width
		m_nHeight			= 0;					// Reset height
		m_nColor			= RGB( 255, 255, 255);	// Reset color
		m_nTransColor		= RGB( 255, 0, 255);	// Reset transparent color
		m_CoordinateMode	= CM_RELATIVE;			// Set coordinate mode

		return true;								// Success
	}


	return  false;									// Fail
}


/*************************************************************
 Rendering

  desc : DDB 이미지의 전체를 parent window의 DC에 출력한다.
  arg  : none
  ret  : none
  ex   : Rendering();
**************************************************************/
void CDDB::Rendering( CDC* pDC)
{
	// Rendering
	if ( m_pParentDC)
	{
		// Copy memory bitmap
		pDC->BitBlt( 0, 0, m_nWidth, m_nHeight, &m_DC, 0, 0, SRCCOPY);
	}
}


/*************************************************************
 Rendering

  desc : DDB 이미지의 일부 영역을 parent window의 DC에 출력한다.
  arg  : x, y = 이미지가 출력될 parent window DC의 시작 좌표
         xSrc, ySrc = 출력할 이미지의 시작 좌표 입력
         xSrc, ySrc = 출력할 이미지의 크기 혹은 끝 좌표
  ret  : none
  ex   : Rendering( 200, 100, 300, 400, 100, 100);
**************************************************************/
void CDDB::Rendering( CDC* pDC, int x, int y, int xSrc, int ySrc, int dxSrc, int dySrc)
{
	// Coordinate mode is not relative
	if ( m_CoordinateMode != CM_RELATIVE)
		GetRelativeCoordinate( &xSrc, &ySrc, &dxSrc, &dySrc);


	// Rendering
	if ( m_pParentDC)
	{
		// Copy memory bitmap
		pDC->BitBlt( x, y, dxSrc, dySrc, &m_DC, xSrc, ySrc, SRCCOPY);
	}
}


/*************************************************************
 PutBitmap

  desc : DDB의 지정한 위치에 다른 DDB로부터 이미지 일부 영역을 복사한다.
  arg  : x, y = 출력을 시작할 위치 좌표 입력
		 *pDC = 출력할 이미지를 가져올 DC 포인터 입력
         xSrc, ySrc = Source DC에서 이미지를 가져올 시작 좌표 입력
		 dxSrc, dySrc = Source DC에서 이미지를 가져올 크기 혹은 끝 좌표
 		 width, height = 가져온 이미지를 출력하기 위한 크기
		 dwRop = 래스터 오퍼레이션(TRANSPARENT=투명색 처리, SRCCOPY, SRCAND, SRCOR...)
		 alpha = 투명값
  ret  : true(=성공) or false(=실패)
  ex   : PutBitmap( 100, 100, GetDC(), 200, 200, 300, 300, SRCCOPY, 255);
**************************************************************/
bool CDDB::PutBitmap( int x, int y, CDC *pDC, int xSrc, int ySrc, int dxSrc, int dySrc, DWORD dwRop, int alpha)
{
	return PutBitmap( x, y, pDC, xSrc, ySrc, dxSrc, dySrc, dxSrc, dySrc, dwRop, alpha);
}

bool CDDB::PutBitmap( int x, int y, CDC *pDC, int xSrc, int ySrc, int dxSrc, int dySrc, int width, int height, DWORD dwRop, int alpha)
{
	// Coordinate mode is not relative
	if ( m_CoordinateMode != CM_RELATIVE)
		GetRelativeCoordinate( &xSrc, &ySrc, &dxSrc, &dySrc);


	// Copy alphablended memory DC
	if ( alpha < 255)
	{
		BLENDFUNCTION blendFunc = { AC_SRC_OVER, 0, alpha, 0 };

		// Copy memory bitmap
		AlphaBlend( m_DC, x, y, width, height, pDC->m_hDC, xSrc, ySrc, dxSrc, dySrc, blendFunc);
	}

	// Copy transparent memory DC
	else if ( dwRop == TRANSPARENT)
	{
		// Copy memory bitmap
		TransparentBlt( m_DC, x, y, width, height, pDC->m_hDC, xSrc, ySrc, dxSrc, dySrc, m_nTransColor);
	}

	// Copy memory DC
	else
	{
		// Copy memory bitmap
		m_DC.StretchBlt( x, y, width, height, pDC, xSrc, ySrc, dxSrc, dySrc, dwRop);
	}


	return true;
}


/*************************************************************
 PutBitmap

  desc : DDB에 지정한 비트맵 리소스의 일부 영역을 출력한다.
  arg  : x, y = DDB에 이미지를 출력할 시작 좌표
		 nIDResource = 비트맵 리소스 ID
         xSrc, ySrc = Source DC에서 이미지를 가져올 시작 좌표 입력
		 dxSrc, dySrc = Source DC에서 이미지를 가져올 크기 혹은 끝 좌표
		 width, height = 가져온 이미지를 출력하기 위한 크기
		 dwRop = 래스터 오퍼레이션(TRANSPARENT=투명색 처리, SRCCOPY, SRCAND, SRCOR...)
		 alpha = 투명값
  ret  : true(=성공) or false(=실패)
  ex   : PutBitmap( 200, 100, IDB_BITMAP, 300, 400, 100, 100, 200, 200, SRCCOPY, 255);
**************************************************************/
bool CDDB::PutBitmap( int x, int y, UINT nIDResource, int xSrc, int ySrc, int dxSrc, int dySrc, DWORD dwRop, int alpha)
{
	return PutBitmap( x, y, nIDResource, xSrc, ySrc, dxSrc, dySrc, dxSrc, dySrc, dwRop, alpha);
}

bool CDDB::PutBitmap( int x, int y, UINT nIDResource, int xSrc, int ySrc, int dxSrc, int dySrc, int width, int height, DWORD dwRop, int alpha)
{
	// Get bitmap resource
	CDC NewDC;
	NewDC.CreateCompatibleDC( &m_DC);
	
	CBitmap NewBmp;
	if ( !NewBmp.LoadBitmap( nIDResource))
		return false;								// Fail


	CBitmap *pOldBmp = (CBitmap *)NewDC.SelectObject( &NewBmp);
	BITMAP bmpInfo;
	NewBmp.GetBitmap(&bmpInfo);


	// Put bitmap
	bool bRetVal = PutBitmap( x, y, &NewDC, xSrc, ySrc, dxSrc, dySrc, width, height, dwRop, alpha);

	NewDC.SelectObject( pOldBmp);


	return bRetVal;
}


/*************************************************************
 FillColor

  desc : DDB 전체를 지정한 색으로 채운다.
  arg  : color = 채울 색상(RGB)
  ret  : none
  ex   : FillColor( RGB(255,255,255));
**************************************************************/
void CDDB::FillColor( COLORREF color)
{
	m_DC.FillSolidRect( 0, 0, m_nWidth, m_nHeight, color);
}


/*************************************************************
 FillTiledBitmap

  desc : 지정한 비트맵 리소스를 타일 형태로 지정한 영역을 채운다.
  arg  : x, y = 비트맵으로 채워질 영역 시작 좌표
         dx, dy = 비트맵으로 채워질 영역 끝 좌표 혹은 크기
		 pDC = 이미지를 가져올 source DC의 포인터 입력
		 xSrc, ySrc = Source DC에서 이미지를 가져올 시작 좌표
		 dxSrc, dySrc = Source DC에서 이미지를 가져올 크기 혹은 끝 좌표
  ret  : true(=성공) or false(=실패)
  ex   : FillTiledBitmap( 100, 100, 200, 200, GetDC(), 50, 50, 100, 100);
**************************************************************/
bool CDDB::FillTiledBitmap( int x, int y, int dx, int dy, CDC *pDC, int xSrc, int ySrc, int dxSrc, int dySrc)
{
	// Coordinate mode is not absolute
	if ( m_CoordinateMode != CM_ABSOLUTE)
		GetAbsoluteCoordinate( &x, &y, &dx, &dy);

	// Coordinate mode is not relative
	if ( m_CoordinateMode != CM_RELATIVE)
		GetRelativeCoordinate( &xSrc, &ySrc, &dxSrc, &dySrc);


	// Fill with bitmap
	int px, py;
	int width, height;
	for ( py = y;  py < dy;  py += dySrc)			// Get size y
	{
		height = dy-py;
		if ( height > dySrc)
			height = dySrc;

		for ( px = x;  px < dx;  px += dxSrc)		// Get size x
		{
			width = dx-px;
			if ( width > dxSrc)
				width = dxSrc;

			// Copy memory bitmap
			m_DC.BitBlt( px, py, width, height, pDC, xSrc, ySrc, SRCCOPY);
		}
	}


	return true;
}


/*************************************************************
 FillTiledBitmap

  desc : DDB 전체를 지정한 비트맵 리소스를 타일 형태로 채운다.
  arg  : x, y = 비트맵으로 채워질 영역 시작 좌표
         dx, dy = 비트맵으로 채워질 영역 끝 좌표 혹은 크기
		 nIDResource = 채울 비트맵 리소스 ID
  		 xSrc, ySrc = Source DC에서 이미지를 가져올 시작 좌표
		 dxSrc, dySrc = Source DC에서 이미지를 가져올 크기 혹은 끝 좌표
  ret  : true(=성공) or false(=실패)
  ex   : FillTiledBitmap(  100, 100, 200, 200, IDB_BITMAP, 50, 50, 100, 100);
**************************************************************/
bool CDDB::FillTiledBitmap( int x, int y, int dx, int dy, UINT nIDResource, int xSrc, int ySrc, int dxSrc, int dySrc)
{
	// Get bitmap resource
	CDC NewDC;
	NewDC.CreateCompatibleDC( &m_DC);
	
	CBitmap NewBmp;
	if ( !NewBmp.LoadBitmap( nIDResource))
		return false;								// Fail


	CBitmap *pOldBmp = (CBitmap *)NewDC.SelectObject( &NewBmp);
	BITMAP bmpInfo;
	NewBmp.GetBitmap( &bmpInfo);


	// Fill with bitmap resource
	BOOL bRetVal = FillTiledBitmap( x, y, dx, dy, &NewDC, xSrc, ySrc, dxSrc, dySrc);

	NewDC.SelectObject( pOldBmp);


	return ( (bRetVal > 0) ? true : false);
}


/*************************************************************
 PutPixel

  desc : DDB에 점을 출력한다.
  arg  : x, y = DDB에 점을 출력할 좌표
         color = 점 색상
  ret  : none
  ex   : PutPixel( 200, 100, RGB(255,255,255));
**************************************************************/
void CDDB::PutPixel( int x, int y, COLORREF color)
{
	if ( color != NOCOLOR)
		m_nColor = color;							// Set color


	// Draw a pixel
	m_DC.SetPixel( x, y, m_nColor);					// Put pixel
}


/*************************************************************
 GetPixel

  desc : DDB에서 지정한 좌표의 색상값(RGB)을 구한다.
  arg  : x, y = 색상값을 구할 좌표(pixel)
  ret  : pixel의 색상값
  ex   : COLORREF Color = GetPixel( 200, 100);
**************************************************************/
COLORREF CDDB::GetPixel( int x, int y)
{
	return m_DC.GetPixel( x, y);					// Get pixel
}


/*************************************************************
 PutLine

  desc : DDB에 선을 출력한다.
  arg  : x, y = DDB에 선을 출력할 시작 좌표
         dx, dy = DDB에 선을 출력할 끝 좌표 혹은 크기
         color = 선 색상(RGB)
		 width = 선 두께
  ret  : none
  ex   : PutLine( 100, 100, 200, 200, RGB(255,255,255), 1);
**************************************************************/
void CDDB::PutLine( int x, int y, int dx, int dy, COLORREF color, int width)
{
	if ( color != NOCOLOR)
		m_nColor = color;							// Set color

	
	// Coordinate mode is not absolute
	if ( m_CoordinateMode != CM_ABSOLUTE)
		GetAbsoluteCoordinate( &x, &y, &dx, &dy);


	// Draw a line
	CPen pen;
	pen.CreatePen( PS_SOLID, width, m_nColor);
	CPen *pOldPen = (CPen *)m_DC.SelectObject( &pen);

	m_DC.MoveTo( x,	 y);
	m_DC.LineTo( dx, dy);
	m_DC.SelectObject( pOldPen);
}


/*************************************************************
 PutBox

  desc : DDB에 사각형을 출력한다.
  arg  : x, y = DDB에 사각형을 출력할 시작 좌표
         dx, dy = DDB에 사각형을 출력할 끝 좌표 혹은 크기
         color = 사각형 색상(RGB)
		 width = 선 두께
  ret  : none
  ex   : PutBox( 100, 100, 200, 200, RGB(255,255,255), 1);
**************************************************************/
void CDDB::PutBox( int x, int y, int dx, int dy, COLORREF color, int width)
{
	if ( color != NOCOLOR)
		m_nColor = color;							// Set color


	// Coordinate mode is not absolute
	if ( m_CoordinateMode != CM_ABSOLUTE)
		GetAbsoluteCoordinate( &x, &y, &dx, &dy);


	// Draw a box
	CPen pen;
	pen.CreatePen( PS_SOLID, width, m_nColor);
	CPen *pOldPen = (CPen *)m_DC.SelectObject( &pen);

	m_DC.MoveTo( x,		y);
	m_DC.LineTo( dx-1,	y);
	m_DC.LineTo( dx-1,	dy-1);
	m_DC.LineTo( x,		dy-1);
	m_DC.LineTo( x,		y-1);
	m_DC.SelectObject( pOldPen);
}


/*************************************************************
 PutFillBox

  desc : DDB에 내부를 채운 사각형을 출력한다.
  arg  : x, y = DDB에 사각형을 출력할 시작 좌표
         dx, dy = DDB에 사각형을 출력할 끝 좌표
         color = 사각형 색상(RGB)
  ret  : none
  ex   : PutFillBox( 200, 100, 100, 100, RGB(255,255,255));
**************************************************************/
void CDDB::PutFillBox( int x, int y, int dx, int dy, COLORREF color)
{
	if ( color != NOCOLOR)
		m_nColor = color;							// Set color

	
	// Coordinate mode is not relative
	if ( m_CoordinateMode != CM_RELATIVE)
		GetRelativeCoordinate( &x, &y, &dx, &dy);


	// Draw a rectangle
	m_DC.FillSolidRect( x, y, dx, dy, m_nColor);
}


/*************************************************************
 PutRoundBox

  desc : DDB에 둥근 사각형을 출력한다.
  arg  : x, y = DDB에 둥근 사각형을 출력할 시작 좌표
         dx, dy = DDB에 사각형을 출력할 끝 좌표 혹은 크기
		 radius = 모서리 원의 지름
         color = 사각형 색상(RGB)
		 width = 선 두께
  ret  : none
  ex   : PutRoundBox( 100, 100, 200, 200, 5, RGB(255,255,255), 1);
**************************************************************/
void CDDB::PutRoundBox( int x, int y, int dx, int dy, int radius, COLORREF color, int width)
{
	if ( color != NOCOLOR)
		m_nColor = color;							// Set color

	
	// Coordinate mode is not absolute
	if ( m_CoordinateMode != CM_ABSOLUTE)
		GetAbsoluteCoordinate( &x, &y, &dx, &dy);


	// Draw a round box
	CPen pen;
	pen.CreatePen( PS_SOLID, width, m_nColor);
	CPen *pOldPen = (CPen *)m_DC.SelectObject( &pen);

	m_DC.MoveTo( x+radius, y); 
	m_DC.AngleArc( x+radius, y+radius, radius, 90, 90); 
	m_DC.MoveTo( dx-1, y+radius); 
	m_DC.AngleArc( dx-radius-1, y+radius, radius, 0, 90); 
	m_DC.MoveTo( x, dy-radius-1); 
	m_DC.AngleArc( x+radius, dy-radius-1, radius, 180, 90); 
	m_DC.MoveTo( dx-radius-1, dy-1); 
	m_DC.AngleArc( dx-radius-1, dy-radius-1, radius, 270, 90); 

	m_DC.MoveTo( x+radius,		y); 
	m_DC.LineTo( dx-radius+1,	y); 
	m_DC.MoveTo( x+radius,		dy-1); 
	m_DC.LineTo( dx-radius+1,	dy-1); 
	m_DC.MoveTo( x,				y+radius); 
	m_DC.LineTo( x,				dy-radius+1); 
	m_DC.MoveTo( dx-1,			y+radius); 
	m_DC.LineTo( dx-1,			dy-radius+1); 

	m_DC.SelectObject( pOldPen);
}


/*************************************************************
 PutFillRoundBox

  desc : DDB에 사각형을 출력한다.
  arg  : x1, y1 = DDB에 사각형을 출력할 시작 좌표
         x2_or_width, y2_or_height = DDB에 사각형을 출력할 끝 좌표 혹은 크기
		 width = 선 두께
         color = 사각형 색상(RGB)
  ret  : none
  ex   : PutFillRoundBox( 100, 100, 200, 200, 5, RGB(255,255,255));
**************************************************************/
void CDDB::PutFillRoundBox( int x, int y, int dx, int dy, int radius, COLORREF color)
{
	if ( color != NOCOLOR)
		m_nColor = color;							// Set color


	// Coordinate mode is not absolute
	if ( m_CoordinateMode != CM_ABSOLUTE)
		GetAbsoluteCoordinate( &x, &y, &dx, &dy);


	// Draw a round box
	CPen pen;
	pen.CreatePen( PS_SOLID, 1, m_nColor);
	CPen *pOldPen = (CPen *)m_DC.SelectObject( &pen);

	CBrush brush;
	brush.CreateSolidBrush( m_nColor);
	CBrush *pOldBrush = (CBrush *)m_DC.SelectObject( &brush);


	m_DC.RoundRect( x, y, dx, dy, radius, radius);

	m_DC.SelectObject( pOldPen);
	m_DC.SelectObject( &pOldBrush);
}


/*************************************************************
 PutCircle

  desc : DDB에 원을 출력한다.
  arg  : x, y = 원을 출력할 중심점
         radius = 원의 반지름
         color = 원의 색상(RGB)
		 width = 선 두께
  ret  : none
  ex   : PutCircle( 100, 100, 50, RGB(0,0,0), 1);
  err  : 원래 사이즈보다 가로세로 1pixel씩 크게 찍힌다.
**************************************************************/
void CDDB::PutCircle( int x, int y, int radius, COLORREF color, int width)
{
	if ( color != NOCOLOR)
		m_nColor = color;							// Set color


	// Draw a circle
	CPen pen;
	pen.CreatePen( PS_SOLID, width, m_nColor);
	CPen *pOldPen = (CPen *)m_DC.SelectObject( &pen);

	m_DC.MoveTo( x+radius, y); 
	m_DC.AngleArc( x, y, radius, 0, 360); 

	m_DC.SelectObject( pOldPen);
}


/*************************************************************
 PutFillCircle

  desc : DDB에 내부를 채운 원을 출력한다.
  arg  : x, y = 원을 출력할 중심점
         radius = 원의 반지름
         color = 원의 색상(RGB)
  ret  : none
  ex   : PutFillCircle( 100, 100, 50, RGB(0,0,0));
**************************************************************/
void CDDB::PutFillCircle( int x, int y, int radius, COLORREF color)
{
	if ( color != NOCOLOR)
		m_nColor = color;							// Set color


	// Draw a circle
	CPen pen;
	pen.CreatePen( PS_SOLID, 1, m_nColor);
	CPen *pOldPen = (CPen *)m_DC.SelectObject( &pen);

	CBrush brush;
	brush.CreateSolidBrush( m_nColor);
	CBrush *pOldBrush = (CBrush *)m_DC.SelectObject( &brush);

	m_DC.Ellipse( x-radius, y-radius, x+radius, y+radius);

	m_DC.SelectObject( pOldPen);
	m_DC.SelectObject( pOldBrush);
}


/*************************************************************
 PutFillEllips

  desc : DDB에 내부를 채운 타원을 출력한다.
  arg  : x, y = 타원을 출력할 중심점
         radiusX, radiusY = 원의 x,y축 반지름
         color = 원의 색상(RGB)
  ret  : none
  ex   : PutFillEllips( 100, 100, 50, 30, RGB(0,0,0));
**************************************************************/
void CDDB::PutFillEllips( int x, int y, int rx, int ry, COLORREF color)
{
	if ( color != NOCOLOR)
		m_nColor = color;							// Set color


	// Draw a ellips
	CPen pen;
	pen.CreatePen( PS_SOLID, 1, m_nColor);
	CPen *pOldPen = (CPen *)m_DC.SelectObject( &pen);

	CBrush brush;
	brush.CreateSolidBrush( m_nColor);
	CBrush *pOldBrush = (CBrush *)m_DC.SelectObject( &brush);

	m_DC.Ellipse( x-rx, y-ry, x+rx, y+ry);

	m_DC.SelectObject( pOldPen);
	m_DC.SelectObject( pOldBrush);
}


/*************************************************************
 PutText

  desc : DDB에 글씨를 출력한다.
  arg  : x, y = DDB에 글씨를 출력할 시작 좌표
         nSize = 글씨 크기
		 lpszFont = 글씨 폰트
		 lpszMsg = 출력 내용
         color = 색상
		 nStyle = 글씨 스타일 ( TS_BOLD | TS_ITALIC | TS_UDLINE)
  ret  : none
  ex   : PutText( 200, 100, 14, "굴림", "PutText 예제", RGB(255,255,255), TS_BOLD);
**************************************************************/
void CDDB::PutText( int x, int y, int nSize, LPCTSTR lpszFont, LPCTSTR lpszMsg, COLORREF color, UINT nStyle)
{
	if ( color != NOCOLOR)
		m_nColor = color;							// Set color

	
	// Put text
	UINT nBold		= (nStyle & TS_BOLD)   ? FW_BOLD : FW_NORMAL;
	BYTE bItalic	= (nStyle & TS_ITALIC) ? true : false;
	BYTE bUnderLine	= (nStyle & TS_UDLINE) ? true : false;

	CFont font;
	font.CreateFont( nSize, 0, 0, 0, nBold, bItalic, bUnderLine, 0, ANSI_CHARSET,
	                 OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                 DEFAULT_PITCH | FF_SWISS, lpszFont);

	CFont *pOldFont = (CFont *)m_DC.SelectObject( &font);

	m_DC.SetTextColor( m_nColor);
	m_DC.TextOut( x, y, lpszMsg);
	m_DC.SelectObject( pOldFont);
}


/*************************************************************
 PutText

  desc : DDB의 지정한 영역 안에만 글씨를 출력한다.
  arg  : x, y = 글씨가 출력될 영역의 시작 좌표
         dx, dy = 글씨를 출력할 영역의 끝 좌표 혹은 크기
         nSize = 글씨 크기
		 lpszFont = 글씨 폰트
		 lpszMsg = 출력 내용
         color = 색상
		 nStyle = 글씨 스타일 ( TS_BOLD | TS_ITALIC | TS_UDLINE)
		 nAlign = 글씨 정렬( DT_LEFT | DT_CENTER | DT_RIGHT | DT_TOP | DT_VCENTER | DT_BOTTOM)
  ret  : none
  ex   : PutText( 200, 100, 300, 200, 14, "굴림", "PutText 예제", TS_BOLD, DT_CENTER|DT_VCENTER, RGB(255,255,255), TS_BOLD,  DT_CENTER);
**************************************************************/
void CDDB::PutText( int x, int y, int dx, int dy, int nSize, LPCTSTR lpszFont, LPCTSTR lpszMsg, COLORREF color, UINT nStyle, UINT nAlign)
{
	if ( color != NOCOLOR)
		m_nColor = color;							// Set color


	// Coordinate mode is not absolute
	if ( m_CoordinateMode != CM_ABSOLUTE)
		GetAbsoluteCoordinate( &x, &y, &dx, &dy);


	// Put text
	UINT nBold		= (nStyle & TS_BOLD)   ? FW_BOLD : FW_NORMAL;
	BYTE bItalic	= (nStyle & TS_ITALIC) ? true : false;
	BYTE bUnderLine	= (nStyle & TS_UDLINE) ? true : false;

	CFont font;
	font.CreateFont( nSize, 0, 0, 0, nBold, bItalic, bUnderLine, 0, ANSI_CHARSET,
	                 OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                 DEFAULT_PITCH | FF_SWISS, lpszFont);

	CFont *pOldFont = (CFont *)m_DC.SelectObject( &font);
	
	CRect rect;
	rect.top		= y;
	rect.left		= x;
	rect.right		= dx;
	rect.bottom		= dy;

	m_DC.SetTextColor( m_nColor);
	m_DC.DrawText( lpszMsg, (LPRECT)rect, nAlign);
	m_DC.SelectObject( pOldFont);
}



/*************************************************************
 GetRelativeCoordinate

  desc : 절대 좌표 값을 상대 좌표 값으로 변환한다
  arg  : *x1, *y1 = 시작 좌표
         *x2, *y2 = 끝 좌표
  ret  : none
**************************************************************/
void CDDB::GetRelativeCoordinate( int *x1, int *y1, int *x2, int *y2)
{
	*x2 = *x2 - *x1;							// Get width
	*y2 = *y2 - *y1;							// Get height
}


/*************************************************************
 GetAbsoluteCoordinate

  desc : 상대 좌표 값을 절대 좌표 값으로 변환한다
  arg  : *x1, *y1 = 시작 좌표
         *width, *height = 넓이/높이
  ret  : none
**************************************************************/
void CDDB::GetAbsoluteCoordinate( int *x1, int *y1, int *width, int *height)
{
	*width  = *x1 + *width;						// Get end x
	*height = *y1 + *height;					// Get end y
}
