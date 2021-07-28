#include "Math.h"

float CMath::Distance(POSITION tPos1, POSITION tPos2)
{
	float fBase = tPos2.x - tPos1.x;
	float fHeight = tPos2.y - tPos1.y;

	return sqrtf(fBase * fBase + fHeight * fHeight);
}
