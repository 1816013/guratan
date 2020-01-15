#include "Weapon.h"
#include "Unit/Player.h"

USING_NS_CC;

cocos2d::Sprite* Weapon::createWeapon(Sprite& sp, OptionType option)
{
	auto weapon = Weapon::create();
	weapon->SetDIR(((Player&)sp).GetDIR());
	weapon->_power = (((Player&)sp).GetPower());
	weapon->_optionType = option;
	return weapon;
}

Weapon::Weapon()
{
	
}

Weapon::~Weapon()
{
}

DIR Weapon::GetDIR()
{
	return _dir;
}

void Weapon::SetDIR(DIR dir)
{
	_dir = dir;
}

int Weapon::GetPower()
{
	return _power;
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
	_power = 1;

	auto size = this->getContentSize() / 2;
	_colSize[static_cast<int>(DIR::UP)] = { Size(-size.width, size.height), Size(size.width, size.height) };
	_colSize[static_cast<int>(DIR::RIGHT)] = { Size(size.width, size.height), Size(size.width, -size.height) };
	_colSize[static_cast<int>(DIR::DOWN)] = { Size(size.width, -size.height), Size(-size.width, -size.height) };
	_colSize[static_cast<int>(DIR::LEFT)] = { Size(-size.width, size.height), Size(-size.width, -size.height) };
	//this->setPosition(100, 100);
	this->scheduleUpdate();

	return true;
}



void Weapon::update(float delta)
{
	_remainCnt++;
	switch (_optionType)
	{
	case OptionType::NOMAL:
		if (_remainCnt > 1)
		{
			this->removeFromParent();
		}
		break;
	case OptionType::RANGE:
		if (_gameMap->mapColision(*this, _speedTbl[static_cast<int>(this->GetDIR())] * 7, _colSize[static_cast<int>(this->GetDIR())]))
		{
			this->setPosition(this->getPosition() + (_speedTbl[static_cast<int>(this->GetDIR())]) * 7);
		}
		else
		{
			this->removeFromParent();
		}
		break;
	default:
		break;
	}
	
}

