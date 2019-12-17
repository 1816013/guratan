#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct CheckList
{
	// ÌÞ×¯¸Ø½Ä‚ÆÎÜ²ÄØ½Ä‚ÌŠm”F
	bool operator()(cocos2d::Sprite& sprite, actModule& module);
};

