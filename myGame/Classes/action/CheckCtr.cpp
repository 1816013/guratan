#include "CheckCtr.h"
#include "Unit/Player.h"
#include "Unit/Enemy.h"

USING_NS_CC;

bool CheckKey::operator()(cocos2d::Sprite & sp, actModule & module)
{
	if (sp.getTag() == static_cast<int>(objTag::PLAYER))
	{
		if (module.inputID == INPUT_ID::NONE)
		{
			if (((Player&)sp)._inputState->GetInput(TRG_STATE::NOW, module.inputID))
			{
				return true;
			}
		}
		if (((Player&)sp)._inputState->GetInput(TRG_STATE::NOW, module.inputID))
		{
			if (module.keyTiming == Timing::ON)
			{
				return true;
			}
			if (module.keyTiming == Timing::ON_MOM)
			{
				if (((Player&)sp)._inputState->GetInput(TRG_STATE::NOW, module.inputID) && !((Player&)sp)._inputState->GetInput(TRG_STATE::OLD, module.inputID))
				{
					return true;
				}
			}
		}
		else
		{
			if (module.keyTiming == Timing::OFF)
			{
				return true;
			}
			if (module.keyTiming == Timing::OFF_MOM)
			{
				if (!((Player&)sp)._inputState->GetInput(TRG_STATE::NOW, module.inputID) && !((Player&)sp)._inputState->GetInput(TRG_STATE::OLD, module.inputID))
				{
					return true;
				}
			}
		}
	}
	else
	{
		CheckAI Ai;
		return Ai(sp, module);
	}
	
	return false;
}

bool CheckAI::operator()(cocos2d::Sprite & sp, actModule & module)
{
	auto followLayer = Director::getInstance()->getRunningScene()->getChildByName("followLayer");
	if (followLayer != nullptr)
	{
		auto charLayer = (Player*)followLayer->getChildByName("charLayer");
		auto player = charLayer->getChildByTag(static_cast<int>(objTag::PLAYER));
		if (((Enemy&)sp).GetEnemyAI() == EnemyAI::FORROW)
		{
			if (player != nullptr)
			{
				if (sp.getPositionX() < player->getPositionX())
				{
					if (module.inputID == INPUT_ID::RIGHT)
					{
						return true;
					}
				}
				else
				{
					if (module.inputID == INPUT_ID::LEFT)
					{
						return true;
					}
				}
				if (sp.getPositionY() < player->getPositionY())
				{
					if (module.inputID == INPUT_ID::UP)
					{
						return true;
					}
				}
				else
				{
					if (module.inputID == INPUT_ID::DOWN)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
