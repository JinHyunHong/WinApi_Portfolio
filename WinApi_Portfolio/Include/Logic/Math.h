#pragma once

#include "../Game.h"

class CMath
{
public:
	static float Distance(const POSITION& tPos1, const POSITION& tPos2);
	static bool RectToRect(const RECTANGLE& src, const RECTANGLE& dest);
	static bool RectToPoint(const RECTANGLE& src, const POSITION& dest);
	static bool RectToSphere(const RECTANGLE& src, const SPHERE& dest);
	static bool SphereToSphere(const SPHERE& src, const SPHERE& dest);
	static bool SphereToPoint(const SPHERE& src, const POSITION& dest);
	static bool RectToPixel(const RECTANGLE& src, const vector<PIXEL>& dest, int iWidth, int iHeight);
	static bool PointToPixel(const POSITION& src, const vector<PIXEL>& dest, int iWidth, int iHeight);
};

