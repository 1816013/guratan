#pragma once
#include "OPRT_state.h"
struct OPRT_key : public OPRT_state
{
	OPRT_key(cocos2d::Node* sp);
	OPRT_TYPE GetType(void)override;	// ���g���Ă���������߂��擾(�����key)
};

