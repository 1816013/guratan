#pragma once
#include "action/ActionMng.h"
struct Attack
{
	bool operator()(cocos2d::Sprite& sp, actModule& module);
};

