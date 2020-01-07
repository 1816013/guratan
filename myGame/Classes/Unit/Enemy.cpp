#include "Enemy.h"
#include <Unit/Player.h>
#include <GameScene.h>

USING_NS_CC;

cocos2d::Sprite * Enemy::createEnemy(EnemyAI enemyAI)
{
	auto enemy = Enemy::create();

	enemy->SetEnemyAI(enemyAI);
	return enemy;
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

int Enemy::GetHP()
{
	return _hp;
}

void Enemy::SetHP(int hp)
{
	_hp = hp;
}

void Enemy::SetEnemyAI(EnemyAI enemyAI)
{
	_enemyAI = enemyAI;
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
	_hp = 1;
	_power = 1;

	this->scheduleUpdate();
	return true;
}

void Enemy::update(float delta)
{
	auto charLayer = (Player*)Director::getInstance()->getRunningScene()->getChildByName("charLayer");
	if (charLayer != nullptr)
	{
		auto player = charLayer->getChildByTag(static_cast<int>(objTag::PLAYER));
		//int dir = rand() % static_cast<int>(DIR::MAX);
		if (_enemyAI == EnemyAI::FORROW)
		{
			if (player != nullptr)
			{
				if (this->getPositionX() < player->getPositionX())
				{
					this->setPosition(this->getPosition() + _speedTbl[static_cast<int>(DIR::RIGHT)]);
				}
				else
				{
					this->setPosition(this->getPosition() + _speedTbl[static_cast<int>(DIR::LEFT)]);
				}
				if (this->getPositionY() < player->getPositionY())
				{
					this->setPosition(this->getPosition() + _speedTbl[static_cast<int>(DIR::UP)]);
				}
				else
				{
					this->setPosition(this->getPosition() + _speedTbl[static_cast<int>(DIR::DOWN)]);
				}
			}
		}
	}
	//this->setPosition(this->getPosition() + _speedTbl[dir]);
	
}

DIR Enemy::GetDIR()
{
	return _dir;
}

void Enemy::SetDIR(DIR dir)
{
	_dir = dir;
}

