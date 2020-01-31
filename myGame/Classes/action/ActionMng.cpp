#include "ActionMng.h"
#include "CheckList.h"
#include "CheckKey.h"
#include "Colision.h"
#include "Move.h"
#include "ChangeLR.h"
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
		if (actName == "���ړ�" || actName == "�E�ړ�" || actName == "��ړ�" || actName == "���ړ�")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].act.emplace_back(actColision());
			_moduleMap[actName].runAction = Move();
		}
		if (actName == "�E����" || actName == "������" || actName == "�����" || actName == "������")
		{
			_moduleMap.emplace(actName, std::move(module));
			_moduleMap[actName].act.emplace_back(CheckList());
			_moduleMap[actName].act.emplace_back(CheckKey());
			_moduleMap[actName].runAction = ChangeDIR();
		}
		if (actName == "���U��")
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
