#pragma once
// 열거체를 정의합니다.

enum DIR
{
	DIR_BACK = -1,
	DIR_NONE,
	DIR_FRONT
};

enum SCENE_TRANSITION
{
	ST_CURRENT,
	ST_NEXT,
	ST_END
};

enum COLLIDER_TYPE
{
	CT_NONE,
	CT_POINT,
	CT_SPHERE,
	CT_RECT,
	CT_PIXEL
};