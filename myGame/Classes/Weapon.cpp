#include "Weapon.h"


USING_NS_CC;

cocos2d::Sprite* Weapon::createWeapon(Sprite& sp, const OptionType option, int chargeLevel)
{
	auto weapon = Weapon::create();
	weapon->_optionType = option;
	weapon->SetDIR(((Player&)sp).GetDIR());
	weapon->_power = (((Player&)sp).GetPower());
	weapon->_chargeType = (((Player&)sp).GetChargeType());
	cocos2d::Vec2 dirOffset = cocos2d::Vec2(0, 0);
	auto offsetCreate = [&](Sprite& sp)
	{
		switch (((Obj&)sp).GetDIR())
		{
		case DIR::UP:
			dirOffset.y = weapon->getContentSize().height / 2 + 16;
			break;
		case DIR::RIGHT:
			dirOffset.x = weapon->getContentSize().height / 2 + 16;
			break;
		case DIR::DOWN:
			dirOffset.y = -weapon->getContentSize().height / 2 - 16;
			break;
		case DIR::LEFT:
			dirOffset.x = -weapon->getContentSize().height / 2 - 16;
			break;
		default:
			break;
		}
	};
	if (option == OptionType::NOMAL)
	{
		weapon->setContentSize({ 32, 32 });
		offsetCreate(sp);
	}
	else
	{
		switch (weapon->_chargeType)
		{
		case ChargeType::SHOT:
			weapon->setContentSize({ 16.0f * chargeLevel, 16.0f * chargeLevel });
			weapon->_hp = 1;
			break;
		case ChargeType::TWISTER:
			weapon->setContentSize({ 96.0f + 16.0f * (chargeLevel - 1), 96.0f + 16.0f * (chargeLevel - 1) });
			break;
		case ChargeType::FLONTAL:
			weapon->setContentSize({ 96.0f, 64.0f });
			weapon->_power *= 1.5 + 0.5 * (chargeLevel - 1);
			offsetCreate(sp);
			break;
		default:
			break;
		}
	}
	
	weapon->SetColSize(sp);
	weapon->setPosition(sp.getPosition() + dirOffset);

	
	weapon->setTag(static_cast<int>(objTag::ATTACK));
	return weapon;
}

Weapon::Weapon()
{
	
}

Weapon::~Weapon()
{
}

bool Weapon::init()
{
	_remainCnt = 0;
	// ｽﾌﾟﾗｲﾄｸﾗｽの初期化@initを自作したため必要
	if (!Sprite::init())
	{
		return false;
	}
	//_chargeType = ChargeType::FLONTAL;

	cocos2d::Rect rect = cocos2d::Rect(0, 0, 32, 32);
	this->setTextureRect(rect);
	this->setColor(cocos2d::Color3B(0, 255, 0));
	_hp = 1000000;
	_power = 1;

	//this->setPosition(100, 100);
	this->scheduleUpdate();

	return true;
}

void Weapon::update(float delta)
{
	_remainCnt++;
	if (_optionType == OptionType::NOMAL)
	{
		if (_remainCnt > 1)
		{
			this->removeFromParent();
		}
	}
	else if (_optionType == OptionType::CHARGE)
	{
		switch (_chargeType)
		{
		case ChargeType::SHOT:
			if (_gameMap->mapColision(*this, _speedTbl[static_cast<int>(this->GetDIR())] * 7, _colSize[static_cast<int>(this->GetDIR())]))
			{
				this->setPosition(this->getPosition() + (_speedTbl[static_cast<int>(this->GetDIR())]) * 7);
			}
			else
			{
				this->removeFromParent();
			}
			break;
		case ChargeType::TWISTER:
			if (_remainCnt > 1)
			{
				this->removeFromParent();
			}
			break;
		case ChargeType::FLONTAL:
			if (_dir == DIR::UP)
			{
				this->setRotation(0.0f);
			}
			if (_dir == DIR::RIGHT)
			{
				this->setRotation(90.0f);
			}
			if (_dir == DIR::DOWN)
			{
				this->setRotation(180.0f);
			}
			if (_dir == DIR::LEFT)
			{
				this->setRotation(270.0f);
			}
			if (_remainCnt > 1)
			{
				this->removeFromParent();
			}
			break;
		default:
			break;
		}
	}
	

}

bool Weapon::ColisionObj(Obj& hitObj, cocos2d::Scene& scene)
{
	bool col = false;

	Rect myRect = this->getBoundingBox();
	Rect hitRect = hitObj.getBoundingBox();
	int hitTag = hitObj.getTag();

  	if (myRect.intersectsRect(hitRect))
	{
		int hitTag = hitObj.getTag();
		//if (hitTag == static_cast<int>(objTag::ENEMY))
		//{
		//	col = true;
		//	_hp -= 1;
		//	hitObj.SetHP(hitObj.GetHP() - _power);
		//	if (_gameMap->mapColision(hitObj, _speedTbl[static_cast<int>(_dir)] * 32, this->_colSize[static_cast<int>(_dir)]))
		//	{
		//		hitObj.setPosition(hitObj.getPosition() + (_speedTbl[static_cast<int>(_dir)]) * 32);		// ノックバック処理
		//	}
		//}
	}
	return col;
}

void Weapon::SetColSize(Sprite & sp)
{
	auto size = sp.getContentSize() / 2;
	_colSize[static_cast<int>(DIR::UP)] = { Size(-size.width, size.height), Size(size.width, size.height) };
	_colSize[static_cast<int>(DIR::RIGHT)] = { Size(size.width, size.height), Size(size.width, -size.height) };
	_colSize[static_cast<int>(DIR::DOWN)] = { Size(size.width, -size.height), Size(-size.width, -size.height) };
	_colSize[static_cast<int>(DIR::LEFT)] = { Size(-size.width, size.height), Size(-size.width, -size.height) };
}

void Weapon::SetState()
{
}


