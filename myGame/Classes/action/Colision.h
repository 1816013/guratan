#pragma once
#include <cocos2d.h>
#include "action/ActionMng.h"

struct actModule;

struct actColision
{
	// �����蔻��
	bool operator()(cocos2d::Sprite & sp, actModule& module) const;	
};

struct Colision
{
	// �����蔻��
	bool operator()(cocos2d::Sprite & sp,cocos2d::Vec2 speed, std::array<cocos2d::Size, 2> colSize) const;
};