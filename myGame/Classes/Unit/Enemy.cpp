#include "Enemy.h"
#include <Unit/Player.h>
#include "Weapon.h"
#include "E_Attack.h"


USING_NS_CC;

cocos2d::Sprite * Enemy::createEnemy(EnemyMoveAI enemyAI)
{
	auto enemy = Enemy::create();

	enemy->SetEnemyAI(enemyAI);
	return enemy;
}

EnemyMoveAI Enemy::GetEnemyAI()
{
	return _enemyMoveAI;
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

bool Enemy::init()
{
	// ｽﾌﾟﾗｲﾄｸﾗｽの初期化@initを自作したため必要
	if (!Sprite::init())
	{
		return false;
	}
	//auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	Rect rect = Rect(0, 0, 32, 32);
	this->setTextureRect(rect);
	this->setColor(cocos2d::Color3B(255, 0, 0));
	_speedTbl = { Vec2(0, 2),Vec2(2, 0), Vec2(0, -2), Vec2(-2, 0) };
	_hp = 3;
	_power = 1;
	_attackIntarval = 1;
	_enemyAttackAI = EnemyAttackAI::AIMING;
	time = 0.0f;

	//// 左移動
	//{
	//	actModule module;
	//	module.actID = ACT_STATE::RUN;
	//	module.speed = Vec2(-2, 0);
	//	module.colSize = { Size(-16, 16), Size(-16, -16) };
	//	module.inputID = INPUT_ID::LEFT;
	//	module.keyTiming = Timing::ON;
	//	module.dir = DIR::LEFT;
	//	_actMng->AddActModule("左移動", module);
	//}
	//// 右移動
	//{
	//	actModule module;
	//	module.actID = ACT_STATE::RUN;
	//	module.speed = Vec2(2, 0);
	//	module.colSize = { Size(16, 16), Size(16, -16) };
	//	module.inputID = INPUT_ID::RIGHT;
	//	module.keyTiming = Timing::ON;
	//	module.dir = DIR::RIGHT;
	//	_actMng->AddActModule("右移動", module);
	//}
	//// 上移動
	//{
	//	actModule module;
	//	module.actID = ACT_STATE::RUN;
	//	module.speed = Vec2(0, 2);
	//	module.colSize = { Size(-16, 16), Size(-16, -16) };
	//	module.inputID = INPUT_ID::UP;
	//	module.keyTiming = Timing::ON;
	//	module.dir = DIR::UP;
	//	_actMng->AddActModule("上移動", module);
	//}
	//// 下移動
	//{
	//	actModule module;
	//	module.actID = ACT_STATE::RUN;
	//	module.speed = Vec2(0, -2);
	//	module.colSize = { Size(-16, 16), Size(-16, -16) };
	//	module.inputID = INPUT_ID::DOWN;
	//	module.keyTiming = Timing::ON;
	//	module.dir = DIR::DOWN;
	//	_actMng->AddActModule("下移動", module);
	//}



	this->scheduleUpdate();
	return true;
}

void Enemy::update(float delta)
{
	auto GameScene = Director::getInstance()->getRunningScene();
	if (GameScene->getName() != "GameScene")
	{
		return;
	}
	auto charLayer = GameScene->getChildByName("charLayer");

	auto player = (Player*)charLayer->getChildByTag(static_cast<int>(objTag::PLAYER));
	if (player != nullptr)
	{
		//int dir = rand() % static_cast<int>(DIR::MAX);
		if (abs(this->getPositionX() - player->getPositionX()) > abs(this->getPositionY() - player->getPositionY()))
		{
			if (this->getPositionX() < player->getPositionX())
			{
				_dir = DIR::RIGHT;
			}
			else
			{
				_dir = DIR::LEFT;
			}
		}
		else
		{
			if (this->getPositionY() < player->getPositionY())
			{
				_dir = DIR::UP;
			}
			else
			{
				_dir = DIR::DOWN;
			}
		}
		if (_enemyMoveAI == EnemyMoveAI::FORROW)
		{
			this->setPosition(this->getPosition() + _speedTbl[static_cast<int>(_dir)] /** delta * 60*/);
		}
	}
	time += delta;
	if (_enemyAttackAI == EnemyAttackAI::AIMING)
	{
		if (time > _attackIntarval)
		{
			time = 0;
			auto e_Attack = E_Attack::createE_Attack(*this);
			e_Attack->setPosition(this->getPosition());
			e_Attack->setTag(static_cast<int>(objTag::E_ATTACK));
			e_Attack->setCameraMask(static_cast<int>(CameraFlag::USER1));
			charLayer->addChild(e_Attack);
		}
	}
		
	
	_actMng->update(*this);
	//this->setPosition(this->getPosition() + _speedTbl[dir]);

}

int Enemy::GetHP()
{
	return _hp;
}

void Enemy::SetHP(int hp)
{
	_hp = hp;
}

int Enemy::GetPower()
{
	return _power;
}

bool Enemy::ColisionObj(Obj * hitObj, cocos2d::Layer * layer)
{
	bool col = false;

	Rect myRect = this->getBoundingBox();
	Rect hitRect = hitObj->getBoundingBox();
	int hitTag = hitObj->getTag();
	if (hitTag == static_cast<int>(objTag::E_ATTACK))
	{
		return false;
	}
	if (myRect.intersectsRect(hitRect))
	{
		int hitTag = hitObj->getTag();
		if (hitTag == static_cast<int>(objTag::PLAYER))
		{
			Player* player = (Player*)hitObj;
			player->SetHP(player->GetHP() -_power);
			//if (/*後ろが移動できるなら*/)
			{
				player->setPosition(player->getPosition() + (_speedTbl[static_cast<int>(_dir)]) * 16);		// ノックバック処理
			}
		}
		else if(hitTag == static_cast<int>(objTag::ATTACK))
		{
			Weapon* weapon = (Weapon*)hitObj;
			_hp -= weapon->GetPower();
			auto dir = weapon->GetDIR();
			this->setPosition(this->getPosition() + (_speedTbl[static_cast<int>(weapon->GetDIR())]) * 16);
			hitObj->removeFromParent();
		}
		col = true;
	}
	return col;
}

void Enemy::SetEnemyAI(EnemyMoveAI enemyAI)
{
	_enemyMoveAI = enemyAI;
}



DIR Enemy::GetDIR()
{
	return _dir;
}

void Enemy::SetDIR(DIR dir)
{
	_dir = dir;
}

