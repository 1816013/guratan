#include "Obj.h"

Obj::Obj()
{
	_actMng.reset(new ActionMng);
}

Obj::~Obj()
{
}

bool Obj::IsCheckedHP()
{
	auto gameScene = cocos2d::Director::getInstance()->getRunningScene();
	if (gameScene->getName() != "GameScene")
	{
		return false;
	}
	auto charLayer = (Obj*)gameScene->getChildByName("charLayer");
	if (charLayer != nullptr)
	{
		for (auto itr : charLayer->getChildren())
		{
			/*Obj* obj = (Obj*)itr;
			if (obj->GetHP() <= 0)
			{
				obj->removeFromParent();
				return true;
			}*/
		}
	}
	return false;
}

bool Obj::ColisionObj(Obj * hitObj, cocos2d::Layer * layer)
{
	return false;
}

int Obj::GetHP()
{
	return _hp;
}

void Obj::SetHP(int hp)
{
}
