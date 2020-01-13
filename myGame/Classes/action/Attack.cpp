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
		dirOffset.y = 40;
		break;
	case DIR::RIGHT:
		dirOffset.x = 40;
		break;
	case DIR::DOWN:
		dirOffset.y = -40;
		break;
	case DIR::LEFT:
		dirOffset.x = -40;
		break;
	default:
		break;
	}
	auto nowScene = (GameScene*)cocos2d::Director::getInstance()->getRunningScene();
	/*auto enemy = Enemy::createEnemy();
	enemy->setPosition(Vec2(32, 32 + 32));
	nowScene->getChildByName("charLayer")->addChild(enemy);*/
	auto weapon = Weapon::createWeapon(sp);
	weapon->setPosition(sp.getPositionX() + dirOffset.x, sp.getPositionY() + dirOffset.y);
	weapon->setTag(static_cast<int>(objTag::ATTACK));
	weapon->setCameraMask(static_cast<int>(CameraFlag::USER1));
	//nowScene->addChild(weapon);
	nowScene->getChildByName("charLayer")->addChild(weapon);
	return true;
}
