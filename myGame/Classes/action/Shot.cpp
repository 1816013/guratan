#include "Shot.h"
//#include "SoundMng.h"
//#include "EffectMng.h"

bool Shot::operator()(cocos2d::Sprite & sp, actModule & module)
{
	/*if (!sp.isFlippedX())
	{
		lpEffectMng.EmitterPlay("Laser01.efk", sp.getPosition(), cocos2d::Vec3(0, 90, 0));
	}
	else
	{
		lpEffectMng.EmitterPlay("Laser01.efk", sp.getPosition(), cocos2d::Vec3(0, 270, 0));
	}
	lpSoundMng.PlayBySoundName("shot");*/
	return true; 
}
