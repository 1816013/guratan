#include "Obj.h"

Obj::Obj()
{
	_actMng.reset(new ActionMng);
}

Obj::~Obj()
{
}

DIR Obj::GetDIR()
{
	return DIR::MAX;
}

void Obj::SetDIR(DIR dir)
{
}

bool Obj::IsCheckedHP()
{
	auto charLayer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("charLayer");
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
	return false;
}

bool Obj::ColisionObj(Obj * hitObj, cocos2d::Layer * layer)
{
	return false;
}
