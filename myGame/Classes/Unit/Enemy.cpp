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
	// ���ײĸ׽�̏�����@init�����삵�����ߕK�v
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

	//// ���ړ�
	//{
	//	actModule module;
	//	module.actID = ACT_STATE::RUN;
	//	module.speed = Vec2(-2, 0);
	//	module.colSize = { Size(-16, 16), Size(-16, -16) };
	//	module.inputID = INPUT_ID::LEFT;
	//	module.keyTiming = Timing::ON;
	//	module.dir = DIR::LEFT;
	//	_actMng->AddActModule("���ړ�", module);
	//}
	//// �E�ړ�
	//{
	//	actModule module;
	//	module.actID = ACT_STATE::RUN;
	//	module.speed = Vec2(2, 0);
	//	module.colSize = { Size(16, 16), Size(16, -16) };
	//	module.inputID = INPUT_ID::RIGHT;
	//	module.keyTiming = Timing::ON;
	//	module.dir = DIR::RIGHT;
	//	_actMng->AddActModule("�E�ړ�", module);
	//}
	//// ��ړ�
	//{
	//	actModule module;
	//	module.actID = ACT_STATE::RUN;
	//	module.speed = Vec2(0, 2);
	//	module.colSize = { Size(-16, 16), Size(-16, -16) };
	//	module.inputID = INPUT_ID::UP;
	//	module.keyTiming = Timing::ON;
	//	module.dir = DIR::UP;
	//	_actMng->AddActModule("��ړ�", module);
	//}
	//// ���ړ�
	//{
	//	actModule module;
	//	module.actID = ACT_STATE::RUN;
	//	module.speed = Vec2(0, -2);
	//	module.colSize = { Size(-16, 16), Size(-16, -16) };
	//	module.inputID = INPUT_ID::DOWN;
	//	module.keyTiming = Timing::ON;
	//	module.dir = DIR::DOWN;
	//	_actMng->AddActModule("���ړ�", module);
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
			//if (/*��낪�ړ��ł���Ȃ�*/)
			{
				player->setPosition(player->getPosition() + (_speedTbl[static_cast<int>(_dir)]) * 16);		// �m�b�N�o�b�N����
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

