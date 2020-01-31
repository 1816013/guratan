#include "mapObject.h"
#include <AnimMng.h>

USING_NS_CC;

cocos2d::Sprite * mapObject::createMapObj()
{
	return mapObject::create();
}

mapObject::mapObject()
{
}

mapObject::~mapObject()
{
}

bool mapObject::init()
{
	// ½Ìß×²Ä¸×½‚Ì‰Šú‰»@init‚ðŽ©ì‚µ‚½‚½‚ß•K—v
	if (!Sprite::init())
	{
		return false;
	}
	lpAnimMng.AnimCreate("potal", "warp", 5, 0.1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->setScale(2.0f);
	this->setPosition(visibleSize / 2);

	/*cocos2d::Rect rect = cocos2d::Rect(0, 0, 32, 32);
	this->setTextureRect(rect);
	this->setColor(cocos2d::Color3B(255, 212, 0));*/
	_hp = 1;
	this->scheduleUpdate();
	return true;
}

void mapObject::update(float delta)
{
	auto animCache = AnimationCache::getInstance();
	auto anim = animCache->getAnimation("potal-warp");
	lpAnimMng.runAnim(*this, *anim, *_oldanim, 0);
	_oldanim = anim;
}
