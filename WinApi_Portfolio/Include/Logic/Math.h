#pragma once

#include "../Game.h"

class CMath
{
public:
	float Distance(const POSITION& tPos1, const POSITION& tPos2);
	bool RectToRect(const RECTANGLE& src, const RECTANGLE& dest);
	bool RectToPoint(const RECTANGLE& src, const POSITION& dest);
	bool RectToSphere(const RECTANGLE& src, const SPHERE& dest);
	bool SphereToSphere(const SPHERE& src, const SPHERE& dest);
	bool SphereToPoint(const SPHERE& src, const POSITION& dest);
	bool RectToPixel(const RECTANGLE& src, const vector<PIXEL>& dest, int iWidth, int iHeight);
	bool PointToPixel(const POSITION& src, const vector<PIXEL>& dest, int iWidth, int iHeight);
};

