#include "Move.h"
#include <obj/Player.h>
#include <obj/Enemy.h>
//#include "EffectMng.h"
//#include "_debug/_DebugConOut.h"

bool Move::operator()(cocos2d::Sprite& sp, actModule& module)
{
	cocos2d::Vec2 speed = module.speed;
	if (((Player&)sp).IsCharged())
	{
		speed = speed / 3.0f;
	}
	sp.setPosition(sp.getPosition() + speed * ((Player&)sp).GetMovePower());
	
	//TRACE("moveLR\n");
	return true;
}

