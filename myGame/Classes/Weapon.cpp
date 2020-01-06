#include "Weapon.h"

cocos2d::Sprite* Weapon::createWeapon()
{
	return Weapon::create();
}

Weapon::Weapon()
{
	
}

Weapon::~Weapon()
{
}

int Weapon::GetHP()
{
	return _hp;
}

void Weapon::SetHP(int hp)
{
	_hp = hp;
}

bool Weapon::init()
{
	_remainCnt = 0;
	// ½Ìß×²Ä¸×½‚Ì‰Šú‰»@init‚ðŽ©ì‚µ‚½‚½‚ß•K—v
	if (!Sprite::init())
	{
		return false;
	}

	cocos2d::Rect rect = cocos2d::Rect(0, 0, 32, 32);

	this->setTextureRect(rect);
	this->setColor(cocos2d::Color3B(0, 255, 0));
	_hp = 1;
	//this->setPosition(100, 100);
	this->scheduleUpdate();

	return true;
}



void Weapon::update(float delta)
{
	_remainCnt++;
	if (_remainCnt > 1)
	{
		this->removeFromParent();
	}
}

