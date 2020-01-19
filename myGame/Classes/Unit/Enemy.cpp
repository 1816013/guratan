#include "Enemy.h"
#include <Unit/Player.h>
#include "Weapon.h"
#include "E_Attack.h"
#include "action/Colision.h"


USING_NS_CC;

cocos2d::Sprite * Enemy::createEnemy(EnemyType enemyType)
{
	auto enemy = Enemy::create();
	enemy->physicsBody = PhysicsBody::createBox(Size(32.0f, 32.0f),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	enemy->physicsBody->setRotationEnable(false);//回転運動不可
	//set the body isn't affected by the physics world's gravitational force
	enemy->physicsBody->setGravityEnable(false);
	enemy->SetEnemyAI(enemyType);
	enemy->setTag(static_cast<int>(objTag::ENEMY));
	enemy->setCameraMask(static_cast<int>(CameraFlag::USER1));
	enemy->addComponent(enemy->physicsBody);

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
	
	_hp = 3;
	_power = 1;
	_attackIntarval = 1.5f;
	_exp = 1;
	
	time = 0.0f;
	auto size = this->getContentSize() / 2;
	_colSize[static_cast<int>(DIR::UP)] = { Size(-size.width, size.height), Size(size.width, size.height) };
	_colSize[static_cast<int>(DIR::RIGHT)] = { Size(size.width, size.height), Size(size.width, -size.height) };
	_colSize[static_cast<int>(DIR::DOWN)] = { Size(size.width, -size.height), Size(-size.width, -size.height) };
	_colSize[static_cast<int>(DIR::LEFT)] = { Size(-size.width, size.height), Size(-size.width, -size.height) };

	//this->scheduleUpdate();
	return true;
}

void Enemy::update(float delta)
{
	time += delta;
	auto GameScene = Director::getInstance()->getRunningScene();
	if (GameScene->getName() != "GameScene")
	{
		return;
	}
	auto charLayer = GameScene->getChildByName("charLayer");

	auto player = (Player*)charLayer->getChildByTag(static_cast<int>(objTag::PLAYER));
	
	if (player != nullptr)
	{
		// 向き変更
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
		// 移動（ある奴だけ）　
		if (_enemyMoveAI == EnemyMoveAI::FORROW)
		{
			if (_gameMap->mapColision(*this, _speedTbl[static_cast<int>(_dir)] * 2, _colSize[static_cast<int>(_dir)]))
			{
				this->setPosition(this->getPosition() + _speedTbl[static_cast<int>(_dir)] * 2/** delta * 60*/);
			}
		}
	}
	// 攻撃
	
	if (_enemyAttackAI != EnemyAttackAI::NONE)
	{
		if (time > _attackIntarval)
		{
			time = 0;
			_attackFlag;
			auto e_Attack = E_Attack::createE_Attack(*this, _enemyAttackAI);
			e_Attack->setPosition(this->getPosition());
			e_Attack->setTag(static_cast<int>(objTag::E_ATTACK));
			e_Attack->setCameraMask(static_cast<int>(CameraFlag::USER1));
			charLayer->addChild(e_Attack);
		}
	}
	
}

int Enemy::GetExp()
{
	return _exp;
}

bool Enemy::ColisionObj(Obj& hitObj, cocos2d::Scene& scene)
{
	bool col = false;

	Rect myRect = this->getBoundingBox();
	Rect hitRect = hitObj.getBoundingBox();
	int hitTag = hitObj.getTag();

	if (myRect.intersectsRect(hitRect))
	{
		int hitTag = hitObj.getTag();
		if (hitTag == static_cast<int>(objTag::PLAYER))
		{
			if (!((Player&)hitObj).GetStrong())
			{
				col = true;
				hitObj.SetHP(hitObj.GetHP() - _power);
				((Player&)hitObj).SetStrong(true);
				if (_gameMap->mapColision(hitObj, _speedTbl[static_cast<int>(_dir)] * 32, hitObj._colSize[static_cast<int>(_dir)]))
				{
					hitObj.setPosition(hitObj.getPosition() + (_speedTbl[static_cast<int>(_dir)]) * 32);		// ノックバック処理
				}
			}
		}
	}
	return col;
}

void Enemy::SetEnemyAI(EnemyType enemyType)
{
	switch (enemyType)
	{
	case EnemyType::SLIME:
		_enemyMoveAI = EnemyMoveAI::FORROW;
		_enemyAttackAI = EnemyAttackAI::NONE; 
		_hp = 3;
		break;
	case EnemyType::CANNON:
		_enemyMoveAI = EnemyMoveAI::IDLE;
		_enemyAttackAI = EnemyAttackAI::AIMING;
		_hp = 3;
		_attackIntarval = 2;
		physicsBody->setEnabled(false);
		break;
	case EnemyType::ARCHAR:
		_enemyMoveAI = EnemyMoveAI::FORROW;
		_enemyAttackAI = EnemyAttackAI::SHOT;
		_attackIntarval = ((float)(rand() % 10) / 10) + 2;
		_hp = 5;
		break;
	default:
		break;
	}
}
