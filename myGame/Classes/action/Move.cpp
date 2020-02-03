#include "Move.h"
#include <obj/Player.h>

bool Move::operator()(cocos2d::Sprite& sp, actModule& module)
{
	((Player&)sp).SetPlayerAct(PlayerAct::MOVE);
	cocos2d::Vec2 speed = module.speed;
	if (((Player&)sp).IsCharged())
	{
		speed = speed / 3.0f;
	}
	sp.setPosition(sp.getPosition() + speed * ((Player&)sp).GetMovePower());
	return true;
}

