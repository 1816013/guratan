#include "E_Attack.h"
#include "Player.h"

USING_NS_CC;

cocos2d::Sprite* E_Attack::createE_Attack(Sprite& sp, EnemyAttackAI enemyAttackAI)
{
	auto e_attack = E_Attack::create();
	e_attack->_dir = ((Obj&)sp).GetDIR();
	e_attack->SetTargetMove(sp, enemyAttackAI);
	if (enemyAttackAI == EnemyAttackAI::SHOT)
	{
		e_attack->setTexture("image/e_attack/spear.png");
	}
	return e_attack;
}

E_Attack::E_Attack()
{
}

E_Attack::~E_Attack()
{
}

void E_Attack::SetTargetMove(Sprite & sp, EnemyAttackAI enemyAttackAI)
{
	auto gameScene = Director::getInstance()->getRunningScene();
	auto charLayer = gameScene->getChildByName("charLayer");
	this->setPosition(sp.getPosition());
	Vec2 speed = { 6.0f, 6.0f };
	auto player = charLayer->getChildByTag(static_cast<int>(objTag::PLAYER));
	if (player != nullptr)
	{
		// 移動量セット
		_targetPos = player->getPosition();
		Vec2 distance = { _targetPos.x - this->getPositionX() , _targetPos.y - this->getPositionY() };
		switch (enemyAttackAI)
		{
		case EnemyAttackAI::AIMING:
			_radian = atan2(distance.y, distance.x);
			_move.x = cos(_radian) * speed.x;
			_move.y = sin(_radian) * speed.y;
			break;
		case EnemyAttackAI::SHOT:
			switch (_dir)
			{
			case DIR::UP:
				_move.y = speed.y;
				this->setRotation(0.0f);
				break;
			case DIR::RIGHT:
				_move.x = speed.x;
				this->setRotation(90.0f);
				break;
			case DIR::DOWN:
				_move.y = -speed.y;
				this->setRotation(180.0f);
				break;
			case DIR::LEFT:
				_move.x = -speed.x;
				this->setRotation(270.0f);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		
		// 動きからの向き変更
		if (abs(_move.x) > abs(_move.y))
		{
			if (_move.x >= 0.0f)
			{
				_dir = DIR::RIGHT;
			}
			else if(_move.x < 0.0f)
			{
				_dir = DIR::LEFT;
			}
		}
		else
		{
			if (_move.y >= 0.0f)
			{
				_dir = DIR::UP;
			}
			else if (_move.y < 0.0f)
			{
				_dir = DIR::DOWN;
			}
		}
	}

}

bool E_Attack::init()
{
	// ｽﾌﾟﾗｲﾄｸﾗｽの初期化@initを自作したため必要
	if (!Sprite::init())
	{
		return false;
	}
	cocos2d::Rect rect = cocos2d::Rect(0, 0, 16, 16);
	
	this->setTextureRect(rect);
	_hp = 1;
	_power = 1;
	_remainCnt = 0;
	auto size = this->getContentSize() / 2;
	_colSize[static_cast<int>(DIR::UP)] = { Size(-size.width, size.height), Size(size.width, size.height) };
	_colSize[static_cast<int>(DIR::RIGHT)] = { Size(size.width, size.height), Size(size.width, -size.height) };
	_colSize[static_cast<int>(DIR::DOWN)] = { Size(size.width, -size.height), Size(-size.width, -size.height) };
	_colSize[static_cast<int>(DIR::LEFT)] = { Size(-size.width, size.height), Size(-size.width, -size.height) };
	//this->setPosition(100, 100);
	this->scheduleUpdate();
	return true;
}

void E_Attack::update(float delta)
{
//	_remainCnt += delta;
	if (_gameMap->mapColision(*this, _move, _colSize[static_cast<int>(_dir)]))
	{
		this->setPosition(this->getPosition() + _move);
	}
	else
	{
		this->removeFromParent();
	}
	/*if (_remainCnt > 2.0f)
	{
		this->removeFromParent();
	}*/
}





