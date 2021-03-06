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

enum EFFECT_TYPE
{
	ET_HURT_SMALL,
	ET_HURT_MEDIUM,
	ET_HURT_BIG,
	ET_EFFECT_END,
	ET_BENIMARU_SPECIAL1,
	ET_BENIMARU_SPECIAL1_1,
	ET_END
};

enum PLAYER_TYPE
{
	PT_BLUE,
	PT_RED,
	PT_END
};

enum GAME_SOUND_TYPE
{
	GST_EFFECT,
	GST_BGM,
	GST_PLAYERBGM,
	GST_ENEMYBGM,
	GST_END
};

enum RESOURCES_TYPE
{
	RT_BENIMARU,
	RT_KYO,
	RT_EFFECT,
	RT_END
};

enum CHARACTER_NAME_TYPE
{
	CNT_NONE,
	CNT_BENIMARU,
	CNT_KYO,
	CNT_END
};