#pragma once
#include <cocos2d.h>
#include "action/ActionMng.h"

struct actModule;

struct Colision
{
	// �����蔻��
	bool operator()(cocos2d::Sprite & sp, actModule& module) const;	
};