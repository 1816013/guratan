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
	auto followLayer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("followLayer");
	if (followLayer != nullptr)
	{
		auto charLayer = (Obj*)followLayer->getChildByName("charLayer");
		if (charLayer != nullptr)
		{
			for (auto itr : charLayer->getChildren())
			{
				Obj* obj = (Obj*)itr;
				if (obj->GetHP() <= 0)
				{
					obj->removeFromParent();
					return true;
				}
			}
		}
	}

	return false;
}

bool Obj::ColisionObj(Obj * hitObj, cocos2d::Layer * layer)
{
	return false;
}
