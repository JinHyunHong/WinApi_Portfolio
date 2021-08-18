#pragma once
// ¸ÅÅ©·Î 

#define SAFE_DELETE(p)	if(p)	{delete p; p = NULL;}
#define SAFE_DELETE_ARRAY(p)	if(p)	{delete[] p; p = NULL;}
#define SAFE_RELEASE(p)			if(p)	{p->ReleaseRef(); p = NULL;}


#define DECLARE_SINGLE(Type)\
private:\
	Type(); \
	~Type(); \
private:\
	static Type* m_pInst; \
public:\
	static Type* GetInst()\
	{\
		if (!m_pInst)\
			m_pInst = new Type;\
		return m_pInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_pInst);\
	}

#define GET_SINGLE(Type) Type::GetInst()
#define DEFINITION_SINGLE(Type)	Type* Type::m_pInst = NULL;
#define DESTROY_SINGLE(Type) Type::DestroyInst()

#define GET_WINDOW_HANDLE  CLogic::GetInst()->GetWindowHandle()

#define BASE_PATH "BasePath"
#define TEXTURE_PATH "TexturePath"
#define SOUND_PATH "SoundPath"
#define EFFECT_PATH "EffectPath"
#define CHARACTER_PATH "CharacterPath"
#define UI_PATH "UIPath"
#define FONT_PATH "FontPath"
#define BENIMARU_PATH "BenimaruPath"
#define KYO_PATH "KyoPath"

#define DECLARE_REFERENCE_COUNT()\
private:\
		int		m_iRef;\
public:\
		void AddRef()\
		{\
			++m_iRef;\
		}\
		void ReleaseRef()\
		{\
			--m_iRef;\
			if(m_iRef == 0)\
			{\
				delete this;\
				return;\
			}\
		}

#define DEFINITION_REFERENCE_COUNT() m_iRef = 1;


#define GRAVITY 9.8f


#define KEYDOWN(key)	GET_SINGLE(CInputManager)->GetKeyDown(key)
#define KEYPRESS(key)	GET_SINGLE(CInputManager)->GetKeyPress(key)
#define KEYUP(key)		GET_SINGLE(CInputManager)->GetKeyUp(key)

#define WINDOWHANDLE	GET_SINGLE(CLogic)->GetWindowHandle()
#define WINDOWHEIGHT	GET_SINGLE(CLogic)->GetClientRS().iHeight
#define WINDOWWIDTH		GET_SINGLE(CLogic)->GetClientRS().iWidth
#define WORLDHEIGHT		GET_SINGLE(CLogic)->GetWorldRS().iHeight
#define WORLDWIDTH		GET_SINGLE(CLogic)->GetWorldRS().iWidth
#define GAMEEND			GET_SINGLE(CLogic)->GameEnd()

#define TIMER_MAX_PANEL 2