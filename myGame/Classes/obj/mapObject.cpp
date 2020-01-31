#include "mapObject.h"

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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->setPosition(visibleSize / 2);
	cocos2d::Rect rect = cocos2d::Rect(0, 0, 32, 32);
	this->setTextureRect(rect);
	this->setColor(cocos2d::Color3B(255, 212, 0));
	_hp = 1;
	return true;
}

void mapObject::update(float delta)
{
}
