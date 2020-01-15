#include "Attack.h"
#include "Colision.h"
#include "GameScene.h"
#include <Unit/Obj.h>
#include "Weapon.h"
#include "Unit/Enemy.h"

USING_NS_CC;

bool Attack::operator()(cocos2d::Sprite & sp, actModule & module)
{
	cocos2d::Vec2 dirOffset = cocos2d::Vec2(0, 0);
	switch (((Obj&)sp).GetDIR())
	{
	case DIR::UP:
		dirOffset.y = 32;
		break;
	case DIR::RIGHT:
		dirOffset.x = 32;
		break;
	case DIR::DOWN:
		dirOffset.y = -32;
		break;
	case DIR::LEFT:
		dirOffset.x = -32;
		break;
	default:
		break;
	}
	auto nowScene = (GameScene*)cocos2d::Director::getInstance()->getRunningScene();
	/*auto enemy = Enemy::createEnemy();
	enemy->setPosition(Vec2(32, 32 + 32));
	nowScene->getChildByName("charLayer")->addChild(enemy);*/
	auto SetWeapon = [](Scene& scene,Sprite& sp, Vec2 offset,Size size,  OptionType optionType)
	{
		auto weapon = Weapon::createWeapon(sp, optionType);
		weapon->setPosition(sp.getPositionX() + offset.x, sp.getPositionY() + offset.y);
		weapon->setTag(static_cast<int>(objTag::ATTACK));
		weapon->setContentSize(size);
		weapon->setCameraMask(static_cast<int>(CameraFlag::USER1));
		//nowScene->addChild(weapon);
		scene.getChildByName("charLayer")->addChild(weapon);
	};
	SetWeapon(*nowScene, sp, Vec2(0, 0), { 16, 16 }, OptionType::RANGE);
	//SetWeapon(*nowScene, sp, dirOffset, { 32, 32 }, OptionType::NOMAL);
	
		//weapon = Weapon::createWeapon(sp, OptionType::RANGE);
		//weapon->setPosition(sp.getPositionX() + dirOffset.x, sp.getPositionY() + dirOffset.y);
		//weapon->setTag(static_cast<int>(objTag::ATTACK));
		//weapon->setCameraMask(static_cast<int>(CameraFlag::USER1));
		////nowScene->addChild(weapon);
		//nowScene->getChildByName("charLayer")->addChild(weapon);
	
	return true;
}
