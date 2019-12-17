#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct Shot
{
	// shot 
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};
