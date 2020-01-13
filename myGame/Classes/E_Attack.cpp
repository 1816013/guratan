#include "E_Attack.h"
#include "Unit/Player.h"

USING_NS_CC;

cocos2d::Sprite* E_Attack::createE_Attack(Sprite& sp)
{
	auto e_attack = E_Attack::create();
	e_attack->SetTargetMove(sp);
	return e_attack;
}

E_Attack::E_Attack()
{
}

E_Attack::~E_Attack()
{
}

DIR E_Attack::GetDIR()
{
	return _dir;
}

void E_Attack::SetDIR(DIR dir)
{
	_dir = dir;
}

int E_Attack::GetPower()
{
	return _power;
}

void E_Attack::SetTargetMove(Sprite & sp)
{
	auto gameScene = Director::getInstance()->getRunningScene();
	auto charLayer = gameScene->getChildByName("charLayer");
	this->setPosition(sp.getPosition());
	Vec2 speed = { 3.0f, 3.0f };
	auto player = charLayer->getChildByTag(static_cast<int>(objTag::PLAYER));
	if (player != nullptr)
	{
		_targetPos = player->getPosition();

		_radian = atan2(_targetPos.y - this->getPositionY(), _targetPos.x - this->getPositionX());

		_move.x = cos(_radian) * speed.x;
		_move.y = sin(_radian) * speed.y;
	}

}

bool E_Attack::init()
{
	// ½Ìß×²Ä¸×½‚Ì‰Šú‰»@init‚ðŽ©ì‚µ‚½‚½‚ß•K—v
	if (!Sprite::init())
	{
		return false;
	}
	cocos2d::Rect rect = cocos2d::Rect(0, 0, 16, 16);
	
	this->setTextureRect(rect);
	this->setColor(cocos2d::Color3B(0, 255, 0));
	_hp = 1;
	_power = 1;
	_remainCnt = 0;
	//this->setPosition(100, 100);
	this->scheduleUpdate();
	return true;
}

void E_Attack::update(float delta)
{
	_remainCnt += delta;
	this->setPosition(this->getPosition() + _move);
	if (_remainCnt > 2.0f)
	{
		this->removeFromParent();
	}
}

