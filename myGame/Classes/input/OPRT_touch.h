#pragma once
#include "OPRT_state.h"
struct touch
{
	cocos2d::Vec2 pos;
	bool isMoveTouch;
	bool isAttackTouch;
};
struct OPRT_touch : public OPRT_state
{
	OPRT_touch(cocos2d::Node* sp);
	OPRT_TYPE GetType(void)override;	// 今使っている入力ﾀｲﾌﾟを取得(これはtouch)
private:
	std::vector<touch> touchVectors;
};

