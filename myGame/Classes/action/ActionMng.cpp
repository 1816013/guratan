#include "ActionMng.h"
#include "CheckList.h"
#include "CheckKey.h"
#include "Colision.h"
#include "Move.h"
#include "ChangeLR.h"
#include "Shot.h"
#include "Attack.h"


USING_NS_CC;

ActionMng::ActionMng()
{
}


ActionMng::~ActionMng()
{
}

void ActionMng::AddActModule(const std::string & actName, actModule & module)
{
	if (_moduleMap.find(actName) == _moduleMap.end())
	{
		if (actName == "左移動" || actName == "右移動" || actName == "上移動" || actName == "下移動")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].act.emplace_back(Colision());
			_moduleMap[actName].runAction = Move();
		}
		if (actName == "右向き" || actName == "左向き")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].runAction = ChangeLR();
		}
		if (actName == "剣攻撃")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].runAction = Attack();
		}
	}
}

void ActionMng::update(cocos2d::Sprite& sp)
{
	auto check = [this](Sprite& sp, actModule& module)
	{
		for (auto listModule : module.act)
		{
			if (!listModule(sp, module))
			{
				return false;
			}
		}
		return true;
	};

	bool actFlag = false;
	for (auto mapModule : _moduleMap)
	{
		if (check(sp, mapModule.second))
		{
			if (mapModule.second.runAction(sp, mapModule.second))
			{
				actFlag = true;
			}
		}
	}
}
