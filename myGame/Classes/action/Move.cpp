#include "Move.h"
#include <Unit/Player.h>
#include <Unit/Enemy.h>
//#include "EffectMng.h"
//#include "_debug/_DebugConOut.h"

bool Move::operator()(cocos2d::Sprite& sp, actModule& module)
{
	auto speed = module.speed;
	if (((Player&)sp).IsCharged())
	{
		speed = speed / 3.0f;
	}
	sp.setPosition(sp.getPosition() + speed * ((Player&)sp).GetMovePower());

	/*if (sp.getTag() == static_cast<int>(objTag::PLAYER))
	{
		
		
	}
	else
	{
		((Enemy&)sp).SetDIR( module.dir);
	}*/
	
	
	//TRACE("moveLR\n");
	return true;
}

