#pragma once
#include <cocos2d.h>
#include "ActionMng.h"
#include "input/OPRT_state.h"
#include "input/OPRT_key.h"

struct actModule;

struct CheckKey
{
	// ·°“ü—ÍŠm”F
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};