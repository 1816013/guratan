#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "E_Attack.h"
#include "action/Colision.h"
#include "AnimMng.h"
#include <UI/DamageText.h>
#include "SoundMng.h"

USING_NS_CC;

cocos2d::Sprite * Enemy::createEnemy(EnemyType enemyType, int floor)
{
	auto enemy = Enemy::create();
	enemy->SetEnemyAI(enemyType, floor);
	enemy->setTag(static_cast<int>(objTag::ENEMY));
	int CameraMask = static_cast<int>(CameraFlag::DEFAULT) | static_cast<int>(CameraFlag::USER1);
	enemy->setCameraMask(static_cast<int>(CameraFlag::USER1));
	return enemy;
}

EnemyType Enemy::GetEnemyType()
{
	return _enemyType;
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
	_dir = DIR::DOWN;
	_oldAnim = nullptr;
	_hp = 3;
	_power = 1;
	_attackIntarval = 1.5f;
	_exp = 1;
	_strongF = false;
	_strongCnt = 0;

	_knockCnt = 0;
	_knockF = false;
	_knockDir = DIR::MAX;
	
	time = 0.0f;
	auto size = this->getContentSize() / 2;
	_colSize[static_cast<int>(DIR::UP)] = { Size(-size.width, size.height), Size(size.width, size.height) };
	_colSize[static_cast<int>(DIR::RIGHT)] = { Size(size.width, size.height), Size(size.width, -size.height) };
	_colSize[static_cast<int>(DIR::DOWN)] = { Size(size.width, -size.height), Size(-size.width, -size.height) };
	_colSize[static_cast<int>(DIR::LEFT)] = { Size(-size.width, size.height), Size(-size.width, -size.height) };

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
	time += delta;
	
	// 無敵判定
	if (_strongF)
	{
		_strongCnt += delta;
		if (_strongCnt >= 0.15f)
		{
			_strongF = false;
			_strongCnt = 0;
		}
	}
	// 向き変更
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
	}
	// 移動（ある奴だけ）　
	if (!_knockF)
	{
		_move = _speedTbl[static_cast<int>(_dir)] * 2;
	}
	else
	{
		_knockCnt += delta;
		_dir = _knockDir;
		if (_knockCnt > 0.1f)
		{
			_knockCnt = 0;
			_knockF = false;
		}
	}
	if (_enemyMoveAI == EnemyMoveAI::FORROW)
	{
		if (_gameMap->mapColision(*this, _move, _colSize[static_cast<int>(_dir)]))
		{
			this->setPosition(this->getPosition() + _move);
		}
	}
	// 攻撃	
	if (_enemyAttackAI != EnemyAttackAI::NONE)
	{
		if (time > _attackIntarval)
		{
			time = 0;
			auto e_Attack = E_Attack::createE_Attack(*this, _enemyAttackAI);
			e_Attack->setPosition(this->getPosition());
			e_Attack->setTag(static_cast<int>(objTag::E_ATTACK));
			
			charLayer->addChild(e_Attack);
		}
	}

	auto anim = SetAnim(_dir);
	lpAnimMng.runAnim(*this, *anim, *_oldAnim, 0);
	_oldAnim = anim;
	
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
		if (hitTag == static_cast<int>(objTag::ATTACK))
		{
			if (!_strongF)
			{
				col = true;
				_strongF = true;
				_hp -= hitObj.GetPower();
				hitObj.SetHP(hitObj.GetHP() - 1);	// 武器の耐久を削る
				_knockF = true;
				_knockDir = hitObj.GetDIR();
				Vec2 distance = { this->getPositionX() - hitObj.getPositionX() , this->getPositionY() - hitObj.getPositionY() };
				auto radian = atan2(distance.y, distance.x);
				_move.x = cos(radian) * 8;
				_move.y = sin(radian) * 8;
				auto damageT = DamageText::createDamageT(hitObj.GetPower(), *this);
				scene.getChildByName("uiLayer")->addChild(damageT);
				lpSoundMng.StopBySoundName("damage2");
				lpSoundMng.PlayBySoundName("damage2");
			}
		}
		// 押し合い判定
		if (hitTag == static_cast<int>(objTag::ENEMY))
		{
			if (_enemyType != EnemyType::CANNON && ((Enemy&)hitObj).GetEnemyType() != EnemyType::CANNON)
			{
				col = true;
				_knockF = true;
				_knockDir = hitObj.GetDIR();
				Vec2 distance = { this->getPositionX() - hitObj.getPositionX() , this->getPositionY() - hitObj.getPositionY() };
				auto radian = atan2(distance.y, distance.x);
				_move.x = cos(radian) * 1;
				_move.y = sin(radian) * 1;
			}
		}
	}
	return col;
}

cocos2d::Animation * Enemy::SetAnim(DIR dir)
{
	auto animCache = AnimationCache::getInstance();
	Animation* anim = nullptr;
	if (EnemyType::SLIME == _enemyType)
	{
		switch (dir)
		{
		case DIR::UP:
			anim = animCache->getAnimation("slime-runB");
			break;
		case DIR::RIGHT:
			anim = animCache->getAnimation("slime-runR");
			this->setFlippedX(false);
			break;
		case DIR::DOWN:
			anim = animCache->getAnimation("slime-runF");
			break;
		case DIR::LEFT:
			anim = animCache->getAnimation("slime-runR");
			this->setFlippedX(true);
			break;
		default:
			break;
		}
		return anim;
	}
	if (EnemyType::ARCHAR == _enemyType)
	{
		switch (dir)
		{
		case DIR::UP:
			anim = animCache->getAnimation("skeleton-runB");
			break;
		case DIR::RIGHT:
			anim = animCache->getAnimation("skeleton-runR");
			this->setFlippedX(false);
			break;
		case DIR::DOWN:
			anim = animCache->getAnimation("skeleton-runF");
			break;
		case DIR::LEFT:
			anim = animCache->getAnimation("skeleton-runR");
			this->setFlippedX(true);
			break;
		default:
			break;
		}
		return anim;
	}
	if (EnemyType::CANNON == _enemyType)
	{
		anim = animCache->getAnimation("orb-idle");
	}
	return anim;
}


void Enemy::SetEnemyAI(EnemyType enemyType, int floor)
{
	_enemyType = enemyType;
	switch (enemyType)
	{
	case EnemyType::SLIME:
		_enemyMoveAI = EnemyMoveAI::FORROW;
		_enemyAttackAI = EnemyAttackAI::NONE; 
		_hp = 2;		
		break;
	case EnemyType::ARCHAR:
		_enemyMoveAI = EnemyMoveAI::FORROW;
		_enemyAttackAI = EnemyAttackAI::SHOT;
		_attackIntarval = cocos2d::random<float>(1.0f, 2.0f);
		_hp = 4;
		break;
	case EnemyType::CANNON:	
		_enemyMoveAI = EnemyMoveAI::IDLE;
		_enemyAttackAI = EnemyAttackAI::AIMING;
		_hp = 5;
		_attackIntarval = 2.0f;
		this->setLocalZOrder(-1);
		break;
	
	default:
		break;
	}
	_exp += floor / 3;
	_hp += floor / 2;
	_power += floor / 5;
}
