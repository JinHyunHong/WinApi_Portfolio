#pragma once
// 열거체를 정의합니다.

enum DIR
{
	DIR_BACK = -1,
	DIR_NONE,
	DIR_FRONT
};

enum CHARACTER_DIR
{
	CD_LEFT,
	CD_RIGHT
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

enum COLLIDER_STATE
{
	CS_ENTER,
	CS_STAY,
	CS_LEAVE,
	CS_END
};

enum ANIMATION_TYPE
{
	AT_ATLAS,
	AT_FRAME
};

enum ANIMATION_OPTION
{
	AO_LOOP,
	AO_ONCE_RETURN,
	AO_ONCE_DESTROY,
	AO_TIME_RETURN,
	AO_TIME_DESTROY
};

enum BUTTON_STATE
{
	BS_NONE,
	BS_ON,
	BS_CLICK,
	BS_OUT
};

enum WORLD_CHARACTER_TYPE
{
	WCT_BENIMARU,
	WCT_KYO,
	WCT_END
};