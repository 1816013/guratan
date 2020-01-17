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
	/*auto gameScene = cocos2d::Director::getInstance()->getRunningScene();
	if (gameScene->getName() != "GameScene")
	{
		return false;
	}
	auto charLayer = (Obj*)gameScene->getChildByName("charLayer");
	if (charLayer != nullptr)
	{
		for (auto itr : charLayer->getChildren())
		{*/
			//Obj* obj = (Obj*)itr;
			if (obj.GetHP() <= 0)
			{
				if (obj.getTag() == static_cast<int>(objTag::ENEMY))
				{
					auto player = (Player*)Director::getInstance()->getRunningScene()->getChildByName("charLayer")->getChildByTag(static_cast<int>(objTag::PLAYER));
					player->addExp(((Enemy&)obj).GetExp());
				}
				obj.removeFromParent();
				return true;
			}
		//}
	//}
	return false;
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
}
