#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct CheckList
{
	// ��ׯ�ؽĂ��ܲ�ؽĂ̊m�F
	bool operator()(cocos2d::Sprite& sprite, actModule& module);
};

