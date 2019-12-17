#pragma once
#include "OPRT_state.h"
struct OPRT_key : public OPRT_state
{
	OPRT_key(cocos2d::Node* sp);
	OPRT_TYPE GetType(void)override;	// ¡g‚Á‚Ä‚¢‚é“ü—ÍÀ²Ìß‚ğæ“¾(‚±‚ê‚Íkey)
};

