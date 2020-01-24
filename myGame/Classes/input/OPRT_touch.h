#pragma once
#include "OPRT_state.h"
struct touch
{
	cocos2d::Vec2 _pos;
	bool isMoveTouch;
	bool isAttackTouch;
	touch() { isMoveTouch = false; isAttackTouch = false; _pos = cocos2d::Vec2::ZERO; }
};
struct OPRT_touch : public OPRT_state
{
	OPRT_touch(cocos2d::Node* sp);
	OPRT_TYPE GetType(void)override;	// ¡g‚Á‚Ä‚¢‚é“ü—ÍÀ²Ìß‚ğæ“¾(‚±‚ê‚Ítouch)
private:
	int numberOfTouch;
	cocos2d::Point _startTPos;
	std::vector<cocos2d::Vec2> touchVectors;
};

