#pragma once
// 구조체를 정의합니다.

typedef struct _tagScreenSize
{
	unsigned int iWidth;
	unsigned int iHeight;

	_tagScreenSize() :
		iWidth(0),
		iHeight(0)
	{
	}

	_tagScreenSize(unsigned int _iWidth, unsigned _iHeight) :
		iWidth(_iWidth),
		iHeight(_iHeight)
	{
	}


}SCREENSIZE, * PSCREENSIZE;

typedef struct _tagPosition
{
	float x;
	float y;

	_tagPosition()	:
		x(0.f),
		y(0.f)
	{
	}

	_tagPosition(float x, float y) :
		x(x),
		y(y)
	{
	}

	void operator =(_tagPosition tPos)
	{
		x = tPos.x;
		y = tPos.y;
	}

	void operator =(POINT tPos)
	{
		x = (float)tPos.x;
		y = (float)tPos.y;
	}

	void operator +=(_tagPosition tPos)
	{
		x += tPos.x;
		y += tPos.y;
	}

	void operator +=(POINT tPos)
	{
		x += tPos.x;
		y += tPos.y;
	}

	void operator -=(_tagPosition tPos)
	{
		x -= tPos.x;
		y -= tPos.y;
	}

	void operator -=(POINT tPos)
	{
		x -= tPos.x;
		y -= tPos.y;
	}
	_tagPosition operator +(_tagPosition _tPos)
	{
		_tagPosition tPos;
		tPos.x = x + _tPos.x;
		tPos.y = y + _tPos.y;
		return tPos;
	}

	_tagPosition operator +(POINT _tPos)
	{
		_tagPosition tPos;
		tPos.x = x + _tPos.x;
		tPos.y = y + _tPos.y;
		return tPos;
	}

	_tagPosition operator -(_tagPosition _tPos)
	{
		_tagPosition tPos;
		tPos.x = x - _tPos.x;
		tPos.y = y - _tPos.y;
		return tPos;
	}

	_tagPosition operator -(POINT _tPos)
	{
		_tagPosition tPos;
		tPos.x = x - _tPos.x;
		tPos.y = y - _tPos.y;
		return tPos;
	}

	_tagPosition operator *(_tagPosition _tPos)
	{
		_tagPosition tPos;
		tPos.x = x * _tPos.x;
		tPos.y = y * _tPos.y;
		return tPos;
	}

	_tagPosition operator *(POINT _tPos)
	{
		_tagPosition tPos;
		tPos.x = x * _tPos.x;
		tPos.y = y * _tPos.y;
		return tPos;
	}

}_SIZE, *_PSIZE, POSITION, * PPOSITION;


typedef struct _tagRectangle
{
	float l;
	float t;
	float r;
	float b;

	_tagRectangle() :
		l(0.f),
		t(0.f),
		r(0.f),
		b(0.f)
	{
	}
}RECTANGLE, *PRECTANGLE;

typedef struct _tagSphere
{
	POSITION tCenter;
	float fRadius;

	_tagSphere() :
		fRadius(0.f)
	{
	}
}SPHERE, *PSPHERE;

typedef struct _tagPixel
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	_tagPixel() :
		r(0),
		g(0),
		b(0)
	{
	}
}PIXEL, *PPIXEL;



