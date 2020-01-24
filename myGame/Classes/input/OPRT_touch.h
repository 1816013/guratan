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
	OPRT_TYPE GetType(void)override;	// 今使っている入力ﾀｲﾌﾟを取得(これはtouch)
private:
	int numberOfTouch;
	cocos2d::Point _startTPos;
	std::vector<cocos2d::Vec2> touchVectors;
};

