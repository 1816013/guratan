#pragma once
#include "OPRT_state.h"
struct OPRT_touch : public OPRT_state
{
	OPRT_touch(cocos2d::Node* sp);
	OPRT_TYPE GetType(void)override;	// ���g���Ă���������߂��擾(�����touch)
private:
	cocos2d::Point _startTPos;
};

