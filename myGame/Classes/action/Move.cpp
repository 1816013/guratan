#include "Move.h"
#include <Unit/Player.h>
//#include "EffectMng.h"
//#include "_debug/_DebugConOut.h"

bool Move::operator()(cocos2d::Sprite& sp, actModule& module)
{
	sp.setPosition(sp.getPosition() + module.speed);

	auto checkinput = [](INPUT_ID input, cocos2d::Sprite& sp)
	{
		for (auto inputID : INPUT_ID())
		{
			if (((Player&)sp)._inputState->GetInput(TRG_STATE::NOW, inputID) == true)
			{
				if (input != inputID)
				{
					return false;
				}
			}
		}
		return true;
	};
	DIR dir = DIR::MAX;
	if (checkinput(module.inputID, sp))
	{
		dir = module.dir;
		((Obj&)sp).SetDIR(dir);
	}
	
	if (dir == DIR::UP)
	{
		sp.setRotation(0.0f);
	}
	if (dir == DIR::RIGHT)
	{
		sp.setRotation(90.0f);
	}
	if (dir == DIR::DOWN)
	{
		sp.setRotation(180.0f);
	}
	if (dir == DIR::LEFT)
	{
		sp.setRotation(270.0f);
	}
	
	
	//TRACE("moveLR\n");
	return true;
}
