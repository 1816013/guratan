#include "Obj.h"
#include "Player.h"
#include "Enemy.h"

USING_NS_CC;

Obj::Obj()
{
	_actMng.reset(new ActionMng);
	_gameMap.reset(new GameMap);
	_speedTbl = { Vec2(0, 1),Vec2(1, 0), Vec2(0, -1), Vec2(-1, 0) };
}

Obj::~Obj()
{
}

bool Obj::IsCheckedHP(Obj& obj)
{
	if (obj.GetHP() <= 0)
	{
		if (obj.getTag() == static_cast<int>(objTag::ENEMY))
		{
			auto player = (Player*)Director::getInstance()->getRunningScene()->getChildByName("charLayer")->getChildByTag(static_cast<int>(objTag::PLAYER));
			if (player == nullptr)
			{
				return false;
			}
			player->addExp(((Enemy&)obj).GetExp());
		}
		obj.removeFromParent();
		return true;
	}

	return false;
}
DIR Obj::GetDIR()
{
	return _dir;
}

void Obj::SetDIR(DIR dir)
{
	_dir = dir;
}

bool Obj::ColisionObj(Obj& hitObj, cocos2d::Scene& scene)
{
	return false;
}

int Obj::GetHP()
{
	return _hp;
}

void Obj::SetHP(const int hp)
{
 	_hp = hp;
}

bool Obj::GetKnockFlag(void)
{
	return _knockF;
}

float Obj::GetPower()
{
	return _power;
}

cocos2d::Vec2 Obj::GetMove(void)
{
	return _move;
}
