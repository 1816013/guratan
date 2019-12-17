#include "ChangeLR.h"
#include <Unit/Player.h>

bool ChangeLR::operator()(cocos2d::Sprite & sp, actModule & module)
{
	bool flagLR;
	if (module.inputID == INPUT_ID::RIGHT)
	{
		flagLR = false;
	}
	else
	{
		flagLR = true;
	}
	sp.runAction(cocos2d::FlipX::create(flagLR));

	return true;
}
