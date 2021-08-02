#include "Math.h"

float CMath::Distance(const POSITION& tPos1, const POSITION& tPos2)
{
	float fBase = tPos2.x - tPos1.x;
	float fHeight = tPos2.y - tPos1.y;

	return sqrtf(fBase * fBase + fHeight * fHeight);
}

bool CMath::RectToRect(const RECTANGLE& src, const RECTANGLE& dest)
{
	if (src.l > dest.r)
		return false;

	else if (src.r < dest.l)
		return false;

	else if (src.t > dest.b)
		return false;

	else if (src.b < dest.t)
		return false;

	return true;
}

bool CMath::RectToPoint(const RECTANGLE& src, const POSITION& dest)
{
	if (src.l > dest.x)
		return false;

	else if (src.r < dest.x)
		return false;

	else if (src.t > dest.y)
		return false;

	else if (src.b < dest.y)
		return false;

	return true;
}

bool CMath::RectToSphere(const RECTANGLE& src, const SPHERE& dest)
{
	if ((src.l <= dest.tCenter.x && dest.tCenter.x <= src.r) ||
		(src.t <= dest.tCenter.y && dest.tCenter.y <= src.b))
	{
		RECTANGLE tRC = src;

		tRC.l -= dest.fRadius;
		tRC.t -= dest.fRadius;
		tRC.r += dest.fRadius;
		tRC.b += dest.fRadius;

		if (dest.tCenter.x < tRC.l)
			return false;

		else if (dest.tCenter.x > tRC.r)
			return false;

		else if (dest.tCenter.y < tRC.t)
			return false;

		else if (dest.tCenter.y > tRC.b)
			return false;

		return true;
	}

	POSITION tPos[4];
	tPos[0] = POSITION(src.l, src.t);
	tPos[1] = POSITION(src.r, src.t);
	tPos[2] = POSITION(src.l, src.b);
	tPos[3] = POSITION(src.r, src.b);

	for (int i = 0; i < 4; ++i)
	{
		float fDist = Distance(tPos[i], dest.tCenter);

		if (fDist <= dest.fRadius)
			return true;
	}

	return false;
}

bool CMath::SphereToSphere(const SPHERE& src, const SPHERE& dest)
{
	return Distance(src.tCenter, dest.tCenter) <= src.fRadius + dest.fRadius;
}

bool CMath::SphereToPoint(const SPHERE& src, const POSITION& dest)
{
	return Distance(src.tCenter, dest) <= src.fRadius;
}

bool CMath::RectToPixel(const RECTANGLE& src, const vector<PIXEL>& dest, int iWidth, int iHeight)
{
	int iStartX, iEndX;
	int iStartY, iEndY;

	iStartX = src.l < 0 ? 0 : src.l;
	iStartY = src.r >= iWidth ? iWidth - 1 : src.r;
	iEndX = src.t < 0 ? 0 : src.t;
	iEndY = src.b >= iHeight ? iHeight - 1 : src.b;

	for (int i = iStartY; i <= iEndY; ++i)
	{
		for (int j = iStartX; j <= iEndX; ++j)
		{
			int idx = i * iWidth + j;
			const PIXEL& pixel = dest[idx];

			if (pixel.r == 40 && pixel.g == 60 && pixel.b == 1)
			{
				return true;
			}
		}
	}
	return false;
}

bool CMath::PointToPixel(const POSITION& src, const vector<PIXEL>& dest, int iWidth, int iHeight)
{
	if (src.y < 0 || src.x < 0 || src.x >= iWidth || src.y >= iHeight)
		return false;

	int idx = (int)src.y * iWidth + (int)src.x;
	const PIXEL& pixel = dest[idx];

	if (pixel.r == 40 && pixel.g == 60 && pixel.b == 1)
	{
		return true;
	}
	return false;
}
