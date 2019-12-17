#include "Enemy.h"

USING_NS_CC;

cocos2d::Sprite * Enemy::createSprite()
{
	return Enemy::create();
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

bool Enemy::init()
{
	// ½Ìß×²Ä¸×½‚Ì‰Šú‰»@init‚ðŽ©ì‚µ‚½‚½‚ß•K—v
	if (!Sprite::init())
	{
		return false;
	}
	//auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	Rect rect = Rect(0, 0, 32, 32);
	this->setTextureRect(rect);
	this->setColor(cocos2d::Color3B(255, 0, 0));
	_speedTbl = { Vec2(0, 5),Vec2(5, 0), Vec2(0, -5), Vec2(-5, 0) };

	this->scheduleUpdate();
	return true;
}

void Enemy::update(float delta)
{
	//Director::getInstance()->getRunningScene()->getChildByName()
	int dir = rand() % static_cast<int>(DIR::MAX);
	this->setPosition(this->getPosition() + _speedTbl[dir]);
	
}

DIR Enemy::GetDIR()
{
	return _dir;
}

