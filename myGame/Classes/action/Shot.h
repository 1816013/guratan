#pragma once
#include "ActionMng.h"

struct Shot
{
	// shot 
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};
