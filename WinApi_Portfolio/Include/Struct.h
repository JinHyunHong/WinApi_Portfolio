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

	_tagPosition operator +(float fPos[2])
	{
		_tagPosition tPos;
		tPos.x = x + fPos[0];
		tPos.y = y + fPos[1];
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

	_tagPosition operator -(float fPos[2])
	{
		_tagPosition tPos;
		tPos.x = x - fPos[0];
		tPos.y = y - fPos[1];
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


	_tagPixel(unsigned int _r,
		unsigned int _g, unsigned int _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}

	_tagPixel() :
		r(0),
		g(0),
		b(0)
	{
	}
}PIXEL, *PPIXEL;

typedef struct _tagAnimationClip
{
	ANIMATION_TYPE			eType;
	ANIMATION_OPTION		eOption;
	vector<class CTexture*> vecTexture;
	float					fAnimationTime;
	float					fAnimationLimitTime;
	float					fAnimationFrameTime;
	int						iFrameX;
	int						iFrameY;
	int						iFrameMaxX;
	int						iFrameMaxY;
	int						iStartX;
	int						iStartY;
	int						iLengthX;
	int						iLengthY;
	float					fOptionTime;
	float					fOptionLimitTime;
	_SIZE					tFrameSize;

}ANIMATIONCLIP, * PANIMATIONCLIP;

typedef struct _tagUiTextInfo
{
	string			strText;
	POSITION		tPos;
	string			strFontName;
	unsigned int	r;
	unsigned int    g;
	unsigned int    b;
	int				iMode;
	unsigned int    iFormat;

	_tagUiTextInfo()	:
		strText(""),
		strFontName(""),
		r(0),
		g(0),
		b(0),
		iMode(TRANSPARENT),
		iFormat(DT_CENTER)
	{
	}
}UITEXTINFO, * PUITEXTINFO;