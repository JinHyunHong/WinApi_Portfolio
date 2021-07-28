#pragma once
// 구조체를 정의합니다.

typedef struct _tagScreenSize
{
	unsigned int iWidth;
	unsigned int iHeight;
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
		x = tPos.x;
		y = tPos.y;
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

}POSITION, * PPOSITION;



