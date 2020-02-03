#include "Weapon.h"
#include "AnimMng.h"

USING_NS_CC;

cocos2d::Sprite* Weapon::createWeapon(Sprite& sp, const OptionType option, int chargeLevel)
{
	auto weapon = Weapon::create();
	int CameraMask = static_cast<int>(CameraFlag::DEFAULT) | static_cast<int>(CameraFlag::USER1);
	weapon->setCameraMask(static_cast<int>(CameraFlag::USER1));
	weapon->_optionType = option;
	weapon->SetDIR(((Player&)sp).GetDIR());
	weapon->_power = (((Player&)sp).GetPower() * ((Player&)sp).GetPowerRate());
	weapon->_chargeType = (((Player&)sp).GetChargeType());
	weapon->setTexture("image/weapon/attackNomal.png");
	weapon->SetWeaponType(sp, chargeLevel);
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
	// ½Ìß×²Ä¸×½‚Ì‰Šú‰»@init‚ðŽ©ì‚µ‚½‚½‚ß•K—v
	if (!Sprite::init())
	{
		return false;
	}
	//_chargeType = ChargeType::FLONTAL;

	cocos2d::Rect rect = cocos2d::Rect(0, 0, 32, 32);
	//this->setTextureRect(rect);
	this->setColor(cocos2d::Color3B(0, 255, 0));
	_hp = 1000000;
	_power = 1;

	//this->setPosition(100, 100);
	this->scheduleUpdate();

	return true;
}

void Weapon::update(float delta)
{

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
	if (_optionType == OptionType::NOMAL)
	{
		if (_remainCnt > 0.1f)
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
				this->setPosition(this->getPosition() + (_speedTbl[static_cast<int>(this->GetDIR())]) * 8);
			}
			else
			{
				this->removeFromParent();
			}
			break;
		case ChargeType::TWISTER:
			if (_remainCnt > 0.1f)
			{
				this->removeFromParent();
			}
			break;
		case ChargeType::FLONTAL:
			if (_remainCnt > 0.1f)
			{
				this->removeFromParent();
			}
			break;
		default:
			break;
		}
	}
	_remainCnt += delta;

}

void Weapon::SetWeaponType(Sprite& sp, int chargeLevel)
{
	cocos2d::Vec2 dirOffset = cocos2d::Vec2(0, 0);
	auto offsetCreate = [&](Sprite& sp)
	{
		switch (((Obj&)sp).GetDIR())
		{
		case DIR::UP:
			dirOffset.y = this->getContentSize().height / 2 + 8;
			break;
		case DIR::RIGHT:
			dirOffset.x = this->getContentSize().height / 2 + 8;
			break;
		case DIR::DOWN:
			dirOffset.y = -this->getContentSize().height / 2 - 8;
			break;
		case DIR::LEFT:
			dirOffset.x = -this->getContentSize().height / 2 - 8;
			break;
		default:
			break;
		}
	};
	if (_optionType == OptionType::NOMAL)
	{
		offsetCreate(sp);
	}
	else
	{
		auto anim = AnimationCache::getInstance()->getAnimation("weapon-twist");
		Animation* _oldanim = nullptr;
		switch (this->_chargeType)
		{
		case ChargeType::SHOT:
			this->setContentSize({ 24.0f + 24.0f * (chargeLevel), 24.0f + 24.0f * (chargeLevel) });
			this->_hp = 2;
			break;
		case ChargeType::TWISTER:
			this->setContentSize({ 96.0f + 16.0f * (chargeLevel), 96.0f + 16.0f * (chargeLevel) });
			this->_power += 0.5 * (chargeLevel);
			lpAnimMng.runAnim(*this, *anim, *_oldanim);
			break;
		case ChargeType::FLONTAL:
			this->setContentSize({ 128.0f, 128.0f });
			this->_power *= 1.5 + 0.5 * (chargeLevel);
			offsetCreate(sp);
			break;
		default:
			break;
		}
	}
	switch (chargeLevel)
	{
	case 0:
		this->setColor(Color3B::GREEN);
		break;
	case 1:
		this->setColor(Color3B::YELLOW);
		break;
	case 2:
		this->setColor(Color3B::MAGENTA);
		break;
	case 3:
		this->setColor(Color3B::RED);
		break;
	default:
		break;
	}

	this->SetColSize(sp);
	this->setPosition(sp.getPosition() + dirOffset);
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


