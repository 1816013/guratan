#pragma once
#include "OPRT_state.h"
struct OPRT_touch : public OPRT_state
{
	OPRT_touch(cocos2d::Node* sp);
	OPRT_TYPE GetType(void)override;	// ¡g‚Á‚Ä‚¢‚é“ü—ÍÀ²Ìß‚ğæ“¾(‚±‚ê‚Ítouch)
private:
	cocos2d::Point _startTPos;
};

